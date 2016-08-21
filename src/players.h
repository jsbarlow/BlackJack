//
// FILE: players.h
//

#include <iostream>
#include "cards.h"

using namespace std;

namespace deck
{
	class Player
	{
	public:
		// Constructor
		Player(Cards& jack)
		{
			score = 0;
			Player::hit(jack);
			Player::hit(jack);
		}

		Player(int j)
		{
			score = 0;
			if (j == 1)
			{
				if (score >= 11)
					score = score + j;
				else
					score = score + 11;
				cards.push_back("Ace");
			}
			else if (j == 11)
			{
				score = score + 10;
				cards.push_back("Jack");
			}
			else if (j == 12)
			{
				score = score + 10;
				cards.push_back("Queen");
			}
			else if (j == 13)
			{
				score = score + 10;
				cards.push_back("King");
			}
			else
			{
				score = score + j;
				cards.push_back(to_string(j));
			}
		}

		// Controls the player "hit" move
		void hit(Cards& jack)
		{
			int j, num;
			num = 0;
			j = jack.draw();

			if (j == -1)
			{
				cout << "Out of cards. Choose to stand and not play a new hand to end game." << endl;
				score = +0;
			}
			if (j == 1)
			{
				if (score >= 11)
					score = score + j;
				else
					score = score + 11;
				cards.push_back("Ace");
			}
			else if (j == 11)
			{
				score = score + 10;
				cards.push_back("Jack");
			}
			else if (j == 12)
			{
				score = score + 10;
				cards.push_back("Queen");
			}
			else if (j == 13)
			{
				score = score + 10;
				cards.push_back("King");
			}
			else
			{
				score = score + j;
				cards.push_back(to_string(j));
			}
		}

		int getSco()
		{
			return score;
		}

		void setSco(int sco)
		{
			score = sco;
		}

		void getPlayCards()
		{
			for (count = cards.begin(); count != cards.end(); count++)
				cout << *count << endl;
		}

		void getDealCards()
		{
			list <string> ::iterator first;
			first = cards.begin();
			++first;
			for (count = first; count != cards.end(); count++)
				cout << *count << endl;
			cout << "One card is hidden." << endl;
		}

		void resetCards()
		{
			while (!cards.empty())
			{
				cards.pop_front();
			}
		}

		int cardNum()
		{
			return cards.size();
		}

		bool pair()
		{
			if (cards.front() == cards.back())
				return true;
			else
				return false;
		}

		int split()
		{
			cards.pop_back();
			return score/2;
		}

	private:
		int score;
		list <string> cards;
		list <string> :: iterator count;
	};
}