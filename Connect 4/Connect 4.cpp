#include <iostream>
#include <string>
#include <cstdlib>
#include <Windows.h>
#include <conio.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>


using namespace std;

char startButton;
char restartButton;

bool m_matchStart = false;
bool m_correctName = true;
bool m_gameFinish = false;
bool m_FirstTurn = true;

int m_rowMaxCount = 6;
int m_columnMaxCount = 7;

float mode1Win = 1;
float mode2Win = 1;
float topWin = 5;
float score = 0;

int one7 = 0;
int *one7Pnt;
int seconds = 1;
int availSpace = 5;
int *availPnt;
int turns = 0;

string levelarray[6][7] = { { "|_|","|_|","|_|","|_|","|_|","|_|","|_|" },
{ "|_|","|_|","|_|","|_|","|_|","|_|","|_|" },
{ "|_|","|_|","|_|","|_|","|_|","|_|","|_|" },
{ "|_|","|_|","|_|","|_|","|_|","|_|","|_|" },
{ "|_|","|_|","|_|","|_|","|_|","|_|","|_|" },
{ "|_|","|_|","|_|","|_|","|_|","|_|","|_|" } };

string player1;
string player2;
string enemy = "You Daddy";

void Draw()
{
	cout << "No One Wins the game, Draw " << endl;

	//cout << "please press any button to close the game " << endl;
	cout << " press 1 to restart the match " << endl;
	cout << " press 2 to quit the match " << endl;


	cin >> restartButton;
	system("cls");
	if (restartButton == '1')
	{
		m_matchStart = false;
		m_correctName = true;
		m_gameFinish = false;
		m_FirstTurn = true;

		one7 = 0;
		*one7Pnt;
		seconds = 1;
		availSpace = 5;
		*availPnt;
		turns = 0;

		for (int i = 0; i<6; i++)
		{
			for (int j = 0; j<7; j++)
			{
				levelarray[i][j] = "|_|";
			}
		}
	}
	if (restartButton == '2')
	{
		exit(0);
	}
	//system("pause");

	//exit(0);
}
void totPoint(float win, int turns, string theplayer)
{
	cout << "\n---------------------------------------------\n\n" << endl;

	cout << theplayer << " has won! \n " << theplayer << " get " << win << " turns win " << endl;

	//cout << "please press any button to close the game " << endl;
	cout << " press 1 to restart the match " << endl;
	cout << " press 2 to quit the match " << endl;


	cin >> restartButton;
	system("cls");
	if (restartButton == '1')
	{
		m_matchStart = false;
		m_correctName = true;
		m_gameFinish = false;
		m_FirstTurn = true;

		one7 = 0;
		*one7Pnt;
		seconds = 1;
		availSpace = 5;
		*availPnt;
		turns = 0;

		for (int i = 0; i<6; i++)    
		{
			for (int j = 0; j<7; j++) 
			{
				levelarray[i][j] = "|_|";
			}
		}
	}
	if (restartButton == '2')
	{
		exit(0);
	}
	//system("pause");

	//exit(0);
}
void playerName(string &Myplayer, bool NameCorrect, int letterNum)
{
	do
	{
		cout << "\n --------------------------------------\n\n" << endl;
		cout << "Please type " << letterNum << "'s name (must more than 2 letter): \n" << endl;
		cin >> Myplayer;
		Myplayer.length();

		if (Myplayer.length() <= 2)
		{
			NameCorrect = false;
		}
		else
		{
			NameCorrect = true;
		}
	}
	while (NameCorrect == false);
	{
		cout << "\n" << Myplayer << " is Player " << letterNum << endl;
	}
}
void myLevel(int m_rowMaxCount, int m_columnMaxCount, string levelarray[6][7])
{
	for (int m_rowCount = 0; m_rowCount <= m_rowMaxCount; m_rowCount++)
	{
		cout << "\n\t";
		for (int m_columnCount = 0; m_columnCount < m_columnMaxCount; m_columnCount++)
		{
			cout << levelarray[m_rowCount][m_columnCount] << " ";
		}
	}
	cout << "\n    --------------------------\n\n";

}
void checkDraw(int *availpnt, int *one7Pnt, bool &gameFinish, string levelarray[6][7])
{
	//Check Draw
	int MaxChip = (m_rowMaxCount*m_columnMaxCount);
	for (int m_rowCount = 0; m_rowCount < m_rowMaxCount; m_rowCount++)
	{
		cout << "\n\t";
		for (int m_columnCount = 0; m_columnCount < m_columnMaxCount; m_columnCount++)
		{
			if (levelarray[m_rowCount][m_columnCount] == "|O|" || levelarray[m_rowCount][m_columnCount] == "|X|")
				MaxChip--;
		}
	}
	//cout << MaxChip << "rest Slot" << endl;
	//system("pause");
	if (MaxChip <= 0)
	{
		Draw();
	}
	else
	{
		MaxChip = (m_rowMaxCount*m_columnMaxCount) / 2;
	}
}
void checkWon(int *availpnt, int *one7Pnt, bool &gameFinish, string levelarray[6][7])
{
	//Horizontal
	if (levelarray[*availpnt][*one7Pnt] == levelarray[*availpnt][*one7Pnt + 1] ||
		(levelarray[*availpnt][*one7Pnt] == levelarray[*availpnt][*one7Pnt - 1]))
	{
		int score = 0;
		if (levelarray[*availpnt][*one7Pnt] == levelarray[*availpnt][*one7Pnt + 1])
		{
			score++;
			if (levelarray[*availpnt][*one7Pnt + 1] == levelarray[*availpnt][*one7Pnt + 2])
			{
				score++;
				if (levelarray[*availpnt][*one7Pnt + 2] == levelarray[*availpnt][*one7Pnt + 3])
				{
					score++;
				}
			}
		}
		if (levelarray[*availpnt][*one7Pnt] == levelarray[*availpnt][*one7Pnt - 1])
		{
			score++;
			if (levelarray[*availpnt][*one7Pnt - 1] == levelarray[*availpnt][*one7Pnt - 2])
			{
				score++;
				if (levelarray[*availpnt][*one7Pnt - 2] == levelarray[*availpnt][*one7Pnt - 3])
				{
					score++;
				}
			}
		}
		if(score >=3)
		{
			gameFinish = true;
		}
	}
	///vertical
	if (levelarray[*availpnt][*one7Pnt] == levelarray[*availpnt+1][*one7Pnt] ||
			(levelarray[*availpnt][*one7Pnt] == levelarray[*availpnt-1][*one7Pnt]))
	{
		int score = 0;
		if (levelarray[*availpnt][*one7Pnt] == levelarray[*availpnt+1][*one7Pnt])
		{
			score++;
			if (levelarray[*availpnt+1][*one7Pnt] == levelarray[*availpnt+2][*one7Pnt])
			{
				score++;
				if (levelarray[*availpnt+2][*one7Pnt] == levelarray[*availpnt+3][*one7Pnt])
				{
					score++;
				}
			}
		}
		if (levelarray[*availpnt][*one7Pnt] == levelarray[*availpnt-1][*one7Pnt])
		{
			score++;
			if (levelarray[*availpnt-1][*one7Pnt] == levelarray[*availpnt-2][*one7Pnt])
			{
				score++;
				if (levelarray[*availpnt-2][*one7Pnt] == levelarray[*availpnt-3][*one7Pnt ])
				{
					score++;
				}
			}
		}
		if(score >=3)
		{
			gameFinish = true;
		}
	}
	// 135(+,-) degree
	if (levelarray[*availpnt][*one7Pnt] == levelarray[*availpnt + 1][*one7Pnt + 1] ||
		(levelarray[*availpnt][*one7Pnt] == levelarray[*availpnt - 1][*one7Pnt - 1]))
	{
		int score = 0;
		if (levelarray[*availpnt][*one7Pnt] == levelarray[*availpnt + 1][*one7Pnt + 1])
		{
			score++;
			if (levelarray[*availpnt + 1][*one7Pnt + 1] == levelarray[*availpnt + 2][*one7Pnt + 2])
			{
				score++;
				if (levelarray[*availpnt + 2][*one7Pnt + 2] == levelarray[*availpnt + 3][*one7Pnt + 3])
				{
					score++;
				}
			}
			//cout << "down135 =score " << score << endl;
			//system("pause");
		}
		if (levelarray[*availpnt][*one7Pnt] == levelarray[*availpnt - 1][*one7Pnt - 1])
		{
			score++;
			if (levelarray[*availpnt - 1][*one7Pnt - 1] == levelarray[*availpnt - 2][*one7Pnt - 2])
			{
				score++;
				if (levelarray[*availpnt - 2][*one7Pnt - 2] == levelarray[*availpnt - 3][*one7Pnt - 3])
				{
					score++;
				}
			}
			//cout << "up135 =score " << score << endl;
			//system("pause");
		}
		if (score >= 3)
		{
			gameFinish = true;
		}
	}
	//45(+,+) degree

	if (levelarray[*availpnt][*one7Pnt] == levelarray[*availpnt + 1][*one7Pnt - 1] ||
		(levelarray[*availpnt][*one7Pnt] == levelarray[*availpnt - 1][*one7Pnt + 1]))
	{
		int score = 0;
		if (levelarray[*availpnt][*one7Pnt] == levelarray[*availpnt + 1][*one7Pnt - 1])
		{
			score++;
			if (levelarray[*availpnt + 1][*one7Pnt - 1] == levelarray[*availpnt + 2][*one7Pnt - 2])
			{
				score++;
				if (levelarray[*availpnt + 2][*one7Pnt - 2] == levelarray[*availpnt + 3][*one7Pnt - 3])
				{
					score++;
				}
			}
			//cout << "down45 =score " << score << endl;
			//system("pause");
		}
		if (levelarray[*availpnt][*one7Pnt] == levelarray[*availpnt - 1][*one7Pnt + 1])
		{
			score++;
			if (levelarray[*availpnt - 1][*one7Pnt + 1] == levelarray[*availpnt - 2][*one7Pnt + 2])
			{
				score++;
				if (levelarray[*availpnt - 2][*one7Pnt + 2] == levelarray[*availpnt - 3][*one7Pnt + 3])
				{
					score++;
				}
			}
			//cout << "up45 =score " << score << endl;
			//system("pause");
		}
		if (score >= 3)
		{
			gameFinish = true;
		}
	}

	//////////////////////////////////////////////////////////////
}
int main()
{
start:
	srand(time(NULL));
	one7Pnt = &one7;
	availPnt = &availSpace;
	//////////////////////////////////////////////////////////////////////////

	cout << "Press '1' button to play with AI\n" << endl;
	cout << "Press '2' button to play versus mode\n" << endl;
	cout << "Press '3' button to close the game\n" << endl;
	cin >> startButton;

	while (m_matchStart == false)
	{
		system("cls");

		if (startButton == '1')
		{
			cout << "\n\n";

			m_matchStart == true;
			playerName(player1, m_correctName, 1);

			system("cls");
			cout << "\n\n------------------------------------------\n\n Game Start" << endl;
			cout << "\n\n------------------------------------------\n\n Please press 1-7 button on your keyboard\n\n" << endl;

			while (!m_gameFinish)
			{
				cout << "It is " << player1 << "'s turn!" << endl;

				if (m_FirstTurn == true)
				{
					for (int m_rowCount = 0; m_rowCount < m_rowMaxCount; m_rowCount++)
					{
						cout << "\n\t";
						for (int m_columnCount = 0; m_columnCount < m_columnMaxCount; m_columnCount++)
						{
							cout << levelarray[m_rowCount][m_columnCount] << " ";
						}
					}
					cout << "\n\t____________________________________________________\n\n\n";
					m_FirstTurn = false;

				}

				/////////////////////////////////////////////////////////////////


				if (m_gameFinish == false)
				{
					cin >> one7; // input

					one7--;
					availSpace = 5;
				}

				while (one7 < 0 || one7 >= 7 && cin.good())
				{
					cin.clear();
					cin.ignore(1000, '\n');
					cout << "\n\n------------------------------------------\n\n" << player1 << " Please press 1-7 button on your keyboard \n\n" << endl;

					cin >> one7;
					one7--;
				}

				while (levelarray[availSpace][(one7)] == "|O|" || levelarray[availSpace][one7] == "|X|")
				{
					availSpace--;

					if (availSpace < 0)
					{
						cout << "\n\n You can't drop the chip to here, it is full!" << endl;

						cout << "\n\n------------------------------------------\n\n" << player1 << " Please press 1-7 button on your keyboard " << endl;
						cin >> one7;

						one7--;
						availSpace = 5;
					}
				}

				levelarray[availSpace][one7] = "|O|";

				checkWon(availPnt, one7Pnt, m_gameFinish, levelarray);

				system("cls");

					if (m_gameFinish == true)
					{
						cout << "player win" << endl;
						totPoint(mode1Win, turns, player1);
						goto start;
					}
					else
					{
						checkDraw(availPnt, one7Pnt, m_gameFinish, levelarray);

						cout << "It is the " << enemy << "'s turn!" << endl;
					}

				myLevel(m_rowMaxCount, m_columnMaxCount, levelarray);

				//////////////////////////////////////////////////////////////////

				one7 = (rand() % 6) + 1;

				availSpace = 5;
				one7--;

				while (levelarray[availSpace][(one7)] == "|O|" || levelarray[availSpace][one7] == "|X|")
				{
					availSpace--;

					if (availSpace <= 0)
					{
						one7 = (rand() % 6) + 1;

						availSpace = 5;
						one7--;
					}
				}

				levelarray[availSpace][one7] = "|X|";

				checkWon(availPnt, one7Pnt, m_gameFinish, levelarray);

				system("cls");
					
				turns++;

				if (m_gameFinish == true)
				{
					totPoint(mode1Win, turns, enemy);
					goto start;

				}
				else
				{
					checkDraw(availPnt, one7Pnt, m_gameFinish, levelarray);

					cout << "It is " << player1 << "'s turn!" << endl;
				}

				myLevel(m_rowMaxCount, m_columnMaxCount, levelarray);
				
			}
		}
		else if (startButton == '2')
		{
			cout << "\n\n";

			m_matchStart == true;

			playerName(player1, m_correctName, 1);
			playerName(player2, m_correctName, 2);

			system("cls");
			cout << "\n\n------------------------------------------\n\n Game Start" << endl;
			cout << "\n\n------------------------------------------\n\n Please press 1-7 button on your keyboard\n\n" << endl;

			while (!m_gameFinish)
			{
				cout << "It is " << player1 << "'s turn!" << endl;

				if (m_FirstTurn == true)
				{
					for (int m_rowCount = 0; m_rowCount < m_rowMaxCount; m_rowCount++)
					{
						cout << "\n\t";

						for (int m_columnCount = 0; m_columnCount < m_columnMaxCount; m_columnCount++)
						{
							cout << levelarray[m_rowCount][m_columnCount] << " ";
						}
					}

					cout << "\n\t____________________________________________________\n\n\n";
					m_FirstTurn = false;
				}

				///////////////////////////////////////////////////

				if (m_gameFinish == false)
				{
					cin >> one7; // input
					one7--;
					availSpace = 5;
				}

				while (one7 < 0 || one7 >= 7 && cin.good()) //cin.good();
				{
					cin.clear();
					cin.ignore(1000, '\n');
					cout << "\n\n------------------------------------------\n\n" << player1 << " Please press 1-7 button on your keyboard \n\n" << endl;

					cin >> one7;
					one7--;
				}

				while (levelarray[availSpace][(one7)] == "|O|" || levelarray[availSpace][one7] == "|X|")
				{
					availSpace--;

					if (availSpace < 0)
					{
						cout << "\n\n You can't drop the chip to here, it is full!" << endl;

						cout << "\n\n------------------------------------------\n\n" << player1 << " Please press 1-7 button on your keyboard " << endl;
						cin >> one7;

						one7--;
						availSpace = 5;
					}
				}

				levelarray[availSpace][one7] = "|O|";

				checkWon(availPnt, one7Pnt, m_gameFinish, levelarray);

				system("cls");

				if (m_gameFinish == true)
				{
					totPoint(mode2Win, turns, player1);
					goto start;

				}
				else
				{
					checkDraw(availPnt, one7Pnt, m_gameFinish, levelarray);

					cout << "It is " << player2 << "'s turn!" << endl;
				}

				myLevel(m_rowMaxCount, m_columnMaxCount, levelarray);

				///////////////////////////////////////////////////////////

				/*if (m_gameFinish == true)
				{

					exit(0);
				}*/

				if (m_gameFinish == false)
				{
					cin >> one7; // input

					one7--;
					availSpace = 5;
				}

				while (one7 < 0 || one7 >= 7 && cin.good())
				{
					cin.clear();
					cin.ignore(1000, '\n');
					cout << "\n\n------------------------------------------\n\n" << player2 << " Please press 1-7 button on your keyboard \n\n" << endl;

					cin >> one7;
					one7--;
				}

				while (levelarray[availSpace][(one7)] == "|O|" || levelarray[availSpace][one7] == "|X|")
				{
					availSpace--;

					if (availSpace < 0)
					{
						cout << "\n\n You can't drop the chip to here, it is full!" << endl;

						cout << "\n\n------------------------------------------\n\n" << player2 << " Please press 1-7 button on your keyboard " << endl;
						cin >> one7;

						one7--;
						availSpace = 5;
					}
				}

				levelarray[availSpace][one7] = "|X|";

				checkWon(availPnt, one7Pnt, m_gameFinish, levelarray);

				system("cls");

				if (m_gameFinish == true)
				{
					totPoint(mode2Win, turns, player2);
					goto start;

				}
				else
				{

					checkDraw(availPnt, one7Pnt, m_gameFinish, levelarray);

					cout << "It is " << player1 << "'s turn!" << endl;
				}

				myLevel(m_rowMaxCount, m_columnMaxCount, levelarray);
			}
		}
		else if (startButton == '3')
		{
			exit(0);
		}
		else
		{
			cout << "Press '1' button to play with AI\n" << endl;
			cout << "Press '2' button to play versus mode\n" << endl;
			cout << "Press '3' button to close the game\n" << endl;
			cin >> startButton;
		}
	}
	return 0;
}


///Need Restart!
//Cin Must be int
