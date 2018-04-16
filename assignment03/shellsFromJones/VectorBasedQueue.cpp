// QueueVectorBased.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
//Queue.cpp
//demonstrates queue
#include <iostream>
#include <vector>
using namespace std;
////////////////////////////////////////////////////////////////

class Queue
{
	private:
	int maxSize;
	vector<int> queVect;
	int front;
	int rear;
	int nItems;
	public:
	//--------------------------------------------------------------
	//constructor
	Queue(int s) : maxSize(s), front(0), rear(-1), nItems(0)
	{
		queVect.resize(maxSize);
	}
	//--------------------------------------------------------------
	void insert(int j)           //put item at rear of queue
	{
		if (rear == maxSize - 1)         //deal with wraparound
		rear = -1;
		queVect[++rear] = j;          //increment rear and insert
		nItems++;                     //one more item
	}
	//--------------------------------------------------------------
	int remove()                 //take item from front of queue
	{
		int temp = queVect[front++];  //get value and incr front
		if (front == maxSize)          //deal with wraparound
		front = 0;
		nItems--;                     //one less item
		return temp;
	}
	//--------------------------------------------------------------
	int peekFront()              //peek at front of queue
	{
		return queVect[front];
	}
	//--------------------------------------------------------------
	bool isEmpty()               //true if queue is empty
	{
		return (nItems == 0);
	}
	//--------------------------------------------------------------
	bool isFull()                //true if queue is full
	{
		return (nItems == maxSize);
	}
	//--------------------------------------------------------------
	int size()                   //number of items in queue
	{
		return nItems;
	}
	//--------------------------------------------------------------
};  //end class Queue
////////////////////////////////////////////////////////////////

int main()
{
	Queue theQueue(5);              //queue holds 5 items
	theQueue.insert(10);            //insert 4 items
	theQueue.insert(20);
	theQueue.insert(30);
	theQueue.insert(40);
	theQueue.remove();              //remove 3 items
	theQueue.remove();              //   (10, 20, 30)
	theQueue.remove();
	theQueue.insert(50);            //insert 4 more items
	theQueue.insert(60);            //   (wraps around)
	theQueue.insert(70);
	theQueue.insert(80);
	while (!theQueue.isEmpty())    //remove and display
	{                            //   all items
		int n = theQueue.remove();   //(40, 50, 60, 70, 80)
		cout << n << " ";
	}
	cout << endl;
	cout << "Enter any number to quit" << endl;
	int hold;
	cin >> hold;
	return 0;
}  //end main()