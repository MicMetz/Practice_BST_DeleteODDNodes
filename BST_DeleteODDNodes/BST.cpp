/*
 * Write C++ code that goes through a Binary Search Tree and deletes every leaf node with an odd
key value. Your function should display the key values of each node of the tree, starting with the
left child, then the right child, before displaying the root of each subtree. The nodes that are
being deleted should display the key with a message “deleting” next to the key value. Your code
should prevent any potential memory leaks.
 */

#include "BST.h"
#include <iostream>
#include <vector>


using namespace std;
#define COUNT 10
#define DEBUG_PRINT_TREE_HELPER true // true: printTreeHelper() will show parent/child relationships

/*
PUBLIC METHODS:
*/

// Constructor definitions:
// Default:
BST::BST() {
	root = NULL;
}

// Parameterized constructor. Create the root and initialize key with data value.
BST::BST(int data) {
	root = createNode(data);
	cout << "New tree created with " << data << "as root node" << endl;
}

// Destructor
BST::~BST() {
	destroySubTree(root);
}

void BST::insert(int data) {
	root = insertHelper(root, data);
	cout << data << " has been added" << endl;
}

// This function will return whether a key is in the tree
bool BST::searchKey(int key) {
	Node *tree = searchKeyHelper(root, key);
	if (tree != NULL) {
		return true;
	}
	cout << "Key not present in the tree" << endl;
	return false;
}


void BST::printTree() {
	if (root) {
		cout << "ROOT node: " << root->key << endl;

	}
	printTreeHelper(root);
	cout << endl;
}


void BST::print2DUtil(int space) {
	print2DUtilHelper(root, space);
}

bool BST::isValidBST() {
	return isBST(root);
}

vector<int> BST::inorderTree() {
	vector<int> inorder;
	inorderHelper(root, inorder);
	return inorder;
}

//TODO:
Node* delOddLeafHelper(vector<Node *> nodes, Node *root) {
	if (nodes.empty()) { return root; }

	for (int i = 0; i < nodes.size(); i++) {
		if (nodes[i]->left == NULL && nodes[i]->right == NULL) {              // If there are no children to the deleting node
			if (nodes[i]->parent) {
				if (nodes[i] == nodes[i]->parent->right) {
					nodes[i]->parent->right = NULL;
					nodes[i]->parent        = NULL;
				}
				else {
					nodes[i]->parent->left = NULL;
					nodes[i]->parent       = NULL;
				}
			}
			free( nodes[i]);
			nodes[i] = NULL;
			continue;
		}
		if (nodes[i]->left != NULL && nodes[i]->right != NULL) {

			// Else there are 2 children to the deleting node
			// Get the right most child of the left node to replace the deleting node
			Node *find_replacement = nodes[i]->left;
			while (find_replacement->right) {               // Find largest value child of the left child of the deleting node
				find_replacement = find_replacement->right;
			}

			if (nodes[i]->parent != NULL) {
				if (nodes[i] == nodes[i]->parent->right) {
					nodes[i]->parent->right         = find_replacement;
					find_replacement->parent->right = find_replacement->left;          // Remove the right pointer of the parent node or have it point to the left child of the replacement
					find_replacement->parent        = nodes[i]->parent;
					free( nodes[i]);
					nodes[i] = NULL;
				}
				else {
					nodes[i]->parent->left          = find_replacement;
					find_replacement->parent->right = find_replacement->left;          // Remove the right pointer of the parent node or have it point to the left child of the replacement
					find_replacement->parent        = nodes[i]->parent;
					free( nodes[i]);
					nodes[i] = NULL;
				}
			}

			else {
				Node *replaceRoot = root;
				root = find_replacement;                           // If there isn't a parents, the left child of the deleting node becomes root
				free(replaceRoot);
				replaceRoot = NULL;
			}
		}

		else {
			if (nodes[i]->left == NULL) {                              // If there is only a right child
				Node *temp = nodes[i]->right;
				if (nodes[i]->parent != NULL) {                         // If there is a parent
					if (nodes[i] == nodes[i]->parent->right) {  // If the node to delete is a right child
						nodes[i]->parent->right = temp;         //      then the parents right child becomes the right child of the deleting node
					}
					else {
						nodes[i]->parent->left = temp;          // Else the parents left child becomes the right child of the deleting node
					}
					free( nodes[i]);
					nodes[i] = NULL;
				}
				else {
					Node *replaceRoot = root;
					root = temp;                           // If there isn't a parents, the left child of the deleting node becomes root
					free(replaceRoot);
					replaceRoot = NULL;
				}
			}

			// if (nodes[i]->right == NULL) {                             // If there is only a left child
			else {
				Node *temp = nodes[i]->left;
				if (nodes[i]->parent != NULL) {                         // If there is a parent
					if (nodes[i] == nodes[i]->parent->right) {  // If the node to delete is a right child
						nodes[i]->parent->right = temp;         //      then the parents right child becomes the left child of the deleting node
					}
					else {
						nodes[i]->parent->left = temp;          // Else the parents left child becomes the left child of the deleting node
					}
					free( nodes[i]);
					nodes[i] = NULL;
				}
				else {
					Node *replaceRoot = root;
					root = temp;                           // If there isn't a parents, the left child of the deleting node becomes root
					delete replaceRoot;
					replaceRoot = NULL;
				}
			}
		}
	}

	return root;
}

vector<Node *> postOrderGather(Node *node, vector<Node *> nodes) {
	if (node->left) {
		nodes = postOrderGather(node->left, nodes);
	}
	if (node->right) {
		nodes = postOrderGather(node->right, nodes);
	}
	nodes.push_back(node);
	return nodes;
}

void BST::delOddLeaf() {
	vector<Node *> deleteNodes;
	vector<Node *> nodes;

	nodes = postOrderGather(getRoot(), nodes);

	for (Node *i : nodes) {
		std::cout << i->key << " ";
		if (i->key % 2 != 0) {
			deleteNodes.push_back(i);
			std::cout << "(deleting)" << std::endl;
		}
		else { std::cout << std::endl; }
	}

	Node& checkLeak = *root;
	std::cout << std::endl << checkLeak.key << std::endl;
	root = delOddLeafHelper(deleteNodes, getRoot());
	std::cout << checkLeak.key << std::endl << std::endl;
}
/*
PRIVATE METHODS:
*/


//   This function will add the data in the tree rooted at currNode.
//   Call this function from insert().


Node *BST::insertHelper(Node *currNode, int data) {
	if (currNode == NULL) {
		return createNode(data);
	}
	else
		if (currNode->key < data) {
			currNode->right         = insertHelper(currNode->right, data);
			currNode->right->parent = currNode;
		}
		else
			if (currNode->key > data) {
				currNode->left         = insertHelper(currNode->left, data);
				currNode->left->parent = currNode;
			}
	return currNode;
}

// This function will search the data in a tree.
// Call this function from searchKey().

Node *BST::searchKeyHelper(Node *currNode, int data) {
	if (currNode == NULL)
		return NULL;

	if (currNode->key == data)
		return currNode;

	if (currNode->key > data)
		return searchKeyHelper(currNode->left, data);

	return searchKeyHelper(currNode->right, data);
}

// This function will destroy the subtree rooted at currNode.


void BST::destroySubTree(Node *currNode) {
	if (currNode != NULL) {
		destroySubTree(currNode->right);
		destroySubTree(currNode->left);

		delete currNode;
		currNode = NULL;
	}
}

// This function will traverse the tree in-order and print out the node elements.
// printTree() function will call this function.

void BST::printTreeHelper(Node *currNode) {
	if (currNode) {
		printTreeHelper(currNode->left);
#if DEBUG_PRINT_TREE_HELPER
		cout << "Node " << currNode->key << ":\n   left child: ";
		if (currNode->left)
			cout << currNode->left->key;
		else
			cout << "null ";
		cout << "\n   right child: ";
		if (currNode->right)
			cout << currNode->right->key;
		else
			cout << "null ";
		cout << "\n   parent: ";
		if (currNode->parent)
			cout << currNode->parent->key << endl;
		else
			cout << "null " << endl;
#else
		cout << " "<< currNode->key;
#endif

		printTreeHelper(currNode->right);
	}
}

bool BST::isBST(Node *root) {
	if (root == NULL) {
		return true;
	}
	if (root->left != NULL && root->key < root->left->key)
		return false;

	if (root->right != NULL && root->key >= root->right->key)
		return false;

	if (!isBST(root->right) || !isBST(root->left))
		return false;

	return true;
}

// Create a new node, setting key value to  input data
// and all pointers to null.
Node *BST::createNode(int data) {
	Node *newNode = new Node;
	newNode->key    = data;
	newNode->parent = NULL;
	newNode->left   = NULL;
	newNode->right  = NULL;
	return newNode;
}

Node *BST::getRoot() {
	return root;
}


/*
   Prints a binary tree in a 2D fashion.
Note: The image of the tree is left rotated by 90 degrees.
*/
void BST::print2DUtilHelper(Node *currNode, int space) {
	// Base case
	if (currNode == NULL)
		return;

	// Increase distance between levels
	space += COUNT;

	// Process right child first
	print2DUtilHelper(currNode->right, space);

	// Print current node after space
	// count
	printf("\n");
	for (int i = COUNT; i < space; i++)
		printf(" ");
	printf("%d\n", currNode->key);

	// Process left child
	print2DUtilHelper(currNode->left, space);
}

void BST::inorderHelper(Node *currNode, vector<int> &inorder) {
	if (currNode == NULL)
		return;
	inorderHelper(currNode->left, inorder);
	inorder.push_back(currNode->key);
	inorderHelper(currNode->right, inorder);
}
