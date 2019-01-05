//
// Created by khokho on 03/01/2019.
//

#include <sodium.h>
#include <iostream>
#include "card.h"

using std::string;
using std::cout;
using std::endl;

Card::Card() {
    rank = Rank::_from_integral(randombytes_uniform(10));
    suit = Suit::_from_integral(randombytes_uniform(4));
}

Card::Card(int rankCode, int suitCode) {
    if (rankCode > 12 || suitCode > 3) {
        cout << "ERROR: Invalid card initialization arguments" << endl << "Defaulting to random card" << endl;
        rank = Rank::_from_integral(randombytes_uniform(10));
        suit = Suit::_from_integral(randombytes_uniform(4));
    } else {
        rank = Rank::_from_integral(rankCode);
        suit = Suit::_from_integral(suitCode);
    }
}

string Card::getCardName() const {
    string rankName = rank._to_string();
    string suitName = suit._to_string();
    return rankName + " of " + suitName;
}

int Card::getPoints() const {
    return rank._to_integral() + 1;
}

int Card::getSuitPoint() const {
    return suit._to_integral() + 1;
}

bool Card::operator == (Card const& otherCard) const {
    return this->getPoints() < otherCard.getPoints();
}