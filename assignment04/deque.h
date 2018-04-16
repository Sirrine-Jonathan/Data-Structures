/***********************************************************************
* Header:
*    deque
* Summary:
*    An std::queue class made by hand
*
*    This will contain the class definition of:
*        deque         : A class that is basically std::deque
*        nowServing    : A class that helps with serving people
*  Author
*    Spencer Eccles
*    Jonathan Sirrine
*    Atsushi Jindo
*    Eric Brich
************************************************************************/
#ifndef deque_H
#define deque_H

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
class deque
{
  public:

   // constructors and destructors
   deque() : data(NULL), max(0), iFront(0), iBack(-1), numItems(0) 
   {
    resize(max);
   }
   deque(int max) throw (const char *);
   deque(const deque <T> & rhs) throw (const char *);
   ~deque() { if (!empty()) delete [] data; }
   deque<T> & operator = (const deque <T> & rhs);

   // standard container interfaces
   bool empty() const { return numItems == 0; }
   //int size() const { return iBack - iFront + 1; }
   int size() const   { return numItems;           }
   int capacity() const { return max; }
   //void clear() { iFront = 0; iBack = -1; }
   void clear() { while (!empty()) pop_front(); }

   // deque-specific interfaces
   void push_back( const T & t) throw (const char *);
   void push_front(const T & t) throw (const char *);
   void pop_back() throw (const char *);
   void pop_front() throw (const char *);
   T & front() throw (const char *);
   T & back() throw (const char *);
   T front() const throw (const char *);
   T back() const throw (const char *);

   //debug functions
   int getIFront() { return iFront; }
   int getIBack() { return iBack; }

  private:
   // utility functions
   int iNormalize(int i) const
   {
    return (i >= 0) ? (i % max) : (max - ((-1 - i) % max) - 1);
   }
   int iBackNormalize() const { return iNormalize(iBack); }
   int iFrontNormalize() const { return iNormalize(iFront); }
   void resize(int newMax) throw (const char *);
   void copy(const deque<T> & rhs); // helps assist the copy constructor
   
   // member variables
   T * data;     // dynamically allocated data for the deque
   int max;      // the capacity of the data array
   int iFront;   // the index of the first item in the array
   int iBack;    // the index of the last item in the array
   int numItems; // how many items are currently in the container?
};


/******************************************************
* deque : Non-Default constructor
* Preallocate the container to "capacity"
******************************************************/
template <class T>
deque <T> :: deque(int max) throw (const char *)
{
    assert (max >= 0);

    // do nothing if there's nothing to do
    if (max == 0)
    {
      this->max = this->numItems = 0;
      this->data = NULL;
      this->iFront = 0;
      this->iBack = -1;
      return;
    }
 
    try
    {
       data = new T[max];
    }
    catch (std::bad_alloc)
    { 
        throw "ERROR: Unable to allocate buffer";
    }

    this->max = max;
    this->iFront = 0;
    this->iBack = -1;
    this->numItems = 0;
}

/******************************************************
* deque : Copy constructor
* Preallocate the container to "capacity"
******************************************************/
template <class T>
deque <T> :: deque(const deque <T> & rhs) throw (const char *)
{
    //*this = rhs;
  assert(rhs.max >= 0);
       
   // do nothing if there is nothing to do
   if (rhs.max == 0)
   {
      max = numItems = 0;
      data = NULL;
      iFront = iBack = 0;
      return;
   }
 
   // attempt to allocate
   try
   {
      data = new T[rhs.max];
   }
   catch (std::bad_alloc)
   {
      throw "ERROR: Unable to allocate buffer";
   }
    
   // copy over the capacity and size
   assert(rhs.numItems >= 0 && rhs.numItems <= rhs.max);
   max = rhs.max;
   numItems = rhs.numItems;
   iFront = rhs.iFront;
   iBack = rhs.iBack;
 
   // copy items over one at a time
   for (int i = 0; i < max; i++)
      data[i] = rhs.data[i];
}

/******************************************************
* deque : Assignment Operator
******************************************************/
template <class T>
deque<T> & deque<T>:: operator = (const deque <T> & rhs)
{
   /* Old code
   Debug(std::cerr << "start of assign\n";);
   if (rhs.max == 0 || rhs.size() == 0)
   {
      Debug(std::cerr << "max = 0\n";);
      max = 0;
      data = NULL;
      clear();
      return *this;
   }
   
   if(max < rhs.size())
   {
        
        Debug(std::cerr << "max < rhs.size()\n";);
        Debug(std::cerr << "So reallocate...\n";);
       
        try
        {
            data = new T[rhs.size()];
        }
        catch (std::bad_alloc)
        { 
            throw "ERROR: Unable to allocate buffer";
        }

        //resize(rhs.size());
        max = rhs.max;
   }

   Debug(std::cerr << "max >= rhs.size() \n";);
   max = rhs.max;
   clear();

   // copy items over one at a time
   Debug(std::cerr << "Just before assign loop\n";);
   Debug(std::cerr << "bfl\trhs.front = " << rhs.iFront << "\n";);
   Debug(std::cerr << "bfl\trhs.back = " << rhs.iBack << "\n";);
   for (int i = rhs.iFront; i <= rhs.iBack; i++)
   {

       //debug block
       Debug(std::cerr << "Loop #" << i << std::endl;);
       Debug(std::cerr << "fl\ti = " << i << "\n";);
       Debug(std::cerr << "fl\trhs.iNormalize(i) = " << rhs.iNormalize(i) << "\n";);
       Debug(std::cerr << "fl\trhs.data[iNormalize(i)] = " << rhs.data[iNormalize(i)] << "\n";);

       Debug(std::cerr << "about to push\n";);
       push_back(rhs.data[iNormalize(i)]);
       Debug(std::cerr << "end loop #" << i << std::endl;);
   }
   Debug(std::cerr << "end of assign\n\n");
   return *this;
   
   
   clear();
   if (capacity() < rhs.size())
      resize(rhs.size());
   for (int i = rhs.iFront; i <= rhs.iBack; i++)
      push_back(rhs.data[iNormalize(i)]);
   *this;
   */

  // New Assignment operator
  clear();
  if (max < rhs.max)
  {
    resize(rhs.max);
  }
  // call copy function to help copy things over
  copy(rhs);

  return *this;
}

/******************************************************
* deque : Push Back
******************************************************/
template <class T>
void deque <T> :: push_back(const T & t) throw (const char *)
{
  /* Old Code
  if (capacity() == 0)
    resize(1);
  else if (capacity() == size())
    resize(capacity() * 2);
  iBack++; */
  
  //debug block
  /*
  Debug(std::cerr << "pbm\tt = " << t << std::endl;);
  Debug(std::cerr << "pbm\tmax = " << max << std::endl;);
  Debug(std::cerr << "pbm\tiFront = " << iFront << std::endl;);
  Debug(std::cerr << "pbm\tiback = " << iBack << std::endl;);
  Debug(std::cerr << "pbm\tsize() = " << size() << std::endl;);
  Debug(std::cerr << "pbm\tempty() = " << empty() << std::endl;);
  Debug(std::cerr << "pbm\tiBackNormalize() = " << iBackNormalize() << std::endl);

  data[iBackNormalize()] = t;
  Debug(std::cerr << "pbm\tAssignment Successful: data[iBackNormalize()] = t\n\n";);*/

  // temp back variable to help with function
  int newBack;

  if (max == 0)
  {
    max = 2;
    resize(max);
    newBack = iNormalize(iBack + 1);
  }
  else if (numItems >= max)
  {
    int newMax = max;
    newMax *= 2;

    // create temp object for help with copying the array
    T * temp;

    // attempt to push
    try
    {
      temp = new T[newMax];
    }
    catch (std::bad_alloc)
    {
      throw "ERROR: unable to push the deque!";
    }

    // copy over from temp array
    for (int i = 0; i < max; i++)
    {
      temp[i] = data[iNormalize(iFront + i)];
    }

    // delete to prevent memory leaks
    delete [] data;

    // copy variables over
    data = temp;
    iFront = 0;
        
    newBack = max;
    max = newMax;
  }
  else
  {
    newBack = iNormalize(iBack + 1);
  }

  iBack = newBack;
  data[iBack] = t;
  numItems++;
}

/******************************************************
* deque : Push Front
******************************************************/
template <class T>
void deque <T> :: push_front(const T & t) throw (const char *)
{
  // temp front variable to help with function
  int newFront;

  if (max == 0)
  {
    max = 2;
    resize(max);
    newFront = iNormalize(iFront - 1);
  }
  else if (numItems >= max)
  {
    int newMax = max;
    newMax *= 2;
    T * temp;

    // attempt to push
    try
    {
      temp = new T[newMax];
    }
    catch(std::bad_alloc)
    {
      throw "ERROR: unable to push the deque!";
    }

    // copy over from temp array
    for (int i = 0; i < max; i++)
    {
      temp[i] = data[iNormalize(iFront + i)];
    }

    delete [] data;
    data = temp;
    iBack = (max - 1);
    max = newMax;
    iFront = 0;
    newFront = iNormalize(iFront - 1);
  }
  else
  {
    newFront = iNormalize(iFront - 1);
  }
  if (numItems == 0)
  {
    iFront = 0;
    iBack = 0;
  }

  iFront = newFront;
  data[iFront] = t;
  numItems++;
}

/******************************************************
* deque : Pop Back
******************************************************/
template <class T>
void deque <T> :: pop_back() throw (const char *)
{
  if (empty())
  {
    // do nothing, since test 4 doesn't want anything here
  }
  else
  {
    iBack--;
    numItems--;
  }
}

/******************************************************
* deque : Pop Front
******************************************************/
template <class T>
void deque <T> :: pop_front() throw (const char *)
{
  if (empty())
  {
    // do nothing, since test 4 doesn't want anything here
  }
  else
  {
    iFront++;
    numItems--;
  }
}
/******************************************************
* deque : Front Setter
******************************************************/
template <class T>
T & deque <T> :: front() throw (const char *)
{
  if (empty())
    throw "ERROR: unable to access data from an empty deque";
  else 
    return data[iFrontNormalize()];
}

/******************************************************
* deque : Back Setter
******************************************************/
template <class T>
T & deque <T> :: back() throw (const char *)
{
  if (empty())
    throw "ERROR: unable to access data from an empty deque";
  else
    return data[iBackNormalize()];
}

/******************************************************
* deque : Front Getter
******************************************************/
template <class T>
T deque <T> :: front() const throw (const char *)
{
  if (empty())
    throw "ERROR: attempting to access data from an empty deque";
  else
    return data[iFrontNormalize()];
}

/******************************************************
* deque : Back Getter
******************************************************/
template <class T>
T deque <T> :: back() const throw (const char *)
{
  if (empty())
    throw "ERROR: attempting to access data from an empty deque";
  else
    return data[iBackNormalize()];
}

/******************************************************
* deque : Resize
* runs traditional allocate function
******************************************************/
template <class T>
void deque <T> :: resize(int newMax) throw (const char *)
{
  /* Old Code
  if (newMax == 0)
  {
     max = 0;
     data = NULL;
     clear();
  }
  else
  {
     T * newData;
     try
     {
        
        Debug(std::cerr << "rs\tresizing to " << newMax << std::endl);
        newData = new T[newMax];
     }
     catch (std::bad_alloc)
     { 
        throw "ERROR: Unable to allocate buffer";
     }
     int newIBack = -1;
     while (!empty())
     {
        newIBack++;
        newData[newIBack] = front();
        pop_front();
     }
     delete [] data;
     data = newData;
     iFront = 0;
     iBack = newIBack;
     max = newMax;
   */
  try
     { 
       delete [] data;
       data = new T[newMax];
     }
     catch (std::bad_alloc)
     {
       throw "ERROR: Unable to allocate a new buffer for the queue";
     }
}
/***************************************************
* private deque function :: copy
* helps with copy constructor
**************************************************/
template <class T>
void deque<T>  :: copy(const deque<T> & rhs)
{
      // copy the capacity and size
      assert(rhs.numItems >= 0 && rhs.numItems <= rhs.max);
      iFront = rhs.iFront;
      iBack = rhs.iBack;
      numItems = rhs.numItems;
      max = rhs.max;

      //copy the items
      for (int i = 0; i < max; i++)
      {
        data[i] = rhs.data[i];
      }
}

}
#endif // deque_H