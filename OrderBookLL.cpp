#include <algorithm>
#include "OrderBookLL.h"
#include "Logger.h"

bool match(bool side, double a, double b) {
	if(side)
		return a >= b;
	return a <= b;
}

void OrderBookLL::match_order(int id, bool side, double price, int size) {
	if ( order_map.count(id) != 0 ) {
		LOG(ERROR) << "Order with id " << id << " already exists, not processing.";
		return;
	}
	LOG(DEBUG) << "OrderBookLL: match_order " << id << " " << (side?"buy":"sell") << " " << price << " " << size;
	Book &cross = side? bid_book:ask_book;
	auto it = cross.levels.begin();
	while( it!= cross.levels.end() && size > 0 && match(side, it->price, price) ) {
		double tradePrice = it->price;
		auto node = it->nodes.begin();
		while( node != it->nodes.end() && size > 0 ) {
			int tradeSize = std::min(size, node->size);
			size -= tradeSize;
			node->size -= tradeSize;
			listener->on_trade(tradePrice, tradeSize);
			listener->on_fill(id, size);
			listener->on_fill(node->id, node->size);
			if(node->size == 0) {
				order_map.erase(node->id);
				node = it->nodes.erase(node);
			}
		}
		if (it->nodes.empty()) {
			level_map.erase(it->price);
			it = cross.levels.erase(it);
		}
	}
	if(size != 0) {
		add_order(id, side, price, size);
	}
	print_books();
}

void OrderBookLL::cancel_order(int id) {
	LOG(DEBUG) << "OrderBookLL: cancel_order " << id << "\n";
	if ( order_map.count(id) == 0 ) {
		LOG(ERROR) << "Order with id " << id << " does not exist.";
		return;
	}
	auto node = order_map[id];
	auto level = node -> level;
	auto &book = (node -> side ) ? ask_book : bid_book;
	level -> nodes.erase(node);
	order_map.erase(id);
	if ( level->nodes.empty() )
		book.levels.erase(level);
	print_books();
}

void OrderBookLL::add_order(int id, bool side, double price, int size) {
	LOG(DEBUG) << "OrderBookLL: add_order " << id << " " << (side?"buy":"sell") << " " << price << " " << size;
	if ( side ) {
		Book &book = ask_book;
		std::list<Level>::iterator it;
		if ( level_map.count( price ) ) {
			it = level_map[price];
		} else {
			it = book.levels.begin();
			while ( it != book.levels.end() && it->price < price ) it++;
			if ( it == book.levels.end() || it->price != price ) {
				it = book.levels.insert( it, Level{price} );
				level_map[price] = it;
			}
		}
		order_map[id] = it->nodes.insert(it->nodes.end(), {id, size, side, it});
	} else {
		Book &book = bid_book;
		std::list<Level>::iterator it;
		if ( level_map.count( price ) ) {
			it = level_map[price];
		} else {
			it = book.levels.begin();
			while ( it != book.levels.end() && it->price > price ) it++;
			if ( it == book.levels.end() || it->price != price ) {
				it = book.levels.insert( it, Level{price} );
				level_map[price] = it;
			}
		}
		order_map[id] = it->nodes.insert(it->nodes.end(), {id, size, side, it});
	}
}

void OrderBookLL::print_books() {
	for(int side = 0; side <= 1; side+=1) {
		std::stringstream ss;
		std::string name = side ? "ask" : "bid";
		Book& book = side ? ask_book : bid_book;
		bool firstLevel = true;
		ss << name << ": [";
		for(const Level& level: book.levels) {
			double price = level.price;
			if (firstLevel) {
				firstLevel = false;
			} else {
				ss << ", ";
			}
			ss << price << ":";
			for(const LevelNode& node: level.nodes) {
				ss << " " << node.size;
			}
		}
		ss << "]";
		LOG(INFO) << ss.str();
	}
}
