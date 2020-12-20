//============================================================================
// Name        : Day5.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string>
#include <set>
#include "days.hpp"
#include "utils.hpp"
using namespace std;

auto seatId = [](int row, int column){return row*8+column;};

int evaluateRow(string str) {
	int row = 0;
	for(int i=0; i<7; i++) {
		row += power(str[i]=='B', 6-i); //6 because 127 is 0b111 1111 so the max bit is 2^6
	}
	return row;
}

int evaluateColumn(string str) {
	int row = 0;
	for(int i=7; i<(int)str.size(); i++) {
		row += power(str[i]=='R', 2-(i-7)); //2 because 7 is 0b111 so the max bit is 2^2
	}
	return row;
}

void day5() {
	cout << "Day 5 start" << endl;

	fstream seats;
	seats.open("inputs/day5.txt");

	if(seats.is_open()) {
		string line;
		int maxId = 0;
		int minId = 127*8+7;
		set<int> seatsTaken;

		while(seats >> line) {
			int tempId = seatId(evaluateRow(line), evaluateColumn(line));
			if(tempId > maxId)
				maxId = tempId;
			if(tempId < minId)
				minId = tempId;
			seatsTaken.insert(tempId);
		}

		cout << "The maximum seat ID is " << maxId << endl;
		cout << "The minimum seat ID is " << minId << endl;

		for(int i=minId; i<=maxId; i++) {
			if(seatsTaken.find(i)==seatsTaken.end())
				cout << "The seat " << i << " is available." << endl;
		}

		seats.close();
	}

	cout << "Day 5 end" << endl;
}
