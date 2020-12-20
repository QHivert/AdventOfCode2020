/*
 * utils.hpp
 *
 *  Created on: 19 Dec 2020
 *      Author: Hivert Quentin
 */

#ifndef HEADERS_UTILS_HPP_
#define HEADERS_UTILS_HPP_

#include <vector>
#include <string>
#include <chrono>


/**
 * Split the string according to the delimiter
 * @param str the string to split
 * @param del the delimiter
 * @return a vector of all parts
 */
std::vector<std::string> splitString(std::string str, std::string del);

std::chrono::duration<double> timerWrap(void (*function)());

long long power(bool doIt, long long pow);

#endif /* HEADERS_UTILS_HPP_ */
