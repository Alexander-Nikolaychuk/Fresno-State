#include <stdio.h>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <limits> // To make sure user input is valid

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

void displayDeck(std::vector<std::string> deck) {
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
	PrintBreak();
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
	cout << "\n-----------------------------------\n\n";
}

int main() {   
	
	srand(time(0)); //Make the numbers actually random 
	
	
	cout << "\n\nIf you split up a deck, does that change the probabilty of getting the cards you want?\n";
	cout << "Let's find out. First, let's get a brand new UNO deck.\n\n";
	
	PrintBreak();
	
	cout << "- Creating New Deck . . . \n";
	
	vector<string> organizedDeck = populateDeckUNO(); 
	displayDeck(organizedDeck);
	
	cout << "Hit Enter to continue.\n"; 
	cin.get();
	
	cout << "- Now Shuffling the deck . . . \n";
	vector<string> deck = shuffleToPlayingDeck(organizedDeck);
	displayDeck(deck);
	
	cout << "Hit Enter to continue.\n"; 
	cin.get();

	Person alex("Alex"), timmy("Timmy"), isaac("Isaac"), ben("Ben");
	
	
	int alexTotalWildCount = 0;
	
	cout << "- Showing an example of dealing out the entire deck . . . \n";
	
	while (deck.size() > 0) {
		alex.draw(deck);
		timmy.draw(deck);
		isaac.draw(deck);
		ben.draw(deck);
	}
	
	alex.displayHand();
	timmy.displayHand();
	ben.displayHand();
	isaac.displayHand();
	
	deck = shuffleToPlayingDeck(organizedDeck); 
	
	cout << "\nHere is how many Wilds they had:\n\n";

	alex.displayWildCount();
	timmy.displayWildCount();
	ben.displayWildCount();
	isaac.displayWildCount();
	alex.discard();
	timmy.discard();
	ben.discard();
	isaac.discard();
	
	cout << "\nHit Enter to continue.\n"; 
	cin.get();
	
	PrintBreak();
	
	
	cout << " Now lets deal out a deck many, many times. This will show if it actually matters over the long run.\n";
	cout << " How many decks should we deal out? (Note: My code will discard and reshuffle for every deck.)\n\n";
	cout << " Enter '1' for 1,000; '2' for 10,000; '3' for 100,000; '4' for your own custom number.\n";
	int option;
	int runs = 0;
	double runsD = 0;
	
	while (runs == 0) {  // Keep looping untill valid number
		while (!(cin >> option)) {  // To check if we got a number
			cout << " Please enter a number: ";
			cin.clear(); 
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
		switch (option) {
			case 1:
			runs = 1000;
			break;
			case 2:
			runs = 10000;
			break;
			case 3:
			runs = 100000;
			break;
			case 4:
			cout << " Please enter how many decks should we deal out:\n";
			while (!(cin >> runs)) {
				cout << " Please enter a number: ";
				cin.clear(); 
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}
			break;
			default:
			cout << " Please select a valid option:\n";
		}
	}
	cout << "\n\n  Now lets deal out a deck " << runs << " times,\n  This is how many wilds on average a player would get in each situation:\n\n";
	
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
	cout << "As you can see, the difference in the overall wild count is negligible.\n\n";
	

	
	return 0; 
}
