#include <iostream>
#include "ExecutionLogger.h"

void ExecutionLogger::on_trade(double price, int size) {
	std::cout << "2," << size << "," << price << "\n";
}

void ExecutionLogger::on_fill(int id, int size_remaining) {
	if(size_remaining==0) {
		std::cout << "3," << id << "\n";
	} else {
		std::cout << "4," << id << "," << size_remaining << "\n";
	}
}
