#include <iostream>
#include <stdio.h>
#include <vector>
#include <cstdlib>
#include <limits> // To make sure user input is valid
#include <chrono> // These two last libraries are for sleep_for()
#include <thread>


using namespace std;

void PrintBreak(); //Declare Functions

class Person {   
 public:
	string name;
	vector<string> hand = {};
	string myString; 
	void displayHand();
	void draw(vector<string> &deck);
	void displayWildCount();
	int returnWildCount();
	void discard();
	
	Person(string x) { 
		name = x;
	}
}; 

void Person::displayHand() {
	cout << "\n  " << name << "'s Hand:\n\n ";
	for (int i = 0; i < hand.size(); i++) {
		if (i==(hand.size()-1)) {
			cout << hand.at(i) << endl;
			break;
		}
		cout << hand.at(i) << ", ";
	}
}

void Person::draw(vector<string> &deck) {
	if (deck.size() < 1) {
		cout << "Error: Cannot draw from empty deck." << endl;
		return;
	}
	hand.push_back(deck.at(0));
	deck.erase(deck.begin() + 0);
}

void Person::displayWildCount() {
	cout << name << "'s wild count is: " << returnWildCount() << "\n";
}

int Person::returnWildCount() {
	int wildCount = 0;
	for (int i = 0; i < hand.size(); i++) {
		if (hand.at(i) == "Wild" || hand.at(i) == "Wild Draw Four") {	wildCount++;}		
	}
	return wildCount;
}

void Person::discard() {
	hand = {};
}

vector<string> shuffleToPlayingDeck(std::vector<std::string> orderedDeck) {
	vector<string> shuffledDeck = {};
	
	if (orderedDeck.size() < 1) {
		cout << "Warning: Attempt to shuffle from a empty deck!" << endl;
		return shuffledDeck;
	}
	while (orderedDeck.size() > 0) {
		int cardNum = rand() % orderedDeck.size();
		shuffledDeck.push_back(orderedDeck.at(cardNum));  //Take random card from ordered, put in shuffled
		orderedDeck.erase(orderedDeck.begin() + cardNum); //Remove the card from ordered 
	}
	return shuffledDeck;
}

void DisplayDeck(std::vector<std::string> deck) {
	cout << "\n- Displaying Deck: \n\n";
	while (deck.size() > 0) {
		if (deck.size() == 1) {
			cout << deck.at(0) << "\n";
			deck.erase(deck.begin() + 0);
			break;
		}
		cout << deck.at(0)  << ", ";
		deck.erase(deck.begin() + 0);
	}
	cout << endl;
	return;
}

vector<string> populateDeckUNO() {
	vector<string> organizedDeck;
	
	organizedDeck.push_back("Red 0");
	organizedDeck.push_back("Yellow 0");
	organizedDeck.push_back("Green 0");
	organizedDeck.push_back("Blue 0");
	
	for (int i = 0; i < 4; i++) { //Push nomal uno cards
		for (int j = 1; j < 11; j++) {
			switch (i) {
				case 0:
				organizedDeck.push_back("Red " + to_string(j));
				organizedDeck.push_back("Red " + to_string(j));
				break;
				case 1:
				organizedDeck.push_back("Yellow " + to_string(j));
				organizedDeck.push_back("Yellow " + to_string(j));
				break;
				case 2:
				organizedDeck.push_back("Green " + to_string(j));
				organizedDeck.push_back("Green " + to_string(j));
				break;
				case 3:
				organizedDeck.push_back("Blue " + to_string(j));
				organizedDeck.push_back("Blue " + to_string(j));
				break;
			}
		}
	}
	
	vector<string> actionCards = {"Skip", "Reverse", "Draw Two"};
	
	for (int i = 0; i < 3; i++) { //Push nomal uno cards
		for (int j = 0; j < 4; j++) {
			switch (j) {
				case 0:
				organizedDeck.push_back("Red " + actionCards.at(i));
				organizedDeck.push_back("Red " + actionCards.at(i));
				break;
				case 1:
				organizedDeck.push_back("Yellow " + actionCards.at(i));
				organizedDeck.push_back("Yellow " + actionCards.at(i));
				break;
				case 2:
				organizedDeck.push_back("Green " + actionCards.at(i));
				organizedDeck.push_back("Green " + actionCards.at(i));
				break;
				case 3:
				organizedDeck.push_back("Blue " + actionCards.at(i));
				organizedDeck.push_back("Blue " + actionCards.at(i));
				break;
			}
		}
	}
	
	organizedDeck.push_back("Red Skip");
	organizedDeck.push_back("Red Skip");
	organizedDeck.push_back("Yellow Skip");
	organizedDeck.push_back("Yellow Skip");
	organizedDeck.push_back("Green Skip");
	organizedDeck.push_back("Green Skip");
	organizedDeck.push_back("Blue Skip");
	organizedDeck.push_back("Blue Skip");
	
	for (int i = 0; i < 4; i++) {
		organizedDeck.push_back("Wild");
	}
	for (int i = 0; i < 4; i++) {
		organizedDeck.push_back("Wild Draw Four");
	}
	
	return organizedDeck;
}

void PrintBreak() {
	cout << " Hit Enter to continue.\n"; 
	cin.get();
	cout << "\n-----------------------------------\n\n";
}

string Flip(vector<string> coin) {
	int random = rand() % coin.size();
	return coin.at(random);
}

bool DisplayFullCoinFlip(int runs, float& headsOdds, float& tailsOdds) {
	vector<string> coin = {"Heads", "Tails"};
	int heads = 0;
	int tails = 0;
	string result = "";
	for (int i = 0; i < runs; i++){
		result = Flip(coin);
		if (result == "Heads") { heads++; }
		if (result == "Tails") { tails++; }	
	 headsOdds = ((static_cast<float>(heads) / runs) * 100);
	 tailsOdds = ((static_cast<float>(tails) / runs) * 100);
	}
	cout << "\n Flipping a coin " << runs << " times: \n";
	cout << "\n -------Results--------\n";
	cout << " |\n";
	cout << " | - Number of Heads: " << heads << "  \n";
	cout << " | - Number of Tails: " << tails << "  \n";
	cout << " |                   \n";
	cout << " |  Distribution of Heads:  " << heads << "/" << runs << ", Or " << headsOdds << "%" << endl;
	cout << " |  Distribution of Tails:  " << tails << "/" << runs << ", Or " << tailsOdds << "%" << endl; 
	cout << " ----------------------\n\n";
	if (tails == heads || headsOdds == tailsOdds) { return true; }
	return false; 
}

void displayAllHands(Person &alex, Person &timmy, Person &isaac, Person &ben) {

    Person* players[] = {&alex, &timmy, &isaac, &ben};

    for (Person* player : players) {
        cout << "\033[2K\r"; // Clear current line

        cout << player->name << ": ";

        for (string card : player->hand) {
            cout << card << ", ";
        }

        cout << "\n";
    }
}


////////////////////////////////////////////////////////////////////////////////////

int main() {   
	
	srand(time(0)); //Make the numbers actually random 
	
	cout << "\n Welcome to my program about probability.\n\n"
	" To start, let us experiment with a coin. We know that flipping a coin\n"
    " will be heads 50% of the time, and tails 50% of the time.\n"
	" If we simulate flipping a coin many times, will we end up\n with an even split between heads and tails?\n"
	" Lets start by fliping a coin 10 times and see what happens.\n\n";
	PrintBreak();
	
	float headsOdds1 = 0.0;
	float tailsOdds1 = 0.0;
	float headsOdds2 = 0.0;
	float tailsOdds2 = 0.0;
	float headsOdds3 = 0.0;
	float tailsOdds3 = 0.0;

	bool fiftyFiftyFlag = false;
	int runs = 10;
	
	do {
		fiftyFiftyFlag = DisplayFullCoinFlip(runs, headsOdds1, tailsOdds1);
		if (fiftyFiftyFlag == false) {
			cout << " As we see, with these 10 flips we did not get heads for 50% of the flips, nor tails.\n "
			"What will happen when we do more flips?\n\n";
			cout << " Lets flip it 1,000 times.\n\n";
			PrintBreak();
		}
		else {
			cout << "As you can see, we got heads 50% of the flips, and tails is 50% of the flips."
			" Will this be true if we do it again?\n\n";
			PrintBreak();
		}
	}
	while (fiftyFiftyFlag == true); 
	
	runs = 1000;
	fiftyFiftyFlag = DisplayFullCoinFlip(runs, headsOdds2, tailsOdds2);
	cout << " Now let's try flipping it 10,000,000 times.\n\n";
	cout << " Hit Enter to continue. (This will take a moment.)\n"; 
	cin.get();
	cout << "\n-----------------------------------\n\n";

	runs = 10000000;
	fiftyFiftyFlag = DisplayFullCoinFlip(runs, headsOdds3, tailsOdds3);
	PrintBreak();
	cout << " Here is how the probability has converged as we did more and more flips:\n\n";
	cout << " For ten flips:\n\n   Heads Distribution: " << headsOdds1 << "%\n   Tails Distribution: " << tailsOdds1;
	cout << "%\n\n For a thousand flips:\n\n   Heads Distribution: " << headsOdds2 << "%\n   Tails Distribution: " << tailsOdds2;
	cout << "%\n\n For ten million flips:\n\n   Heads Distribution: " << headsOdds3 << "%\n   Tails Distribution: " << tailsOdds3;
	cout << "\n\n As you can see, as we do more and more flips,\n"
	" the amount of heads and tails we get start to become closer to a 50/50 split.\n\n"
	" This means if we do something random many, many times, and take its average,\n"
	" we will be albe to see approximately the chances of the outcome.\n\n";
	PrintBreak();

	
	// START OF CARD SECTION
	// Features to add: Loading bar, and check if distrubtion changes. Average does not change, Does chance of getting 0 or all 8 wilds change? 
	
	cout << "\n\n Here is a new question: If you split up a deck, does that change the\n "
	"probabilty of getting the cards you want?\n"
	" Let's find out. First, let's get a brand new UNO deck.\n\n";
	PrintBreak();
	
	cout << " - Creating New Deck . . . \n";
	
	vector<string> organizedDeck = populateDeckUNO(); 
	DisplayDeck(organizedDeck);
	PrintBreak();
	
	cout << " - Now Shuffling the deck . . . \n";
	vector<string> deck = shuffleToPlayingDeck(organizedDeck);
	DisplayDeck(deck);
	PrintBreak();

	Person alex("Alex"), timmy("Timmy"), isaac("Isaac"), ben("Ben");
	Person* people[4] = {&alex, &timmy, &isaac, &ben};
	
	int alexTotalWildCount = 0;
	
	cout << " Now that we have a 1 shuffled Uno Deck, let us\n"
	" deal it out to four people, 1 by 1.\n\n"
	"- Showing an example of dealing out the entire deck . . . \n\n";

	//DISPLAY LOGIC ANIMATION
	
	int sleepLength  = 3000;
	//int sleepLength  = 0; //FOR DEBUG
	int loopCount = 0;
	while (!deck.empty()) {
		if (loopCount == 0) { 
			cout << "\033[H"; //Move cursor to top left
			cout << "\033[2J"; // Clear screen
			DisplayDeck(deck);
			alex.displayHand();
			timmy.displayHand();
			isaac.displayHand();
			ben.displayHand();
			this_thread::sleep_for(chrono::milliseconds(sleepLength));
		} 
		
		if (loopCount == 1) { 
			sleepLength  = 500; 
			//sleepLength  = 0; //FOR DEBUG
		} 
		
		for (int j = 0; j < 4; j++) {
			cout << "\033[H";
			cout << "\033[2J";
			people[j]->draw(deck);
			DisplayDeck(deck);
			alex.displayHand();
			cout << flush;
			timmy.displayHand();
			cout << flush;
			isaac.displayHand();
			cout << flush;
			ben.displayHand();
			cout << flush;
	
			this_thread::sleep_for(chrono::milliseconds(sleepLength));
			if (sleepLength > 80) {
				sleepLength = sleepLength - 10;
			}
		}
		loopCount++;
	}
	cout << endl;
	PrintBreak();
	
	cout << " Now lets deal out a deck many, many times. This will show if it actually matters over the long run.\n";

	runs = 0;
	double runsD = 0;
	vector<int> runsV = {10, 10000, 1000000};

	for (int i = 0; i < runsV.size(); i ++) {
		runs = runsV.at(i);
		
		cout << "\n\n  Now lets deal out a deck " << runs << " times,\n  This is how many wilds on average a player would get in each situation:\n\n";
		if (runs > 10000) {
			cout << "  (This may take a while.)\n\n";
		}
		
		// LOGIC FOR 1 SHARED DECK
		
		for (int i = 0; i < runs; i++) {
			while (deck.size() > 0) {
				alex.draw(deck);
				timmy.draw(deck);
				isaac.draw(deck);
				ben.draw(deck);
			}
			alexTotalWildCount = alexTotalWildCount + alex.returnWildCount();
			
			alex.discard();
			timmy.discard();
			isaac.discard();
			ben.discard();
			
			deck = shuffleToPlayingDeck(organizedDeck); 
		}
		
		double alexAverageWildCount = (alexTotalWildCount / (runsD+ runs));
		
		cout << "----------------------\n";
		cout << "| - One Shared Deck - |\n|     Total | Average |\n";
		cout << "|     " << alexTotalWildCount << " - " << alexAverageWildCount << endl; 
		cout << "----------------------\n";
		
		// LOGIC FOR 2 SHARED DECKS
		
		alexTotalWildCount = 0;
		vector<string> deck2 = {};
		
		for (int i = 0; i < runs; i++) {
			
			int halfDeckSize = deck.size() / 2;
			
			for (int i = 0; i < halfDeckSize; i++) {
				deck2.push_back(deck.at((deck.size() - 1)));
				deck.pop_back();
			}
			while (deck.size() > 0) {
				alex.draw(deck2);
				timmy.draw(deck2);
				isaac.draw(deck);
				ben.draw(deck);
			}
			
			//cout << "Hand Size: " << alex.hand.size() << endl;
			//alex.displayWildCount();
			//cout << "----------\n";
			
			alexTotalWildCount = alexTotalWildCount + alex.returnWildCount();
			
			alex.discard();
			timmy.discard();
			isaac.discard();
			ben.discard();
			
			deck = shuffleToPlayingDeck(organizedDeck); 
		}
		
		alexAverageWildCount = (alexTotalWildCount / (runsD+ runs));
		
		
		cout << "| - Two Split Decks - |\n|    Total | Average  |\n";
		cout << "|     " << alexTotalWildCount << " -  " << alexAverageWildCount << endl; 
		cout << "----------------------\n\n";
		cout << "\nHit Enter to continue.\n"; 
		cin.get();
	}
	cout << "As you can see, the difference in the overall wild count is negligible.\n\n";
	
	return 0; 
}
