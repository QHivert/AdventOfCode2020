/*
 * Day16.cpp
 *
 *  Created on: 21 Dec 2020
 *      Author: Hivert Quentin
 */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <numeric>
#include "days.hpp"
#include "utils.hpp"
using namespace std;

class Field
{
public:
	string name;
	pair<int, int> firstRange;
	pair<int, int> secondRange;
	set<int> okPos;
	set<int> notOkPos;


	Field(){
		name = "";
		firstRange = make_pair(0,0);
		secondRange = make_pair(0,0);
		okPos = {};
		notOkPos = {};
	}

	Field(string line) {
		vector<string> splitLine = splitString(line, ": ");
		vector<string> splitRanges = splitString(splitLine[1], " or ");
		vector<string> splitFirst = splitString(splitRanges[0], "-");
		vector<string> splitSecond = splitString(splitRanges[1], "-");
		name = splitLine[0];
		firstRange = make_pair(stoi(splitFirst[0]),stoi(splitFirst[1]));
		secondRange = make_pair(stoi(splitSecond[0]),stoi(splitSecond[1]));
		okPos = {};
		notOkPos = {};
	}

	bool checkValue(int value) {
		return (firstRange.first<=value && value<=firstRange.second) || (secondRange.first<=value && value<=secondRange.second);
	}

	void checkValue(int value, int pos) {
		bool isValid = (firstRange.first<=value && value<=firstRange.second) || (secondRange.first<=value && value<=secondRange.second);
		if(isValid) {
			if(notOkPos.find(pos)==notOkPos.end()) {
				okPos.insert(pos);
			}
		}
		else {
			notOkPos.insert(pos);
			if(okPos.find(pos)!=okPos.end()) {
				okPos.erase(pos);
			}
		}
	}

	void printFieldPos() {
		cout << name << ": ";
		cout << (*okPos.begin()) << endl;
	}
};

class Ticket
{
public:
	vector<Field> fields;

	Ticket() {
		fields = {};
	}

	void addField(string line) {
		fields.push_back(Field(line));
	}

	bool chekValueAllFields(int value) {
		int ret = 0;
		for(Field f: fields) {
			ret += f.checkValue(value);
		}
		return ret;
	}

	bool isNotValid(vector<string> values) {
		int ret = 0;
		for(string value: values) {
			ret += chekValueAllFields(stoi(value));
		}
		return ret;
	}

	void printAllFieldPos() {
		for(Field f: fields) {
			f.printFieldPos();
		}
	}
};

void day16() {
	cout << "Day 16 start" << endl;

	ifstream input;
	input.open("inputs/day16.txt");

	const int FIELD          = 0;
	const int MY_TICKET      = 1;
	const int NEARBY_TICKETS = 2;

	if(input.is_open()) {

		string line;
		int i = 0;
		Ticket ticket = Ticket();
		vector<int> wrongValues;


		while(getline(input, line)) {
			if(line.length() == 0){
				//Empty line
				i++;
				continue;
			}
			else if(i==FIELD) {
				ticket.addField(line);
			}
			else if(i==MY_TICKET) {
				continue;
			}
			else if(i==NEARBY_TICKETS) {
				if(line=="nearby tickets:") continue;
				vector<string> splitLine = splitString(line, ",");
				for(int k=0; k<(int)splitLine.size(); k++) {
					if(!ticket.chekValueAllFields(stoi(splitLine[k]))) {
						wrongValues.push_back(stoi(splitLine[k]));
					}
				}
				if(!ticket.isNotValid(splitLine)) {
					for(int k=0; k<(int)splitLine.size(); k++) {
						for(Field &field: ticket.fields) {
							field.checkValue(stoi(splitLine[k]), k);
						}
					}
				}
			}
		}
		cout << "There are " << wrongValues.size() << " wrong values in all those tickets" << endl;
		cout << "The answer for part one is " << accumulate(wrongValues.begin(), wrongValues.end(), 0) << endl << endl;
		ticket.printAllFieldPos();

	}

	cout << "Day 16 end" << endl;
}


