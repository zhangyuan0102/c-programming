#include "input.h"
#include "future.h"
#include <stdio.h>
#include <string.h>
deck_t * hand_from_string(const char * str, future_cards_t * fc){
    deck_t *hand = malloc(sizeof(*hand));
    hand->n_cards =0;
    hand->cards = NULL;
    while(str !=NULL && *str !='\0'){
            if (*str == ' ') {
            str++;
            continue;
        } else {
            char value = *str;
            str++;
            if(value == '?') {
                int index = atoi(str);
                str = strchr(str, ' ');
                add_future_card(fc, index, add_empty_card(hand));
            } else {
                char suit = *str;
                str++;
                add_card_to(hand, card_from_letters(value, suit));
            }
        }
    }
    if(hand->n_cards<5){
        fprintf(stderr, "Each hand should have at least 5 cards.\n");
        exit(EXIT_FAILURE);
    }
  return hand;
}

deck_t ** read_input(FILE * f, size_t * n_hands, future_cards_t * fc){
   deck_t ** ans =NULL;
   *n_hands = 0;
   ssize_t num=0;
   size_t sz=0;
  char *line = NULL;

  while((num = getline(&line, &sz, f))!=-1){

  line[num-1] = '\0';
  (*n_hands)++;
  ans = realloc(ans,(*n_hands)*sizeof(*ans));
  ans[*n_hands-1]=hand_from_string(line,fc);
  (*n_hands)++;
  }
  free(line);
  return ans;

}
