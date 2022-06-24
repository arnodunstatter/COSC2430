#include "PriorityQueue.h"

PriorityQueue::PriorityQueue()
	:Queue() {}

ProcessNode::ProcessNode(Process* addMe)
	:node(addMe) {} //invoking node's constructor

ProcessNode::~ProcessNode()
{
	if (this != nullptr)
	{
		delete this;
	}
}

void PriorityQueue::push(Process* addMe)
{
	ProcessNode* newNode = new ProcessNode(addMe);

	if (isEmpty())
	{
		f = newNode;
		b = newNode;
	}
	else //we must find where to put it
	{
		if (newNode->hold->ProcessNumber < f->hold->ProcessNumber) //we have a new front
		{
			newNode->next = f;
			f = newNode;
		}
		else if (newNode->hold->ProcessNumber > b->hold->ProcessNumber) //we have a new back
		{
			b->next = newNode;
			b = newNode;
		}
		else //we must insert somewhere in the middle
		{
			node<Process*>* cur = f; //why couldn't I use: `ProcessNode* cur = f;`
			//must position cur
			while (newNode->hold->ProcessNumber >= cur->next->hold->ProcessNumber)
				cur = cur->next;

			newNode->next = cur->next;
			cur->next = newNode;
		}
	}

}

Process* PriorityQueue::front()
{
	return Queue::front();
}

void PriorityQueue::dequeue()
{
	Queue::dequeue();
}

bool PriorityQueue::isEmpty()
{
	return Queue::isEmpty();
}

int PriorityQueue::size()
{
	return Queue::size();
}

