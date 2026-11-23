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
	int wildCount();
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
	cout << name << "'s wild count is: " << wildCount() << "\n";
}

int Person::wildCount() {
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
		shuffledDeck.push_back(orderedDeck.at(cardNum));  // Take a random card from ordered, put in shuffled
		orderedDeck.erase(orderedDeck.begin() + cardNum); // Remove that random card from ordered 
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
		cout << flush;
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
	
	for (int i = 0; i < 3; i++) { //Push special uno cards
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
	
	for (int i = 0; i < 4; i++) {
		organizedDeck.push_back("Wild");
	}
	for (int i = 0; i < 4; i++) {
		organizedDeck.push_back("Wild Draw Four");
	}
	
	return organizedDeck;
}

vector<string> populateDeckPoker() {
	vector<string> organizedDeck;
	
	for (int i = 0; i < 4; i++) { //Push Non-face poker cards
		for (int j = 1; j < 11; j++) {
			switch (i) {
				case 0:
				organizedDeck.push_back(to_string(j) + " Spade");
				break;
				case 1:
				organizedDeck.push_back(to_string(j) + " Heart");
				break;
				case 2:
				organizedDeck.push_back(to_string(j) + " Clover");
				break;
				case 3:
				organizedDeck.push_back(to_string(j) + " Diamond");
				break;
			}
		}
	}
	
	vector<string> actionCards = {"Jack", "Queen", "King", "Ace"};
	
	for (int i = 0; i < 3; i++) { //Push face cards
		for (int j = 0; j < 4; j++) {
			switch (j) {
				case 0:
				organizedDeck.push_back(actionCards.at(i) + " of Spades");
				break;
				case 1:
				organizedDeck.push_back(actionCards.at(i) + " of Hearts");
				break;
				case 2:
				organizedDeck.push_back(actionCards.at(i) + " of Clover");
				break;
				case 3:
				organizedDeck.push_back(actionCards.at(i) + " of Diamond");
				break;
			}
		}
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

int main(int argc, char* argv[]) {
	srand(time(0)); //Make the numbers actually random 
	
	// Argument Parser
	
	bool skipCoinFlag = false;
	bool debugCardsFlag = false;
	bool pokerDeckFlag = false;
	
	for (int i = 1; i < argc; i++) {
		string arg = argv[i];
		if (arg == "-h" || arg == "--help") {
			cout << "\n Current flags are --skipCoin (-c) to skip the coin demo,\n"
			" and --debugCards (-d) to skip the card animation." << endl;
			return 0;
		}
	}
	for (int i = 1; i < argc; i++) {
		string arg = argv[i];
		if (arg == "-c" || arg == "--skipCoin") { skipCoinFlag = true; }
	}
	for (int i = 1; i < argc; i++) {
		string arg = argv[i];
		if (arg == "-c" || arg == "--debugCards") { debugCardsFlag = true; }
	}
	for (int i = 1; i < argc; i++) {
		string arg = argv[i];
		if (arg == "-p" || arg == "--Poker") { pokerDeckFlag = true; }
	}
	
	// Program Start
	
	cout << "\n Welcome to my program about probability.\n\n";
	int runs = 10;
		
	if (skipCoinFlag==false) {
		
		cout << " To start, let us experiment with a coin. We know that flipping a coin\n"
		" will be heads 50% of the time, and tails 50% of the time.\n"
		" So, if we simulate flipping a coin many times, will we end up\n with an even split between heads and tails?\n"
		" Lets start by fliping a coin 10 times and see what happens.\n\n";
		PrintBreak();
		
		float headsOdds1 = 0.0;
		float tailsOdds1 = 0.0;
		float headsOdds2 = 0.0;
		float tailsOdds2 = 0.0;
		float headsOdds3 = 0.0;
		float tailsOdds3 = 0.0;

		bool fiftyFiftyFlag = false;
		
		do {
			fiftyFiftyFlag = DisplayFullCoinFlip(runs, headsOdds1, tailsOdds1);
			if (fiftyFiftyFlag == false) {
				cout << " As we see, with these 10 flips we did not get heads for 50% of the flips,\n"
				" nor tails. What will happen when we do more flips?\n\n";
				cout << " Lets flip it 1,000 times.\n\n";
				PrintBreak();
			}
			else {
				cout << " As you can see, we got heads 50% of the flips,\n"
				" and tails is 50% of the flips.\n"
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
		" the amount of heads and tails we get start to become closer to the probability\n"
		" we expect.\n\n"
		" This means if we do something random many, many times, and take its average\n"
		" accross all of the times we did that thing, we will be able to see\n"
		" approximately the chances of all the outcomes of that action.\n\n";
		PrintBreak();
	}
	if (skipCoinFlag==true) {
		PrintBreak();
		cout << " Skipping coin demonstration . . ." << endl;
		cout << "\n-----------------------------------";
	}
	
	// START OF CARD SECTION
	// Features to add: Loading bar, and check if distrubtion changes. Average does not change, Does chance of getting 0 or all 8 wilds change? 
	
	cout << "\n\n So what about the chances for something we do not know:\n"
	" If you split up a deck, does that change the\n"
	" probabilty of what cards you get?\n"
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

	//DISPLAY LOGIC ANIMATION FOR 1 DECK
	
	int sleepLength  = 3000;
	if (debugCardsFlag==true) { sleepLength  = 0; }
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
		
		if (loopCount == 1) { sleepLength  = 500;}		
		if (debugCardsFlag==true) { sleepLength  = 0; }
		
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
	
	cout << "\nHere is how many Wilds they had:\n\n";

	alex.displayWildCount();
	timmy.displayWildCount();
	ben.displayWildCount();
	isaac.displayWildCount();
	alex.discard();
	timmy.discard();
	ben.discard();
	isaac.discard();
	cout << endl;	
	PrintBreak();
	
	
	//DISPLAY LOGIC ANIMATION FOR 2 DECKS
	
	cout << " Now let us see the same thing, but with 2 decks,\n"
	" two people drawing from one deck, two people drawing from another.\n\n"
	"- Showing an example of dealing out the two decks . . . \n\n";
	
	deck = shuffleToPlayingDeck(organizedDeck); 
	vector<string> deck2 = {};
	int halfDeckSize = deck.size() / 2;
	
	for (int i = 0; i < halfDeckSize; i++) {
		deck2.push_back(deck.at((deck.size() - 1)));
		deck.pop_back();
	}	
	
	sleepLength  = 5000;
	if (debugCardsFlag==true) { sleepLength  = 0; }
	loopCount = 0;
	while (!deck.empty()) {
		if (loopCount == 0) { 
			cout << "\033[H"; //Move cursor to top left
			cout << "\033[2J"; // Clear screen
			DisplayDeck(deck);
			DisplayDeck(deck2);
			alex.displayHand();
			timmy.displayHand();
			isaac.displayHand();
			ben.displayHand();
			this_thread::sleep_for(chrono::milliseconds(sleepLength));
		} 
		
		if (loopCount == 2) { sleepLength  = 500; } 
		if (debugCardsFlag==true) { sleepLength  = 0; }
		
		for (int j = 0; j < 2; j++) {
			cout << "\033[H";
			cout << "\033[2J";
			people[j]->draw(deck);
			cout << flush;
			DisplayDeck(deck);
			DisplayDeck(deck2);
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
		for (int j = 2; j < 4; j++) {
			cout << "\033[H";
			cout << "\033[2J";
			people[j]->draw(deck2);
			DisplayDeck(deck);
			DisplayDeck(deck2);
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
	
	cout << "\nHere is how many Wilds they had:\n\n";

	alex.displayWildCount();
	timmy.displayWildCount();
	ben.displayWildCount();
	isaac.displayWildCount();
	alex.discard();
	timmy.discard();
	ben.discard();
	isaac.discard();
	cout << endl;	
	PrintBreak();
	
	// START OF SIMULATION
	
	runs = 0;
	int alex5Wild1Deck = 0;
	int alex5Wild2Deck = 0;
	int alex0Wild1Deck = 0;
	int alex0Wild2Deck = 0;
	double runsD = 0;
	vector<int> runsV = {10, 1000, 100000};
	vector<int> alexTotalWildCount1DeckV = {};
	vector<float> alexAverageWildCount1DeckV = {};
	vector<int> alexTotalWildCount2DeckV = {};
	vector<float> alexAverageWildCount2DeckV = {};
	deck = shuffleToPlayingDeck(organizedDeck); 
	
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
			if (alex.wildCount() > 5) { alex5Wild1Deck++; }
			else if (alex.wildCount() == 0) { alex0Wild1Deck++; }
			alexTotalWildCount = alexTotalWildCount + alex.wildCount();
			
			alex.discard();
			timmy.discard();
			isaac.discard();
			ben.discard();
			
			deck = shuffleToPlayingDeck(organizedDeck); 
		}
		alexTotalWildCount1DeckV.push_back(alexTotalWildCount);
		double alexAverageWildCount = (alexTotalWildCount / (runsD+ runs));
		alexAverageWildCount1DeckV.push_back(alexAverageWildCount);
		
		cout << "\n -------Results--------\n"
		" | - One Shared Deck -"
		"\n |\n |  Alex's Wild Count: " << alexTotalWildCount << 
		"\n |  Alex's Average Wilds Per Game: " << alexAverageWildCount;
		
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
			
			if (alex.wildCount() > 5) { alex5Wild2Deck++; }	
			else if (alex.wildCount() == 0) { alex0Wild2Deck++; }			
			alexTotalWildCount = alexTotalWildCount + alex.wildCount();
			
			alex.discard();
			timmy.discard();
			isaac.discard();
			ben.discard();
			
			deck = shuffleToPlayingDeck(organizedDeck); 
		}
		alexTotalWildCount2DeckV.push_back(alexTotalWildCount);
		alexAverageWildCount = (alexTotalWildCount / (runsD+ runs));
		alexAverageWildCount2DeckV.push_back(alexAverageWildCount);
		
		cout << "\n |\n | - Two Split Decks -"
		"\n |\n |  Alex's Wild Count: " << alexTotalWildCount << 
		"\n |  Alex's Average Wilds Per Game: " << alexAverageWildCount;
		cout << "\n |\n ----------------------\n\n";
		PrintBreak();
	}
	
	int round = 0;
	while(round != alexTotalWildCount1DeckV.size()) {
		cout << " " << runsV.at(round) << " Rounds: \n\n"
		" One Deck: ";
		//" Alex's Total Wild Count: " << alexTotalWildCount1DeckV.at(round) << endl;
		cout << " Alex's Average Wild Count: " << alexAverageWildCount1DeckV.at(round) << "\n" << endl;
		cout << " Two Decks: ";
		//" Alex's Total Wild Count: " << alexTotalWildCount2DeckV.at(round) << endl;
		cout << " Alex's Average Wild Count: " << alexAverageWildCount2DeckV.at(round) << "\n\n" << endl;
		round++;
	}
	PrintBreak();
	
	cout << " So hopfully we can agree that the average amout of a certain card\n"
	" you get does not change if you split the deck or not. However, while the\n"
	" average may not change, what about the chances to get a lot of wilds? or 0?\n"
	"\n\n Good thing my program already calcuated that!\n\n";
	
	PrintBreak();
	
	cout << " Here is how many times Alex got 5 wilds when there was 1 deck: " << alex5Wild1Deck;
	cout << "\n Here is how many times Alex got 5 wilds when there was 2 decks: " << alex5Wild2Deck;
	cout << "\n\n Here is how many times Alex got 0 wilds when there was 1 deck: " << alex0Wild1Deck;
	cout << "\n Here is how many times Alex got 0 wilds when there was 2 decks: " << alex0Wild2Deck << endl;
	
	/*
	cout << endl;
	PrintBreak();
	organizedDeck = populateDeckPoker(); 
	DisplayDeck(organizedDeck);
	PrintBreak();
	
	cout << " - Now Shuffling the deck . . . \n";
	deck = shuffleToPlayingDeck(organizedDeck);
	DisplayDeck(deck);
	PrintBreak();
	*/
	
	
	cout << "\n\n\n\n ~~~ End of Program ~~~\n\n Thank you for your time\n";
	
	return 0; 
}
