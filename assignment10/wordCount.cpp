/***********************************************************************
 * Module:
 *    Week 10, WORD COUNT
 *    Brother Helfrich, CS 235
 * Author:
 *    Spencer Eccles
 *    Jonathan Sirrine
 *    Atsushi Jindo
 *    Eric Brich
 * Summary:
 *    This program will implement the wordCount() function
 ************************************************************************/

#include "wordCount.h" // for wordCount() prototype
#include <iostream>
#include <fstream>
#include <map>
#include <string>
using namespace std;
// void readFile(map <string, Count> & counts, const string & fileName);

/*****************************************************
 * WORD COUNT
 * Prompt the user for a file to read, then prompt the
 * user for words to get the count from
 *****************************************************/
void wordCount()
{
   cout << "What is the filename to be counted? ";
   string filename;
   cin >> filename;

   ifstream fin(filename.c_str());
   if (fin.fail()){
      cout << "nope\n";
      return;
   }
   
   map <string, int> words;
   
   //generate map of wordcounts
   while (!fin.eof())
   {
      string nextWord;
      fin >> nextWord;
         
      map <string, int> :: iterator it;

      it = words.find(nextWord);

      if (it == words.end())
      {
         pair <string, int> p(nextWord, 1);
         words.insert(p);
      }
      else {
         words[nextWord]++;
      }
   }

   //handle display interface
   cout << "What word whose frequency is to be found. Type ! when done\n";
   string word;
   do {
      cout << "> ";
      cin >> word;
      if (word != "!"){        
         cout << "\t";
         cout << word << " : ";
         map <string, int> :: iterator it;
         it = words.find(word);
         if (it != words.end())
            cout << words[word] << endl;
         else
            cout << 0 << endl;
      }
   }
   while (word != "!");
}
