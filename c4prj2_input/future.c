#include "future.h"
#include "deck.h"
#include <stdio.h>
void add_future_card(future_cards_t * fc, size_t index, card_t * ptr){
        if (index >= fc->n_decks) {
        fc->decks = realloc(fc->decks, (index + 1) * sizeof(deck_t));
        for (size_t i = fc->n_decks; i <= index; i++) {
            fc->decks[i] = (deck_t){ .cards = NULL, .n_cards = 0 };
        }
        fc->n_decks = index + 1;
    }
	add_card_to(&(fc->decks[index)), *ptr);
}
void future_cards_from_deck(deck_t * deck, future_cards_t * fc){
    if (deck->n_cards < fc->n_decks) {
        fprintf(stderr, "Error: Not enough cards in the deck to fill future cards.\n");
        return;
    }
    
    for (size_t i = 0; i < fc->n_decks; i++) {
        if (fc->decks[i].n_cards == 0) {
            fprintf(stderr, "Error: Future card deck %zu is empty.\n", i);
            continue;
        }
        for (size_t j = 0; j < fc->decks[i].n_cards; j++) {
            *fc->decks[i].cards[j] = *deck->cards[j];
        }
    }
}
