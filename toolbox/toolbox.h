#pragma once

#include <string>
#include "../classes/Player.h"
#include "../libraries/enums.h"

using std::string;

BETTER_ENUM(GameResult, int, WIN, TIE, LOSE);

long long getInputLong(string const& question);
unsigned int getInputUInt(string const& question);
void newGame(Player& human, Player& computer, bool isStartGame, unsigned int deltaCash);
GameResult result(Player const& human, Player const& computer);
void game();
void playerWon(Player& human, Player& computer, unsigned int deltaCash);
void playerLose(Player& human, Player& computer, unsigned int deltaCash);