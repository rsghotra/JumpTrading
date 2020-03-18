#include <iostream>
#include<vector>
#include<iostream>
#include <sstream>
#include<algorithm>

#include "MessageParser.h"
#include "Util.h"
#include "Logger.h"

void MessageParser::parse(const std::string  &input) {
	std::istringstream ss(input);
	std::string token;
	try {
		std::getline(ss, token, ',');
		int c = str2i(token);
		if( c==0 ) {
			int id;
			int side;
			int size;
			double price;
			std::getline(ss, token, ',');
      		id = str2i(token);
			std::getline(ss, token, ',');
			side = str2i(token);
			std::getline(ss, token, ',');
			size = str2i(token);
			std::getline(ss, token, ',');
			price = str2d(token);
			if(validate_input(id, side, size, price)) book.match_order(id, side, price, size);
		} else if( c==1 ) {
			int id;
			std::getline(ss, token, ',');
			id = str2i(token);
			if(validate_input(id, 1, -1,-1,true)) book.cancel_order(id);			
		} else {
			LOG(ERROR) << "Bad Request: Invalid order type.";
		}
	} catch(...) {
		LOG(ERROR) << "Bad Input: Unexpected or out of range datatype detected.";
	}
}