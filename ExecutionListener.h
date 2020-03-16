#ifndef EXECUTIONLISTENER_H
#define EXECUTIONLISTENER_H
#include <iostream>

class ExecutionListener {
public:
  virtual void on_trade(double price, int size)=0;
  virtual void on_fill(int id, int size_remaining=0)=0;
};

#endif
