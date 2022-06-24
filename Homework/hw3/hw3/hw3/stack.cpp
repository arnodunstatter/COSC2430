#ifndef STACK_CPP
#define STACK_CPP
#include "stack.h"

template<class T>
stack<T>::stack() {}


template<class T>
stack<T>::~stack()
{
	while (topNode != nullptr)
	{
		sNode<T>* deleteMe = topNode;
		topNode = topNode->next;
		delete deleteMe;
	}
}

template<class T>
void stack<T>::push(T newTop)
{
	sNode<T>* newTopNode = new sNode<T>(newTop);
	newTopNode->next = topNode;
	topNode = newTopNode;
}

template<class T>
T stack<T>::top()
{
	return topNode->hold;
}

template<class T>
void stack<T>::pop()
{
	if (this->isEmpty()) return;
	//else...
	sNode<T>* deleteMe = topNode;
	topNode = topNode->next;
	delete deleteMe;
}

template<class T>
bool stack<T>::isEmpty()
{
	return topNode == nullptr;
}

template<class T>
int stack<T>::size()
{
	sNode<T>* cur = topNode;
	int counter = 0;

	while (cur != nullptr)
	{
		counter++;
		cur = cur->next;
	}
	return counter;
}

template<class T>/////////////////////////////////////////////////////////////////////////////////
void stack<T>::flip()
{
	stack<T> newStack;
	while (!isEmpty())
	{
		newStack.push(top()); pop();
	}
	this = newStack;	
}

//////////////////////////////////////////

template<class T>
sNode<T>::sNode(T val)
	:hold(val) {}
#endif