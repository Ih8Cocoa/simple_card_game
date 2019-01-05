#include <iostream>
#include "toolbox/toolbox.h"

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::make_unique;

int main() {
    long long cash = getInputLong("Please enter initial cash");
    unsigned int deltaCash = getInputUInt("Enter delta cash");
    bool isStartGame = true;

    cout << "Please enter your name: ";
    string name;
    cin >> name;

    //let's begin the game
    cout << "Let's begin the game!" << endl;

    auto you = make_unique<Player>(Player(name, cash));
    auto him = make_unique<Player>(Player());

    unsigned int input = 1;

    while (input != 0) {
        if (!(you->canContinue())) {
            cout << "ERROR: You have lost all of the money! Good bye." << endl;
            break;
        }
        if (!(him->canContinue())) {
            cout << "The computer has lost all of the money. Enjoy your fame!" << endl;
            break;
        }
        newGame(*you, *him, isStartGame, deltaCash);
        if (isStartGame) {
            cin.get();
            isStartGame = false;
        }
        input = getInputUInt("Would you like to continue? (Input 0 to stop)");
        cout << "\033[2J\033[1;1H";
    }

}