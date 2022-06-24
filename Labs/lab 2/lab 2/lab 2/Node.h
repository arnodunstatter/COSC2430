#ifndef Node_h
#define Node_h
#include <string>
using namespace std;
class Node
{
public:
	Node* previous = nullptr;
	Node* next = nullptr;
	string word = "";

	Node(string);
	~Node();
};

#endif