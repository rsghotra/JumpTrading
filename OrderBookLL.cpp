#include "OrderBookLL.h"

void OrderBookLL::match_order(int id, bool side, double price, int size) {
	Book &askBook = ask_book;
	Book &bidBook = bid_book;
	if(side) {
		auto it = bidBook.levels.begin();
		if(it == bidBook.levels.end() || it->price < price) {
			add_order(id, side, price, size);
		}
		while( it!= bidBook.levels.end() &&	 size > 0 && it->price >= price) {
			double tradePrice = it->price;
			int tradeSize = 0;
			if(it->num_nodes == 0) {
				std::cerr << "OrderBookLL.match_order: Bid Book LevelNodeList is empty.";
			}
			auto tradeNodeItr = it->nodes.begin();
			tradeSize = std::min(size, tradeNodeItr->size);
			size -= tradeSize;
			tradeNodeItr->size -= tradeSize;
			listener->on_trade(tradePrice, tradeSize);
			listener->on_fill(id, size);
			listener->on_fill(tradeNodeItr->id, tradeNodeItr->size);
			if(tradeNodeItr->size == 0) {
				tradeNodeItr = it->nodes.erase(tradeNodeItr);
			}
		}
		if(size != 0) {
			add_order(id, side, price, size);
		}
	} else {
		auto it = askBook.levels.begin();
		if(it == askBook.levels.end() || it->price > price) {
			add_order(id, side, price, size);
		}
		while(it != askBook.levels.end() && size > 0 && it->price <= price) {
			double tradePrice = it->price;
			int tradeSize = 0;
			if(it->num_nodes == 0) {
				std::cerr << "OrderBookLL.match_order: Ask Book LevelNodeList is empty.";
			}
			auto tradeNodeItr = it->nodes.begin();
			tradeSize = std::min(size, tradeNodeItr->size);
			size -= tradeSize;
			tradeNodeItr->size -= tradeSize;
			listener->on_trade(tradePrice, tradeSize);
			listener->on_fill(id, size);
			listener->on_fill(tradeNodeItr->id, tradeNodeItr->size);
			if(tradeNodeItr->size == 0) {
				tradeNodeItr = it->nodes.erase(tradeNodeItr);
			}
		}
		if(size != 0) {
			add_order(id, side, price, size);
		}
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

