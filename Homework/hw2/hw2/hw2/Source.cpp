#include <string>
#include <fstream>
#include "ArgumentManager.h"
#include "Problem.h"

using namespace std;

string find(string key, string line);
void adder(int pos, string ID, string name, string difficulty, Problem*& head, Problem*& tail, int& listLength);
void remove(Problem*& current, Problem*& head, Problem*& tail);
void swap(Problem*& current, Problem*& swap, Problem*& head, Problem*& tail);
void sort(string& keyword, string& order, Problem*& head, Problem*& tail);
void output(Problem* head, ofstream& write);
int getListLength(Problem* head);
void swapAdder(int pos, string ID, string name, string difficulty, Problem*& head, Problem*& tail, int& listLength);
int posOfNode(Problem* node, Problem* head);

int main(int argc, char** argv)
{
	ArgumentManager am(argc, argv); //creates our ArgumentManager object, 'am'

	//these will get the input and output file names
	string inputFile = am.get("input");
	string commandFile = am.get("command");
	string outputFile = am.get("output");
	

	ifstream read(inputFile.c_str()); //creates our read object and opens the input file

	if (!read.is_open()) cout << inputFile << " did not open properly\n"; 
	else
	{
		string temp, name, id, difficulty, garb; //some dummy variables we'll use to read into
		int suspectedListLength = 0;
		int listLength = 0;

		//first we find out how long our linked list will be
			
		read.clear();
		read.seekg(0);
		while (getline(read, temp))
		{
			if (temp != "") suspectedListLength++;
		}

		//now we reset the read stream marker
		read.clear();
		read.seekg(0);
		

		//now we load our linked list
		//but first we have to check to make sure that it shouldn't just be empty
		Problem* current;
		Problem* head = nullptr;
		Problem* tail = nullptr;
		if (suspectedListLength >= 1)
		{
			//now we read data from our inputFile and load our linked list

			for (int i = 0; i < suspectedListLength; ++i)
			{
				name = "";
				//first we load our information into current

				//lets get our id
				read >> temp; //temp = "problem_id:123456,"
				id = temp.substr(11, 6); //id = 123456

				//now lets get our name
				getline(read, garb, ':'); //gets the space after " problem_name"
				getline(read, name, ','); //gets the name
				getline(read, garb, ':'); //gets " difficulty"
				getline(read, difficulty);



				//is the latest addition to the list already in the list? If so we need to remove it
				bool notAlreadyPresent = 1;
				if(head != nullptr)
				{
					for (Problem* checker = head; checker != nullptr; checker = checker->next)
					{
						if (checker->id == id)
						{
							notAlreadyPresent = 0;
						}
					}
				}

				if (notAlreadyPresent)
				{
					adder(i, id, name, difficulty, head, tail, listLength);
				}

			}
			

			//this block tests that we got all our problems
			{
				current = head;
				for (int i = 0; i < listLength; ++i)
				{
					cout << "problem_id:" << current->id << ", " << "problem_name:" << current->name << ", " << "difficulty:" << current->difficulty_S << endl;
					current = current->next;
				}
			}

		}
		read.close();
		listLength = getListLength(head);
		

		

		
		//now we read each command in, perform it, and then continue on reading the next command
		string order; //this will hold either "increasing" or "decreasing" and will be passed to our output function
		ifstream read(commandFile.c_str());
		if (!read.is_open()) cout << commandFile << " did not open properly.\n";
		else
		{
			while (!read.eof())
			{
				string command, garb;
				read >> command;
				getline(read, garb, ' ');
				if (command == "add")
				{
					int pos;
					string pos_S, problem_id, problem_name, problem_diff, garb;
					getline(read, garb, ':');
					getline(read, pos_S, ' '); //gets pos as a string
					pos = stoi(pos_S);
					getline(read, garb, ':');
					getline(read, problem_id, ',');
					getline(read, garb, ':');
					getline(read, problem_name, ',');
					getline(read, garb, ':');
					getline(read, problem_diff);
					adder(pos, problem_id, problem_name, problem_diff, head, tail, listLength);
				}
				else if (command == "remove")
				{
					string keyword;
					getline(read, keyword, ':'); //keyword will be either "pos", "problem_id", "problem_name", or "difficulty"

					if (keyword == "pos")
					{
						int pos;
						string pos_S;
						getline(read, pos_S);
						pos = stoi(pos_S);

						if (pos >= 0 && pos < listLength) //we only remove if the pos is b/w 0 and listLength
						{
							current = head;
							int counter = 0;
							while (current != NULL)
							{
								if (counter == pos)
								{
									remove(current, head, tail);
									--listLength;
								}
								current = current->next;
								++counter;
							}
						}
						//else we remove nothing
					}
					else if (keyword == "problem_id")
					{
						string problem_id;
						getline(read, problem_id);

						current = head;
						while (current != NULL)
						{
							if (current->id == problem_id)
							{
								remove(current, head, tail);
								--listLength;
							}
							else
								current = current->next;
						}
					}
					else if (keyword == "problem_name")
					{
						string problem_name;
						getline(read, problem_name);
						current = head;

						while (current != NULL)
						{
							if (current->name == problem_name)
							{
								remove(current, head, tail);
								--listLength;
							}
							else
								current = current->next;
						}
					}
					else if (keyword == "difficulty")
					{
						string difficulty; //gets the difficulty from commandLine
						getline(read, difficulty);

						//now we traverse the linked list and remove if needed
						current = head;
						while (current != NULL)
						{
							if (current->difficulty_S == difficulty)
							{
								remove(current, head, tail);
								--listLength;
							}
							else
								current = current->next;
						}
					}
				}
				else if (command == "sort")
				{
					string keyword, order;
					getline(read, keyword, ' ');
					getline(read, order);
					sort(keyword, order, head, tail);
				}
			}
	
			
		}
		

		//this block tests that our linked list was changed
		cout << endl;
		if(head != nullptr)
		{
			current = head;
			while(current != nullptr)
			{
				cout << "problem_id:" << current->id << ", " << "problem_name:" << current->name << ", " << "difficulty:" << current->difficulty_S << endl;
				current = current->next;
			}
		}



		ofstream write;
		write.open(outputFile.c_str());
		if (!write.is_open()) cout << outputFile << " did not open properly.\n";
		else
		output(head, write);
		write.close();


		//can't forget to deallocate
		current = head;
		while(current != nullptr)
		{
				Problem* deleteMe = current;
				current = current->next;
				delete deleteMe;
		}
	}

	return 0;
}

string find(string key, string line) //find("pos:","add pos:2") will return 2. This gets the data after the key
{
	string data = "";
	for (int i = 0; i < line.length(); ++i)
	{
		if (line.substr(i, key.length()) == key)
		{
			for (int j = i + key.length(); j < line.length(); ++j)
			{
				if (line[j] == ' ' || line[j] == ',' || line[j] == ':') break;
				data += line[j];

			}
			break;

		}
	}
	return data;
}

void adder(int pos, string ID, string name, string difficulty, Problem* &head, Problem*& tail, int& listLength)
{
	//first we get our current
	Problem* current = head;
	//then we make the node we're going to add
	Problem* toAdd = new Problem(ID, name, difficulty);

	//now we check if we have an empty linked list
	if (current == NULL) //we have an empty linked list
	{
		head = toAdd;
		current = head;
		tail = current;
	}

	else //we must not have an empty linked list
	{
		for (Problem* checker = head; checker != nullptr; checker = checker->next)
		{
			if (checker->id == ID)
				return;

		}


		if (pos <= 0) //add to begining
		{
			head->previous = toAdd;
			toAdd->next = head;
			head = toAdd;
		}
		else if (pos >= listLength) //add to end
		{
			tail->next = toAdd;
			toAdd->previous = tail;
			tail = toAdd;
		}
		else //insert
		{
			current = head; //reset current to head
			for (int i = 0; i <= pos; ++i)
			{
				if (i == pos - 1)
				{
					toAdd->previous = current;
				}
				if (i == pos)
				{
					current->previous->next = toAdd;
					toAdd->next = current;
					current->previous = toAdd;
				}
				current = current->next;
			}
		}
	}
	++listLength;
}

void remove(Problem*& current, Problem*& head, Problem*& tail) //must remember to update listLength
{
	Problem* deleteMe = current;
	if (current->previous == NULL)//we are at head
	{
		if (current->next != NULL) //if true then we have at least 2 nodes in the linked list, if false then we are deleting the only node in the linked list
		{
			current->next->previous = NULL;
			current = current->next;
			head = current;
		}	
		else //if we enter this else then we are removing the only node in the linked list, so we set head and current to NULL
		{
			head = current = NULL;
		}
	}
	else if (current->next == NULL) //we are at the tail
	{
		if (current->previous != NULL) //if true then we have at least 2 nodes in the linked list, if false then we are deleting the only node in the linked list
		{
			current->previous->next = NULL;
			current = current->previous;
			tail = current;
		}
		else //if we enter this else then we are removing the only node in the linked list, so we set head and current to NULL
		{
			head = current = NULL;
		}
	}
	else //we are somewhere in the middle
	{
		current->previous->next = current->next; //links the previous with the next in the forward direction
		current->next->previous = current->previous; //links the next with the previous in the reverse direciton
		//current is no longer in the linked list
		current = current->next;
	}
	delete deleteMe;
}

void swap(Problem*& current, Problem*& swap, Problem*& head, Problem*& tail) //swaps position of current and current->next in the linked list
{
	if (current->next == NULL) //cannot perform a swap with the next element if we're at the last element
		return;

	Problem* oF = current; //original current (First arg)
	Problem* oS = swap; //original next (Second arg)

	//a bunch of holders
	Problem* oFp = oF->previous;
	Problem* oFn = oF->next;
	Problem* oSp = oS->previous;
	Problem* oSn = oS->next;


	//now we reorder the linked list
	if (oF->next != oS)
	{
		//change the previous and next of the first and second
		oF->previous = oSp;
		oF->next = oSn;
		oS->previous = oFp;
		oS->next = oFn;

		//change other involved nodes' pointers
		oF->previous->next = oF;
		oS->next->previous = oS;
		//new as of 9/12/20 2:16pm
		if(oSn != NULL) //re-establishes the reverse link for the element after Second
		oSn->previous = oF;
		if(oFp != NULL) //re-establishes the forward link for the element before First
		oFp->next = oS;
	}
	else
	{
		oF->previous = oFn;
		oF->next = oSn;
		oS->previous = oFp;
		oS->next = oSp;
		if (oSn != NULL) //re-establishes the reverse link for the element after Second
			oSn->previous = oF;
		if (oFp != NULL) //re-establishes the forward link for the element before First
			oFp->next = oS;
	}
	

	if (oF->next == NULL) //must reassign tail
		tail = oF;
	if (oS->previous == NULL) //must reassign head
		head = oS;


	
	//now we update current
	current = oS;
	
}

void sort(string& keyword, string& order, Problem*& head, Problem*& tail)
{
	Problem* leftComp = head; //leftCompare for bubbsort
	Problem* rightComp = head; //rightCompare for bubbsort
	int listLength = getListLength(head);

	int i = 0;
	while(leftComp!=NULL) //for (int i = 0; i < listLength && leftComp != NULL; ++i)
	{
		int j = 0;
		//these next three lines bring rightComp to the node immediately proceeding leftComp
		rightComp = head;
		while (rightComp != leftComp->next)
			rightComp = rightComp->next;

		while(rightComp!=NULL)//for (int j = i + 1; j < listLength && rightComp != NULL; ++j)
		{
			if (keyword == "problem_name")
			{
				if (order == "increasing" && leftComp->name > rightComp->name)
				{
					swap(leftComp, rightComp, head, tail);
					while (rightComp != leftComp) //brings rightComp up to leftComp
						rightComp = rightComp->next;
				}
				else if (order == "decreasing" && leftComp->name < rightComp->name)
				{
					swap(leftComp, rightComp, head, tail);
					while (rightComp != leftComp) //brings rightComp up to leftComp
						rightComp = rightComp->next;
				}
			}
			else if (keyword == "problem_id") //we will bubble sort with each Problem's id
			{
				if(order == "increasing" && leftComp->id > rightComp->id)
				{
					swap(leftComp, rightComp, head, tail);
					while (rightComp != leftComp) //brings rightComp up to leftComp
						rightComp = rightComp->next;
				}
				else if (order == "decreasing" && leftComp->id < rightComp->id)
				{
					swap(leftComp, rightComp, head, tail);
					while (rightComp != leftComp) //brings rightComp up to leftComp
						rightComp = rightComp->next;
				}
			}
			else if (keyword == "difficulty") //we will sort with each problem's difficulty
			{
				if (order == "increasing" && leftComp->difficulty_I > rightComp->difficulty_I)
				{
					int posOfLeftComp = posOfNode(leftComp, head);
					swapAdder(posOfLeftComp, rightComp->id, rightComp->name, rightComp->difficulty_S, head, tail, listLength);
					Problem* newRightComp = rightComp->previous;
					remove(rightComp, head, tail);
					leftComp = leftComp->previous;
					rightComp = newRightComp;
					
				}
				else if (order == "decreasing" && leftComp->difficulty_I < rightComp->difficulty_I)
				{
					swap(leftComp, rightComp, head, tail);
					while (rightComp != leftComp) //brings rightComp up to leftComp
						rightComp = rightComp->next;
				}
				j++;
			}
			rightComp = rightComp->next;
			//cout << endl << "problem_id:" << rightComp->id << ", " << "problem_name:" << rightComp->name << ", " << "difficulty:" << rightComp->difficulty_S << endl;
			++i;
		}
		leftComp = leftComp->next;
	}


	
}

void output(Problem* head, ofstream& write)
{
	Problem* current = head;
	while (current != nullptr)
	{
		write << "problem_id:" << current->id << ", " << "problem_name:" << current->name << ", " << "difficulty:" << current->difficulty_S << endl;
		current = current->next;
	}

}

int getListLength(Problem* head)
{
	int i = 0;
	Problem* current = head;

	while (current != nullptr)
	{
		++i;
		current = current->next;
	}

	
	return i;
}

void swapAdder(int pos, string ID, string name, string difficulty, Problem*& head, Problem*& tail, int& listLength)
{
	//first we get our current
	Problem* current = head;
	//then we make the node we're going to add
	Problem* toAdd = new Problem(ID, name, difficulty);

	//now we check if we have an empty linked list
	if (current == NULL) //we have an empty linked list
	{
		head = toAdd;
		current = head;
		tail = current;
	}

	else //we must not have an empty linked list
	{
		if (pos <= 0) //add to begining
		{
			head->previous = toAdd;
			toAdd->next = head;
			head = toAdd;
		}
		else if (pos >= listLength) //add to end
		{
			tail->next = toAdd;
			toAdd->previous = tail;
			tail = toAdd;
		}
		else //insert
		{
			current = head; //reset current to head
			for (int i = 0; i <= pos; ++i)
			{
				if (i == pos - 1)
				{
					toAdd->previous = current;
				}
				if (i == pos)
				{
					current->previous->next = toAdd;
					toAdd->next = current;
					current->previous = toAdd;
				}
				current = current->next;
			}
		}
	}
	
}

int posOfNode(Problem* node, Problem* head)
{
	int counter = 0;
	Problem* current = head;
	while (current != node)
	{
		++counter;
		current = current->next;
	}
	return counter;
}