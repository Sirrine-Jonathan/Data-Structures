/***********************************************************************
 * Module:
 *    Assignment 12, Spell Check
 *    Brother Helfrich, CS 235
 * Author:
 *    Spencer Eccles
 *    Jonathan Sirrine
 *    Atsushi Jindo
 *    Eric Brich
 * Summary:
 *    This program will implement the spellCheck() function
 ************************************************************************/

#include <iostream>
#include <fstream>
#include <string>
#include "spellCheck.h"
#include "hash.h"

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::ostream;
using std::ios;
using std::ifstream;
// using namespace std;

/****************************************
 * DICTIONARY HASH
 * A has of words designed specifically
 * to optimize looking up words in a dictionary
 ****************************************/
class DictionaryHash : public Hash <string>
{
public:
   DictionaryHash(int numBuckets)        throw (const char *) : Hash <string> (numBuckets) {};
   DictionaryHash(const DictionaryHash & rhs) throw (const char *) :
         Hash <string> (rhs)       { assert(false); }

   // hash function for strings will add up all the ASCII values
   int hash(const string & s) const
   {
      unsigned int value = 0;
      for (const char * p = s.c_str(); *p; p++)
         if (isalpha(*p))
            value = (value * 26) + (*p - 'a');
      return value % capacity();
   }
};

/*****************************************
 * SPELL CHECK
 * Prompt the user for a file to spell-check
 ****************************************/
void spellCheck()
{
	ifstream dictionary("/home/cs235/week12/dictionary.txt");
	if (dictionary.fail())
	{
		cout << "unable to open" << dictionary;
		return;
	}
	DictionaryHash dHash(3485); // 1.5x the size of the dictionary
	while (!dictionary.eof())
	{
		string s;
		dictionary >> s;
		dHash.insert(s);
	}
	cout << "What file do you want to check? ";
	char filename[256];
	cin >> filename;
	ifstream fin(filename);
	if (fin.fail())
	{
		cout << "unable to open" << filename;
		return;
	}
	bool isError = false;
	while (!fin.eof())
	{
		char c[256];
		fin >> c;
		string s = c;
		c[0] = tolower(c[0]);
		if (!(dHash.find(c)))
		{
			if (!isError)
			{
				cout << "Misspelled: ";
				isError = true;
			}
			else
				cout << ", ";
			cout << s;
		}
	}
	if (!isError)
		cout << "File contains no spelling errors";
	cout << endl;
}
