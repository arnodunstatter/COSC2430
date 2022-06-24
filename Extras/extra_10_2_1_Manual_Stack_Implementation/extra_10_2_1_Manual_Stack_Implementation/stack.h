#ifndef STACK_H
#define STACK_H
//using namespace std;

template<typename T>
class node;

template<typename T>
class stack
{
private:
	node<T>* topNode = nullptr;

public:
	stack();
	~stack(); //de-allocates memory

	void push(T); //pushes T onto the stack
	T top(); //returns the top
	void pop(); //removes the top
	bool isEmpty();
	int size();
};

template<typename T>
class node
{
private:
	T hold;
	node<T>* next;
	friend class stack<T>;
public:
	node(T);
};

#endif