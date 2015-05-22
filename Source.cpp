//Project	:- BlackJack
//Name		:- Tejas N Varsekar
//SID		:- 108763596 

#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
const int siz = 156;
using namespace std;


string face(string f)
{
	if (f == "11")
	{
		f = 'J';

	}
	else if (f == "12")
	{
		f = 'Q';
	}
	else if (f == "13")
	{
		f = 'K';
	}
	return f;
}
void next(int *suit,string *csuit,int size)
{
	int tempNo;
	string tempCard;
	for (int i = 0; i < size; i++)
	{
		tempNo=suit[0];
		tempCard = csuit[0];
		for (int j = 0; j < 52; j++)
		{
			suit[j] = suit[j + 1];
			csuit[j] = csuit[j + 1];
		}
		suit[51] = tempNo;
		csuit[51] = tempCard;
	}
}
void shuffle(int *suit,string *csuit, int i)
{
	string f;
	int t;
	int temp = suit[i];
	if (suit[i] <= 13)
	{
		t = suit[i] ;
		f = face(to_string(suit[i]));
		csuit[i] = "Diamond " + f;
	}
	else if (suit[i] <= 26)
	{
		t = suit[i]-13;
		f = face(to_string(t));
		csuit[i] = "Heart " + f;
	}
	else if (suit[i] <= 39)
	{
		t = suit[i] - 26;
		f = face(to_string(t));
		csuit[i] = "Spade " + f;
	}
	else if (suit[i] <= 52)
	{
		t = suit[i] - 39;
		f = face(to_string(t));
		csuit[i] = "Club " + f;
	}
	if (t>=10)
	{
		suit[i] = 10;
	}
	else
	{
		suit[i] = t;
	}
}
int count(int cardCounter,int input)
{
	if (input >= 2 && input <= 6)
	{
		cardCounter = cardCounter + 1;
	}
	if (input == 10 || input == 1)
	{
		cardCounter = cardCounter - 1;
	}
	int c = cardCounter / 1;
	return c;
}
void randomizer(int *suit,string *csuit,int siz)
{
	int random_int;
	int lowest = 0, highest = 52;
	int range = (highest - lowest);
	int noOfSuit = 3;
	for (int index = 0; index < siz; ++index)
	{
		int temp = 0;
		random_int = lowest + int(range * rand() / RAND_MAX + 1);
		for (int j = 0; j < index; j++)
		{
			if (suit[j] == random_int)
			{
				noOfSuit--;
				if (noOfSuit == 0)
				{
					random_int = lowest + int(range * rand() / RAND_MAX + 1);
					j = -1;
					noOfSuit = 3;
				}
			}
		}
		suit[index] = random_int;
//		shuffle(suit, csuit, index);
	}
}
int hitOrstay(int dealerCount, int playerCount, int aceCounter, int playerSoftCount)
{
	int decision = 2;
	if (dealerCount == 1)
	{
		dealerCount = 11;
	}
	if (aceCounter == 0)
	{
		if (playerSoftCount<18)
		{
			decision = 2;

		}
		else if (playerSoftCount<19 && dealerCount>8)
		{
			decision = 2;
		}
		else if (playerSoftCount >= 18 && playerSoftCount < 22)
		{
			decision = 3;
		}
	}
	if (dealerCount < 4 && playerCount < 13 && decision != 3)
	{
		decision = 2;
	}
	else if (dealerCount < 7 && playerCount < 12 && decision != 3)
	{
		decision = 2;
	}
	else if (dealerCount > 6 && playerCount < 17 && decision != 3)
	{
		decision = 2;
	}
	else
	{
		decision = 3;
	}
	return decision;
}

int main()
{
	ofstream myfile;
	myfile.open("output.txt");

	int hand = 0;
	int noOfCards = 0;
	int suit[siz];
	string csuit[siz];
	bool pburst = 0;
	bool dburst = 0;
	int bankRoll = 1000;
	srand((unsigned)time(0));
	int cardCounter = 0;

//***************************Code for Shuffleing****************************************************************//
	randomizer(suit,csuit,siz);
	for (int c = 0; c < siz; c++)
	{
		shuffle(suit, csuit, c);
	}
	
	int i = 0;
	int dealerAce, input, size, r, bet, p,a;
	int temp = 4;
	size = 5;
	int win = 0;
	int loose = 0;
	int aceCounter = 1;
	int playerCount = suit[i] + suit[i + 2];
	int dealerCount = 0;
	int playerSoftCount = 0;
	int dealerSoftCount = 0;
	bool blackJack = 0;

	int choose;
	cout << "Press 1 to Play.\nPress 2 to Observe.\nEnter your Choice : ";
	cin >> choose;
	input = 1;
	system("CLS");

	do
	{
		if (choose == 1 )
		{
			cout << "\n--------------------------------------------------------------------------\n";
			cout << "Enter 1 to Deal.\t\tEnter 2 to Hit.\t\tEnter 3 to Stand.";
			cout << "\n##########################################################################\n";
			cout << "\nEnter Your Choice : ";
			cin >> input;
		}
		else
		{

			if (choose ==0)
			{
				input = hitOrstay(dealerCount, playerCount, aceCounter, playerSoftCount);
			}
			//				input = 1;
			choose = 0;
			if (input == 3)
			{
				myfile << "\n* * * STAY * * * \n";
				cout << "\n* * * STAY * * * \n";
			}
			else if (input == 2)
			{
				cout << "\n* * * HIT * * *\n\n";
			}
		}

		switch (input)
		{
			break;
		case 1:
			system("CLS");
			playerCount = 0;
			playerSoftCount = 0;
			if (cardCounter < 0)
			{
				bet = 10;
			}
			else if (cardCounter < 8)
			{
				bet = 20;
			}
			else if (cardCounter < 12)
			{
				bet = 50;
			}
			else
			{
				bet = 100;
			}
			myfile << "\nCurrent BankRoll is : " << bankRoll;
			myfile << "\nCurrent Table Count is : " << cardCounter;
			myfile << "\n##########################################################################\n";
			myfile << "\nCurrent Bet is : " << bet;
			myfile << "\nPlayers Cards : \n" << csuit[i] << "\n" << csuit[i + 2] << endl;
			myfile << "\nDealers Cards : \n" << csuit[i + 1] << endl;


			cout<< "\nCurrent BankRoll is : " << bankRoll;
			cout << "\nCurrent Table Count is : " << cardCounter;
			cout << "\n--------------------------------------------------------------------------\n";
			cout << "Enter 1 to Deal.\t\tEnter 2 to Hit.\t\tEnter 3 to Stand.";
			cout << "\n##########################################################################\n";
			cout << "\nCurrent Bet is : " << bet;
			cout << "\nPlayers Cards : \n" << csuit[i] << "\n" << csuit[i + 2] << endl;
			cout << "\nDealers Cards : \n" << csuit[i + 1] << endl;

			playerCount = suit[i] + suit[i + 2];
			dealerCount = suit[i + 1];
			cardCounter = count(cardCounter, suit[i]);
			cardCounter = count(cardCounter, suit[i+1]);
			noOfCards = noOfCards + 2;
			if (suit[i] == 1)
			{
				aceCounter = 0;
				playerSoftCount = suit[i + 2] + 11;
				if (csuit[i + 2].at(csuit[i + 2].size() - 1) == 'J')
				{
					blackJack = 1;
					myfile << "This is Black Jack\n";
					cout << "This is Black Jack\n";
				}
			}
			if (suit[i+2] == 1)
			{
				aceCounter = 0;
				playerSoftCount = suit[i] + 11;
			}
			r= 1;
			cardCounter = count(cardCounter, suit[i + 2]);
			myfile << "\nPlayer Count is " << playerCount << endl;
			cout << "\nPlayer Count is " << playerCount << endl;
			if (playerSoftCount>0)
			{
				myfile << "\nPlayer Softhand Hand : " << playerSoftCount << endl << endl;
				cout << "\nPlayer Softhand Hand : " << playerSoftCount << endl << endl;
			}

			break;

		case 2:
			playerCount = 0;
			playerSoftCount = 0;
			aceCounter = 0;
			for (int j = 0; j < size; j++)
			{
				if (j!=1 && j!=3 )
				{
					noOfCards++;
//********************************SHUFFel AGAIN***************************************//
					if (noOfCards % siz == 0)
					{
						cardCounter = 0;
						cardCounter = count(cardCounter, suit[j]);
					}
					myfile << csuit[j] << "\n";
					cout << csuit[j] << "\n";
					if (j == temp)
					{
						cardCounter = count(cardCounter, suit[j]);
					}
					playerCount = playerCount + suit[j];
					playerSoftCount = playerSoftCount + suit[j];
				}
 				if (suit[j] == 1 && playerSoftCount<21 && aceCounter == 0)
				{
					playerSoftCount = playerSoftCount + 10;
					aceCounter = 1;
					a = 0;
				}
				if (playerCount >21)
				{
					pburst = 1;
					break;
				}
			}
			temp = size;
			size++;
			myfile << "\nPlayer Hand : " << playerCount << "\t";
			cout << "\nPlayer Hand : " << playerCount << "\t";
			if (playerSoftCount>0 && playerSoftCount <= 21)
			{
				myfile << "\nPlayer Softhand Hand : " << playerSoftCount;
				cout << "\nPlayer Softhand Hand : " << playerSoftCount;
			}
			if (choose != 1)
			{
				input = hitOrstay(dealerCount, playerCount, aceCounter, playerSoftCount);
			}
			/*
			if (dealerCount < 4 && playerCount < 13)
			{
				myfile  << "\n**HIT**\n";
			}
			else if (dealerCount < 7 && playerCount < 12)
			{
				myfile  << "\n**HIT**\n";
			}
			else if (playerCount < 17)
			{
				myfile  << "\n**HIT**\n";
			}
			else if (aceCounter == 0)
			{
				if (playerSoftCount < 18)
				{
					myfile  << "\n**HIT**\n";
				}
				else if (playerSoftCount < 19 && dealerCount>8)
				{
					myfile  << "\n**HIT**\n";
				}
			}
			else
			{
				myfile  << "\n**stay**\n";
			}
	*/
			myfile  << endl ;
			cout << endl;
			break;
		case 3:
			dealerAce = 0;
			dealerCount = 0;
			myfile << "\nDealers Cards : \n" << csuit[i + 1] << "\n" << csuit[i + 3] << endl;
			cout << "\nDealers Cards : \n" << csuit[i + 1] << "\n" << csuit[i + 3] << endl;
			cardCounter = count(cardCounter, suit[i + 3]);
			if (playerSoftCount<=21 && playerSoftCount > playerCount)
			{
				playerCount = playerSoftCount;
			}
			if (pburst != 1)
			{
				dealerCount = suit[i + 1] + suit[i + 3];
				if (suit[i+1]== 1 || suit[i+3] == 1)
				{
					dealerSoftCount = dealerCount + 10;
					a = dealerAce;
					dealerAce = 1;
				}
				if (dealerSoftCount > playerCount && dealerSoftCount > 16 && dealerSoftCount <= 21)
				{
					dealerCount = dealerSoftCount;
				}

				for (int i = size - 1; dealerCount <17; i++)
				{
					myfile << csuit[i] << endl;
					cout << csuit[i] << endl;
					noOfCards++;
//********************************SHUFFel AGAIN***************************************//
					if (noOfCards % siz == 0)
					{
						cardCounter = 0;
//						cardCounter = count(cardCounter, suit[i]);
					}
					if (suit[i] == 1 && dealerAce == 0)
					{
						dealerSoftCount = dealerCount + 10;
					}
					dealerSoftCount = dealerSoftCount + suit[i];
					dealerCount = dealerCount + suit[i];
					cardCounter = count(cardCounter, suit[i]);
					if (dealerSoftCount <= 21 && dealerSoftCount > dealerCount && dealerSoftCount > 16)
					{
						dealerCount = dealerSoftCount;
					}
					if (playerCount < dealerCount && dealerCount < 21)
					{
						dburst = 0;
						break;
					}
				}
				if (dealerCount > 21)
				{
					dburst = 1;
				}
				myfile << "\nPlayer Hand : " << playerCount << "\tVS.\t";
				cout << "\nPlayer Hand : " << playerCount << "\tVS.\t";

				myfile << "Dealer Hand : " << dealerCount << endl;
				cout << "Dealer Hand : " << dealerCount << endl;
				
				if (dburst == 1)
				{
					win++;
					bankRoll = bankRoll + bet;
					myfile << "\nDealer is Busted Player Won.";
					cout << "\nDealer is Busted Player Won.";
				}
				else if (playerCount == dealerCount)
				{
					myfile << "\nDraw/Push.";
					cout << "\nDraw/Push.";
				}
				else if (playerCount<dealerCount)
				{
					loose++;
					bankRoll = bankRoll - bet;
					myfile << "\nDealer Win.";
					cout << "\nDealer Win.";
				}
				else
				{
					win++;
					bankRoll = bankRoll + bet;
					myfile << "\nPlayer Win.";
					cout << "\nPlayer Win.";
				}
			}
			else
			{
				loose++;
				bankRoll = bankRoll - bet;
				myfile << "\nPlayer Busted Dealer Won.";
				cout << "\nPlayer Busted Dealer Won.";
			}
			next(suit, csuit, size);
			pburst = 0;
			dburst = 0;
			dealerSoftCount = 0;
			dealerCount = 0;
			size = 5;
			temp = 4;
			myfile << "\nTable Counter at END of Game : " << count(cardCounter, 0) << endl;
			myfile << "\nWin : " << win;
			myfile << "\nloose : " << loose;
			myfile << "\nBank Status " << bankRoll;

			cout << "\nTable Counter at END of Game : " << count(cardCounter, 0) << endl;
			cout << "\nWin : " << win;
			cout << "\nloose : " << loose;
			cout << "\nBank Status " << bankRoll;

			myfile << "\n--------------------------------------------------------------------------\n\n";
			cout << "\n--------------------------------------------------------------------------\n\n";

			if (choose == 0)
			{
				if (hand <500)
				{
					input = 1;
					hand++;
					choose = 3;
				}
				else
				{
					input = 5;
				}
			}
			else
			{
				myfile << "Seed Money : 1000\n";
				myfile << "Current Bank Roll Is : " << bankRoll << endl;
				cout << "Seed Money : 1000\n";
				cout << "Current Bank Roll Is : " << bankRoll << endl;
			}
			break;
		case 4:
			break;
		case 5:
			exit(EXIT_FAILURE);
		default:
			break;
		}
	} while (input<5);
}
