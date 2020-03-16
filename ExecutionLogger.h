#ifndef EXECUTIONLOGGER_H
#define EXECUTIONLOGGER_H
#include "ExecutionListener.h"

class ExecutionLogger: public ExecutionListener {
public:
  void on_trade(double price, int size) override;
  void on_fill(int id, int size_remaining=0) override;
};
#endif

