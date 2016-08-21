//
// FILE: blackjack.cpp
//

#include <iostream>
#include <string>
#include "game.h"

using namespace deck;
using namespace std;

int main()
{
	int decks;
	string ans;
	bool repeat, bet;
	repeat = true;
	cout << "***Welcome to Blackjack!***" << endl;
	cout << "\nHow many decks do you want to play with?" << endl;
	do
	{
		cin >> decks;
		if (decks >= 1 && decks <= 4)
			break;
		else
			cout << "Invaid input. Try again." << endl;
	} while (true);

	cout << "\nWould you like to bet? Answer 'yes' or 'no'." << endl;
	do
	{
		cin >> ans;
		if (ans == "yes")
		{
			cout << "\nThe initial bet is $1.00." << endl;
			bet = true;
			break;
		}
		else if (ans == "no")
		{
			bet = false;
			break;
		}
		else
			cout << "Invaid input. Try again." << endl;
	} while (true);

	Game blackjack(decks, bet);
	blackjack.turns();

	do
	{
		ans = "0";
		cout << "\nWould you like to play another hand? Enter 'yes' or 'no'." << endl;
		do
		{
			cin >> ans;
			if (ans == "yes")
				break;
			else if (ans == "no")
			{
				repeat = false;
				break;
			}
			else
				cout << "Invaid input. Try again." << endl;
		} while (true);
		if (repeat == true)
			blackjack.turns();
	} while (repeat == true);

	blackjack.saveRecords();
}