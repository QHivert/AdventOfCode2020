/*
 * Day24.cpp
 *
 *  Created on: 24 Dec 2020
 *      Author: Hivert Quentin
 */

#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <map>
#include <limits>
#include "days.hpp"
using namespace std;

auto e(pair<int, int>& coord){coord.first++; coord.second++;};
auto w(pair<int, int>& coord){coord.first--; coord.second--;};
auto ne(pair<int, int>& coord){coord.first++;};
auto se(pair<int, int>& coord){coord.second++;};
auto nw(pair<int, int>& coord){coord.second--;};
auto sw(pair<int, int>& coord){coord.first--;};

map<string, void(*)(pair<int, int>&)> moveTile;

void fillMap() {
	moveTile.insert({"e", &e});
	moveTile.insert({"w", &w});
	moveTile.insert({"ne", &ne});
	moveTile.insert({"se", &se});
	moveTile.insert({"nw", &nw});
	moveTile.insert({"sw", &sw});
}

pair<int, int> findTile(string line) {
	int i = 0;
	pair<int, int> coord = {0,0};
	while(i < (int)line.size()) {
		string s = "";
		s.push_back(line[i]);
		if(s=="n" or s=="s") {
			i++;
			s.push_back(line[i]);
		}
		moveTile[s](coord);
		i++;
	}
	return coord;
}
pair<int,int> addPair(pair<int,int> coord, int x, int y){coord.first += x; coord.second += y; return coord;}

int countAround(set<pair<int,int>>* blacks, pair<int,int> tile) {
	int ret = 0;
	ret += blacks->find(addPair(tile, 1, 1))!=blacks->end();
	ret += blacks->find(addPair(tile, -1, -1))!=blacks->end();
	ret += blacks->find(addPair(tile, 0, 1))!=blacks->end();
	ret += blacks->find(addPair(tile, 1, 0))!=blacks->end();
	ret += blacks->find(addPair(tile, 0, -1))!=blacks->end();
	ret += blacks->find(addPair(tile, -1, 0))!=blacks->end();

	return ret;
}

vector<int> findMapSize(const set<pair<int,int>>& blacks) {
	int xMax = numeric_limits<int>::min();
	int yMax = numeric_limits<int>::min();
	int xMin = numeric_limits<int>::max();
	int yMin = numeric_limits<int>::max();

	for(pair<int,int> k: blacks) {
		if(k.first < xMin) xMin = k.first;
		if(k.second < yMin) yMin = k.second;
		if(k.first > xMax) xMax = k.first;
		if(k.second > yMax) yMax = k.second;
	}

	return {xMin, xMax, yMin, yMax};
}

void day24() {
	cout << "Day 24 start:" << endl;

	fillMap();

	ifstream input;
	input.open("inputs/day24.txt");

	set<pair<int, int>> blacks = {};

	if(input.is_open()) {

		string line;
		while(input >> line) {
			pair<int,int> newTile = findTile(line);
			if(blacks.find(newTile)==blacks.end()) {
				blacks.insert(newTile);
			}
			else {
				blacks.erase(newTile);
			}
		}
		cout << "There are " << blacks.size() << " black tiles!" << endl;
		input.close();
	}

	int round = 0;
	while(round < 100) {
		vector<int> mapSize = findMapSize(blacks);
		int xMin = mapSize[0]-1;
		int xMax = mapSize[1]+1;
		int yMin = mapSize[2]-1;
		int yMax = mapSize[3]+1;

		set<pair<int,int>> temp = blacks;
		for(int i=xMin; i<=xMax; i++) {
			for(int j=yMin; j<=yMax; j++) {
				pair<int,int> currentTile = make_pair(i,j);
				if(blacks.find(currentTile)==blacks.end()) {
					//i,j is a white tile
					if(countAround(&blacks, currentTile)==2){
						//i,j is rounded by 2 black tiles, it becomes black
						temp.insert(currentTile);
					}
				}
				else {
					//i,j is a black tile
					if(countAround(&blacks, currentTile)>2 or countAround(&blacks, currentTile)==0) {
						temp.erase(currentTile);
					}
				}
			}
		}
		blacks = temp;
		round++;
	}

	cout << "At the 100th round, there are " << blacks.size() << " black tiles!" << endl;

	cout << "Day 24 end:" << endl;
}



