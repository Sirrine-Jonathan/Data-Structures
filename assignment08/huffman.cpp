#include "huffman.h"

void huffman(string & fileName){
   cout << "Starting huffman function\n";



   ifstream inputFile(fileName.c_str());
   if (inputFile.fail())
   {
      cout << "ERROR: Unable to open file " << fileName
           << " to read the value frequencies\n";
      return;
   }

   //set head of linked list to null
   Node <custom::pair <float, string> > * hNodePtr = NULL;

   // put pairs from file into a linked list
   while(!inputFile.eof())
   {
      cout << "In loop\n";
      // build pair from the data in the current line
      string s;
      float f;
      inputFile >> s >> f;
      custom::pair <float, string> linePair(f, s);
      
      //if no list started, make the first node the head
      if (hNodePtr == NULL)
         hNodePtr = insert(hNodePtr, linePair);
         
      //traverse list setting the compare to the next node to be compared
      Node <custom::pair <float, string> > * cNodePtr = hNodePtr;
      bool addToRight = false;
      while (cNodePtr != NULL && cNodePtr->data < linePair)
      {
         //compare next node
         if (cNodePtr->pNext != NULL){
            cNodePtr = cNodePtr->pNext;
            cout << "data: " << cNodePtr->data << "\n";
         }
         else
         {
            addToRight = true;
            return;
         }
      }

      
      //place new node in ordered position
      cout << "Before Insert\n";
      insert(cNodePtr, linePair, addToRight);
      cout << "After Insert\n";
   }

   cout << "finished making sorted list\n";
}
/*

void huffman(string fileName)
{
   /*
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
      custom::pair <float, string> linePair(f, s);

      // build a new node
      //Node <custom::pair <string, float> > n(linePair);
      
      //if no list started, make the first node the head
      if (hNodePtr == NULL)
         hNodePtr = insert(NULL, linePair);


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
   
/*

   //list sorted
  // test node orde
   Node <custom::pair <float, string> > * lNodePtr = hNodePtr->pNext;
   while (lNodePtr != NULL){
      cout << lNodePtr->data << endl;
      lNodePtr = hNodePtr->pNext;
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
   
   /*
}

*/


