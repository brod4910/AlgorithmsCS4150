#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <algorithm>
#include <string>
#include <map>
#include <vector>
#include <sstream>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <ctime>
#include <climits>
#include <iomanip>
#include <queue>

using namespace std;

struct Node {
	int value;
	Node* Left = NULL;
	Node* Right = NULL;
};

struct Tree {
	Node* root;
};

int checkEqual(vector<int*>, int , int );
bool areSimilar(Node* rootR, Node* rootL);
Node* createNode(int value);
Tree createTree(int* ptree, int k);
Node* insertNode(Node* root, int);
void printTree(Node* root);
int checkSimilarities(vector<Tree> trees, int n);
void postorder(Node* , int);

int main (int argc, char* argv[])
{
	string n_k, str, buf;
    vector<int*> pretree; // Create vector to hold preprocessed trees
    vector<Tree> trees;
    queue<string> strbuffs;
	char sizes[2048];
	int n, k;

	// get n and k
	cin.getline(sizes, 2048);

	// make the first line a string
	n_k += sizes;

	// extract both n and k respectively
	n = stoi(n_k.substr(0, n_k.find(" ")));
	k = stoi(n_k.substr(n_k.find(" "), n_k.length()));

    for(int i = 0; i < n;i++)
    {
    	getline(cin, str);
    	strbuffs.push(str);
    }

    for(int i = 0; i < n; i++)
    {
    	int* treebuff = (int*)calloc(k, sizeof(int));
    	stringstream ss(strbuffs.front()); // Insert the string into a stream

    	for(int j = 0; j < k; j++)
    	{
    		ss >> buf;
    		treebuff[j] = stoi(buf);
    	}

    	strbuffs.pop();
    	trees.push_back(createTree(treebuff, k));
    	delete treebuff;
    }

    cout << checkSimilarities(trees, n);
}

int checkSimilarities(vector<Tree> trees, int n)
{
	for(int i = 0; i < trees.size(); i++)
	{
		for(int j = i + 1; j < trees.size(); j++)
		{
			if(areSimilar(trees[i].root, trees[j].root))
			{
				trees.erase(trees.begin()+i);
				i = 0;
				j = 0;
			}
		}
	}
	return trees.size();
}

/*
 * Checks to see if the Nodes are similar in structure
 */
bool areSimilar(Node* rootL, Node* rootR)
{
	if (rootL == NULL && rootR == NULL) 
	{
		return true;
	}

	if (rootL == NULL || rootR == NULL) 
	{
		return false;
	}

	return (areSimilar(rootL->Left, rootR->Left) && areSimilar(rootL->Right, rootR->Right));
}

/*
 * Creates a new node from the given value
 */
Node* createNode(int value)
{
	Node* node = new Node;
	node->value = value;
	return node;
}

/*
 * Creates a tree from the given array of ints
 */
Tree createTree(int* ptree, int k)
{
	Tree tree;
	tree.root = createNode(ptree[0]);

	for(int i = 1; i < k; i++)
	{
		insertNode(tree.root, ptree[i]);
	}

	return tree;
}

/*
 * Inserts a new node with the specified value
 */
Node* insertNode(Node* root, int value)
{
    if (root == NULL) 
    {
    	return createNode(value);
    }
 
    if (value < root->value)
    {
        Node *lNode = insertNode(root->Left, value);
        root->Left  = lNode;
    }
    else if (value > root->value)
    {
        Node *rNode = insertNode(root->Right, value);
        root->Right  = rNode;
    }
 
    return root;
}

/*
 * Print the from left to right
 */
void printTree(Node* root)
{
	if(root == NULL)
	{
		return;
	}

	printTree(root->Left);
    cout<<root->value<<' ';
    printTree(root->Right);
}

/*
 * Sanity Checker. Not my code. Was taken from stackoverflow
 */
void postorder(Node* p, int indent)
{
    if(p != NULL) 
    {
        if(p->Right) 
        {
            postorder(p->Right, indent+4);
        }
        if (indent) 
        {
            std::cout << setw(indent) << ' ';
        }
        if (p->Right) 
        {
        	std::cout<<" /\n" << setw(indent) << ' ';
    	}	

        std::cout<< p->value << "\n ";

        if(p->Left) 
        {
            std::cout << setw(indent) << ' ' <<" \\\n";
            postorder(p->Left, indent+4);
        }
    }
}