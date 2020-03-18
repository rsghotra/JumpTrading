#ifndef UTIL_H
#define UTIL_H
#include <sstream>
#include <string>
#include <stdexcept>
#include "Logger.h"
#include "OrderBookLL.h"

int str2i (const std::string& input) {
	if(input.find('.') != std::string::npos) {
		//forcing not to convert double to int.
		return std::stoi("abc");
	}
	return std::stoi(input);
}

double str2d (const std::string& input) {
	double price;
	std::stringstream ss(input);
	ss >> price;
	return price;
}

bool validate_input(int id, bool side=-1, int size=-1, double price=-1, bool isCancelOrder = false ) {
	if(id <= 0) {
		LOG(ERROR) << "Bad Request: OrderId can not be zero/negative/out-of-range.";
		return false;
	}
	if(!isCancelOrder) {
		if(side != 0 && side != 1) {
			LOG(ERROR) << "Bad Request: OrderSide must be 0=Buy or 1=Sell.";
			return false;
		}
		if(size <= 0) {
			LOG(ERROR) << "Bad Request: Order size must be greater than zero.";
			return false;
		}
		if(price <= 0) {
			LOG(ERROR) << "Bad Request: Price must be greater than zero.";
			return false;
		}
	}
	return true;
}

#endif
