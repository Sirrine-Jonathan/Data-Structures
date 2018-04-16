/***********************************************************************
* Header:
*    list
* Summary:
*    Hand-made library for a list along with an iterator and
*	 a const iterator
*
*    This will contain the class definition of:
*        list         : A class that holds stuff
*        listIterator : An interator through Container
*        listConstIterator : A const iterator
* Author
*    Spencer Eccles
*    Jonathan Sirrine
*    Atsushi Jindo
*    Eric Brich
************************************************************************/

#ifndef LIST_H
#define LIST_H
 
#include <cassert>
#include <iostream>

//#include "wholeNumber.h"

/*******************************************************************************
* LIST
* a list
*******************************************************************************/
template <class T>
class list
{
	public:
	// default constructor
	list() : numItems(0), pHead(NULL), pTail(NULL) {}
	// non-default constructor
   list(const list <T> &rhs) throw (const char *): numItems(0), pHead(NULL), 
    	pTail(NULL) {*this = rhs;}

   // deconstructor
   ~list() { clear(); }

   // standard std::library functions
   bool empty () const { return (pHead == 0); }
   void clear();
   int size() { return numItems; }
   void push_back(const T & t) throw(const char *);
   void push_front(const T & t) throw(const char *);
	
   // getters
   T & front() 	throw (const char *);
   T & back() 	throw (const char *);

   // assignment operator
   list <T> & operator = (const list<T> & rhs) throw(const char *);

   // iterator functions
	
	class iterator;
	class reverse_iterator;
	class const_iterator;
	
   // insert an item somewhere in the list
   iterator insert(iterator & it, const T & t) throw(const char*);
   // remove an item from somewhere in the list
   iterator erase(iterator it);

   // return an iterator to the beginning of the list
   iterator begin()  { return iterator(pHead); }
   // return an iterator to the end of the list
   reverse_iterator rbegin() { return reverse_iterator(pTail); }
   const_iterator crbegin()  { return const_iterator(pTail);   }

   // return an iterator referring to the past-the-end element in the list
   iterator end()    { return  iterator(NULL);  }
   // return an interator referring to the past-the-front element in the list
   reverse_iterator rend()   { return  reverse_iterator(NULL);  }
   const_iterator crend()    { return  const_iterator(NULL);    }
	
	private:
	
	class Node;
	
	int numItems;     // counts number of items in list
	Node * pHead; // keeps track of the beginning of list
	Node * pTail; // keeps track of the end of list
};

/*******************************************************************************
* NODE
* list node.
*******************************************************************************/
template <class T>
class list <T> :: Node
{
public:
   T data;
   Node * pPrev;
   Node * pNext;
   
   Node() : data(), pNext(NULL), pPrev(NULL) {}
   Node(const T & t) : data(t), pPrev(NULL), pNext(NULL) {}
};

/**************************************************
* LIST ITERATOR
* An iterator through list
**************************************************/
template <class T>
class list <T> :: iterator
{
  public:
   iterator()      : p(NULL)      {              }
   iterator(Node * p) : p(p)      {              }
   iterator(const iterator & rhs) { *this = rhs; }
   iterator & operator = (const iterator & rhs)
   {
      p = rhs.p;
      return *this;
   }

   // equals, not equals operator
   bool operator != (const iterator & rhs) const { return rhs.p != this->p; }
   bool operator == (const iterator & rhs) const { return rhs.p == this->p; }

   // dereference operator
         T & operator * ()  throw (const char *)
			{
				if (p)
					return p->data;
				else
					throw "ERROR: Trying to dereference a NULL pointer";
			}
			
   /* const T & operator * () const { return *p; } */

   // prefix increment
   iterator & operator ++ ()
   {
      if (p)
        p = p->pNext;
      return *this;
      //p++;
      //return *this;
   }

   // postfix increment
   iterator operator ++ (int postfix)
   {
      iterator old(*this);
      if (p)
        p = p->pNext;
      return old;
      //iterator tmp(*this);
      //p++;
      //return tmp;
   }
   
   // prefix decrement
   iterator & operator -- ()
   {
      if (p)
        p = p->pPrev;
      return *this;
      //p--;
      //return *this;
   }

   // postfix decrement
   iterator operator -- (int postfix)
   {
      iterator old(*this);
      if (p)
        p = p->pPrev;
      return *this;
      //iterator tmp(*this);
      //p--;
      //return tmp;
   }  
   
   // two friends who need to access p directly
   friend iterator list <T> :: insert(iterator & it, const T & data) throw (const char *);
   friend iterator list <T> :: erase(iterator it) throw(const char *);

 private:
   typename list <T> :: Node * p;
};

/**************************************************
* LIST CONST_ITERATOR
* An const_iterator through list
**************************************************/
template <class T>
class list <T> :: const_iterator
{
public:
   // constructors, destructors, and assignment operator
   const_iterator()      : p(NULL)      {              }
   const_iterator(Node * p) : p(p)         {              }
   const_iterator(const const_iterator & rhs) { *this = rhs; }
   const_iterator & operator = (const const_iterator & rhs)
   {
      p = rhs.p;
      return *this;
   }

   // equals, not equals operator
   bool operator != (const const_iterator & rhs) const { return rhs.p != this->p; }
   bool operator == (const const_iterator & rhs) const { return rhs.p == this->p; }

   // dereference operator
         T & operator * ()       { return *p; }
   const T & operator * () const { return *p; }

   // prefix increment
   const_iterator & operator ++ ()
   {
      //p++;
    if (p)
      p = p->pNext;
    return *this;
   }

   // postfix increment
   const_iterator operator ++ (int postfix)
   {
      const_iterator old(*this);
      if (p)
        return p->pNext;
      //p++;
      return old;
   }
   
   // prefix decrement
   const_iterator & operator -- ()
   {
      //p--;
      if (p)
        p = p->pPrev;
      return *this;
   }

   // postfix decrement
   const_iterator operator -- (int postfix)
   {
      const_iterator old(*this);
      //p--;
      if (p)
        p = p->pPrev;
      return old;
   }
   
 private:
   list <T> :: Node * p;
};

/**************************************************
* LIST REVERSE_ITERATOR
* An reverse_iterator through list
**************************************************/
template <class T>
class list <T> :: reverse_iterator
{
  public:
   reverse_iterator()      : p(NULL)      {              }
   reverse_iterator(Node * p) : p(p)         {              }
   reverse_iterator(const reverse_iterator & rhs) { *this = rhs; }
   reverse_iterator & operator = (const reverse_iterator & rhs)
   {
      p = rhs.p;
      return *this;
   }

   // equals, not equals operator
   bool operator != (const reverse_iterator & rhs) const { return rhs.p != this->p; }
   bool operator == (const reverse_iterator & rhs) const { return rhs.p == this->p; }

   // dereference operator
         T & operator * () throw (const char *)
			{
				if (p)
					return p->data;
				else
					throw "ERROR: Trying to dereference a NULL pointer";
			}

   // prefix increment
   reverse_iterator & operator ++ ()
   {
      //p++;
      if (p)
        p = p->pPrev;
      return *this;
   }

   // postfix increment
   reverse_iterator operator ++ (int postfix)
   {
      reverse_iterator old(*this);
      if (p)
        p = p->pPrev;
      return old;
      //reverse_iterator tmp(*this);
      //p++;
      //return tmp;
   }
   
   // prefix decrement
   reverse_iterator & operator -- ()
   {
      //p--;
      if (p)
        p = p->pNext;
      return *this;
   }

   // postfix decrement
   reverse_iterator operator -- (int postfix)
   {
      reverse_iterator old(*this);
      if (p)
        p = p->pNext;
      //p--;
      return old;
   } 

  // two friends who need to access p directly
  //friend iterator list <T> :: insert(iterator & it, const T & data) throw (const char *);
  //friend iterator list <T> :: erase(iterator it) throw(const char *);   
   
 private:
   list <T> :: Node  * p;
};

/***********************************************
* list :: clear
* empties list of all items
***********************************************/
template <class T>
void list<T> :: clear()
{
  list<T> :: Node * pNode;

  // loop through the list and empty it
  for (list<T> :: Node * p = pHead; p; p = pNode)
  {
    pNode = p->pNext;
    delete p;
  }

  // don't forget nulls
  pHead = pTail = NULL;
  numItems = 0;
}
/***********************************************
* list :: front
* returns the item currently at the front of list
***********************************************/
template <class T>
T & list<T> :: front() throw(const char *)
{
   assert(numItems >= 0);

   // determine if the list is empty
   if (empty())
      throw "ERROR: unable to access data from an empty list";
   // otherwise return the answer
   return pHead->data;
}

/***********************************************
* list :: back
* returns the item currently at the back of list
***********************************************/
template <class T>
T & list<T> :: back() throw(const char *)
{
   assert(numItems >= 0);

   // determine if the list is empty
   if (empty())
      throw "ERROR: unable to access data from an empty list";
   // otherwise return the answer
   return pTail->data;
}

/***********************************************
* list :: push_back
* adds an item to the back of the list
***********************************************/
template <class T>
void list<T> :: push_back(const T & t) throw(const char *)
{
  try
   {
     // create new node and add data passed
     list<T> :: Node * pNew = new list<T> :: Node(t);
      
     // point to the previous node
     pNew->pPrev = pTail;

     // connect current last to new node
     if (pTail != NULL)
       pTail->pNext = pNew;
     else
       pHead = pNew;

     // connect curent to new
     pTail = pNew;
     numItems++;

   }
   catch (...)
   {
     throw "ERROR: Unable to allocate a new node for a list";
   }
}
/***********************************************
* list :: push_back
* adds an item to the front of the list
***********************************************/
 template <class T>
 void list<T> :: push_front(const T & t) throw(const char *)
 {
   assert(numItems >= 0);

   try
   {
     // create new node and add data passed
     list<T> :: Node * pNew = new list<T> :: Node(t);
      
     // point to the head node
     pNew->pNext = pHead;

     // connect current head to new node
     if (pHead != NULL)
       pHead->pPrev = pNew;
     else
       pTail = pNew;

     // connect current to new
     pHead = pNew;
     numItems++;

   }
   catch (...)
   {
     throw "ERROR: Unable to allocate a new node for a list";
   }
}

/*******************************************
* list :: Assignment Operator
*******************************************/
template <class T>
list<T> & list<T> :: operator=(const list<T> & rhs) throw(const char *)
{
  clear();

  // allocate nodes
  for (list<T> :: Node * p = rhs.pHead; p; p = p->pNext)
    push_back(p->data);

  return *this;
}

/**************************************************
 * ListIterator :: insert
 * insert an item in the middle of the list
 *************************************************/
template <class T>
typename list<T> :: iterator list<T> :: insert(list<T> :: iterator & it, const T & data) 
  throw(const char *)
{
  // check if list is empty
  if (pHead == NULL)
  {
    assert(pTail == NULL);
    pHead = pTail = new list<T> :: Node(data);
    return begin();
  }

  // check if first and last are NULL
  assert(pTail && pHead);
  assert(pHead->pPrev == NULL);
  assert(pTail->pNext == NULL);

  try
  {
    list<T> :: Node * pNode = new list<T> :: Node(data);

    // if this is the end of the list
    if (it == end())
    {
      //update last
      pTail->pNext = pNode;
      pNode->pPrev = pTail;
      pTail = pNode;

      it = pNode;
    }
    else
    {
      // set previous and next
      pNode->pPrev = it.p->pPrev;
      pNode->pNext = it.p;

      // update what next and previous point to
      if (pNode->pPrev)
        pNode->pPrev->pNext = pNode;
      else
        pHead = pNode;
      
      if (pNode->pNext)
        pNode->pNext->pPrev = pNode;
      else
        pTail = pNode;

      it = pNode;
    }
    // increment numItems
    numItems++;
  }
  catch (...)
  {
    throw "ERROR: unable to allocate a new node for list";
  }

  return it;
}

/**************************************************
 * listIterator :: remove
 * remove an item in the middle of the list
 *************************************************/
template <class T>
typename list<T> :: iterator list<T> :: erase(list<T> :: iterator it)
{
  list<T> :: iterator itNext = end();

  // check if invalid iterator
  if (it == end())
    throw "ERROR: enable to remove from an invalid locaton in a list";

  assert(pHead && pTail);

  // prep nodes after current node (from iterator)
  if (it.p->pNext)
  {
    it.p->pNext->pPrev = it.p->pPrev;
    itNext = it.p->pNext;
  }
  else
  {
    // already last node
    pTail = pTail->pPrev;
  }

  // not the first node
  if (it.p->pPrev)
  {
    it.p->pPrev->pNext = it.p->pNext;
  }
  else
  {
    pHead = pHead->pNext;
  }

  // self cleanup
  delete it.p;
  numItems--;

  return itNext;

}
#endif  
