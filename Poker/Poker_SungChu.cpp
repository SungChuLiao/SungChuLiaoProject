//Sung Chu Liao

#include <iostream>
#include <string>
#include <time.h>
#define _CRTDBG_MAP_ALLOC
#define _CRTDBG_MAP_ALLOC_NEW
#include <cstdlib>
#include <crtdbg.h>
#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW
#endif
#endif


using namespace std;


///////Input
string m_inputButton;

/////////////////////PlayerInfo
int m_money = 10;
int* myMoney;

bool m_gameStart = false;
bool m_matchstart = false;
bool m_changeCard = false;
bool m_MatchEnd = false;

string m_shape = "";
string m_value = "";


//Add card to the intList for checking the poker hand

struct arrayIntlist
{
	int* array;
	int capacity; // 14capacity
	int count; // which slot
};
arrayIntlist* create_array_list()
{
	const int INIT_CAP = 14;
	arrayIntlist* Intlist = new arrayIntlist;
	Intlist->array = new int[INIT_CAP];
	Intlist->capacity = INIT_CAP;
	Intlist->count = 0;
	return Intlist;
}
void AddInt(arrayIntlist* Intlist, int index)
{
	// Need to increase capacity?
	if (index - 1 < Intlist->capacity)
	{
		Intlist->array[index - 1] += 1;
	}
}
int GetInt(arrayIntlist* Intlist, int index)
{
	if (index < 0 || index >= Intlist->capacity)
	{
		cout << "ErrorI!" << endl;
		return -1; // Out of bounds.
	}

	return Intlist->array[index];
}
void printIntList(arrayIntlist* Intlist)
{
	for (int i = 0; i < Intlist->capacity; i++)
	{
		cout << i + 1 << " :" << Intlist->array[i] << " , " ;
	}
	cout << " \n\n /////////////////////////\n\n "<< endl;
}
void deleteIntList(arrayIntlist* Intlist)
{
	delete[] Intlist->array;
	delete Intlist;
}

//For Player

////////////////////////// PlayerCardList
struct Card
{
	string Shape;
	string value;
	bool Keep = false;
};
struct PlayerCardList
{
	Card* array;
	int count;
	int capacity;
};
////////////Create PlayerCardList
PlayerCardList* CreatePlayerCardList()
{
	const int INIT_CAP = 5;
	PlayerCardList* list = new PlayerCardList;
	list->array = new Card[INIT_CAP];
	list->capacity = INIT_CAP;
	list->count = 0;
	return list;
}
//////////Add
void addCard(PlayerCardList* list, string Shape, string value)
{
	if (list->count < list->capacity)
	{
		Card card;
		card.Shape = Shape;
		card.value = value;
		/*if (list->array == nullptr)
		{
			list->array = new Card;
		}*/
		list->array[list->count] = card;
		list->count++;
	}
}
//////////Print
void printHand(PlayerCardList* list)
{
	cout << endl;

	for (int i = 0; i < list->count; i++)
	{
		if (list->array[i].Keep != true)
		{
			cout << i + 1 << " :" << list->array[i].Shape << " of " << list->array[i].value << endl;
		}
		else
		{
			cout << i + 1 << " :" << list->array[i].Shape << " of " << list->array[i].value << " (kept) " << endl;
		}
	}
	cout << endl;
}
////////Get
string GetHandShape(PlayerCardList* list, int index)
{
	if (index < 0 || index >= list->count)
	{
		cout << "ErrorS!" << endl;
		return "Error"; // Out of bounds.
	}

	return list->array[index].Shape;
}
string GetHandValue(PlayerCardList* list, int index)
{
	if (index < 0 || index >= list->count)
	{
		cout << "ErrorV!" << endl;
		return "Error"; // Out of bounds.
	}

	return list->array[index].value;
}
/////////Remove
void removeCard(PlayerCardList* list, int index)
{
	if (index < 0 || index >= list->count)
	{
		cout << "ErrorE!" << endl;
		return; // Out of bounds.
	}

	// Shift items after 'index' by 1.
	for (int i = index; i < list->count - 1; ++i)
	{
		list->array[i] = list->array[i + 1];
	}
	list->count--;
}

/////////Delete
void DeletePlayerCardList(PlayerCardList* list)
{
	delete[] list->array;
	delete list;
}

//For Deck
////////////////////////////////////////////////////////////////

struct MyDeck
{
	string Shape;
	string value;
	MyDeck* next;
};
struct newDeck
{
	MyDeck* head;
};
newDeck* CreateMyDeck()
{
	newDeck* list = new newDeck;
	list->head = nullptr;

	return list;
}
void AddFirst (newDeck* list, string Shape, string value)
{
	MyDeck* n = new MyDeck;
	n->Shape = Shape;
	n->value = value;
	n->next = list->head;
	list->head = n;
}
void AddLast(newDeck* list, string Shape, string value)
{
	if (list->head == nullptr)
	{
		AddFirst(list, Shape, value);
		return;
	}

	MyDeck* temp = list->head;
	while (temp->next != nullptr)
		temp = temp->next;

	MyDeck* n = new MyDeck;
	n->Shape = Shape;
	n->value = value;
	n->next = nullptr;
	temp->next = n;
}
void printDeck(newDeck* list)
{
	MyDeck* n = list->head;
	while (n != nullptr)
	{
		cout << n->value << " of " << n->Shape << ",";
		n = n->next;
	}
}
int CountDeckCard(newDeck* list)
{
	int count = 0;
	MyDeck* n = list->head;
	while (n != NULL)
	{
		++count;
		n = n->next;
	}
	return count;
}
string GetDeckShape(newDeck* list, int index)
{
	MyDeck* n = list->head;
	while (index > 0)
	{
		n = n->next;
		--index;
	}
	return n->Shape;
}
string GetDeckValue(newDeck* list, int index)
{
	MyDeck* n = list->head;
	while (index > 0)
	{
		n = n->next;
		--index;
	}
	return n->value;
}
void RemoveDeckFromFirst(newDeck* list)
{
	if (list->head == nullptr)
	{
		cout << "Error!" << endl;
		return;
	}

	MyDeck* n = list->head;
	list->head = n->next;
	delete n;
}
void RemoveDeckByIndex(newDeck* list, int index)
{
	if (index == 0)
	{
		RemoveDeckFromFirst(list);
		return;
	}

	MyDeck* temp = list->head;
	while (index > 1)
	{
		temp = temp->next;
		--index;
	}

	MyDeck* n = temp->next;
	temp->next = n->next;
	delete n;
}
void DeleteDeck(newDeck* list)
{
	MyDeck* n = list->head;
	while (n != nullptr)
	{
		MyDeck* temp = n;
		n = n->next;
		delete temp;
	}

	delete list;
}
void DeckCreateChecker(newDeck* deck, string suit ,int j)
{
	if (j == 1)
		AddFirst(deck, suit, "A");
	else if (j == 11)
		AddFirst(deck, suit, "J");
	else if (j == 12)
		AddFirst(deck, suit, "Q");
	else if (j == 13)
		AddFirst(deck, suit, "K");
	else if (j == 2)
		AddFirst(deck, suit, "2");
	else if (j == 3)
		AddFirst(deck, suit, "3");
	else if (j == 4)
		AddFirst(deck, suit, "4");
	else if (j == 5)
		AddFirst(deck, suit, "5");
	else if (j == 6)
		AddFirst(deck, suit, "6");
	else if (j == 7)
		AddFirst(deck, suit, "7");
	else if (j == 8)
		AddFirst(deck, suit, "8");
	else if (j == 9)
		AddFirst(deck, suit, "9");
	else if (j == 10)
		AddFirst(deck, suit, "10");
}

//////////////Find index
int find_index(string s, bool(*criteria)(char))
{
	for (int i = 0; i < s.length(); ++i)
	{
		char c = s[i];
		if (criteria(c))
		{
			return i;
		}
	}
	return -1;
}
void CheckCard(PlayerCardList* list, newDeck* deck, string s, bool(*criteria)(char))
{
	for (int i = 0; i < list->count; ++i)
	{
		list->array[i].Keep = false;
	}
	for (int i = 0; i < s.length(); ++i)
	{
		char c = s[i];
		if (criteria(c))
		{
			list->array[(int)c - '1'].Keep = true;
		}
	}
	for (int i = list->count - 1; i >= 0; --i)
	{
		if (list->array[i].Keep == false)
		{
			removeCard(list, i);
			if (CountDeckCard(deck) <= 0)
			{
				for (int g = 0; g <= 3; g++)
				{
					for (int j = 1; j < 14; j++)
					{
						string suit = "";
						switch (g)
						{
						case 0:
							suit = "Club";
							DeckCreateChecker(deck, suit, j);
							break;
						case 1:
							suit = "Diamond";
							DeckCreateChecker(deck, suit, j);
							break;
						case 2:
							suit = "Heart";
							DeckCreateChecker(deck, suit, j);
							break;
						case 3:
							suit = "Spades";
							DeckCreateChecker(deck, suit, j);
							break;
						default:
							cout << "Deck Error" << endl;
							break;
						}
					}
				}

				//to define which card play have
				for (int t = 0; t < list->count; t++)
				{
					for (int j = 0; j < CountDeckCard(deck); j++)
					{

						string DeckShape = GetDeckShape(deck, j);
						string DeckValue = GetDeckValue(deck, j);
						string PlayerShape = GetHandShape(list, t);
						string PlayerValue = GetHandValue(list, t);
						if (PlayerShape == DeckShape && PlayerValue == DeckValue)
						{
							RemoveDeckByIndex(deck, j);
						}
					}
				}
			}
			int randomNum = rand() % CountDeckCard(deck);
			addCard(list, GetDeckShape(deck, randomNum), GetDeckValue(deck, randomNum));
			RemoveDeckByIndex(deck, randomNum);
		}
	}
}
bool is_vowel(char c)
{
	return c == '1' || c == '2' ||
		   c == '3' || c == '4' ||
		   c == '5';
}
/////////////////GetScore
void GetScore(int extraScore, bool winMoney) // Might need Pointer
{
	if(winMoney)
	{
		cout << "Congratulation! You Win the Match" << endl;
		cout << "You earned: " << extraScore << " $ " << endl;
		m_money += extraScore;
		cout << "You now have : " << m_money << " $ " << endl;
	}
	if (!winMoney)
	{
		cout << "No Poker hand scored :(" << endl;
		cout << "You earned: " << extraScore << " $ " << endl;
		cout << "You now have : " << m_money << " $ " << endl;
	}
	system("pause");
}
////////////////For Swap
void Swap(PlayerCardList* cardlist, newDeck* swapDeck, int choice, string chooseShape, string chooseValue)
{
	//Card temp = list->array[choice];

	for (int d = 0; d < CountDeckCard(swapDeck); d++)
	{
		//If deck no card, can't change
		if (chooseShape == GetDeckShape(swapDeck, d) && chooseValue == GetDeckValue(swapDeck, d))
		{
			//change deck
			RemoveDeckByIndex(swapDeck, d);
			AddFirst(swapDeck, GetHandShape(cardlist, choice - 1), GetHandValue(cardlist, choice- 1));
			//Change hand
			removeCard(cardlist, choice -1);
			addCard(cardlist, chooseShape, chooseValue);
		}
	}
}
////////////////////////////////////////////			Main			//////////////////////////////////////////////////////
int main()
{
	///Check memory Leak
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF |
		_CRTDBG_LEAK_CHECK_DF);

	if (!m_gameStart)
	{
		srand(time(NULL));
		m_money = 10;
		//myMoney = &m_money;
		m_matchstart = true;
		m_gameStart = true;;
		////Create Deck
	}

	if (m_gameStart)
	{
		newDeck* deck = CreateMyDeck();
		for (int i = 0; i <= 3; i++)
		{
			for (int j = 1; j < 14; j++)
			{
				string suit = "";
				switch (i)
				{
				case 0:
					suit = "Club";
					DeckCreateChecker(deck, suit, j);
					break;
				case 1:
					suit = "Diamond";
					DeckCreateChecker(deck, suit, j);
					break;
				case 2:
					suit = "Heart";
					DeckCreateChecker(deck, suit, j);
					break;
				case 3:
					suit = "Spades";
					DeckCreateChecker(deck, suit, j);
					break;
				default:
					cout << "Deck Error" << endl;
					break;
				}
			}
		}
		while (m_matchstart)
		{
			system("cls");
			//Create PlayerCartList
			PlayerCardList* list = CreatePlayerCardList();

			//print player money
			cout << "Welcome to my Poker Game \n" << endl;
			cout << "Player Money: " << m_money << " $" << endl;
			m_money -= 1;
			cout << "You pay a 1 $ and now you have " << m_money << " $ \n" << endl;

			//Add 5 Card From Deck To playerCard

			for (int i = 0; i < 5; i++)
			{
				if (CountDeckCard(deck) <= 0)
				{
					for (int g = 0; g <= 3; g++)
					{
						for (int j = 1; j < 14; j++)
						{
							string suit = "";
							switch (g)
							{
							case 0:
								suit = "Club";
								DeckCreateChecker(deck, suit, j);
								break;
							case 1:
								suit = "Diamond";
								DeckCreateChecker(deck, suit, j);
								break;
							case 2:
								suit = "Heart";
								DeckCreateChecker(deck, suit, j);
								break;
							case 3:
								suit = "Spades";
								DeckCreateChecker(deck, suit, j);
								break;
							default:
								cout << "Deck Error" << endl;
								break;
							}
						}
					}

					//to define which card play have
					for (int t = 0; t < list->count; t++)
					{
						for (int j = 0; j < CountDeckCard(deck); j++)
						{
							string DeckShape = GetDeckShape(deck, j);
							string DeckValue = GetDeckValue(deck, j);
							string PlayerShape = GetHandShape(list, t);
							string PlayerValue = GetHandValue(list, t);
							if (PlayerShape == DeckShape && PlayerValue == DeckValue)
							{
								RemoveDeckByIndex(deck, j);
							}
						}
					}
				}
				if (CountDeckCard(deck) > 0)
				{
					int randomNum = rand() % CountDeckCard(deck);
					addCard(list, GetDeckShape(deck, randomNum), GetDeckValue(deck, randomNum));
					RemoveDeckByIndex(deck, randomNum);
				}

			}
		start:
			//print Hand
			cout << "Your hand contains: " << endl;
			printHand(list);

			cout << "" << endl;
			cout << "Deck have " << CountDeckCard(deck) << " cards! \n" << endl;

			cout << "Type the Numbers for the card you wish to keep (1,2,3,4,5)" << endl;
			cout << "Type 'none' or nonInteger to drop all card" << endl;
			cout << "Type 'all' to keep all cards" << endl;
			cout << "Type 'view' to view your card remaining in the deck" << endl;
			cout << "Type 'swap' to Cheat and swap a card in your hand" << endl;
			cout << "Type 'exit' to exit the game" << endl;
			cout << "Your Choice: ";
			
			cin >> m_inputButton;

			string mystring = m_inputButton;
			if (mystring == "swap" || mystring == "view" || mystring == "none" || mystring == "all")
			{
				if (mystring == "view")
				{
					system("cls");
					cout << "My Deck List: \n" << endl;
					printDeck(deck);
					cout << "\n" << endl;
					cout << "Deck have " << CountDeckCard(deck) << " cards! \n" << endl;
					cin.clear();
					cin.ignore(1000, '\n');
					goto start;
				}
				if (mystring == "swap")
				{
					int choice = 0;
					string chooseShape = "";
					string chooseValue = "";
					cout << "Please type the index you want to switch [just one card]" << endl;
					cout << "Your Choice: ";
					cin >> m_inputButton;
					if (cin.good() && stoi(m_inputButton) >= 1 && stoi(m_inputButton) <= 5)
					{
						choice = atoi(m_inputButton.c_str());
						cin.clear();
						cin.ignore(1000, '\n');
						cout << "Please type the suit you want to switch to (Club,Heart,Diamond,Spades)" << endl;
						cout << "Your Choice: ";
						cin >> m_inputButton;
						if (m_inputButton == "Club" || m_inputButton == "Heart" || m_inputButton == "Diamond" || m_inputButton == "Spades")
						{
							chooseShape = m_inputButton;
							cin.clear();
							cin.ignore(1000, '\n');
							cout << "Please type the value you want to switch to (A,2,3,4,5,6,7,8,9,10,J,Q,K)" << endl;
							cout << "Your Choice: ";
							cin >> m_inputButton;
							if (m_inputButton == "2" || m_inputButton == "3" || m_inputButton == "4" || m_inputButton == "5" ||
								m_inputButton == "6" || m_inputButton == "7" || m_inputButton == "8" || m_inputButton == "9" ||
								m_inputButton == "10"|| m_inputButton == "A" || m_inputButton == "J" || m_inputButton == "Q" || m_inputButton == "K")
							{
								chooseValue = m_inputButton;
								cin.clear();
								cin.ignore(1000, '\n');
								Swap(list, deck, choice, chooseShape, chooseValue);
							}
						}
					}
					system("cls");
					cout << "Cheater!" << endl;
					goto start;
				}
				if (mystring == "none")
				{
					//Do nothing
				}
				if (mystring == "all")
				{
					CheckCard(list, deck, "12345", is_vowel);
				}
			}
			else if (mystring == "exit")
			{
				exit(0);
			}
			else if (cin.good())
			{
				cin.clear();
				cin.ignore(1000, '\n');
				/*
				char myChar [16];
				strncpy(myChar, mystring.c_str(), sizeof(myChar));
				myChar[sizeof(myChar) - 1] = 0;
				cout << mystring.length() << " Char " << myChar << endl;
				system("pause");*/
				CheckCard(list, deck, mystring, is_vowel);
				/*for (int i = 0; i < mystring.length(); i++)
				{
					if (myChar[i] == '1' || '2' || '3' || '4' || '5')
					{
						int myint = (int)myChar[i];
						cout << "Myint: " <<  myint - 48 << endl;
						system("pause");
						removeCard(list, myint - 49);
						int randomNum = rand() % CountDeckCard(deck);
						printHand(list);
					}
					int randomNum = rand() % CountDeckCard(deck);
					for (int i = 0; i < mystring.length(); i++)
					{
						addCard(list, GetDeckShape(deck, randomNum), GetDeckValue(deck, randomNum));
					}
				}*/
			}
			else
			{
				//Do nothing
			}
			//print hand
			cout << "You Hand now contain: \n" << endl;
			// might add how many card player keep?
			printHand(list);
			for (int i = 0; i < list->count; ++i)
			{
				list->array[i].Keep = false;
			}

			//add hands card to new intlist
			arrayIntlist* IntList = create_array_list();
			for (int i = 0; i < 14; i++)
			{
				IntList->array[i] = 0;
			}
			for (int i = 0; i < list->count; i++)
			{
				if (GetHandValue(list, i) == "A")
				{
					AddInt(IntList, 1);
					AddInt(IntList, 14);
				}
				else if (GetHandValue(list, i) == "K")
					AddInt(IntList, 13);
				else if (GetHandValue(list, i) == "Q")
					AddInt(IntList, 12);
				else if (GetHandValue(list, i) == "J")
					AddInt(IntList, 11);
				else if (GetHandValue(list, i) == "2")
					AddInt(IntList, 2);
				else if (GetHandValue(list, i) == "3")
					AddInt(IntList, 3);
				else if (GetHandValue(list, i) == "4")
					AddInt(IntList, 4);
				else if (GetHandValue(list, i) == "5")
					AddInt(IntList, 5);
				else if (GetHandValue(list, i) == "6")
					AddInt(IntList, 6);
				else if (GetHandValue(list, i) == "7")
					AddInt(IntList, 7);
				else if (GetHandValue(list, i) == "8")
					AddInt(IntList, 8);
				else if (GetHandValue(list, i) == "9")
					AddInt(IntList, 9);
				else if (GetHandValue(list, i) == "10")
					AddInt(IntList, 10);
			}

			//Detect
			bool isStraight = false;
			bool isRoyal = false;
			bool isFlush = false;
			bool isFourKind = false; //1
			bool isFullHouse = false;
			bool isThreeKind = false; //2
			bool isTwopair = false; //3
			bool isOnePair = false; // 4

			//int MultiCount = 0; // if count have 3; if 2 = full house, if 3 = isThreeKind (used to detect 2 pair and full house)

			int flushCount = 0;
			//Check Royal // Work
			for (int i = 10; i < 14; i++)
			{
				int StraightCount = 0;
				if (GetInt(IntList, i) == 1)
				{
					for (int h = 0; h < 5; h++)
					{
						if (i + h < 14 && i + h >= 0)
						{
							if (GetInt(IntList, i + h) == 1)
							{
								StraightCount += 1;
							}
							else
							{
								break;
							}
						}
						else
						{
							break;
						}
					}
				}
				if (StraightCount == 5)
				{
					isRoyal = true;
				}
			}
			//Check Straight // Work
			for (int i = 0; i < 14; i++)
			{
				int StraightCount = 0;
				if (GetInt(IntList, i) == 1)
				{
					for (int h = 0; h < 5; h++)
					{
						if (i + h < 14 && i + h >= 0)
						{
							if (GetInt(IntList, i + h) == 1)
							{
								StraightCount += 1;
							}
							else
							{
								break;
							}
						}
						else
						{
							break;
						}
					}
				}
				if (StraightCount == 5)
				{
					isStraight = true;
				}
			}
			//Check Flush // work
			for (int i = 0; i < 4; i++)
			{
				if (GetHandShape(list, i) == GetHandShape(list, i + 1))
					flushCount += 1;
			}
			if (flushCount >= 4)
			{
				isFlush = true;
			}
			//Check SameCard // work
			for (int i = 0; i < 14; i++)
			{
				if (GetInt(IntList, i) == 4)
				{
					isFourKind = true;
				}
				else if ((GetInt(IntList, i) == 3))
				{
					int MultiCount = 0;
					for (int k = 0; k < 13; k++)
					{
						if (GetInt(IntList, k) >= 1)
						{
							MultiCount += 1;
						}
					}
					if (MultiCount == 2)
					{
						isFullHouse = true;
					}
					if (MultiCount >= 3)
					{
						isThreeKind = true;
					}
				}
				else if ((GetInt(IntList, i) == 2))
				{
					int MultiCount = 0;
					for (int k = 0; k < 13; k++)
					{
						if (GetInt(IntList, k) >= 1)
						{
							MultiCount += 1;
						}
					}
					if (MultiCount == 3)
					{
						isTwopair = true;
					}
				}
			}
			//Check OnePair   //work
			for (int i = 10; i < 14; i++)
			{
				if ((GetInt(IntList, i) == 2))
				{
					int MultiCount = 0;
					for (int k = 0; k < 13; k++)
					{
						if (GetInt(IntList, k) >= 1)
						{
							MultiCount += 1;
						}
					}
					if (MultiCount == 4)
					{
						isOnePair = true;
					}
				}
			}

			// Win money!!!
			if (isRoyal && isFlush)
			{
				cout << "Royal Flush($800)" << endl;
				GetScore(800, true);
			}
			else if (isStraight && isFlush)
			{
				cout << "Straight Flush($50)" << endl;
				GetScore(50, true);
			}
			else if (isFourKind)
			{
				cout << "Four of a Kind($25)" << endl;
				GetScore(25, true);
			}
			else if (isFullHouse)
			{
				cout << "Full House($9)" << endl;
				GetScore(9, true);
			}
			else if (isFlush)
			{
				cout << "Flush($6)" << endl;
				GetScore(6, true);
			}
			else if (isStraight)
			{
				cout << "Straight($4)" << endl;
				GetScore(4, true);
			}
			else if (isThreeKind)
			{
				cout << "Three of a Kind($3)" << endl;
				GetScore(3, true);
			}
			else if (isTwopair)
			{
				cout << "Two Pair($2)" << endl;
				GetScore(2, true);
			}
			else if (isOnePair)
			{
				cout << "One Pair, Jacks or Better ($1)" << endl;
				GetScore(1, true);
			}
			else
			{
				GetScore(0, false);
			}

			//clean hand mess
			delete list;
			list = nullptr;
			delete IntList;
			IntList = nullptr;

			//For sure Cin is clear
			/*cin.clear();
			cin.ignore(1000, '\n');*/
			//If no money
			if (m_money <= 0)
			{
				m_matchstart = false;
			}
		}
		delete deck;
		deck = nullptr;
		cout << "\n\n\n GameOver! \n\n\n" << endl;
		system("PAUSE");
		exit(0);
	}
			//////3. clean the mess
	return 0;
}