//
// FILE: game.h
//

#include <iostream>
#include <string>
#include <list>
#include <fstream>
#include "cards.h"
#include "players.h"

using namespace std;

namespace deck
{
	class Game
	{
	public:
		// Constructor
		Game(int num, bool bet)
		{
			jack = new Cards(num);
			betting = bet;
			money = 1.00;
		}

		void turns()
		{
			// Variable setup
			int down, user1, user2, comp;
			bool playLoop, compLoop, victory, split, user1Loop, user2Loop, splitLoop;
			string ans;
			user1 = 0;
			user2 = 0;
			comp = 0;
			down = 1;
			split = false;
			user1Loop = true;
			user2Loop = true;
			splitLoop = true;
			playLoop = true;
			compLoop = true;
			victory = false;

			// Player setup
			cout << "-----------------------------------" << endl;
			cout << "Dealer's cards:" << endl;
			Player dealer(*jack);
			dealer.getDealCards();
			cout << "-----------------------------------" << endl;
			cout << "Your cards:" << endl;
			Player user(*jack);
			user.getPlayCards();
			cout << "\nYour total: " << user.getSco() << endl;
			if (dealer.getSco() == 21 || user.getSco() == 21)
				victory = true;

			// Turn Manager
			while (victory != true)
			{
				if (playLoop != false)
				{
					cout << "\nWould you like to 'hit' or 'stand'?" << endl;
					if (user.cardNum() == 2 && betting == true)
						cout << "You may also choose to 'double'." << endl;
					if (user.pair() ==  true && betting == true)
						cout << "You may also choose to 'split'." << endl;
					do
					{
						cin >> ans;
						if (ans == "hit")
						{
							cout << "-----------------------------------" << endl;
							cout << "Your cards:" << endl;
							user.hit(*jack);
							user.getPlayCards();
							cout << "\nYour total: " << user.getSco() << endl;
							if (user.getSco() >= 21)
								victory = true;
							break;
						}
						else if (ans == "stand")
						{
							playLoop = false;
							break;
						}
						else if (ans == "double" && betting == true)
						{
							cout << "-----------------------------------" << endl;
							cout << "Your cards:" << endl;
							user.hit(*jack);
							user.getPlayCards();
							cout << "\nYour total: " << user.getSco() << endl;
							playLoop = false;
							down = 2;
							break;
						}
						else if (ans == "split" && betting == true && user.pair() == true)
						{
							split = true;
							cout << "\nSpliting Hand..." << endl;
							Player hand2(user.split());

							while (victory != true)
							{
								if (user1Loop == true)
								{
									cout << "\nHand 1" << endl;
									user1 = hitStand(user, 1);
									if (user1 == 2)
										victory = true;
									if (user1 == 1)
										user1Loop = false;
								}

								if (user2Loop == true)
								{
									cout << "\nHand 2" << endl;
									user2 = hitStand(hand2, 2);
									if (user2 == 2)
										victory = true;
									if (user2 == 1)
										user2Loop = false;
								}

								if (victory != true && split != true)
								{
									if (compLoop != false)
									{
										comp = deal(dealer);
										if (comp == 2)
											victory = true;
										if (comp == 1)
											compLoop = false;
									}
								}
							}

							vicCon(user, dealer, down);
							vicCon(hand2, dealer, down);
							break;
						}
						else
							cout << "Invaid input. Try again." << endl;
					} while (true);
				}

				if (victory != true && split != true)
				{
					if (compLoop != false)
					{
						comp = deal(dealer);
						if (comp == 2)
							victory = true;
						if (comp == 1)
							compLoop = false;
					}
				}

				if (playLoop == false && compLoop == false)
					victory = true;
			}

			if (split != true)
				vicCon(user, dealer, down);

			user.resetCards();
			dealer.resetCards();
		}

		void saveRecords()
		{
			ofstream outFile;
			outFile.open("C:\\Users\\Joseph\\Desktop\\results.txt"); // Replace with your own file path
			list <string> ::iterator cont;
			list <double> ::iterator mon;
			mon = payout.begin();
			int i;
			i = 1;
			outFile << "Started with $1.00" << endl;
			outFile << "-----------------------------------" << endl;
			for (cont = record.begin(); cont != record.end(); cont++)
			{
				outFile << "Hand " << i << endl;
				outFile << "Result: " << *cont << endl;
				if (betting == true)
				{
					if (*mon >= 0)
						outFile << "Payout: $" << *mon << endl;
					else
						outFile << "Payout: -$" << abs(*mon) << endl;
				}
				outFile << "-----------------------------------" << endl;
				i++;
				mon++;
			}

			if (betting == true)
			{
				if (money >= 0)
					outFile << "Total money: $" << money << endl;
				else
					outFile << "Total money: -$" << abs(money) << endl;
			}
			outFile.close();
		}

		int hitStand(Player &user, int hand)
		{
			string ans;
			bool victory, playLoop;
			victory = false;
			playLoop = true;

			cout << "\nWould you like to 'hit' or 'stand'?" << endl;
			do
			{
				cin >> ans;
				if (ans == "hit")
				{
					cout << "-----------------------------------" << endl;
					cout << "Hand " << hand << "'s cards:" << endl;
					user.hit(*jack);
					user.getPlayCards();
					cout << "\nHand " << hand << "'s total: " << user.getSco() << endl;
					if (user.getSco() >= 21)
						victory = true;
					break;
				}
				else if (ans == "stand")
				{
					playLoop = false;
					break;
				}
			} while (true);

			if (victory == true)
				return 2;
			else if (playLoop == false)
				return 1;
			else
				return 0;
		}

		int deal(Player &dealer)
		{
			bool compLoop, victory;
			compLoop = true;
			victory = false;

			if (dealer.getSco() < 17)
			{
				cout << "-----------------------------------" << endl;
				cout << "Dealer chose to hit." << endl;
				cout << "\nDealer's cards:" << endl;
				dealer.hit(*jack);
				dealer.getDealCards();
				if (dealer.getSco() >= 21)
					victory = true;
			}

			else
			{
				compLoop = false;
				cout << "-----------------------------------" << endl;
				cout << "Dealer chose to stand." << endl;
				cout << "\nDealer's cards:" << endl;
				dealer.getDealCards();
			}

			if (victory == true)
				return 2;
			else if (compLoop == false)
				return 1;
			else
				return 0;
		}

		void vicCon(Player user, Player dealer, int mul)
		{
			cout << "-----------------------------------" << endl;
			if (user.getSco() == dealer.getSco())
			{
				record.push_back("Push");
				payout.push_back(0.00);
			}
			else if (user.getSco() == 21)
			{
				record.push_back("Blackjack");
				payout.push_back(1.50*mul);
			}
			else if (user.getSco() > 21)
			{
				record.push_back("Bust");
				payout.push_back(-1.00*mul);
			}
			else if (user.getSco() > dealer.getSco())
			{
				record.push_back("Win");
				payout.push_back(1.00*mul);
			}
			else if (dealer.getSco() > 21)
			{
				record.push_back("Win");
				payout.push_back(1.00*mul);
			}
			else
			{
				record.push_back("Lose");
				payout.push_back(-1.00*mul);
			}

			cout << record.back() << endl;
			money = money + payout.back();
			if (betting == true)
			{
				if (money >= 0)
					cout << "\nMoney: $" << money << endl;
				else
					cout << "\nMoney: -$" << abs(money) << endl;
			}
			cout << "\nYour Score: " << user.getSco() << endl;
			cout << "Dealer Score: " << dealer.getSco() << endl;
			cout << "-----------------------------------" << endl;
		}

	private:
		int num;
		double money;
		bool betting;
		Cards* jack;
		list <string> record;
		list <double> payout;
	};
}