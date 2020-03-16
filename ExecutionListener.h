#ifndef EXECUTIONLISTENER_H
#define EXECUTIONLISTENER_H
#include <iostream>

class ExecutionListener {
private:
  enum {TRADE_EVENT=2, FULLY_FILLED=3, PARTIALLY_FILLED=5};
public:
  void on_trade(double price, int size);
  void on_fill(int id, int size_remaining=0);
};

#endif