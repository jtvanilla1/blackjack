#include "cards.h"
using namespace std;

int Card::returnValue() {
	return value;
}

void Card::setValue(int val) {
	value = val;
}

void Card::setName(string newname) {
	name = newname;
}

string Card::returnName() {
	return name;
}

void Card::setSuit(int cardsuit) {
	suit = cardsuit;
}

string Card::returnSuit() {
	string suitname;
	switch (suit) {
		case 1: 
			suitname = "clubs";
			break;
		case 2:
			suitname = "hearts";
			break;
		case 3:
			suitname = "diamonds";
			break;
		default:
			suitname = "spades";
			break;
	}
	return suitname;
}


string Card::printCard() {
	string cardname;
	cardname.append(returnName());
	cardname.append(" of ");
	cardname.append(returnSuit());
	return cardname;
}

vector<Card> Hand::returnHand() {
	return hand;
}

void Hand::printHand()
{
	cout << "Hand:" << endl;
	for (int i = 0; i < hand.size(); i++)
		cout << hand[i].printCard() << endl;
}

int Hand::returnHandValue() {
	int temp = 0;
	for (int i = 0; i < hand.size(); i++) {
		if (hand[i].returnName() == "ace" && temp > 10)
			hand[i].setValue(1);
		temp += hand[i].returnValue();
	}
	return temp;
}

bool Hand::draw(Deck & deck)
{
	Card drawcard = deck.returnDeck()[0];
	hand.push_back(drawcard);
	deck.poptop();

	if (returnHandValue() > 21)
		return 0;
	return 1;
}

void Hand::discard()
{
	hand.pop_back();
}

void Hand::bustHand()
{
	bust = true;
}

void Hand::addToPot(double bid)
{
	pot += bid;
}

double Hand::returnPot()
{
	return pot;
}

bool Hand::busted()
{
	return bust;
}

void Hand::addCard(Card card)
{
	hand.push_back(card);
}

void Deck::shuff() {
	random_device seed;
	mt19937 rng(seed());

	shuffle(deck.begin(), deck.end(), rng);
}

vector<Card> Deck::returnDeck()
{
	return deck;
}

void Deck::poptop()
{
	deck.erase(deck.begin());
}

void Deck::printDeck()
{
	for (int i = 0; i < deck.size(); i++) {
		cout << deck[i].printCard();
	}
}

