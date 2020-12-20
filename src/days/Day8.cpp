//============================================================================
// Name        : Day8.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <set>
#include "days.hpp"

using namespace std;

void day8() {
	cout << "Day 8 start" << endl;

	fstream code;
	code.open("inputs/day8.txt");

	vector<pair<string, int>> commands;

	if(code.is_open()) {
		string operation;
		int argument;
		while(code >> operation >> argument) {
			commands.push_back(make_pair(operation, argument));
		}
		code.close();
	}

	int accumulator = 0;
	int line = 0;
	set<int> already_visited = {};

	set<int> nopAndJmpPosition;

	while((already_visited.find(line) == already_visited.end()) && (line < (int)commands.size())) {
		already_visited.insert(line);
		string cmd = commands[line].first;
		int arg = commands[line].second;
		if(cmd=="acc") {
			accumulator += arg;
			line++;
		}
		else if(cmd=="jmp") {
			nopAndJmpPosition.insert(line);
			line += arg;
		}
		else {
			nopAndJmpPosition.insert(line);
			line++;
		}
	}

	cout << "The boucle was at line " << line << ", the accumulator is at " << accumulator << endl;

	for(int pos: nopAndJmpPosition) {
		already_visited.clear();
		line = 0;
		accumulator = 0;
		while((already_visited.find(line) == already_visited.end()) && (line < (int)commands.size())) {
			already_visited.insert(line);
			string cmd = commands[line].first;
			int arg = commands[line].second;
			if(cmd=="acc") {
				accumulator += arg;
				line++;
			}
			else if(cmd=="jmp") {
				if(line == pos)
					line++; //nop
				else
					line += arg;
			}
			else {
				if(line == pos)
					line += arg; //jmp
				else
					line ++;
			}
		}
		if(line == (int)commands.size()) {
			cout << "The value of " << pos << " was changed, the accumulator is at " << accumulator << endl;
		}
	}

	cout << "Day 8 end" << endl;
}
