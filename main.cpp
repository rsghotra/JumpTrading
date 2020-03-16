#include <iostream>
#include "MessageParser.cpp"
#include "OrderBook.h"

int main() {
  MessageParser parser;
  OrderBook book;
  std::string input;
  while(std::getline(std::cin, input)) {
    parser.parse(input, book);
  }
  return 0;
}
