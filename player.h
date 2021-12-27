#ifndef _PLAYER_H_
#define _PLAYER_H_
#include <vector>
#include <memory>
#include "card.h"
#include "table.h"

class Player {
    std::shared_ptr<Table> table;

    // current cards in hand
    std::vector<std::shared_ptr<Card>> hand; 

    // current discard pile
    std::vector<std::shared_ptr<Card>> discardpile; 

    int playerNum;
    int score = 0; // default value
    int discardPileScore = 0;
    int oldScore = 0;

    // list of legal plays
    std::vector<std::shared_ptr<Card>> legalplays; 

    std::string playerType = "h"; // default value

    public: 
        Player(std::shared_ptr<Table> table, int playerNum);

        ~Player();

        void addCard(std::shared_ptr<Card> card);

        int findCard(Card card) const;

        void discard(std::shared_ptr<Card> card);

        void playCard(std::shared_ptr<Card> card);

        // determines if the player has the 7 of Spades
        bool startingPlayer() const;

        bool isHandEmpty() const;

        int getScore() const;

        int getOldScore() const;

        int getDiscardPileScore();

        void updateScore();

        int getPlayerNum() const;

        // when a new round starts
        void clearHand();

        // when a new round starts
        void clearDiscardPile();

        // used for discarding first card in hand for computer players
        std::shared_ptr<Card> getFirstCard();
        
        // for playing first card in legalplays for computer players
        std::shared_ptr<Card> getFirstLegalPlay();

        int getNumDiscards() const;

        int getNumCardsinHand() const;

        // when this returns 0, then player must discard
        int getNumLegalPlays() const;

         // updates the legal plays because each round it changes
        void setLegalPlays();

        std::vector<std::shared_ptr<Card>> getHand();

        std::vector<std::shared_ptr<Card>> getDiscardPile();

        std::vector<std::shared_ptr<Card>> getLegalPlays();

        std::shared_ptr<Table> getTable();

        // returns pointer to card at index i
        std::shared_ptr<Card> getCard(int i) const;

        // converts human player to computer player
        void becomeComputerPlayer(); 

        // returns type of player (Human / Computer)
        std::string getType() const;
};

#endif