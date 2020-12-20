/*
 * Day14.cpp
 *
 *  Created on: 20 Dec 2020
 *      Author: Hivert Quentin
 */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include "days.hpp"
#include "utils.hpp"
using namespace std;

class Mask {
public:
	string force;
	long long force1;
	long long force0;

	Mask() {
		force1 = 0;
		force0 = 1;
	}

	Mask(string str) {
		force = str;
		string str1 = str;
		string str0 = str;
		for(int i=0; i<(int)str.size(); i++) {
			if(str[i]=='X') {
				str1[i]='0';
				str0[i]='1';
			}
		}
		force1 = stoll(str1, 0, 2);
		force0 = stoll(str0, 0, 2);
	}

	long long apply(long long input) {
		return (input|force1)&force0;
	}

	vector<long long> apply2(long long input) {
		vector<long long> temp = {0};
		for(int c=0; c<(int)force.size(); c++) {
			if(force[c]=='X') {
				vector<long long> copy = temp;
				for(long long k: copy) {
					temp.push_back(k+power(true, (force.size()-1-c)));
				}
			}
			else if(force[c]=='1') {
				for(int i = 0; i<(int)temp.size(); i++) {
					temp[i] += power(true, (force.size()-1-c));
				}
			}
			else {
				for(int i = 0; i<(int)temp.size(); i++) {
					temp[i] += input&(long long)power(true, (force.size()-1-c));
				}
			}
		}
		return temp;
	}
};

void day14() {
	cout << "Day 14 start" << endl;

	ifstream input;
	input.open("inputs/day14.txt");

	Mask mask;
	map<int, long long> memory;
	map<long long, long long> memory2;
	if(input.is_open()) {
		string line;
		while(getline(input, line)) {
			vector<string> lineSplit = splitString(line, " = ");
			if(lineSplit[0]=="mask") {
				mask = Mask(lineSplit[1]);
			}
			else {
				long long address = stoi(lineSplit[0].substr(4, lineSplit[0].size()-1));
				memory[address] = mask.apply(stoll(lineSplit[1]));
				vector<long long> listAddress = mask.apply2(address);
				for(long long address: listAddress) {
					memory2[address] = stoll(lineSplit[1]);
				}

			}
		}
		long long sum = 0;
		long long sum2 = 0;
		for(auto i: memory) {
			sum += i.second;
		}
		for(auto i: memory2) {
			sum2 += i.second;
		}
		cout << "The answer for part 1 is " << sum << endl;
		cout << "The answer for part 2 is " << sum2 << endl;
	}

	cout << "Day 14 end" << endl;
}


