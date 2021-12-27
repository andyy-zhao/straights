#include "player.h"
#include <iostream>
#include "card.h"
#include "table.h"

Player::Player(std::shared_ptr<Table> table, int playerNum) : table{table}, playerNum{playerNum} {}

Player::~Player() {}

void Player::addCard(std::shared_ptr<Card> card) {
    hand.emplace_back(card);
}

// card must be in player's hand.
void Player::discard(std::shared_ptr<Card> card) {
    int index = findCard(*card);
    if (index >= 0) {
        discardpile.emplace_back(std::move(hand.at(index))); // adding card to discard pile
        hand.erase(hand.begin() + index); // removing card from player's hand
    }
}

void Player::playCard(std::shared_ptr<Card> card) {
    int index = findCard(*card);
    Suit suit = card->getSuit();
    table->addCard(suit, hand.at(index)); // adding card to the correct pile on the Table
    hand.erase(hand.begin() + index);
}

bool Player::startingPlayer() const {
    for (size_t i = 0; i < hand.size(); ++i) {
        if ( (hand[i]->getRank() == 7 ) && (hand[i]->getSuit() == 3) ){
            return true;
        }
    }
    return false;
}

bool Player::isHandEmpty() const {
    if (hand.size() == 0) {
        return true;
    }
    return false;
}

int Player::findCard(Card card) const {
    for (size_t i = 0; i < hand.size(); ++i) { 
        if (*hand.at(i) == card) {
            return i;
        }
    }
    return -1; // if card not found
}

int Player::getScore() const {
    return score;
}

int Player::getDiscardPileScore() {
    discardPileScore = 0;
    for (size_t i = 0; i < discardpile.size(); ++i) {
        discardPileScore += (int)discardpile[i]->getRank(); // casting to int
    }
    return discardPileScore;
}

int Player::getOldScore() const {
    return oldScore;
}

void Player::updateScore() {
    int discardscore = getDiscardPileScore();

    oldScore = score;
    score = oldScore + discardscore;
}

int Player::getPlayerNum() const {
    return playerNum;
}

void Player::clearHand() {
    hand.clear();
}

void Player::clearDiscardPile() {
    discardpile.clear();
}

std::shared_ptr<Card> Player::getFirstCard() {
    return hand.at(0);
}

std::shared_ptr<Card> Player::getFirstLegalPlay() {
    return legalplays.at(0);
}

int Player::getNumDiscards() const {
    return discardpile.size();
}

int Player::getNumCardsinHand() const {
    return hand.size();
}

int Player::getNumLegalPlays() const {
    return legalplays.size();
}

std::vector<std::shared_ptr<Card>> Player::getHand() {
    return hand;
}

std::vector<std::shared_ptr<Card>> Player::getDiscardPile() {
    return discardpile;
}

std::vector<std::shared_ptr<Card>> Player::getLegalPlays() {
    return legalplays;
}

std::shared_ptr<Table> Player::getTable() {
    return table;
}

std::shared_ptr<Card> Player::getCard(int i) const{
    return hand.at(i);
}

void Player::setLegalPlays() {
    legalplays.clear();
    Card c{S,SEVEN};
    if (table->isTableEmpty()) {
        if (findCard(c) >= 0) {
            legalplays.emplace_back(hand.at(findCard(c)));
            return;
        }
    }
    else {
        for (size_t i = 0; i < hand.size(); ++i) {
            if (table->isLegalPlay(hand.at(i))) {
                legalplays.emplace_back(hand.at(i));
            }
        }
    }
}

void Player::becomeComputerPlayer() {
    playerType = "c";
}

std::string Player::getType() const{
    return playerType;
}