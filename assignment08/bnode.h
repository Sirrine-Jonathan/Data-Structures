/***********************************************************************
* Header:
*    BNode.h header file
* Author:
*	   Spencer Eccles
*    Jonathan Sirrine
*    Atsushi Jindo
*    Eric Brich
* Summary: 
*    	BNode Template Class Header File
************************************************************************/
#ifndef BNODE_H
#define BNODE_H

#include <cassert> //for asserts
#include <iostream>
#include <string>

template <class T>
class BNode 
{
  public:
   T data;
   BNode <T> * pLeft;
   BNode <T> * pRight;
   BNode <T> * pParent;

   BNode() : pLeft(NULL), pRight(NULL), pParent(NULL), data() {}
   BNode(const T & data) : pLeft(NULL), pRight(NULL), pParent(NULL), data(data) {}
};

template <class T>
void addLeft (BNode <T> * pNode, BNode <T> * pAdd) throw  (const char *)
{
	try
	{
		pNode->pLeft = pAdd;

		// if we are inserting to the left position
		if (pAdd !=NULL)
		{
			//pNode->pLeft->pParent = pNode;
			pAdd->pParent = pNode;
		}
	}
	catch(...)
	{
		throw "Error: Unable to allocate new node";
	}
}

template <class T>
void addRight(BNode <T> * pNode, BNode <T> * pAdd) throw (const char *)
{
	try
	{
		pNode->pRight = pAdd;
	
		// if we are inserting to the right position
		if (pAdd !=NULL)
		{
			//pNode->pRight->pParent = pNode;
			pAdd->pParent = pNode;
		}
	}
	catch(...)
	{
		throw "Error: Unable to allocate new node";
	}

}

template <class T>
void addLeft (BNode <T> * pNode, const T & t) throw (const char *) //ERROR: Unable to allocate a node
{
 	try
   	{
      	// allocate a new BinaryNode
       	BNode<T> * tempLeft = new BNode<T>(t);
       	//addLeft(pNode, tempLeft);
       	tempLeft->pParent = pNode;
       	pNode->pLeft = tempLeft;
   	}
   	catch(...) 
   	{
      	throw "Error: Unable to allocate a new node";
   	}
}

template <class T>
void addRight(BNode <T> * pNode, const T & t) throw (const char *) //ERROR: Unable to allocate a node
{
 	try
   	{
      	// allocate a new BinaryNode
       	BNode<T> * tempRight = new BNode<T>(t);
       	//addRight(pNode, tempRight);
       	tempRight->pParent = pNode;
       	pNode->pRight = tempRight;
   	}
   	catch(...) 
   	{
      	throw "Error: Unable to allocate a new node";
   	}
}

/*
   Takes a BNode as a parameter makes a copy of the tree. 
   The return value is the newly copied tree. This is a recursive function.
*/
template <class T>
BNode <T> * copyBTree(const BNode <T> * pSource) throw (const char *)
{
	
	if (pSource == NULL)
		return NULL;

	BNode<T> * destination = new BNode<T>(pSource->data);
	
	/*destination->data = pSource->data;

	destination->pLeft = copyBTree(pSource->pLeft);
	destination->pRight = copyBTree(pSource->pRight);*/
	
	//destination->pLeft = copyBTree(pSource->pLeft);
	if (pSource->pLeft != NULL)
	{
		
		BNode <T> * lDestination;
		lDestination = copyBTree(pSource->pLeft);
		addLeft(destination, lDestination);
		//destination->pLeft->pParent = destination;
	}
	//destination->pRight = copyBTree(pSource->pRight);
	if (pSource->pRight != NULL)
	{	
		
		BNode <T> * rDestination;
		rDestination = copyBTree(pSource->pRight);
		addRight(destination, rDestination);
		
		//destination->pRight->pParent = destination;
	}
	
	return destination;
}

/*
   Takes a BNode as a parameter and deletes all the children and itself. 
   This is a recursive function.
*/
template <class T>
void deleteBTree(BNode <T> * & pRemove)
{
	// delete items from the list
	/*
	while (pRemove != NULL)
	{
		BNode<T>  * p = pRemove->pLeft;

		delete pRemove;
		pRemove = p;
	}

	pRemove = NULL;*/
	if (pRemove == NULL)
		return;

	deleteBTree(pRemove->pLeft);
	deleteBTree(pRemove->pRight);
	
	delete pRemove;
	pRemove = NULL;
}

/*
   Takes a constant BNode * as a parameter and displays the tree under the passed parameter. 
   This is a recursive function traversing the tree in LVR order. 
   A single space will be displayed after every element.
*/
template <class T>
std::ostream & operator << (std::ostream & out, const BNode <T> * pHead)
{
	// return nothing if there isn't anything
	if (NULL == pHead)
		return out;

		const BNode<T> * p = pHead;
		out << p->pLeft;
		out << p->data << " ";
		out << p->pRight;
	return out;
}

template <class T>
int sizeBTree(const BNode <T> * pNode)
{
	if (pNode == NULL)
		return 0;
	else
		return sizeBTree(pNode->pLeft) + 1 + sizeBTree(pNode->pRight);
}
#endif