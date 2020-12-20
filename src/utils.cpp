/*
 * utils.cpp
 *
 *  Created on: 19 Dec 2020
 *      Author: Hivert Quentin
 */

#include "utils.hpp"

std::vector<std::string> splitString(std::string str, std::string del) {
	std::vector<std::string> result;

	if(str.find(del) == std::string::npos)
		return {str};

	while(str.find(del) != std::string::npos) {
		std::string o1 = str.substr(0, str.find(del));
		str = str.substr(str.find(del)+del.size(), str.size());
		result.push_back(o1);
	}

	result.push_back(str);

	return result;
}

std::chrono::duration<double> timerWrap(void (*function)()) {
	auto start = std::chrono::high_resolution_clock::now();
	function();
	auto end = std::chrono::high_resolution_clock::now();
	return std::chrono::duration_cast<std::chrono::milliseconds>(end-start);
}

long long power(bool doIt, long long pow) {
	if(doIt)
		return (long long)1 << pow;
	else
		return (long long)0;
}




