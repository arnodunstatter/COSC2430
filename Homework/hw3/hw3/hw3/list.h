#ifndef List_h
#define List_h
#include "stack.cpp"
#include <string>
#include <iostream>
#include <fstream>
using namespace std;

class node
{
public:
	node* previous = nullptr;
	string type = "";
	string expression;
	node* next = nullptr;

	node(string, string);
	string removeSpaces(string);

};
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class list
{
public:
	list(string, string, string); //final version
	~list();
	void printList();
	
/*----------------------------------------------------------------------------------------------------------------------------------------------------*/
private:
	node* head = nullptr;
	node* tail = nullptr;

	stack<node*> reserve;


	void adder(node*);

	int length();

	bool lineHasArgument(string);
	string splitLine(string&);

	void executeCommand(ofstream&, string); //for commands without arguments
	void outputList(ofstream&, string); //called "printList" and "printListBackwards" in instructions
	void flipReserve();
	void outputReserveSize(ofstream&); //called "printReserveSize" in the instructions
	void convertReserve();
	void outputReserveTop(ofstream&); //called "printReserveTop" in instructions


	void executeCommand(ofstream&, string, string); //for commands with arguments
	void convertList(string);
	void notationConverter(node*);
	bool isInt(string);
	void removeList(string);
	void remover(node*);
	void pushReserve(string); //removes from linked list and adds to reserve
	void prRemover(node*); //removes from linked list
	void popReserve(string);
	void emptyReserve(string);
};
#endif