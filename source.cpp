#include "cards.h"
using namespace std;
double wallet = 1000;

bool hitme(Hand &player, Deck &deck);
void play(Hand &hand, Hand &house, Deck &deck, double &bid, vector<Hand> &allHands);
bool houseTurn(Hand &dealer, Deck &deck);

int main() {
	
	bool menu = true;
	
	

	while (menu) {
		Hand player, house;
		Deck deck;
		char k;
		double bid = 0;
		vector<Hand> allHands;
	
		cout << "Welcome to Blackjack 1.0!" << endl
			<< "By Josiah Manning" << endl << endl
			<< "Enter a bid number (up to " << wallet << ") and return to begin a new game, or 0 to quit: ";
		cin >> bid;

		if (!bid)
			return 0;
		wallet -= bid;
		player.addToPot(bid * 2);
		cout << "Shuffling the deck..." << endl;
		deck.shuff();
		cout << "The house deals you 2 cards." << endl;
		player.draw(deck);
		player.draw(deck);
		player.printHand();
		cout << "Hand value: " << player.returnHandValue() << endl << endl
			<< "The house draws 2 cards." << endl;
		house.draw(deck);
		house.draw(deck);
		if (house.returnHandValue() == 21 && house.returnHand().size() == 2) {
			cout << "House got blackjack. Surrender for half your bet back? (y/n): ";
			cin >> k;
			switch (k) {
				case 'y':
				case 'Y':
					wallet += bid / 2;
					cout << "You recieve $" << bid / 2 << endl << endl;
					continue;
				case 'n':
				case 'N':
					break;
			}
		}
		else
			cout << "House: " << house.returnHand()[1].printCard() << " and 1 facedown card." << endl << endl;


		play(player, house, deck, bid, allHands);
		bool housebust = houseTurn(house, deck);

		cout << endl << endl << "Dealer Hand:" << endl;
		house.printHand();
		cout << endl << "House hand value: " << house.returnHandValue();
		cout << endl << endl;
		for (int j = 0; j < allHands.size(); j++) {
			if (allHands[j].busted())
				continue;
			else if (allHands[j].returnHandValue() > house.returnHandValue() || housebust) {
				if (allHands[j].returnHand().size() == 2 && allHands[j].returnHandValue() == 21 && j == 0)
					allHands[j].addToPot(bid);
				wallet += allHands[j].returnPot();
			cout << "You won $" << allHands[j].returnPot() << "!" << endl;
			}
			else if (allHands[j].returnHandValue() == house.returnHandValue() && !house.busted() && !player.busted()){
				wallet += allHands[j].returnPot() / 2;
				cout << "You tied with the dealer and receive $" << allHands[j].returnPot()/2 << "!" << endl;
			}
		}
		allHands.erase(allHands.begin(), allHands.end());
	}
}

void play(Hand &hand, Hand &house, Deck &deck, double &bid,  vector<Hand> &allHands) {
	if (hand.returnHand().size() < 2)
		hitme(hand, deck);
	char p;
	bool split = false, blackjack = false, dbd = false;
	hand.printHand();
	

	bool pick = true;
	while (pick) {
		cout << endl << "Hand value: " << hand.returnHandValue();
		cout << endl << "(h): Hit me!" << endl;
		if (hand.returnHandValue() >= 9 && hand.returnHandValue() <= 11) {
			cout << "(d): Double down!" << endl;
			dbd = true;
		}
		if (hand.returnHand()[0].returnName() == hand.returnHand()[1].returnName() && hand.returnHand().size() == 2) {
			split = true;
			cout << "(x): Split!" << endl;
		}
		cout << "(s): Stand!" << endl
			<< "Enter an option: ";
		cin >> p;
		bool nobust = true;
		switch (p) {
			case 'h':
			case 'H':
				nobust = hitme(hand, deck);
				hand.returnHandValue(); //determines ace value if drawn;
				cout << "You drew the " << hand.returnHand()[hand.returnHand().size() - 1].printCard()
					<< "with a card value of " << hand.returnHand()[hand.returnHand().size() - 1].returnValue() << endl;
				hand.printHand();
				cout << "Hand value: " << hand.returnHandValue() << endl << endl;
				if (!nobust) {
					cout << "You busted with a hand value of " << hand.returnHandValue() << endl;
					hand.bustHand();
					pick = false;
					break;
				}
				break;

			case 'd':
			case 'D':
				if (dbd) {
					hand.addToPot(bid * 2);
					wallet -= bid;
					cout << "you doubled your bid, drew the " << hand.returnHand()[hand.returnHand().size() - 1].printCard()
						<< " with a card value of " << hand.returnHand()[hand.returnHand().size() - 1].returnValue() << " and ";
					;
					if (hitme(hand, deck))
						cout << "got";
					else {
						cout << "busted with";
						hand.bustHand();
					}
					cout << " a hand value of: " << hand.returnHandValue() << endl;
					hand.printHand();
					pick = false;
					break;
				}
				break;
			case 'x':
			case 'X':
				split = true;
				if (split) {
					cout << "Splitting deck into two decks. Paying $" << bid << endl;
					Hand splitoff;
					Card popcard = hand.returnHand()[1];
					cout << "card popped: " << hand.returnHand()[1].printCard() << " = " << popcard.printCard() << endl;
					splitoff.addCard(popcard);
					hand.discard();
					wallet -= bid;
					splitoff.addToPot(bid * 2);
					cout << "split pot: " << splitoff.returnPot();
					splitoff.printHand();
					hitme(splitoff, deck);
					hitme(hand, deck);
					cout << endl << "Splitoff hand:" << endl;
					play(hand, house, deck, bid, allHands);
					play(splitoff, house, deck, bid, allHands);
					
					pick = false;
					break;
				}
				break;

			case 's':
			case 'S':
				cout << "You stood on your hand with a value of: " << hand.returnHandValue() << endl;
				pick = false;
				break;
		}
	}
	allHands.push_back(hand);
}

bool hitme(Hand &player, Deck &deck) {
	return(player.draw(deck));
}

bool houseTurn(Hand &dealer, Deck &deck) {
	while(dealer.returnHandValue() < 17){
		hitme(dealer, deck);
	}
	if (dealer.returnHandValue() > 21) {
		cout << "Dealer busted." << endl;
		return 1;
	}
	return 0;
}



