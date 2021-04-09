#include <iostream>
#include "BST.h"

using namespace std;

int main (int argc, char* argv[]){
	cout<<"Creating tree"<<endl;
	BST tree2;
	tree2.insert(5);
	tree2.insert(3);
	tree2.insert(8);
	tree2.insert(6);
	tree2.insert(15);
	tree2.insert(10);
	tree2.insert(17);


	/*
				5
			/       \
		  3           8
					/   \
				  6       15
						 /  \
						10  17
	*/
	tree2.print2DUtil(1);

	tree2.delOddLeaf();

	vector<int> inorder2 = tree2.inorderTree();
	for(int i=0;i<inorder2.size();i++)
	{
		cout<<inorder2[i]<<" ";
	}
	cout<<endl;
	cout<<tree2.isValidBST()<<endl;
	return 0;

}
