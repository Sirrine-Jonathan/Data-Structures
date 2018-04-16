/***********************************************************************
 * Header:
 *    Vector
 * Summary:
 *    This class contains the notion of a vector: a bucket to hold
 *    data for the user that expands as needed. 
 *
 *    This will contain the class definition of:
 *       vector             : similar to std::vector
 *       vector :: iterator : an iterator through the vector
 * Author
 *    Br. Helfrich and Spencer Eccles
 ************************************************************************/

#ifndef VECTOR_H
#define VECTOR_H

#include <cassert>  // because I am paranoid

/*/ a little helper macro to write debug code
#ifdef NDEBUG
#define Debug(statement)
#else
#define Debug(statement) statement
#endif // !NDEBUG
*/

namespace custom
{
/************************************************
 * Vector
 * A class that holds stuff and expands as needed
 ***********************************************/
template <class T>
class vector
{
public:
   // constructors and destructors
   vector()                  throw (const char *);
   vector(int num)                  throw (const char *);
   vector(const vector & rhs)        throw (const char *);
  ~vector()                         { delete [] data;   }
   vector & operator = (const vector & rhs) throw (const char *);
   
   // standard container interfaces
   int  size()     const { return numElements; }
   int  capacity() const { return numCapacity; }
   bool empty() { if (numElements == 0) return true; else return false; }
   void push_back(T t);
   void clear() { numElements = 0; }
   // vector-specific interfaces
   // what would happen if I passed -1 or something greater than num?
   T & operator [] (int index)       throw (const char *)
   {
      return data[index];
   }
   const T & operator [] (int index) const throw (const char *)
   {
      return data[index];
   }
   
   // the various iterator interfaces
   class iterator;
   iterator begin()      { return iterator (data); }
   iterator end();

   // a debug utility to display the vector
   // this gets compiled to nothing if NDEBUG is defined
   void display() const; 
   
private:
   T * data;              // dynamically allocated vector of T
   int numCapacity;
   int numElements;
   void resize(int &numCapacity);
};

/**************************************************
 * VECTOR ITERATOR
 * An iterator through vector
 *************************************************/
template <class T>
class vector <T> :: iterator
{
public:
   // constructors, destructors, and assignment operator
   iterator()      : p(NULL)      {              }
   iterator(T * p) : p(p)         {              }
   iterator(const iterator & rhs) { *this = rhs; }
   iterator & operator = (const iterator & rhs)
   {
      this->p = rhs.p;
      return *this;
   }

   // equals, not equals operator
   bool operator != (const iterator & rhs) const { return rhs.p != this->p; }
   bool operator == (const iterator & rhs) const { return rhs.p == this->p; }

   // dereference operator
         T & operator * ()       { return *p; }
   const T & operator * () const { return *p; }

   // prefix increment
   iterator & operator ++ ()
   {
      p++;
      return *this;
   }

   // postfix increment
   iterator operator ++ (int postfix)
   {
      iterator tmp(*this);
      p++;
      return tmp;
   }
   
private:
   T * p;
};

/********************************************
 * VECTOR :: END
 * Note that you have to use "typename" before
 * the return value type
 ********************************************/
template <class T>
typename vector <T> :: iterator vector <T> :: end ()
{
   return iterator (data + numElements);
}

/*******************************************
 * VECTOR :: Assignment
 *******************************************/
template <class T>
vector <T> & vector <T> :: operator = (const vector <T> & rhs)
          throw (const char *)
{
   if (rhs.size() > size())
   {
      data = new T[rhs.numElements];
      numCapacity = rhs.numElements;
      numElements = rhs.numElements;
   }

   assert(numElements == rhs.numElements);
   for (int i = 0; i < numElements; i++)
      data[i] = rhs.data[i];

   return *this;
}

/*******************************************
 * VECTOR :: COPY CONSTRUCTOR
 *******************************************/
template <class T>
vector <T> :: vector(const vector <T> & rhs) throw (const char *)
{
   assert(rhs.numElements >= 0);
      
   // do nothing if there is nothing to do
   if (rhs.numElements == 0)
   {
      numElements = 0;
      numCapacity = 0;
      data = NULL;
      return;
   }

   // attempt to allocate
   try
   {
      data = new T[rhs.numElements];
      numElements = rhs.numElements;
   }
   catch (std::bad_alloc)
   {
      throw "ERROR: Unable to allocate buffer";
   }
   
   // copy over the capacity
   numCapacity = rhs.numElements;

   // copy the items over one at a time using the assignment operator
   for (int i = 0; i < numElements; i++)
      data[i] = rhs.data[i];
}

/**********************************************
 * VECTOR : NON-DEFAULT CONSTRUCTOR
 * Preallocate the vector to "capacity"
 **********************************************/
template <class T>
vector <T> :: vector(int num) throw (const char *)
{
   assert(numElements >= 0);
   
   // do nothing if there is nothing to do.
   if (num == 0)
   {
      numElements = 0;
      numCapacity = 0;
      this->data = NULL;
      return;
   }

   // attempt to allocate
   try
   {
      data = new T[num];
      numElements = num;
   }
   catch (std::bad_alloc)
   {
      throw "ERROR: Unable to allocate buffer";
   }
      
   // copy over the stuff
   numCapacity = num;
}

/**********************************************
 * VECTOR : DEFAULT CONSTRUCTOR
 * Preallocate the vector to 0 capacity
 **********************************************/
template <class T>
vector <T> :: vector() throw (const char *)
{
   this->data = NULL;
   numCapacity = 0;
   numElements = 0;
}

/**********************************************
 * VECTOR : PUSH BACK
 * Adds an element to the vector
 **********************************************/
template <class T>
void vector <T> :: push_back(T t) 
{
   numElements++;
   if (numElements > numCapacity)
      resize(numCapacity);
   data[numElements - 1] = t;
}

/**********************************************
 * VECTOR : RESIZE
 * Resizes the vector
 **********************************************/
template <class T>
void vector <T> :: resize(int &numCapacity) 
{
   if (numElements == 1)
   {
      data = new T[1];
      numCapacity = 1;
   }
   else
   {
      numCapacity *= 2;
      T *pData = new T[numCapacity];
      for (int i = 0; i < numElements - 1; i++)
         pData[i] = data[i];
      data = pData;
   }
}

/********************************************
 * VECTOR : DISPLAY
 * A debug utility to display the contents of the vector
 *******************************************/
template <class T>
void vector <T> :: display() const
{
#ifndef NDEBUG
   std::cerr << "vector<T>::display()\n";
   std::cerr << "\tnumElements = " << numElements << "\n";
   std::cerr << "\tnumCapacity = " << numCapacity << "\n";
   for (int i = 0; i < numElements; i++)
      std::cerr << "\tdata[" << i << "] = " << data[i] << "\n";
#endif // NDEBUG
}

}; // namespace custom

#endif // VECTOR_H
