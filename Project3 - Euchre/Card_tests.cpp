// Project UID 1d9f47bfc76643019cfbf037641defe1



#include "Card.h"

#include "unit_test_framework.h" 

#include <iostream>



using namespace std;



//bowers, same rank, trumps

TEST(test_card_ctor) {

	Card c(Card::RANK_ACE, Card::SUIT_HEARTS);

	ASSERT_EQUAL(Card::RANK_ACE, c.get_rank());

	ASSERT_EQUAL(Card::SUIT_HEARTS, c.get_suit());

}

TEST(test_get_rank_and_get_suit)

{

	Card five_spades = Card(Card::RANK_FIVE, Card::SUIT_SPADES);

	ASSERT_EQUAL(five_spades.get_rank(), Card::RANK_FIVE);

	ASSERT_EQUAL(five_spades.get_suit(), Card::SUIT_SPADES);

}



TEST(test_is_face)

{

	Card five_spades = Card(Card::RANK_FIVE, Card::SUIT_SPADES);

	ASSERT_FALSE(five_spades.is_face());



	Card queen_diamonds = Card(Card::RANK_QUEEN, Card::SUIT_DIAMONDS);

	ASSERT_TRUE(queen_diamonds.is_face());

}



TEST(test_is_right_and_left_bowers)

{

	Card jack_spades = Card(Card::RANK_JACK, Card::SUIT_SPADES);

	ASSERT_TRUE(jack_spades.is_right_bower(Card::SUIT_SPADES));

	ASSERT_FALSE(jack_spades.is_left_bower(Card::SUIT_SPADES));



	Card jack_hearts = Card(Card::RANK_JACK, Card::SUIT_HEARTS);

	ASSERT_FALSE(jack_hearts.is_left_bower(Card::SUIT_SPADES));

	ASSERT_FALSE(jack_hearts.is_right_bower(Card::SUIT_SPADES));

	ASSERT_FALSE(jack_hearts.is_left_bower(Card::SUIT_CLUBS));

	ASSERT_FALSE(jack_hearts.is_right_bower(Card::SUIT_CLUBS));

}



TEST(test_is_trump)

{

	Card jack_spades = Card(Card::RANK_JACK, Card::SUIT_SPADES);

	ASSERT_TRUE(jack_spades.is_trump(Card::SUIT_SPADES));

	ASSERT_TRUE(jack_spades.is_trump(Card::SUIT_CLUBS));

	ASSERT_FALSE(jack_spades.is_trump(Card::SUIT_HEARTS));

}



TEST(test_comparison_operators)

{

	Card jack_spades = Card(Card::RANK_JACK, Card::SUIT_SPADES);



	ASSERT_FALSE(jack_spades < jack_spades);

	ASSERT_FALSE(jack_spades > jack_spades);

	ASSERT_TRUE(jack_spades == jack_spades);

	ASSERT_FALSE(jack_spades != jack_spades);



	Card queen_hearts = Card(Card::RANK_QUEEN, Card::SUIT_HEARTS);

	Card queen_diamonds = Card(Card::RANK_QUEEN, Card::SUIT_DIAMONDS);

	Card queen_clubs = Card(Card::RANK_QUEEN, Card::SUIT_CLUBS);

	Card queen_spades = Card(Card::RANK_QUEEN, Card::SUIT_SPADES);



	ASSERT_FALSE(queen_hearts == queen_diamonds);

	ASSERT_FALSE(queen_diamonds < queen_hearts);

	ASSERT_TRUE(queen_clubs > queen_spades);

	ASSERT_TRUE(queen_hearts < queen_clubs);

}



TEST(test_suit_next)

{

	ASSERT_EQUAL(Suit_next(Card::SUIT_CLUBS), Card::SUIT_SPADES);

	ASSERT_EQUAL(Suit_next(Card::SUIT_DIAMONDS), Card::SUIT_HEARTS);

}



TEST(test_first_card_less)

{

	Card jack_spades = Card(Card::RANK_JACK, Card::SUIT_SPADES);

	Card jack_clubs = Card(Card::RANK_JACK, Card::SUIT_CLUBS);

	Card king_spades = Card(Card::RANK_KING, Card::SUIT_SPADES);

	Card jack_hearts = Card(Card::RANK_JACK, Card::SUIT_HEARTS);



	ASSERT_TRUE(Card_less(jack_spades, jack_spades, Card::SUIT_SPADES))

		ASSERT_TRUE(Card_less(jack_spades, jack_clubs, Card::SUIT_CLUBS));

	ASSERT_FALSE(Card_less(jack_spades, jack_clubs, Card::SUIT_SPADES))

		ASSERT_TRUE(Card_less(king_spades, jack_clubs, Card::SUIT_SPADES));

	ASSERT_TRUE(Card_less(king_spades, jack_spades, Card::SUIT_SPADES));

	ASSERT_FALSE(Card_less(king_spades, jack_hearts, Card::SUIT_SPADES))

}



TEST(test_second_card_less)

{

	Card jack_spades = Card(Card::RANK_JACK, Card::SUIT_SPADES);

	Card jack_clubs = Card(Card::RANK_JACK, Card::SUIT_CLUBS);

	Card king_spades = Card(Card::RANK_KING, Card::SUIT_SPADES);

	Card jack_hearts = Card(Card::RANK_JACK, Card::SUIT_HEARTS);

	Card jack_diamonds = Card(Card::RANK_JACK, Card::SUIT_DIAMONDS);

	Card ace_diamonds = Card(Card::RANK_ACE, Card::SUIT_DIAMONDS);



	ASSERT_FALSE(Card_less(jack_spades, jack_spades, jack_spades,

		Card::SUIT_SPADES));

	ASSERT_TRUE(Card_less(jack_diamonds, jack_spades, ace_diamonds,

		Card::SUIT_SPADES));

	ASSERT_FALSE(Card_less(jack_diamonds, jack_hearts, ace_diamonds,

		Card::SUIT_SPADES));

	ASSERT_FALSE(Card_less(ace_diamonds, jack_hearts, jack_diamonds,

		Card::SUIT_SPADES));

}



TEST(test_card_insertion) {

	Card three_spades = Card(Card::RANK_THREE, Card::SUIT_SPADES);

	ostringstream oss;

	oss << three_spades;

	ASSERT_EQUAL(oss.str(), "Three of Spades");

}





// Add more test cases here



TEST_MAIN()