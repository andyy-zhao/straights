#ifndef _CARD_H_
#define _CARD_H_

#include <iostream>
#include <string>

enum Suit{ C = 0, D, H, S };
enum Rank { ACE = 1, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING };

class Card {
    Suit suit;
    Rank rank;

    friend std::istream &operator>>(std::istream &in, Card &c);

    public:
        Card(Suit suit, Rank rank); // constructor

        Card(); // default constructor

        Suit getSuit() const;

        Rank getRank() const;
        
        std::string printCard() const; // returns string representing card 
};

bool operator==(const Card &c1, const Card &c2);

std::ostream &operator<<(std::ostream &out, const Card &c1);

std::istream &operator>>(std::istream &in, Card &c1);

#endif