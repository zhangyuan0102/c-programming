#include "input.h"
#include "future.h"
#include <stdio.h>
#include <string.h>
deck_t * hand_from_string(const char * str, future_cards_t * fc){
    deck_t *hand = malloc(sizeof(*hand));
    hand->n_cards =0;
    hand->cards = NULL;
    while(str !=NULL && *str !='\0'){
        char *end=strchr(str,' ');
        char value = *str;
        char suit = *(str+1);
        if(value =='?'){
         int index = atoi(str+1);
         add_future_card(fc, index, add_empty_card(hand));   
        }
        else{
           add_card_to(hand,card_from_letters(value,suit));
        }
        str = end +1;  
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
  
  ans = realloc(ans,(*n_hands+1)*sizeof(*ans));
  ans[*n_hands]=hand_from_string(line,fc);
  (*n_hands)++;
  }
  free(line);
  return ans;

}
