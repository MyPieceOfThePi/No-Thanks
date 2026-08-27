#include "bots.h"

Action threshold_action(const GameView *gameView, void *state){
    PlayerState newState = gameView->playerStates[gameView->player];
    newState.numChips += gameView->upCard.numChips;
    newState.cards[newState.numCards++] = gameView->upCard.card;

    int currScore = score(&gameView->playerStates[gameView->player]);
    int newScore = score(&newState);
    int delta = newScore - currScore;

    return delta <= *(int *) state ? TAKE : PASS;
}
