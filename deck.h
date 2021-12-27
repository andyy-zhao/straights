#ifndef _DECK_H_
#define _DECK_H_

#include <algorithm>
#include <memory>
#include <vector>
#include "card.h"
#include <iostream>
#include <random>
#include <chrono>

class Deck {
    std::default_random_engine rng;
    std::vector<std::shared_ptr<Card>> cards;

    public:
        Deck(std::default_random_engine rng); // shuffle deck before handing out cards. 

        void shuffle();

        void createDeck();

        std::shared_ptr<Card> getCard(int i) const; // return the card at index i in the deck

        void printDeck();
};

#endif