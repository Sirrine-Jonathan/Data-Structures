#include <iostream>        // for CIN and COUT
#include <iomanip>         // for SETW
#include <string>          // for the String class
#include <fstream>         // for IFSTREAM
#include <iomanip>         // for SETW
#include <cassert>         // for ASSERT
#include "node.h"          // your Node class should be in node.h
#include "sortInsertion.h" // your insertionSort() function
using namespace std;

#define NUM_COLUMNS   8
#define INDENT        2
#define WIDTH_COLUMN ((80 - INDENT) / NUM_COLUMNS)

/***********************************************
 * DISPLAY
 * Display the contents of the list
 **********************************************/
template <class T>
void display(T array[], int num)
{
   // loop through the entire list
   for (int i = 0; i < num; i++)
   {
      // display the leading indnet
      if (i % NUM_COLUMNS == 0)
         cout << setw(INDENT) << "";

      // display the item
      cout << setw(WIDTH_COLUMN)
           << array[i];

      // display the trailing newline character
      if (i % NUM_COLUMNS == (NUM_COLUMNS - 1) || i == num - 1)
         cout << endl;
   }
}



int main()
{
   cout.setf(ios::fixed | ios::showpoint);
   cout.precision(1);

      // create
      cout << "Create a char linked list: { a, b, c, d, e, f }\n";
      Node <int> * n = NULL;

      n = insert(n, 1, true);            // { c } 
      insert(n, 2, true);                // { c, d }
      insert(n->pNext, 3, true);         // { c, d, f }
      n = insert(n, 4);                  // { b, c, d, f }
      insert(n->pNext->pNext->pNext, 5); // { b, c, d, e, f }
      n = insert(n, 6);                  // { a, b, c, d, e, f }
}