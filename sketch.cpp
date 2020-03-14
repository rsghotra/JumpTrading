#include <cstring>
#include <iostream>
#include <list>
#include <unordered_map>
#include <string>
/* Details of data structures */
struct Book {
  std::list<Level*> levels;
};

struct Level {
  double price;
  int num_nodes;
  std::list<LevelNode*> nodes;
};

struct LevelNode {
  int id;
  int size;
  Level* level;
};

class OrderBook {
private:
  Book ask_book;
  Book bid_book;
  // Hash table to get LevelNode* from id
  std::unordered_map<int, std::list<LevelNode*>::iterator> order_map;
public:
  void add_order(int id, bool side, double price, int size) {

  }
  void cancel_order(int id);
};

class MessageParser {
//ideal way to write
public:
  void parse(std::string  &input) {
    //sohisticated validation need to be done here
    //1. Check if you have 5 required parameters for add order and three paramters for cancel order
    //2. Check types of each parameter
    //3. Populate order book's buy and sell struct
    //4. Run OrderMatching algorithm to see if there is a trade match

  }
};

class ExecutionListener {
public:
  void on_trade(double price, int size);
  void on_fill(int id, int size_remaining=0);
};

/* Main */

void main() {
  MessageParser parser;
  OrderBook book;
  std::string input;
  while(std::getline(std::cin, input)) {
    parser.parse(input);
  }
}
