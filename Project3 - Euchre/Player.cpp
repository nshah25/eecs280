#include <cassert>
#include <iostream>
#include <string>
#include <algorithm>
#include "Player.h"

using namespace std;

class Simple : public Player
{
public:
	Simple(const string name_in) : name(name_in) {}

	virtual const string& get_name() const
	{
		return name;
	}

	virtual void add_card(const Card& c)
	{
		assert(playerHand.size() <= MAX_HAND_SIZE);

		if (playerHand.size() < MAX_HAND_SIZE)
		{
			playerHand.push_back(c);
		}
	}

	virtual bool make_trump(const Card& upcard, bool is_dealer,
		int round, string& order_up_suit) const
	{
		assert(round == 1 || round == 2);

		int numTrumpFaceCards = 0;
		if (round == 1)
		{
			for (int i = 0; i < MAX_HAND_SIZE; i++)
			{
				if ((playerHand[i].is_trump(upcard.get_suit()) == true) &&
					(playerHand[i].is_face() == true))
				{
					numTrumpFaceCards++;
				}
			}
			if (numTrumpFaceCards <= 1)
			{
				return false;
			}
			else
			{
				order_up_suit = upcard.get_suit();
				return true;
			}
		}
		else
		{
			if (is_dealer == false)
			{
				int numFaceSuits = 0;
				string getUpcardSuit = Suit_next(upcard.get_suit());
				for (int i = 0; i < MAX_HAND_SIZE; i++)
				{
					if (playerHand[i].is_trump(getUpcardSuit) == true &&
						(playerHand[i].is_face() == true))
					{
						numFaceSuits++;
					}
				}
				if (numFaceSuits > 0)
				{
					order_up_suit = Suit_next(upcard.get_suit());
					return true;
				}
				else
				{
					return false;
				}
			}
			else
			{
				order_up_suit = upcard.get_suit();
				return true;
			}
		}
	}

	virtual void add_and_discard(const Card& upcard)
	{
		assert(int(playerHand.size()) >= 1);

		playerHand.push_back(upcard);

		int index = 0;
		for (int i = 0; i < int(playerHand.size()); i++)
		{
			if (Card_less(playerHand[i], playerHand[index], upcard.get_suit()))
			{
				index = i;
			}
		}

		playerHand.erase(playerHand.begin() + index);
	}

	Card lead_card(const string& trump)
	{
		int num_trump_cards = 0;

		sort(playerHand.begin(), playerHand.end());

		for (int i = 0; i < int(playerHand.size()); i++)
		{
			if (playerHand[i].is_trump(trump) == true)
			{
				num_trump_cards++;
			}
		}

		if (num_trump_cards == int(playerHand.size()))
		{
			int highestTrumpCard = 0;
			Card lowestGuess = { Card::RANK_TWO, Card::SUIT_SPADES };
			if (trump == Card::SUIT_SPADES)
			{
				lowestGuess = { Card::RANK_TWO, Card::SUIT_HEARTS };
			}
			for (int i = 0; i < int(playerHand.size()); i++)
			{
				if (Card_less(lowestGuess, playerHand[i], trump) == true)
				{
					lowestGuess = playerHand[i];
					highestTrumpCard = i;
				}
			}
			Card wanted = playerHand[highestTrumpCard];
			playerHand.erase(playerHand.begin() + highestTrumpCard);
			return wanted;
		}

		if (num_trump_cards != int(playerHand.size()))
		{
			Card lowest = { Card::RANK_TWO, Card::SUIT_SPADES };
			if (trump == Card::SUIT_SPADES)
			{
				lowest = { Card::RANK_TWO, Card::SUIT_HEARTS };
			}

			int highestNonTrump = 0;
			for (int i = 0; i < int(playerHand.size()); i++)
			{
				if (Card_less(lowest, playerHand[i], trump) == true)
				{
					if (playerHand[i].get_suit(trump) != trump)
					{
						highestNonTrump = i;
					}
				}
			}
			Card toBePlayed = playerHand[highestNonTrump];
			playerHand.erase(playerHand.begin() + highestNonTrump);
			return toBePlayed;
		}
		Card c1;
		return c1;
	}

	virtual Card play_card(const Card& led_card, const string& trump)
	{
		assert(int(playerHand.size()) >= 1);
		assert(trump == Card::SUIT_CLUBS || trump == Card::SUIT_DIAMONDS
			|| trump == Card::SUIT_HEARTS || trump == Card::SUIT_SPADES);

		sort(playerHand.begin(), playerHand.end());

		int numCardsFollowingSuit = 0;
		for (int i = 0; i < int(playerHand.size()); i++)
		{
			if (led_card.get_suit(trump) == playerHand[i].get_suit(trump))
			{
				numCardsFollowingSuit++;
			}
		}

		if (numCardsFollowingSuit > 0)
		{
			int highestCardFollowingSuit = 0;
			Card lowestGuess = { Card::RANK_TWO, Card::SUIT_SPADES };
			if (trump == Card::SUIT_SPADES)
			{
				lowestGuess = { Card::RANK_TWO, Card::SUIT_HEARTS };
			}

			for (int i = 0; i < int(playerHand.size()); i++)
			{
				if (playerHand[i].get_suit(trump) == led_card.get_suit(trump) &&
					Card_less(lowestGuess, playerHand[i], trump) == true)
				{
					lowestGuess = playerHand[i];
					highestCardFollowingSuit = i;
				}
			}
			Card toBePlayed = playerHand[highestCardFollowingSuit];
			playerHand.erase(playerHand.begin() + highestCardFollowingSuit);
			return toBePlayed;
		}
		else
		{
			int index = 0;
			for(int  i = 0; i < int(playerHand.size()); i++)
			{
				if (Card_less(playerHand[i], playerHand[index], trump))
				{
					index = i;
				}
			}
			Card copy = playerHand[index];
			playerHand.erase(playerHand.begin() + index);
			return copy;
		}
	}
private:
	string name;
	vector <Card> playerHand;
};


class Human : public Player
{
public:
	Human(const string name_in) : name(name_in) {}

	virtual const string& get_name() const
	{
		return name;
	}
	virtual void add_card(const Card& c)
	{
		if (playerHand.size() < MAX_HAND_SIZE)
		{
			playerHand.push_back(c);
		}
	}
	virtual bool make_trump(const Card& upcard, bool is_dealer,
		int round, string& order_up_suit) const
	{
		string userCard;
		vector <Card> copy;

		copy = playerHand;

		sort(copy.begin(), copy.end());

		for (int i = 0; i < int(copy.size()); i++)
		{
			cout << "Human player " << get_name() << "'s hand:" << "[" << i << "] "
				<< copy[i] << endl;
		}

		if (round == 1)
		{
			cout << "Human player " << get_name() << " please enter a suit, or \"pass\":"
				<< endl;
			cin >> userCard;

			if (userCard == "Pass" || userCard == "pass")
			{
				return false; 
			}
			else
			{
				order_up_suit = userCard;
				return true;
			}
		}

		else if (round >= 2)
		{
			cout << "Human player " << get_name() << "please enter a suit, or \"pass\":"
				<< endl;
			cin >> userCard;

			if (userCard == "Pass" || userCard == "pass")
			{
				return false;
			}

			if (userCard == Card::SUIT_CLUBS || userCard == Card::SUIT_SPADES ||
				userCard == Card::SUIT_HEARTS || userCard == Card::SUIT_DIAMONDS)
			{
				order_up_suit = userCard;
				return true;
			}
		}
		return false;
	}
	virtual void add_and_discard(const Card& upcard)
	{
		int userDiscard = 0;
		int index = {};

		assert(playerHand.size() >= 1);
		sort(playerHand.begin(), playerHand.end());
		cout << "Discard upcard: [-1]" << endl;

		cout << "Human player: " << get_name() << ", please select a card to discard:"
			<< endl;
		cin >> userDiscard;

		for (int i = 0; i < int(playerHand.size()); ++i)
		{
			if (playerHand[i] == playerHand[userDiscard]) {
				index = i;
			}
		}

		if (userDiscard != -1) {
			playerHand[index] = upcard;
		}
	}

	virtual Card lead_card(const string& trump)
	{
		assert(int(playerHand.size()) >= 1);

		sort(playerHand.begin(), playerHand.end());
		int card = 0;
		int cardIndex = 0;
		vector <Card> copy;
		for (int i = 0; i < int(playerHand.size()); i++)
		{
			cout << playerHand[i] << " ";
			copy.push_back(playerHand[i]);
		}

		cout << "Human player " << get_name() << ", please select a card:" << endl;
		cin >> card;

		for (int i= 0; i < int(playerHand.size()); i++)
		{
			cout << "Human player " << get_name() << "'s hand:" << "[" << i << "] "
				<< copy[i] << endl;

			if (playerHand[i] == copy[card])
			{
				cardIndex = i;
			}
		}

		cout << playerHand[cardIndex] << " led by " << get_name() << endl;
		Card temp = playerHand[cardIndex];
		playerHand.erase(playerHand.begin() + cardIndex);
		return temp;
	}

	virtual Card play_card(const Card& led_card, const string& trump)
	{
		assert(int(playerHand.size()) >= 1);

		sort(playerHand.begin(), playerHand.end());
		int card;
		int cardIndex = 0;
		vector <Card> tempCopy;
		for (int i = 0; i < int(playerHand.size()); i++)
		{
			tempCopy.push_back(playerHand[i]);
			cout << "Human player " << get_name() << "'s hand:" << "[" << i << "] "
				<< tempCopy[i] << endl;
		}

		cout << "Human player " << get_name() << " , please select a card:" << endl;
		cin >> card;

		for (int j = 0; j < int(playerHand.size()); j++)
		{
			if (playerHand[j] == tempCopy[card])
			{
				cardIndex = j;
			}
		}
		Card temp = playerHand[cardIndex];
		playerHand.erase(playerHand.begin() + cardIndex);
		return temp;

	}
private:
	string name;
	vector <Card> playerHand;
};

Player* Player_factory(const string& name, const string& strategy)
{
	if (strategy == "Simple")
	{
		return new Simple(name);
	}
	else if (strategy == "Human")
	{
		return new Human(name);
	}
	else
	{
		assert(false);
		return nullptr;
	}
}

ostream& operator<<(ostream& os, const Player& p)
{
	os << p.get_name();

	return os;
}
