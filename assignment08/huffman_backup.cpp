#include "huffman.h"
#include <string>
#include "pair.h"
#include "bnode.h"
#include "node.h"

using namespace std;


void huffman(string fileName)
{
   ifstream inputFile(fileName.c_str());
	//BNode <custom::pair <string, float> > * nHead;
   Node <custom::pair <float, string> > * hNodePtr = NULL;

   // put pairs from file into a linked list
	while(!inputFile.eof())
	{
      // build pair from the data in the current line
      string s;
      float f;
		inputFile >> s >> f;
      custom::pair <string, float> linePair(f, s);

      // build a new node
      //Node <custom::pair <string, float> > n(linePair);
      
      //if no list started, make the first node the head
      if (hNodePtr == NULL)
         hNodePtr = nHead.insert(NULL, linePair);


      //traverse list setting the compare to the next node to be compared
      Node <custom::pair <float, string> > * cNodePtr = hNodePtr;
      bool addToRight = false;
      while (cNodePtr != NULL && cNodePtr->data < linePair)
      {
         //compare next node
         if (cNodePtr->pNext != NULL)
            cNodePtr = cNodePtr->pNext;
         else
         {
            addToRight = true;
            return;
         }
      }
      
      //place new node in ordered position
      insert(cNodePtr, linePair, addToRight);
	}

   cout << "finished making sorted list\n";
   


   //list sorted
  // test node orde
   Node <custom::pair <float, string> > * lNodePtr = hNodePtr->next;
   while (lNodePtr != NULL){
      cout << lNodePtr->data cout << endl;
      lNodePtr = hNodePtr->next;
   }
/*
   for(list<int> :: iterator it = nextList.begin(); it != nextList.end(); ++it)
   {
    if(*it != nextList.back())
    {
        cout << *it << ",";
    }
    else
    {
        cout << *it << endl;
    }
   }
   */
   
   
}



