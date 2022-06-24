#ifndef STACK_CPP
#define STACK_CPP
#include "stack.h"

template<typename T>
stack<T>::stack() {}

template<typename T>
stack<T>::~stack()
{
	while (topNode != nullptr)
	{
		node<T>* deleteMe = topNode;
		topNode = topNode->next;
		delete deleteMe;
	}
}

template<typename T>
void stack<T>::push(T newTop)
{
	node<T>* newTopNode = new node<T>(newTop);
	newTopNode->next = topNode;
	topNode = newTopNode;
}

template<typename T>
T stack<T>::top()
{
	return topNode->hold;
}

template<typename T>
void stack<T>::pop()
{
	node<T>* deleteMe = topNode;
	topNode = topNode->next;
	delete deleteMe;
}

template<typename T>
bool stack<T>::isEmpty()
{
	return topNode == nullptr;
}

template<typename T>
int stack<T>::size()
{
	node<T>* cur = topNode;
	int counter = 0;

	while (cur != nullptr)
	{
		counter++;
		cur = cur->next;
	}
	return counter;
}

//////////////////////////////////////////

template<typename T>
node<T>::node(T val)
	:hold(val) {}
#endif