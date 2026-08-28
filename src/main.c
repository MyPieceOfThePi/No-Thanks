#include "game.h"
#include "bots.h"

int main(void) {
    srand(time(0));

    int thresholds[NUM_PLAYERS] = {4,5,6,7};
    Player players[NUM_PLAYERS] = {
                    make_player(human_action, NULL),
                    make_player(threshold_action, &thresholds[1]),
                    make_player(threshold_action, &thresholds[2]),
                    make_player(threshold_action, &thresholds[3])
    };

    Game g = make_game(players);

    printf("%d\n", play(&g));

    for(int i = 0; i < NUM_PLAYERS; i++){
        printf("Player %d score: %d\n", i, g.scores[i]);
    }

    free(g.hist.moves);
}