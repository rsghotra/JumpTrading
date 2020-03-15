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
  void parse(const std::string  &input, OrderBook &orderBook) {
    //https://www.fluentcpp.com/2017/04/21/how-to-split-a-string-in-c/
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(input);
    int msgId=-1, orderId=0, size=0;
    bool side=0;
    double price=0.0;
    while(std::getline(tokenStream, token, ',')) {
      //stripping whitespace from each token, if exists
      //https://www.techiedelight.com/remove-whitespaces-string-cpp/
      token.erase(std::remove_if(token.begin(), token.end(), ::isspace), token.end());
      tokens.push_back(token);
    }
    if(tokens.size() != 2 && tokens.size() != 5) {
      std::cerr <<"====Erroneus Input===" << std::endl;
      std::cerr << "Please check number of arguments provided to the system." << std::endl;
      std::cerr << "Order book accepts either 5(for adding a order) or 2(for cancelling a order)." << std::endl;
    }
    try {
      msgId  = std::stoi(tokens[0]);
      orderId = std::stoi(tokens[1]);
      if(orderId <= 0) std::cerr << "Order ID is negative, please enter a valid orderID" << std::endl;
      if(msgId == 0 && tokens.size() == 5) {
        //at this point we know that the incoming message is a addOrder message.
      } else if(msgId == 1 && tokens.size() == 2) {
        orderBook.cancel_order(orderId);
      } else {
        std::cerr << "Wrong msg type detected and number of parameters detected. Possible input message types are: 0 and 1.\nPossible number of input paramters are five." << std::endl;
      }
    } catch(...) {
      std::cerr << "msgID or orderID size is too big or the value is not convertable to int" << std::endl;
    }
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
    parser.parse(input, book); // for each input line. OrderMatcher is invoked
  }
  return 0;
}
