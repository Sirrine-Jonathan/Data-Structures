/***********************************************************************
 * Component:
 *    Assignment 10, Map
 *    Brother Helfrich, CS 235
 * Author:
 *    Br. Helfrich
 * Summary:
 *    Create a Map
 ************************************************************************/
#ifndef MAP_H
#define MAP_H
#include "pair.h"     // for pair
#include "bst.h"      // no nested class necessary for this assignment
#ifndef debug
#ifdef DEBUG
#define debug(x) x
#else
#define debug(x)
#endif // DEBUG
#endif // !debug
namespace custom
{
/*****************************************************************
 * MAP
 * Create a Map, similar to a Binary Search Tree
 *****************************************************************/
template <class K, class V>
class map
{
public:
   // constructor, destructor, and assignment operator
   map()                                     {                          }
   map(const map & rhs) throw (const char *) { *this = rhs;             }
  ~map()                                     {                          }
   map & operator = (const map & rhs) throw (const char &)
   {
      clear();
      bst = rhs.bst;
      return *this;
   }
   
   // standard container interfaces
   bool empty() const               { return bst.empty();               }
   int  size() const                { return bst.size();                }
   void clear()                     { bst.clear();                      }
   // iterators
   class iterator;
   class reverse_iterator;
   iterator          begin() { return iterator         (bst.begin());  }
   reverse_iterator rbegin() { return reverse_iterator (bst.rbegin()); }
   iterator            end() { return iterator         (bst.end());    }
   reverse_iterator   rend() { return reverse_iterator (bst.rend());   }
   // map-specific interfaces
   V   operator [] (const K & k) const;
   V & operator [] (const K & k) throw (const char *);
   iterator    find(const K & k)
   {
      return iterator (bst.find( pair < K, V > (k, V()) ) );
   }
   void insert(const pair <K, V> & rhs) throw (const char *)
   {
      bst.insert(rhs);
   }
   void insert(const K & k, const V & v) throw (const char *)
   {
      insert(pair <K, V> (k, v));
   }
   
private:
   // the students DO NOT need to use a nested class
   BST < pair < K, V > > bst;
};