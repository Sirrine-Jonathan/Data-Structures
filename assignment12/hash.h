/***********************************************************************
 * Component:
 *    Week 12, Hash
 * Author:
 *    Spencer Eccles
 *    Jonathan Sirrine
 *    Atsushi Jindo
 *    Eric Brich
************************************************************************/
#include "list.h"
#ifndef HASH_H
#define HASH_H
/*****************************************************************
 * HASH
 *****************************************************************/
template <class T>
class Hash
{
public:
	Hash (int numBuckets) throw (const char *) : numBuckets(numBuckets), numElements(0) 
	{ table = new list <T> [numBuckets]; }
	Hash (const Hash <T> & rhs) { *this = rhs; }
	~Hash() { if (numBuckets) clear(); }
	Hash <T> & operator = (const Hash <T> & rhs) throw(const char *)
	{ 
		clear(); 
		table = new list <T> [rhs.numBuckets];
		for (int i = 0; i < rhs.numBuckets; i++) 
			table[i] = rhs.table[i]; 
		numBuckets = rhs.numBuckets;
		numElements = rhs.numElements;
	}

	int size() { return numElements; }
	int capacity() const { return numBuckets; }
	bool empty() { return (numElements == 0); }
	void clear() { numElements = 0; }
	
	bool find(T t) 
	{ 
		for (typename list <T> :: iterator it = table[hash(t)].begin(); it != NULL; ++it)
			if (*it == t)
				return true;
		return false;
	}
	void insert(T t) { table[hash(t)].push_back(t); numElements++; }
	virtual int hash(const T & t) const = 0;

private:
	list <T> * table;
	int numElements;
	int numBuckets;
};

#endif // BST_H