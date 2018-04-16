/***********************************************************************
 * Module:
 *    Week 11, Sort Bubble
 *    Brother Helfrich, CS 235
 * Author:
 *    Spencer Eccles
 *    Jonathan Sirrine
 *    Atsushi Jindo
 *    Eric Brich
 * Summary:
 *    This program will implement the Bubble Sort
 ************************************************************************/

#ifndef SORT_BUBBLE_H
#define SORT_BUBBLE_H

/*****************************************************
 * SORT BUBBLE
 * Perform the bubble sort
 ****************************************************/
template <class T>
void sortBubble(T array[], int num)
{
   for (int iPivot = num - 1; iPivot > 0; iPivot--)
   {
      bool swapped = false;
      for (int iCheck = 0; iCheck <= iPivot - 1; iCheck++)
      {
         if (array[iCheck] > array[iCheck + 1])
         {
            T temp = array[iCheck];
            array[iCheck] = array[iCheck + 1];
            array[iCheck + 1] = temp;
            swapped = true;
         }
      }
      if (!swapped)
         return;
   }
}


#endif // SORT_BUBBLE_H
