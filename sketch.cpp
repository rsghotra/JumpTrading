class OrderBook {
public:
  void add_order(int id, bool side, double price, int size);
  void cancel_order(int id);
};

class MessageParser {
public:
  void parse(const string &input);
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
};

/* Details of data structures */

struct Book;

class OrderBook {
private:
  Book ask_book;
  Book bid_book;

  // Hash table to get LevelNode* from id
  std::unordered_map<int, std::list<LevelNode*>::iterator> order_map;
};

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
