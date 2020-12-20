//============================================================================
// Name        : Day12.cpp
// Author      : Quentin Hivert
// Version     :
// Copyright   : 
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>
#include <cstdlib>
#include "days.hpp"
using namespace std;

char N = 'N';
char E = 'E';
char W = 'W';
char S = 'S';
char F = 'F';
char L = 'L';
char R = 'R';

void north(pair<int, int> &coord, int cmd){coord.second += cmd;};
void east(pair<int, int> &coord, int cmd){coord.first += cmd;};
void west(pair<int, int> &coord, int cmd){coord.first -= cmd;};
void south(pair<int, int> &coord, int cmd){coord.second -= cmd;};
map<char, void(*)(pair<int, int>&, int)> road;

void forward(pair<int, int> &coord, char facing, int cmd) {
	road[facing](coord, cmd);
}

void turnRight(char &facing, int degree) {
	string compass = {E, S, W, N};
	int move = degree/90;
	int currentInd = compass.find(facing);
	int newId = (currentInd+move)%4;
	facing = compass[newId];
}

void turnLeft(char &facing, int degree) {
	string compass = {E, N, W, S};
	int move = degree/90;
	int currentInd = compass.find(facing);
	int newId = (currentInd+move)%4;
	facing = compass[newId];
}

void forward2(pair<int, int> &ship, pair<int, int> waypoint, int cmd) {
	ship.first += cmd*waypoint.first;
	ship.second += cmd*waypoint.second;
}

void turnRight2(pair<int, int> &ship, int degree) {
	pair<int, int> copy = ship;
	if(degree==90) {
		ship.first = copy.second;
		ship.second = -copy.first;
	}
	else if(degree==180) {
		ship.first = -copy.first;
		ship.second = -copy.second;
	}
	else {
		ship.first = -copy.second;
		ship.second = copy.first;
	}
}

void turnLeft2(pair<int, int> &ship, int degree) {
	pair<int, int> copy = ship;
	if(degree==90) {
		ship.first = -copy.second;
		ship.second = copy.first;
	}
	else if(degree==180) {
		ship.first = -copy.first;
		ship.second = -copy.second;
	}
	else {
		ship.first = copy.second;
		ship.second = -copy.first;
	}
}

void day12() {
	cout << "Day 12 start" << endl;

	fstream cmd;
	cmd.open("inputs/day12.txt");

	road.insert({'N', &north});
	road.insert({'E', &east});
	road.insert({'W', &west});
	road.insert({'S', &south});

	if(cmd.is_open()) {
		pair<int, int> coord1 = {0,0};
		string line;
		char facing = E;
		while(cmd >> line) {
			char dir = line[0];
			int length = stoi(line.substr(1, line.size()));
			if(dir==F) {
				forward(coord1, facing, length);
			}
			else if(dir==R) {
				turnRight(facing, length);
			}
			else if(dir==L) {
				turnLeft(facing, length);
			}
			else {
				road[dir](coord1, length);
			}
		}
		cout << "The ship is facing " << facing << " at coordinates (" << coord1.first << "," << coord1.second << ")" << endl;
		cout << "The answer of part 1 is " << abs(coord1.first)+abs(coord1.second) << endl;
		cmd.close();
	}

	fstream cmd2;
	cmd2.open("inputs/day12.txt");

	if(cmd2.is_open()) {
		pair<int, int> coordShip = {0,0};
		pair<int, int> coordWaypoint = {10,1};
		string line;
		while(cmd2 >> line) {
			char dir = line[0];
			int length = stoi(line.substr(1, line.size()));
			if(dir==F) {
				forward2(coordShip, coordWaypoint, length);
			}
			else if(dir==R) {
				turnRight2(coordWaypoint, length);
			}
			else if(dir==L) {
				turnLeft2(coordWaypoint, length);
			}
			else {
				road[dir](coordWaypoint, length);
			}
		}
		cout << "The waypoint is at coordinates (" << coordWaypoint.first << "," << coordWaypoint.second << ")" << endl;
		cout << "The ship is at coordinates (" << coordShip.first << "," << coordShip.second << ")" << endl;
		cout << "The answer of part 2 is " << abs(coordShip.first)+abs(coordShip.second) << endl;
		cmd2.close();
	}

	cout << "Day 12 end" << endl;
}
