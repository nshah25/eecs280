// Project UID db1f506d06d84ab787baf250c265e24e

#include "BinarySearchTree.h"
#include "unit_test_framework.h"
#include <sstream>
using namespace std;

TEST(testSizeHeightandEmpty)
{
	BinarySearchTree<int> treeTest1;
	ASSERT_TRUE(treeTest1.size() == 0);
	ASSERT_TRUE(treeTest1.height() == 0);
	ASSERT_TRUE(treeTest1.empty());

	for (int i = 0; i < 10; i++)
	{
		treeTest1.insert(i);
	}
	ASSERT_TRUE(treeTest1.size() == 10);
	ASSERT_TRUE(treeTest1.height() == 10);
	ASSERT_FALSE(treeTest1.empty());

	BinarySearchTree<int> treeTest2;

	treeTest2.insert(50);
	treeTest2.insert(60);
	treeTest2.insert(40);
	treeTest2.insert(70);
	ASSERT_EQUAL(treeTest2.height(), 3);
	treeTest2.insert(10);
	treeTest2.insert(0);
	ASSERT_EQUAL(treeTest2.height(), 4);
}

TEST(testCopy)
{
	BinarySearchTree<int> treeTest1;
	for (int i = 0; i < 3; i++)
	{
		treeTest1.insert(i);
	}
	BinarySearchTree<int> treeTestCopy1 = treeTest1;

	ASSERT_EQUAL(treeTest1.to_string(), treeTestCopy1.to_string());

	BinarySearchTree<int> treeTest2;
	treeTest2.insert(100);
	treeTest2.insert(50);
	treeTest2.insert(150);
	treeTest2.insert(200);
	treeTest2.insert(25);
	BinarySearchTree<int> treeTestCopy2 = treeTest2;

	ASSERT_EQUAL(treeTest2.to_string(), treeTestCopy2.to_string());

	BinarySearchTree<int> treeTest3;
	treeTest3.insert(1);
	BinarySearchTree<int> treeTestCopy3 = treeTest3;
	ASSERT_EQUAL(treeTest3.to_string(), treeTestCopy3.to_string());

	BinarySearchTree<int> treeTest4;
	BinarySearchTree<int> treeTestCopy4 = treeTest4;
	ASSERT_EQUAL(treeTest4.to_string(), treeTestCopy4.to_string());
}

TEST(testFind)
{
	BinarySearchTree<int> testTree1;
	testTree1.insert(5);
	testTree1.insert(10);
	testTree1.insert(15);
	BinarySearchTree<int>::Iterator it = testTree1.begin();
	BinarySearchTree<int>::Iterator it2 = testTree1.find(5);
	ASSERT_EQUAL(it, it2);
	
	BinarySearchTree<int> testTree2;
	testTree2.insert(5);
	testTree2.insert(10);
	testTree2.insert(15);
	BinarySearchTree<int>::Iterator it3 = testTree2.begin();
	BinarySearchTree<int>::Iterator it4 = testTree2.find(20);
	ASSERT_NOT_EQUAL(it3, it4);

	BinarySearchTree<int> testTree3;
	testTree3.insert(50);
	testTree3.insert(10);
	testTree3.insert(15);
	testTree3.insert(60);
	BinarySearchTree<int>::Iterator it5 = testTree3.begin();
	BinarySearchTree<int>::Iterator it6 = testTree3.find(60);
	ASSERT_EQUAL((++++++it5), it6);

	BinarySearchTree<int> testTree4;
	testTree4.insert(50);
	testTree4.insert(10);
	testTree4.insert(7);
	testTree4.insert(8);
	BinarySearchTree<int>::Iterator it7 = testTree4.find(7);
	BinarySearchTree<int>::Iterator it8 = testTree4.find(8);
	ASSERT_EQUAL((++it7), it8);

	BinarySearchTree<int> testTree5;
	testTree5.insert(50);
	testTree5.insert(60);
	testTree5.insert(70);
	testTree5.insert(65);
	testTree5.insert(55);
	BinarySearchTree<int>::Iterator it9 = testTree4.find(50);
	BinarySearchTree<int>::Iterator it10 = testTree4.find(70);
	ASSERT_EQUAL(++it9, it10);
}

TEST(testInsert)
{
	BinarySearchTree<int> testTree1;
	testTree1.insert(1);
	ASSERT_EQUAL(testTree1.size(), 1);
	
	testTree1.insert(-5);
	testTree1.insert(5);
	testTree1.insert(10);
	ASSERT_TRUE(testTree1.height() == 3);
	ASSERT_TRUE(testTree1.size() ==  4);
	ASSERT_TRUE(testTree1.check_sorting_invariant());



	BinarySearchTree<int> testTree2 = testTree1;
	testTree2.insert(50);
	ASSERT_EQUAL(testTree2.height(), 4);
	ASSERT_TRUE(testTree2.size() == 5);
	ASSERT_TRUE(testTree2.check_sorting_invariant());
}

TEST(testMinElement)
{
	BinarySearchTree<int> testTree1;
	BinarySearchTree<int>::Iterator it1 = testTree1.end();

	ASSERT_EQUAL(testTree1.min_element(), it1);

	for (int i = 1; i < 11; i++)
	{
		testTree1.insert(i);
		testTree1.insert(i * -1);
	}
	BinarySearchTree<int>::Iterator it2 = testTree1.find(-10);
	ASSERT_EQUAL(testTree1.min_element(), it2);

	BinarySearchTree<int> testTree2;
	testTree2.insert(5);
	testTree2.insert(6);
	BinarySearchTree<int>::Iterator it3 = testTree2.find(5);
	ASSERT_EQUAL(testTree2.min_element(), it3);

	BinarySearchTree<int> testTree3;
	testTree3.insert(5);
	testTree3.insert(4);
	testTree3.insert(3);
	testTree3.insert(2);
	BinarySearchTree<int>::Iterator it4 = testTree3.find(2);
	ASSERT_EQUAL(testTree3.min_element(), it4);
}

TEST(testMaxElement)
{
	BinarySearchTree<int> testTree1;
	BinarySearchTree<int>::Iterator it1 = testTree1.end();

	ASSERT_EQUAL(testTree1.max_element(), it1);

	for (int i = 1; i < 11; i++)
	{
		testTree1.insert(i);
		testTree1.insert(i * -1);
	}
	BinarySearchTree<int>::Iterator it2 = testTree1.find(10);
	ASSERT_EQUAL(testTree1.max_element(), it2);

	BinarySearchTree<int> testTree2;
	testTree2.insert(5);
	testTree2.insert(6);
	testTree2.insert(7);
	testTree2.insert(8);
	BinarySearchTree<int>::Iterator it3 = testTree2.find(8);
	ASSERT_EQUAL(testTree2.max_element(), it3);

	BinarySearchTree<int> testTree3;
	testTree3.insert(5);
	testTree3.insert(4);
	testTree3.insert(3);
	testTree3.insert(2);
	BinarySearchTree<int>::Iterator it4 = testTree3.find(5);
	ASSERT_EQUAL(testTree3.max_element(), it4);
}

TEST(testSortingInvariant)
{
	BinarySearchTree<int> testTree1;
	for (int i = 0; i < 5; i++)
	{
		testTree1.insert(i);
	}
	BinarySearchTree<int>::Iterator it = testTree1.find(4);
	*it = -5;
	ASSERT_FALSE(testTree1.check_sorting_invariant());

	BinarySearchTree<int> testTree2;
	for (int i = 1; i < 6; i++)
	{
		testTree2.insert(i);
		testTree2.insert(i * -1);
	}
	BinarySearchTree<int>::Iterator it1 = testTree2.find(1);
	*it1 = 0;
	ASSERT_TRUE(testTree2.check_sorting_invariant());

	BinarySearchTree<int> testTree3;
	ASSERT_TRUE(testTree3.check_sorting_invariant());

	BinarySearchTree<int> testTree4;
	for (int i = 1; i < 6; i++)
	{
		testTree4.insert(i * -1);
	}
	BinarySearchTree<int>::Iterator it3 = testTree4.find(-4);
	*it3 = 4;
	ASSERT_FALSE(testTree4.check_sorting_invariant());

	BinarySearchTree<int> testTree5;
	testTree5.insert(10);
	testTree5.insert(8);
	testTree5.insert(7);
	testTree5.insert(9);
	testTree5.insert(12);
	testTree5.insert(11);
	testTree5.insert(13);

	BinarySearchTree<int>::Iterator it4 = testTree5.find(9);
	*it4 = 6;
	ASSERT_FALSE(testTree5.check_sorting_invariant());
}

TEST(testInorder)
{
	ostringstream test1;
	BinarySearchTree<int> testTree1;
	testTree1.traverse_inorder(test1);
	ASSERT_TRUE(test1.str() == "");

	ostringstream test2;
	BinarySearchTree<int> testTree2;
	for (int i = 0; i < 5; i++)
	{
		testTree2.insert(i);
	}
	testTree2.traverse_inorder(test2);
	ASSERT_TRUE(test2.str() == "0 1 2 3 4 ");

	ostringstream test3;
	BinarySearchTree<int> testTree3;
	for (int i = 1; i <= 3; i++)
	{
		testTree3.insert(i);
		testTree3.insert(i * -1);
	}
	testTree3.insert(0);
	testTree3.traverse_inorder(test3);
	ASSERT_TRUE(test3.str() == "-3 -2 -1 0 1 2 3 ");
}

TEST(testPreorder1)
{
	ostringstream test1;
	BinarySearchTree<int> testTree1;
	testTree1.traverse_preorder(test1);
	ASSERT_TRUE(test1.str() == "");
}
TEST(testPreorder2)
{
	ostringstream test2;
	BinarySearchTree<int> testTree2;
	for (int i = 0; i < 5; i++)
	{
		testTree2.insert(i);
	}
	testTree2.traverse_preorder(test2);
	ASSERT_TRUE(test2.str() == "0 1 2 3 4 ");
}

TEST(testMinGreaterThan)
{
	BinarySearchTree<int> treeTest1;
	BinarySearchTree<int>::Iterator it = treeTest1.end();
	ASSERT_EQUAL(treeTest1.min_greater_than(5), it);

	BinarySearchTree<int> treeTest2;
	treeTest2.insert(10);
	BinarySearchTree<int>::Iterator it2 = treeTest2.find(10);
	ASSERT_EQUAL(treeTest2.min_greater_than(-100), it2);

	BinarySearchTree<int> treeTest3;
	treeTest3.insert(10);
	treeTest3.insert(15);
	treeTest3.insert(5);
	treeTest3.insert(17);
	treeTest3.insert(3);
	treeTest3.insert(7);
	treeTest3.insert(14);
	BinarySearchTree<int>::Iterator it3 = treeTest3.end();
	ASSERT_EQUAL(treeTest3.min_greater_than(100), it3);

	BinarySearchTree<int> treeTest4;
	treeTest4.insert(10);
	treeTest4.insert(15);
	treeTest4.insert(5);
	treeTest4.insert(17);
	treeTest4.insert(3);
	treeTest4.insert(7);
	treeTest4.insert(14);
	BinarySearchTree<int>::Iterator it4 = treeTest4.find(17);
	ASSERT_EQUAL(treeTest4.min_greater_than(15), it4);

	BinarySearchTree<int> treeTest5;
	treeTest5.insert(10);
	treeTest5.insert(15);
	treeTest5.insert(8);
	treeTest5.insert(6);
	treeTest5.insert(5);
	treeTest5.insert(7);
	treeTest5.insert(9);
	BinarySearchTree<int>::Iterator it5 = treeTest5.find(7);
	ASSERT_EQUAL(treeTest5.min_greater_than(6), it5);
}
TEST_MAIN()
