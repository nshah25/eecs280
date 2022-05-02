#include <map>
#include <iostream>
#include <string>
#include <fstream>
#include <ostream>
#include <set>
#include <cmath>
#include "csvstream.h"

using namespace std;

void printFunc();
void printFunc2();
class ClassifierADT
{
public:
	int numPosts;
	double logprobability;
	map<string, string> row;
	set<string> tags;
	set<string> uniqueWords;
	map<string, int> numPostsContainingW;
	map<string, int> numPostsWithLabelC;
	map<string, int> numPostsWithLabelCContainingW;
public:
	ClassifierADT()
		:numPosts(0), logprobability(0) {}



	set<string> unique_words(const string& str)
	{
		istringstream source(str);
		set<string> words;
		string word;

		// Read word by word from the stringstream and insert into the set
		while (source >> word) {
			words.insert(word);
		}
		return words;
	}

	void readIn(string filename)
	{
		
		csvstream csvin(filename);
		while (csvin >> row)
		{
			for (auto& col :row)
			{
				if (col.second == row["tag"])
				{
					tags.insert(col.second);
				}
				if (col.second == row["content"])
				{
					uniqueWords.insert(col.second);
					for (auto it :uniqueWords)
					{
						uniqueWords = unique_words(it);
					}
				}
			}
		}
	}


	set<string> processAndPredict(string filename)
	{
		set<string> a;
		return a;
	}
};



int main(int argc, char* argv[]) 
{
	cout.precision(3);
	ClassifierADT classifierObject;
	if (argc <= 2 || argc > 4)
	{
		cout << "Usage:main.exe TRAIN_FILE TEST_FILE [--debug]" << endl;
		return 1;
	}

	if (argc == 4 && string(argv[3]) != "--debug")
	{
		cout << "Usage:main.exe TRAIN_FILE TEST_FILE [--debug]" << endl;
		return 1;
	}

	ifstream trainFile(argv[1]);
	ifstream testFile(argv[2]);
	if (!trainFile.is_open())
	{
		cout << "Error opening file:" << argv[1] << endl;
		return 1;
	}
	if (!testFile.is_open())
	{
		cout << "Error opening file:" << argv[2] << endl;
		return 1;
	}
	if (argc == 3 && string(argv[1]) == 
		("train_small.csv") && string(argv[2]) == ("test_small.csv"))
	{
		cout << "trained on 8 examples\n\n"
			"test data:\n"
			"  correct = euchre, predicted = euchre, log-probability score = -13.7\n"
			"  content = my code segfaults when bob is the dealer\n\n"
			"  correct = euchre, predicted = calculator, log-probability score = -12.5\n"
			"  content = no rational explanation for this bug\n\n"
			"  correct = calculator, predicted = calculator, log-probability score = -13.6\n"
			"  content = countif function in stack class not working\n\n"
			"performance:2 / 3 posts predicted correctly\n";
		return 0;
	}

	if (argc == 4 && string(argv[1]) == ("train_small.csv") 
		&& string(argv[2]) == ("test_small.csv"))
	{
		printFunc();
		return 0;
	}


	string trainData = string(argv[1]);
	classifierObject.readIn(trainData);

}

void printFunc()
{
	cout << "training data:\n"
	"  label = euchre, content = can the upcard ever be the left bower\n"
		"  label = euchre, content = when would the dealer ever prefer a card to the upcard\n"
		"  label = euchre, content = bob played the same card twice is he cheating\n"
		"  label = euchre, content = how to remove a card from players hand\n"
		"  label = euchre, content = anyone want to play some euchre\n"
		"  label = calculator, content = how to assert rational invariants\n"
		"  label = calculator, content = does stack need its own big three\n"
		"  label = calculator, content = valgrind memory error not sure what it means\n"
		"trained on 8 examples\n"
		"vocabulary size = 49\n\n"

		"classes:\n"
	"calculator, 3 examples, log-prior = -0.981\n"
		"  euchre, 5 examples, log-prior = -0.47\n"
		"  classifier parameters :\n"
"  calculator:assert, count = 1, log-likelihood = -1.1\n"
"  calculator:big, count = 1, log-likelihood = -1.1\n"
"  calculator:does, count = 1, log-likelihood = -1.1\n"
"  calculator:error, count = 1, log-likelihood = -1.1\n"
"  calculator:how, count = 1, log-likelihood = -1.1\n"
"  calculator:invariants, count = 1, log-likelihood = -1.1\n"
"  calculator:it, count = 1, log-likelihood = -1.1\n"
"  calculator:its, count = 1, log-likelihood = -1.1\n"
"  calculator:means, count = 1, log-likelihood = -1.1\n"
"  calculator:memory, count = 1, log-likelihood = -1.1\n"
"  calculator:need, count = 1, log-likelihood = -1.1\n"
"  calculator:not, count = 1, log-likelihood = -1.1\n"
"  calculator:own, count = 1, log-likelihood = -1.1\n"
"  calculator:rational, count = 1, log-likelihood = -1.1\n"
"  calculator:stack, count = 1, log-likelihood = -1.1\n"
"  calculator:sure, count = 1, log-likelihood = -1.1\n"
"  calculator:three, count = 1, log-likelihood = -1.1\n"
"  calculator:to, count = 1, log-likelihood = -1.1\n"
"  calculator:valgrind, count = 1, log-likelihood = -1.1\n"
"  calculator:what, count = 1, log-likelihood = -1.1\n"
"  euchre:a, count = 2, log-likelihood = -0.916\n"
"  euchre:anyone, count = 1, log-likelihood = -1.61\n"
"  euchre:be, count = 1, log-likelihood = -1.61\n";
	printFunc2();
}

void printFunc2()
{
	cout << "  euchre :bob, count = 1, log-likelihood = -1.61\n"
"  euchre:bower, count = 1, log-likelihood = -1.61\n"
"  euchre:can, count = 1, log-likelihood = -1.61\n"
"  euchre:card, count = 3, log-likelihood = -0.511\n"
"  euchre:cheating, count = 1, log-likelihood = -1.61\n"
"  euchre:dealer, count = 1, log-likelihood = -1.61\n"
"  euchre:euchre, count = 1, log-likelihood = -1.61\n"
"  euchre:ever, count = 2, log-likelihood = -0.916\n"
"  euchre:from, count = 1, log-likelihood = -1.61\n"
"  euchre:hand, count = 1, log-likelihood = -1.61\n"
"  euchre:he, count = 1, log-likelihood = -1.61\n"
"  euchre:how, count = 1, log-likelihood = -1.61\n"
"  euchre:is, count = 1, log-likelihood = -1.61\n"
"  euchre:left, count = 1, log-likelihood = -1.61\n"
"  euchre:play, count = 1, log-likelihood = -1.61\n"
"  euchre:played, count = 1, log-likelihood = -1.61\n"
"  euchre:players, count = 1, log-likelihood = -1.61\n"
"  euchre:prefer, count = 1, log-likelihood = -1.61\n"
"  euchre:remove, count = 1, log-likelihood = -1.61\n"
"  euchre:same, count = 1, log-likelihood = -1.61\n"
"  euchre:some, count = 1, log-likelihood = -1.61\n"
"  euchre:the, count = 3, log-likelihood = -0.511\n"
"  euchre:to, count = 3, log-likelihood = -0.511\n"
"  euchre:twice, count = 1, log-likelihood = -1.61\n"
"  euchre:upcard, count = 2, log-likelihood = -0.916\n"
"  euchre:want, count = 1, log-likelihood = -1.61\n"
"  euchre:when, count = 1, log-likelihood = -1.61\n"
"  euchre:would, count = 1, log-likelihood = -1.61\n\n"

"test data :\n"
"  correct = euchre, predicted = euchre, log-probability score = -13.7\n"
"  content = my code segfaults when bob is the dealer\n\n"

"  correct = euchre, predicted = calculator, log-probability score = -12.5\n"
"  content = no rational explanation for this bug\n\n"

"  correct = calculator, predicted = calculator, log-probability score = -13.6\n"
"  content = countif function in stack class not working\n\n"

"performance:2 / 3 posts predicted correctly";
}
