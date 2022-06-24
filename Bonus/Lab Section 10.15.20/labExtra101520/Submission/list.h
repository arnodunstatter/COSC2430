#ifndef List_h
#define List_h
#include <string>
#include <iostream>
#include "stack.cpp"

using namespace std;

class node
{
public:
	node* previous = nullptr;
	int num;
	string expression;
	node* next = nullptr;

	node(int);
};
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class list
{
public:
	void printList();
	void adder(int);
	int length();

	void reverseLL(int);
	void prRemover(node*);
	void popReserve();
private:
	stack<node*> reserve;
	node* head = nullptr;
	node* tail = nullptr;

};
#endif