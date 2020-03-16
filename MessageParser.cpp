#include "MessageParser.h"

void MessageParser::print_vector(std::vector<std::string> const &input) {
    for(auto it = input.cbegin(); it != input.end(); it++) {
        std::cout << *it << ' ';
    }
}

void MessageParser::parse(const std::string  &input, OrderBook &orderBook) {
    //https://www.fluentcpp.com/2017/04/21/how-to-split-a-string-in-c/
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(input);
    int msgId=-1, orderId=-1, size=-1;
    bool side;
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
        if(tokens[2] == "0") {
          side = 0;
        } else if(tokens[2] == "1") {
          side = 1;
        } else {
          std::cerr << "Invalid side found.";
          return;
        }
        //validate price and size
        try {
          size = std::stoi(tokens[3]);
        } catch(...) {
          std::cerr << "Quantity is too large or too low than permissible limits.";
          return;
        }
        try {
          price = std::stoi(tokens[4]);
        } catch(...) {
          std::cerr << "Price is too large or too low than permissible limits.";
          return;
        }
        orderBook.order_matcher(orderId, side, price, size);
      } else if(msgId == 1 && tokens.size() == 2) {
        orderBook.cancelOrder(orderId);
        return;
      } else {
        std::cerr << "Wrong msg type detected and number of parameters detected. Possible input message types are: 0 and 1." << std::endl;
        return;
      }
    } catch(...) {
      std::cerr << "msgID or orderID size is too big or the value is not convertable to int" << std::endl;
      return;
    }
}