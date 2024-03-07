#include "eval.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int card_ptr_comp(const void * vp1, const void * vp2){
    const card_t * const * cp1 = vp1;
    const card_t * const * cp2 = vp2;


    if ((*cp1)->value > (*cp2)->value) {
        return -1;
    } else if ((*cp1)->value < (*cp2)->value) {
        return 1;
    } else { 
        if ((*cp1)->suit > (*cp2)->suit) {
            return -1;
        } else if ((*cp1)->suit < (*cp2)->suit) {
            return 1;
        } else { 
            return 0;
        }
    }
}

suit_t flush_suit(deck_t * hand) {
    int a = 0, b = 0, c = 0, d = 0;
    for (int i = 0; i < hand->n_cards; i++) {
        if (hand->cards[i]->suit == CLUBS) {
            a++;
        }
        if (hand->cards[i]->suit == DIAMONDS) {
            b++;
        }
        if (hand->cards[i]->suit == HEARTS) {
            c++;
        }
        if (hand->cards[i]->suit == SPADES) {
            d++; 
        }
    }
    if (a >= 5) {
        return CLUBS;
    } else if (b >= 5) {
        return DIAMONDS;
    } else if (c >= 5) {
        return HEARTS;
    } else if (d >= 5) {
        return SPADES;
    } else {
        return NUM_SUITS;
    }
}

unsigned get_largest_element(unsigned * arr, size_t n) {
  unsigned temp =arr[0];
  for(int i=1;i<n;i++){
    if(arr[i]>temp){
      temp = arr[i];
    }
  }
  return temp;
}

size_t get_match_index(unsigned * match_counts, size_t n,unsigned n_of_akind){
    for (size_t i = 0; i < n; ++i) {
        if (match_counts[i] == n_of_akind) {
            return i; 
        }
    }
    return n; 
}
ssize_t  find_secondary_pair(deck_t * hand,
			     unsigned * match_counts,
			     size_t match_idx) {
  ssize_t index;
  for(index=0; index<hand->n_cards; index++) {
    if (match_counts[index] > 1
	&& hand->cards[index]->value != hand->cards[match_idx]->value) {
      return index;
    }
  }
  return -1;
}


int is_n_length_straight_at(deck_t * hand, size_t index, suit_t fs, int n) {
  card_t *c1 = hand->cards[index];
  suit_t suitAtIndex = c1->suit;
  card_t *c2 = NULL;
  int count = 1;
  for (int j=index+1; j<hand->n_cards; j++)
    {
      c2 = hand->cards[j];
      if (c1->value == c2->value) // equal card values - could be straight
	{
	  if (fs == NUM_SUITS)
	    continue;
	  else if (c2->suit==suitAtIndex)
	    {
	      count++;
	      if (count==n)
		return 1;
	      c1=c2;
	    }
	}
      else if (c1->value == (c2->value + 1)) // straight/straight flush
	{
	  if ((fs == NUM_SUITS) || (suitAtIndex == c2->suit) )
	    {
	      count++;
	      if (count==n)
		return 1;
	    }
	  c1 = c2; // next card may be of same value as current and suit as suitAtIndex
	}
      else
	return 0; // no straight - break the loop early
    }
  return 0;
}

// returns -1 if found ace-low straight else 0
int is_ace_low_straight_at(deck_t * hand, size_t index, suit_t fs) {
   if (hand->cards[index]->value != VALUE_ACE)
   {
     return 0;
   }
   // first_value =ace and do not care suit
   if (fs == NUM_SUITS)
   {
    int count = 1;
    size_t idx_temp =0;
    // find whether 5 exist
    for ( size_t i = index+1; i < hand->n_cards    ;i++)
    {
      if (hand->cards[i]->value == 5)
      {
        idx_temp = i;
        break;
      }
    }
    if ((idx_temp==0)||idx_temp>3) {return 0;}
    count++;
    //A A 5 5 4 3 2 
    // check whether 4 3 2 is follwoing 5
    unsigned current_card_value = hand->cards[idx_temp]->value;
    for (size_t m =idx_temp;m<hand->n_cards    ;m++)
    {
      if (hand->cards[m]->value == current_card_value){continue;}
      if (hand->cards[m]->value == current_card_value -1)
      {
        current_card_value = hand->cards[m]->value ;
        count++;
      }
    }
    if (count>=5){return -1;}
    else {return 0;}
   }

   // take in the consideration of suit and has already check the ace at the index)
   if (hand->cards[index]->suit != fs){return 0;}
   int count2 =1;
   size_t idx2 = 0;
   //As Ks Qs Js 0s 9s 8s 
   //find where is 5 
   for (size_t k=index+1;k<hand->n_cards    ;k++)
   {
     if ((hand->cards[k]->value == 5) && (hand->cards[k]->suit == fs))
     {
       idx2 = k;
       break;
     }
   }
   if ((idx2== 0)||idx2>3) {return 0;}
   count2++;
   unsigned card_curr_value = hand->cards[idx2]->value;
   for (size_t j=idx2+1;j<hand->n_cards    ;j++)
    {
      //Ac As Kc Ks Qs Js 0s 2---6
      if (hand->cards[j]->suit != fs){continue;}
      if (hand->cards[j]->value == card_curr_value -1)
      {
        card_curr_value = hand->cards[j]->value ;
        count2++;
      }
    }
   if (count2==5){return -1;}
   else {return 0;}
 
 }

// Hand is sorted by value
int is_straight_at(deck_t * hand, size_t index, suit_t fs) {
  if (hand==NULL)
    return 0;

  if ((is_n_length_straight_at(hand, index, fs, 5)==1)||(is_n_length_straight_at(hand, index, fs, 6)==1)||(is_n_length_straight_at(hand, index, fs, 7)==1))
    return 1;
  else if (hand->cards[0]->value==VALUE_ACE){
        return is_ace_low_straight_at(hand, index, fs);
    }
        
    return 0;
}
hand_eval_t build_hand_from_match(deck_t * hand,
				  unsigned n,
				  hand_ranking_t what,
				  size_t idx) {

  hand_eval_t ans;
  ans.ranking=what;
 
    for (size_t i = 0; i < n; i++) {
        ans.cards[i] = hand->cards[idx + i];
    }

    size_t card_index = n;
    size_t hand_index = 0;

    while (card_index < 5) {
        if (hand_index >= idx && hand_index < idx + n) {
            hand_index++;
            continue;
        }
        ans.cards[card_index] = hand->cards[hand_index];
        hand_index++;
        card_index++;
    }
   
  return ans;
}


int compare_hands(deck_t * hand1, deck_t * hand2) {
    qsort(hand1->cards, hand1->n_cards, sizeof(card_t *), card_ptr_comp);
    qsort(hand2->cards, hand2->n_cards, sizeof(card_t *), card_ptr_comp);

    hand_eval_t eval1 = evaluate_hand(hand1);
    hand_eval_t eval2 = evaluate_hand(hand2);

    if (eval1.ranking != eval2.ranking) {
        return eval2.ranking - eval1.ranking;
    } else {
        for (size_t i = 0; i < 5; i++) {
            if (eval1.cards[i]->value != eval2.cards[i]->value) {
                return eval1.cards[i]->value - eval2.cards[i]->value;
            }
        }
        return 0;
    }
}



//You will write this function in Course 4.
//For now, we leave a prototype (and provide our
//implementation in eval-c4.o) so that the
//other functions we have provided can make
//use of get_match_counts.
unsigned * get_match_counts(deck_t * hand) {
  unsigned * count=malloc(hand->n_cards * sizeof(unsigned));
  for(int i=0;i<hand->n_cards;i++){
  if(hand->cards[i-1] != hand->cards[i]||i<1){
    count[i]=1;
  }
  else if(hand->cards[i-1] == hand->cards[i]){
      count[i]=count[i-1];
    for(int j=0;j<count[i-1]+1;j++){
      count[i-j]++;
    }
  }
}
return count;
}
// We provide the below functions.  You do NOT need to modify them
// In fact, you should not modify them!


//This function copies a straight starting at index "ind" from deck "from".
//This copies "count" cards (typically 5).
//into the card array "to"
//if "fs" is NUM_SUITS, then suits are ignored.
//if "fs" is any other value, a straight flush (of that suit) is copied.
void copy_straight(card_t ** to, deck_t *from, size_t ind, suit_t fs, size_t count) {
  assert(fs == NUM_SUITS || from->cards[ind]->suit == fs);
  unsigned nextv = from->cards[ind]->value;
  size_t to_ind = 0;
  while (count > 0) {
    assert(ind < from->n_cards);
    assert(nextv >= 2);
    assert(to_ind <5);
    if (from->cards[ind]->value == nextv &&
	(fs == NUM_SUITS || from->cards[ind]->suit == fs)){
      to[to_ind] = from->cards[ind];
      to_ind++;
      count--;
      nextv--;
    }
    ind++;
  }
}


//This looks for a straight (or straight flush if "fs" is not NUM_SUITS)
// in "hand".  It calls the student's is_straight_at for each possible
// index to do the work of detecting the straight.
// If one is found, copy_straight is used to copy the cards into
// "ans".
int find_straight(deck_t * hand, suit_t fs, hand_eval_t * ans) {
  if (hand->n_cards < 5){
    return 0;
  }
  for(size_t i = 0; i <= hand->n_cards -5; i++) {
    int x = is_straight_at(hand, i, fs);
    if (x != 0){
      if (x < 0) { //ace low straight
	assert(hand->cards[i]->value == VALUE_ACE &&
	       (fs == NUM_SUITS || hand->cards[i]->suit == fs));
	ans->cards[4] = hand->cards[i];
	size_t cpind = i+1;
	while(hand->cards[cpind]->value != 5 ||
	      !(fs==NUM_SUITS || hand->cards[cpind]->suit ==fs)){
	  cpind++;
	  assert(cpind < hand->n_cards);
	}
	copy_straight(ans->cards, hand, cpind, fs,4) ;
      }
      else {
	copy_straight(ans->cards, hand, i, fs,5);
      }
      return 1;
    }
  }
  return 0;
}


//This function puts all the hand evaluation logic together.
//This function is longer than we generally like to make functions,
//and is thus not so great for readability :(
hand_eval_t evaluate_hand(deck_t * hand) {
  suit_t fs = flush_suit(hand);
  hand_eval_t ans;
  if (fs != NUM_SUITS) {
    if(find_straight(hand, fs, &ans)) {
      ans.ranking = STRAIGHT_FLUSH;
      return ans;
    }
  }
  unsigned * match_counts = get_match_counts(hand);
  unsigned n_of_a_kind = get_largest_element(match_counts, hand->n_cards);
  assert(n_of_a_kind <= 4);
  size_t match_idx = get_match_index(match_counts, hand->n_cards, n_of_a_kind);
  ssize_t other_pair_idx = find_secondary_pair(hand, match_counts, match_idx);
  free(match_counts);
  if (n_of_a_kind == 4) { //4 of a kind
    return build_hand_from_match(hand, 4, FOUR_OF_A_KIND, match_idx);
  }
  else if (n_of_a_kind == 3 && other_pair_idx >= 0) {     //full house
    ans = build_hand_from_match(hand, 3, FULL_HOUSE, match_idx);
    ans.cards[3] = hand->cards[other_pair_idx];
    ans.cards[4] = hand->cards[other_pair_idx+1];
    return ans;
  }
  else if(fs != NUM_SUITS) { //flush
    ans.ranking = FLUSH;
    size_t copy_idx = 0;
    for(size_t i = 0; i < hand->n_cards;i++) {
      if (hand->cards[i]->suit == fs){
	ans.cards[copy_idx] = hand->cards[i];
	copy_idx++;
	if (copy_idx >=5){
	  break;
	}
      }
    }
    return ans;
  }
  else if(find_straight(hand,NUM_SUITS, &ans)) {     //straight
    ans.ranking = STRAIGHT;
    return ans;
  }
  else if (n_of_a_kind == 3) { //3 of a kind
    return build_hand_from_match(hand, 3, THREE_OF_A_KIND, match_idx);
  }
  else if (other_pair_idx >=0) {     //two pair
    assert(n_of_a_kind ==2);
    ans = build_hand_from_match(hand, 2, TWO_PAIR, match_idx);
    ans.cards[2] = hand->cards[other_pair_idx];
    ans.cards[3] = hand->cards[other_pair_idx + 1];
    if (match_idx > 0) {
      ans.cards[4] = hand->cards[0];
    }
    else if (other_pair_idx > 2) {  //if match_idx is 0, first pair is in 01
      //if other_pair_idx > 2, then, e.g. A A K Q Q
      ans.cards[4] = hand->cards[2];
    }
    else {       //e.g., A A K K Q
      ans.cards[4] = hand->cards[4];
    }
    return ans;
  }
  else if (n_of_a_kind == 2) {
    return build_hand_from_match(hand, 2, PAIR, match_idx);
  }
  return build_hand_from_match(hand, 0, NOTHING, 0);
}
