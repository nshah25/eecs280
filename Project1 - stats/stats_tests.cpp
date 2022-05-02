/* stats_tests.cpp
 *
 * Unit tests for the simple statistics library
 * Project UID 5366c7e2b77742d5b2142097e51561a5
 *
 * EECS 280 Project 1
 *
 * Protip #1: Write tests for the functions BEFORE you implement them!  For
 * example, write tests for median() first, and then write median().  It sounds
 * like a pain, but it helps make sure that you are never under the illusion
 * that your code works when it's actually full of bugs.
 *
 * Protip #2: Instead of putting all your tests in main(),  put each test case
 * in a function!
 */
#include "stats.h"
#include <iostream>
#include <cassert>
#include <vector>
using namespace std;

// Add prototypes for you test functions here.
void testCount();
void testSum();
void testMean();
void testMedian();
void testMode();
void testMin();
void testMax();
void testStandDev();
void testPercentile();
void testSummarize();

int main()
{
	testCount();
	testSum();
	testMean();
	testMedian();
	testMode();
	testMin();
	testMax();
	testStandDev();
	testPercentile();
	testSummarize();
  return 0;
}

void testCount()
{
	vector<double> testData;
	for (size_t i = 0; i < 100; i += 2)
	{
		testData.push_back(i);
	}

	assert(count(testData) == 50);
	cout << "Test passed." << endl;
}

void testSum()
{
	vector<double> testData;
	for (size_t i = 0; i <= 100; i ++)
	{
		testData.push_back(i);
	}

	assert(sum(testData) == 5050);
	cout << "Test passed." << endl;
}

void testMean()
{
	vector<double> testData;
	for (size_t i = 0; i < 10; i++)
	{
		testData.push_back(i);
	}
	assert(mean(testData) == 45.0 / 10.0);
	cout << "Test passed." << endl;
}

void testMedian()
{
	vector<double> testData;
	for (size_t i = 0; i < 10; i++)
	{
		testData.push_back(i);
	}
	assert(median(testData) == 4.5);
	cout << "Test passed." << endl;

	vector<double> testData1;
	for (size_t i = 0; i < 11; i++)
	{
		testData1.push_back(i);
	}
	assert(median(testData1) == 5);
	cout << "Test passed." << endl;

}

void testMode()
{
	vector<double> testData;
	testData.push_back(1);
	testData.push_back(1);
	testData.push_back(2);
	testData.push_back(2);

	assert(mode(testData) == 1);
	cout << "Mode test1 passed." << endl;

	vector<double> testData1;
	for (size_t i = 0; i < 10; i++)
	{
		testData1.push_back(i);
	}
	testData1.push_back(1);

	assert(mode(testData1) == 1);
	cout << "Mode test2 passed." << endl;

	vector<double> testData3;
	for (size_t i = 0; i < 10; i++)
	{
		testData3.push_back(i);
	}
	assert(mode(testData3) == 1);
	cout << "Mode test3 passed." << endl;
}

void testMin()
{
	vector<double> testData;
	for (size_t i = 0; i <= 10; i++)
	{
		testData.push_back(i);
	}

	assert(min(testData) == 0);
	cout << "Test passed." << endl;
}

void testMax()
{
	vector<double> testData;
	for (size_t i = 0; i <=  10; i++)
	{
		testData.push_back(i);
	}

	assert(max(testData) == 10);
	cout << "Test passed." << endl;
}

void testStandDev()
{
	vector<double> testData;
	for (size_t i = 0; i <= 10; i++)
	{
		testData.push_back(1);
	}

	assert(stdev(testData) == 0);
	cout << "Test passed." << endl;
}

void testPercentile()
{
	vector<double> testData;
	testData.push_back(10);
	testData.push_back(20);
	testData.push_back(30);
	testData.push_back(40);
	testData.push_back(50);
	testData.push_back(60);
	testData.push_back(70);
	testData.push_back(80);
	testData.push_back(90);
	testData.push_back(100);

	assert(percentile(testData, 50.0) == 55.0);
	cout << "Test passed." << endl;

}

void testSummarize()
{
	vector<vector<double>> testData1;
	vector<double> testData2;
	for (int i = 0; i < 10; i++)
	{
		testData2.push_back(1);
	}
	testData1.push_back(testData2);

	assert(testData1[0][0] == 1);
	cout << "Test passed." << endl;
}