// Project UID c1f28c309e55405daf00c565d57ff9ad

#include <string>
#include "List.h"
#include "unit_test_framework.h"

using namespace std;

// Add your test cases here
TEST(testEmpty) 
{
	List<int> list1;
	list1.push_back(10);
	list1.push_front(500);
	ASSERT_FALSE(list1.empty());

	list1.pop_front();
	list1.pop_back();
	ASSERT_TRUE(list1.empty());

	list1.clear();
	ASSERT_TRUE(list1.empty());
}
TEST(testSize)
{
	List<double> list1;
	for (int i = 0; i < 500; i++)
	{
		list1.push_front(1);
		list1.push_back(2);
	}
	ASSERT_EQUAL(list1.size(), 1000);

	list1.clear();
	ASSERT_EQUAL(list1.size(), 0);

	List<double> list2 = list1;
	ASSERT_EQUAL(list2.size(), 0);

}
TEST(testFrontandBack)
{
	List<int> list1;

	for (int i = 0; i < 5; i++)
	{
		list1.push_back(i);
	}
	ASSERT_EQUAL(list1.back(), 4);
	ASSERT_EQUAL(list1.front(), 0);
	
	list1.push_back(6);
	list1.push_front(10);
	ASSERT_EQUAL(list1.back(), 6);
	ASSERT_EQUAL(list1.front(), 10);
}
TEST(testClearandPopPush)
{
	List<int> list1;
	for ( int i = 0; i < 10; i++)
	{
		list1.push_front(1);
		list1.push_back(2);
	}
	ASSERT_EQUAL(list1.front(), 1);

	for (int i = 0; i < 10; i++)
	{
		list1.pop_front();
	}
	ASSERT_EQUAL(list1.front(), 2);

	list1.clear();
	list1.push_back(5);
	ASSERT_EQUAL(list1.back(), 5);
	ASSERT_EQUAL(list1.front(), 5);

	list1.clear();
	ASSERT_EQUAL(list1.size(), 0);

	List<double> list2;
	for (int i = 0; i < 10; i++)
	{
		list2.push_back(1);
	}
	list2.pop_back();
	ASSERT_TRUE(list2.size() == 9);
}
TEST(testConstructorandOverload)
{
	List<double> list1;
	for (int i = 0; i < 5; i++)
	{
		list1.push_back(1);
	}

	List<double>list2(list1);
	
	ASSERT_EQUAL(list1.front(), list2.front());
	ASSERT_EQUAL(list1.back(), list2.back());

	List<bool> list3;
	List<bool> list4(list3);
	ASSERT_TRUE(list4.size() == 0);

	List<bool> list5;
	list5.push_front(true);
	list4 = list5;
	ASSERT_EQUAL(list4.front(), true);

	list1.clear();
	list2 = list1;
	ASSERT_EQUAL(list1.begin(), list2.begin());
}
TEST(testIteratorConstructorandOverload)
{
	List<int> l1;
	for (int i = 0; i < 10; i++)
	{
		l1.push_back(i);
	}

	List<int>::Iterator it = l1.begin();
	++it;
	ASSERT_EQUAL(*it, 1);
	--it;
	ASSERT_EQUAL(*it, 0);

	List<int>::Iterator it2;
	it2 = it;
	ASSERT_EQUAL(*it, 0);

	ASSERT_TRUE(it2 == it);

	List<int> l2;
	l2.push_back(5);
	List<int>::Iterator it3;
	List<int>::Iterator it4 = l2.begin();
	ASSERT_TRUE(it3 != it4);
}
TEST(testInsert)
{
	List<int> l1;
	for (int i = 0; i < 10; i++)
	{
		l1.push_front(i);
	}

	List<int>::Iterator it = l1.begin();
	l1.insert(it, 11);
	--it;
	ASSERT_EQUAL(*it, 11);
}
TEST(testInsert1)
{
	List<int> l1;
	List<int>::Iterator it = l1.begin();
	l1.clear();
	it = l1.begin();
	l1.insert(it, 100);
	ASSERT_EQUAL(l1.front(), 100);
}
TEST(testInsert2)
{
	List<int> l1;
	List<int>::Iterator it = l1.begin();
	for (int i = 0; i < 10; i++)
	{
		l1.push_front(i);
	}
	it = l1.end();
	l1.insert(it, 5);
	ASSERT_EQUAL(l1.back(), 5);
}
TEST(testErase)
{
	List<int> l1;
	for (int i = 0; i < 5; i++)
	{
		l1.push_back(i);
	}
	List<int>::Iterator it = l1.begin();
	l1.erase(it);
	ASSERT_TRUE(l1.size() == 4);
	ASSERT_EQUAL(l1.front(), 1);
	ASSERT_EQUAL(l1.back(), 4);

	List<int>::Iterator it2 = l1.begin();
	++ ++it2;
	l1.erase(it2);
	ASSERT_TRUE(l1.size() == 3);
	ASSERT_EQUAL(l1.front(), 1);
	ASSERT_EQUAL(l1.back(), 4);

	List<int>::Iterator it3 = l1.begin();
	++ ++it3;
	l1.erase(it3);
	ASSERT_TRUE(l1.size() == 2);
	ASSERT_EQUAL(l1.front(), 1);
	ASSERT_EQUAL(l1.back(), 2);
}

TEST(testErase1)
{
	List<int> l1;
	for (int i = 0; i < 50; i++)
	{
		l1.push_back(i);
	}
	List<int>::Iterator it = l1.begin();
	l1.erase(it);

	it = l1.begin();
	++ ++it;
	l1.erase(it);
	ASSERT_TRUE(l1.size() == 48);
	ASSERT_EQUAL(l1.front(), 1);
	ASSERT_EQUAL(l1.back(), 49);

}
TEST_MAIN()
