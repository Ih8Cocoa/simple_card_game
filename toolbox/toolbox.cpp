#include <iostream>
#include <limits>
#include "toolbox.h"

using std::cout;
using std::cin;
using std::endl;
using std::stoull;
using std::stoul;
using std::exception;
using std::numeric_limits;

long long getInputLong(string const& question) {
    cout << question << ": ";
    string input;
    cin >> input;
    long long rtn = 0;
    bool done = false;
    while (!done) {
        try {
            rtn = stoull(input);
            if (rtn < 1) {
                throw exception();
            }
            done = true;
        } catch (exception const& e) {
            cout << "Invalid input. Please enter again: " << endl;
            cin >> input;
        }
    }
    return rtn;
}

unsigned int getInputUInt(string const& question) {
    cout << question << ": ";
    string input;
    cin >> input;
    unsigned long rtn = 0;
    bool done = false;
    while (!done) {
        try {
            rtn = stoul(input);
            if (rtn > numeric_limits<unsigned int>::max()) {
                throw exception();
            }
            done = true;
        } catch (exception const& e) {
            cout << "Invalid input. Please enter again: " << endl;
            cin >> input;
        }
    }
    return static_cast<unsigned int>(rtn);
}

void newGame(Player& human, Player& computer, bool isStartGame, unsigned int deltaCash) {
    cout << "GAME RESULT: " << endl;
    cout << human.getName() << "'s cards: " << endl;
    if (!isStartGame) {
        human.fillCards();
        computer.fillCards();
    }
    cout << human.displayCards() << endl;
    cout << "Total points: " << human.getTotalPoints() << endl << endl;
    cout << "Computer's cards:" << endl;
    cout << computer.displayCards() << endl;
    cout << "Total points: " << computer.getTotalPoints() << endl << endl;
    auto gameResult = result(human, computer);
    switch (gameResult) {
        case GameResult::WIN:
            cout << "You won!!" << endl;
            playerWon(human, computer, deltaCash);
            break;
        case GameResult::LOSE:
            cout << "You lose!!" << endl;
            playerLose(human, computer, deltaCash);
            break;
        case GameResult::TIE:
            cout << "It's a tie!!!" << endl;
            break;
        default:
            cout << "Wtf??" << endl;
            break;
    }
    cout << endl << "Current cash:" << endl;
    cout << "Your cash: " << human.getCash() << endl;
    cout << "Computer cash: " << computer.getCash() << endl;
}

GameResult result(Player const& human, Player const& computer) {
    auto win = GameResult::WIN;
    auto lose = GameResult::LOSE;
    int humanPoint = human.getTotalPoints();
    int computerPoint = computer.getTotalPoints();
    if (humanPoint > computerPoint) {
        return win;
    }
    if (humanPoint < computerPoint) {
        return lose;
    }
    humanPoint = human.getTotalSuitPoint();
    computerPoint = computer.getTotalSuitPoint();
    if (humanPoint > computerPoint) {
        return win;
    }
    if (humanPoint < computerPoint) {
        return lose;
    }
    if (human.hasAceOfSpades()) {
        return win;
    }
    if (computer.hasAceOfSpades()) {
        return lose;
    }
    return GameResult::TIE;
}

void playerWon(Player& human, Player& computer, unsigned int deltaCash) {
    human.winGame(deltaCash);
    computer.loseGame(deltaCash);
}

void playerLose(Player& human, Player& computer, unsigned int deltaCash) {
    computer.winGame(deltaCash);
    human.loseGame(deltaCash);
}