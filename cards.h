#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <random>
#include <time.h>
using namespace std;

class Card {
	
	string name;
	int suit;
	int value;
public:
	int returnValue();
	void setValue(int val);
	void setName(string newname);
	void setSuit(int cardsuit);
	string returnName();
	string returnSuit();
	string printCard();
	
};

class Deck {
	vector<Card> deck;
public:
	Deck() {
		Card temp;
		for (int i = 0; i < 4; i++) {
			temp.setSuit(i);
			for (int j = 2; j < 11; j++) {
				temp.setName(to_string(j));
				temp.setValue(j);
				deck.push_back(temp);
			}
			temp.setName("jack");
			temp.setValue(10);
			deck.push_back(temp);
			temp.setName("queen");
			temp.setValue(10);
			deck.push_back(temp);
			temp.setName("king");
			temp.setValue(10);
			deck.push_back(temp);
			temp.setName("ace");
			temp.setValue(11);
			deck.push_back(temp);
		}
		shuff();
		
	}

	void shuff();
	vector<Card> returnDeck();
	void poptop();
	void printDeck();
	
};

class Hand {
	vector<Card> hand;
	double pot;
	bool bust;
public:
	vector<Card> returnHand();
	void printHand();
	int returnHandValue();
	bool draw(Deck &deck);
	void discard();
	void bustHand();
	void addToPot(double bid);
	double returnPot();
	bool busted();
	void addCard(Card card);

};
