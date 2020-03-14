#ifndef QUOTES_H
#define QUOTES_H

#include "Clock.h"
#include <iostream>
#include <map>
#include <unordered_map>
#include <memory>
#include <fstream>
#include <string>
#include <future>
#include <thread>
#include <cstdlib>
#include <time.h>
using namespace std;
namespace feed {
    class Quotes{
        public:
            Quotes(string Time, string ExchangeCode, string Bid, string Ask,
            string BidSize, string AskSize):
            tine(0),
            bids(0.0f),
            asks(0.0f),
            bid_size(0),
            ask_size(0),
            exchange_code(0),
            time_from_file(Time),
            exchange_code_from_file(ExchangeCode),
            bids_from_file(Bid),
            asks_from_file(Ask),
            bid_size_from_file(BidSize),
            ask_size_from_file(AskSize),
            BIDtickCount(0),
            ASKtickCount(0),
            matchSwitch(false),
            ExchangeTradeOccured(0)
            {

            }

            virtual ~Quotes()
            {
                
            }

    };
}


#endif