#ifndef UTIL_H
#define UTIL_H
#include <sstream>
#include <string>

int str2i (const std::string& input) {
	return std::stoi(input);
}

double str2d (const std::string& input) {
	double d;
	std::stringstream ss(input);
	ss >> d;
	return d;
}
#endif
