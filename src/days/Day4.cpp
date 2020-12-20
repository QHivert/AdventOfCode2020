//============================================================================
// Name        : Day4.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <set>
#include <string>
#include <map>
#include "utils.hpp"
#include "days.hpp"

using namespace std;




//rules is a map of {"key": functionCheckValue()}
map<string, bool(*)(string)> rules;

auto byr = [](string str){return (str.length()==4) && (1920<=stoi(str)) && (stoi(str)<=2002);};
auto iyr = [](string str){return (str.length()==4) && (2010<=stoi(str)) && (stoi(str)<=2020);};
auto eyr = [](string str){return (str.length()==4) && (2020<=stoi(str)) && (stoi(str)<=2030);};

auto hgt = [](string str){
	string suffix = str.substr(str.size()-2, str.size());
	if(suffix=="cm") {
		string value = str.substr(0, str.find("c"));
		return (150<=stoi(value)) && (stoi(value)<= 193);
	}
	else if(suffix=="in") {
		string value = str.substr(0, str.find("i"));
		return (59<=stoi(value)) && (stoi(value)<= 76);
	}
	else
		return false;
};

auto hcl = [](string str){
	if(str.size()==7 and str[0]=='#') {
		string allowed = "0123456789abcdef";
		for(char c: str.substr(1, str.size())) {
			if(allowed.find(c) == string::npos)
				return false;
		}
		return true;
	}
	else
		return false;

};

auto ecl = [](string str){
	set<string> allowed = {"amb", "blu", "brn", "gry", "grn", "hzl", "oth"};
	return allowed.find(str) != allowed.end();
};

auto pid = [](string str){
	if(str.size()==9) {
		string allowed = "0123456789";
		for(char c: str) {
			if(allowed.find(c) == string::npos)
				return false;
		}
		return true;
	}
	else
		return false;
};

auto cid = [](string str){return true;};



void day4() {
	cout << "Day 4 start" << endl;

	//Add all rules
	rules.insert({"byr", byr});
	rules.insert({"iyr", iyr});
	rules.insert({"eyr", eyr});
	rules.insert({"hgt", hgt});
	rules.insert({"hcl", hcl});
	rules.insert({"ecl", ecl});
	rules.insert({"pid", pid});
	rules.insert({"cid", cid});

	const set<string> requirements = {"byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid"};

	ifstream passport;
	passport.open("inputs/day4.txt");
	if(passport.is_open()) {

		string line;
		int passportsValid = 0;
		int passportsValidAndOk = 0;
		set<string> missingForm  = requirements;
		set<string> notValidForm = requirements;

		while(getline(passport, line)) {

			if(line.length() == 0){
				// New passport incoming
				if(missingForm.size() == 0){
					passportsValid++;
					if(notValidForm.size() == 0) {
						passportsValidAndOk++;
					}
				}

				missingForm = requirements;
				notValidForm = requirements;
				continue;
			}

			vector<string> splitSpace = splitString(line, " ");
			for(auto form: splitSpace){
				vector<string> splitKeyValue = splitString(form, ":");
				string key = splitKeyValue[0];
				string value = splitKeyValue[1];
				missingForm.erase(key);
				if(rules[key](value))
					notValidForm.erase(key);
			}

		}

		//Check the last passport in file
		if(missingForm.size() == 0){
			passportsValid++;
			if(notValidForm.size() == 0) {
				passportsValidAndOk++;
			}
		}

		cout << "There are " << passportsValid << " passports valid !" << endl;
		cout << "There are " << passportsValidAndOk << " passports valid and ok !" << endl;
		passport.close();
	}
	cout << "Day 4 end" << endl;
}
