/***********************************************************************
* Program:
*    Week 02, Go Fish
*    Brother Helfrich, CS 235
* Author:
*    <your names here>
* Summary: 
*    This is all the functions necessary to play Go Fish!
*
*    Estimated:  0.0 hrs   
*    Actual:     0.0 hrs
*      Please describe briefly what was the most difficult part.
************************************************************************/

#include <iostream>    // for CIN and COUT
#include <fstream>     // for IFSTREAM
#include "set.h"       // for SET and SET_ITERATOR
#include "card.h"      // for CARD
#include "goFish.h"    // for GOFISH()

using namespace std;
using namespace custom;
#define NUM_ROUNDS 5

/****************************************
 * GO FISH
 * The game of Go Fish
 ****************************************/
class GoFish
{
public:
   // non-default constructor: the filename is the paramter
   GoFish(const char * fileName);

   // play 10 hands of the game
   void playGame();

   // display the game
   friend ostream & operator << (ostream & out, GoFish & rhs);
   
private:
   set <Card> hand;          // the hand of cards
   int found;                // the number found thus far

   // play one round
   void playOneRound(int round);
};

/**********************************************************************
 * GO FISH
 * The function which starts it all
 ***********************************************************************/
void goFish()
{
   // 1. read the hand
   GoFish game("/home/cs235/week05/hand.txt");

   // 2. play the game
   game.playGame();

   // 3. display the hand when finished
   cout << "The remaining cards: " << game;
}

/**********************************************************************
 * GO FISH :: PLAY GAME
 * Play the 10 rounds
 ***********************************************************************/
void GoFish :: playGame()
{
   // display a nice message
   cout << "We will play "
        << NUM_ROUNDS
        << " rounds of Go Fish.  Guess the card in the hand\n";
   
   // play the rounds
   for (int round = 1; round <= NUM_ROUNDS; round++)
      playOneRound(round);

   cout << "You have " << found << " matches!\n";
}

/**********************************************************************
 * GO FISH :: PLAY ONE ROUND
 * Play a single round of the game
 ***********************************************************************/
void GoFish :: playOneRound(int round)
{
   // prompt for a card
   Card card;
   cout << "round " << round << ": ";
   cin  >> card;
      
   // find it
   set <Card> :: iterator it = hand.find(card);
   set <Card> :: iterator itEmpty = hand.end();
   
   // give a message and remove found cards
   if (it == itEmpty)
      cout << "\tGo Fish!\n";
   else
   {
      cout << "\tYou got a match!\n";
      hand.erase(it);
      found++;
   }
}

/********************************************************************
 * GO FISH INSERTION
 * display the contents of the hand
 *******************************************************************/
ostream & operator << (ostream & out, GoFish & rhs)
{
   // check if the list is empty
   set <Card> :: iterator it = rhs.hand.begin();
   if (it == rhs.hand.end())
      return out;

   // display the first item
   out << *it;

   // display the rest
   for (it++; it != rhs.hand.end(); it++)
      out << ", " << *it;

   // finish up
   out << endl;
   return out;
}

/*************************************************
 * GoFish :: GoFish
 * Read a hand from a file
 ************************************************/
GoFish :: GoFish(const char * fileName) : found(0)
{
   // prepare to read
   ifstream fin(fileName);
   if (fin.fail())
   {
      cout << "Error, unable to open file "
           << fileName
           << " for reading.\n";
      return;
   }

   // read all the cards from the file into the hand
   Card card;
   while (fin >> card)
      if (!card.isInvalid())
         hand.insert(card);
   
   // close and return
   fin.close();
}
