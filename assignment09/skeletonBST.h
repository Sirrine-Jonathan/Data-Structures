/***********************************************************************
 * Component:
 *    Assignment 09, Binary Search Tree (BST)
 *    Brother <your instructor name here>, CS 235
 * Author
 *    Spencer Eccles
 *    Jonathan Sirrine
 *    Atsushi Jindo
 *    Eric Brich
 * Summary:
 *    Create a binary search tree
 * Notes:
 *    Body of BST iterator decrement operator is commented out
 ************************************************************************/

#ifndef BST_H
#define BST_H

#include "debug.h"

namespace custom
{
/**************************************************
 * BST
 *************************************************/
template <class T>
class BST
{
  public:
   BST() throw(const char *) : root(NULL) {}
   BST(const BST <T> & rhs) throw(const char *);
   ~BST(){ deleteBinaryTree(root); };
   BST <T> & operator = (const BST<T> & rhs) throw(const char *);

   bool empty() const { return (root == NULL); }
   void clear() { deleteBinaryTree(root); }
   int size() { return numElements; }



   class iterator;
   class reverse_iterator;
  // class const_iterator;

   iterator insert(iterator & it, const T & t) throw(const char *);
   iterator erase(iterator it);
   iterator begin() { return iterator(root); }
   iterator end() { return iterator(NULL); }
   reverse_iterator rbegin();
   reverse_iterator rend()   { return  reverse_iterator(NULL);  }
   iterator find(T & t);   


  private:
   class BNode;
   BNode * root;
   int numElements;
}; // BST

/*******************************************************************************
* BNODE
* BST node.
*******************************************************************************/
template <class T>
class BST <T> :: BNode 
{
  public:
   T data;
   BNode * pLeft;
   BNode * pRight;
   BNode * pParent;

   void addLeft(BNode * pNode, BNode * pAdd) throw (const char *);

   BNode() : pLeft(NULL), pRight(NULL), pParent(NULL), data() {}
   BNode(const T & data) : pLeft(NULL), pRight(NULL), pParent(NULL), data(data) {}
};

/*******************************************************************************
* BNODE FUNCTION
* addLeft 
*******************************************************************************/
template <class T>
void BST <T> :: BNode :: addLeft (BNode * pNode, BNode * pAdd) throw  (const char *)
{
   try
   {
      pNode->pLeft = pAdd;

      // if we are inserting to the left position
      if (pAdd !=NULL)
      {
         //pNode->pLeft->pParent = pNode;
         pAdd->pParent = pNode;
      }
   }
   catch(...)
   {
      throw "Error: Unable to allocate new node";
   }
}

/**************************************************
* BST ITERATOR
**************************************************/
template <class T>
class BST <T> :: iterator
{ 
   typename BST <T> :: iterator & operator -- ();
}; // BST iterator

/**************************************************
 * BST ITERATOR :: DECREMENT PREFIX
 *     advance by one. 
 * Author:      Br. Helfrich
 * Performance: O(log n) though O(1) in the common case
 *************************************************/
template <class T>
typename BST <T> :: iterator & BST <T> :: iterator :: operator -- ()
{
/*
   // do nothing if we have nothing
   if (NULL == pNode)
      return *this;

   // if there is a left node, take it
   if (NULL != pNode->pLeft)
   {
      // go left
      pNode = pNode->pLeft;

      // jig right - there might be more right-most children
      while (pNode->pRight)
         pNode = pNode->pRight;
      return *this;
   }

   // there are no left children, the right are done
   assert(NULL == pNode->pLeft);
   BNode * pSave = pNode;

   // go up
   pNode = pNode->pParent;

   // if the parent is the NULL, we are done!
   if (NULL == pNode)
      return *this;

   // if we are the right-child, got to the parent.
   if (pSave == pNode->pRight)
      return *this;

   // we are the left-child, go up as long as we are the left child!
   while (NULL != pNode && pSave == pNode->pLeft)
   {
      pSave = pNode;
      pNode = pNode->pParent;
   }

   return *this;
*/
} // BST ITERATOR :: DECREMENT PREFIX

}// namespace custom

#endif // BST_H
