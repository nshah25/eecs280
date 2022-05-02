#include "Card.h"
#include "Pack.h"
#include <array>
#include <string>
#include <cassert>
#include <vector>
using namespace std;


Pack::Pack() 
{
	next = 0;
	for (int currSuit = 0; currSuit < NUM_SUITS; currSuit++) 
	{
		for (int currRank = 7; currRank < NUM_RANKS; currRank++)
		{
			cards[currSuit * 6 + currRank - 7]
				= Card(RANK_NAMES_BY_WEIGHT[currRank], SUIT_NAMES_BY_WEIGHT[currSuit]);
		}
	}
	reset();
}

Pack::Pack(istream& pack_input) 
{
	this->next = 0;
	string rank;
	string of;
	string suit;

	for (int i = 0; i < PACK_SIZE; i++)
	{
		pack_input >> rank >> of >> suit;
		Card a(rank, suit);

		cards[i] = a;
	}
}

Card Pack::deal_one() 
{
	//assert(this->next < PACK_SIZE);

	this->next = this->next + 1;
	return cards[(this->next) - 1];
}

void Pack::reset() 
{
	this->next = 0;
}

void Pack::shuffle()
{
	array<Card, PACK_SIZE> card = this->cards;

	for (int time = 0; time < 7; time++)
	{
		for (int first_card = 0; first_card < 12; first_card++)
		{
			card[first_card * 2 + 1] = this->cards[first_card];
		}
		for (int last_card = 12; last_card < 24; last_card++)
		{
			card[(last_card - 12) * 2] = this->cards[last_card];
		}
		this->cards = card;
	}
	reset();
}

bool Pack::empty() const 
{
	if (this->next >= PACK_SIZE) 
	{
		return true;
	}
    else
    {
	return false;
    }
}
