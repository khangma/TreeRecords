#pragma once
#include <iostream>

using namespace std;

struct Node {
public:
	int index;
	Node *next;
};

class linkedList {
private:
	Node * first;	//pointer to the first node of the list
	int length;
public:
	linkedList() {
		first = NULL;
	}

	~linkedList() {
		reset();
	}

	bool isEmpty() {
		return first == NULL;
	}
	int getIndex() {
		return first->index;
	}
	void print() {
		Node *current = first;
		if (isEmpty()) {
			cout << "<Empty>";
		}
		else {
			while (current != NULL) {
				cout << current->index << " ";
				current = current->next;
			}
		}
		cout << endl;
	}

	void reset() {
		Node * temp;
		while (first != NULL) {
			temp = first;
			first = first->next;
			delete temp;
		}
	}
	Node* getNext(Node* node) {
		return node->next;
	}
	Node* getHead() {
		return first;
	}
	int getlength() {
		return length;
	}
	void insertSorted(int in) {
		Node* newNode = new Node;
		newNode->index = in;
		newNode->next = NULL;
		
		/* Special case for the head end */
		if (first == NULL || first->index >= newNode->index)
		{
			newNode->next = first;
			first = newNode;
			length++;
		}
		else
		{
			/* Locate the node before the point of insertion */
			Node* current;
			current = first;
			while (current->next != NULL &&
				current->next->index < newNode->index)
			{
				current = current->next;
			}
			newNode->next = current->next;
			current->next = newNode;
			length++;
		}
	}
};