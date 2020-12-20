//============================================================================
// Name        : Day2.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "utils.hpp"
#include "days.hpp"

using namespace std;

int findValidPasswordPart1(fstream& input) {
	int valid = 0;
	string limits;
	string restriction;
	string password;

	while(input >> limits >> restriction >> password) {
		vector<string> splitLimits = splitString(limits, "-");
		int min = stoi(splitLimits[0]);
		int max = stoi(splitLimits[1]);
		char letter = restriction[0];

		int nbOccurence = count(password.begin(), password.end(), letter);

		if((min <= nbOccurence) & (nbOccurence <= max)) {
			valid++;
		}
	}
	return valid;
}

int findValidPasswordPart2(fstream& input) {
	int valid = 0;
	string positions;
	string restriction;
	string password;

	while(input >> positions >> restriction >> password) {
		vector<string> splitPositions = splitString(positions, "-");
		int first = stoi(splitPositions[0]);
		int second = stoi(splitPositions[1]);
		char letter = restriction[0];

		bool firstPos = password[first-1] == letter;
		bool secondPos = password[second-1] == letter;
		if(firstPos ^ secondPos) {
			valid++;
		}
	}
	return valid;
}

void day2() {
	cout << "Day 2 start" << endl;


	fstream passwordFile;
	passwordFile.open("inputs/day2.txt");

	if(passwordFile.is_open()) {
		int result = findValidPasswordPart1(passwordFile);
		cout << "Result for part one is " << result << endl;
		passwordFile.close();
	}

	fstream passwordFile2;
	passwordFile2.open("inputs/day2.txt");

	if(passwordFile2.is_open()) {
		int result = findValidPasswordPart2(passwordFile2);
		cout << "Result for part two is " << result << endl;
		passwordFile2.close();
	}

	cout << "Day 2 end" << endl;
}
