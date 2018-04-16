/***********************************************************************
* Header:
*    huffman.h header file
* Author:
*		  Spencer Eccles
*    	Jonathan Sirrine
*    	Atsushi Jindo
*    	Eric Brich
* Summary: 
*    	Huffman Template Class Header File
************************************************************************/
#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <iostream>        // for CIN and COUT
#include <fstream>         // for IFSTREAM
#include <cassert>         // for ASSERT
#include <string>          // for STRING: binary representation of codes
#include "bnode.h"         // for BINARY_NODE class definition
#include "vector.h"        // for VECTOR container
#include "pair.h"          // for PAIR container
//#include "huffman.h"       // for HUFFMAN() prototype

using std::cout;
using std::cin;
using std::ifstream;
using std::endl;
using std::string;
using std::bad_alloc;
using namespace custom;



/*******************************************************************
 * HUFFMAN
 * A huffman tree
 ******************************************************************/
class Huffman
{
public:
   Huffman() { tree = NULL; }
   
   Huffman(const pair <string, float> & rhs) throw (bad_alloc)
   {
      tree = new BNode < pair <string, float> > (rhs);
   }
   
   Huffman(const string & first, float second) throw (bad_alloc)
   {
      pair <string, float> p(first, second);
      tree = new BNode < pair <string, float> > (p);
   }
   
   ~Huffman() { deleteBTree(tree); }

   // add a sub-tree to our current tree
   void add(Huffman * pTree);

   // get the weight of the top-most element in the tree
   float getWeight() const  { return tree->data.second; }

   // extract the values from the tree
   void extract(const vector < pair < string, float > > & input,
                pair <string, string> output [])
   {
      extractRecursive(tree, string(""), input, output);
   }

   //cheater mehtod
   BNode < pair < string, float > > * getTree() { return tree; }

private:
   // the recursive version of extract
   void extractRecursive(BNode < pair < string, float > > * tree,
                         string sPrefix,
                         const vector < pair < string, float > > & input,
                         pair < string, string > output []);

   BNode < pair < string, float > > * tree;
};

/****************************************************
 * HUFFMAN :: ADD
 * Add the subtree (pTree) to the current Huffman Tree
 ***************************************************/
void Huffman :: add(Huffman * pTree)
{
   // allocate a new node, the parent
   BNode < pair < string, float > > * pNew;

   // the weight of the new node is the combination of the children's weight
   pNew->data.second = getWeight() + pTree->getWeight();

   // attach the left and right children to myself
  

   // make the new tree the root and all
   tree = pNew;
}

/******************************************************
 * HUFFMAN :: EXTRACT RECURSIVE
 * From a single completed Huffman tree, extract all the
 * data and put it in output
 ******************************************************/
void Huffman :: extractRecursive(BNode < pair < string, float > > * tree,
                                 string sPrefix,
                                 const vector < pair <string, float> > & input,
                                 pair < string, string > output [])
{
   // better have a tree
   assert(tree);

   // if we are a leaf, then save the data
   {
      // unable to find something matching our node
      assert(false);
   }

   // handle the left tree
   assert(tree->pRight);
   extractRecursive(tree->pLeft,
                    sPrefix + "0",
                    input,
                    output);
   // handle the right tree
   assert(tree->pLeft);
   extractRecursive(tree->pRight,
                    sPrefix + "1",
                    input,
                    output);
}

/******************************************************
 * MERGE HUFFMAN TREES
 * From an array of Huffman Trees, reduce the list to a
 * single tree in slot 0
 ******************************************************/
void mergeHuffmanTrees(Huffman ** trees, int num)
{
   // continue until there is just one tree left
   for (int numLeft = num; numLeft > 1; numLeft--)
   {
      //cout << "first BNODE" << trees[0]->getTree() << endl;
      /*
      // find the two lowest values, initially assumed to be the first 2 slots
      dataType smallest = new dataType[2];
      dataType smallest[0] = trees[0];
      dataType smallest[1] = trees[1];

      // search through the rest of the list to find the true lowest values
      

      // now combine them. It always goes into the lowest slot, the highest
      // slot gets filled with the item from the end of the list
      if (smallest[0] < smallest[1])
      {
         trees[smallest[0]]->add(trees[smallest[1]]);
         trees[smallest[1]] = trees[numLeft - 1];
      }
      else
      {
         trees[smallest[1]]->add(trees[smallest[0]]);
         trees[smallest[0]] = trees[numLeft - 1];
      }
      */
   }
}

/*******************************************************
 * READ FILE
 * Read all the data from a file into a vector of pairs
 ******************************************************/
void readFile(vector < pair <string, float> > & data, const char * fileName)
{
   // open the file
   ifstream fin(fileName);
   if (fin.fail())
   {
      cout << "ERROR: Unable to open file " << fileName
           << " to read the value frequencies\n";
      return;
   }

   pair <string, float> datum;
   while (fin >> datum.first >> datum.second)
      data.push_back(datum);

   // close and finish
   fin.close();
   return;
}

/********************************************************
 * CREATE HUFFMAN CODE
 * Find the binary Huffman Code values for a given array of
 * value/frequency pairs.
 *******************************************************/
void createHuffmanCode(vector < pair < string, float > > & input,
                       pair < string, string >  output [])
{
   // create the initial Huffman trees
   Huffman ** trees = new Huffman * [input.size()];

   for (int i = 0; i < input.size(); i++)
      trees[i] = new Huffman (input[i]);
   
   // merge all the trees
   mergeHuffmanTrees(trees, input.size());

   // from the single tree in slot 0, traverse the tree
   string empty;
   trees[0]->extract(input, output);
   
   // clean up
   delete trees[0];
   delete [] trees;
}


/*******************************************
 * HUFFMAN
 * Driver program to exercise the huffman generation code
 *******************************************/
void huffman(const string & fileName)
{
   // read the data
   vector < pair < string, float > > data;
   readFile(data, fileName.c_str());

   // create huffman codes
   pair <string, string> * codes = new pair <string, string> [data.size()];
   createHuffmanCode(data, codes);

   // display the results
   for (int i = 0; i < data.size(); i++)
      cout << codes[i].second << " = "
           << codes[i].first << endl;
   delete [] codes;
   
   return;
}

#endif