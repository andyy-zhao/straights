#include "table.h"
#include "gamestate.h"
#include <iostream>

GameState::~GameState() {}

GameState::GameState() {}

void GameState::setPlayers(std::vector<std::shared_ptr<Player>> &listofplayers) {
    players = listofplayers;
}

void GameState::setMaxScore() {
    for (size_t i = 0; i < players.size(); ++i) {
        if (players[i]->getScore() > maxScore) {
            maxScore = players[i]->getScore();
        }
    }
}

void GameState::setCurrentPlayer() {
    if (roundStart) {
        for (size_t i = 0; i < players.size(); ++i) {
            if (players[i]->startingPlayer()) { // if player has 7S
                currentPlayer = i + 1; // accounting for index
            }
        }
        roundStart = false;
    }
    else {
        ++currentPlayer;
        if (currentPlayer > 4) {
            currentPlayer = 1;
        }
    }
}

int GameState::getCurrentPlayer() const {
    return currentPlayer;
}

bool GameState::isGameOver() const {
    return gameOver;
}

bool GameState::isRoundOver() const {
    return roundOver;
}

void GameState::setGameOver() {
    if (isRoundOver() && (maxScore >= 80)) {
        gameOver = true;
    }
}

void GameState::setRoundOver() {
    setMaxScore();
    for (size_t i = 0; i < players.size(); ++i) {
        if (players[i]->isHandEmpty()) {
            roundOver = true;
        }
    }
}

std::shared_ptr<Player> GameState::getPlayer(int playerNum) {
    return players[playerNum - 1];
}

std::vector<int> GameState::getWinners() const {
    std::vector<int> winners;
    int minscore = players[0]->getScore();
    winners.emplace_back(1);

    for (size_t i = 1; i < players.size(); ++i) {
        if (players[i]->getScore() < minscore) {
            minscore = players[i]->getScore();
            winners.clear();
            winners.emplace_back(i + 1);
        }
        else if (players[i]->getScore() == minscore) {
            winners.emplace_back(i + 1);
        }
    }
    return winners;
}

void GameState::rageQuit(int currplayer) { 
    players[currplayer - 1]->becomeComputerPlayer();
}

void GameState::reset() {
    roundOver = false;
}

void GameState::endGame() {
    roundOver = true;
    gameOver = true;
}

void GameState::setRoundStart() {
    roundStart = true;
}