/***********************************************************************
 * Implementation:
 *    STOCK
 * Summary:
 *    This will contain the implementation for stocksBuySell() as well
 *    as any other function or class implementation you need
 * Author
 *    Spencer Eccles
 *    Jonathan Sirrine
 *    Atsushi Jindo
 *    Eric Brich
 **********************************************************************/
 
#include <iostream>    // for ISTREAM, OSTREAM, CIN, and COUT
#include <string>      // for STRING
#include <cassert>     // for ASSERT
#include "stock.h"     // for STOCK_TRANSACTION
#include "queue.h"     // for QUEUE
#include "dollars.h"   // still not getting Dollar though

//using namespace std;
using namespace custom;

/************************************************
 * STOCKS BUY SELL
 * The interactive function allowing the user to
 * buy and sell stocks
 ***********************************************/
void stocksBuySell()
{
   // instructions
   std::cout << "This program will allow you to buy and sell stocks. "
        << "The actions are:\n";
   std::cout << "  buy 200 $1.57   - Buy 200 shares at $1.57\n";
   std::cout << "  sell 150 $2.15  - Sell 150 shares at $2.15\n";
   std::cout << "  display         - Display your current stock portfolio\n";
   std::cout << "  quit            - Display a final report and quit the program\n";
   
   /*
   //declare user input variables
   custom::queue <string> q;
   string wordInput;
   int numStocks;
   Dollars price;
   
   do
   {
   //get first word
   cout << ">";
   cin >> wordInput;
	
   //handle first word
   if (wordInput == "quit")
      return;
   else if (wordInput == "display")
   {
	   //do display
	   cout << "Currently held:\n";
		
		//cout << "\t" << queueS.wordInput << "$";
   }
   else
   {
      cin >> numStocks >> price;
	  cout << wordInput << numStocks << price;
   }
}*/

   std::string choice;
   int quantity;
   class custom::queue <int> buyQueue;
   Dollars price;
   class custom::queue <Dollars> buyPriceQueue;
   class custom::queue <int> sellQueue;
   class custom::queue <Dollars> sellPriceQueue;
   class custom::queue <Dollars> portfolio; //holds profit/loss
   int buyTran = 0; //buy transaction counter
   int sellTran = 0; //sell transaction counter

   do
   {
      std::cout << "> ";
      std::cin >> choice;

      
      if (choice == "buy")
      {
        std::cin >> quantity >> price;
        buyQueue.push(quantity);
        buyPriceQueue.push(price);
        buyTran++;
  
      }
      else if (choice == "sell")
      {
        class custom::queue <int> wrkQ;
        class custom::queue <Dollars> wrkP;

        std::cin >> quantity >> price;
        wrkQ.push(quantity);
        wrkP.push(price);
        sellTran++;

        int sellShares = 0;
        int buyShares = 0;
        //calculate proceeds

        sellShares = wrkQ.front();
        while (sellShares != buyShares)
        {
            buyShares = buyQueue.front(); //get share count
            sellShares = wrkQ.front();
            Dollars proceeds = 0; 
            
            if(sellShares < buyShares)
            {
                int tempFront = buyQueue.iTail(); //get current position
                proceeds = (wrkP.front() - buyPriceQueue.front()) * sellShares;
                // move items from workQ to sell and price queues
                sellQueue.push(wrkQ.front());
                sellPriceQueue.push(wrkP.front());
                wrkQ.pop();
                wrkP.pop();
                //set buy queues properly
                buyQueue.pop();
                buyShares -= sellShares;
                buyQueue.push(buyShares); //push new share count
                buyShares = sellShares;  //setting the same to break the loops
                portfolio.push(proceeds); //pushing proceeds of sale to portfolio queue
            }
            else if (sellShares == buyShares)
            {
                proceeds = ((wrkP.front() - buyPriceQueue.front()) * sellShares);
                sellQueue.push(wrkQ.front());
                sellPriceQueue.push(wrkP.front());
                wrkQ.pop();
                wrkP.pop();
                buyQueue.pop();         //pop all purchased shares at this price
                buyPriceQueue.pop();    //pop all share prices at this quantity
                buyShares = sellShares;  //setting the same to break the loops
                portfolio.push(proceeds); //pushing proceeds of sale to portfolio queue
                buyTran--;
            }
            else
            {
                int tempFront = wrkQ.iHead(); //get current position
                int tempBack = wrkQ.iTail();
                proceeds = ((wrkP.front() - buyPriceQueue.front()) * buyShares);
                buyQueue.pop();         //pop all purchased shares at this price
                buyPriceQueue.pop();    //pop all share prices at this quantity
                portfolio.push(proceeds); //pushing proceeds of sale to portfolio queue
                sellShares -= buyShares; //decrements the sell Shares buy the buy share amt.
                sellQueue.push(buyShares);
                sellPriceQueue.push(wrkP.front());
                wrkQ.pop();
                wrkQ.push(sellShares);
                buyTran--;
                sellTran++;
            }

        }

      }
      else if (choice == "display")
      {
        Dollars portSum = 0; //for use with the proceeds

         queue <int> bQ(buyQueue); //buyQueue
         queue <Dollars> bP(buyPriceQueue); //buyPriceQueue
         queue <int> sQ(sellQueue); //sellQueue
         queue <Dollars> sP(sellPriceQueue); //sellPriceQueue
         queue <Dollars> pList(portfolio); //portfolio queue
         
        //output holdings
         if (buyTran > 0)
         {
            std::cout << "Currently held:\n";
            for (int i = 0; i < buyTran; i++)
            {
                std::cout << "\tBought " << bQ.front()
                    << " shares at " << bP.front()
                    << std::endl;
                bQ.pop();
                bP.pop();
            }
         }

         //output sell history
         if (sellTran > 0)
         {
             std::cout << "Sell History:\n";
            for (int i = 0; i < sellTran; i++)
            {
                std::cout << "\tSold " << sQ.front()
                    << " shares at " << sP.front()
                    << " for a profit of " << pList.front() << std::endl; 
                portSum += pList.front();
                sQ.pop();
                sP.pop();
                pList.pop();
            }
         }
         
         //display proceeds
         std::cout << "Proceeds: "; 
         if (portfolio.empty())
         {
             std::cout << "$0.00\n";
         }
         else
         {
             std::cout << portSum << std::endl;
         }
      }
    }
   while (choice != "quit");        
}


