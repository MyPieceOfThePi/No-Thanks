#ifndef GAME_H
#define GAME_H

#include "cards.h"

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <limits.h>
#include <string.h>

#define NUM_PLAYERS 4
#define NUM_CARDS (DECK_SIZE - 5 - NUM_PLAYERS)

typedef struct {
    Card cards[NUM_CARDS];
    int numCards;
    int numChips;
} PlayerState;

typedef struct {
    Card card;
    int numChips;
} PassedCard;

typedef enum {
    TAKE,
    PASS
} Action;

typedef struct {
    int player;
    Action action;
    PassedCard passedCard;
} Move;

typedef struct {
    Move *moves;
    int length;
    int capacity;
} MoveHistory;

typedef struct Player Player;

typedef struct {
    PassedCard upCard;
    const MoveHistory *hist;
    PlayerState playerStates[NUM_PLAYERS];
    int player;
} GameView;

typedef Action (*ActionFn)(const GameView *gameView, void *state);

struct Player {
    ActionFn actionFn;
    PlayerState playerState;
    void *state;
};

typedef struct {
    Deck deck;
    PassedCard upCard;
    int player;
    Player players[NUM_PLAYERS];
    MoveHistory hist;
    int scores[NUM_PLAYERS];
} Game;

int score(const PlayerState *ps);
int play(Game *g);

Player make_player(ActionFn actionFn, void *state);
Game make_game(Player players[NUM_PLAYERS]);

#endif