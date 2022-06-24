#ifndef PriorityQueue_H
#define PriorityQueue_H

#include <string>
#include <iostream>
#include <fstream>

using namespace std;

class Node;

class PriorityQueue
{
private:
	Node* front = nullptr;
	Node* back = nullptr;

	friend class Node;

public:
	PriorityQueue();
	~PriorityQueue();
	void push(string);
	string frontTask();
	double frontTime();
	void pop();
	
	bool isEmpty();

	Node* getFront();
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Node
{
private:
	string task;
	double time;
	Node* next;

	Node(string);

	friend class PriorityQueue;
};

#endif
