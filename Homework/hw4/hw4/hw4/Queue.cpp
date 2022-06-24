#ifndef QUEUE_CPP
#define QUEUE_CPP
#include "Queue.h"

template<class T>
node<T>::node(T addMe)
:hold(addMe)
{}

template<class T>
node<T>::~node()
{
	if (this != nullptr)
	{
		delete this;
	}
}


template<class T>
void Queue<T>::push(T addMe)
{
	node<T>* newBack = new node<T>(addMe);
	
	if (isEmpty())
	{
		f = newBack;
		b = newBack;
	}
	else
	{
		b->next = newBack;
		b = newBack;
	}
}


template<class T>
T Queue<T>::front()
{
	if (f != nullptr)
		return f->hold;
	else return nullptr;
}

template<class T>
void Queue<T>::dequeue()
{
	//node<T>* deleteMe = f;

	f = f->next;

	if (f == nullptr) //for when we clear the queue
		b = nullptr;

	//delete deleteMe;
}

template<class T>
bool Queue<T>::isEmpty()
{
	if (f == nullptr && b == nullptr)
		return true;
	else 
		return false;
}

template<class T>
int Queue<T>::size()
{
	int size = 0;
	for (node<T>* cur = f; cur != nullptr; cur = cur->next)
	{
		size++;
	}
	return size;
}
#endif
