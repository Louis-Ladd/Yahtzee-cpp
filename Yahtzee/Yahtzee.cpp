#include <algorithm>
#include <iostream>
#include <string>
#include <stdio.h>
#include <time.h>
#include <random>
#include <vector>
#include <cctype>

using namespace std;

string one;
string two;
string three;
string four;
string five;
string six;

void printRoll(vector<int> rollSet)
{
	//get ready to see some terrible code.
	vector<string> dice;
	dice =
	{		"-----"
			"\n|   |"
			"\n| o |"
			"\n|   |"
			"\n-----\n",
			"-----"
			"\n|o  |"
			"\n|   |"
			"\n|  o|"
			"\n-----\n",
			"-----"
			"\n|o  |"
			"\n| o |"
			"\n|  o|"
			"\n-----\n",
			"-----"
			"\n|o o|"
			"\n|   |"
			"\n|o o|"
			"\n-----\n",
			"-----"
			"\n|o o|"
			"\n| o |"
			"\n|o o|"
			"\n-----\n",
			"-----"
			"\n|o o|"
			"\n|o o|"
			"\n|o o|"
			"\n-----\n" };

	for (int i = 0; i <= 4; i++)
	{
		cout << dice[rollSet[i] - 1];
	}

	
}

static random_device rd;//vv and this is for the true random number generation.
static mt19937 generator(rd());
int rollDie()
{
	uniform_int_distribution<int> distribution(1, 6);
	return distribution(generator);
}

int rollSetSum(vector<int> rollSet)
{
	int sum;
	sum = 0;
	for (int i = 0; i <= 4; i++) 
	{
		sum += rollSet[i];
	}

	return sum;
}
vector<int> rollSet()
{
	vector<int> diceSet(5);
	for (int i = 0; i <= 4; i++)
	{
		diceSet[i] = rollDie();
	}
	sort(diceSet.begin(), diceSet.end());
	return diceSet;
}

vector<int> getScoreSet(vector<int> fiveDice) 
{
	vector<int> scoreSet(6, 0);
	for (int i = 0; i <= 4; i++)
	{
		switch (fiveDice[i])
		{
		case 1:
			scoreSet[0] += 1;
			break;
		case 2:
			scoreSet[1] += 1;
			break;
		case 3:
			scoreSet[2] += 1;
			break;
		case 4:
			scoreSet[3] += 1;
			break;
		case 5:
			scoreSet[4] += 1;
			break;
		case 6:
			scoreSet[5] += 1;
			break;


		}
	}
	return scoreSet;
}

/*
RETURN VALUE MEANINGS:
3 Of a Kind = 1
4 Of a Kind = 2
Fullhouse = 3
Small Straight = 4
Large Straight = 5
Yahtzee = 6

*/

int scoreScoreSet(vector<int> scoreSet, int rollSetSum) 
{
	int trueSize;
	trueSize = scoreSet.size() - 1; //accounts for 0 indexing
	//FullHouse
	if (count(scoreSet.begin(), scoreSet.end(), 3) && count(scoreSet.begin(), scoreSet.end(), 2))
	{
		return 25;
	}
	//3 Of a Kind
	for (int i = 0; i <= trueSize; i++) 
	{
		if (scoreSet[i] == 3)
		{
			return rollSetSum;
		}
	}
	//4 Of a Kind
	for (int i = 0; i <= trueSize; i++)
	{
		if (scoreSet[i] == 4)
		{
			return rollSetSum;
		}
	}
	//Small Straight
	if (scoreSet[0] && scoreSet[1] && scoreSet[2] && scoreSet[3] && scoreSet[4] == 1) //lol
	{
		return 30;
	}
	//Large Straight
	if (scoreSet[0] && scoreSet[1] && scoreSet[2] && scoreSet[3] && scoreSet[4] && scoreSet[5] == 1) //lol pt2
	{
		return 40;
	}
	//Yahtzee
	for (int i = 0; i <= trueSize; i++)
	{
		if (scoreSet[i] == 5)
		{
			return 50;
		}
	}
	return 0;
	
}

void printRawRollSet(vector<int> rollSet)
{
	cout << rollSet[0] << ":";
	cout << rollSet[1] << ":";
	cout << rollSet[2] << ":";
	cout << rollSet[3] << ":";
	cout << rollSet[4] << endl;
}

void printScoreSet(vector<int> scoreSet)
{
	cout << scoreSet[0] << ":";
	cout << scoreSet[1] << ":";
	cout << scoreSet[2] << ":";
	cout << scoreSet[3] << ":";
	cout << scoreSet[4] << ":";
	cout << scoreSet[5] << endl;
}

string stringLowerCase(string inString)
{
	transform(inString.begin(), inString.end(), inString.begin(), [](unsigned char c) {return std::tolower(c); });
	return inString;
	
}

bool getUserYN(string prompt)
{
	string userInput;
	while (true)
	{
		cout << prompt;
		cin >> userInput;
		userInput = stringLowerCase(userInput);
		if (userInput == "y")
		{
			return true;
		}
		else if (userInput == "n")
		{
			return false;
		}
	}
}

int getUserNum(string prompt)
{
	string userInput;
	int userInt;
	while (true)
	{
		cout << prompt;
		cin >> userInput;
		userInt = stoi(userInput);
		if (userInt <= 6 && userInt >= 1)
		{
			return userInt;
		}
	}
}


int main()
{
	int rounds;
	int score;
	bool chance;
	chance = false;
	score = 0;
	vector<int> fiveDice(5);
	vector<int> scoreSet(6);
	vector<int> holdSet(5, 0);
	cout << "Welcome to Ladds Yahtzee, Coded in c++. Have fun!!!\n";
	system("PAUSE");
	system("CLS");
	
	for (rounds = 1; rounds <= 13; rounds++)
	{
		cout << "Score: " << score << "  ---Yahtzee---  " << "Round: " << rounds;
		fiveDice = rollSet();
		printRoll(fiveDice);
		system("PAUSE");
		scoreSet = getScoreSet(fiveDice);

		score += scoreScoreSet(scoreSet, rollSetSum(fiveDice));

		if (rounds != 13) 
		{
			score += scoreScoreSet(scoreSet, rollSetSum(fiveDice));
		}
		else if (rounds == 13)
		{
			chance = getUserYN("Would you like to chance your last roll?");
			if (chance == true)
			{
				score += rollSetSum(fiveDice);
			}
		}

		system("CLS");

	}
	
	cout << "Score: " << score << endl;
	system("PAUSE");
}