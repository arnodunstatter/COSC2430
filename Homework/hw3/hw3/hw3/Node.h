#ifndef Node_h
#define Node_h
#include <string>
#include <iostream>
#include <fstream>

using namespace std;
class Node
{
public:
	Node* previous = nullptr;
	string type = "";
	string expression;
	Node* next = nullptr;

	Node(string, string);
	string removeSpaces(string);

};
#endif
