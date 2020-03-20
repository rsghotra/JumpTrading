#include <iostream>
#include <chrono>
#include <string>
#include "MessageParser.h"
#include "OrderBookLL.h"
#include "OrderBookRBT.h"
#include "ExecutionLogger.h"
#include "Logger.h"

int main() {
  Log::ReportingLevel = ERROR;
  OrderBookLL book;
  MessageParser parser(book);
  ExecutionLogger logger;
  book.set_execution_listener(&logger);
  std::string input;
  auto start = std::chrono::high_resolution_clock::now();
  while(std::getline(std::cin, input)) {
    parser.parse(input);
  }
  auto stop = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
  std::cout << "Test Case Running Time: " << duration.count() << std::endl;
  return 0;
}
