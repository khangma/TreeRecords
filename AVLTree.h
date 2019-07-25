#pragma once
#include <iostream>
#include "LinkedList.h"
#include "Date.h"
#include "Student.h"
using namespace std;

template<class Type>
struct AVLNode
{
	Type key;
	linkedList index;
	int bfactor; //balance factor
	AVLNode<Type> *llink;
	AVLNode<Type> *rlink;
};

template <class Type> class AVLTree {
private:
	AVLNode<Type> * root;

public:
	AVLTree() {
		root = NULL;
	}
	~AVLTree() {
		destroyTree(root);
	}

	void destroyTree(AVLNode<Type> *leaf) {
		if (leaf == NULL) {
			return;
		}
		destroyTree(leaf->llink);
		destroyTree(leaf->rlink);
		leaf->index.reset();
		delete leaf;
	}
	//Rotate the subtree to the left
	void rotateToLeft(AVLNode<Type>* &root)
	{
		AVLNode<Type> *p; //pointer to the root of the
						   //right subtree of root
		if (root == NULL)
			cerr << "Error in the tree" << endl;
		else if (root->rlink == NULL)
			cerr << "Error in the tree:"
			<< " No right subtree to rotate." << endl;
		else
		{
			p = root->rlink;
			root->rlink = p->llink; //the left subtree of p becomes
									//the right subtree of root
			p->llink = root;
			root = p; //make p the new root node
		}
	}//rotateLeft

	//Rotate the subtree to the right
	void rotateToRight(AVLNode<Type>* &root)
	{
		AVLNode<Type> *p; //pointer to the root of
						   //the left subtree of root
		if (root == NULL)
			cerr << "Error in the tree" << endl;
		else if (root->llink == NULL)
			cerr << "Error in the tree:"
			<< " No left subtree to rotate." << endl;
		else
		{
			p = root->llink;
			root->llink = p->rlink; //the right subtree of p becomes
									//the left subtree of root
			p->rlink = root;
			root = p; //make p the new root node
		}
	}//end rotateRight


	void balanceFromLeft(AVLNode<Type>* &root)
	{
		AVLNode<Type> *p;
		AVLNode<Type> *w;
		p = root->llink; //p points to the left subtree of root
		switch (p->bfactor)
		{
		case -1:
			root->bfactor = 0;
			p->bfactor = 0;
			rotateToRight(root);
			break;
		case 0:
			cerr << "Error: Cannot balance from the left." << endl;
			break;
		case 1:
			w = p->rlink;
			switch (w->bfactor) //adjust the balance factors
			{
			case -1:
				root->bfactor = 1;
				p->bfactor = 0;
				break;
			case 0:
				root->bfactor = 0;
				p->bfactor = 0;
				break;
			case 1:
				root->bfactor = 0;
				p->bfactor = -1;
			}//end switch
			w->bfactor = 0;
			rotateToLeft(p);
			root->llink = p;
			rotateToRight(root);
		}//end switch;
	}//end balanceFromLeft


	void balanceFromRight(AVLNode<Type>* &root)
	{
		AVLNode<Type> *p;
		AVLNode<Type> *w;
		p = root->rlink; //p points to the left subtree of root
		switch (p->bfactor)
		{
		case -1:
			w = p->llink;
			switch (w->bfactor) //adjust the balance factors
			{
			case -1:
				root->bfactor = 0;
				p->bfactor = 1;
				break;
			case 0:
				root->bfactor = 0;
				p->bfactor = 0;
				break;
			case 1:
				root->bfactor = -1;
				p->bfactor = 0;
			}//end switch
			w->bfactor = 0;
			rotateToRight(p);
			root->rlink = p;
			rotateToLeft(root);
			break;
		case 0:
			cerr << "Error: Cannot balance from the left." << endl;
			break;
		case 1:
			root->bfactor = 0;
			p->bfactor = 0;
			rotateToLeft(root);
		}//end switch;
	}//end balanceFromRight


	void insertIntoAVL(AVLNode<Type>* &root,
		AVLNode<Type> *newNode, bool& isTaller)
	{
		if (root == NULL)
		{
			root = newNode;
			isTaller = true;
		}
		else if (root->key == newNode->key) {
			root->index.insertSorted(newNode->index.getIndex());
			newNode->index.reset();
			delete newNode;
		}
		else if (root->key > newNode->key) //newItem goes in
											 //the left subtree
		{
			insertIntoAVL(root->llink, newNode, isTaller);
			if (isTaller) //after insertion, the subtree grew in height
				switch (root->bfactor)
				{
				case -1:
					balanceFromLeft(root);
					isTaller = false;
					break;
				case 0:
					root->bfactor = -1;
					isTaller = true;
					break;
				case 1:
					root->bfactor = 0;
					isTaller = false;
					break;
				}//end switch
		}//end if
		else
		{
			insertIntoAVL(root->rlink, newNode, isTaller);
			if (isTaller) //after insertion, the subtree grew in
						  //height
				switch (root->bfactor)
				{
				case -1:
					root->bfactor = 0;
					isTaller = false;
					break;
				case 0:
					root->bfactor = 1;
					isTaller = true;
					break;
				case 1:
					balanceFromRight(root);
					isTaller = false;
				}//end switch
		}//end else
	}//insertIntoAVL


	void insert(const Type &newItem, int index)
	{
		bool isTaller = false;
		AVLNode<Type> *newNode;
		newNode = new AVLNode<Type>;
		newNode->key = newItem;
		newNode->index.insertSorted(index);
		newNode->bfactor = 0;
		newNode->llink = NULL;
		newNode->rlink = NULL;
		insertIntoAVL(root, newNode, isTaller);
	}
	void search(const Type key, int &indexAccess) {
		indexAccess++;
		while (root != NULL) {
			if (key == root->key) {
				indexAccess++;
				break;
			}
			else if (key < root->key) {
				indexAccess++;
				root = root->llink;
			}
			else if (key > root->key) {
				indexAccess++;
				root = root->rlink;
			}
		}
		
	}
};