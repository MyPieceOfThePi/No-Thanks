#include "bots.h"

PlayerState playerStates[NUM_PLAYERS];

void print_hand(PlayerState ps) {
    Card suitedcards[4][13] = {0};
    for (int i = 0; i < ps.numCards; i++) {
        if (ps.cards[i].rank == 0 || ps.cards[i].suit == UNDEF) {
            break; 
        }
        suitedcards[ps.cards[i].suit - 1][ps.cards[i].rank - 1] = ps.cards[i];
    }
    for (int i = 0; i < 4; i++) {
        char str[512];
        for (int j = 0; j < 13; j++) {
            if (suitedcards[i][j].suit == UNDEF) { continue; }
            to_string(suitedcards[i][j], str + j*6);
        }
        printf(str);
        putc('\n', stdout);
    }
}

Action human_action(const GameView *gameView, void *state) {
    printf("player %d:\n", gameView->player);
    print_hand(gameView->playerStates[gameView->player]);
    return TAKE;
}
