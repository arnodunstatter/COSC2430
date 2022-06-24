#include "list.h"
node::node(string t, string e)
	: type(t)
{
	expression = removeSpaces(e);
}

string node::removeSpaces(string eWS) //eWS is "expression with spaces"
{
	string e = ""; //will be "expression without spaces" by the end
	for (int i = 0; i < eWS.length(); ++i)
	{
		if (eWS[i] != ' ')
			e += eWS[i];
	}
	return e;
}



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*------------------------PUBLIC FUNCTIONS-----------------------------------------------------------------------------*/
list::list(string inputFile, string commandFile, string outputFile)
{
	ifstream read(inputFile.c_str());
	if (!read.is_open())
	{
		cout << "Input file did not open properly.\n";
		return;
	}
	//else...
	string type;
	while (getline(read, type, ':')) //gets our type
	{
		string expWS; //expression with spaces
		getline(read, expWS); //gets the expression with spaces
		//now we have to remove spaces
		node* addMe = new node(type, expWS);
		//call adder
		adder(addMe);
	}
	read.close();
	printList(); //trouble shooting

	//now we have to process commands
	read.open(commandFile.c_str());
	if (!read.is_open())
	{
		cout << "Command file did not open properly.\n";
		return;
	}
	//else...
	ofstream write(outputFile.c_str());
	if (!write.is_open())
	{
		cout << "Output file did not open properly.\n";
		return;
	}
	//else...
	string line;
	while (getline(read, line))
	{
		string argument;
		if (lineHasArgument(line))
		{
			argument = splitLine(line);
			executeCommand(write, line, argument);
		}
		else
		{
			executeCommand(write, line);
		}
		printList(); //troubleshooting
	}

	//for testing purposes
	while (!reserve.isEmpty())
	{
		popReserve("20");
	}
	printList();
	//////////////////////////////////////////////////////////////////
}

list::~list()
{
	for (node* c = head; c != nullptr;)
	{
		node* deleteMe = c;
		c = c->next;
		delete deleteMe;
	}
}

void list::printList()
{
	for (node* cur = head; cur != nullptr; cur = cur->next)
	{
		cout << cur->type << ":" << cur->expression << endl;
	}
	cout << endl;
}


/*------------------------PRIVATE FUNCTIONS------------------------------------------------------------------------------------------------------------*/

void list::adder(node* addMe)
{
	if (head == nullptr && tail == nullptr) // we have an empty list
	{
		head = addMe;
		tail = addMe;
	}
	else //we are adding to the end
	{
		tail->next = addMe;
		addMe->previous = tail;
		tail = addMe;
	}
}

int list::length()
{
	int counter = 0;
	for (node* cur = head; cur != nullptr; cur = cur->next)
		++counter;
	return counter;
}

bool list::lineHasArgument(string line)
{
	for (int i = 0; i < line.size(); i++)
	{
		if (line[i] == ' ')
			return 1;
	}
	return 0;
}

string list::splitLine(string& originalLine)
{
	string toOrLine; //we will change originalLine to be toOrLine at the end
	int j = 0;
	while (originalLine[j] != ' ')
	{
		toOrLine += originalLine[j];
		++j;
	}

	string toReturn = "";
	for (int i = j + 1; i < originalLine.length(); ++i)
		toReturn += originalLine[i];

	originalLine = toOrLine;
	return toReturn;
}

void list::executeCommand(ofstream& write, string command)
{
	if (command == "printList")
		outputList(write, command);
	else if (command == "printListBackwards")
		outputList(write, command);
	else if (command == "flipReserve")
		flipReserve();
	else if (command == "printReserveSize")
		outputReserveSize(write);
	else if (command == "convertReserve")
		convertReserve();
	else if (command == "printReserveTop")
		outputReserveTop(write);
	else
		cout << "A command was read improperly.\n";
}

void list::outputList(ofstream& write, string command) //called "printList" and "printListBackwards" in instructions
{
	
	if (command == "printList") //outputting in forwards direction
	{
		write << "List:\n";

		if (head == nullptr)
			write << "EMPTY\n";
		else
		{
			for (node* cur = head; cur != nullptr; cur = cur->next)
			{
				write << cur->type << ":" << cur->expression << endl;
			}
		}
	}
	else //start should be tail, outputting in backwards direction
	{
		write << "Reversed List:\n";

		if (tail == nullptr)
			write << "EMPTY\n\n";
		else
		{
			for (node* cur = tail; cur != nullptr; cur = cur->previous)
			{
				write << cur->type << ":" << cur->expression << endl;
			}
		}
	}
	write << endl;
}

void list::flipReserve()
{
	stack<node*>* newReserve = new stack<node*>;
	while (!reserve.isEmpty())
	{
		newReserve->push(reserve.top()); reserve.pop();
	}
	reserve = *newReserve;
}

void list::outputReserveSize(ofstream& write)
{
	write << "Reserve Size: " << reserve.size() << endl << endl;
}

void list::convertReserve()
{
	if (reserve.isEmpty())
		return;
	//else...

	//top it
	node* topToConvert = reserve.top();
	//pop it
	reserve.pop();
	//convert it
	notationConverter(topToConvert);
	//push it
	reserve.push(topToConvert);
}

void list::outputReserveTop(ofstream& write)
{
	write << "Top of reserve: ";
	if (reserve.isEmpty())
		write << "EMPTY\n\n";
	else
		write << reserve.top()->type << ":" << reserve.top()->expression << endl << endl;
}




void list::executeCommand(ofstream& write, string command, string argument)
{
	argument = argument.substr(1, argument.size() - 2); //removes the parenthesis

	if (command == "convertList")
		convertList(argument);
	else if (command == "removeList")
		removeList(argument);
	else if (command == "pushReserve")
		pushReserve(argument);
	else if (command == "popReserve")
		popReserve(argument);
	else if (command == "emptyReserve")
		emptyReserve(argument);
}

void list::convertList(string arg)
{
	if (arg == "all")
	{
		for (node* cur = head; cur != nullptr; cur = cur->next)
		{
			notationConverter(cur);
		}
	}
	else if (isInt(arg)) //convert by pos
	{
		int pos = stoi(arg);
		if (pos >= length())
			return;
		else if (pos <= 0) //convert at head
			notationConverter(head);
		else if (pos == length() - 1) //convert at tail
			notationConverter(tail);
		else //we are converting somewhere in the list
		{
			node* cur = head;
			for (int i = 0; i < pos; ++i) //will bring cur to the pos index in the list
				cur = cur->next;
			notationConverter(cur);
		}
	}
	else if (arg == "postfix")
	{
		for (node* cur = head; cur != nullptr; cur = cur->next)
		{
			if (cur->type == "postfix")
				notationConverter(cur);
		}
	}
	else if (arg == "prefix")
	{
		for (node* cur = head; cur != nullptr; cur = cur->next)
		{
			if (cur->type == "prefix")
				notationConverter(cur);
		}
	}
}

void list::notationConverter(node* cur)
{
	stack<string> holder;
	if (cur->type == "postfix") //postfix to prefix converter
	{
		string postfix = cur->expression;
		string prefix;
		string temp = "";
		string dummy;
		for (int i = 0; i < postfix.length(); ++i)
		{
			if (isalpha(postfix[i]))
			{
				temp = postfix[i];
				holder.push(temp);
			}
			else //we got to an operator
			{
				temp = postfix[i];
				dummy = holder.top(); holder.pop();
				temp += holder.top(); holder.pop();
				temp += dummy;
				holder.push(temp);
			}
		}
		prefix = holder.top(); holder.pop();
		cur->expression = prefix;
		cur->type = "prefix";
	}
	else if (cur->type == "prefix") //prefix to postfix converter
	{
		string prefix = cur->expression;
		string postfix;
		stack<string> holder;
		string temp;

		for (int i = prefix.length() - 1; i >= 0; --i)
		{
			if (isalpha(prefix[i])) //operand
			{
				temp = prefix[i];
				holder.push(temp);
			}
			else //operator
			{
				temp = holder.top(); holder.pop();
				temp += holder.top(); holder.pop();
				temp += prefix[i];
				holder.push(temp);
			}
		}
		postfix = holder.top(); holder.pop();
		cur->expression = postfix;
		cur->type = "postfix";
	}
}

bool list::isInt(string arg)
{
	for (int i = 0; i < arg.length(); ++i)
	{
		if (!isdigit(arg[i]))
			return false;
	}
	return true;
}

void list::removeList(string arg)
{
	if (arg == "all")
	{
		for (node* cur = head; cur != nullptr; cur = head)
			remover(cur);
	}
	else if (isInt(arg)) //remove by pos
	{
		int pos = stoi(arg);
		if (pos >= length())
			return;
		else if (pos <= 0) //remove at head
			remover(head);
		else if (pos == length() - 1) //remove at tail
			remover(tail);
		else //we are removing somewhere in the list
		{
			node* cur = head;
			for (int i = 0; i < pos; ++i) //will bring cur to the pos index in the list
				cur = cur->next;
			remover(cur);
		}
	}
	else if (arg == "postfix")
	{
		for (node* cur = head; cur != nullptr;) //need a saver
		{
			if (cur->type == "postfix") //if we delete cur we can't update it using cur->next, so we need a saver
			{
				node* saver = cur->next;
				remover(cur);
				cur = saver;
			}
			else //if we don't delete cur we can update using cur = cur->next
				cur = cur->next;
		}
	}
	else if (arg == "prefix")
	{
		for (node* cur = head; cur != nullptr;) //need a saver
		{
			if (cur->type == "prefix") //if we delete cur we can't update it using cur->next, so we need a saver
			{
				node* saver = cur->next;
				remover(cur);
				cur = saver;
			}
			else //if we don't delete cur we can update using cur = cur->next
				cur = cur->next;
		}
	}
}

void list::remover(node* cur)
{
	//is the list already empty?
	if (cur == nullptr)
		return;

	node* deleteMe = cur;
	//does the list have only one element?
	if (cur == head && cur == tail)
	{
		head = nullptr;
		tail = nullptr;
	}
	//we either remove at head
	else if (cur == head)
	{
		head->next->previous = nullptr;
		head = head->next;
	}
	//we remove at tail
	else if (cur == tail)
	{
		tail->previous->next = nullptr;
		tail = tail->previous;
	}
	//we remove in the middle
	else //we are removing from a middle area
	{
		cur->previous->next = cur->next;
		cur->next->previous = cur->previous;
	}
	delete deleteMe;
}

void list::pushReserve(string arg)
{
	if (arg == "all")
	{
		for (node* cur = head; cur != nullptr; cur = head)
		{
			reserve.push(cur);
			prRemover(cur); //removes from linked list
		}
	}
	else if (isInt(arg)) //using pos
	{
		int pos = stoi(arg);
		if (pos >= length())
			return;
		else if (pos <= 0) //push and prRemove at head
		{
			reserve.push(head);
			prRemover(head);
		}
		else if (pos == length() - 1) //push and prRemove at tail
		{
			reserve.push(tail);
			prRemover(tail);
		}
		else //push and prRemove at somewhere in the list
		{
			node* cur = head;
			for (int i = 0; i < pos; ++i) //will bring cur to the pos index in the list
				cur = cur->next;
			reserve.push(cur);
			prRemover(cur);
		}
	}
	else if (arg == "postfix")
	{
		for (node* cur = head; cur != nullptr;) //need a saver
		{
			if (cur->type == "postfix") //if we remove cur we can't update it using cur->next, so we need a saver
			{
				node* saver = cur->next;
				reserve.push(cur);
				prRemover(cur);
				cur = saver;
			}
			else //if we don't delete cur we can update using cur = cur->next
				cur = cur->next;
		}
	}
	else if (arg == "prefix")
	{
		for (node* cur = head; cur != nullptr;) //need a saver*****************
		{

			if (cur->type == "prefix") //if we delete cur we can't update it using cur->next, so we need a saver
			{
				node* saver = cur->next;
				reserve.push(cur);
				prRemover(cur);
				cur = saver;
			}
			else //if we don't delete cur we can update using cur = cur->next
				cur = cur->next;
		}
	}
}

void list::prRemover(node* cur) //push reserve remover 
{
	//is the list already empty?
	if (cur == nullptr)
		return;

	//does the list have only one element?
	if (cur == head && cur == tail)
	{
		head = nullptr;
		tail = nullptr;
	}
	//we either remove at head
	else if (cur == head)
	{
		head->next->previous = nullptr;
		head = head->next;
	}
	//we remove at tail
	else if (cur == tail)
	{
		tail->previous->next = nullptr;
		tail = tail->previous;
	}
	//we remove in the middle
	else //we are removing from a middle area
	{
		cur->previous->next = cur->next;
		cur->next->previous = cur->previous;
	}

	cur->previous = nullptr;
	cur->next = nullptr;
}

void list::popReserve(string arg)
{
	if (reserve.isEmpty())
		return;
	//else...

	int pos = stoi(arg);
	if (head == nullptr) //we are adding to en empty list
	{
		head = reserve.top();
		tail = head;
	}
	else if (pos <= 0) //want to add at head
	{
		reserve.top()->next = head;
		head->previous = reserve.top();
		head = reserve.top();
	}
	else if (pos >= length() - 1) //want to add at tail
	{
		reserve.top()->previous = tail;
		tail->next = reserve.top();
		tail = reserve.top();
	}
	else //we want to add at somewhere in the list
	{
		node* cur = head;
		for (int i = 0; i < pos; ++i) //will bring cur to the pos index in the list
			cur = cur->next;

		reserve.top()->next = cur;
		reserve.top()->previous = cur->previous;
		cur->previous->next = reserve.top();
		cur->previous = reserve.top();
	}

	reserve.pop();
}

void list::emptyReserve(string arg)
{
	while (!reserve.isEmpty())
		popReserve(arg);
}

