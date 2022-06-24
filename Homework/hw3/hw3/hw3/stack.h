#ifndef STACK_H
#define STACK_H

using namespace std;

template<class T>
class sNode;

template<class T>
class stack
{
private:
	sNode<T>* topNode = nullptr;

public:
	stack();
	//stack(stack&);
	~stack(); //de-allocates memory

	void push(T); //pushes T onto the stack
	T top(); //returns the top
	void pop(); //removes the top
	bool isEmpty(); 
	int size();
	void flip(); //flips the stack
};

template<class T>
class sNode
{
private:
	T hold;
	sNode<T>* next;
	friend class stack<T>;
public:
	sNode(T);
};

#endif