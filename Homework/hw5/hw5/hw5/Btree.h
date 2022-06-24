#ifndef Btree_h
#define Btree_h
#include <vector>
#include <fstream>

using namespace std;

class Node
{
public:
	int maxSize; //degree - 1
	vector<int> hold;

	Node* parent = nullptr;
	vector<Node*> children;
	Node(int size, Node* parent);
	void insert(int num);
	void insert(int num, Node* left, Node* right); //used for promoting upward
};

class Btree
{
	int degree;
	int maxNodeSize;
	Node* root = nullptr;

	void promoter(int addMe, Node* cur, Node* left, Node* right);
	bool alreadyHere(int num) { return aHhelper(num, root); }
	bool aHhelper(int num, Node* cur);

public:
	Btree(int degree);
	~Btree();
	void deallocator(Node*);
	void insert(int addMe, Node* cur);
	Node* getRoot() { return root; }
	void output(Node* cur, int curLevel, int levelToGoTo, ofstream& write);
	int getHeight(Node* start);
	
};
#endif
