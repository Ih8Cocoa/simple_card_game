#pragma once

#include <string>
#include <memory>
#include "card.h"

using std::string;
using std::unique_ptr;

class Player {
private:
    string name;
    unique_ptr<Card> card1, card2, card3;
    long long cash;

public:
    Player();
    Player(string const& str, long long s);
    void fillCards();
    int getTotalPoints() const;
    int getTotalSuitPoint() const;
    bool hasAceOfSpades() const;
    void winGame(unsigned int deltaCash);
    void loseGame(unsigned int deltaCash);
    string displayCards() const;
    bool canContinue() const;
    long long getCash() const;
    string getName() const;
};

