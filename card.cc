#include "card.h"
#include <string>
using namespace std;

Card::Card(Suit suit, Rank rank) 
    : suit{suit}, rank{rank} {} 

Card::Card() {}

Suit Card::getSuit() const {
    return suit;
}

Rank Card::getRank() const {
    return rank;
}

string Card::printCard() const {
    // array of strings
    string ranks[13] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "T", "J", "Q", "K"};
    string suits[4] = {"C", "D", "H", "S"};

    string s = ranks[rank-1] + suits[suit];
    return s;
}

bool operator==(const Card &c1, const Card &c2) {
    return c1.getSuit() == c2.getSuit() && c1.getRank() == c2.getRank();
}

ostream &operator<<(ostream &out, const Card &c1) {
    out << c1.getRank() << c1.getSuit();
    return out;
}

istream &operator>>(istream &in, Card &c1) {
    string s;
    in >> s; 
    string listofranks = "A23456789TJQK";
    if ( listofranks.find(s.at(0)) != string::npos ) {
        size_t found = listofranks.find(s.at(0)); // returns index of where it is found in listofranks
        c1.rank = static_cast<Rank>(found + 1);
    }
    string listofsuits = "CDHS";
    if ( listofsuits.find(s.at(1)) != string::npos ) {
        size_t found = listofsuits.find(s.at(1));
        c1.suit = static_cast<Suit>(found);
    }

    return in;
}