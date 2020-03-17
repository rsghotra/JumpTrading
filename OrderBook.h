#ifndef ORDERBOOK_H
#define ORDERBOOK_H

#include "ExecutionListener.h"

class OrderBook {
public:
	virtual void add_order(int id, bool side, double price, int size) = 0;
	virtual void cancel_order(int id) = 0;
	virtual void set_execution_listener(ExecutionListener* listener) = 0;
	virtual void match_order(int id, bool side, double price, int size) = 0;
};
#endif
