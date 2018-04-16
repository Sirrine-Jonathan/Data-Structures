/***********************************************************************
 * Header:
 *    WHOLE_NUMBER
 * Summary:
 *    This will contain the class definition of:
 *        WholeNumber  : A class containing the notion of a large positve #
 * Author
 *    Br. Helfrich
 ************************************************************************/
#ifndef WHOLE_NUMBER_H
#define WHOLE_NUMBER_h
//#include <list>
#include "list.h"      // for LIST
#include <iostream>    // for ISTREAM and OSTREAM

template <class T>
class list;
// using custom::list;
/************************************************
 * WHOLE NUMBER
 * A class to represent an arbitrary large whole
 * number.  Currently supports:
 *     INSERTION : for displaying the number w/o thousands separator
 *     +=        : add one WholeNumber onto this
 *     = (int)   : assign an integer to the current value
 *     =         : assign one WholeNumber onto this
 ***********************************************/
//template <class T>
class WholeNumber
{
public:
   // constructors. We will use the default destructor
   WholeNumber()                        { }//data->push_back(0); }
   WholeNumber(unsigned int value)      { *this = value;     }
   WholeNumber(const WholeNumber & rhs) { *this = rhs;  }
   
   // display the number
   friend std::ostream & operator << (std::ostream & out,
                                      const WholeNumber & rhs);
   // fetch a given number
   friend std::istream & operator >> (std::istream & in, WholeNumber & rhs);
   
   // add onto a given whole number
   WholeNumber & operator += (const WholeNumber & rhs);
   // assignment operator for numbers
   WholeNumber & operator = (unsigned int value);
   // assignment operator for values
   WholeNumber & operator = (const WholeNumber & rhs)
   {
      data = rhs.data;
      return *this;
   }
   WholeNumber & operator - (const WholeNumber & rhs)
   {

   }
   WholeNumber & operator + (const WholeNumber & rhs)
   {
      
   }
private:
   list<int> * data;
};
#endif // WHOLE_NUMBER_H