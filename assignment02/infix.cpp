/***********************************************************************
 * Module:
 *    Week 02, Stack
 *    Brother Helfrich, CS 235
 * Author:
 *    Jonathan Sirrine
 * Summary:
 *    This program will implement the testInfixToPostfix()
 *    and testInfixToAssembly() functions
 ************************************************************************/

#include <iostream>    // for ISTREAM and cout
#include <string>      // for string
#include <cassert>     // for ASSERT
#include "stack.h"     // for STACK
//using namespace std;
using namespace custom;


/*****************************************************
 * CONVERT INFIX TO POSTFIX
 * Convert infix equation "5 + 2" into postifx "5 2 +"
 *****************************************************/
std::string convertInfixToPostfix(const std::string & infix)
{
    std::string postfix;
   
   char token,
         topToken;
   // class has to be referred to in its custom namespace
   class custom::stack<char> myStack;
   const std::string BLANK = " ";
   for (int i = 0; i < infix.length(); i++)
   {
      token = infix[i];
      // using switch and cases to help convert infix to postfix
      switch(token)
      {
         case ' ' : break;    //do nothing skip blanks
         case '(' : myStack.push(token);
                    break;
         case ')' : for (;;)
            {
               assert (!myStack.empty());
               topToken = myStack.top();
               myStack.pop();
               if (topToken == '(') break;
               postfix.append(BLANK + topToken);
            }
            break;
         case '+' : case '-' :
         case '^' : case '*' : case '/' : case '%':
                    for (;;)
                    {
                        if (myStack.empty() ||
                           myStack.top() == '(' ||
                           ((token == '^' || token == '*' || token == '/' || token == '%') &&
                           (myStack.top() == '*' || myStack.top() == '+' || myStack.top() == '-')))
                        {
                           myStack.push(token);
                           break;
                        }
                        else
                        {
                           topToken = myStack.top();
                           myStack.pop();
                           postfix.append(BLANK + topToken);
                        }
                    }
                    break;
         default : //operand
                  // postfix.append(BLANK + token);
                  if ( isdigit(infix[i-1]) )
                  {
                     postfix.append(1, token);
                  }
                  else
                  {
                     postfix.append(BLANK + token);
                  }

                  for(;;)
                  {
                     if ( !isalnum(infix[i+1]) ) break; //end of identifier
                     i++;
                     token = infix[i];
                     postfix.append(1, token);
                  }
      }
   }
   // pop remaining operators on the stack
   for (;;)
   {
      if (myStack.empty()) break;
      topToken = myStack.top();
      myStack.pop();
      if (topToken != '(')
      {
         postfix.append(BLANK + topToken);
      }
      else
      {
         std::cout << " *** Error in infix expression ***\n";
         break;
      }
   }

   return postfix;
}

/*****************************************************
 * TEST INFIX TO POSTFIX
 * Prompt the user for infix text and display the
 * equivalent postfix expression
 *****************************************************/
void testInfixToPostfix()
{
   std::string input;
   std::cout << "Enter an infix equation.  Type \"quit\" when done.\n";
   
   do
   {
      // handle errors
      if (std::cin.fail())
      {
         std::cin.clear();
         std::cin.ignore(256, '\n');
      }
      
      // prompt for infix
      std::cout << "infix > ";
      getline(std::cin, input);

      // generate postfix
      if (input != "quit")
      {
         std::string postfix = convertInfixToPostfix(input);
         std::cout << "\tpostfix: " << postfix << std::endl << std::endl;
      }
   }
   while (input != "quit");
}

/**********************************************
 * CONVERT POSTFIX TO ASSEMBLY
 * Convert postfix "5 2 +" to assembly:
 *     LOAD 5
 *     ADD 2
 *     STORE VALUE1
 **********************************************/
std::string convertPostfixToAssembly(const std::string & postfix)
{
   std::string assembly;

   return assembly;
}

/*****************************************************
 * TEST INFIX TO ASSEMBLY
 * Prompt the user for infix text and display the
 * resulting assembly instructions
 *****************************************************/
void testInfixToAssembly()
{
   std::string input;
   std::cout << "Enter an infix equation.  Type \"quit\" when done.\n";

   do
   {
      // handle errors
      if (std::cin.fail())
      {
         std::cin.clear();
         std::cin.ignore(256, '\n');
      }
      
      // prompt for infix
      std::cout << "infix > ";
      getline(std::cin, input);
      
      // generate postfix
      if (input != "quit")
      {
         std::string postfix = convertInfixToPostfix(input);
         std::cout << convertPostfixToAssembly(postfix);
      }
   }
   while (input != "quit");
      
}
 // end custom namespace