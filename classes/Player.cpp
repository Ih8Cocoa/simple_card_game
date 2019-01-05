//
// Created by khokho on 03/01/2019.
//

#include <sodium.h>
#include <boost/algorithm/string/predicate.hpp>
#include <set>
#include "Player.h"

using std::make_unique;
using std::move;
using std::string;
using std::set;
using boost::iequals;

auto makeCardUniquePtr(set<string>& blackList) {
    auto card = make_unique<Card>(Card());
    while (blackList.count(card->getCardName())) {
        card = make_unique<Card>(Card());
    }
    blackList.insert(card->getCardName());
    return card;
}

Player::Player() : name("Computer"), cash(randombytes_random()) {
    fillCards();
}

Player::Player(string const &str, long long c) : name(str), cash(c) {
    fillCards();
}

void Player::fillCards() {
    set<string> blackList;
    card1 = makeCardUniquePtr(blackList);
    card2 = makeCardUniquePtr(blackList);
    card3 = makeCardUniquePtr(blackList);
}

int Player::getTotalPoints() const {
    int total = card1->getPoints() + card2->getPoints() + card3->getPoints();
    int score = total % 10;
    return score == 0 ? 10 : score;
}

int Player::getTotalSuitPoint() const {
    return card1->getSuitPoint() + card2->getSuitPoint() + card3->getSuitPoint();
}

bool Player::hasAceOfSpades() const {
    string meow = "Ace of Spades";
    auto card1Name = card1->getCardName();
    auto card2Name = card2->getCardName();
    auto card3Name = card3->getCardName();
    return iequals(meow, card1Name) || iequals(meow, card2Name) || iequals(meow, card3Name);
}

void Player::winGame(unsigned int deltaCash) {
    cash += deltaCash;
}

void Player::loseGame(unsigned int deltaCash) {
    cash -= deltaCash;
}

string Player::displayCards() const {
    return card1->getCardName() + "\n" + card2->getCardName() + "\n" + card3->getCardName();
}

bool Player::canContinue() const {
    return cash > 0;
}

long long Player::getCash() const {
    return cash;
}

string Player::getName() const {
    return name;
}