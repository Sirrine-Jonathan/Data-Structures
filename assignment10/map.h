/***********************************************************************
 * Component:
 *    Week 10, map
 * Author:
 *    Spencer Eccles
 *    Jonathan Sirrine
 *    Atsushi Jindo
 *    Eric Brich
 * Summary:
 *    
 ************************************************************************/
#ifndef map_H
#define map_H

#ifdef NDEBUG
#define debug(x)
#else
#define DEBUG
#define debug(x) x
#endif // !NDEBUG

#include <cassert>
#include "bst.h"
#include "pair.h"
#include <string>

namespace custom
{
/***********************************************************************
 * map
 ************************************************************************/
template <class K, class V>
class map
{
public:
   // constructors, destructor, assignment operator
   map() /*, numElements(0)*/ {}
   map(const map & rhs) throw (const char *) { bst = rhs.bst; }
  ~map() { clear(); }
   map & operator = (const map & rhs) throw (const char *) { 
      clear(); 
      bst = rhs.bst;
      return *this; 
   }

   // standard container interfaces
   bool empty() const { return bst.empty(); }
   int  size()  const { return bst.size(); }
   void clear() { bst.clear(); }
   V & operator [] (const K & k) throw (const char *); // mutator
   V operator [] (const K & k)const throw (const char *); // accessor

   // iterators
   class iterator;
   iterator begin() { 
         //return iterator(bst.begin());
         //return iterator ();
         iterator mit;
         mit.getIt() = bst.begin(); 
         return mit; 
   }
   iterator end() { 
         //return iterator(bst.end());
         iterator mit;
         mit.getIt() = bst.end();
         return mit; 
   }

   iterator find(const K & k) { 
      
      //make pair
      pair < K, V > p;
      p.first = k;

      iterator mit;
      mit.getIt() = bst.find(p);

      return mit; 
   }
   void insert (const pair <K, V> & rhs) throw (const char *) { bst.insert(rhs); }
   void insert (const K & k, const V & v) throw (const char *) { insert(pair <K, V> (k, v)); }
   
private:
   BST <pair <K, V> > bst;
};
  
/***********************************************************************
 * map :: iterator
 ************************************************************************/
template <class K, class V>
class map <K, V> :: iterator
{
public:
   // constructors and assignment
   iterator(){}
   iterator(typename BST <pair <K, V> > :: iterator & rhs) { it = rhs; }
   iterator(const iterator & rhs)      { it = rhs.it; }
   iterator & operator = (const iterator & rhs) { it = rhs.it; }

   // compare
   bool operator == (const iterator & rhs) const { return it == rhs.it; }
   bool operator != (const iterator & rhs) const { return it != rhs.it; }

   // de-reference. Cannot change because it will invalidate the BST
   const pair <K, V> & operator * () const { return *it; }

   // iterators
   iterator & operator ++ () { ++it; return *this; }
   iterator   operator ++ (int postfix) { iterator temp(this); it++; return temp; }
   iterator & operator -- () { --it; return *this; }
   iterator   operator -- (int postfix) { return it--; }

   // must give friend status to remove so it can call getNode() from it
   void erase(iterator & it) { it.erase(it.it); }

   friend V & map <K, V> :: operator [] (const K & k) throw (const char *);
   friend V map <K, V> :: operator [] (const K & k)const throw (const char *);
   // friend iterator map <K, V> :: begin();
   // friend iterator map <K, V> :: end();

   typename BST <pair <K, V> > :: iterator & getIt() { return it; }

private:
   typename BST <pair <K, V> > :: iterator it;
}; // map :: iterator

/***********************************************************************
 * map :: [] OPERATOR
 * Mutator
 ************************************************************************/
template <class K, class V>
V & map <K, V> :: operator [] (const K & k) throw (const char *)
{
   pair <K, V> pairValue;
   pairValue.first = k;

   iterator it;
   it.it = bst.find(pairValue);

   //return the value by reference
   if (it.it != NULL)
   {                       
      return pairValue.second;
   }

   //insert the value and return it by reference
   else
   { 
      bst.insert(pairValue);
     //V * v = &pairValue.getSecond();
      //return (*it.it).getSecond();
      return pairValue.second;
   }
}

/***********************************************************************
 * map :: [] OPERATOR
 * Accessor
 ************************************************************************/
template <class K, class V>
V map <K, V> :: operator [] (const K & k)const throw (const char *)
{

   V defaultValue;
   pair <K, V> pairValue(k, defaultValue);

   iterator it;
   it.it = bst.find(pairValue);

   //return the value by reference
   if (it.it != NULL)
   {                       
      return pairValue.second;
   }

   //insert the value and return it by reference
   else
   { 
      bst.insert(pairValue);
     //V * v = &pairValue.getSecond();
      //return (*it.it).getSecond();
      return pairValue.second;
   }
} // namespace custom

#endif // BST_H