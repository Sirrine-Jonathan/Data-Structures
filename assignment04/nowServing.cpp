/***********************************************************************
 * Implementation:
 *    NOW SERVING
 * Summary:
 *    This will contain the implementation for nowServing() as well as any
 *    other function or class implementations you may need
 * Author
 *    Spencer Eccles
 *    Jonathan Sirrine
 *    Atsushi Jindo
 *    Eric Brich
 **********************************************************************/

#include <iostream>     // for ISTREAM, OSTREAM, CIN, and COUT
#include <string>       // for STRING
#include <cassert>      // for ASSERT
#include "nowServing.h" // for nowServing() prototype
#include "deque.h"      // for DEQUE
//using namespace std;
using namespace custom;


/************************************************
 * NOW SERVING
 * The interactive function allowing the user to
 * handle help requests in the Linux lab
 ***********************************************/
void nowServing()
{
   // instructions
   std::cout << "Every prompt is one minute.  The following input is accepted:\n";
   std::cout << "\t<class> <name> <#minutes>    : a normal help request\n";
   std::cout << "\t!! <class> <name> <#minutes> : an emergency help request\n";
   std::cout << "\tnone                         : no new request this minute\n";
   std::cout << "\tfinished                     : end simulation\n";

   // your code here
   class custom::deque <std::string> choiceDeque;
   class custom::deque <std::string> nameDeque;
   class custom::deque <int> minDeque;
   std::string choice;
   std::string name;
   int minutes = 0;
   int request = 0;
   int emergency = 0;
   int newFront = 0;
   
   do
   {
      std::cout << "<" << request << "> ";
      request++;
      
      std::cin >> choice;
      
      if(choice == "cs124" || choice == "cs165")
      {
         std::cin >> name >> minutes;
         
         if(choiceDeque.size() == 0)
         {
            choiceDeque.push_front(choice);
            nameDeque.push_front(name);
            minDeque.push_front(minutes);
            
            std::cout << "\tCurrently serving " << nameDeque.front()
                 << " for class " << choiceDeque.front()
                 << ". Time left: " << minDeque.front() << std::endl;
         }
         else
         {
            choiceDeque.push_back(choice);
            nameDeque.push_back(name);
            minDeque.push_back(minutes);
            
            std::cout << "\tCurrently serving " << nameDeque.front()
                 << " for class " << choiceDeque.front()
                 << ". Time left: " <<  minDeque.front() << std::endl;
         }

         newFront = minDeque.front();
         newFront -= 1;
         minDeque.pop_front();
         minDeque.push_front(newFront);


         if(!newFront)
         {
            nameDeque.pop_front();
            choiceDeque.pop_front();
            minDeque.pop_front();
         }
  
      }
      else if(choice == "!!")
      {
         std::cin >> choice >> name >> minutes;
         emergency = 1;
         
         if(nameDeque.size() > 0)
         {
            std::cout << "\tCurrently serving " << nameDeque.front()
                 << " for class " << choiceDeque.front()
                 << ". Time left: " <<  minDeque.front() << std::endl;
            
            newFront = minDeque.front();
            newFront -= 1;
            minDeque.pop_front();
            minDeque.push_front(newFront);
                        
            if(!newFront)
            {
               nameDeque.pop_front();
               choiceDeque.pop_front();
               minDeque.pop_front();
            }
                        
            choiceDeque.push_front(choice);
            nameDeque.push_front(name);         
            minDeque.push_front(minutes);
            
         }
         else
         {
            choiceDeque.push_front(choice);
            nameDeque.push_front(name);
            minDeque.push_front(minutes);         
            
            std::cout << "\tEmergency for " << nameDeque.front()
                 << " for class " << choiceDeque.front()
                 << ". Time left: " <<  minDeque.front() << std::endl;

            emergency = 0;
            
            newFront = minDeque.front();
            newFront -= 1;
            minDeque.pop_front();
            minDeque.push_front(newFront);
                       
            if(!newFront)
            {
               nameDeque.pop_front();
               choiceDeque.pop_front();
               minDeque.pop_front();
            }
         }
      }
      else if(choice == "none")
      {
         if(nameDeque.size() > 0)
         {
            if(!emergency)
            {
            std::cout << "\tCurrently serving " << nameDeque.front()
                 << " for class " << choiceDeque.front()
                 << ". Time left: " <<  minDeque.front() << std::endl;
            }
            else
            {
               std::cout << "\tEmergency for " << nameDeque.front()
                    << " for class " << choiceDeque.front()
                    << ". Time left: " <<  minDeque.front() << std::endl;

               emergency = 0;
            }
            
            newFront = minDeque.front();
            newFront -= 1;
            minDeque.pop_front();
            minDeque.push_front(newFront);

            if(!newFront)
            {
               nameDeque.pop_front();
               choiceDeque.pop_front();
               minDeque.pop_front();
            }            
         } 
      }
   }
   while(choice != "finished");

   if(choice == "finished")
   {
     // end
     std::cout << "End of simulation\n";
   }  
}



