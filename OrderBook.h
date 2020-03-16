#ifndef ORDERBOOK_H
#define ORDERBOOK_H
#include<iostream>
#include<list>
#include<unordered_map>

class OrderBook {
private:
    struct Level;
    struct LevelNode {
        int id;
        int size;
        Level* level;
    };

    struct Level {
        double price;
        int num_nodes;
        std::list<LevelNode*> nodes;
    };

    struct Book {
        std::list<Level*> levels;
    };
    Book ask_book;
    Book bid_book;
    //heads
    Book *askBookHead;
    Book *bidBookHead;

    // Hash table to get LevelNode* from order id
    std::unordered_map<int, std::list<LevelNode*>::iterator> order_map;
    public:
        OrderBook() {
            askBookHead = &ask_book;
            bidBookHead = &bid_book;
        }
        ~OrderBook() {};
        std::list<OrderBook::Level*> get_matching_levels() {}

        void order_matcher(int id, bool side, double price, int size) {}
        //partial fill - update the data structure

        //insert in the data structure
        void add_order(int id, bool side, double price, int size) {}
        //call order matcher with same paramterest and additional
        //delete in data structure
        void cancel_order(int id) {}
        //find the corresponding level node from hash map.
        //remove the identified level node.
};
#endif