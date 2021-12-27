#ifndef _GAMESTATE_H_
#define _GAMESTATE_H_

#include "player.h"
#include <memory>
#include <vector>

class GameState {
    int maxScore = 0; // keeps track of the maximum score
    int currentPlayer;
    bool roundStart = true;
    bool gameOver = false;
    bool roundOver = false;

    std::vector<std::shared_ptr<Player>> players;

    public:
        GameState();

        ~GameState();

        // in game controller, after inputting all players, will pass vector of players into here to update players
        void setPlayers(std::vector<std::shared_ptr<Player>> &listofplayers);

        void setMaxScore();

        void setCurrentPlayer(); // if round start, set current player sets to player with 7S

        int getCurrentPlayer() const; 

        bool isGameOver() const;

        bool isRoundOver() const;
        
        // changes value of gameOver. If game over, set to true. else, set to false. 
        void setGameOver();

        // changes value of roundOver. If round over, set to true. else, set to false
        void setRoundOver();

        std::shared_ptr<Player> getPlayer(int playerNum);

        std::vector<int> getWinners() const;

        // changes player to a computer player
        // passes in player num that will be replaced by a computer player
        void rageQuit(int currplayer);

        void reset();

        void setRoundStart();

        // ends game if command is quit
        void endGame();
};

#endif