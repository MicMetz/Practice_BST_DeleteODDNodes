//
// Created by Nurd on 4/7/2021.
//

#ifndef PRAC_QUESTION1_BST_HPP

#include <vector>

using namespace std;

struct Node {
	int key;
	Node *parent = nullptr;
	Node *left   = nullptr;
	Node *right  = nullptr;
};

class BST {

public:
	// Core public methods:
	BST();                          // default constructor
	BST(int data);                  // parameterized constructor
	~BST();                         // destructor
	void insert(int data);          // insert a node a new element into tree
	bool searchKey(int key);        // search for a key in tree in the tree
	void printTree();               // function to print the tree
	void delOddLeaf();

	// Extra methods:

	void print2DUtil(int space);

	bool isValidBST();

	vector<int> inorderTree();

private:
	Node *root;

	// Helper functions:
	//     Since root is a private member we need helper functions
	//     to access the root and traverse the trees recursively.

	Node *insertHelper(Node *currNode, int data);

	Node *searchKeyHelper(Node *currNode, int data);

	void destroySubTree(Node *currNode);

	void printTreeHelper(Node *currNode);

	bool isBST(Node *root);


	Node *createNode(int data);

	Node *getRoot();                // Returns the root of the tree;

	void print2DUtilHelper(Node *currNode, int space);

	void inorderHelper(Node *currNode, vector<int> &inorder);

};

#endif
