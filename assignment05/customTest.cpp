/***********************************************************************
* Program:
*    Temp file so we can run custom tests
*    b.out
* Author:
*    Jonathan Sirrine
* Summary: 
*    This is a driver program to exercise the Set class.
************************************************************************/

#include <iostream>       // for CIN and COUT
#include <string>         // because testIterate() uses a Set of string
#include "set.h"          // your Set class needs to be in set.h
#include "goFish.h"       // your goFish() function needs to be defined here

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::ostream;
using std::ios;
//using namespace std;
using namespace custom;

/****************************************************************
 * just an easier way to display strings
 ****************************************************************/
void d(string s){
	cout << s << endl;
}

/****************************************************************
 * displays the properties of a set
 * the pass the set variable name as a string for name
 ****************************************************************/
template <class T>
void showSet(string name, set <T> s)
{
	cout << name << ".size() = "     << s.size() << endl;
	cout << name << ".capacity() = " << s.capacity() << endl;
	cout << name << ".empty() = "    << ((s.empty()) ? "True":"False") << endl;
	cout << s << endl << endl;
}

/****************************************************************
 * display function I took from assignment05
 ****************************************************************/
template <class T>
ostream & operator << (ostream & out, set <T> rhs)
{

   out << "{ ";
   typename set <T> :: iterator it;
   for (it = rhs.begin(); it != rhs.end(); ++it)
      out << *it << ' ';
   out << '}';
   return out;
}


/****************************************************************
 * first tests I ran that I'm scared to delete
 ****************************************************************/
void basicTest()
{

	d("Default Constructor");
	set <int> s1; 
	cout << "s1" << ".size() = "     << s1.size() << endl;
	cout << "s1" << ".capacity() = " << s1.capacity() << endl;
	cout << "s1" << ".empty() = "    << ((s1.empty()) ? "True":"False") << endl;
	cout << endl;

	d("Non-default Constructor");
	set <int> s2(2);
	cout << "s2" << ".size() = "     << s2.size() << endl;
	cout << "s2" << ".capacity() = " << s2.capacity() << endl;
	cout << "s2" << ".empty() = "    << ((s2.empty()) ? "True":"False") << endl;
	cout << endl;


	d("Copy Constructor");
	set <int> s3(s2);
	cout << "s3" << ".size() = "     << s3.size() << endl;
	cout << "s3" << ".capacity() = " << s3.capacity() << endl;
	cout << "s3" << ".empty() = "    << ((s3.empty()) ? "True":"False") << endl;
	cout << endl;

	d("Assignment Operator");
	s1 = s3;
	cout << "s1" << ".size() = "     << s1.size() << endl;
	cout << "s1" << ".capacity() = " << s1.capacity() << endl;
	cout << "s1" << ".empty() = "    << ((s1.empty()) ? "True":"False") << endl;
	cout << endl;

	d("Insert");
	set <int> s4;
	s4.insert(1);
	cout << "s4" << ".size() = "     << s4.size() << endl;
	cout << "s4" << ".capacity() = " << s4.capacity() << endl;
	cout << "s4" << ".empty() = "    << ((s4.empty()) ? "True":"False") << endl;
	cout << s4 << endl;
	cout << endl;

	s4.insert(2);
	cout << "s4" << ".size() = "     << s4.size() << endl;
	cout << "s4" << ".capacity() = " << s4.capacity() << endl;
	cout << "s4" << ".empty() = "    << ((s4.empty()) ? "True":"False") << endl;
	cout << s4 << endl;
	cout << endl;

	s4.insert(3);
	cout << "s4" << ".size() = "     << s4.size() << endl;
	cout << "s4" << ".capacity() = " << s4.capacity() << endl;
	cout << "s4" << ".empty() = "    << ((s4.empty()) ? "True":"False") << endl;
	cout << s4 << endl;
	cout << endl;

}

/****************************************************************
 * find seg fault on copy 
 ****************************************************************/
void testIterators()
{

   set <string> s1;

   s1.insert("alpha");
   s1.insert("charlie");
   s1.insert("echo");
   s1.insert("delta");
   s1.insert("beta");
   
   set <string> s2(s1);
   showSet("s2", s2);

   //regular iterators
   d("Iterator loop display\n");
   cout << " { ";
   for (set <string> :: iterator itStart = s2.begin(); itStart != s2.end(); ++itStart)
       cout << *itStart << ", ";
   cout << " } \n";


   string deleteString = "delta";
   set <string> :: iterator itEnd = s2.end();
   set <string> :: iterator itFind = s2.find(deleteString);
   d("just did find\n");
   if (itFind != itEnd)
   {
      cout << "*itFind = " << *itFind << endl;
   	  bool deleteSuccess = s2.erase(itFind);
   	  cout << "delete success = " << ((deleteSuccess) ? "Yes":"No") << "\n";

	  d("Iterator loop display\n");
	  cout << " { ";
	  for (set <string> :: iterator itStart = s2.begin(); itStart != s2.end(); ++itStart)
	     cout << *itStart << ", ";
	  cout << " } \n";
   }
   else
   	  cout << "not found\n";


}

void test3()
{
   try
   {
      // create a list using the default constructor
      set <string> s1;

      // fill the Set with text
      cout << "Enter text, type \"quit\" when done\n";
      string text;
      do
      {
         cout << "\t" << s1 << " > ";
         cin  >> text;
         if (text != "quit")
            s1.insert(text);
      }
      while (text != "quit");

      // make a copy of the set using the copy constructor
      set <string> s2(s1);
   
      // look for an item in the set
      cout << "Find items in the set and delete.\n";
      cout << "Enter words to search for, type \"quit\" when done\n";
      
      cout << "\t" << s1 << " > ";
      cin  >> text;
      do
      {
         set <string> :: iterator itEmpty = s1.end();
         set <string> :: iterator itFind = s1.find(text);
         if (itFind != itEmpty)
         {
            cout << "\tFound and removed!\n";
            s1.erase(itFind);
         }
         else
            cout << "\tNot found\n";
         cout << "\t" << s1 << " > ";
         cin  >> text;
      }
      while (text != "quit");

      // show the list again
      cout << "The remaining set after the items were removed\n";
      cout << "\t" << s1 << endl;

      // show the list before the items were removed
      cout << "The items in the set before the items were removed\n";
      cout << "\t" << s2 << endl;
   }
   catch (const char * sError)
   {
      cout << sError << endl;
   }
}

void testDifference()
{
   try
   {
      // create a set of 10 characters
      set <char> s1;
      s1.insert('a');
      s1.insert('b');
      s1.insert('c');
      s1.insert('d');
      s1.insert('e');
      s1.insert('f');
      s1.insert('g');
      s1.insert('h');
      s1.insert('i');
      s1.insert('j');
      cout << "s1: " << s1 << endl;


      // create a second set of 10 characters
      set <char> s2;
      s2.insert('z');
      s2.insert('y');
      s2.insert('x');
      s2.insert('d');
      s2.insert('e');
      s2.insert('f');
      s2.insert('g');
      s2.insert('h');
      s2.insert('i');
      s2.insert('j');
      cout << "s2: " << s2 << endl;

      // s1 - s2 and s2 - s1
      set <char> sDifference;
      sDifference = s1 - s2;
      cout << "\t" << s1 << " - " << s2 << " = " << sDifference << endl;
      sDifference = s2 - s1;
      cout << "\t" << s2 << " - " << s1 << " = " << sDifference << endl;
   }
   catch (const char * sError)
   {
      cout << sError << endl;
   }   
}


/****************************************************************
 * MAIN runs the different tests
 ****************************************************************/
int main()
{
   //basicTest();
   //testIterators();
   //test3();
   testDifference();
   return 0;
}

