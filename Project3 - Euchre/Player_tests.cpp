// Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Player.h"
#include "unit_test_framework.h"

#include <iostream>

using namespace std;

TEST(test_player_get_name)
{
	Player* alice = Player_factory("Alice", "Simple");
	ASSERT_EQUAL("Alice", alice->get_name());

	delete alice;
}

TEST(testSimpleAddCard1)
{
	Player* bob1 = Player_factory("Bob", "Simple");

	vector <Card> testArr = { {Card::RANK_TEN, Card::SUIT_CLUBS} };
	for (int i = 0; i < int(testArr.size()); i++)
	{
		bob1->add_card(testArr[i]);
	}

	Card expected = { Card::RANK_TEN, Card::SUIT_CLUBS };
	ASSERT_EQUAL(testArr[0], expected);
	delete bob1;
}

TEST(testSimpleAddCard2)
{
	Player* bob2 = Player_factory("Bob", "Simple");

	vector <Card> testArr = { {Card::RANK_TEN, Card::SUIT_CLUBS},
	{Card::RANK_JACK, Card::SUIT_CLUBS},{Card::RANK_QUEEN, Card::SUIT_CLUBS},
	{Card::RANK_KING, Card::SUIT_CLUBS},{Card::RANK_ACE, Card::SUIT_CLUBS} };
	for (int i = 0; i < int(testArr.size()); i++)
	{
		bob2->add_card(testArr[i]);
	}

	Card expected = { Card::RANK_ACE, Card::SUIT_CLUBS };
	ASSERT_EQUAL(testArr[4], expected);
	delete bob2;
}

TEST(testSimpleAddDiscard1)
{
	Player* bob1 = Player_factory("Bob", "Simple");

	vector <Card> testArr = { {Card::RANK_TEN, Card::SUIT_CLUBS} };
	for (int i = 0; i < int(testArr.size()); i++)
	{
		bob1->add_card(testArr[i]);
	}
	Card upcard = { Card::RANK_TEN, Card::SUIT_HEARTS };

	bob1->add_and_discard(upcard);

	Card expected = { Card::RANK_TEN, Card::SUIT_CLUBS };
	ASSERT_EQUAL(testArr[0], expected);
	delete bob1;

}

TEST(testSimpleMakeTrump1)
{
	//TEST 1 - Entire hand is the same suit, should assert true
	//Create new Player object
	Player* bob = Player_factory("Bob", "Simple");

	//Initalize parameter variables
	int round = 1;
	bool isDealer = false;
	string trump = Card::SUIT_CLUBS;
	Card upCard(Card::RANK_NINE, Card::SUIT_CLUBS);

	//Create cards to pass into player hand
	vector <Card> testArr = { {Card::RANK_TEN, Card::SUIT_CLUBS},
	{Card::RANK_JACK, Card::SUIT_CLUBS},{Card::RANK_QUEEN, Card::SUIT_CLUBS},
	{Card::RANK_KING, Card::SUIT_CLUBS},{Card::RANK_ACE, Card::SUIT_CLUBS} };
	for (int i = 0; i < int(testArr.size()); i++)
	{
		bob->add_card(testArr[i]);
	}

	bool test = bob->make_trump(upCard, isDealer, round, trump);
	ASSERT_TRUE(test);
	ASSERT_EQUAL(trump, Card::SUIT_CLUBS);
	delete bob;
}
TEST(testSimpleMakeTrump2)
{
	//TEST 2 - All Jacks, testing left and right bower, should pass
	Player* bob1 = Player_factory("Bob", "Simple");

	//Initalize parameter variables
	int round1 = 1;
	bool isDealer1 = false;
	string trump1 = Card::SUIT_CLUBS;
	Card upCard1(Card::RANK_ACE, Card::SUIT_CLUBS);

	//Create cards to pass into player hand
	vector <Card> testArr1 = { {Card::RANK_JACK, Card::SUIT_CLUBS},
	{Card::RANK_JACK, Card::SUIT_HEARTS},{Card::RANK_JACK, Card::SUIT_DIAMONDS},
	{Card::RANK_JACK, Card::SUIT_SPADES},{Card::RANK_ACE, Card::SUIT_DIAMONDS} };
	for (int i = 0; i < int(testArr1.size()); i++)
	{
		bob1->add_card(testArr1[i]);
	}
	bool test1 = bob1->make_trump(upCard1, isDealer1, round1, trump1);
	ASSERT_TRUE(test1);
	ASSERT_EQUAL(trump1, Card::SUIT_CLUBS);
	delete bob1;
}

TEST(testSimpleMakeTrump3)
{
	//TEST 3 - Should change trump suit, passing all diamonds
	Player* bob2 = Player_factory("Bob", "Simple");

	//Initalize parameter variables
	int round2 = 1;
	bool isDealer2 = false;
	string trump2 = Card::SUIT_CLUBS;
	Card upCard2(Card::RANK_ACE, Card::SUIT_CLUBS);

	//Create cards to pass into player hand
	vector <Card> testArr2 = { {Card::RANK_ACE, Card::SUIT_DIAMONDS},
	{Card::RANK_KING, Card::SUIT_DIAMONDS},{Card::RANK_QUEEN, Card::SUIT_DIAMONDS},
	{Card::RANK_JACK, Card::SUIT_DIAMONDS},{Card::RANK_ACE, Card::SUIT_CLUBS} };
	for (int i = 0; i < int(testArr2.size()); i++)
	{
		bob2->add_card(testArr2[i]);
	}
	bool test2 = bob2->make_trump(upCard2, isDealer2, round2, trump2);
	ASSERT_FALSE(test2);
	ASSERT_EQUAL(trump2, Card::SUIT_CLUBS);
	delete bob2;
}
TEST(testSimpleMakeTrump4)
{
	//TEST 4 - 2 face cards of upcard suit and 3 face cards of non-upcard suit
	Player* bob4 = Player_factory("Bob", "Simple");

	//Initalize parameter variables
	int round4 = 1;
	bool isDealer4 = false;
	string trump4 = Card::SUIT_HEARTS;
	Card upCard4(Card::RANK_NINE, Card::SUIT_SPADES);

	//Create cards to pass into player hand
	vector <Card> testArr4 = { {Card::RANK_JACK, Card::SUIT_SPADES},
	{Card::RANK_QUEEN, Card::SUIT_SPADES},{Card::RANK_JACK, Card::SUIT_DIAMONDS},
	{Card::RANK_ACE, Card::SUIT_CLUBS},{Card::RANK_ACE, Card::SUIT_HEARTS} };
	for (int i = 0; i < int(testArr4.size()); i++)
	{
		bob4->add_card(testArr4[i]);
	}
	bool test4 = bob4->make_trump(upCard4, isDealer4, round4, trump4);
	ASSERT_TRUE(test4);
	ASSERT_EQUAL(trump4, Card::SUIT_SPADES);
	delete bob4;
}
TEST(testSimpleMakeTrump5)
{
	//TEST 5 - 2 non-face trump cards, should pass
	Player* bob5 = Player_factory("Bob", "Simple");

	int round5 = 1;
	bool isDealer5 = true;
	string trump5 = Card::SUIT_HEARTS;
	Card upCard5(Card::RANK_JACK, Card::SUIT_HEARTS);

	//Create cards to pass into player hand
	vector <Card> testArr5 = { {Card::RANK_NINE, Card::SUIT_HEARTS},
	{Card::RANK_TEN, Card::SUIT_HEARTS},{Card::RANK_NINE, Card::SUIT_DIAMONDS},
	{Card::RANK_TEN, Card::SUIT_DIAMONDS},{Card::RANK_NINE, Card::SUIT_CLUBS} };
	for (int i = 0; i < int(testArr5.size()); i++)
	{
		bob5->add_card(testArr5[i]);
	}
	bool test5 = bob5->make_trump(upCard5, isDealer5, round5, trump5);
	ASSERT_FALSE(test5);
	ASSERT_EQUAL(trump5, Card::SUIT_HEARTS);
	delete bob5;
}
TEST(testSimpleMakeTrump6)
{
	//TEST 6 - only one face card, but same color as upcard
	Player* bob6 = Player_factory("Bob", "Simple");

	int round6 = 2;
	bool isDealer6 = true;
	string trump6 = Card::SUIT_HEARTS;
	Card upCard6(Card::RANK_NINE, Card::SUIT_DIAMONDS);

	//Create cards to pass into player hand
	vector <Card> testArr6 = { {Card::RANK_NINE, Card::SUIT_HEARTS},
	{Card::RANK_TEN, Card::SUIT_DIAMONDS},{Card::RANK_JACK, Card::SUIT_HEARTS},
	{Card::RANK_NINE, Card::SUIT_CLUBS},{Card::RANK_TEN, Card::SUIT_SPADES} };
	for (int i = 0; i < int(testArr6.size()); i++)
	{
		bob6->add_card(testArr6[i]);
	}
	bool test6 = bob6->make_trump(upCard6, isDealer6, round6, trump6);
	ASSERT_TRUE(test6);
	ASSERT_EQUAL(trump6, Card::SUIT_DIAMONDS);
	delete bob6;
}
TEST(testSimpleMakeTrump7)
{
	//TEST 7 - only one face card, but not the same color as upcard
	Player* bob7 = Player_factory("Bob", "Simple");

	int round7 = 2;
	bool isDealer7 = true;
	string trump7 = Card::SUIT_HEARTS;
	Card upCard7(Card::RANK_NINE, Card::SUIT_DIAMONDS);

	//Create cards to pass into player hand
	vector <Card> testArr7 = { {Card::RANK_NINE, Card::SUIT_HEARTS},
	{Card::RANK_TEN, Card::SUIT_DIAMONDS},{Card::RANK_JACK, Card::SUIT_SPADES},
	{Card::RANK_NINE, Card::SUIT_CLUBS},{Card::RANK_TEN, Card::SUIT_SPADES} };
	for (int i = 0; i < int(testArr7.size()); i++)
	{
		bob7->add_card(testArr7[i]);
	}
	bool test7 = bob7->make_trump(upCard7, isDealer7, round7, trump7);
	ASSERT_TRUE(test7);
	ASSERT_EQUAL(trump7, Card::SUIT_DIAMONDS);
	delete bob7;
}

TEST(testSimpleLeadCard1)
{
	//TEST 1 - No trump cards
	Player* bob1 = Player_factory("Bob", "Simple");
	string trump1 = Card::SUIT_HEARTS;

	vector <Card> testArr1 = { {Card::RANK_ACE, Card::SUIT_SPADES},
	{Card::RANK_KING, Card::SUIT_SPADES},{Card::RANK_QUEEN, Card::SUIT_SPADES},
	{Card::RANK_JACK, Card::SUIT_SPADES},{Card::RANK_NINE, Card::SUIT_SPADES} };
	for (int i = 0; i < int(testArr1.size()); i++)
	{
		bob1->add_card(testArr1[i]);
	}
	Card correctCard = { Card::RANK_ACE, Card::SUIT_SPADES };
	Card ledCard = bob1->lead_card(trump1);
	ASSERT_EQUAL(correctCard, ledCard);
	delete bob1;
}
TEST(testSimpleLeadCard2)
{
	//Test 2 - Has left and right bower
	Player* bob2 = Player_factory("Bob", "Simple");
	string trump2 = Card::SUIT_HEARTS;

	vector <Card> testArr2 = { {Card::RANK_ACE, Card::SUIT_HEARTS},
	{Card::RANK_KING, Card::SUIT_HEARTS},{Card::RANK_QUEEN, Card::SUIT_HEARTS},
	{Card::RANK_JACK, Card::SUIT_HEARTS},{Card::RANK_JACK, Card::SUIT_DIAMONDS} };
	for (int i = 0; i < int(testArr2.size()); i++)
	{
		bob2->add_card(testArr2[i]);
	}
	Card correctCard2 = { Card::RANK_JACK, Card::SUIT_HEARTS };
	Card ledCard2 = bob2->lead_card(trump2);
	ASSERT_EQUAL(correctCard2, ledCard2);
	delete bob2;
}
TEST(testSimpleLeadCard3)
{
	//TEST 3- Only 1 trump card
	Player* bob3 = Player_factory("Bob", "Simple");
	string trump3 = Card::SUIT_HEARTS;

	vector <Card> testArr3 = { {Card::RANK_NINE, Card::SUIT_HEARTS},
	{Card::RANK_KING, Card::SUIT_SPADES},{Card::RANK_QUEEN, Card::SUIT_SPADES},
	{Card::RANK_JACK, Card::SUIT_SPADES},{Card::RANK_JACK, Card::SUIT_CLUBS} };
	for (int i = 0; i < int(testArr3.size()); i++)
	{
		bob3->add_card(testArr3[i]);
	}
	Card correctCard3 = { Card::RANK_KING, Card::SUIT_SPADES };
	Card ledCard3 = bob3->lead_card(trump3);
	ASSERT_EQUAL(correctCard3, ledCard3);
	delete bob3;
}
TEST(testSimpleLeadCard4)
{
	//TEST 4 - multiple trumps
	Player* bob4 = Player_factory("Bob", "Simple");
	string trump4 = Card::SUIT_CLUBS;

	vector <Card> testArr4 = { {Card::RANK_NINE, Card::SUIT_CLUBS},
	{Card::RANK_KING, Card::SUIT_CLUBS},{Card::RANK_QUEEN, Card::SUIT_CLUBS},
	{Card::RANK_JACK, Card::SUIT_DIAMONDS},{Card::RANK_ACE, Card::SUIT_SPADES} };
	for (int i = 0; i < int(testArr4.size()); i++)
	{
		bob4->add_card(testArr4[i]);
	}
	Card correctCard4 = { Card::RANK_ACE, Card::SUIT_SPADES };
	Card ledCard4 = bob4->lead_card(trump4);
	ASSERT_EQUAL(correctCard4, ledCard4);
	delete bob4;
}
TEST(testSimpleLeadCard5)
{
	//TEST 5 - all trump 
	Player* bob5 = Player_factory("Bob", "Simple");
	string trump5 = Card::SUIT_CLUBS;

	vector <Card> testArr5 = { {Card::RANK_NINE, Card::SUIT_CLUBS},
	{Card::RANK_KING, Card::SUIT_CLUBS},{Card::RANK_QUEEN, Card::SUIT_CLUBS},
	{Card::RANK_JACK, Card::SUIT_CLUBS},{Card::RANK_ACE, Card::SUIT_CLUBS} };
	for (int i = 0; i < int(testArr5.size()); i++)
	{
		bob5->add_card(testArr5[i]);
	}
	Card correctCard5 = { Card::RANK_JACK, Card::SUIT_CLUBS };
	Card ledCard5 = bob5->lead_card(trump5);
	ASSERT_EQUAL(correctCard5, ledCard5);
	delete bob5;
}
TEST(testSimpleLeadCard6)
{
	//TEST 6- leading card while left and right bower are present
	Player* bob6 = Player_factory("Bob", "Simple");
	string trump6 = Card::SUIT_CLUBS;

	vector <Card> testArr6 = { {Card::RANK_JACK, Card::SUIT_CLUBS},
	{Card::RANK_QUEEN, Card::SUIT_HEARTS},{Card::RANK_KING, Card::SUIT_CLUBS},
	{Card::RANK_ACE, Card::SUIT_SPADES},{Card::RANK_ACE, Card::SUIT_CLUBS} };
	for (int i = 0; i < int(testArr6.size()); i++)
	{
		bob6->add_card(testArr6[i]);
	}
	Card correctCard6 = { Card::RANK_ACE, Card::SUIT_SPADES };
	Card ledCard6 = bob6->lead_card(trump6);
	ASSERT_EQUAL(correctCard6, ledCard6);
	delete bob6;
}
TEST(testSimpleLeadCard7)
{
	//TEST 7 - all jacks plus ace
	Player* bob7 = Player_factory("Bob", "Simple");
	string trump7 = Card::SUIT_SPADES;

	vector <Card> testArr7 = { {Card::RANK_JACK, Card::SUIT_CLUBS},
	{Card::RANK_JACK, Card::SUIT_SPADES},{Card::RANK_JACK, Card::SUIT_DIAMONDS},
	{Card::RANK_JACK, Card::SUIT_HEARTS},{Card::RANK_ACE, Card::SUIT_CLUBS} };
	for (int i = 0; i < int(testArr7.size()); i++)
	{
		bob7->add_card(testArr7[i]);
	}
	Card correctCard7 = { Card::RANK_ACE, Card::SUIT_CLUBS };
	Card ledCard7 = bob7->lead_card(trump7);
	ASSERT_EQUAL(correctCard7, ledCard7);
	delete bob7;
}

TEST(testSimplePlayCard1)
{
	//TEST 1- all trump, led is diamond, should return Jack of Diamonds
	Player* bob1 = Player_factory("Bob", "Simple");
	string trump1 = Card::SUIT_DIAMONDS;
	vector <Card> testArr1 = { {Card::RANK_ACE, Card::SUIT_DIAMONDS},
	{Card::RANK_JACK, Card::SUIT_DIAMONDS},{Card::RANK_QUEEN, Card::SUIT_DIAMONDS},
	{Card::RANK_KING, Card::SUIT_DIAMONDS},{Card::RANK_JACK, Card::SUIT_HEARTS} };
	for (int i = 0; i < int(testArr1.size()); i++)
	{
		bob1->add_card(testArr1[i]);
	}

	Card ledCard1(Card::RANK_NINE, Card::SUIT_DIAMONDS);
	Card cardPlayed1 = bob1->play_card(ledCard1, trump1);
	Card correctCard1(Card::RANK_JACK, Card::SUIT_DIAMONDS);
	ASSERT_EQUAL(cardPlayed1, correctCard1);
	delete bob1;
}
TEST(testSimplePlayCard2)
{
	//TEST 2 - No led card suits, should return Nine of Spades
	Player* bob2 = Player_factory("Bob", "Simple");
	string trump2 = Card::SUIT_DIAMONDS;
	vector <Card> testArr2 = { {Card::RANK_ACE, Card::SUIT_SPADES},
	{Card::RANK_JACK, Card::SUIT_SPADES},{Card::RANK_QUEEN, Card::SUIT_SPADES},
	{Card::RANK_KING, Card::SUIT_SPADES},{Card::RANK_NINE, Card::SUIT_SPADES} };
	for (int i = 0; i < int(testArr2.size()); i++)
	{
		bob2->add_card(testArr2[i]);
	}

	Card ledCard2(Card::RANK_NINE, Card::SUIT_HEARTS);
	Card cardPlayed2 = bob2->play_card(ledCard2, trump2);
	Card correctCard2(Card::RANK_NINE, Card::SUIT_SPADES);
	ASSERT_EQUAL(cardPlayed2, correctCard2);
	delete bob2;
}
TEST(testSimplePlayCard3)
{
	//TEST 3 - 1 led card, should return Queen of Hearts
	Player* bob3 = Player_factory("Bob", "Simple");
	string trump3 = Card::SUIT_DIAMONDS;
	vector <Card> testArr3 = { {Card::RANK_ACE, Card::SUIT_SPADES},
	{Card::RANK_JACK, Card::SUIT_SPADES},{Card::RANK_QUEEN, Card::SUIT_HEARTS},
	{Card::RANK_KING, Card::SUIT_SPADES},{Card::RANK_NINE, Card::SUIT_SPADES} };
	for (int i = 0; i < int(testArr3.size()); i++)
	{
		bob3->add_card(testArr3[i]);
	}

	Card ledCard3(Card::RANK_NINE, Card::SUIT_HEARTS);
	Card cardPlayed3 = bob3->play_card(ledCard3, trump3);
	Card correctCard3(Card::RANK_QUEEN, Card::SUIT_HEARTS);
	ASSERT_EQUAL(cardPlayed3, correctCard3);
	delete bob3;
}
TEST(testSimplePlayCard4)
{
	//TEST 4- 2 led cards, one Jack, one Ace at the start and end of the array
	Player* bob4 = Player_factory("Bob", "Simple");
	string trump4 = Card::SUIT_HEARTS;
	vector <Card> testArr4 = { {Card::RANK_ACE, Card::SUIT_HEARTS},
	{Card::RANK_JACK, Card::SUIT_SPADES},{Card::RANK_QUEEN, Card::SUIT_HEARTS},
	{Card::RANK_KING, Card::SUIT_SPADES},{Card::RANK_JACK, Card::SUIT_HEARTS} };
	for (int i = 0; i < int(testArr4.size()); i++)
	{
		bob4->add_card(testArr4[i]);
	}

	Card ledCard4(Card::RANK_NINE, Card::SUIT_HEARTS);
	Card cardPlayed4 = bob4->play_card(ledCard4, trump4);
	Card correctCard4(Card::RANK_JACK, Card::SUIT_HEARTS);
	ASSERT_EQUAL(cardPlayed4, correctCard4);
	delete bob4;
}
TEST(testSimplePlayCard5)
{
	//TEST 5-
	Player* bob5 = Player_factory("Bob", "Simple");
	string trump5 = Card::SUIT_CLUBS;
	vector <Card> testArr5 = { {Card::RANK_JACK, Card::SUIT_HEARTS},
	{Card::RANK_QUEEN, Card::SUIT_HEARTS},{Card::RANK_KING, Card::SUIT_HEARTS},
	{Card::RANK_ACE, Card::SUIT_HEARTS},{Card::RANK_TEN, Card::SUIT_HEARTS} };
	for (int i = 0; i < int(testArr5.size()); i++)
	{
		bob5->add_card(testArr5[i]);
	}

	Card ledCard5(Card::RANK_NINE, Card::SUIT_HEARTS);
	Card cardPlayed5 = bob5->play_card(ledCard5, trump5);
	Card correctCard5(Card::RANK_ACE, Card::SUIT_HEARTS);
	ASSERT_EQUAL(cardPlayed5, correctCard5);
	delete bob5;
}
TEST(testSimplePlayCard6)
{
	//TEST 5-
	Player* bob6 = Player_factory("Bob", "Simple");
	string trump6 = Card::SUIT_HEARTS;
	vector <Card> testArr6 = { {Card::RANK_JACK, Card::SUIT_HEARTS},
	{Card::RANK_QUEEN, Card::SUIT_HEARTS},{Card::RANK_KING, Card::SUIT_HEARTS},
	{Card::RANK_ACE, Card::SUIT_HEARTS},{Card::RANK_TEN, Card::SUIT_HEARTS} };
	for (int i = 0; i < int(testArr6.size()); i++)
	{
		bob6->add_card(testArr6[i]);
	}

	Card ledCard6(Card::RANK_NINE, Card::SUIT_CLUBS);
	Card cardPlayed6 = bob6->play_card(ledCard6, trump6);
	Card correctCard6(Card::RANK_TEN, Card::SUIT_HEARTS);
	ASSERT_EQUAL(cardPlayed6, correctCard6);
	delete bob6;
}
TEST(testSimplePlayCard7)
{
	//TEST 5-
	Player* bob7 = Player_factory("Bob", "Simple");
	string trump7 = Card::SUIT_HEARTS;
	vector <Card> testArr7 = { {Card::RANK_ACE, Card::SUIT_HEARTS},
	{Card::RANK_ACE, Card::SUIT_CLUBS},{Card::RANK_ACE, Card::SUIT_SPADES},
	{Card::RANK_ACE, Card::SUIT_DIAMONDS},{Card::RANK_JACK, Card::SUIT_CLUBS} };
	for (int i = 0; i < int(testArr7.size()); i++)
	{
		bob7->add_card(testArr7[i]);
	}

	Card ledCard7(Card::RANK_NINE, Card::SUIT_CLUBS);
	Card cardPlayed7 = bob7->play_card(ledCard7, trump7);
	Card correctCard7(Card::RANK_ACE, Card::SUIT_CLUBS);
	ASSERT_EQUAL(cardPlayed7, correctCard7);
	delete bob7;
}
// Add more tests here

TEST_MAIN()
