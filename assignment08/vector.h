/***********************************************************************
 * Header:
 *    vector
 * Summary:
 *    This class contains the notion of an vector: a bucket to hold
 *    data for the user. This is just a starting-point for more advanced
 *    constainers such as the vector, set, stack, queue, deque, and map
 *    which we will build later this semester.
 *
 *    This will contain the class definition of:
 *       vector             : similar to std::vector
 *       vector :: iterator : an iterator through the vector
 * Author
 *    Jonathan Sirrine
 ************************************************************************/
#include <string>
#ifndef VECTOR_H
#define VECTOR_H

#include <cassert>  // because I am paranoid

// a little helper macro to write debug code
#ifdef NDEBUG
#define Debug(statement)
#else
#define Debug(statement) statement
#endif // !NDEBUG

namespace custom
{

/************************************************
 * VECTOR
 * A class that holds stuff
 ***********************************************/
template <class T>
class vector
{
public:
   // constructors and destructors
   vector() {
      numElements = 0;      
      numCapacity = 0;
	  data = NULL;
   }
   vector(int numElements)           throw (const char *);
   vector(int numElements, T t) {}
   vector(const vector & rhs)        throw (const char *);
  ~vector()                         { 
	  delete [] data; 
	  data = NULL;
   }
   vector & operator = (const vector & rhs) throw (const char *);
   
   // standard container interfaces
   // vector treats size and max_size the same
   int  size()     const { return numElements;                 }
   int  capacity() const { return numCapacity;                 }
   bool empty()    const { return (numElements == 0);          }
   void clear()          { numElements = 0;                    }
   void push_back(T t);
   
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
   iterator begin()        { return iterator (data); }
   iterator end();
   
   class const_iterator;
   const_iterator cbegin() const { return const_iterator (data); } 
   const_iterator cend() const;
   
   

   // a debug utility to display the vector
   // this gets compiled to nothing if NDEBUG is defined
   void display() const; 
   
private:
   T * data;              // dynamically allocated vector of T
   int numElements;       // both the capacity and the number of elements
   int numCapacity;
   
   //private method to allocate memory
   //during push_back, copy, or reassignment
   void resize(int numCapacity);
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
   
   // prefix decrement
   iterator & operator -- ()
   {
      p--;
      return *this;
   }

   // postfix decrement
   iterator operator -- (int postfix)
   {
      iterator tmp(*this);
      p--;
      return tmp;
   }  
   
private:
   T * p;
};

/**************************************************
 * VECTOR CONST_ITERATOR
 * An iterator through vector
 *************************************************/
template <class T>
class vector <T> :: const_iterator
{
public:
   // constructors, destructors, and assignment operator
   const_iterator()      : p(NULL)      {              }
   const_iterator(T * p) : p(p)         {              }
   const_iterator(const iterator & rhs) { *this = rhs; }
   const_iterator & operator = (const iterator & rhs)
   {
      this->p = rhs.p;
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
      p++;
      return *this;
   }

   // postfix increment
   const_iterator operator ++ (int postfix)
   {
      const_iterator tmp(*this);
      p++;
      return tmp;
   }
   
   // prefix decrement
   const_iterator & operator -- ()
   {
      p--;
      return *this;
   }

   // postfix decrement
   const_iterator operator -- (int postfix)
   {
      const_iterator tmp(*this);
      p--;
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

/********************************************
 * VECTOR :: CEND
 * Note that you have to use "typename" before
 * the return value type
 ********************************************/
template <class T>
typename vector <T> :: const_iterator vector <T> :: cend () const
{
   return const_iterator (data + numElements);
}

/*******************************************
 * VECTOR :: Assignment
 *******************************************/
template <class T>
vector <T> & vector <T> :: operator = (const vector <T> & rhs)
          throw (const char *)
{
   
   assert(rhs.numElements >= 0); 
   numElements = 0;
   
   if (rhs.size() > numCapacity)
	   resize(rhs.size());
   
   numElements = rhs.size();

   // copy the items over one at a time using the assignment operator
   for (int i = 0; i < numElements; i++)
      data[i] = rhs.data[i];  
  
   return *this;
}


/*******************************************
 * VECTOR :: PUSH_BACK
 *******************************************/
template <class T>
void vector <T> :: push_back(T t)
{

	if (size() == capacity() && capacity() != 0)
		resize(capacity() * 2);
	else if (size() == capacity())
		resize(capacity() + 1);

	data[numElements++] = t;

}

/*******************************************
 * VECTOR :: RESIZE
 *******************************************/
template <class T>
void vector <T> :: resize(int numCapacity)
{

   T * newData;

   // attempt to allocate
   try
   {
      newData = new T[numCapacity];
   }
   catch (std::bad_alloc)
   {
      throw "ERROR: Unable to allocate buffer";
   }
   
   // put data into newData
   for (int i = 0; i < numElements; i++)
	   newData[i] = data[i];
   
   // attempt to allocate
   try
   {
      data = new T[numCapacity];
   }
   catch (std::bad_alloc)
   {
      throw "ERROR: Unable to allocate buffer";
   }
   
   
   // put newData into data
   for (int i = 0; i < numElements; i++)
	   data[i] = newData[i];
   
   
   this->numCapacity = numCapacity;
   
}

/*******************************************
 * VECTOR :: COPY CONSTRUCTOR
 *******************************************/
template <class T>
vector <T> :: vector(const vector <T> & rhs) throw (const char *)
{
   assert(rhs.numElements >= 0); 
   numElements = 0;
   numCapacity = 0;
   
   if (rhs.size() > numCapacity)
	   resize(rhs.size());
   else 
	   numCapacity = rhs.size();
   numElements = rhs.size();

   // copy the items over one at a time using the assignment operator
   for (int i = 0; i < numElements; i++)
      data[i] = rhs.data[i];
  
   //display();
}

/**********************************************
 * VECTOR : NON-DEFAULT CONSTRUCTOR
 * Preallocate the vector to "capacity"
 **********************************************/
template <class T>
vector <T> :: vector(int numElements) throw (const char *)
{
   assert(numElements >= 0);
   
   // do nothing if there is nothing to do.
   if (numElements == 0)
   {
	  this->numCapacity = 0;
      this->numElements = 0;
      this->data = NULL;
      return;
   }

   // attempt to allocate
   try
   {
	  this->numCapacity = numElements;
	  this->numElements = numElements;
      data = new T[numElements];
   }
   catch (std::bad_alloc)
   {
      throw "ERROR: Unable to allocate buffer";
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
   std::cerr << "\tnum = " << numElements << "\n";
   for (int i = 0; i < numElements; i++)
      std::cerr << "\tdata[" << i << "] = " << data[i] << "\n";
#endif // NDEBUG
}

}; // namespace custom

#endif // VECTOR_H

