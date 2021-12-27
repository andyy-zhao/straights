#include "gamecontroller.h"
#include "player.h"
#include "card.h"
#include "table.h"
#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>

GameController::GameController(std::default_random_engine rng) : rng{rng} {}

std::shared_ptr<Table> GameController::getTable() {
    return table;
}

std::shared_ptr<Deck> GameController::getDeck() {
    return deck;
}

std::shared_ptr<GameState> GameController::getGameState() {
    return gameState;
}

std::vector<std::shared_ptr<Player>> GameController::getPlayers() {
    return players;
}

void GameController::startGame() {
    // creating deck pointer with rng
    deck = std::make_shared<Deck>(rng);
    deck->createDeck(); // creates deck
    table = std::make_shared<Table>();
    gameState = std::make_shared<GameState>();
    // currently, all players have score = 0; deck has just been created (not shuffled). 
}

void GameController::invitePlayers() {
    for (int i = 1; i <= 4; ++i) {
        std::cout << "Is Player" << i << " a human (h) or a computer (c)?" << std::endl;
        std::string s;
        std::cin >> s;
        if (s == "h") {
            players.emplace_back(std::make_shared<Player>(table, i));
        }
        else if (s == "c") {
            std::shared_ptr<Player> computerplayer = std::make_shared<Player>(table, i);
            computerplayer->becomeComputerPlayer();
            players.emplace_back(computerplayer);
        }
    }
    gameState->setPlayers(players);
}

void GameController::dealCards() {
    for (int i = 0; i < 52; ++i) {
        std::shared_ptr<Card> tempcard = deck->getCard(i);
        if (i < 13) {
            players[0]->addCard(tempcard);
        }
        else if (i < 26) {
            players[1]->addCard(tempcard);
        }
        else if (i < 39) {
            players[2]->addCard(tempcard);
        }
        else {
            players[3]->addCard(tempcard);
        }
    }
}

void GameController::startRound() {
    table->clearTable();
    gameState->reset(); // setting roundOver to false again.
    gameState->setRoundStart();
    // reset players hands
    for (size_t i = 0; i < players.size(); ++i) {
        players[i]->clearHand();
        players[i]->clearDiscardPile();
    }
    // shuffle deck once
    deck->shuffle();
    dealCards();
    
    gameState->setCurrentPlayer();

    int currplayer = gameState->getCurrentPlayer();

    std::cout << "A new round begins. It's Player" << currplayer << "'s turn to play." << std::endl;
    std::cout << "Cards on the table:" << std::endl;
    std::cout << "Clubs:" << std::endl;
    std::cout << "Diamonds:" << std::endl;
    std::cout << "Hearts:" << std::endl;
    std::cout << "Spades:" << std::endl;
}

void GameController::playRound() {
    // while the round is not over
    while (!gameState->isRoundOver()) { 
        // each of the 4 players take their turns
        for (int i = 0; i < 4; ++i) {
            if (gameState->isRoundOver() || gameState->isGameOver()) {
                break;
            }

            int currentplayer = gameState->getCurrentPlayer();

            players[currentplayer - 1]->setLegalPlays();

            std::cout << "Your hand:";
            printHand(currentplayer);
            std::cout << std::endl;

            std::cout << "Legal plays:";
            printLegalPlays(currentplayer);
            std::cout << std::endl;

            // if human player
            if (players[currentplayer - 1]->getType() == "h") {

                while (true) {
                    std::string s1;
                    getline(std::cin, s1);
                    std::istringstream ss1{s1};

                    // command input
                    std::string s;
                    ss1 >> s;
                    
                    if (s == "play") {
                        // card input
                        Card tempcard;
                        ss1 >> tempcard;
                        std::shared_ptr<Card> playcard = std::make_shared<Card>(tempcard.getSuit(), tempcard.getRank());
                        int cardatindex = players[currentplayer - 1]->findCard(tempcard); // if the card is in their hand
                        bool playIsLegal = table->isLegalPlay(playcard); // if the card is a legal play
                        if (playIsLegal && (cardatindex >= 0)) { // if card was found in their hand and is a legal play
                            std::cout << "Player" << currentplayer << " plays " << playcard->printCard() << "." << std::endl;
                            players[currentplayer - 1]->playCard(playcard);
                            break;
                        }
                        else {
                            std::cout << "This is not a legal play." << std::endl;
                        }
                    } // if "play"
                    else if (s == "discard") {
                        Card tempcard;
                        ss1 >> tempcard;
                        std::shared_ptr<Card> discardcard = std::make_shared<Card>(tempcard.getSuit(), tempcard.getRank());

                        // assume that the card is in player's hand
                        if (players[currentplayer - 1]->getNumLegalPlays() == 0) {
                            std::cout << "Player" << currentplayer << " discards " << discardcard->printCard() << "." << std::endl;
                            players[currentplayer - 1]->discard(discardcard);
                            table->discard();
                            break;
                        }
                        else {
                            std::cout << "You have a legal play. You may not discard." << std::endl;
                        }
                    } // else if "discard"
                    else if (s == "deck") {
                        deck->printDeck();
                    } // else if "deck"
                    else if (s == "quit") {
                        exit(0);
                    } // else if "quit"
                    else if (s == "ragequit") {
                        std::cout << "Player" << currentplayer << " ragequits. A computer will now take over." << std::endl;
                        gameState->rageQuit(currentplayer); // does this do exactly what below does? to change the player type
                        break;
                    } // else if "ragequit"
                } // while
            } // if 
            // if computer player
            if (players[currentplayer - 1]->getType() == "c") {
                if (players[currentplayer - 1]->getNumLegalPlays() > 0) {
                    std::cout << "Player" << currentplayer << " plays " << players[currentplayer - 1]->getFirstLegalPlay()->printCard() << "." << std::endl;
                    players[currentplayer - 1]->playCard(players[currentplayer - 1]->getFirstLegalPlay());
                }
                else if (players[currentplayer - 1]->getNumCardsinHand() > 0) {
                    std::cout << "Player" << currentplayer << " discards " << players[currentplayer - 1]->getFirstCard()->printCard() << "." << std::endl;
                    players[currentplayer - 1]->discard(players[currentplayer - 1]->getFirstCard());
                    table->discard();
                }
                else {
                    gameState->setRoundOver();
                }
            }
            if (gameState->isRoundOver()) {
                break;
            }
            gameState->setCurrentPlayer();
        } // for

        gameState->setMaxScore();

        gameState->setRoundOver();
        gameState->setGameOver();
    } // while
    for (size_t i = 0; i < players.size(); ++i) {
        players[i]->updateScore(); // updating old score, discardscore, and score.
    }
}

void GameController::printHand(int playerNum) {
    std::vector<std::shared_ptr<Card>> playerhand = players[playerNum - 1]->getHand();
    
    for (size_t i = 0; i < playerhand.size(); ++i) {
        std::shared_ptr<Card> tempcard = playerhand[i];
        std::cout << " " << tempcard->printCard();
    }
}

void GameController::printLegalPlays(int playerNum) {
    std::vector<std::shared_ptr<Card>> legalplays = players[playerNum - 1]->getLegalPlays();
    for (size_t i = 0; i < legalplays.size(); ++i) {
        std::cout << " " << legalplays[i]->printCard();
    }
}

void GameController::printEndRoundResults() {
    for (int i = 1; i <= 4; ++i) {
        std::vector<std::shared_ptr<Card>> discards = players[i - 1]->getDiscardPile();
        std::cout << "Player" << i << "'s discards:";
        for (size_t j = 0; j < discards.size(); ++j) {
            std::cout << " " << discards[j]->printCard();
        }
        std::cout << std::endl;
        int oldscore = players[i - 1]->getOldScore();
        int discardscore = players[i - 1]->getDiscardPileScore();
        int updatedscore = players[i - 1]->getScore();
        std::cout << "Player" << i << "'s score: " << oldscore << " + " << discardscore << " = " << updatedscore << std::endl; 
        if (updatedscore >= 80) {
            // as of now, roundOver is true;
            gameState->setGameOver();
        }
        gameState->setMaxScore();
    }
}

void GameController::printWinners() {
    std::vector<int> winners = gameState->getWinners();

    for (size_t i = 0; i < winners.size(); ++i) {
        std::cout << "Player" << winners[i] << " wins!" << std::endl;
    }
}