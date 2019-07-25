#pragma once
#include <iostream>
#include <string>
#include "Student.h"
#include "AVLTree.h"
#include "Date.h"
using namespace std;

class ArrayList {
private:
	Student * list;
	int maxSize;
	int length;
public:
	ArrayList(int size) { // constructor
		list = new Student[size];
		maxSize = size;
		length = 0;
	}

	ArrayList() { // default constructor
		list = new Student[100];
		maxSize = 100;
		length = 0;
	}

	~ArrayList() { // destructor
		delete[] list;
	}
	void clear() {
		delete[] list;
	}

	int listSize() {
		return length;
	}

	int maxListSize() {
		return maxSize;
	}

	void print() {
		for (int i = 0; i < length; i++) {
			list[i].print();
		}
	}
	void print(int index) {
		list[index].print();
	}

	bool isEmpty() {
		return (length == 0);
	}

	bool isFull() {
		return (length == maxSize);
	}

	void insert(Student insertItem) {
		if (isEmpty()) {
			list[length++] = insertItem;
		}
		else if (isFull()) {
			cout << "Cannot insert in a full list." << endl;
		}
		else {
			int i = 0;
			while (list[i].getID() < insertItem.getID() && i < length) {
				i++;
			}

			if (i == length) {
				list[i] = insertItem;
				length++;
			}
			else {
				for (int j = length; j > i; j--) {
					list[j] = list[j - 1];
				}
				list[i] = insertItem;
				length++;
			}
		}
	}

	int binSearch(string ID, int &access) {
		int first, last, mid;
		first = 0; last = length - 1; mid = (first + last) / 2;
		if (last < 1)
			return -1;
		while (first <= last) {
			access++;
			mid = (first + last) / 2;
			if (ID == list[mid].getID()) {
				access++;
				return mid;
			}
			else if (ID < list[mid].getID()) {
				last = mid - 1;
			}
			else if (ID > list[mid].getID()) {
				first = mid + 1;
			}
		}
		return -1;
	}

	void seqSearch(string searchType, string searchValue, bool &found, int &access) {
		found = false;
		int i = access;
		if (searchType == "FIRSTNAME") {
			for (; i < length; i++) {
				access++;
				if (list[i].getFName() == searchValue) {
					found = true;
					break;
				}
				else
					continue;

			}
		}
		else if (searchType == "LASTNAME") {
			for (; i < length; i++) {
				access++;
				if (list[i].getLName() == searchValue) {
					found = true;
					break;
				}
				else
					continue;
			}
		}
		else if (searchType == "GPA") {
			float key = stof(searchValue);
			for (; i < length; i++) {
				access++;
				if (list[i].getGPA() == key) {
					found = true;
					break;
				}
				else
					continue;
			}
		}
		else if (searchType == "MAJOR") {
			for (; i < length; i++) {
				access++;
				if (list[i].getMajor() == searchValue){
					found = true;
					break;
				}
				else
					continue;
			}
		}
		else if (searchType == "DOB") {
			Date date = Date(searchValue);
			for (; i < length; i++) {
				access++;
				if (list[i].getDOB() == date) {
					found = true;
					break;
				}
				else
					continue;
			}
		}
	}

	//a bunch of get functions
	string ID(int index) {
		return list[index].getID();
	}
	string fName(int index) {
		return list[index].getFName();
	}
	string lName(int index) {
		return list[index].getLName();
	}
	string major(int index) {
		return list[index].getMajor();
	}
	float gpa(int index) {
		return list[index].getGPA();
	}
	Date dob(int index) {
		return list[index].getDOB();
	}
};