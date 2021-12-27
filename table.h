#ifndef _TABLE_H_
#define _TABLE_H_

#include "card.h"
#include "subject.h"
#include <map>
#include <vector>
#include <memory>
#include <algorithm>

class Table: public Subject {

    std::map<Suit, std::vector<std::shared_ptr<Card>>> playedCards; 
    std::shared_ptr<Card> lastPlayed;

    public:
        Table();

        void addCard(Suit &suit, std::shared_ptr<Card> card);

        void discard();
        
        // used prior to start of new round
        void clearTable(); 

        // checks if a play is legal
        bool isLegalPlay(std::shared_ptr<Card> card);

        // for start of round, if empty, only legal play is 7S
        bool isTableEmpty(); 

        // returns the pile (vector) of cards of a specific suit
        std::vector<std::shared_ptr<Card>> getPile(Suit suit);
};

#endif