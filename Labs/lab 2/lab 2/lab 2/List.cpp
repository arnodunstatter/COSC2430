#include "List.h"

Node* List::getHead() { return head; }

Node* List::getTail() { return tail; }

int List::length()
{
	int counter = 0;
	
	for (Node* cur = head; cur != nullptr; cur = cur->next)
		counter++;

	return counter;
}

void List::adder(string newWord)
{
	Node* toAdd = new Node(newWord); //makes the new node

	//to decide how to add it we must know the length of our linked list
	int len = length();

	if (len == 0) //we have an empty list
	{
		head = toAdd;
		tail = toAdd;
	}

	else //we already have a head so we're making a new tail
	{
		toAdd->previous = tail;
		tail->next = toAdd;
		tail = toAdd;
	}
}

void List::makeList(string inputFile)
{
	ifstream read(inputFile.c_str());

	if (!read.is_open()) cout << "Input file did not open properly.\n";
	else
	{
		string newWord;
		while (read >> newWord)
		{
			adder(newWord);
		}
		read.close();
	}
}

void List::output(string outputFile)
{
	ofstream write(outputFile.c_str());
	if (!write.is_open()) cout << "Output file did not open properly.\n";
	else
	{
		Node* current = head;
		revOutput(write, current);
	}
}

void List::revOutput(ofstream& write, Node* current)
{
	if (current == nullptr) return;
	revOutput(write, current->next);
	if (current->previous == nullptr)
		write << current->word;
	else
		write << current->word << " ";
}