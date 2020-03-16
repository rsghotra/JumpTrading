#ifndef MESSAGEPARSER_H
#define MESSAGEPARSER_H
#include<vector>
#include<iostream>
#include<sstream>
#include<algorithm>
#include<string>

#include "OrderBook.h"

class MessageParser {
public:
	MessageParser(OrderBook& book) : book(book) {}
    void parse(const std::string  &input);

private:
	OrderBook& book;
};

#endif
