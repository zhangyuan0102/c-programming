#include "future.h"
#include "deck.h"
#include <stdio.h>
#include <assert.h>
void add_future_card(future_cards_t * fc, size_t index, card_t * ptr){
        if (index+1 > fc->n_decks) {
        fc->decks = realloc(fc->decks, (index + 1) * sizeof(*fc->decks));
        for (size_t i = fc->n_decks; i <= index; i++) {
	  fc->decks[i].cards = NULL;
	  fc->decks[i].n_cards = 0 ;
        }
        fc->n_decks = index + 1;
    }
          fc->decks[index].n_cards++;
    fc->decks[index].cards = realloc(fc->decks[index].cards, sizeof(*(fc->decks[index].cards)) * fc->decks[index].n_cards); 
    fc->decks[index].cards[fc->decks[index].n_cards - 1] = ptr;
}
void future_cards_from_deck(deck_t * deck, future_cards_t * fc){
        assert(deck->n_cards >= fc->n_decks);

    int deck_index = 0;
    for (int i = 0; i < fc->n_decks; i++) {
        if (fc->decks[i].n_cards == 0) {
            continue;
        }
        for(int j = 0; j < fc->decks[i].n_cards; j++) {
            *fc->decks[i].cards[j] = *deck->cards[deck_index]; 
        }
        deck_index++;
    }
}
