#ifndef ORDERBOOKRBT_H
#define ORDERBOOKRBT_H

#include <set>
#include <vector>

#include "OrderBook.h"

class OrderBookRBT : public OrderBook {
public:
	OrderBookRBT() : seq_num(0) {}
	void add_order(int id, bool side, double price, int size) override;
	void cancel_order(int id) override;
	void set_execution_listener(ExecutionListener* listener) override {
		this->listener = listener;
	}

private:
	void print_books();

	struct OrderInfo {
		int id;
		double price;
		mutable int size;
		int seq_num;
	};

	struct CompAsk {
		bool operator()(const OrderInfo& a, const OrderInfo& b) {
			if(a.price != b.price) { return a.price < b.price; }
			return a.seq_num < b.seq_num;
		}
	};

	struct CompBid {
		bool operator()(const OrderInfo& a, const OrderInfo& b) {
			if(a.price != b.price) { return a.price > b.price; }
			return a.seq_num < b.seq_num;
		}
	};

	int seq_num;
	std::set<OrderInfo, CompAsk> _askBook;
	std::set<OrderInfo, CompBid> _bidBook;
	ExecutionListener* listener;
};
#endif
