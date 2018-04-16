/***********************************************************************
 * Module:
 *    Week 11, Sort Binary
 *    Brother Helfrich, CS 235
 * Author:
 *    Spencer Eccles
 *    Jonathan Sirrine
 *    Atsushi Jindo
 *    Eric Brich
 * Summary:
 *    This program will implement the Binary Tree Sort
 ************************************************************************/

#ifndef SORT_BINARY_H
#define SORT_BINARY_H

#include "bst.h"
#include <cassert>

/*****************************************************
 * SORT BINARY
 * Perform the binary tree sort
 ****************************************************/
template <class T>
void sortBinary(T array[], int num)
{
   typename custom :: BST <T> bst;
   for (int i = 0; i <= num - 1; i++)
      bst.insert(array[i]);
   

   int i = 0;
   for (typename custom::BST <T> :: iterator it = bst.begin(); !(it == bst.end()); ++it)
      array[i++] = *it;
}


#endif // SORT_BINARY_H
