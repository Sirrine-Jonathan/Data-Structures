/***********************************************************************
 * Module:
 *    Assignment 02, Stack
 *    Brother JonesL, CS 235
 * Author:
 *    Br. Helfrich
 * Summary:
 *    This file will implement a stack ADT
 ************************************************************************/
#ifndef STACK_H
#define STACK_H
#include <cassert>  // because I am paranoid
#include <iostream>
namespace custom
{
/**************************************************
 * STACK
 * First-in-Last-out data structure
 *************************************************/
template <class T>
class stack
{
public:
   // constructors, destructors, and assignment operator
   stack() : data(NULL), numCapacity(0), numElements(0)                    { }
   stack(int numCapacity)      throw(const char *);
   stack(const stack<T> & rhs) throw(const char *);
  ~stack()             { if (numCapacity != 0) delete [] data; }
   stack <T> & operator = (const stack <T> & rhs) throw (const char *);
   
   // standard container interfaces
   int  size     () const                     { return numElements;           }
   int  capacity () const                     { return numCapacity;           }
   bool empty    () const                     { 
	  //std::cerr << "numElements = " << numElements << std::endl;
	  return numElements == 0;      
   }
   void clear    ()                           { numElements = 0;              }
   
   // stack-specific interfaces
   void pop();
   T &  top()                  throw(const char *);
   const T & top() const       throw(const char *);
   void push(const T & t)      throw(const char *);
  
private:
   void resize(int newMax = 0) throw(const char *);
  
   T * data;             // dynamically allocated data for the stack
   int numCapacity;      // the size of the data array
   int numElements;      // the number of elements currently used in the array
};
/**********************************************************
 * STACK :: non-default constructor
 * This is O(1)
 *********************************************************/
template <class T>
stack <T> :: stack (int numCapacity) throw (const char *) :
      data(NULL), numCapacity(0), numElements(0)
{
   this->numCapacity = numCapacity;
   if(capacity() > 0)
      resize(numCapacity);	   
}

/**********************************************************
 * STACK :: copy constructor
 * This is O(n) where n == rhs.size()
 *********************************************************/
template <class T>
stack <T> :: stack (const stack <T> & rhs) throw (const char *) :
      data(NULL), numCapacity(0), numElements(0)
{
   //if there are no elements in rhs
   if (rhs.empty())
   {
	  data = NULL;
	  clear();
   }
   
   //if there are more elements in rhs
   if (rhs.size() > size())
   {
      data = new T[rhs.numElements];
      numCapacity = rhs.numElements;
      numElements = rhs.numElements;
   }

   assert(numElements == rhs.numElements);
   for (int i = 0; i < numElements; i++)
      data[i] = rhs.data[i];

   // paranoia
   assert(rhs.numCapacity >= 0              );
   assert(rhs.numElements >= 0              );
   assert(rhs.numElements <= rhs.numCapacity);
}
/*********************************************************
 * STACK :: assign
 * Copy one stack onto another
 * This is O(n) where n == rhs.size();
 ********************************************************/
template <class T>
stack<T> & stack <T> :: operator = (const stack <T> & rhs) throw (const char *)
{
   //if there are no elements in rhs
   if (rhs.empty())
   {
	  data = NULL;
	  clear();
   }
   
   //if there are more elements in rhs
   if (rhs.size() > size())
   {
      data = new T[rhs.numElements];
      numCapacity = rhs.numElements;
      numElements = rhs.numElements;
   }

   assert(numElements == rhs.numElements);
   for (int i = 0; i < numElements; i++)
      data[i] = rhs.data[i];

   // paranoia
   assert(rhs.numCapacity >= 0              );
   assert(rhs.numElements >= 0              );
   assert(rhs.numElements <= rhs.numCapacity);
   
   return *this;
}
/********************************************************
 * STACK :: TOP
 * Returns a reference to the top element in the stack.
 *******************************************************/
template <class T>
T & stack <T> :: top() throw(const char *)
{
   // if an element is not present in the stack, throw
   if (empty())
      throw "ERROR: Unable to reference the element from an empty Stack";
   return data[numElements - 1];
}
/********************************************************
 * STACK :: TOP
 * Returns a reference to the top element in the stack. 
 *******************************************************/
template <class T>
const T & stack <T> :: top() const throw(const char *)
{
   // if an element is not present in the stack, throw
   if (empty())
      throw "ERROR: Unable to reference the element from an empty Stack";
  return data[numElements - 1];
}
/********************************************************
 * STACK :: POP
 * Removes the element on top of the stack, effectively reducing its size by
 * one.
 *******************************************************/
template <class T>
void stack <T> :: pop()
{
   // if an element is not present in the stack, do nothing
   if (numElements == 0)
     return;
   numElements--;
}

// old push function. If you guys still want this, let me know.
// I kind of decided to run a different direction with it
// Message me with any questions you have about it
/*template <class T>
void stack <T> :: push(const T & t) throw(const char *)
{
   // make sure there is room in our stack  
   if (numElements == numCapacity)
     resize(numCapacity);
   
   numElements++;
   data[numElements - 1] = t;
}*/

/********************************************************
 * STACK :: PUSH
 * Inserts a new element at the top of the stack, above its current
 * top element. The content of this new element is initialized to a
 * copy of t.
 *******************************************************/
template <class T>
void stack <T> :: push(const T & t) throw(const char*)
{
	if (numCapacity == 0)
	{
		numCapacity = 1;

		//attempt to allocate space
		try
		{
			data = new T[numCapacity];
		}
		catch (std::bad_alloc)
		{
			throw "ERROR: Unable to allocate a new buffer for the Stack";
		}
	}
	else if (numElements == numCapacity)
	{
		// double capacity size
		numCapacity *= 2;
		// create temp object for stack copy
		T * temp;

		// attempt to push
		try
		{
			temp = new T[numCapacity];
		}
		catch (std::bad_alloc)
		{
			throw "ERROR: unable to push the stack!";
		}

		// copy over from temp array
		for (int i = 0; i < numElements; i++)
		{
			temp[i] = data[i];
		}
		// helps stop memory leaks
		delete [] data;
		data = temp;
	}
	data[numElements] = t;
	numElements++;
}
/*********************************************************
 * STACK :: RESIZE
 * Grow the size of the stack to (at a minimum) of a given
 * size.  If the size is set to zero, then the capacity will
 * be doubled.  If the stack is currently not empty, the contents
 * will be copied over to the new buffer
 *   This is O(n) where  n == this->num
 *********************************************************/
template <class T>
void stack <T> :: resize(int newCapacity) throw(const char *)
{
   assert(numCapacity >= 0);
   assert(numElements >= 0);
   
   // determine the new buffer size
   if (numElements == 0)
   {
   // allocate the new buffer
      data = new T[1];
      numCapacity = 1;
   }
   else
   {
      numCapacity *= 2;
      // allocate the new buffer
      T *pData = new T[numCapacity];
      // copy the contents of the old buffer over to the new buffer
      for (int i = 0; i < numElements - 1; i++)
         pData[i] = data[i];
     // helps stop memory leaks
      delete [] data;
      data = pData;
      
   }
   
   assert(numElements <= numCapacity);
   
}

}// end namespace custom
#endif // STACK_H