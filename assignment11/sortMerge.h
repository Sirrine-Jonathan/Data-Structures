/***********************************************************************
 * Module:
 *    Week 11, Sort Merge
 *    Brother Helfrich, CS 235
 * Author:
 *    Spencer Eccles
 *    Jonathan Sirrine
 *    Atsushi Jindo
 *    Eric Brich
 * Summary:
 *    This program will implement the Merge Sort
 ************************************************************************/

#ifndef SORT_MERGE_H
#define SORT_MERGE_H

using std::cerr;
using std::endl;

template <class T>
void merge(T left[], int nL, T right[], int nR, T destination[]);

/*****************************************************
 * SORT MERGE
 * Perform the merge sort
 ****************************************************/
template <class T>
void sortMerge(T array[], int num)
{
   if (num < 2)
      return;
   int mid = num / 2;
   T left[mid];
   T right[num - mid];
   for (int i = 0; i < mid; i++)
      left[i] = array[i];
   for (int i = mid; i < num; i++)
      right[i - mid] = array[i];

   //spit
   sortMerge(left, mid);
   sortMerge(right, num - mid);
   merge(left, mid, right, num - mid, array);
}

template <class T>
void merge(T left[], int nL, T right[], int nR,  T destination[])
{

/*      //debug
   cerr << "Debug\n";
   cerr << "size of left: " << nL << endl;
   cerr << "size of right: " << nR << endl;

   cerr << "left: [ ";
   for (int i = 0; i < nL; i++)
      cerr << left[i] << ", ";
   cerr << " ]\n";

   cerr << "right: [ ";
   for (int i = 0; i < nR; i++)
      cerr << right[i] << ", ";
   cerr << " ]\n"; */

   int l = 0; //moves through left
   int r = 0; //moves through right
   int k = 0; //moves through destination
   while (l < nL && r < nR)
   {
      if (  !(left[l] > right[r]) )
      {
         destination[k] = left[l];
         l++;
      }
      else
      {
         destination[k] = right[r];
         r++;
      }
      k++;
   }
   while (l < nL)
   {
      destination[k] = left[l];
      k++;
      l++;
   }
   while (r < nR)
   {
      destination[k] = right[r];
      k++;
      r++;
   }
}


#endif // SORT_MERGE_H
