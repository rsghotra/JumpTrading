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
    void _updateAskBook() {

    }

    void _updateBidBook() {

    }
    public:
        OrderBook() {
        }
        ~OrderBook() {};
        //createOrderNode->createLevelNodeList->createLevelNode
        Level* createOrderNode(int id, double price, int size) {
            //when it will create level it will also create LevelNode for the entry itself.
            Level *levelPtr = new Level;
            levelPtr->price = price;
            levelPtr->nodes = createLevelNodeList(levelPtr, id, size);
            levelPtr->num_nodes = levelPtr->nodes.size();
            return levelPtr;
        }
        //insertBookNode->createOrderNode->createLevelNodeList->createLevelNode
        void insertOrderNode(int id, bool side, double price, int size) {
            Level* level = createOrderNode(id, price, size);
            if(side) {
                ask_book.levels.push_back(level);
                std::list<LevelNode*>::iterator iter = level->nodes.begin();
                //order_map(id, iter);
            } else {
                //bid_book insert
                bid_book.levels.push_back(level);
            }
        }

        void updateOrderBook() {
            _updateAskBook();
            _updateBidBook();
        }

        //createLevelNodeList->createLevelNode
        std::list<LevelNode*> createLevelNodeList(Level* parent, int id, int size) {
            //createLevelNode could be called both by createLevel and also when order comes for same price
            LevelNode *levelNodePtr = createLevelNode(parent, id, size);
            std::list<LevelNode*> newLevelNodeList;
            newLevelNodeList.push_back(levelNodePtr);
            return newLevelNodeList;
        }

        //createLevelNode
        LevelNode* createLevelNode(Level* parent, int id, int size) {
            //createLevelNode could be called both by createLevel and also when order comes for same price
            LevelNode *levelNodePtr = new LevelNode;
            levelNodePtr->id = id;
            levelNodePtr->size = size;
            levelNodePtr->level = parent;
            return levelNodePtr;
        }

        void cancelOrder(int id) {
            //find out LevelNode using unordered map to find parents
            //if there is only one node in the LevelNode list then remove Level as well
            //else remove respective node from the list
        }

        void order_matcher(int id, bool side, double price, int size) {}
        //partial fill - update the data structure

        //insert in the data structure
        void add_order(int id, bool side, double price, int size) {}

        //iterate order book
        void iterateOrderBook(OrderBook &book) {
            if(book.ask_book.levels.size() != 0) {
                std::cout << "Current SALE Ledger." << std::endl;
                std::list<Level*>::iterator iter = book.ask_book.levels.begin();
                while(iter != book.ask_book.levels.end()) {
                    std::cout << "Level:: " << (*iter)->price << "\tNumber of Resting Orders:: " 
                    << (*iter)->num_nodes << std::endl;
                    iterateLevelNodeList((*iter)->nodes);
                    std::cout << "==>==>==>==>==>" << std::endl;
                    ++iter;
                }
            }
            if(book.bid_book.levels.size() != 0) {
                //iterate over bid_book
                std::cout << "Current BUY Ledger." << std::endl;
                std::list<Level*>::iterator iter = book.bid_book.levels.begin();
                while(iter != book.bid_book.levels.end()) {
                    std::cout << "Level:: " << (*iter)->price << "\tNumber of Resting Orders:: " 
                    << (*iter)->num_nodes << std::endl;
                    iterateLevelNodeList((*iter)->nodes);
                    std::cout << "<==<==<==<==<==" << std::endl;
                    ++iter;
                }
            }
        }

        //iterate LevelNode
        void iterateLevelNodeList(std::list<LevelNode*> levelNodeList) {
            if(levelNodeList.size()) {
                //iterate over levelNodeList
                std::list<LevelNode*>::iterator iter = levelNodeList.begin();
                while(iter != levelNodeList.end()) {
                    std::cout << "Order ID:: " << (*iter)->id << "\tSize:: " << (*iter)->size 
                    << "\tParent Level:: " << (*iter)->level->price << std::endl;
                    iter++;
                }
            }
        }
};
#endif