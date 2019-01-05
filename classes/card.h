#pragma once

#include <string>
#include "../libraries/enums.h"

using std::string;

BETTER_ENUM(Rank, int, ACE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK);
BETTER_ENUM(Suit, int, SPADES, CLUBS, DIAMONDS, HEARTS);

class Card {
private:
    Suit suit;
    Rank rank;

public:
    Card();
    Card(int rankCode, int suitCode);
    int getPoints() const;
    int getSuitPoint() const;
    string getCardName() const;
    bool operator == (Card const& otherCard) const;
};