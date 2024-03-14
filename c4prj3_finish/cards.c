#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "cards.h"
#include <string.h>

void assert_card_valid(card_t c) {
  assert(c.value>=2 && c.value <= VALUE_ACE );
  assert(c.suit >= SPADES && c.suit <= CLUBS);
  return;
}

const char * ranking_to_string(hand_ranking_t r) {
      char * hand; 
    hand = (char *)malloc(15 * sizeof(char));

    switch (r) {
        case STRAIGHT_FLUSH:
            strcpy(hand, "STRAIGHT_FLUSH");
            break;
        case FOUR_OF_A_KIND:
            strcpy(hand, "FOUR_OF_A_KIND");
            break;
        case FULL_HOUSE:
            strcpy(hand, "FULL_HOUSE");
            break;
        case FLUSH:
            strcpy(hand, "FLUSH");
            break;
        case STRAIGHT:
            strcpy(hand, "STRAIGHT");
            break;
        case THREE_OF_A_KIND:
            strcpy(hand, "THREE_OF_A_KIND");
            break;
        case TWO_PAIR:
            strcpy(hand, "TWO_PAIR");
            break;
        case PAIR:
            strcpy(hand, "PAIR");
            break;
        default:
            strcpy(hand, "NOTHING");
            break;
    }

    return hand;
 
}

char value_letter(card_t c) {
      switch (c.value) {
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
            // For values 2-9, return the digit character
            return '0' + c.value;
        case 10:
            // For value 10, return '0'
            return '0';
        case 11:
            // For Jack, return 'J'
            return 'J';
        case 12:
            // For Queen, return 'Q'
            return 'Q';
        case 13:
            // For King, return 'K'
            return 'K';
        case 14:
            // For Ace, return 'A'
            return 'A';
        default:
            // Handle invalid values
            return '?';
      }
  return 'x';
}


char suit_letter(card_t c) {
      switch (c.suit) {
        case SPADES:
            return 's';
        case HEARTS:
            return 'h';
        case DIAMONDS:
            return 'd';
        case CLUBS:
            return 'c';
        default:
            return '?'; 
    }
  return 'x';
  
}

void print_card(card_t c) {
  printf("%c%c", value_letter(c), suit_letter(c));
}

card_t card_from_letters(char value_let, char suit_let) {
  card_t temp;
      switch (value_let) {
        case '2':
            temp.value = 2;
            break;
        case '3':
            temp.value = 3;
            break;
        case '4':
            temp.value = 4;
            break;
        case '5':
            temp.value = 5;
            break;
        case '6':
            temp.value = 6;
            break;
        case '7':
            temp.value = 7;
            break;
        case '8':
            temp.value = 8;
            break;
        case '9':
            temp.value = 9;
            break;
        case '0':
            temp.value = 10;
            break;
        case 'J':
            temp.value = 11;
            break;
        case 'Q':
            temp.value = 12;
            break;
        case 'K':
            temp.value = 13;
            break;
        case 'A':
            temp.value = 14;  
            break;
        default:
            printf("Invalid value letter: %c\n", value_let);
            exit(EXIT_FAILURE);
    }

    switch (suit_let) {
        case 's':
            temp.suit = SPADES;
            break;
        case 'h':
            temp.suit = HEARTS;
            break;
        case 'd':
            temp.suit = DIAMONDS;
            break;
        case 'c':
            temp.suit = CLUBS;
            break;
        default:
            printf("Invalid suit letter: %c\n", suit_let);
            exit(EXIT_FAILURE);
    }
  return temp;
}

card_t card_from_num(unsigned c) {
  card_t temp;
 
    temp.value = (c % 13) + 2; 

    temp.suit = c / 13;  
  return temp;
}
