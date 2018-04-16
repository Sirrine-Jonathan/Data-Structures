#ifndef QUEUE_H
#define QUEUE_H
#include <cassert>  // because I am paranoid

namespace custom
{
/**************************************************
 * queue
 * First-in-First-out data structure
 *************************************************/
template <class T>
class queue
{
public:
   // constructors, destructors, and assignment operator
   queue() : data(NULL), numCapacity(0), numPush(0), numPop(0)  { }
   queue(int max)               throw(const char *);
   queue(const queue <T> & rhs) throw(const char *);
   ~queue() { if (numCapacity != 0) delete [] data; }
   queue <T> & operator = (const queue <T> & rhs) throw (const char *);
   
   // standard container interfaces
   int  size()     const                     { return numPush - numPop;      }
   int  capacity() const                     { return numCapacity;           }
   bool empty()    const                     { return size() == 0;           }
   void clear()                              { numPush = numPop = 0;         }
   
   // queue-specific interfaces
   void push(const T & t) throw(const char *);
   void pop();
   T &  front()           throw(const char *);
   T &  back()            throw(const char *);
   void display() const;
   int inline iTail() const
   {
      assert(numCapacity != 0);
      return (numPush - 1) % numCapacity;
   }
   
   int inline iHead() const
   {
      assert(numCapacity != 0);
      return  numPop       % numCapacity;
   }
private:
   // grow the queue as necessary. This will double the size
   void resize(int newCapacity = 0) throw(const char *);
   
   // find the index of the head or the tail in the data array
   /*
   int inline iTail() const
   {
      assert(numCapacity != 0);
      return (numPush - 1) % numCapacity;
   }*/
   
   /*int inline iHead() const
   {
      assert(numCapacity != 0);
      return  numPop       % numCapacity;
   }*/
   
   bool inline isFull() const
   {
	  //return (iTail() + 1) % numCapacity == iHead();
	  return size() >= capacity();
   }
   
   // member variables
   T * data;             // dynamically allocated data for the queue
   int numCapacity;      // the size of the data array
   int numPush;          // number of items ever pushed to the queue
   int numPop;           // number of items ever popped from the queue
};
#ifdef DEBUG
using std::cerr;
using std::endl;
/*******************************************************
 * debug display
 *******************************************************/
template <class T>
void queue <T> :: display() const
{
   cerr << "data = ";
   for (int i = 0; i < numCapacity; i++)
   {
      if (iHead() > iTail() && (i <= iTail() || i >= iHead()))
         cerr << data[i] <<  ' ';
      else if (iHead() <= iTail() && i >= iHead() && i <= iTail())
         cerr << data[i] << ' ';
      else
         cerr << "? ";
   }
   cerr << endl;
   cerr << "\tnumPush     " << numPush     << endl;
   cerr << "\tnumPop      " << numPop      << endl;
   cerr << "\tnumCapacity " << numCapacity << endl;
   if (numCapacity)
   {
      cerr << "\tiHead()     " << iHead()  << endl;
      cerr << "\tiTail()     " << iTail()  << endl;
   }
}

#else
template <class T>
void queue <T> :: display() const
{
}
#endif // DEBUG
/********************************************************
 * QUEUE :: assignment operator
 *******************************************************/
template <class T>
queue <T> & queue <T> :: operator = (const queue <T> & rhs) throw(const char *)
{
   clear();
	
   // do nothing if there is nothing to do
   if (rhs.empty())
   {
	   data = NULL;
	   numCapacity = 0;
	   numPush = 0;
	   numPop = 0;
	   return *this;
   }
   else
   {
	   if (numCapacity < rhs.size())
	   {
		  //std::cerr << "resize called from assignment operator\n";
	      resize(rhs.size());
	   }
	   
	   //copy elements rhs elements into this
	   for (int i = rhs.numPop; i < rhs.numPush; i++)
	   {
		   push(rhs.data[i % rhs.numCapacity]);
	   }
	   
	   
	 /*  
     for (int i = rhs.iHead(); i != rhs.iTail(); i++)
     {
      if (rhs.iHead() > rhs.iTail() && (i <= rhs.iTail() || i >= rhs.iHead())) // if it wraps
         push(rhs.data[i]); // this line needs to be modified
      else if (rhs.iHead() <= rhs.iTail() && i >= rhs.iHead() && i <= rhs.iTail()) // if it doesn't
         { push(rhs.data[i]);}
     }
	 */
   }
  
   //paranoia 
   assert(rhs.numCapacity > 0);
   assert(rhs.numPush > 0 && rhs.numPop >= 0);
   assert(numPush <= numCapacity);
   
   return *this;
}
/**********************************************************
 * QUEUE :: non-default constructor
 *********************************************************/
template <class T>
queue <T> :: queue(int newCapacity) throw(const char *) :
     numPush(0), numPop(0), numCapacity(0), data(NULL)
{
   if (newCapacity > numCapacity)
   {
	   //std::cerr << "resize called from non-default constructor\n";
	   resize(newCapacity);
   }
}
/**********************************************************
 * QUEUE :: copy constructor
 *********************************************************/
template <class T>
queue <T> :: queue(const queue <T> & rhs) throw(const char *) :
     numPush(0), numPop(0), numCapacity(0), data(NULL)
{
   *this = rhs;
	/*
   clear();
	
   // do nothing if there is nothing to do
   if (!rhs.empty())
   {
	   if (numCapacity < rhs.size())
	   {
		  //std::cerr << "resize called from assignment operator\n";
	      resize(rhs.size());
	   }
	   
	   //copy elements rhs elements into this
	   /*for (int i = rhs.numPop; i < rhs.numPush; i++)
	   {
		   push(rhs.data[i % rhs.numCapacity]);
	   }
     for (int i = rhs.iHead(); i != rhs.iTail(); i++)
     {
      if (rhs.iHead() > rhs.iTail() && (i <= rhs.iTail() || i >= rhs.iHead())) // if it wraps
         push(rhs.data[i]); // this line needs to be modified
      else if (rhs.iHead() <= rhs.iTail() && i >= rhs.iHead() && i <= rhs.iTail()) // if it doesn't
         { push(rhs.data[i]); std::cerr << "push called from assignment operator\n"; }
     }
   }
  */
}
/*********************************************************
 * QUEUE :: PUSH
 * Add an item to the queue
 ********************************************************/
template <class T>
void queue <T> :: push(const T & t) throw (const char *)
{
	// set the new capacity, numPush, and numPop
   /*
   numCapacity = newCapacity;
   numPush = newNumPush;
	*/
	
   // grow if the queue is not currently large enough
   if (size() == capacity())
   {
	  //std::cerr << "resize called from push\n";
      resize(capacity() * 2);
   }
   
   //add new element to the tail position
   numPush++;
   data[iTail()] = t;
   
   //debug
   /*
   std::cerr << "numCapacity = " << numCapacity << std::endl;
   std::cerr << "size() = " << size() << std::endl;
   std::cerr << "iTail() = " << iTail() << std::endl;
   std::cerr << "input = " << t << std::endl;
   */
}
/*********************************************************
 * QUEUE :: POP
 * Remove an item from the end of the queue
 ********************************************************/
template <class T>
void queue <T> :: pop() 
{
   if (size() > 0)
      numPop++;
}
/********************************************************
 * QUEUE :: FRONT
 * return a reference to the next element in the front of the queue
 ********************************************************/
template <class T>
T & queue <T> :: front() throw (const char *)
{
   // determine if the queue is empty
   if (empty())
      throw "ERROR: attempting to access an element in an empty queue";
   // otherwise, return the answer
   return data[iHead()];
}
/********************************************************
 * QUEUE :: BACK
 * return a reference to the last element in the back of the queue
 ********************************************************/
template <class T>
T & queue <T> :: back() throw (const char *)
{
   // determine if the queue is empty
   if (empty())
      throw "ERROR: attempting to access an element in an empty queue";
   // otherwise, return the answer
   return data[iTail()];
}
/*********************************************************
 * QUEUE :: RESIZE
 * Grow the size of the queue to a given size.
 * If the capacity is not zero, then the capacity will
 * be doubled, otherwise it will be one.  If the stack is 
 * currently not empty, the contents
 * will be copied over to the new buffer
 *********************************************************/
template <class T>
void queue <T> :: resize(int newCapacity) throw(const char *)
{
   assert(newCapacity >= 0);
   
   //handles zero newCapacity case 
   newCapacity = (newCapacity > 0) ? (numCapacity * 2):1;
   
   // attempt to allocate the new buffer
   T * newData;
   try {
	   newData = new T[newCapacity];
   }
   catch (std::bad_alloc)
   {
	   throw "ERROR: Unable to allocate a new buffer for queue";
   }
      
	  
   //copy elements rhs elements into this
   /*for (int i = numPop; i < numPush; i++)
   {
	   push(data[i % numCapacity]);
   }*/
   int newNumPush = 0;
   while (!empty())
   {
     newData[newNumPush] = front();
     pop();
     newNumPush++;
   }
   
   data = newData;
   
   // set the new capacity, numPush, and numPop
   numCapacity = newCapacity;
   numPush = newNumPush;
   numPop = 0;
   //std::cerr << "data resized to " << numCapacity << " capacity\n";
}

}
#endif // QUEUE_H
