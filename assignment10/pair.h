/***********************************************************************
 * Module:
 *    PAIR
 * Author:
 *    Br. Helfrich
 * Summary:
 *    This program will implement a pair: two values
 ************************************************************************/

#ifndef PAIR_H
#define PAIR_H

#include <iostream>  // for ISTREAM and OSTREAM

namespace custom
{

/**********************************************
 * PAIR
 * This class couples together a pair of values, which may be of
 * different types (K and V). The individual values can be
 * accessed through its public members first and second.
 *
 * Additionally, when compairing two pairs, only K is compared. This
 * is a key in a name-value pair.
 ***********************************************/
template <class K, class V>
class pair
{
public:
   // constructors
   pair()                                    : first(     ), second(      ) {}
   pair(const K & first, const V & second) : first(first), second(second) {}
   pair(const pair <K, V> & rhs)   : first(rhs.first), second(rhs.second) {}

   // copy the values
   pair <K, V> & operator = (const pair <K, V> & rhs)
   {
      first  = rhs.first;
      second = rhs.second;
      return *this;
   }

   // constant fetchers
   const K & getFirst()  const { return first;  }
   const V & getSecond() const { return second; }

   // nonConstant fetchers
   K & getFirst()  { return first;  }
   V & getSecond() { return second; }
   
   // compare Pairs. Only first will be compared.
   bool operator >  (const pair & rhs) const { return first >  rhs.first; }
   bool operator >= (const pair & rhs) const { return first >= rhs.first; }
   bool operator <  (const pair & rhs) const { return first <  rhs.first; }
   bool operator <= (const pair & rhs) const { return first <= rhs.first; }
   bool operator == (const pair & rhs) const { return first == rhs.first; }
   bool operator != (const pair & rhs) const { return first != rhs.first; }
   
   // these are public. We cannot validate because we know nothing about T
   K first;
   V second;
};

/*****************************************************
 * PAIR INSERTION
 * Display a pair for debug purposes
 ****************************************************/
template <class K, class V>
inline std::ostream & operator << (std::ostream & out,
                                   const pair <K, V> & rhs)
{
   out << '(' << rhs.first << ", " << rhs.second << ')';
   return out;
}

/*****************************************************
 * PAIR EXTRACTION
 * input a pair
 ****************************************************/
template <class K, class V>
inline std::istream & operator >> (std::istream & in,
                                   pair <K, V> & rhs)
{
   in >> rhs.first >> rhs.second;
   return in;
}

}

#endif // PAIR_H
