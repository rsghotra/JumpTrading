#include "ExecutionListener.h"

enum {TRADE_EVENT=2, FULLY_FILLED=3, PARTIALLY_FILLED=5};

void ExecutionListener::on_trade(double price, int size) {
    std::cout << "Trade Event!";
    std::cout << TRADE_EVENT << " " << size << " " << price << std::endl; 
  }

void ExecutionListener::on_fill(int id, int size_remaining) {
    if(size_remaining == 0) {
        std::cout << "Fully Filled Trade Happened.";
        std::cout << FULLY_FILLED << " " << id << std::endl;
    } else
    {
        std::cout << "Partial Filled Trade Happened.";
        std::cout << PARTIALLY_FILLED << " " << id << " " << size_remaining << std::endl;
    }
}
