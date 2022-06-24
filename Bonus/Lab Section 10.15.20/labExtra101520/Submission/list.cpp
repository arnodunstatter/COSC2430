#include "list.h"

node::node(int num)
	: num(num) {}

void list::adder(int num)
{
	node* addMe = new node(num);

	if (head == nullptr && tail == nullptr) // we have an empty list
	{
		head = addMe;
		tail = addMe;
	}
	else //we are adding to the end
	{
		tail->next = addMe;
		addMe->previous = tail;
		tail = addMe;
	}
}

int list::length()
{
	int counter = 0;
	for (node* cur = head; cur != nullptr; cur = cur->next)
		++counter;
	return counter;
}

void list::printList()
{
	for (node* cur = head; cur != nullptr; cur = cur->next)
	{
		cout << cur->num;
		if(cur->next != nullptr)
			cout << " -> ";
	}
	cout << endl;
}

void list::reverseLL(int howMany)
{
	if (howMany < 0) return;
	else if (howMany >= length())
	{
		while (head != nullptr)
		{
			reserve.push(head);
			prRemover(head);
		}
	}
	else
	{
		int pos = length() - howMany;
		for (int i = 0; i < howMany; ++i) //pushes into stack, removes from list
		{
			node* cur = head;

			for (int i = 0; i < pos; i++) //moves cur to where we need to start pushing into stack
				cur = cur->next;

			reserve.push(cur);
			prRemover(cur);
		}
	}
	
	//now we add to the end from our reserve stack
	while(!reserve.isEmpty())
		popReserve();
}
void list::prRemover(node* cur) //push reserve remover 
{
	//is the list already empty?
	if (cur == nullptr)
		return;

	//does the list have only one element?
	if (cur == head && cur == tail)
	{
		head = nullptr;
		tail = nullptr;
	}
	//we either remove at head
	else if (cur == head)
	{
		head->next->previous = nullptr;
		head = head->next;
	}
	//we remove at tail
	else if (cur == tail)
	{
		tail->previous->next = nullptr;
		tail = tail->previous;
	}
	//we remove in the middle
	else //we are removing from a middle area
	{
		cur->previous->next = cur->next;
		cur->next->previous = cur->previous;
	}

	cur->previous = nullptr;
	cur->next = nullptr;
}

void list::popReserve()
{
	if (reserve.isEmpty())
		return;
	//else...

	if (tail == nullptr) //empty list
	{
		head = reserve.top();
		tail = head;
	}
	else
	{
		tail->next = reserve.top();
		reserve.top()->previous = tail;
		tail = tail->next;
	}
	reserve.pop();
}