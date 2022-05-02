// Project UID 1d9f47bfc76643019cfbf037641defe1

#include <cassert>
#include <iostream>
#include <string>
#include "Card.h"
using namespace std;

// add any necessary #include or using directives here

// rank and suit names -- do not remove these
constexpr const char* const Card::RANK_TWO;
constexpr const char* const Card::RANK_THREE;
constexpr const char* const Card::RANK_FOUR;
constexpr const char* const Card::RANK_FIVE;
constexpr const char* const Card::RANK_SIX;
constexpr const char* const Card::RANK_SEVEN;
constexpr const char* const Card::RANK_EIGHT;
constexpr const char* const Card::RANK_NINE;
constexpr const char* const Card::RANK_TEN;
constexpr const char* const Card::RANK_JACK;
constexpr const char* const Card::RANK_QUEEN;
constexpr const char* const Card::RANK_KING;
constexpr const char* const Card::RANK_ACE;

constexpr const char* const Card::SUIT_SPADES;
constexpr const char* const Card::SUIT_HEARTS;
constexpr const char* const Card::SUIT_CLUBS;
constexpr const char* const Card::SUIT_DIAMONDS;

// add your code below

Card::Card()
:rank(RANK_TWO), suit(SUIT_SPADES){}

Card::Card(const string &rank_in, const string &suit_in)
:rank(rank_in), suit(suit_in){
    /*assert(rank_in == RANK_TWO || rank_in == RANK_THREE ||
     rank_in == RANK_FOUR || rank_in == RANK_FIVE ||
     rank_in == RANK_SIX || rank_in == RANK_SEVEN ||
     rank_in == RANK_EIGHT ||rank_in == RANK_TEN ||
     rank_in == RANK_JACK || rank_in == RANK_KING ||
     rank_in == RANK_QUEEN ||rank_in == RANK_ACE);
     
     assert(suit_in == SUIT_SPADES || suit_in == SUIT_HEARTS ||
     suit_in == SUIT_CLUBS ||suit_in == SUIT_DIAMONDS);*/
}

string Card::get_rank() const
{
    return rank;
}

string Card::get_suit() const
{
    return suit;
}

string Card::get_suit(const string &trump) const
{
    assert(trump == SUIT_CLUBS || trump == SUIT_DIAMONDS ||
           trump == SUIT_HEARTS || trump == SUIT_SPADES);
    if (get_rank() == RANK_JACK && get_suit() == Suit_next(trump))
    {
        return trump;
    }
    
    else
    {
        return suit;
    }
}

bool Card::is_face() const
{
    if (rank == RANK_ACE || rank == RANK_KING || rank == RANK_QUEEN || rank == RANK_JACK)
    {
        return true;
    }
    
    return false;
}

bool Card::is_right_bower(const string& trump) const
{
    if (rank == RANK_JACK && suit == trump)
    {
        return true;
    }
    return false;
}

bool Card::is_left_bower(const string& trump) const {
    if (rank == RANK_JACK && suit == Suit_next(trump))
    {
        return true;
    }
    return false;
}

bool Card::is_trump(const string& trump) const
{
    assert(trump == SUIT_SPADES || trump == SUIT_HEARTS ||
           trump == SUIT_DIAMONDS || trump == SUIT_CLUBS);
    
    if (suit == trump)
    {
        return true;
    }
    
    else if (rank == RANK_JACK && suit == Suit_next(trump))
    {
        return true;
    }
    return false;
}

string Suit_next(const string& suit)
{
    assert(suit == Card::SUIT_SPADES || suit == Card::SUIT_HEARTS ||
        suit == Card::SUIT_DIAMONDS || suit == Card::SUIT_CLUBS);

    if (suit == Card::SUIT_SPADES)
    {
        return Card::SUIT_CLUBS;
    }
    else if (suit == Card::SUIT_HEARTS)
    {
        return Card::SUIT_DIAMONDS;
    }
    else if (suit == Card::SUIT_DIAMONDS)
    {
        return Card::SUIT_HEARTS;
    }
    else
    {
        return Card::SUIT_SPADES;
    }
}

bool operator==(const Card& lhs, const Card& rhs)
{
    if ((lhs.get_rank() == rhs.get_rank()) && (lhs.get_suit() == rhs.get_suit()))
    {
        return true;
    }
    return false;
}

bool operator!=(const Card& lhs, const Card& rhs)
{
    if ((lhs.get_rank() != rhs.get_rank()) || (lhs.get_suit() != rhs.get_suit()))
    {
        return true;
    }
    return false;
}

ostream& operator<<(ostream& os, const Card& card)
{
    os << card.get_rank() << " of " << card.get_suit();

    return os;
}

bool operator<(const Card& lhs, const Card& rhs)
{
    if (lhs.get_rank() == rhs.get_rank() && lhs.get_suit() == rhs.get_suit())
    {
        return false;
    }

    for (int i = 0; i < NUM_RANKS; i++)
    {
        if (lhs.get_rank() == RANK_NAMES_BY_WEIGHT[i] &&
            rhs.get_rank() == RANK_NAMES_BY_WEIGHT[i])
        {
            for (int j = 0; j < NUM_SUITS; j++)
            {
                if (rhs.get_suit() == SUIT_NAMES_BY_WEIGHT[j])
                {
                    return false;
                }
                else if (lhs.get_suit() == SUIT_NAMES_BY_WEIGHT[j])
                {
                    return true;
                }
            }
        }
        else if (lhs.get_rank() == RANK_NAMES_BY_WEIGHT[i] &&
                 rhs.get_rank() != RANK_NAMES_BY_WEIGHT[i])
        {
            return true;
        }
        else if (rhs.get_rank() == RANK_NAMES_BY_WEIGHT[i])
        {
            return false;
        }
    }
    return true;
}

bool operator>(const Card& lhs, const Card& rhs)
{
    if (lhs.get_rank() == rhs.get_rank() && lhs.get_suit() == rhs.get_suit())
    {
        return false;
    }

    for (int j = 0; j < NUM_RANKS; j++)
    {
        if (lhs.get_rank() == RANK_NAMES_BY_WEIGHT[j] &&
            rhs.get_rank() == RANK_NAMES_BY_WEIGHT[j])
        {
            for (int i = 0; i < NUM_SUITS; i++)
            {
                if (rhs.get_suit() == SUIT_NAMES_BY_WEIGHT[i])
                {
                    return true;
                }
                else if (lhs.get_suit() == SUIT_NAMES_BY_WEIGHT[i])
                {
                    return false;
                }
            }
        }
        else if (lhs.get_rank() == RANK_NAMES_BY_WEIGHT[j] &&
            rhs.get_rank() != RANK_NAMES_BY_WEIGHT[j])
        {
            return false;
        }
        else if (rhs.get_rank() == RANK_NAMES_BY_WEIGHT[j])
        {
            return true;
        }
    }
    return true;
}

bool Card_less(const Card& a, const Card& b, const string& trump)
{
    if (b.is_right_bower(trump))
    {
        return true;
    }
    else if (a.is_right_bower(trump))
    {
        return false;
    }
    else if (b.is_left_bower(trump))
    {
        return true;
    }
    else if (a.is_left_bower(trump))
    {
        return false;
    }
    else if (a.is_trump(trump) && b.is_trump(trump))
    {
        return a < b;
    }
    else if (a.is_trump(trump))
    {
        return false;
    }
    else if (b.is_trump(trump))
    {
        return true;
    }
    else
    {
        return a < b;
    }
}

bool Card_less(const Card& a, const Card& b, const Card& led_card, const string& trump)
{
    assert(trump == Card::SUIT_SPADES || Card::SUIT_CLUBS ||
           Card::SUIT_HEARTS || Card::SUIT_DIAMONDS);
    
    if (a.is_right_bower(trump))
    {
        return false;
    }
    else if (b.is_right_bower(trump))
    {
        return true;
    }
    else if (a.is_left_bower(trump))
    {
        return false;
    }
    else if (b.is_left_bower(trump))
    {
        return true;
    }
    else if (a.is_trump(trump) && b.is_trump(trump))
    {
        return a < b;
    }
    else if (a.is_trump(trump))
    {
        return false;
    }
    else if (b.is_trump(trump))
    {
        return true;
    }
    else if (a.get_suit() == led_card.get_suit() &&
             b.get_suit() == led_card.get_suit())
    {
        return a < b;
    }
    else if (a.get_suit() == led_card.get_suit())
    {
        return false;
    }
    else if (b.get_suit() == led_card.get_suit())
    {
        return true;
    }
    else
    {
        return a < b;
    }
}
