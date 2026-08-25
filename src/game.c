#include "game.h"

#define NUM_PLAYERS 4

int score(const PlayerState *ps){
    uint16_t presence[4] = {0};
    int score = 0;

    for(int i = 0; i < ps->numCards; i++){
        presence[ps->cards[i].suit - 1] |= 1 << (ps->cards[i].rank - 1);
    }

    for(int i = 0; i < 4; i++){
        for(int m = presence[i] & ~(presence[i] << 1); m; m &= m - 1){
            score += __builtin_ctz(m) + 1;
        }
    }

    return score;
}

GameView make_game_view(const Game *g){
        return (GameView) {
        .upCard = g->upCard,
        .playerState = g->players[g->player].playerState,
        .hist = &g->hist,
        .player = g->player
    };
}

void update_history(Game *g, Move mv){
    MoveHistory *hist = &g->hist;
    if(hist->length == hist->capacity){
        int newCapacity = hist->capacity ? hist->capacity * 2 : 1;

        Move *newMoves = realloc(
            hist->moves,
            newCapacity * sizeof(*newMoves)
        );

        hist->moves = newMoves;
        hist->capacity = newCapacity;
    }

    hist->moves[hist->length++] = mv;
}

void play_round(Game *g){
    Action action;
    Player *curr = &g->players[g->player];

    while(true){
        GameView view = make_game_view(g);
        action = curr->actionFn(&view, curr->state);
        Move mv = {g->player, action, g->upCard};
        update_history(g, mv);

        if (action == TAKE) {
            curr->playerState.numChips += g->upCard.numChips;
            curr->playerState.cards[curr->playerState.numCards++] = g->upCard.card;

            if(g->deck.top == DECK_SIZE) return;
            g->upCard = (PassedCard) {deal_card(&g->deck), 0};
        } 
        else if (action == PASS){
            curr->playerState.numChips--;
            g->upCard.numChips++;
            break;
        } 
    }
}

void play(Game *g) {
    make_deck(&g->deck);
    shuffle(&g->deck);

    for(int i = 0; i < 5 + NUM_PLAYERS; i++) deal_card(&g->deck);

    g->upCard = (PassedCard) {deal_card(&g->deck), 0};

    while(g->deck.top  < DECK_SIZE) {
        play_round(g);
        g->player++;
        g->player %= NUM_PLAYERS;
    }
}