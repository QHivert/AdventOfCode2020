//============================================================================
// Name        : Day1.cpp
// Author      : Quentin Hivert
// Version     :
// Copyright   : Your copyright notice
// Description : First day of Advent of code 2020
//============================================================================

#include <iostream>
#include <vector>
#include "days.hpp"
using namespace std;

int find2020in2parts(fstream& input) {
	vector<int> expenses;
	int expense;

	while(input >> expense) {
		expenses.push_back(expense);
		int toFind = 2020 - expense;
		for (auto i: expenses) {
			if(toFind == i) {
				return expense * i;
			}
		}
	}

	return 0;
}

int find2020in3parts(fstream& input) {
	vector<int> expenses;
	int expense1;

	while(input >> expense1) {
		expenses.push_back(expense1);
		int expense2 = 2020 - expense1;
		for (auto i: expenses) {
			int expense3 = expense2 - i;
			for (auto j: expenses) {
				if(expense3 == j) {
					return expense1 * i * j;
				}
			}
		}
	}
	return 0;
}

void day1() {
	cout << "Day 1 start:" << endl;

	fstream moduleFile;
	moduleFile.open("inputs/day1.txt");

	if(moduleFile.is_open()) {
		int result = find2020in2parts(moduleFile);
		cout << "Result for part one is " << result << endl;
		moduleFile.close();

	}

	fstream moduleFile2;
	moduleFile2.open("inputs/day1.txt");

	if(moduleFile2.is_open()) {
		int result = find2020in3parts(moduleFile2);
		cout << "Result for part two is " << result << endl;
		moduleFile2.close();

	}


	cout << "Day 1 end!" << endl;
}
