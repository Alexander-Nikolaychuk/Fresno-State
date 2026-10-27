#include <stdio.h>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <unistd.h> //For sleep

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
	cout << "  " << name << "'s Hand:\n\n ";
	for (int i = 0; i < hand.size(); i++) {
		if (i==(hand.size()-1)) {
			cout << hand.at(i);
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
	int wildCount = 0;
	for (int i = 0; i < hand.size(); i++) {
		if (hand.at(i) == "Wild") {	wildCount++;}		
	}
	cout << name << "'s wild count is: " << wildCount << endl;
}

int Person::returnWildCount() {
	int wildCount = 0;
	for (int i = 0; i < hand.size(); i++) {
		if (hand.at(i) == "Wild") {	wildCount++;}		
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

vector<string> populateDeck() {
	vector<string> organizedDeck;
	
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
	
	for (int i = 0; i < 4; i++) {
		organizedDeck.push_back("Wild");
	}
	
	return organizedDeck;
}

void PrintBreak() {
	cout << "\n-----------------------------------\n\n";
}

int main() {   
	
	srand(time(0)); //Make the numbers actually random 
	
	
	cout << "\n\nIf you split up a deck, does that change the probabilty of getting the cards you want?\n";
	cout << "Let's find out.\n";
	
	PrintBreak();
	
	cout << "- Generating New Deck . . . \n";
	
	//usleep(1000000);
	
	vector<string> organizedDeck = populateDeck(); 
	
	displayDeck(organizedDeck);
	cout << "- Now Randoming . . . \n\n";
	
	//usleep(3000000);
	
	vector<string> deck = shuffleToPlayingDeck(organizedDeck);
	
	displayDeck(deck);

	Person alex("Alex"), timmy("Timmy"), isaac("Isaac"), ben("Ben");
	
	int runs = 1000;
	double runsD = 0;
	
	int alexTotalWildCount = 0;
	
	
	cout << "- Showing an example of dealing out the entire deck . . . \n";
	
	while (deck.size() > 0) {
		alex.draw(deck);
		timmy.draw(deck);
		isaac.draw(deck);
		ben.draw(deck);
	}
	
	cout << "\n";
	alex.displayHand();
	cout << "\n";
	
	cout << "\n";
	timmy.displayHand();
	cout << "\n";
	
	cout << "\n";
	ben.displayHand();
	cout << "\n";
	
	cout << "\n";
	isaac.displayHand();
	cout << "\n";
	
	alex.discard();
	timmy.discard();
	isaac.discard();
	ben.discard();
		
	deck = shuffleToPlayingDeck(organizedDeck); 
	
	PrintBreak();
	
	
	cout << "- Now Simulating dealing a deck " << runs << " times,\n  This is how many wilds a player would get in each situation:\n\n";
	
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
	cout << "| - - Shared Deck - - |\n|     Total | Average |\n";
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
	
	cout << "| - - Split Deck - -  |\n|    Total | Average  |\n";
	cout << "|     " << alexTotalWildCount << " -  " << alexAverageWildCount << endl; 
	cout << "----------------------\n\n";
	cout << "As you can see, the difference in the overall wild count is negligible.\n\n";
	

	
	return 0; 
}
