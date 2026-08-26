#include "cards.h"

#define DECK_SIZE 52

const char *suits[] = {" ", "♣ ", "♦ ", "♥ ", "♠ "};
const char *ranks[] = {"", " A", " 2", " 3", " 4", " 5", " 6", " 7", " 8", " 9", "10", " J", " Q", " K"};

void make_deck(Deck *deck){
    for(int s = 1; s <= 4; s++){
        for(int r = 1; r <= 13; r++){
            deck->cards[s*13 + r - 14] = (Card) {.suit = s, .rank = r};
        }
    }
    deck->top = 0;
}

void shuffle(Deck *deck){
    for(int i = DECK_SIZE - 1; i > 0; i--){     
        int j = rand() % (i + 1);
        Card temp = deck->cards[i];
        deck->cards[i] = deck->cards[j];
        deck->cards[j] = temp;
    }
}

Card deal_card(Deck *deck){
    return deck->cards[deck->top++];
}

char *to_string(const Card card){
    return "[" + ranks[card.rank] + suits[card.suit] + "]";
}
