#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "deck.h"

void print_hand(deck_t * hand){
    int width = 3 * hand->n_cards;
    int spaces = (80 - width) / 2;
    for (int i = 0; i < spaces; i++) {
        printf(" ");
    }
    for (int j = 0; j < hand->n_cards; j++) {
        print_card(*(hand->cards[j]));
        printf(" ");
  }
    
}

int deck_contains(deck_t * d, card_t c) {
    for (size_t i = 0; i < d->n_cards; i++) {
        if (c.value == d->cards[i]->value && c.suit == d->cards[i]->suit) {
            return 1;
    }
    }
  return 0;
}

void shuffle(deck_t * d){
    for (int i = d->n_cards - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        card_t *temp = d->cards[i];
        d->cards[i] = d->cards[j];
        d->cards[j] = temp;
    }
}

void assert_full_deck(deck_t * d) {
    for (unsigned i = 0; i < 52; ++i) {
        card_t card = card_from_num(i);

        if (!deck_contains(d, card)) {
            assert(0); 
        }
    }

 
    if (d->n_cards  > 52) {
            assert(0); 
        }
        for (int j = 0; j < d->n_cards; ++j) {
           for(int k = j+1; k< d->n_cards; ++k) {
	     if (d->cards[j] == d->cards[k]) {
                assert(0); 
            }
        }
    }
}

