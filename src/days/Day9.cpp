//============================================================================
// Name        : Day9.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <set>
#include "days.hpp"
using namespace std;

bool sumCanBeFound(int sum, int* batch) {
	for(int i=0; i<25; i++) {
		int to_find = sum-*(batch+i);
		for(int j=0; j<25; j++) {
			if(j==i)
				continue;
			else if(to_find==*(batch+j))
				return true;
		}
	}
	return false;
}

void day9() {
	cout << "Day 9 start" << endl;

	fstream input;
	input.open("inputs/day9.txt");

	int invalid = 0;

	if(input.is_open()) {
		int code;
		int i = 0;
		int batch[25];
		while(input >> code ) {
			if(i<25) {
				batch[i] = code;
			}else{
				if(sumCanBeFound(code, batch))
					batch[i%25] = code;
				else
					break;
			}
			i++;
		}
		invalid = code;
		input.close();
	}

	input.open("inputs/day9.txt");
	if(input.is_open()) {

		vector<int> sumSet;
		vector<pair<int,int>> minMax;
		int code;
		input >> code;
		sumSet.push_back(code);
		minMax.push_back(make_pair(code,code));

		int i=0;
		while(input >> code ) {
			for(int j=0; j<i+1; j++) {
				sumSet[j] += code;
				if(code < minMax[j].first)
					minMax[j].first = code;
				if(code > minMax[j].second)
					minMax[j].second = code;
				if(sumSet[j]==invalid) {
					cout << "The limit " << sumSet[j] << " has been found with min: " << minMax[j].first << " and max: " << minMax[j].second <<endl;
					cout << "The answser is " << minMax[j].first+minMax[j].second << endl;
					goto endloop;
				}
			}
			sumSet.push_back(code);
			minMax.push_back(make_pair(code,code));
			i++;
		}
		input.close();
	}
endloop:
	cout << "Day 9 end" << endl;
}
