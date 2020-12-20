//============================================================================
// Name        : Day11.cpp
// Author      : Quentin Hivert
// Version     :
// Copyright   : 
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "days.hpp"
using namespace std;

int countAround(char c, vector<string>* map, int nbLine, int nbChar) {
	int ret = 0;
	ret += (*map)[nbLine-1][nbChar-1] == c;
	ret += (*map)[nbLine-1][nbChar]   == c;
	ret += (*map)[nbLine-1][nbChar+1] == c;
	ret += (*map)[nbLine][nbChar-1]   == c;
	ret += (*map)[nbLine][nbChar+1]   == c;
	ret += (*map)[nbLine+1][nbChar-1] == c;
	ret += (*map)[nbLine+1][nbChar]   == c;
	ret += (*map)[nbLine+1][nbChar+1] == c;

	return ret;
}

int countInSight(vector<string>* map, int nbLine, int nbChar) {
	int ret = 0;
	char free  = 'L';
	char taken = '#';

	int maxLine = map->size()-1;
	int maxChar = (*map)[0].size()-1;

	int iLine = nbLine;
	int iChar = nbChar;
	while(iLine>0 && iChar>0) {
		char cTemp = (*map)[--iLine][--iChar];
		if(cTemp==free)
			break;
		if(cTemp==taken) {
			ret++;
			break;
		}
	}

	iLine = nbLine;
	iChar = nbChar;
	while(iLine>0) {
		char cTemp = (*map)[--iLine][iChar];
		if(cTemp==free)
			break;
		if(cTemp==taken) {
			ret++;
			break;
		}
	}

	iLine = nbLine;
	iChar = nbChar;
	while(iLine>0 && iChar<maxChar) {
		char cTemp = (*map)[--iLine][++iChar];
		if(cTemp==free)
			break;
		if(cTemp==taken) {
			ret++;
			break;
		}
	}

	iLine = nbLine;
	iChar = nbChar;
	while(iChar>0) {
		char cTemp = (*map)[iLine][--iChar];
		if(cTemp==free)
			break;
		if(cTemp==taken) {
			ret++;
			break;
		}
	}

	iLine = nbLine;
	iChar = nbChar;
	while(iChar<maxChar) {
		char cTemp = (*map)[iLine][++iChar];
		if(cTemp==free)
			break;
		if(cTemp==taken) {
			ret++;
			break;
		}
	}

	iLine = nbLine;
	iChar = nbChar;
	while(iLine<maxLine && iChar>0) {
		char cTemp = (*map)[++iLine][--iChar];
		if(cTemp==free)
			break;
		if(cTemp==taken) {
			ret++;
			break;
		}
	}

	iLine = nbLine;
	iChar = nbChar;
	while(iLine<maxLine) {
		char cTemp = (*map)[++iLine][iChar];
		if(cTemp==free)
			break;
		if(cTemp==taken) {
			ret++;
			break;
		}
	}

	iLine = nbLine;
	iChar = nbChar;
	while(iLine<maxLine && iChar<maxChar) {
		char cTemp = (*map)[++iLine][++iChar];
		if(cTemp==free)
			break;
		if(cTemp==taken) {
			ret++;
			break;
		}
	}

	return ret;
}

void day11() {
	cout << "Day 11 start" << endl;

	fstream input;
	input.open("inputs/day11.txt");
//	input.open("UnitTest.txt");

	char free  = 'L';
	char taken = '#';
	char floor = '.';

	vector<string> map;

	bool firstLine = true;

	/*
	 * Create the map and add floors as a first line, first column, last column
	 * and last line.
	 */
	if(input.is_open()) {
		string line;
		while(input >> line) {
			if(firstLine) {
				int size = line.size();
				string full (size+2, floor);
				map.push_back(full);
				firstLine = false;
			}
			line.insert(0, 1, floor);
			line.push_back(floor);
			map.push_back(line);
		}
		int size = line.size();
		string full (size, floor);
		map.push_back(full);
		input.close();
	}



	bool isStabilized = false;
	int seatTaken = 0;

	vector<string> mapPart2 = map;

	while(!isStabilized) {
		isStabilized = true;
		seatTaken = 0;
		vector<string> temp = map;
		for(int nbLine = 1; nbLine < (int)map.size()-1; nbLine++) {
			for(int nbChar = 1; nbChar < (int)map[0].size()-1; nbChar++) {
				if(map[nbLine][nbChar] == floor)
					continue;
				else if(map[nbLine][nbChar] == free) {
					int count = countAround(taken, &map, nbLine, nbChar);
					if(count==0) {
						temp[nbLine][nbChar] = taken;
						isStabilized = false;
					}
				}
				else {
					seatTaken++;
					int count = countAround(taken, &map, nbLine, nbChar);
					if(count>=4) {
						temp[nbLine][nbChar] = free;
						isStabilized = false;
					}
				}
			}
		}
		map = temp;
	}

	cout << "The map is stabilized with " << seatTaken << " seats occupied!" << endl << endl;

	isStabilized = false;
	seatTaken = 0;

	while(!isStabilized) {
		isStabilized = true;
		seatTaken = 0;
		vector<string> temp = mapPart2;
		for(int nbLine = 1; nbLine < (int)mapPart2.size()-1; nbLine++) {
			for(int nbChar = 1; nbChar < (int)mapPart2[0].size()-1; nbChar++) {
				if(mapPart2[nbLine][nbChar] == floor)
					continue;
				else if(mapPart2[nbLine][nbChar] == free) {
					int count = countInSight(&mapPart2, nbLine, nbChar);
					if(count==0) {
						temp[nbLine][nbChar] = taken;
						isStabilized = false;
					}
				}
				else {
					seatTaken++;
					int count = countInSight(&mapPart2, nbLine, nbChar);
					if(count>=5) {
						temp[nbLine][nbChar] = free;
						isStabilized = false;
					}
				}
			}
		}
		mapPart2 = temp;
	}

	cout << "The map is stabilized with " << seatTaken << " seats occupied!" << endl;

	cout << "Day 11 end" << endl;
}
