#include "PriorityQueue.h"
//PriorityQueue functions


PriorityQueue::PriorityQueue() {}


PriorityQueue::~PriorityQueue()
{
	while (!isEmpty())
	{
		pop();
	}
}

void PriorityQueue::push(string line)
{
	if (line == "") return;
	//else...

	Node* newNode = new Node(line);
	if (isEmpty())
	{
		front = newNode;
		back = newNode;
	}
	else //we must find where to put it
	{
		if (newNode->time < front->time) //we have a new front
		{
			newNode->next = front;
			front = newNode;
		}
		else if (newNode->time > back->time) //we have a new back
		{
			back->next = newNode;
			back = newNode;
		}
		else //we must insert somewhere in the middle
		{
			Node* cur = front;
			//must position cur
			while (newNode->time >= cur->next->time)
				cur = cur->next;

			newNode->next = cur->next;
			cur->next = newNode;
		}
	}
	
}

string PriorityQueue::frontTask()
{
	return front->task;
}

double PriorityQueue::frontTime()
{
	return front->time;
}

void PriorityQueue::pop()
{
	if (isEmpty()) return;
	//else...
	Node* deleteMe = front;
	front = front->next;
	delete deleteMe;
}

bool PriorityQueue::isEmpty()
{
	if (front == nullptr) return true;
	else return false;
}

Node* PriorityQueue::getFront()
{
	return front;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Node functions
Node::Node(string line)
{
	//line.erase(remove(line.begin(), line.end(), '\r'), line.end());
	//line.erase(remove(line.begin(), line.end(), '\n'), line.end());
	string taskString = "";
	string timeString = "";

	//break string into task and time strings
	for (int i = 0; i < line.length(); ++i)
	{
		if (isalpha(line[i]) || line[i] == ' ')
			taskString += line[i];
		else
			timeString += line[i];
	}
	taskString = taskString.substr(0, taskString.length() - 1); //should remove the last ' ' 
	task = taskString; //set task
	time = stod(timeString);
}






