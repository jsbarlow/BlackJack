//
// FILE: cards.h
//

#ifndef CARD_H
#define CARD_H

#include <algorithm>
#include <list>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

namespace deck
{
	class Cards
	{
	public:
		// Constructor
		Cards(int decks)
		{
			// Creates 1-4 decks of cards, according to user input
			int i, j, k;

			// Add cards Ace and 2-10 to the deck
			for (i = 1; i <= decks; i++)
			{
				for (j = 1; j <= 4; j++)
				{
					for (k = 1; k <= 13; k++)
					{
						card.push_back(k);
					}
				}
			}

			// Shuffles cards
			Cards::shuffle_deck();
		}

		// Shuffles cards
		void shuffle_deck()
		{
			int i, shufCount;
			srand(time(NULL));
			shufCount = rand() % 100 + 1;

			for (i = 0; i <= shufCount; i++)
			{
				vector<int> temp(make_move_iterator(card.begin()), make_move_iterator(card.end()));
				card.clear();
				random_shuffle(temp.begin(), temp.end());
				move(temp.begin(), temp.end(), back_inserter(card));
			}
		}

		// Draws card
		int draw()
		{
			if (card.empty())
			{
				return -1;
			}

			int i;
			i = card.front();
			card.pop_front();
			return i;
		}

	private:
		list <int> card;
	};
}
#endif