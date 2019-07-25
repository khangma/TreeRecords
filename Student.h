#pragma once
#include <iostream>
#include "LinkedList.h"
#include "Date.h"
#include <sstream>
#include <cstdio>
#include <string>
using namespace std;

class Student {
private:
	string studentID;
	string firstName;
	string lastName;
	string major;
	float GPA;
	Date DOB;
public:
	Student() {
		studentID = "";
		firstName = "";
		lastName = "";
		major = "";
		GPA = 0.0;
		DOB = Date();
	}
	Student(string iD, string fName, string lName, string Major,
		float grade, string dateOB) {
		studentID = iD;
		firstName = fName;
		lastName = lName;
		major = Major;
		GPA = grade;
		DOB = Date(dateOB);
	}

	string getID() {
		return studentID;
	}
	string getFName() {
		return firstName;
	}
	string getLName() {
		return lastName;
	}
	string getMajor() {
		return major;
	}
	float getGPA() {
		return GPA;
	}
	Date getDOB() {
		return DOB;
	}
	void print() {
		cout << studentID << ", ";
		cout << firstName << ", ";
		cout << lastName << ", ";
		cout << DOB.toString() << ", ";
		cout << GPA << ", ";
		cout << major << endl;
	}
};