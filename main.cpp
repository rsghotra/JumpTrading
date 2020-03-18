#include <iostream>
#include "MessageParser.h"
#include "OrderBookLL.h"
#include "OrderBookRBT.h"
#include "ExecutionLogger.h"
#include "Logger.h"

int main() {
  Log::ReportingLevel = DEBUG;
  OrderBookLL book;
  MessageParser parser(book);
  ExecutionLogger logger;
  book.set_execution_listener(&logger);
  std::string input;
  while(std::getline(std::cin, input)) {
    parser.parse(input);
  }
  return 0;
}
