#include <cstring>
#include <iostream>
#include <list>
#include <unordered_map>
#include <string>
#include <iterator>
#include <sstream>
#include <vector>
/* Details of data structures */
struct Level;
struct LevelNode {
  int id;
  int size;
  Level* level;
};

struct Level {
  double price;
  int num_nodes;
  std::list<LevelNode*> nodes;
};

struct Book {
  std::list<Level*> levels;
};

class OrderBook {
private:
  Book ask_book;
  Book bid_book;
  // Hash table to get LevelNode* from order id
  std::unordered_map<int, std::list<LevelNode*>::iterator> order_map;
  void _orderMatcher() {
    
  }
public:
  void add_order(int id, bool side, double price, int size) {
      //call order matcher with same paramterest and additional
  }
  void cancel_order(int id) {
    //find the corresponding level node from hash map.
    //remove the identified level node.
  }
};

class MessageParser {
public:
  void parse(const std::string  &input) {
    std::istringstream iss(input);
    std::vector<std::string> tokens{std::istream_iterator<std::string>{iss},
                                    std::istream_iterator<std::string>{}};
    //sohisticated validation need to be done here
    //1. Check if you have 5 required parameters for add order and three paramters for cancel order
    //2. Check data types of each parameter
    //if incoming msg id == 0 then call book.add_order
    //else if incoming msg id == 1  then call book.cancel_order
  }
};

class ExecutionListener {
private:
  enum {TRADE_EVENT=2, FULLY_FILLED=3, PARTIALLY_FILLED=5};
public:
  void on_trade(double price, int size) {
    std::cout << "Trade Event!";
    std::cout << TRADE_EVENT << " " << size << " " << price << std::endl; 
  }
  void on_fill(int id, int size_remaining=0) {
    if(size_remaining == 0) {
      std::cout << "Fully Filled Trade Happened.";
      std::cout << FULLY_FILLED << " " << id << std::endl;
    } else
    {
      std::cout << "Partial Filled Trade Happened.";
      std::cout << PARTIALLY_FILLED << " " << id << " " << size_remaining << std::endl;
    }
  }
};

/* Main */

int main() {
  MessageParser parser;
  OrderBook book;
  std::string input;
  while(std::getline(std::cin, input)) {
    parser.parse(input); // for each input line. OrderMatcher is invoked
  }
  return 0;
}
