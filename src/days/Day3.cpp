//============================================================================
// Name        : Day3.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <algorithm>
#include <string>
#include "days.hpp"

using namespace std;

struct Slope
{
	int right;
	int down;

	Slope(int r, int d) {
		right = r;
		down = d;
	}
};

bool isThisATree(char c) {
	return c == '#';
}

int slideToboggan(Slope slope, vector<vector<bool>>* mapSlide) {
	int nbTree = 0;
	int posH = 0; // horizontal position
	int posV = 0; // vertical position
	int lenghtH = (mapSlide->at(0)).size();
	int lenghtV = mapSlide->size();

	while(posV < lenghtV) {
		nbTree += (mapSlide->at(posV))[posH%lenghtH];
		posH += slope.right;
		posV += slope.down;
	}

	return nbTree;
}

void day3() {
	cout << "Day 3 start" << endl;

	// mapTree will be the map of true/false (tree/empty)
	vector<vector<bool>> mapTree;

	fstream toboggan;
	toboggan.open("inputs/day3.txt");
	if(toboggan.is_open()) {
		string line;
		while(toboggan >> line) {
			vector<bool> lineBool;
			for(char c: line) {
				lineBool.push_back(isThisATree(c));
			}
			mapTree.push_back(lineBool);
		}
		toboggan.close();
	}

	Slope slope1 = Slope(3,1);
	int nbTree1 = slideToboggan(slope1, &mapTree);
	cout << "Result for Slope(3,1) (and part one) is " << nbTree1 << endl;

	Slope slope2 = Slope(1,1);
	int nbTree2 = slideToboggan(slope2, &mapTree);
	cout << "Result for Slope(1,1) is " << nbTree2 << endl;

	Slope slope3 = Slope(5,1);
	int nbTree3 = slideToboggan(slope3, &mapTree);
	cout << "Result for Slope(5,1) is " << nbTree3 << endl;

	Slope slope4 = Slope(7,1);
	int nbTree4 = slideToboggan(slope4, &mapTree);
	cout << "Result for Slope(7,1) is " << nbTree4 << endl;

	Slope slope5 = Slope(1,2);
	int nbTree5 = slideToboggan(slope5, &mapTree);
	cout << "Result for Slope(3,1) is " << nbTree5 << endl;

	int result = nbTree1 * nbTree2 * nbTree3 * nbTree4 * nbTree5;
	cout << "Result for part two is " << result << endl;

	cout << "Day 3 end" << endl;
}
