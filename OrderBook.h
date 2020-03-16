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
    Book ask_book; //instantiation
    Book bid_book; //instantiation

    // Hash table to get LevelNode* from order id
    std::unordered_map<int, std::list<LevelNode*>::iterator> order_map;
    public:
        OrderBook() {
        }
        ~OrderBook() {};
        //method to create a Level by price which will call createLevelNode
        Level* createBookNode(int id, double price, int size) {
            //when it will create level it will also create LevelNode for the entry itself.
            Level *levelPtr = new Level;
            levelPtr->price = price;
            levelPtr->nodes = createLevelNode(levelPtr, id, size);
            levelPtr->num_nodes = levelPtr->nodes.size;
            return levelPtr;
        }

        void insertBookNode(bool side, Level* level) {
            if(side) {
                //ask_book insert
                //createBookNode
                ask_book.levels.push_back(level);
                //because it is a new order with unique order id. corresponding data will be entered order_map
                //initialize the iterator to the LevelNode
                std::list<LevelNode*>::iterator it;
                
            } else {
                //bid_book insert
                bid_book.levels.push_back(level);
            }
        }

        std::list<LevelNode*> createLevelNode(Level* parent, int id, int size) {
            //createLevelNode could be called both by createLevel and also when order comes for same price
        }

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