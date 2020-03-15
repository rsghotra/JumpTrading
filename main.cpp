#include <cstring>
#include <iostream>
#include <list>
#include <unordered_map>
#include <string>
#include <iterator>
#include <sstream>
#include <vector>
#include <algorithm>
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
private:
  void _print_vector(std::vector<std::string> const &input) {
    for(auto it = input.cbegin(); it != input.end(); it++) {
      std::cout << *it << ' ';
    }
  }

public:
  void parse(const std::string  &input) {
    //https://www.fluentcpp.com/2017/04/21/how-to-split-a-string-in-c/
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(input);
    while(std::getline(tokenStream, token, ',')) {
      //stripping whitespace from each token, if exists
      //https://www.techiedelight.com/remove-whitespaces-string-cpp/
      token.erase(std::remove_if(token.begin(), token.end(), ::isspace), token.end());
      tokens.push_back(token);
    }
    if(tokens.size() == 2 || tokens.size() == 5) {
      //passes first test of validation
    } else {
      std::cerr <<"====Erroneus Input===" << std::endl;
      std::cerr << "Please check number of arguments provided to the system." << std::endl;
      std::cerr << "Order book accepts either 5(for adding a order) or 2(for cancelling a order)." << std::endl;
    }
    //Since there are only two possible types of input messages.
    //1. Check if you have 2 or 5 required parameters for add order and three paramters for cancel order
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
