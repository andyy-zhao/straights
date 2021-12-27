#ifndef _GAMECONTROLLER_H_
#define _GAMECONTROLLER_H_

#include "deck.h"
#include "table.h"
#include "gamestate.h"
#include <memory>
#include <vector>
#include "player.h"

class GameController {
    std::default_random_engine rng;
    std::shared_ptr<Table> table;
    std::shared_ptr<GameState> gameState;
    std::shared_ptr<Deck> deck;
    std::vector<std::shared_ptr<Player>> players;

    public:
        // if passed in as argument, use that. otherwise use time
        GameController(std::default_random_engine rng);

        std::shared_ptr<Table> getTable();

        std::shared_ptr<Deck> getDeck();

        std::shared_ptr<GameState> getGameState();

        std::vector<std::shared_ptr<Player>> getPlayers();

        // initializes GAME start. shuffles deck, creates table, resets everything. Clearing scores, 
        void startGame();

        // taking in input and assigning players to players vector
        void invitePlayers();

        // deals cards to players
        void dealCards();

        // start a new round. removes current player's cards, clears table, shuffles deck, assigns new cards, set starting player
        void startRound();

        // play the new round.
        void playRound();

        void printEndRoundResults();

        void printWinners();

        void printHand(int playerNum);

        void printLegalPlays(int playerNum);
};

#endif