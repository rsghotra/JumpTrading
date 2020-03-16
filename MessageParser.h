#ifndef MESSAGEPARSER_H
#define MESSAGEPARSER_H
#include "OrderBook.h"
#include<vector>
#include<iostream>
#include <sstream>
#include<algorithm>
#include<string>

class MessageParser {
private:
public:
    void print_vector(std::vector<std::string> const &input);
    void parse(const std::string  &input, OrderBook &orderBook);
};

#endif