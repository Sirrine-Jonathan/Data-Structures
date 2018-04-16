/***********************************************************************
 * Header:
 *    set
 * Summary:
 *    set class similar to std::set but including more union type
 *    functions.
 *
 *    This will contain the class definition of:
 *       set             : similar to std::set
 *       set :: iterator : an iterator through the set
 * Author
*    Spencer Eccles
*    Jonathan Sirrine
*    Atsushi Jindo
*    Eric Brich
 ************************************************************************/
#ifndef SET_H
#define SET_H

#ifdef DEBUG
#define Debug(x) x
#else
#define Debug(x)
#endif

#include <cassert>
#include <iostream>
namespace custom
{

template <class T>
class set
{
  public:
   set() : data(NULL), numCapacity(0), numElements(0) { clear(); }
   set(int numCapacity)                       throw (const char *);
   set(const set <T> & rhs)                   throw (const char *);
   ~set()                       { if (!empty()) delete [] data;                    }
   set<T> & operator = (const set <T> & rhs)  throw (const char *);
   set<T> operator && (const set <T> & rhs);
   set<T> operator || (const set <T> & rhs);
   set<T> operator - (const set <T> & rhs);

   // bracket [] operator
   T & operator[](int index) throw(const char*);
   const T & operator[](int index) const throw(const char*);
      
   int    size()          const { return numElements;                              }
   int    capacity()      const { return numCapacity;                              }
   bool   empty()               { if (size() == 0) return true; else return false; }
   void   clear()               { numElements = 0;                                 }
   bool   insert(T t);

   class    iterator;
   iterator begin() { return iterator (data); }
   iterator end();
   iterator find(T & t);

   class const_iterator;
   const_iterator cbegin() const { return const_iterator (data); }
   const_iterator cend() const;
   const_iterator find(const T & t) const;

   bool erase(iterator & it);

 private:
   int findIndex (const T & t) const;
   void resize(int newCapacity) throw (const char *);

   int numElements;
   int numCapacity;
   T * data;

};

/********************************************
 * SET :: NON-DEFAULT CONSTRUCTOR
 *******************************************/
template <class T>
set <T> :: set (int numCapacity) throw (const char *) :
data(NULL), numCapacity(0)
{
   clear(); //sets numElements = 0;
   if (numCapacity > 0)
      resize(numCapacity);
}

/********************************************
 * SET :: COPY CONSTRUCTOR
 *******************************************/
template <class T>
set <T> :: set (const set <T> & rhs) throw (const char *) :
data(NULL), numCapacity(0)
{
   clear();
   *this = rhs;
}

/********************************************
 * SET :: ASSIGNMENT OPERATOR
 *******************************************/
template <class T>
set <T> & set <T> :: operator = (const set <T> & rhs) throw (const char *)
{
   if (&rhs == this)
      return *this;

   clear();
   if (rhs.size() == 0)
      return *this;

   if (rhs.size() >= capacity())
      resize(rhs.size());

   //copy data over
   for (int i = 0; i < rhs.size(); i++)
      data[i] = rhs.data[i];
   numElements = rhs.numElements;   

};

/********************************************
 * SET :: INTERSECTION OPERATOR
 *******************************************/
template <class T>
set <T> set <T> :: operator && (const set <T> & rhs)
{
   set <T> setReturn;
   int iLHS = 0;
   int iRHS = 0;
   while (iLHS < numElements || iRHS < rhs.numElements)
      if (iLHS == numElements)
         return setReturn;
      else if (iRHS == rhs.numElements)
         return setReturn;
      else if (data[iLHS] == rhs.data[iRHS])
      {
         setReturn.insert(data[iLHS]);
         iLHS++;
         iRHS++;
      }
      else if (data[iLHS] < rhs.data[iRHS])
         iLHS++;
      else 
         iRHS++;
   return setReturn;
};

/********************************************
 * SET :: UNION OPERATOR
 *******************************************/
template <class T>
set <T> set <T> :: operator || (const set <T> & rhs)
{
   set <T> setReturn;
   int iLHS = 0;
   int iRHS = 0;
   while (iLHS < numElements || iRHS < rhs.numElements)
      if (iLHS == numElements)
         setReturn.insert(rhs.data[iRHS++]);
      else if (iRHS == rhs.numElements)
         setReturn.insert(data[iLHS++]);
      else if (data[iLHS] == rhs.data[iRHS])
      {
         setReturn.insert(data[iLHS]);
         iLHS++;
         iRHS++;
      }
      else if (data[iLHS] < rhs.data[iRHS])
         setReturn.insert(data[iLHS++]);
      else 
         setReturn.insert(rhs.data[iRHS++]);
   return setReturn;
};

/********************************************
 * SET :: DIFFERENCE OPERATOR
 *******************************************/
template <class T>
set <T> set <T> :: operator - (const set <T> & rhs)
{
   /*
   set <T> setReturn;
   int iLHS = 0;
   int iRHS = 0;
   while (iLHS < numElements || iRHS < rhs.numElements)
      if (iLHS == numElements)
         iLHS--;
      else if (iRHS == rhs.numElements)
         while (iLHS < numElements)
            setReturn.insert(data[iLHS++]);
      else if (data[iLHS] == rhs.data[iRHS])
      {
         iLHS++;
         iRHS++;
      }
      else if (data[iLHS] < rhs.data[iRHS])
         setReturn.insert(data[iLHS++]);
      else 
         iRHS++;
   */

   set <T> setReturn(*this);
   set <T> :: iterator itEmpty = end();
   for(int i = 0; i < rhs.size(); i++)
   {
      T copyElement(rhs[i]);
      set <T> :: iterator itFind = find(copyElement);
      if (itFind != itEmpty)
         setReturn.erase(itFind);
   }

   return setReturn;
};

/********************************************
 * SET :: INSERT
 *******************************************/
template <class T>
bool set <T> :: insert (T t) 
{
   int iInsert = findIndex (t);     
   if (iInsert != size())             //t already in array
      return false;
   else if (size() == capacity())     //t not in array and no room
      resize(capacity() * 2);

   // now there is room and a need to insert t

  

   //if this is the first element just add it. 
   if (size() == 0)
   {
      data[0] = t;
      numElements++;
      return true;
   }

   //THIS LOOP puts t in its correct place
   int iEnd = size() - 1;
   bool keepLooping = true;   //there is probably a more natural exit
   int count = 0;
   while (keepLooping)
   {
      if (iEnd == 0)
      {
         if (t > data[iEnd])
         {
            for(int i = 0; i < count; i++)
               data[size() - i] = data[size() - i - 1];
            data[iEnd + 1] = t;
            keepLooping = false;
         }
         else
         {
            for(int i = 0; i < count; i++)
               data[size() - i] = data[size() - i - 1];
            data[1] = data[0];
            data[0] = t;
            keepLooping = false;
         }
      }
      else if (t > data[iEnd])
      {
         for(int i = 0; i < count; i++)
            data[size() - i] = data[size() - i - 1];
         data[iEnd + 1] = t;
         keepLooping = false;
      }
      else
      {
      count++;
      iEnd--;
      }
   }
   numElements ++;
}

/**************************************************
 * SET ITERATOR
 * An iterator through set
 *************************************************/
template <class T>
class set <T> :: iterator
{
  public:
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
 * SET ITERATOR END
 * Note that you have to use "typename" before
 * the return value type
 *************************************************/
template <class T>
typename set <T> :: iterator set <T> :: end ()
{
   return iterator (data + numElements);
}

/**************************************************
 * SET FIND
 *************************************************/
template <class T>
typename set <T> :: iterator set <T> :: find (T & t)
{
   int index = findIndex(t);
   if (index == size())
      return end();
   iterator tPtr = &data[index];
   return tPtr;
}

/**************************************************
 * SET FIND CONST
 *************************************************/
template <class T>
typename set <T> :: const_iterator set <T> :: find (const T & t) const
{
   int index = findIndex(t);
   if (index == size())
      return cend();
   const_iterator tPtr = &data[index];
   return tPtr;
}

/**************************************************
 * SET ERASE
 *************************************************/
template <class T>
bool set <T> :: erase (iterator & it)
{
   /* PSEUDOCODE FROM BOOK */
   int iErase = findIndex(*it);
   if (iErase == size())             //t not in array
      return false;
   if (data[iErase] == (*it))
   {
      for (int i = iErase; i < size() - 1; i++)
         data[i] = data[i + 1];    //shift everything to left   
      numElements--;
   }
   return true;
}

/**************************************************
 * SET CONST_ITERATOR
 *************************************************/
template <class T>
class set <T> :: const_iterator
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
 * SET :: CEND
 * Note that you have to use "typename" before
 * the return value type
 ********************************************/
template <class T>
typename set <T> :: const_iterator set <T> :: cend () const
{
   return const_iterator (data + numElements);
};


/********************************************
 * SET :: FINDINDEX
 *******************************************/
template <class T>
int set <T> :: findIndex (const T & t) const
{
   /* BINARY SEARCH ALGORITHM FROM BOOK */
   int iBegin = 0;
   int iEnd = size() - 1;

   while (iBegin <= iEnd)
   {
      int iMiddle = (iBegin + iEnd) / 2;
      if (t == data[iMiddle])
         return iMiddle;
      if (t < data[iMiddle])
         iEnd = iMiddle - 1;
      else
         iBegin = iMiddle + 1;
   }

   return size();
}

/********************************************
 * SET :: RESIZE
 *******************************************/
template <class T>
void set <T> :: resize (int newCapacity) throw (const char *)
{
   //handle zero case
   if (newCapacity <= 0 || newCapacity < capacity())
      newCapacity = (numCapacity ? numCapacity * 2 : 1);

   //resize
   T * newData = new(std::nothrow) T[newCapacity];
   if (NULL == newData)
      throw "ERROR: Unable to allocate a new buffer for set";
   numCapacity = newCapacity;

   //copy over data
   for (int i = 0; i < size(); i++)
      newData[i] = data[i];

   //delete old data
   if (NULL != data)
      delete [] data;

   //set data to new data
   data = newData;
}
/*******************************************
 * Set :: [] Operator
 *******************************************/
template <class T>
T & set<T> :: operator[](int index) throw(const char *)
{
   if (index < 0 || index > numElements)
   {
      throw "ERROR: index out of bounds";
   }
   
   return data[index];
}
template <class T>
const T & set<T> :: operator[](int index) const throw(const char *)
{
   if (index < 0 || index > numElements)
   {
      throw "ERROR: index out of bounds";
   }
   return data[index];
}

} //end custom namespace
#endif //SET_H