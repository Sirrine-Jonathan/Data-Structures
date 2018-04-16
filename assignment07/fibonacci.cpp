/***********************************************************************
 * Implementation:
 *    FIBONACCI
 * Summary:
 *    This will contain the implementation for fibonacci() as well as any
 *    other function or class implementations you may need
 * Author
 *   Spencer Eccles
 *   Jonathan Sirrine
 *   Atsushi Jindo
 *   Eric Brich
 **********************************************************************/

#include <iostream>
#include "fibonacci.h"   // for fibonacci() prototype
#include "list.h"        // for LIST
#include "wholeNumber.h" // for WholeNumber
using namespace std;

/******************************************************
* COMPUTE FIBONACCI
* Computes the nth element of a fibonacci sequence
*****************************************************/
int computeFibonacci(int number)
{
  if (number == 1 || number == 2)
  {
    return 1;
  }
  int prev = 1;
  int curr = 1;
  int next;
  for (int i = 3; i <= number; i++)
  {
      next = prev + curr;
      prev = curr;
      curr = next;
  }
  return next;
}

/******************************************************
* COMPUTE FIBONACCI
* Computes the nth element of a fibonacci sequence
*****************************************************/
int computeLargeFibonacci(int number)
{
   //WholeNumber currList;
   //WholeNumber nextList;
  list<int> currList;
  list<int> nextList;

  currList.push_back(1);
  list<int> prevList(currList);

  int carry = 0;
  int sumBack = 0;
  //WholeNumber<unsigned int> carry = 0;
  //WholeNumber<unsigned int> sumBack = 0;
  //unsigned int carry = 0;
  //unsigned int sumBack = 0;

  for (int i = 0; i < number - 2; i++)
  {
      
    nextList.clear();
      
    for(list<int> :: reverse_iterator cit = currList.rbegin();
        cit != currList.rend(); --cit)
        for(list<int> :: reverse_iterator pit = prevList.rbegin();
            pit != prevList.rend(); --pit)
        {

              sumBack = (((*cit + *pit) % 1000) + carry);
              carry = (((*cit + *pit) - sumBack) / 1000);
               
              nextList.push_front(sumBack);
              sumBack = 0;
            
              if(carry >= 1 && pit == prevList.rbegin())
              {
                nextList.push_front(carry);
                carry = 0;
                  
                if(prevList.size() != nextList.size())
                    currList.push_front(0);
              }

              prevList.clear();
              prevList = currList;
               
              currList.clear();
              currList = nextList;            
        }      
  }   
  // display List for nth Fibonacci number
  cout << "\t";

  for(list<int> :: iterator it = nextList.begin();
      it != nextList.end(); ++it)
  {
    if(*it != nextList.back())
    {
        cout << *it << ",";
    }
    else
    {
        cout << *it << endl;
    }
   }

}
 
/************************************************
 * FIBONACCI
 * The interactive function allowing the user to
 * display Fibonacci numbers
 ***********************************************/
void fibonacci()
{
   // show the first serveral Fibonacci numbers
   int number;
   cout << "How many Fibonacci numbers would you like to see? ";
   cin  >> number;

   // your code to display the first <number> Fibonacci numbers
   for (int i = 1; i <= number; i++)
   {
      cout << "\t" << computeFibonacci(i) << endl;   
   } 
      
   // prompt for a single large Fibonacci
   cout << "Which Fibonacci number would you like to display? ";
   cin  >> number;

   // your code to display the <number>th Fibonacci number
   cout << computeLargeFibonacci(number) << endl;
}