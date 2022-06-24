#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H
#include "Queue.cpp"
#include "Process.h"
class PriorityQueue : protected Queue<Process*>//, protected node<Process*>
{
public:
	PriorityQueue();

	void push(Process*);

	Process* front(); //returns whatever front is holding

	void dequeue(); //removes front from the queue and deletes that node

	bool isEmpty(); //checks if the queue is empty

	int size(); //returns the size of the queue
};

class ProcessNode : protected node<Process*> 
{
	friend class PriorityQueue;
public:
	ProcessNode(Process*);
	~ProcessNode();
};
#endif
