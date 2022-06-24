#ifndef QUEUE_H
#define QUEUE_H

#include <string>
#include <iostream>
#include <fstream>

using namespace std;

template<class T>
class node;

template<class T>
class Queue
{
protected:
	node<T>* f = nullptr;
	node<T>* b = nullptr;

public:
	void push(T); //creates a node which holds the passed in argument and puts it at the back of the queue

	T front(); //returns whatever front is holding

	void dequeue(); //removes front from the queue and deletes that node
	
	bool isEmpty(); //checks if the queue is empty

	int size(); //returns the size of the queue
};

template<class T>
class node
{
	friend class Queue<T>;
	friend class PriorityQueue; //why is this necessary?

protected:
	T hold = NULL;
	node* next = nullptr;
	 
	node(T);
	~node();
};
#endif
