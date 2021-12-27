#include "deck.h"
#include "card.h"
#include <memory>
#include <vector>
#include <algorithm>
#include <iostream>
#include <string>
#include <random>
#include <chrono>

Deck::Deck(std::default_random_engine rng) : rng{rng} {}

void Deck::shuffle() {
	std::shuffle( cards.begin(), cards.end(), rng );		
}

void Deck::createDeck() {
    std::string suit;
    for (int i = 0; i < 4; ++i) { // suits
        for (int j = 0; j < 13; ++j) { // ranks

            if (i == 0) {
                suit = "C"; // clubs
            }
            else if (i == 1) {
                suit = "D"; // diamonds
            }
            else if (i == 2) {
                suit = "H"; // hearts
            }
            else {
                suit = "S"; // spades
            }
            // the deck is a vector of cards, each element in the vector is a shared pointer to a card.
            cards.emplace_back(std::make_shared<Card>(Suit(i), Rank(j + 1)));  
        }
    }
}

std::shared_ptr<Card> Deck::getCard(int i) const {
    return cards.at(i); 
}

void Deck::printDeck() {
    int count = 0;
    bool firstline = true;
    for (int i = 0; i < 52; ++i) {
        if ( (count % 13) == 0 ) {
            if (firstline != true) {
                std::cout << std::endl; // printing on new line 
            }
            firstline = false;
        }
        if ( (count == 0) || (i == 13) || (i == 26) || (i == 39) ) { // first one of row
            std::cout << getCard(i)->printCard();
        }
        else {
            std::cout << " " << getCard(i)->printCard();
        }
        ++count;
    }
    std::cout << std::endl;
}