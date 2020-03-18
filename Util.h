#ifndef UTIL_H
#define UTIL_H
#include <sstream>
#include <string>
#include <stdexcept>
#include "Logger.h"

int str2i (const std::string& input, std::string label) {
	int out;
	try {
		out = std::stoi(input);
		if(out < 0) {
			LOG(ERROR) << "Bad Request: " << label << " is negative. GIVEN: " << out;
			throw std::exception();
		}	
		if(label.compare("OrderSide") != 0 && label.compare("OrderType") != 0 && out == 0) {
			LOG(ERROR) << "Bad Request: " << label << " can not be zero. GIVEN: " << out;
			throw std::exception();
		}
		if(label.compare("OrderSide") == 0 && label.compare("OrderType") == 0 && (out != 0 || out != 1)) {
			LOG(ERROR) << "Bad Request: " << label << " can only be 0 or 1. GIVEN: " << out;
			throw std::exception();
		}
	}
	catch(std::invalid_argument& e) {
		LOG(ERROR) << "Bad Request: " << label << " is not convertible to int.";
	}
	catch(std::out_of_range& e) {
		LOG(ERROR) << "Bad Request: " << label << " is out of 32-bit int range.GIVEN: " << out;
	}
	catch(...) {
		
	} 
	return out;
}

double str2d (const std::string& input) {
	double price;
	try {
		std::stringstream ss(input);
		ss >> price;
		if(price < 0) {
			LOG(ERROR) << "Bad Request: Price can not be negative.";
			return -1;
		}
		if(price == 0) {
			LOG(ERROR) << "Bad Request: Price can not be zero.";
			return -1;
		}
	}
	catch(std::invalid_argument& e) {
		LOG(ERROR) << "Bad Request: Price is not convertible to double.";
	}
	catch(std::out_of_range& e) {
		LOG(ERROR) << "Bad Request: Price is out of 64-bit double range.";
	}
	catch(...) {
		LOG(ERROR) << "Bad Request Detected.";
	}
	return price;
}

#endif
