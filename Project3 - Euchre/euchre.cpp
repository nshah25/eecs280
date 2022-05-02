#include <string>
#include <cstring>
#include <vector>
#include <cassert>
#include <iostream>
#include <fstream>
#include "Player.h"
#include "Card.h"
#include "Pack.h"
using namespace std;

class Game {
public:
	//constructor
	Game(Pack pack_in, vector <Player*> player_in, bool choice, int goalscore_in)
		:deckOfCards(pack_in), players(player_in), shuffle(choice),
		team1score(0), team2score(0), goalscore(goalscore_in) {}

	//shuffle the cards
	void callShuffle(bool shuffle)
	{
		if (shuffle == true)
		{
			deckOfCards.shuffle();
		}
		else {}
	}

	//deal the card
	void dealCards(int dealerIndex)
	{
		int dealCardOrder[8]  = { 3,2,3,2,2,3,2,3 };
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < dealCardOrder[i]; ++j)
			{
				int deal = (dealerIndex + i + 1) % 4;
				players[deal]->add_card(deckOfCards.deal_one());
			}
		}
		upCard = deckOfCards.deal_one();
		cout << upCard << " turned up" << endl;
	}

	//decide upcard
	Card getUpcard() 
	{
		return upCard;
	}

	//make trump and discard card
	string setTrump(int dealerIndex, int& orderUpIndex, Card& upcard,
		 string& order_up_suit)
	{
		for (int i = 1; i <= int(players.size() * 2); i++) 
		{
			int currRound = (i - 1) / 4 + 1;
			if (players[(i + dealerIndex) % 4]->make_trump
			(upcard,(((i + dealerIndex) % 4) == dealerIndex),currRound, order_up_suit)) 
			{
				cout << players[(i + dealerIndex) % 4]->get_name() << " orders up ";
				cout << order_up_suit << endl;
				if (currRound == 1) 
				{
					players[dealerIndex]->add_and_discard(upcard);
				}
				orderUpIndex = (i + dealerIndex) % 4;
				cout << endl;
				break;
			}
			cout << players[(i + dealerIndex) % 4]->get_name() << " passes" << endl;
		}
		return order_up_suit;
	}

	//trick taking, return who win the trick
	vector<int> determineTrickWinner(string& trump, int dealerIndex)
	{
		vector <int> indexOfWinner;
		int currLeader = (dealerIndex + 1) % 4;

		for (int trick = 0; trick < MAX_NUM_TRICKS; trick++)
		{
			int ledcopy = currLeader;
			Card win = players[currLeader]->lead_card(trump);
			Card led = win;
			cout << win << " led by " << players[currLeader]->get_name() << endl;
			for (int i = 1; i < 4; i++) 
			{
				Card played = players[(currLeader + i) % 4]->play_card(led, trump);
				cout << played << " played by ";
				cout << players[(currLeader + i) % 4]->get_name() << endl;
				if (Card_less(win, played, led, trump)) 
				{
					win = played;
					ledcopy = (currLeader + i) % 4;
				}
			}
			currLeader = ledcopy;
			indexOfWinner.push_back(ledcopy);
			cout << players[ledcopy]->get_name() << " takes the trick";
			cout << endl << endl;
		}
		return indexOfWinner;
	}

	//scoring, change team scores per hand
	void score(int indexOfTrumpWinner, vector<int> indexOfWinner)
	{
		int count1 = 0;
		for (int i = 0; i < int(indexOfWinner.size()); i++) 
		{
			if (indexOfWinner[i] == 0 || indexOfWinner[i] == 2) {
				count1 = count1 + 1;
			}
		}
		int count2 = 5 - count1;
		//team 1 wins
		if (count1 > count2)
		{
			cout << players[0]->get_name() << " and " << players[2]->get_name();
			cout << " win the hand" << endl;
			if (indexOfTrumpWinner == 0 || indexOfTrumpWinner == 2) 
			{
				if (count1 == 5) 
				{
					team1score = team1score + 2;
					cout << "march!" << endl;
				}
				else {
					team1score = team1score + 1;
				}
			}
			else
			{
				team1score = team1score + 2;
				cout << "euchred!" << endl;
			}
		}
		//team 2 wins
		else {
			cout << players[1]->get_name() << " and ";
			cout << players[3]->get_name() << " win the hand" << endl;
			if (indexOfTrumpWinner == 1 || indexOfTrumpWinner == 3) {
				if (count2 == 5) {
					team2score = team2score + 2;
					cout << "march!" << endl;
				}
				else {
					team2score = team2score + 1;
				}
			}
			else {
				team2score = team2score + 2;
				cout << "euchred!" << endl;
			}
		}
	}

	//play game
	void startGame() 
	{
		int hand = 0;
		while (team1score < goalscore && team2score < goalscore) 
		{
			int currDealer = hand % 4;
			cout << "Hand " << hand << endl;
			cout << players[currDealer]->get_name() << " deals" << endl;
			//shuffle
			callShuffle(shuffle);
			//deal
			dealCards(currDealer);
			//decide upcard
			Card Upcard = getUpcard();
			//Make trump
			string trump;
			int indexOfTrump = 0;
			trump = setTrump(currDealer, indexOfTrump, Upcard, trump);
			//play tricks
			vector <int> winner = determineTrickWinner(trump, currDealer);
			//score
			score(indexOfTrump, winner);
			cout << players[0]->get_name() << " and " << players[2]->get_name();
			cout << " have " << team1score << " points" << endl;
			cout << players[1]->get_name() << " and " << players[3]->get_name();
			cout << " have " << team2score << " points" << endl << endl;

			hand++;
		}
		if (team1score > team2score) {
			cout << players[0]->get_name() << " and " << players[2]->get_name();
			cout << " win!" << endl;
		}
		else {
			cout << players[1]->get_name() << " and " << players[3]->get_name();
			cout << " win!" << endl;
		}
	}
	void delete_players()
	{
		for (int i = 0; i < int(players.size()); ++i)
		{
			delete players[i];
		}
	}
private:
	Pack deckOfCards;
	vector <Player*> players;
	Card upCard;
	bool shuffle;
	int team1score;//0 or 2
	int team2score;//1 or 3
	int goalscore;
	const int MAX_NUM_TRICKS = 5;
};

int main(int argc, char* argv[]) 
{
	string message = "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle]\n "
		"POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3\n NAME4 TYPE4";

	if (argc != 12)
	{
		cout << message << endl;
		return 1;
	}
	if (atoi(argv[3]) < 1 || atoi(argv[3]) > 100)
	{
		cout << message << endl;
		return 1;
	}
	if (string(argv[2]) != "shuffle" && string(argv[2]) != "noshuffle")
	{
		cout << message << endl;
		return 1;
	}
	if (string(argv[5]) != "Simple" && string(argv[5]) != "Human" &&
		string(argv[7]) != "Simple" && string(argv[7]) != "Human" &&
		string(argv[9]) != "Simple" && string(argv[9]) != "Human" &&
		string(argv[11]) != "Simple" && string(argv[11]) != "Human")
	{
		cout << message << endl;
		return 1;
	}

	for (int i = 0; i < argc; i++)
	{
		cout << argv[i] << " ";
	}

	ifstream openPack(argv[1]);
	if (!openPack.is_open())
	{
		cout << "Error opening " << argv[1] << endl;

	}
	cout << endl;

	//read in variable
	bool choice = !strcmp(argv[2], "shuffle");
	int targetSore = atoi(argv[3]);
	Player* player0 = Player_factory(argv[4], argv[5]);
	Player* player1 = Player_factory(argv[6], argv[7]);
	Player* player2 = Player_factory(argv[8], argv[9]);
	Player* player3 = Player_factory(argv[10], argv[11]);
	vector <Player*> players;
	players.push_back(player0);
	players.push_back(player1);
	players.push_back(player2);
	players.push_back(player3);

	//create new pointer
	Game* game = new Game(openPack, players, choice, targetSore);
	//play
	game->startGame();
	
	game->delete_players();

	delete game;
	return 0;
}