/*
 * Day15.cpp
 *
 *  Created on: 20 Dec 2020
 *      Author: Hivert Quentin
 */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <set>
#include "days.hpp"
#include "utils.hpp"
using namespace std;


void day15() {
	cout << "Day 15 start" << endl;

	vector<int> input = {0,14,6,20,1,4};

	unordered_map<int, int> spoken; // {number, lastRoundSpoken}
	for(int i=0; i<(int)input.size(); i++) {
		spoken.insert({input[i], i});
	}

	input.push_back(0);

	int index = (int)input.size();

	while(index <= 30000000) {
		int last_round = input[index-1];
		auto findlastspoken = spoken.find(last_round);
		if(findlastspoken!=spoken.end()) {
			int lastspoken = findlastspoken->second+1;
			int newNb = index-lastspoken;
			input.push_back(newNb);
			spoken[last_round] = index-1;
		}
		else {
			input.push_back(0);
			spoken[last_round] = index-1;
		}
		index++;
	}

	cout << "The 2020nth number is "<<input[2019] << endl;
	cout << "The 30000000nth number is "<<input[30000000-1] << endl;

	cout << "Day 15 end" << endl;
}


