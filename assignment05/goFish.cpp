/***********************************************************************
* Program:
*    Assignment 01, Go Fish
*    Brother Helfrich, CS 235
* Author:
*    Spencer Eccles
*    Jonathan Sirrine
*    Atsushi Jindo
*    Eric Brich
* Summary: 
*    This is all the functions necessary to play Go Fish!
*
*    Estimated:  2.0 hrs   
*    Actual:     3.0 hrs
*      handling the invalid case
************************************************************************/

#include <iostream>
#include <fstream>
#include <string>
#include "set.h"
#include "card.h"
#include "goFish.h"
//using namespace std;
using namespace custom;

/**********************************************************************
 * GO FISH
 * The function which starts it all
 ***********************************************************************/
void goFish()
{
    // set hand variables including text file with pre-set hand.
   class custom::set <Card> hand;
   char fileName[] = "/home/cs235/week05/hand.txt";
   Card fileCard;
   
   // open file 
   std::ifstream fin(fileName);

   // return error if read fails.
   if (fin.fail())
   {
      std::cout << "Error reading file\n";
   }

   // read file and insert each card into the hand.
   while (!fin.eof())
   {
      fin >> fileCard;

      /*ERIC, I used this line to see what the 
        hand was and saw an invalid card coming through.
        std::cerr << "card: " << fileCard << std::endl; */

      hand.insert(fileCard);
   }

   // close file
   fin.close();      

   // set game variables
   Card cardRequest;
   int round = 1;
   int match = 0;

   std::cout << "We will play 5 rounds of Go Fish.  Guess the card in the hand\n";

   // seemed like test bed always ran less than 6 rounds
   while(round < 6)
   {
      std::cout << "round " << round << ": ";
      std::cin >> cardRequest;
      round++;

      // set variables to find requested card in the hand.
      class custom::set <Card> :: iterator itEmpty = hand.end();
      class custom::set <Card> :: iterator itFind = hand.find(cardRequest);

      // ERIC, I added this condition to filter out the invalid
      // GoldFish guess.
      if(itFind != itEmpty && !(*itFind).isInvalid())
      {
         std::cout << "\tYou got a match!\n";
         hand.erase(itFind);
         match++;
      }
      else
      {
         std::cout << "\tGo Fish!\n";
      }
   }

   std::cout << "You have " << match << " matches!\n";
   std::cout << "The remaining cards: ";

   for(int i = 0; i < (hand.size() - 1); i++)
   {
      if (!hand[i].isInvalid())
         std::cout << hand[i] << ", ";
   }

   std::cout << hand[hand.size() - 1] << std::endl;
   
   return ;
}
