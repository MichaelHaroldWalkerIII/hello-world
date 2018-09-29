// ----------------------------------------------------------------------
// file: card.c
//
// Description: This file implements the CARD module. Its job is to 
//     create an interface for providing cards from a shuffled deck of
//     52 standing playing cards. Each call to card_get() will return
//     the top card in that shuffled deck. If all the cards get used, 
//     then the deck is invisibly (and unknowingly) reshuffled.
//
// Created: 2016-05-03 (P. Clark)
//
// 2017-10-30 (P. Clark)
//     Added card_init().
// 2018-05-09 (P. Clark)
//     Transitioned to the bool type.
// ----------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/times.h>
#include "card.h"
#include "common.h"

#define NUM_SHUFFLES 10
#define CARDS_PER_SUIT 13
#define ATTRIBUTES_PER_CARD 2 
#define SUIT_COL    0
#define PATTERN_COL 1
#define CARD_STATE_INIT 42
#define RESET  "\033[0m"
#define CARDS_PER_DECK 52
#define ATTRIBUTES_PER_CARD 2



// **********************************************************************
// ***************** G L O B A L    V A R I A B L E S *******************
// **********************************************************************

// Has the module been initialized?
static unsigned char Card_state = 0;

// Have the cards been shuffled?
static bool Deck_shuffled = false;        

// The deck of cards:
// Cards[i][SUIT_COL]    = the suit of the ith card
// Cards[i][PATTERN_COL] = the pattern of the ith card
static unsigned char Cards[CARDS_PER_DECK][ATTRIBUTES_PER_CARD];



// **********************************************************************
// ***************** E X T E R N A L    F U Ni C T I O N S ***************
// **********************************************************************

// The following function must be called before card_get() is called.
extern void card_init(void)
{
        // initialize the random number generator
        srandom(times(NULL));

        // set up a brand new deck with no shuffling whatsover
        // ****** TBD student code goes here ********
        //*suit = cards[i][SUIT];
        //*pattern = cards[j][PATTERN];
        int i;

        for (i=0;i<CARDS_PER_SUIT;i++) {
                Cards[i][SUIT_COL] = CLUBS;
                Cards[i+CARDS_PER_SUIT][SUIT_COL] = HEARTS;
                Cards[i+CARDS_PER_SUIT+CARDS_PER_SUIT][SUIT_COL] = SPADES;
                Cards[i+CARDS_PER_SUIT+CARDS_PER_SUIT+CARDS_PER_SUIT][SUIT_COL] = DIAMONDS;
        }

        for (i=0;i<CARDS_PER_SUIT;i++) {
                Cards[i][PATTERN_COL] = i+1;
                Cards[i+CARDS_PER_SUIT][PATTERN_COL] = i + 1;
                Cards[i+CARDS_PER_SUIT+CARDS_PER_SUIT][PATTERN_COL] = i + 1;
                Cards[i+CARDS_PER_SUIT+CARDS_PER_SUIT+CARDS_PER_SUIT][PATTERN_COL] = i + 1;
        }
        // Set the state of the module to initialized
        Card_state = CARD_STATE_INIT;
}



// Get a card from the current deck.
//
// suit: This is interpreted as follows:
//     1 = Clubs
//     2 = Hearts
//     3 = Spades
//     4 = Diamonds
//
// pattern: This is interpreted as the 
//     1 = Ace
//     2..10 as expected
//     11 = Jack
//     12 = Queen
//     13 = King
extern void card_get(unsigned char *suit, unsigned char *pattern)
{
        static int next_card = 0; // index into Cards array
        int random_card = 0;
        int random_pattern = 0;
        int random_suit = 0;
        // Make sure we are ready to run...
        if (Card_state != CARD_STATE_INIT) {
                printf(RESET);
                printf("card_get was called before card_init\n");
                exit(-1);
        }

        if (!Deck_shuffled) {
                // shuffle the deck
                // ****** TBD student code goes here to shuffle the deck
        //*suit = cards[i][SUIT];
        //*pattern = cards[j][PATTERN];       
                for (int i=0;i<CARDS_PER_DECK;i++) {
                        random_card = random() % CARDS_PER_SUIT;
                        random_pattern = Cards[random_card][PATTERN_COL];
                        random_suit = Cards[random_card][SUIT_COL];
                
                        Cards[random_card][PATTERN_COL] = Cards[i][PATTERN_COL];
                        Cards[random_card][SUIT_COL] = Cards[i][SUIT_COL];
                
                        Cards[i][PATTERN_COL] = random_pattern;
                        Cards[i][SUIT_COL] = random_suit;
                }                
                // Mark that the deck is shuffled,
                // as well as the index to the next card to take.
                Deck_shuffled = true;
                next_card = 0;
        }
        *suit = Cards[next_card][SUIT_COL];
        *pattern = Cards[next_card][PATTERN_COL];
        ++next_card;
        if (next_card == CARDS_PER_DECK) {
                next_card = 0;
                Deck_shuffled = false;
        }
        // Return a card from the "top" of the deck
        // TBD code to return the next card
} // card_get()


// end of card.c
