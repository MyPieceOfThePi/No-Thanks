#ifndef BOTS_H
#define BOTS_H

#include "game.h"
#include "cards.h"

// Human bot
Action human_action(const GameView *gameView, void *state);

// Treshhold bot
Action threshold_action(const GameView *gameView, void *state);

#endif 