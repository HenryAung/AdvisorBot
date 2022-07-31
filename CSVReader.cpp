#include"CSVReader.h"
#include<fstream>
#include<iostream>
#include<string>

using namespace std; 

CSVReader::CSVReader()  { 

}

vector<OrderBookEntry> CSVReader::readCSV(string csvFilename) {
    vector<OrderBookEntry> entries; 

     /* opening the file*/ 
    ifstream csvFile {csvFilename}; 
    string line; 

    if (csvFile.is_open()) { 
        while (getline(csvFile, line)) {
                try { 
                    OrderBookEntry obe = stringsToOBE(tokenise(line, ','));
                    entries.push_back(obe); 
                } catch (exception& e) {
                    // cout << "CSVReader::readCSV --> read bad data.. " << endl;
                } // end of while 
            }
        }
     
        return entries; 
    } ; 

vector<string> CSVReader::tokenise(string csvLine, char seperator) {
    // string vector tokens ## stores the tokens 
    vector<string> tokens;

    signed int start, end; 
    string token; 

    start = csvLine.find_first_not_of(seperator, 0); 

    do { 
        end = csvLine.find_first_of(seperator, start); 

        if (start == csvLine.length() || start == end) 
            break ;

        if (end >= 0) 
            token = csvLine.substr(start, end - start); 
        else 
            token = csvLine.substr(start, csvLine.length() - start); 

        tokens.push_back(token); 
        start = end + 1;  }

    while (end >0 ) ; 

    return tokens; 
    }; 
    
OrderBookEntry CSVReader::stringsToOBE(vector<string> tokens) {

    double price, amount; 

    if (tokens.size() != 5 ) {     // checking the line has missing values 
            //    cout << "CSVReader::stringsToOBE :: something bad happens in this gabbage line" << endl; 
               throw exception{}; 
            }  
            // now we have five tokens 
    try { 
            price = stod(tokens[3]); 
            amount = stod(tokens[4]); 

        } catch (const exception& e) { 
            // cout << "CSVReader::stringsToOBE :: bad float" << tokens[3] << endl; 
            // cout << "CSVReader::stringsToOBE :: bad float" << tokens[4] << endl;
            throw; 
        }; 

    OrderBookEntry obe {
        price,
        amount ,
        tokens[0], 
        tokens[1], 
        OrderBookEntry::stringToOrderType(tokens[2])};  

    return obe; 
}; 
