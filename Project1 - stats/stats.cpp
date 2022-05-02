// stats.cpp
#include "stats.h"
#include "p1_library.h"
#include <cassert>
#include <vector>
#include <cmath>
#include <iostream>
using namespace std;

vector<vector<double>> summarize(vector<double> v)
{
	//Declaring a 2D vector to store the final result
	vector<vector<double>> finalVec;
	double count = 1;
	//sorting the given vector
	sort(v);

	for (size_t i = 1; i < v.size(); i++)
	{
		//If the previous element is equal to the current element, increment the value of the count variable
		if (v[i] == v[i - 1])
		{
			count++;
		}
		else if (v[i] != v[i - 1])
		{
			//If the previous element and the current element are not equal, initialize a vector
			vector<double> tempVec;
			//Push the previous value from the original vector into in, storing the value
			tempVec.push_back(v[i - 1]);
			//Push the back the count value, storing the occurances of the previous value
			tempVec.push_back(count);
			//Push back the entire vector into the 2D vector
			finalVec.push_back(tempVec);
			//Reset count to 1 for the next value in the vector 
			count = 1;
		}
		//Edge test for the final element in the vector, does the same as the previous if statement
		if (i == v.size() - 1)
		{
			//Create a temp 1d vector
			vector<double> temp;
			//Push the current value into the vector
			temp.push_back(v[i]);
			//Push the frequency into the vector
			temp.push_back(count);
			//Finally, push the entire temp vector into the 2D vector
			finalVec.push_back(temp);
		}
	}
	//return the 2D vector with all the previous 1d vectors stored
	return finalVec;
}
int count(vector<double> v) 
{
	//Intialize, set, and return a temp variable to the .size() method from the vector class
	size_t vectorCount = v.size();
	return vectorCount;
}

double sum(vector<double> v) 
{
	//Initalize a double to store the addition of the values
	double sumVal = 0;
	for (size_t i = 0; i < v.size(); i++)
	{
		//Loop through the vector and add each element to sumVal and then return sumVal
		sumVal += v[i];
	}
	return sumVal;
}

double mean(vector<double> v) 
{
	//Initalize a variable to store the average, and then set it to the value of the sum funtion
	double averageVal = sum(v);
	//Return the sum value divided by the size to find the average
	return (averageVal / v.size());
}

double median(vector<double> v) 
{
	//Sort the given vector
	sort(v);
	//Initalize a variable to the size of the vector
	size_t size = v.size();
	
	//If there are an even number of elements, return the average of the middle two elements
	if (v.size() % 2 == 0)
	{
		return (v[size / 2 - 1] + v[size / 2]) / 2.0;
	}
	//If there are an odd number of elements, return the middle element
	else
	{
		return (v[size / 2.0]);
	}
}

double mode(vector<double> v) 
{
	//Sort the given vector
	sort(v);

	//Initalize several variables to use later
	double count = 1, maxVal = 0;
	double mode = v[0];

	for (size_t i = 1; i < v.size(); i++)
	{
		//If the current and next element are equal, increment the value of count
		if (v[i] == v[i - 1])
		{
			count++;
			//If the value of count is greater than maxVal, reset maxVal to count and set mode equal to the current index
			if (count > maxVal)
			{
				maxVal = count;
				mode = v[i];
			}
		}
		//If the two indexes are not equal, set the count to 1
		else
		{
			count = 1;
		}
	}
	//return the variable containing the mode
	return mode; 
}

double min(vector<double> v) 
{
	//Initalize a double to the first index of the vector
	double minVal = v[0];
	for (size_t i = 0; i < v.size(); i++)
	{
		//If the current index is smaller than the current minimum value, set the new minimum value to the current index
		if (v[i] < minVal)
		{
			minVal = v[i];
		}
	}
	//return the variable with the smallest value stored
	return minVal;
}

double max(vector<double> v) 
{
	//Initalize a double to the first index of the vector
	double maxVal = v[0];
	for (size_t i = 0; i < v.size(); i++)
	{
		//If the current index is larger than the current maximum value, set the new maximum value to the current index
		if (v[i] > maxVal)
		{
			maxVal = v[i];
		}
	}
	//return the variable with the largest value stored
	return maxVal;
}

double stdev(vector<double> v) 
{
	double meanVal, standDev = 0;
	//Store the mean value in a variable to be used later
	meanVal = mean(v);

	for (size_t i = 0; i < v.size(); i++)
	{
		//Loop through the entire vector and calculate the standard deviation using the pow function on the difference between the mean and current index
		standDev += pow(v[i] - meanVal, 2);
	}
	//Divide the standard deviation by the size - 1 based on the formula
	standDev = standDev / (v.size() - 1);
	//return the square root of the standDev to caculate the final answer
	return sqrt(standDev);
}

double percentile(vector<double> v, double p)
{
	double percentile, intNum = 0, fractionalNum = 0;
	//Calculate the percetile based on the given formula
	if (p == 100)
	{
		percentile = ((p / 100) * (v.size() - 1)) + 1;
		//Seperate the whole number and decimal value using modf
		fractionalNum = modf(percentile, &intNum);
		//Calculating the final answer using the given formula
		percentile = int(percentile);
		//Same formula as below, just without the Vk+1 for the 100th percentile edge case
		percentile = v[intNum - 1] + (fractionalNum * ((-1)*v[intNum - 1]));
	}
	else
	{
		percentile = ((p / 100) * (v.size() - 1)) + 1;
		//Seperate the whole number and decimal value using modf
		fractionalNum = modf(percentile, &intNum);
		//Calculating the final answer using the given formula
		percentile = int(percentile);
		percentile = v[intNum - 1] + (fractionalNum * (v[intNum] - v[intNum - 1]));
	}

	return percentile;
}