//============================================================================
// Name        : Day7.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <set>
#include "utils.hpp"
#include "days.hpp"

using namespace std;

class Bags {
public:
	string id;
	set<pair<int, string>> children;
	int nbChild=0;

	Bags(string name) {
		id = name;
		children = {};
	}

	void add(int nb, string name) {
		children.insert(make_pair(nb,name));
		nbChild = children.size();
	}
};


void day7() {
	cout << "Day 7 start" << endl;

	vector<Bags> listBags;

	ifstream bagsRule;
	bagsRule.open("inputs/day7.txt");
	if(bagsRule.is_open()) {
		string line;
		while(getline(bagsRule, line)) {
			vector<string> lineSplit = splitString(line, " bags contain");
			Bags temp = Bags(lineSplit[0]);
			if(lineSplit[1]==" no other bags.")
				continue;
			vector<string> lineChildren = splitString(lineSplit[1], ",");
			for(int i=0; i<(int)lineChildren.size(); i++) {
				string oneRule = lineChildren[i];
				int nb = oneRule[1] -'0';
				string bagName = splitString(oneRule.substr(3, oneRule.size()), " ba")[0];
				temp.add(nb, bagName);
			}
			listBags.push_back(temp);
		}
	}

	cout << "There is " << listBags.size() << " bags in this world!" << endl;
	cout << "first bags is " << listBags[0].id << " which can have:" << endl;
	for(auto i: listBags[0].children) {
		cout << i.first << " bags of type " << i.second << endl;
	}

	cout << "Day 7 end" << endl;

}
