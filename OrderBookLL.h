#ifndef ORDERBOOKLL_H
#define ORDERBOOKLL_H
#include<iostream>
#include<list>
#include<unordered_map>
#include<vector>

#include "OrderBook.h"

class OrderBookLL : public OrderBook {
	public:
		OrderBookLL() {}
		~OrderBookLL() {};

		void add_order(int id, bool side, double price, int size) override;
		void cancel_order(int id) override;
		void set_execution_listener(ExecutionListener* listener) override {
			this->listener = listener;
		};
		void match_order(int id, bool side, double price, int size) override;
	private:
		struct Level;
		struct LevelNode {
			int id;
			int size;
			bool side;
			std::list<Level>::iterator level;
		};

		struct Level {
			double price;
			int num_nodes;
			std::list<LevelNode> nodes;

			Level (double price) : price(price), num_nodes(0) {}
		};

		struct Book {
			std::list<Level> levels;
		};

		Book ask_book;
		Book bid_book;
		ExecutionListener* listener;

		std::unordered_map<int, std::list<LevelNode>::iterator> order_map;
		std::unordered_map<double, std::list<Level>::iterator> level_map;

	private:
		void print_books();
};
#endif
