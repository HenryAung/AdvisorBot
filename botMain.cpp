#include<iostream> 
#include<string>
#include<cmath>
#include"botMain.h"
#include"OrderBook.h"
#include"OrderBookEntry.h"
#include"CSVReader.h"
#include<map>

using namespace std; 


botMain::botMain() {

}; 

void botMain::init() { 

    vector<string> userInput;

    currentTime = OrderBook.getEarliestTime(); 
    
    while (true) { 
        printMenu(); 
        userInput = getUserInput(); 
        processUserInput(userInput);
    }
};

void botMain:: printMenu () { 
    cout << "                                                      " << endl; 
    cout << "******************* ADVISOR BOT ******************* " << endl; 
    cout << "Welcome to ADVISOR BOT for crypto market analysis. "<< endl; 
    cout << "Please enter a command to proceed. "<< endl; 
    cout << "If you don't remember commands, type 'help' for list of all commands. " << endl; 
    cout << "******************* ----------- ******************** " << endl; 
    cout << "                                                      " << endl; 
}; 

void botMain:: help() { 
    cout<< "The avalilable commands are \n1. help \n2. help <cmd> \n3. prod \n4. max \n5. min \n6. avg \n7. predict \n8. time \n9. step \n10. prev \n11. market stats \n12. market gainers \n13. market losers " << endl; 
    cout << "                                                      " << endl; 
}

// printing purposes of all codes 
void botMain:: prodPurpose() { 
    cout << "- Purpose :: To list all available products " << endl;                                                                   
    cout << "- Command :: prod" << endl; 
    cout << "- Eg      :: user> prod" << endl; 
    cout << "             advisorBot> ETH/BTC, DOGE/BTC, ... " << endl; 
    cout << "                                                      " << endl; 
}

void botMain::maxPropuse() {
        cout << "- Purpose :: To find maximum bid or ask for product in current time step" << endl;                                         
		cout << "- Command :: max product bid/ask " << endl; 
		cout << "- Eg      :: user> max ETH/BTC bid " << endl; 
		cout << "             advisorBot> The maximum ask for ETH/BTC is 1.0  " << endl; 
        cout << "                                                      " << endl; 
}

void botMain::minPurpose() {
    cout << "- Purpose :: To find minimum bid or ask for product in current time step" << endl;                          
    cout << "- Command :: min product bid/ask " << endl; 
    cout << "- Eg      :: user> min ETH/BTC bid " << endl; 
    cout << "             advisorBot> The minimum ask for ETH/BTC is 1.0  " << endl; 
    cout << "                                                      " << endl; 
}

void botMain::avgPurpose() { 
        cout << "- Purpose :: To compute average ask price or bid price for the sent product over the sent number of time steps. " << endl;  
		cout << "- Command :: avg product ask/bid timesteps " << endl; 
		cout << "- Eg      :: user> avg ETH/BTC ask 10  " << endl; 
		cout << "             advisorBot> The average ETH/BTC ask price over the last 10 timesteps was 1.0. " << endl; 
        cout << "                                                      " << endl; 
}

void botMain::predictPurpose() { 
    cout << "- Purpose :: To predict maximum or minimum ask or bid price for the sent product for the next time step. " << endl;            
    cout << "- Command :: predict max/min product ask/bid " << endl; 
    cout << "- Eg      :: user> predict max ETH/BTC bid " << endl; 
    cout << "             advisorBot> The average ETH/BTC ask price over last 10 time steps was" << endl; 
    cout << "                                                      " << endl; 
}; 

void botMain::timePurpose() {
    cout << "- Purpose :: To state current time in dataset, i.e which timeframe are we looking at" << endl;                                  
    cout << "- Command :: time" << endl; 
    cout << "- Eg      :: user> time 	" << endl; 
    cout << "             advisorBot> 2020/03/17 17:01:24" << endl; 
    cout << "                                                      " << endl; 
}; 

void botMain::stepPrupose() {
        cout << "- Purpose :: To move next time step " << endl;                                                                                        
		cout << "- Command :: step " << endl; 
		cout << "- Eg      :: user> step" << endl; 
		cout << "             advisorBot> now at 2020/03/17 17:01:30 " << endl; 
        cout << "                                                      " << endl; 
}; 

void botMain::prevPurpose() {
        cout << "- Purpose :: To move previous time step " << endl;                                                                                        
		cout << "- Command :: prev " << endl; 
		cout << "- Eg      :: user>  prev" << endl; 
		cout << "             advisorBot> now at 2020/03/17 17:01:30 " << endl; 
        cout << "                                                      " << endl; 
}; 

void botMain::marketStatsPurpose() {
        cout << "- Purpose :: To print out market statistics at current time step " << endl;                                                                                        
		cout << "- Command :: market stats " << endl; 
		cout << "- Eg      :: user> market stats" << endl; 
		cout << "             advisorBot> Maximum ask price for current time step is 0.3324 " << endl; 
        cout << "                         Minimum ask price for current time step is 0.3324"  << endl; 
        cout << "                         Average ask price for current time step is 0.3324. " << endl;
        cout << "                                                      " << endl; 
}; 

void botMain::marketGainersPurpose() {
        cout << "- Purpose :: To print out price increasing product in the market at current time step " << endl;                                                                                        
		cout << "- Command :: market gainers " << endl; 
		cout << "- Eg      :: user> market gainers" << endl; 
		cout << "             advisorBot> The percentage increase for ETH/BTC ASK price is : 0.334 %. " << endl; 
        cout << "                                                      " << endl; 
}; 

void botMain::marketLosersPurpose() {
        cout << "- Purpose :: To print out price increasing product in the market at current time step " << endl;                                                                                        
		cout << "- Command :: market losers " << endl; 
		cout << "- Eg      :: user> market losers" << endl; 
		cout << "             advisorBot> The percentage decrease for ETH/BTC ASK price is : 0.334 %. " << endl; 
        cout << "                                                      " << endl; 
}; 


// return the string message of product list 
void botMain::listProduct() {
    vector<string> entries = OrderBook.getKnownProducts(); 
    cout << "Avaliable Products are :: " << endl; 
    for (string const& p : entries) { 
        cout << p << endl; 
    }; 
}; 

// returing the mininmum value of product in current time stamp
void botMain::min(vector<string>tokens) {
   
    OrderType orderType = OrderBookEntry::stringToOrderType(tokens[2]); // changing data type from string to ordertype
    vector<OrderBookEntry> entries = OrderBook.getFilteredOBE(tokens[1], orderType, currentTime);  // filtering the data set
    cout << "                                                                      " << endl; 
    cout << "Current time frame is  " << currentTime << endl; 
    cout << "Minimum " << tokens[2] << " for " << tokens[1] << " in current time step is  " << OrderBook::getlowPrice(entries) << endl; 
    cout << "                                                                      " << endl; 
        
};

// returning the maximum value of product in current time stamp
void botMain::max(vector<string>tokens) {

            OrderType orderType = OrderBookEntry::stringToOrderType(tokens[2]); 
            vector<OrderBookEntry> entries = OrderBook.getFilteredOBE(tokens[1], orderType, currentTime); 
            cout << "                                                                      " << endl; 
            cout << "Current time frame is  " << currentTime << endl; 
            cout << "Maximum " << tokens[2] << " for " << tokens[1] << " in current time step is  " << OrderBook::getHighPrice(entries) << endl; 
            cout << "                                                                      " << endl; 
};

//  return average value by using moving average algorithm
double botMain::calculateAvg(vector<string>tokens) {

    OrderType orderType = OrderBookEntry::stringToOrderType(tokens[2]); // changing data type from string to ordertype 
    int inputTimeStep = stoi(tokens[3]); 
    int totalTimeStep = OrderBook.getAllTimeStep().size(); 


    vector<OrderBookEntry> subOBE; 

    // filtering the data according to input command
    for (int i = 0; i < inputTimeStep; i++ ) {
        
        vector<OrderBookEntry> entries = OrderBook.getFilteredOBE(tokens[1], orderType, currentTime ); 
        
        for (int j = 0; j < entries.size(); j++) {
            subOBE.push_back(entries[j]);
        }
        currentTime = OrderBook.getPreviousTime(currentTime); // for looping the previous time with input time steps 
    }; 
     
    double avg = OrderBook.meanPrice(subOBE); // calculating average price 

    // returning to the current time 
    for (int i = 0; i < inputTimeStep; i ++) {
        currentTime = OrderBook.getNextTime(currentTime); 
    }

    return avg; 
    
}; 

// returning average result message according to the command 
void botMain::avg(vector<string>tokens) {

        double avg = botMain::calculateAvg(tokens); 
        cout << " This average value is calculated by using simple moving average algoirthms " << endl; 
        cout<< " The average " << tokens[1] << " "<< tokens[2] << " price over the last " <<  tokens[3] << " timesteps was " << avg << endl;

}

// return upperbound value for the last 5 timestamps by using Bollinger Band Algorithm.
double botMain::calculateUBPrediction (vector<string>tokens) {
    
    OrderType orderType = OrderBookEntry::stringToOrderType(tokens[3]); 
    vector<string> timestemps = OrderBook.getAllTimeStep(); 
    int totalTimeSteps = OrderBook.getAllTimeStep().size(); 
    int lastStep = 5; // data has been filtered for last 5 steps

    vector<OrderBookEntry> subOBE; 

    //filtering the data set accroding to input command  
    for (int i = 0; i < lastStep ; i++ ) {
        vector<OrderBookEntry> entries = OrderBook.getFilteredOBE(tokens[2], orderType, currentTime); 
        
        for (int j = 0; j < entries.size(); j++) {
            subOBE.push_back(entries[j]);
        }
    currentTime = OrderBook.getPreviousTime(currentTime); // for looping the previous time with input time steps 
    }; 

    double movingAvg = OrderBook.meanPrice(subOBE); // calculating Moving average 

    // calculating standard deviation for Upperbound 
    double stdDev; 
    double square_diff; 
    double sumOfSquare; 
    for (OrderBookEntry & e: subOBE) {
        square_diff = (e.price - movingAvg) * (e.price - movingAvg); 
        sumOfSquare += square_diff; 
    }
    stdDev = sqrt((sumOfSquare) / subOBE.size()); 


    // calculating UpperBound
    int numberOfStdDev = 2; 
    double upperBound; 
    upperBound = movingAvg + numberOfStdDev * stdDev; 
    return upperBound;       
    
}; 

// retrun lowerbound value for the last 5 timestamps 
double botMain::calculateLBPrediction(vector<string>tokens) {
     
    OrderType orderType = OrderBookEntry::stringToOrderType(tokens[3]); 
    vector<string> timestemps = OrderBook.getAllTimeStep(); 
    int totalTimeSteps = OrderBook.getAllTimeStep().size(); 
    int lastStep = 5; // data has been filtered for last 5 steps

    // filtering the data set according the to sent data 
    vector<OrderBookEntry> subOBE; 
    for (int i = 0; i < lastStep ; i++ ) {

        vector<OrderBookEntry> entries = OrderBook.getFilteredOBE(tokens[2], orderType, currentTime); 
        for (int j = 0; j < entries.size(); j++) {
            subOBE.push_back(entries[j]);}

    currentTime = OrderBook.getPreviousTime(currentTime); // for looping the previous time with input time steps 
    }; 

    
    double movingAvg = OrderBook.meanPrice(subOBE); // calculating Moving average 

    // calculating standard deviation for lowerbound  
    double stdDev; 
    double square_diff; 
    double sumOfSquare; 
    for (OrderBookEntry & e: subOBE) {
        square_diff = (e.price - movingAvg) * (e.price - movingAvg); 
        sumOfSquare += square_diff; 
    }
    stdDev = sqrt((sumOfSquare) / subOBE.size()); 


    // calculating lower bound 
    int numberOfStdDev = 2; 
    double lowerBound; 
    lowerBound = movingAvg - numberOfStdDev * stdDev; 
    return lowerBound;    
    
}; 

// return prediction result message according to the command 
void botMain::predict(vector<string>input) {

        cout << "This prediction is calculated by using Bollinger Band Algorithm. " << endl;

        double prediction; 
        if (input[1] == "min") {
            prediction = botMain::calculateLBPrediction(input); 
            cout << " The lower bound value for the product " << input[2] << " " << input[3] << " price over the last 5 timesteps was " << prediction << endl; 
        } else if (input[1] == "max") {
            prediction = botMain::calculateUBPrediction(input); 
            cout << "The upper bound value for the product " << input[2] << " " << input[3] << " price over the last 5 timesteps was " << prediction << endl; 
        }
         
        

}

// retrun time message 
void botMain::time() { 
    cout << "Current Time Frame is :: " << currentTime << endl; 
}; 

// advancing to the next time step and printing out current time message .. 
void botMain::step() {
    cout << "Going to next time frame ..... " << endl; 
    currentTime = OrderBook.getNextTime(currentTime); 
    botMain::time(); 
}

// retrieving to the previous time step and printing out current time message .. 
void botMain::prev() {
    cout << " Going to previous time frame .... " <<endl; 
    currentTime = OrderBook.getPreviousTime(currentTime); 
    botMain::time(); 
}

// retruning market statistics in string format 
void botMain::printMarketStats() {
    
    for (string const & p : OrderBook.getKnownProducts()) { 
        
        vector<OrderBookEntry> ask_entries = OrderBook.getFilteredOBE(p, OrderType::ask, currentTime); 
        vector<OrderBookEntry> bid_entries = OrderBook.getFilteredOBE(p, OrderType::bid , currentTime); 

        cout << "Asks seen for " << p << " : " << ask_entries.size() << endl; 
        cout << "Maximum ask price for current time step is " << p << " : " << OrderBook::getHighPrice(ask_entries) << endl; 
        cout << "Minimum ask price for current time step is " << p << " : " << OrderBook::getlowPrice(ask_entries) << endl;
        cout << "Average ask price for current time step is " << p << " : " << OrderBook::meanPrice(ask_entries) << endl; 
        cout << "                                                        " << endl;

        cout << "Bids seen for " << p << " : " << bid_entries.size() << endl; 
        cout << "Maximum bid price for current time step is " << p << " : " << OrderBook::getHighPrice(bid_entries) << endl; 
        cout << "Minimum bid price for current time step is " << p << " : " << OrderBook::getlowPrice(bid_entries) << endl;
        cout << "Average bid price fo r current time step is " << p << " : " << OrderBook::meanPrice(bid_entries) << endl; 
        cout << "                                                        " << endl;
        cout << "######################################################" << endl;  
    }; 
}

// printing the percentage increasing product 
void botMain::marketGainers() {
    map<string, double> askPercentageMap; 
    map<string, double> bidPercentageMap;  

    for (string const & p : OrderBook.getKnownProducts()) {

        vector<OrderBookEntry> current_ask_entries = OrderBook.getFilteredOBE(p, OrderType::ask, currentTime);
        vector<OrderBookEntry> current_bid_entries = OrderBook.getFilteredOBE(p, OrderType::bid, currentTime);  
        double currentAskAvg = OrderBook.meanPrice(current_ask_entries); 
        double currentBidAvg = OrderBook.meanPrice(current_bid_entries);
        currentTime = OrderBook.getPreviousTime(currentTime); 


        vector<OrderBookEntry> previous_ask_entries = OrderBook.getFilteredOBE(p, OrderType::ask, currentTime);
        vector<OrderBookEntry> previous_bid_entries = OrderBook.getFilteredOBE(p, OrderType::bid, currentTime);
        double previousAskAvg = OrderBook.meanPrice(previous_ask_entries); 
        double previousBidAvg = OrderBook.meanPrice(previous_bid_entries); 
        currentTime = OrderBook.getNextTime(currentTime); 
 
        double askPercentageChange = (currentAskAvg - previousAskAvg) / previousAskAvg * 100 ; 
        double bidPercentageChange = (currentBidAvg - previousBidAvg) / previousBidAvg * 100 ; 

        askPercentageMap[p] = askPercentageChange; 
        bidPercentageMap[p] = bidPercentageChange;

    }; 

    for (auto & e : askPercentageMap) { 
        if  (e.second > 0 ) {
            cout << "The percentage increase for " << e.first << " ASK price is : " << e.second << " %." << endl; 
        } 
    } 
}

// printing out percentage decreasing product  
void botMain::marketLosers() {
    map<string, double> askPercentageMap; 
    map<string, double> bidPercentageMap;  

    for (string const & p : OrderBook.getKnownProducts()) {

        vector<OrderBookEntry> current_ask_entries = OrderBook.getFilteredOBE(p, OrderType::ask, currentTime);
        vector<OrderBookEntry> current_bid_entries = OrderBook.getFilteredOBE(p, OrderType::bid, currentTime);  
        double currentAskAvg = OrderBook.meanPrice(current_ask_entries); 
        double currentBidAvg = OrderBook.meanPrice(current_bid_entries);
        currentTime = OrderBook.getPreviousTime(currentTime); 


        vector<OrderBookEntry> previous_ask_entries = OrderBook.getFilteredOBE(p, OrderType::ask, currentTime);
        vector<OrderBookEntry> previous_bid_entries = OrderBook.getFilteredOBE(p, OrderType::bid, currentTime);
        double previousAskAvg = OrderBook.meanPrice(previous_ask_entries); 
        double previousBidAvg = OrderBook.meanPrice(previous_bid_entries); 
        currentTime = OrderBook.getNextTime(currentTime); 
 
        double askPercentageChange = (currentAskAvg - previousAskAvg) / previousAskAvg * 100 ; 
        double bidPercentageChange = (currentBidAvg - previousBidAvg) / previousBidAvg * 100 ; 

        askPercentageMap[p] = askPercentageChange; 
        bidPercentageMap[p] = bidPercentageChange;
    }; 

    for (auto & e : bidPercentageMap) {
        if (e.second < 0) {
            cout << "The percentage decrease for " << e.first << " BID price is : " << e.second << " %." << endl; 
        } 
    }; 

}

// getting user input 
vector<string> botMain::getUserInput() { 

    cout << "Type your command here : " << endl; 
    string userInput; 
    getline(cin, userInput);  

    vector<string> tokens = CSVReader::tokenise(userInput, ' ');
        
    cout << "You typed : " << userInput << endl; 
    cout << "                                    " << endl; 

    system("cls"); 
    return tokens; 
}; 

// processing the program according to the user input command 
void botMain::processUserInput(vector<string> input) { 

    if (input.size() == 1) {
        if (input[0] == "help") {
        botMain::help(); 
        } else if (input[0] == "prod") { 
        botMain::listProduct();    
        } else if (input[0] == "time") {
            botMain::time(); 
        } else if (input[0] == "step") { 
            botMain::step();
        } else if (input[0] == "prev") {
            botMain::prev(); 
        } else { 
            cout << "Invalid input. Please enter the correct command. " << endl;
            cout << "                                                      " << endl; 
        };

    } else if ( input.size() == 2) {
        if (input[0] == "help" && input[1] == "prod") { 
            botMain::prodPurpose(); 
        } else if (input[0] == "help" && input[1] == "max") { 
            botMain::maxPropuse();
        } else if (input[0] == "help" && input[1] == "min") { 
            botMain::minPurpose();
        } else if (input[0] == "help" && input[1] == "avg") { 
            botMain::avgPurpose(); 
        } else if (input[0] == "help" && input[1] == "predict") { 
            botMain::predictPurpose(); 
        } else if (input[0] == "help" && input[1] == "time") { 
            botMain::timePurpose(); 
        } else if (input[0] == "help" && input[1] == "step") { 
            botMain::stepPrupose(); 
        } else if (input[0] == "market" && input[1] == "stats") {
            botMain::printMarketStats(); 
        } else if (input[0] == "market" && input[1] == "gainers") {
            botMain::marketGainers(); 
        } else if (input[0] == "market" && input[1] == "losers") {
            botMain::marketLosers(); 
        }
        else { 
            cout << "Invalid input. Please enter the correct command. " << endl;
            cout << "                                                      " << endl; 
        };

    } else if (input.size() == 3) {
        if (input[0] == "min") {
            botMain::min(input); 
        } else if (input[0] == "max") {
            botMain::max(input); 
        } else if (input[2] == "stats") {
            botMain::marketStatsPurpose(); 
        } else if (input[2] == "gainers") {
            botMain::marketGainersPurpose(); 
        } else if (input[2] == "losers") {
            botMain :: marketLosersPurpose(); 
        } else { 
            cout << "Invalid input. Please enter the correct command. " << endl;
            cout << "                                                      " << endl; 
        };

    } else if (input.size() == 4) {
        if (input[0] == "avg") {
            botMain::avg(input);
        } else if (input[0] == "predict") {
            botMain::predict(input);
        } else { 
            cout << "Invalid input. Please enter the correct command. " << endl;
            cout << "                                                      " << endl; 
        };
    } 
}; 

