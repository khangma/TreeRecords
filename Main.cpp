#include <iostream>
#include <fstream>
#include <sstream>
#include "Student.h"
#include "ArrayList.h"
#include "LinkedList.h"
#include "AVLTree.h"
#include "ArgumentManager.h"
#include <iomanip>
using namespace std;

string toString(ArrayList& list, int index) {
	string output;
	float g = list.gpa(index);
	stringstream stream;
	stream << fixed << setprecision(2) << g;
	string gpa = stream.str();
	output += list.ID(index) + ", " + list.fName(index) + ", " + list.lName(index)
		+ ", " + list.dob(index).toString() + ", " + list.major(index) + ", " + gpa; //+to_string(list.gpa(index));
	return output;
}

int main(int argc, char* argv[]) {
	if (argc < 2) {
		cout << "Usage: main \"A=<file>;C=<file>\"" << endl;
		return -1;
	}

	// get input and output file names from arguments
	ArgumentManager am(argc, argv);
	string infilename = am.get("A");
	string infile2name = am.get("B");
	string outfilename = am.get("C");

	cout << "File name for matrix A: " << infilename << endl
		<< "File name for matrix B: " << infile2name << endl
		<< "File name for matrix C: " << outfilename << endl;

	ifstream inFile(infilename);
	ifstream inFile2(infile2name);
	ofstream outFile(outfilename);

	string input;
	Student student;
	ArrayList list;
	int access = 0;
	bool found;
	int indexAccess = 0;

	//getting info from the first txt file
	while (!inFile.eof()) {
		getline(inFile, input);
		stringstream ss(input);
		string ID;
		getline(ss, ID, ',');
		string fName;
		ss.ignore();
		getline(ss, fName, ',');
		string lName;
		ss.ignore();
		getline(ss, lName, ',');
		string dob;
		ss.ignore();
		getline(ss, dob, ',');
		string major;
		ss.ignore();
		getline(ss, major, ',');
		string gpa;
		ss.ignore();
		getline(ss, gpa, ',');
		float GPA = stof(gpa);
		student = Student(ID, fName, lName, major, GPA, dob);
		//load the student object into the arrayList
		list.insert(student);
	}

	AVLTree<string> fName;
	AVLTree<string> lName;
	AVLTree<string> major;
	AVLTree<float> gpa;
	AVLTree<Date> dob;

	//inserting all into tree
	for (int i = 0; i < list.listSize(); i++) {
		fName.insert(list.fName(i), i);
		lName.insert(list.lName(i), i);
		major.insert(list.major(i), i);
		gpa.insert(list.gpa(i), i);
		dob.insert(list.dob(i), i);
	}
	while (!inFile2.eof()) {
		string searchInput;
		getline(inFile2, searchInput);
		stringstream ss2(searchInput);
		string searchType;
		getline(ss2, searchType, ':');
		string searchValue;
		ss2.ignore();
		getline(ss2, searchValue);
		string output;
		bool result = false;
		if (searchType == "ID") {
			int index = list.binSearch(searchValue, access);
			if (index != -1) {
				result = true;
				output = toString(list, index);
				outFile << output << endl;
				outFile << "Without index: " << access << " accesses";
				outFile << endl;
			}
		}
		else if (searchType == "MAJOR") {
			major.search(searchValue, indexAccess);
			while (access <= list.listSize()) {
				list.seqSearch(searchType, searchValue, found, access);

				if (found) {
					result = true;
					output = toString(list, access - 1);
					outFile << output << endl;
					outFile << "Without index: " << access << " accesses" << endl;
					outFile << "With index: " << indexAccess << " accesses" << endl;
					outFile << endl;
				}
				else {
					access++;
					continue;
				}
			}
		}
		else if (searchType == "FIRSTNAME") {
			fName.search(searchValue, indexAccess);
			while (access <= list.listSize()) {
				list.seqSearch(searchType, searchValue, found, access);

				if (found) {
					result = true;
					output = toString(list, access - 1);
					outFile << output << endl;
					outFile << "Without index: " << access << " accesses" << endl;
					outFile << "With index: " << indexAccess << " accesses" << endl;
					outFile << endl;
				}
				else {
					access++;
					continue;
				}
			}
		}
		else if (searchType == "LASTNAME") {
			lName.search(searchValue, indexAccess);
			while (access <= list.listSize()) {
				list.seqSearch(searchType, searchValue, found, access);

				if (found) {
					result = true;
					output = toString(list, access - 1);
					outFile << output << endl;
					outFile << "Without index: " << access << " accesses" << endl;
					outFile << "With index: " << indexAccess << " accesses" << endl;
					outFile << endl;
				}
				else {
					access++;
					continue;
				}
			}
		}
		else if (searchType == "GPA") {
			float value = stof(searchValue);
			gpa.search(value, indexAccess);
			while (access <= list.listSize()) {
				list.seqSearch(searchType, searchValue, found, access);

				if (found) {
					result = true;
					output = toString(list, access - 1);
					outFile << output << endl;
					outFile << "Without index: " << access << " accesses" << endl;
					outFile << "With index: " << indexAccess << " accesses" << endl;
					outFile << endl;
				}
				else {
					access++;
					continue;
				}
			}
		}
		else if (searchType == "DOB") {
			Date dOB = Date(searchValue);
			dob.search(dOB, indexAccess);
			while (access <= list.listSize()) {
				list.seqSearch(searchType, searchValue, found, access);

				if (found) {
					result = true;
					output = toString(list, access - 1);
					outFile << output << endl;
					outFile << "Without index: " << access << " accesses" << endl;
					outFile << "With index: " << indexAccess << " accesses" << endl;
					outFile << endl;
				}
				else {
					access++;
					continue;
				}
			}
		}

		if (!result) {
			if (searchType == "ID") {
				outFile << "No record found for " << searchType << searchValue << endl;
				outFile << "Without index: " << access << " accesses" << endl;
			}
			if (searchType != "ID") {
				outFile << "No record found for " << searchType << searchValue << endl;
				outFile << "Without index: " << access - 1 << " accesses" << endl;
				outFile << "With index: " << indexAccess << " accesses" << endl;
			}
			outFile << endl;
		}
	}

	system("pause");
	return 0;
}

