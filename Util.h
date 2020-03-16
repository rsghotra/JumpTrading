#ifndef UTIL_H
#define UTIL_H
#include <sstream>
#include <string>

int str2i (const std::string& input) {
	int i;
	std::stringstream ss(input);
	ss >> i;
	return i;
}

double str2d (const std::string& input) {
	double d;
	std::stringstream ss(input);
	ss >> d;
	return d;
}
#endif
