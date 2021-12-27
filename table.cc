#include "table.h"
#include "card.h"
#include <iostream>
#include <vector>

Table::Table() : lastPlayed(std::make_shared<Card>(S, SEVEN)) {
    // creating empty piles
    playedCards[S] = std::vector<std::shared_ptr<Card>>();
    playedCards[C] = std::vector<std::shared_ptr<Card>>();
    playedCards[D] = std::vector<std::shared_ptr<Card>>();
    playedCards[H] = std::vector<std::shared_ptr<Card>>();
}

bool mysortingfunction(std::shared_ptr<Card> &card1, std::shared_ptr<Card> &card2) {
    return card1->getRank() < card2->getRank();
}

void Table::addCard(Suit &suit, std::shared_ptr<Card> card) {
    playedCards[suit].emplace_back(card);
    lastPlayed = card;

    std::sort( playedCards[suit].begin(), playedCards[suit].end(), mysortingfunction);

    Subject::notifyObservers(); 
}

void Table::discard() {
    Subject::notifyObservers();
}

bool Table::isLegalPlay(std::shared_ptr<Card> card) {
    Suit suit = card->getSuit();
    Rank rank = card->getRank();

    if ((card->getRank() == 7) && !isTableEmpty()) { // if table is not empty
        return true;
    }
    else if ((card->getRank() == 7) && (card->getSuit() == S)) { // if table is empty
        return true;
    }
    else {
        for (size_t i = 0; i < playedCards[suit].size(); ++i) {
            if (playedCards[suit][i]->getRank() == (rank - 1) || playedCards[suit][i]->getRank() == (rank + 1)) {
                return true;
            }
        }
    }
    return false;  
}

void Table::clearTable() {
    for (auto it = playedCards.begin(); it != playedCards.end(); ++it) {
        it->second.clear(); // removing (clearing) piles
    }
    // creating empty piles
    playedCards[S] = std::vector<std::shared_ptr<Card>>();
    playedCards[C] = std::vector<std::shared_ptr<Card>>();
    playedCards[D] = std::vector<std::shared_ptr<Card>>();
    playedCards[H] = std::vector<std::shared_ptr<Card>>();

}

bool Table::isTableEmpty() {
    return (playedCards[S].size() == 0) && (playedCards[C].size() == 0) && (playedCards[D].size() == 0) && (playedCards[H].size() == 0);
}

std::vector<std::shared_ptr<Card>> Table::getPile(Suit suit) {
    return playedCards[suit];
}