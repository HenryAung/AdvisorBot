#include<iostream> 
#include<string>
#include"botMain.h"

using namespace std; 


botMain::botMain() {

}; 

void botMain::init() { 
    // botGreeting(); 
    string userInput;
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

string botMain::getUserInput() { 

    string userInput;
    cout << "Type your command here : " << endl; 
    getline(cin, userInput);  

    system("cls"); 
    return userInput;  

}

void botMain::processUserInput(string input) { 
    if (input == "help") { 
        cout<< "The avalilable commands are \n1. help, \n2. help<cmd>, \n3. prod, \n4. max, \n5. min, \n6. avg \n7. predict, \n8. time, \n9. step" << endl; 
        cout << "                                                      " << endl; 
    } else if (input == "help prod") { 
        cout << "- To list all available products " << endl;                                                                   
		cout << "- Command :: prod" << endl; 
		cout << "- Eg: user> prod" << endl; 
		cout << "advisorBot> ETH/BTC, DOGE/BTC, ... " << endl; 
        cout << "                                                      " << endl; 
    } else if (input == "help max") { 
        cout << "- to find maximum bid or ask for product in current time step" << endl;                                         
		cout << "- Command :: max product bid/ask " << endl; 
		cout << "- Eg: user> max ETH/BTC bid " << endl; 
		cout << "advisorBot> The maximum ask for ETH/BTC is 1.0  " << endl; 
        cout << "                                                      " << endl; 
    } else if (input == "help min") { 
        cout << "- to find minimum bid or ask for product in current time step" << endl;                          
		cout << "- Command :: min product bid/ask " << endl; 
		cout << "- Eg: user> min ETH/BTC bid " << endl; 
		cout << "advisorBot> The minimum ask for ETH/BTC is 1.0  " << endl; 
        cout << "                                                      " << endl; 
    } else if (input == "help avg") { 
        cout << "- To compute average ask price or bid price for the sent product over the sent number of time steps. " << endl;  
		cout << "- Command :: avg product ask/bid timesteps " << endl; 
		cout << "- Eg: user> avg ETH/BTC ask 10  " << endl; 
		cout << "advisorBot> The average ETH/BTC ask price over the last 10 timesteps was 1.0. " << endl; 
        cout << "                                                      " << endl; 
    } else if (input == "help predict") { 
        cout << "- To predict maximum or minimum ask or bid price for the sent product for the next time step. " << endl;            
		cout << "- Command :: predict max/min product ask/bid " << endl; 
		cout << "- Eg: user> predict max ETH/BTC bid " << endl; 
		cout << "advisorBot> The average ETH/BTC ask price over last 10 time steps was" << endl; 
        cout << "                                                      " << endl; 
    } else if (input == "help time") { 
        cout << "- To state current time in dataset, i.e which timeframe are we looking at" << endl;                                  
		cout << "- Command :: time" << endl; 
		cout << "- Eg: user> time 	" << endl; 
		cout << " advisorBot> 2020/03/17 17:01:24" << endl; 
        cout << "                                                      " << endl; 
    } else if (input == "help step") { 
        cout << "- To move next time step " << endl;                                                                                        
		cout << "- Command :: step " << endl; 
		cout << "- Eg: user> step" << endl; 
		cout << "advisorBot> now at 2020/03/17 17:01:30 " << endl; 
        cout << "                                                      " << endl; 
    } else { 
        cout << "Invalid input. Please enter the correct command. " << endl;
        cout << "                                                      " << endl; 
    };
}; 

void botMain::commandPurpose(string input) {
    
}; 