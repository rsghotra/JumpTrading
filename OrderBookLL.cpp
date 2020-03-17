#include "OrderBookLL.h"

void OrderBookLL::match_order(int id, bool side, double price, int size) {
	//if sell side
	if(side) {
		Book &book = bid_book;
		auto it = book.levels.begin();
		while ( it != book.levels.end() && it->price < price ) it++;
		//Now if end of bid book is reached and no eligible bid found
		if ( it == book.levels.end()) {
			it = book.levels.insert( it, Level{price});
			//level_map[price] = it;
			order_map[id] = it->nodes.insert(it->nodes.end(), {id, size, side, it});
		}
		std::cout << "==============================" << std::endl;
		//price-the-time rule, Best bid will be the last element of the list.
		auto best_bid_node = book.levels.rbegin();
		std::cout << "==============================" << std::endl;
		//if eligible Level(s) found then traverse until the last not
		//because list is sorted in ascending order. And, if eligible price is found
		//save the price
	} else {
		//if buy side
		Book &book = ask_book;
		auto it = book.levels.begin();
		//best ask side will be at the beginning of the list
		//therefore no need to go backwards or forward. Just keep processing
		//until order_size == 0 or end of order book is reached.

	}
}

void OrderBookLL::cancel_order(int id) {
	std::cout << "OrderBookLL: cancel_order " << id << "\n";
	if ( order_map.count(id) == 0 ) {
		std::cerr << "Order with id " << id << " does not exist.\n";
		return;
	}
	auto node = order_map[id];
	auto level = node -> level;
	auto &book = (node -> side ) ? ask_book : bid_book;
	level -> nodes.erase(node);
	if ( level->nodes.empty() )
		book.levels.erase(level);
	print_books();
}


void OrderBookLL::add_order(int id, bool side, double price, int size) {
	std::cout << "OrderBookLL: add_order " << id << " " << (side?"buy":"sell") << " " << price << " " << size << '\n';
	if ( side ) {
		Book &book = ask_book;
		auto it = book.levels.begin();
		while ( it != book.levels.end() && it->price < price ) it++;
		if ( it == book.levels.end() || it->price != price ) {
			it = book.levels.insert( it, Level{price});
			//level_map[price] = it;
		}
		order_map[id] = it->nodes.insert(it->nodes.end(), {id, size, side, it});
	} else {
		Book &book = bid_book;
		auto it = book.levels.begin();
		while ( it != book.levels.end() && it->price > price ) it++;
		if ( it == book.levels.end() || it->price != price ) {
			it = book.levels.insert( it, Level{price});
			level_map[price] = it;
		}
		order_map[id] = it->nodes.insert(it->nodes.end(), {id, size, side, it});
	}
	print_books();
}

void OrderBookLL::print_books() {
	std::cout << "bid: [";
	bool firstLevel = true;
	for(const Level& level: bid_book.levels) {
		double price = level.price;
		if (firstLevel) {
			firstLevel = false;
		} else {
			std::cout << ", ";
		}
		std::cout << price << ": ";
		for(const LevelNode& node: level.nodes) {
			std::cout << node.id << " ";
		}
	}
	std::cout << "]\n";

	std::cout << "ask: [";
	firstLevel = true;
	for(const Level& level: ask_book.levels) {
		double price = level.price;
		if (firstLevel) {
			firstLevel = false;
		} else {
			std::cout << ", ";
		}
		std::cout << price << ": ";
		for(const LevelNode& node: level.nodes) {
			std::cout << node.id << " ";
		}
	}
	std::cout << "]\n";
}

