#include "game.h"
#include "bots.h"

int main(void) {
    Player players[4] = {
                    make_player(human_action, NULL),
                    make_player(human_action, NULL),
                    make_player(human_action, NULL),
                    make_player(human_action, NULL)
    };

    Game g = make_game(players);

    printf("%d\n", play(&g));

    free(g.hist.moves);
}