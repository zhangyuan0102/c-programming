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
void add_card_to(deck_t * deck, card_t c){
  card_t* c1=malloc(sizeof(*c1));
  
  c1->value = c.value;
  
  c1->suit = c.suit;
    deck->cards = realloc(deck->cards,(deck->n_cards+1)*sizeof(*deck ->cards));
    deck->cards[deck->n_cards] =c1;
    deck->n_cards++;
}
card_t * add_empty_card(deck_t * deck){
  card_t* c1=malloc(sizeof(*c1));
  
  c1->value = 0;
  
  c1->suit = 0;
    deck->cards = realloc(deck->cards,(deck->n_cards+1)*sizeof(*deck->cards));
    deck->cards[deck->n_cards] = c1;
    deck->n_cards++;
    return deck->cards[deck->n_cards-1];
}    
deck_t * make_deck_exclude(deck_t * excluded_cards){
    deck_t *deck_exclude =malloc(sizeof(*deck_exclude));
    deck_exclude->cards = NULL;
    deck_exclude->n_cards = 0;
    for(unsigned i =0;i<52;i++){
    card_t c = card_from_num(i);
    if(deck_contains(excluded_cards,c)==0){
       add_card_to(deck_exclude,c);
    }   
    }
    return deck_exclude;
}
deck_t * build_remaining_deck(deck_t ** hands, size_t n_hands){
    deck_t * excluded = malloc(sizeof(*excluded));
    excluded->cards = NULL;
    excluded->n_cards = 0;
    deck_t *hand;
    card_t *card;

    for(int i=0;i<n_hands;i++){
        hand = hands[i];
        for(int j=0;j<hand->n_cards;j++){
            card = hand->cards[j];
            if(card->value !=0){
                if(deck_contains(excluded,*card)==0){
                  add_card_to(excluded, *card);       
                }
            }
        }
    }
    deck_t *d = make_deck_exclude(excluded);
    free_deck(excluded);
    return d;
}
void free_deck(deck_t * deck){
    for(int i=0;i<deck->n_cards;i++){
        free(deck->cards[i]);
    }
    free(deck->cards);
    free(deck);
}
