#ifndef List_h
#define List_h

#include "Node.h"
#include <fstream>
#include <iostream>

class List
{
private:
	Node* head = nullptr;
	Node* tail = nullptr;

public:
	Node* getHead();
	Node* getTail();
	int length();
	void adder(string); //adds nodes to the linked list
	void makeList(string); //reads inputFile and makes the list
	void output(string); //opens our outputFile and calls our recursive reverse outputter
	void revOutput(ofstream&, Node*); //our recursive outputter which will output in reverse order

};

#endif