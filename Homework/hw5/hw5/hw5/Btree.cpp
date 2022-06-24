#include "Btree.h"
//------------------------Begin Node functions----------------------------------------------------------------------------------------------------
Node::Node(int s, Node* p)
	:maxSize(s), parent(p) {}

void Node::insert(int num)
{
	if (hold.empty())
		hold.push_back(num);
	else
	{
		vector<int>::iterator ih = hold.begin();
		const vector<int>::iterator holdBegin = hold.begin();
		vector<Node*>::iterator ic = children.begin();
		for (;; ++ih, ++ic)
		{
			if (num < *ih) //we found where we need to put it
			{
				hold.insert(ih, num); //adds num to our hold
				children.insert(ic, nullptr);
				break;
			}
			else if (ih == --hold.end())
			{
				hold.push_back(num);
				children.push_back(nullptr);
				break;
			}
		}
	}
}

void Node::insert(int num, Node* left, Node* right)
{
	vector<int>::iterator ih = hold.begin();
	vector<Node*>::iterator ic = children.begin();
	for (;; ++ih, ++ic)
	{
		if (num < *ih) //we found where we need to put it
		{
			hold.insert(ih, num); //adds num to our hold

			*ic = right;
			children.insert(ic, left);
			break;
		}
		else if (ih == --hold.end())
		{
			hold.push_back(num);
			*++ic = left; //might need to be `*ic = left;`
			children.push_back(right);
			break;
		}
	}
}

//------------------------End Node functions----------------------------------------------------------------------------------------------------



//------------------------Begin Btree functions----------------------------------------------------------------------------------------------------

Btree::Btree(int d)
	:degree(d), maxNodeSize(d-1) {}

Btree::~Btree()
{
	deallocator(root);
}

void Btree::deallocator(Node* cur)
{
	if (cur->children[0] == nullptr)
		delete cur;
	else
	{
		for (int i = 0; i < cur->children.size(); ++i)
			deallocator(cur->children[i]);
	}
}

void Btree::insert(int addMe, Node* cur)
{
	if(!alreadyHere(addMe)) //if it's not already in the tree, we insert it
	{
		if (root == nullptr) //making first node in the tree
		{
			Node* newRoot = new Node(maxNodeSize, nullptr);
			newRoot->hold.push_back(addMe);
			newRoot->children.push_back(nullptr);
			newRoot->children.push_back(nullptr);
			root = newRoot;
		}
		else if (cur->children[0] == nullptr)//then either it goes in the node or it's time to start promoting
		{
			cur->insert(addMe);
			if (cur->hold.size() > maxNodeSize) //if inserting it into the node overloads it, then it's time to start promoting
			{
				//figure out which number needs to be promoted, promoteMe
				int promoteMe, promotedIndex;
				if (cur->hold.size() % 2 == 0) //even number of elements
					promotedIndex = cur->hold.size() / 2 - 1;
				else //odd number of elements
					promotedIndex = cur->hold.size() / 2;
				promoteMe = cur->hold[promotedIndex];

				//make new nodes
				Node* left = new Node(cur->maxSize, cur->parent);
				Node* right = new Node(cur->maxSize, cur->parent);

				//lets fill in left
				for (int i = 0; i < promotedIndex; ++i)
				{
					left->hold.push_back(cur->hold[i]);
					left->children.push_back(cur->children[i]);
					//get the last pointer
					if (i == promotedIndex - 1)
						left->children.push_back(cur->children[i + 1]);
				}

				//lets fill in right
				for (int i = promotedIndex + 1; i < cur->hold.size(); ++i)
				{
					right->hold.push_back(cur->hold[i]);
					right->children.push_back(cur->children[i]);
					//get the last pointer
					if (i == cur->hold.size() - 1)
						right->children.push_back(cur->children[i + 1]);
				}

				promoter(promoteMe, cur->parent, left, right);
				delete cur;
			}
		}
		else//it has children, check which pointer we have to go down
		{
			vector<int>::iterator ih = cur->hold.begin();
			vector<Node*>::iterator ic = cur->children.begin();
			vector<int>::iterator last = --cur->hold.end();
			for (;; ++ih, ++ic)
			{
				if (addMe <= *ih)
				{
					insert(addMe, *ic); //recursive call
					break;
				}
				else if (ih == last)
				{
					insert(addMe, *(++ic));
					break;
				}
			}
		}
	}
}


void Btree::promoter(int addMe, Node* cur, Node* leftBelow, Node* rightBelow)
{
	if (cur == nullptr) //we need to make a new root
	{
		Node* newRoot = new Node(maxNodeSize, nullptr);
		newRoot->hold.push_back(addMe);
		newRoot->children.push_back(leftBelow);
		leftBelow->parent = newRoot;
		newRoot->children.push_back(rightBelow);
		rightBelow->parent = newRoot;
		root = newRoot;
	}
	else
	{
		if (cur->hold.size() < cur->maxSize) //it just goes into cur
		{
			cur->insert(addMe, leftBelow, rightBelow);
			leftBelow->parent = cur;
			rightBelow->parent = cur;
		}
		else //time to make a new level
		{
			cur->insert(addMe, leftBelow, rightBelow); //now the node has too many elements
			//figure out which number needs to be promoted
			int promoteMe, promotedIndex;
			if (cur->hold.size() % 2 == 0) //even number of elements
				promotedIndex = cur->hold.size() / 2 - 1;
			else
				promotedIndex = cur->hold.size() / 2;
			promoteMe = cur->hold[promotedIndex];

			//make new nodes
			Node* left = new Node(cur->maxSize, cur->parent);
			Node* right = new Node(cur->maxSize, cur->parent);
			
			//lets fill in left
			for (int i = 0; i < promotedIndex; ++i)
			{
				left->hold.push_back(cur->hold[i]);
				left->children.push_back(cur->children[i]);
				//get the last pointer
				if (i == promotedIndex - 1)
					left->children.push_back(cur->children[i + 1]);
			}

			//lets fill in right
			for (int i = promotedIndex + 1; i < cur->hold.size(); ++i)
			{
				right->hold.push_back(cur->hold[i]);
				right->children.push_back(cur->children[i]);
				//get the last pointer
				if (i == cur->hold.size() - 1)
					right->children.push_back(cur->children[i + 1]);
			}

			//adjust parents
			for (int i = 0; i < left->children.size(); ++i)
				left->children[i]->parent = left;
			for (int i = 0; i < right->children.size(); ++i)
				right->children[i]->parent = right;

			//recursive call
			promoter(promoteMe, cur->parent, left, right);

			//don't need cur anymore
			delete cur;
		}
	}
}


bool Btree::aHhelper(int num, Node* cur)
{
	if (cur == nullptr) return false;
	vector<int>::iterator ih = cur->hold.begin();
	vector<int>::iterator last = --cur->hold.end();
	vector<Node*>::iterator ic = cur->children.begin();
	for (;; ++ih, ++ic)
	{
		if (num == *ih) return true;
		else if (num < *ih) return aHhelper(num, *ic);
		else if (ih == last) return aHhelper(num, *++ic);
	}
}

void Btree::output(Node* cur, int curLevel, int levelToGoTo, ofstream& write)
{
	if (levelToGoTo > getHeight(root)) write << "Empty";
	else if (curLevel == levelToGoTo)
	{
		if (cur->hold.empty())
			write << "Empty";
		else
		{
			for (int i = 0; i < cur->hold.size(); ++i)
				write << cur->hold[i] << " ";
		}
	}
	else
	{
		for (int i = 0; i < cur->children.size(); ++i)
			output(cur->children[i], curLevel + 1, levelToGoTo, write);
	}

}

int Btree::getHeight(Node* start)
{
	if (start->children[0] == nullptr)
		return 1;
	else
		return 1 + getHeight(start->children[0]);
}



//------------------------End Btree functions----------------------------------------------------------------------------------------------------