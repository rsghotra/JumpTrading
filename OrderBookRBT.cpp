#include "OrderBookRBT.h"

void OrderBookRBT::add_order(int id, bool side, double price, int size) {
	std::cout << "OrderBookRBT: add_order " << id << " " << (side?"sell":"buy") << " " << price << " " << size << '\n';
	if (side) {
		int sizeRemaining = size;
		auto it = _bidBook.begin();
		while( it != _bidBook.end() && it->price >= price && size > 0 ) {
			std::cout << "it: " << it->id << " " << it->price << " " << it->size <<"\n";
			double tradePrice = it->price;
			int tradeSize = std::min(size, it->size);

			size -= tradeSize;
			it->size -= tradeSize;

			listener->on_trade(tradePrice, tradeSize);
			listener->on_fill(id, size);
			listener->on_fill(it->id, it->size);

			if(it->size == 0)
				it = _bidBook.erase(it);
		}
		_askBook.insert({id, price, size, seq_num++});
	} else {
		auto it = _askBook.begin();
		while( it != _askBook.end() && it->price <= price && size > 0 ) {
			std::cout << "it: " << it->id << " " << it->price << " " << it->size <<"\n";
			double tradePrice = it->price;
			int tradeSize = std::min(size, it->size);

			size -= tradeSize;
			it->size -= tradeSize;

			listener->on_trade(tradePrice, tradeSize);
			listener->on_fill(id, size);
			listener->on_fill(it->id, it->size);

			if(it->size == 0)
				it = _askBook.erase(it);
		}
		_bidBook.insert({id, price, size, seq_num++});
	}
};

void OrderBookRBT::cancel_order(int id) {
	std::cout << "OrderBookRBT: cancel_order " << id << "\n";
	for(auto it = _askBook.begin(); it!=_askBook.end(); ++it) {
		if(it->id == id) {
			_askBook.erase(it);
			return;
		}
	}
	for(auto it = _bidBook.begin(); it!=_bidBook.end(); ++it) {
		if(it->id == id) {
			_bidBook.erase(it);
			return;
		}
	}
	std::cerr<<"Could not find order: " << id << "\n";
};

void OrderBookRBT::print_books() {
	double price=-1.0;
	bool firstLevel = true;
	std::cout << "bid: [";
	for(const OrderInfo& order: _bidBook) {
		bool newLevel = order.price != price;
		if (newLevel) {
			price = order.price;
			if (firstLevel) {
				firstLevel = false;
			} else {
				std::cout << ", ";
			}
			std::cout << price << ": ";
		}
		std::cout << order.id << "(" << order.seq_num << ")";
	}
	std::cout << "]\n";

	price=-1.0;
	firstLevel = true;
	std::cout << "ask: [";
	for(const OrderInfo& order: _askBook) {
		bool newLevel = order.price != price;
		if (newLevel) {
			price = order.price;
			if (firstLevel) {
				firstLevel = false;
			} else {
				std::cout << ", ";
			}
			std::cout << price << ": ";
		}
		std::cout << order.id << "(" << order.seq_num << ")";
	}
	std::cout << "]\n";
};
