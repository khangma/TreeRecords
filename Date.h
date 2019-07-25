#pragma once
#include <iostream>
#include <string>
using namespace std;

class Date {
private:
	int day;
	int month;
	int year;
public:

	//default constructor
	Date() {
		day = 0;
		month = 0;
		year = 0;
	}

	//constructor with parameters
	Date(string dateOB) {
		stringstream ss(dateOB);
		string token;
		getline(ss, token, '-');
		year = stoi(token);
		getline(ss, token, '-');
		month = stoi(token);
		getline(ss, token);
		day = stoi(token);
	}
	int getYear() {
		return year;
	}
	int getMonth() {
		return month;
	}
	int getDay() {
		return day;
	}

	//this function converts the int values into one string
	string toString() {
		string DOB = "";
		DOB += to_string(year) + "-";
		if (month < 10) {
			if (day < 10)
				DOB += "0" + to_string(month) + "-" + "0" + to_string(day);
			else
				DOB += "0" + to_string(month) + "-" + to_string(day);
		}
		else {
			if (day < 10)
				DOB += to_string(month) + "-" + "0" + to_string(day);
			else
				DOB += to_string(month) + "-" + to_string(day);
		}
		return DOB;
	}

	//overloading the operator >= for comparison of DOB
	bool operator>(const Date &d) const {
		if (this->year > d.year)
			return true;						//if the year is greater
		else if (this->year == d.year)			//if the year is the same
			if (this->month > d.month)
				return true;					//if month is greater
			else if (this->month == d.month)	//when the month is the same
			{
				if (this->day > d.day)			//if the day larger than or equal
					return true;
				else
					return false;				//if the day is smaller
			}
			else
				return false;					//if the month is smaller
		else
			return false;					//if the year is smaller

	}

	bool operator<(const Date &d) const {
		if (this->year < d.year)
			return true;						//if the year is greater
		else if (this->year == d.year)			//if the year is the same
			if (this->month < d.month)
				return true;					//if month is greater
			else if (this->month == d.month)	//when the month is the same
			{
				if (this->day < d.day)			//if the day larger than or equal
					return true;
				else
					return false;				//if the day is smaller
			}
			else
				return false;					//if the month is smaller
		else
			return false;
	}

	bool operator==(const Date &d) const {
		if (this->year == d.year)
			if (this->month == d.month)
				if (this->day == d.day)
					return true;
				else
					return false;
			else
				return false;
		else
			return false;
	}
};