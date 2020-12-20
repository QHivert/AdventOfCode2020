//============================================================================
// Name        : Day6.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <vector>
#include "days.hpp"

using namespace std;

void day6() {
	cout << "Day 6 start" << endl;

	ifstream answers;
	answers.open("inputs/day6.txt");
	if(answers.is_open()) {

		string line;
		int isYes    = 0; //questions answered yes
		int isAllYes = 0; //questions answered yes by all group
		set<char> questions;
		set<char> questionsAll;
		bool firstMember = true;

		while(getline(answers, line)) {

			if(line.length() == 0){
				// New group
				isYes += questions.size();
				questions.clear();
				firstMember = true;
				isAllYes += questionsAll.size();
				questionsAll.clear();
				continue;
			}
			for(char c: line) {
				questions.insert(c);
				if(firstMember)
					questionsAll.insert(c);
			}
			if(!firstMember) {
				set<char> tempSet = questionsAll;
				for(char c: tempSet) {
					if(line.find(c)==string::npos) {
						questionsAll.erase(c);
					}
				}
			}
			firstMember = false;

		}

		isYes += questions.size();
		isAllYes += questionsAll.size();

		cout << "All groups answered yes to " << isYes << " questions!" << endl;
		cout << "All groups answered collectively yes to " << isAllYes << " questions!" << endl;

		answers.close();
	}

	cout << "Day 6 end" << endl;
}
