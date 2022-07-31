#include"OrderBook.h"
#include"CSVReader.h"
#include<map>
#include<algorithm>

using namespace std; 

   /** construct, reading a csv data file */ 
    OrderBook:: OrderBook(string filename) {
       orders =  CSVReader::readCSV(filename); 
    }; 

    /** return vector of all know products in the data set*/ 
    vector<string> OrderBook::getKnownProducts() { 

        vector<string> products; 

        map<string, bool> prodMap; 

        for(OrderBookEntry& e : orders) { 
            prodMap[e.product]  = true; 
        }

        /// now flatten the map to a vecotor of a stirings 
        for (auto const& e : prodMap) { 
            products.push_back(e.first); 
        }
        
        return products; 
    }; 

    /** return vector of all time steps in the data set*/ 
    vector<string> OrderBook::getAllTimeStep() {
        vector <string> timeSteps; 

        map<string, bool> timeMap; 

        for (OrderBookEntry& e : orders) {
            timeMap[e.timestamp] = true; 
        }

        // flatten the map to a vector of strings 
        for (auto const& e : timeMap) {
            timeSteps.push_back(e.first); 
        }; 

        return timeSteps; 
    }

    // /** return vector of Orders according to the sent filters */
    vector<OrderBookEntry> OrderBook::getFilteredOBE(string product, OrderType ordertype, string & timestamp) { 
        
        vector<OrderBookEntry> subOBE; 
        try {
                for (OrderBookEntry & e : orders ) {
                    if ( (product == e.product) && 
                         (ordertype == e.orderType) && 
                         (timestamp == e.timestamp)) {
                            subOBE.push_back(e); 
                         } 
                } 

            } catch (const exception & e)  {
                cout << "Invalid Input! Please try again... " << endl; 
            }; 
            
            return subOBE;
    }

    double OrderBook::getHighPrice(vector<OrderBookEntry> & orders) { 
        double max = orders[0].price; 
        for (OrderBookEntry & e: orders ) {
            if (e.price > max)
                max = e.price; 
        }
        return max; 
    }

    double OrderBook::getlowPrice (vector<OrderBookEntry> & orders) { 

        double min = orders[0].price; 
        for (OrderBookEntry & e: orders ) {
            if (e.price < min)min  = e.price; 
        }
        return min ; 
    }

    // calculating mean 
    double OrderBook::meanPrice(vector<OrderBookEntry> & orders)  {
        double mean; 
        double sum = 0; 
        int count = orders.size(); 
        for (OrderBookEntry & e : orders ) {
            sum += e.price; 
        }
        mean = sum / count; 
        return mean; 
    }

    string OrderBook::getEarliestTime() { 
        return orders[0].timestamp; 
    }; 

    string OrderBook::getNextTime(string timestamp) { 
        sort(orders.begin(), orders.end(), OrderBookEntry::compareByTimestampAsc);
        string next_timesptamp = ""; 
        for(OrderBookEntry & e : orders) { 
            if (e.timestamp > timestamp) { 
                next_timesptamp = e.timestamp; 
                break; 
            }
        }

        if (next_timesptamp == "") { 
            next_timesptamp = orders[0].timestamp; 
        }

        return next_timesptamp; 
    }; 

    string OrderBook::getPreviousTime(string timestamp) { 
        sort(orders.begin(), orders.end(), OrderBookEntry::compareByTimestampDesc);

        string prev_timestamp = ""; 
        for(OrderBookEntry & e : orders) { 
            if (e.timestamp < timestamp) { 
                prev_timestamp = e.timestamp; 
                break; 
            }
        }

        if (prev_timestamp == "") { 
            prev_timestamp = orders[0].timestamp; 
        }

        return prev_timestamp; 
    };
