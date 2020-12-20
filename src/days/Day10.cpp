//============================================================================
// Name        : Day10.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <set>
#include "days.hpp"
using namespace std;

class Adapters
{
public:
	int max = 0;
	vector<int> listAdapters;

	Adapters(){};

	void add(int ad) {
		if(ad>max) {
			max = ad;
			listAdapters.push_back(ad);
		}
		else {
			vector<int> temp;
			bool placed = false;
			for(int i: listAdapters) {
				if(i<ad)
					temp.push_back(i);
				else if(!placed) {
					temp.push_back(ad);
					placed = true;
					temp.push_back(i);
				}
				else
					temp.push_back(i);
			}
			listAdapters = temp;
		}
	}

	void evaluateDiff(int* diff) {

		for(int i=1; i<(int)listAdapters.size(); i++) {
			diff[listAdapters[i]-listAdapters[i-1]-1]++;
		}
	}

	bool find(int i) {
		for(int c: listAdapters) {
			if(i==c)
				return true;
			if(i<c)
				return false;
		}
		return false;
	}
};

void day10() {
	cout << "Day 10 start" << endl;

	fstream input;
	input.open("inputs/day10.txt");

	Adapters adapters = Adapters();
	if(input.is_open()) {
		int code;
		while(input >> code) {
			adapters.add(code);
		}
		input.close();
	}

	cout << "size is " << adapters.listAdapters.size() << endl;

	int diff[3] = {1,0,1};
	adapters.evaluateDiff(diff);
	cout << "There are " << diff[0] << " 1 jolts difference." << endl;
	cout << "There are " << diff[2] << " 3 jolts difference." << endl;
	cout << "The result is " << diff[0]*diff[2] << "!" << endl;

//	for(int i: adapters.listAdapters) {
//		cout << i << endl;
//	}

	cout << "Day 10 end" << endl;
}
