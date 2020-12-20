/*
 * Day13.cpp
 *
 *  Created on: 20 Dec 2020
 *      Author: Hivert Quentin
 */

#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <limits>
#include "days.hpp"
#include "utils.hpp"
using namespace std;

void day13() {
	cout << "Day 13 start" << endl;

	fstream input;
	input.open("inputs/day13.txt");


	if(input.is_open()) {
		int timestamp;
		string busLine;
		input >> timestamp >> busLine;
		input.close();
		vector<string> busSplit = splitString(busLine, ",");
		set<int> busList = {};
		for(string bus: busSplit) {
			if(bus!="x") {
				busList.insert(stoi(bus));
			}
		}

		int minRemain = numeric_limits<int>::max();
		int busToTake = -1;
		for(int bus: busList) {
			int temp = timestamp/bus;
			int remain = bus*(temp+1) - timestamp;
			if(remain<minRemain) {
				minRemain = remain;
				busToTake = bus;
			}
		}
		cout << "The first bus we can take is " << busToTake << " with " << minRemain << "min to wait" << endl;
		cout << "Answer for part 1 is " << busToTake*minRemain << endl;

		vector<pair<int, int>> busAndDelay;
		for(int i = 0; i<(int)busSplit.size(); i++) {
			if(busSplit[i]=="x")
					continue;
			busAndDelay.push_back(make_pair(stoi(busSplit[i]), i));
		}

		//This code sample was taken and translated from debnet python answer
		//https://github.com/debnet/AdventOfCode2020/blob/master/Day13.ipynb
		long long index = busAndDelay[0].first;
		long long jump = busAndDelay[0].first;
		for(int i=1; i<(int)busAndDelay.size(); i++) {
			while((index+busAndDelay[i].second)%busAndDelay[i].first != 0) {
				index += jump;
			}
			jump *= busAndDelay[i].first;
		}

		cout << "The first index is " << index << endl;
	}

	cout << "Day 13 end" << endl;
}




