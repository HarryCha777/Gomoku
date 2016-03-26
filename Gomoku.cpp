// Author: Harry Cha
// Date created: 3/23/16 - 3/26/16

#include <iostream>
#include <algorithm>
using namespace std;

// Use RED, GRN, and NRM to change mark colors.
//#define RED  "\x1B[31m"
//#define GRN  "\x1B[32m"
//#define NRM  "\x1B[0m"

char board[15][15] = {};
int prevX[1000], prevY[1000]; // make it into array to be able to undo multiple times.
int prevXIndex = 0, prevYIndex = 0;
int userNum[1000]; char userCh[1000];
int userNumIndex = 0, userChIndex = 0;
int countTurns = 0;

void printBoard()
{
	printf("   ");
	for (int i = 0; i < 15; i++)
		printf("%c ", (char)'A' + i);
	printf("\n");

	for (int i = 15; i > 0; i--)
	{
		if (i < 10) printf(" ");
		printf("%d ", i);

		for (int j = 0; j < 15; j++)
			printf("%c ", board[i - 1][j]);
			/*if (board[i - 1][j] == 'O')
				printf(GRN "%c ", board[i - 1][j]);
			else if (board[i - 1][j] == 'X' || board[i - 1][j] == 'N')
				printf(RED "%c ", board[i - 1][j]);
			else
				printf(NRM "%c ", board[i - 1][j]);*/
		if (i < 10) printf(" ");
		printf("%d ", i);
		printf("\n");
	}

	printf("   ");
	for (int i = 0; i < 15; i++)
		printf("%c ", (char)'A' + i);
	printf("\n\n");
}

void printNewMarkPos()
{
	printf("Program positioned its new mark at %d, %c.\n", prevX[prevXIndex - 1] + 1, 'A' + prevY[prevYIndex - 1]);
}

bool checkBingoInATurn(int who)
{
	char mark;
	!who ? mark = 'X' : mark = 'O';

	// hoziaontal
	for (int i = 0; i < 15; i++)
		for (int j = 0; j < 15; j++)
		{
			if (board[i][j] == mark && board[i][j + 1] == mark
				&& board[i][j + 2] == mark && board[i][j + 3] == mark
				&& board[i][j + 4] == '+'
				&& j + 4 < 15)
			{
				board[i][j + 4] = 'X'; prevX[prevXIndex++] = i; prevY[prevYIndex++] = j + 4;
				return true;
			}

			if (board[i][j] == '+' && board[i][j + 1] == mark
				&& board[i][j + 2] == mark && board[i][j + 3] == mark
				&& board[i][j + 4] == mark
				&& j + 4 < 15)
			{
				board[i][j] = 'X'; prevX[prevXIndex++] = i; prevY[prevYIndex++] = j; prevX[prevXIndex++] = i; prevY[prevYIndex++] = j;
				return true;
			}

			if (board[i][j] == mark && board[i][j + 1] == '+'
				&& board[i][j + 2] == mark && board[i][j + 3] == mark
				&& board[i][j + 4] == mark
				&& j + 4 < 15)
			{
				board[i][j + 1] = 'X'; prevX[prevXIndex++] = i; prevY[prevYIndex++] = j + 1;
				return true;
			}

			if (board[i][j] == mark && board[i][j + 1] == mark
				&& board[i][j + 2] == mark && board[i][j + 3] == '+'
				&& board[i][j + 4] == mark
				&& j + 4 < 15)
			{
				board[i][j + 3] = 'X'; prevX[prevXIndex++] = i; prevY[prevYIndex++] = j + 3;
				return true;
			}

			if (board[i][j] == mark && board[i][j + 1] == mark
				&& board[i][j + 2] == '+' && board[i][j + 3] == mark
				&& board[i][j + 4] == mark
				&& j + 4 < 15)
			{
				board[i][j + 2] = 'X'; prevX[prevXIndex++] = i; prevY[prevYIndex++] = j + 2;
				return true;
			}
		}

	// vertical
	for (int j = 0; j < 15; j++)
		for (int i = 0; i < 15; i++) // maybe flip them around?
		{
			if (board[j][i] == mark && board[j + 1][i] == mark
				&& board[j + 2][i] == mark && board[j + 3][i] == mark
				&& board[j + 4][i] == '+'
				&& j + 4 < 15)
			{
				board[j + 4][i] = 'X'; prevX[prevXIndex++] = j + 4; prevY[prevYIndex++] = i;
				return true;
			}

			if (board[j][i] == '+' && board[j + 1][i] == mark
				&& board[j + 2][i] == mark && board[j + 3][i] == mark
				&& board[j + 4][i] == mark
				&& j + 4 < 15)
			{
				board[j][i] = 'X'; prevX[prevXIndex++] = j; prevY[prevYIndex++] = i;
				return true;
			}

			if (board[j][i] == mark && board[j + 1][i] == '+'
				&& board[j + 2][i] == mark && board[j + 3][i] == mark
				&& board[j + 4][i] == mark
				&& j + 4 < 15)
			{
				board[j + 1][i] = 'X'; prevX[prevXIndex++] = j + 1; prevY[prevYIndex++] = i;
				return true;
			}

			if (board[j][i] == mark && board[j + 1][i] == mark
				&& board[j + 2][i] == mark && board[j + 3][i] == '+'
				&& board[j + 4][i] == mark
				&& j + 4 < 15)
			{
				board[j + 3][i] = 'X'; prevX[prevXIndex++] = j + 3; prevY[prevYIndex++] = i;
				return true;
			}

			if (board[j][i] == mark && board[j + 1][i] == mark
				&& board[j + 2][i] == '+' && board[j + 3][i] == mark
				&& board[j + 4][i] == mark
				&& j + 4 < 15)
			{
				board[j + 2][i] = 'X'; prevX[prevXIndex++] = j + 2; prevY[prevYIndex++] = i;
				return true;
			}
		}

	// diagonal ascendingly left to right
	for (int i = 0; i < 15; i++)
		for (int j = 0; j < 15; j++)
		{
			if (board[i][j] == mark && board[i + 1][j + 1] == mark
				&& board[i + 2][j + 2] == mark && board[i + 3][j + 3] == mark
				&& board[i + 4][j + 4] == '+'
				&& i + 4 < 15 && j + 4 < 15)
			{
				board[i + 4][j + 4] = 'X'; prevX[prevXIndex++] = i + 4; prevY[prevYIndex++] = j + 4;
				return true;
			}

			if (board[i][j] == '+' && board[i + 1][j + 1] == mark
				&& board[i + 2][j + 2] == mark && board[i + 3][j + 3] == mark
				&& board[i + 4][j + 4] == mark
				&& i + 4 < 15 && j + 4 < 15)
			{
				board[i][j] = 'X'; prevX[prevXIndex++] = i; prevY[prevYIndex++] = j;
				return true;
			}

			if (board[i][j] == mark && board[i + 1][j + 1] == '+'
				&& board[i + 2][j + 2] == mark && board[i + 3][j + 3] == mark
				&& board[i + 4][j + 4] == mark
				&& i + 4 < 15 && j + 4 < 15)
			{
				board[i + 1][j + 1] = 'X'; prevX[prevXIndex++] = i + 1; prevY[prevYIndex++] = j + 1;
				return true;
			}

			if (board[i][j] == mark && board[i + 1][j + 1] == mark
				&& board[i + 2][j + 2] == mark && board[i + 3][j + 3] == '+'
				&& board[i + 4][j + 4] == mark
				&& i + 4 < 15 && j + 4 < 15)
			{
				board[i + 3][j + 3] = 'X'; prevX[prevXIndex++] = i + 3; prevY[prevYIndex++] = j + 3;
				return true;
			}

			if (board[i][j] == mark && board[i + 1][j + 1] == mark
				&& board[i + 2][j + 2] == '+' && board[i + 3][j + 3] == mark
				&& board[i + 4][j + 4] == mark
				&& i + 4 < 15 && j + 4 < 15)
			{
				board[i + 2][j + 2] = 'X'; prevX[prevXIndex++] = i + 2; prevY[prevYIndex++] = j + 2;
				return true;
			}
		}

	// diagonal ascendingly right to left
	for (int i = 0; i < 15; i++)
		for (int j = 0; j < 15; j++)
		{
			if (board[i][j] == mark && board[i - 1][j + 1] == mark
				&& board[i - 2][j + 2] == mark && board[i - 3][j + 3] == mark
				&& board[i - 4][j + 4] == '+'
				&& j + 4 < 15)
			{
				board[i - 4][j + 4] = 'X'; prevX[prevXIndex++] = i - 4; prevY[prevYIndex++] = j + 4;
				return true;
			}

			if (board[i][j] == '+' && board[i - 1][j + 1] == mark
				&& board[i - 2][j + 2] == mark && board[i - 3][j + 3] == mark
				&& board[i - 4][j + 4] == mark
				&& j + 4 < 15)
			{
				board[i][j] = 'X'; prevX[prevXIndex++] = i; prevY[prevYIndex++] = j;
				return true;
			}

			if (board[i][j] == mark && board[i - 1][j + 1] == '+'
				&& board[i - 2][j + 2] == mark && board[i - 3][j + 3] == mark
				&& board[i - 4][j + 4] == mark
				&& j + 4 < 15)
			{
				board[i - 1][j + 1] = 'X'; prevX[prevXIndex++] = i - 1; prevY[prevYIndex++] = j + 1;
				return true;
			}

			if (board[i][j] == mark && board[i - 1][j + 1] == mark
				&& board[i - 2][j + 2] == mark && board[i - 3][j + 3] == '+'
				&& board[i - 4][j + 4] == mark
				&& j + 4 < 15)
			{
				board[i - 3][j + 3] = 'X'; prevX[prevXIndex++] = i - 3; prevY[prevYIndex++] = j + 3;
				return true;
			}

			if (board[i][j] == mark && board[i - 1][j + 1] == mark
				&& board[i - 2][j + 2] == '+' && board[i - 3][j + 3] == mark
				&& board[i - 4][j + 4] == mark
				&& j + 4 < 15)
			{
				board[i - 2][j + 2] = 'X'; prevX[prevXIndex++] = i - 2; prevY[prevYIndex++] = j + 2;
				return true;
			}
		}

	return false;
}

bool checkBingoIn2Turns(int who)
{
	char mark;
	!who ? mark = 'X' : mark = 'O';

	// hoziaontal
	for (int i = 0; i < 15; i++)
		for (int j = 0; j < 15; j++)
		{
			if (countTurns < 7)
			{
				if (board[i][j] == '+' && board[i + 1][j] == mark // only needed once here, no need in vertical or diagnals
					&& board[i][j + 1] == mark && board[i - 1][j] == mark
					&& board[i][j - 1] == '+')
				{
					board[i][j - 1] = 'X';  prevX[prevXIndex++] = i; prevY[prevYIndex++] = j - 1;
					return true;
				}

				if (board[i][j] == '+' && board[i + 1][j] == mark // only needed once here, no need in vertical or diagnals
					&& board[i][j + 1] == mark && board[i - 1][j] == '+'
					&& board[i][j - 1] == mark)
				{
					board[i - 1][j] = 'X';  prevX[prevXIndex++] = i - 1; prevY[prevYIndex++] = j;
					return true;
				}

				if (board[i][j] == '+' && board[i + 1][j] == mark // only needed once here, no need in vertical or diagnals
					&& board[i][j + 1] == '+' && board[i - 1][j] == mark
					&& board[i][j - 1] == mark)
				{
					board[i][j + 1] = 'X';  prevX[prevXIndex++] = i; prevY[prevYIndex++] = j + 1;
					return true;
				}

				if (board[i][j] == '+' && board[i + 1][j] == '+' // only needed once here, no need in vertical or diagnals
					&& board[i][j + 1] == mark && board[i - 1][j] == mark
					&& board[i][j - 1] == mark)
				{
					board[i + 1][j] = 'X';  prevX[prevXIndex++] = i + 1; prevY[prevYIndex++] = j;
					return true;
				}
			}

			if (board[i][j] == mark && board[i][j + 1] == mark
				&& board[i][j + 2] == '+' && board[i][j + 3] == mark
				&& j + 3 < 15)
			{
				board[i][j + 2] = 'X'; prevX[prevXIndex++] = i; prevY[prevYIndex++] = j + 2;
				return true;
			}

			if (board[i][j] == mark && board[i][j + 1] == '+'
				&& board[i][j + 2] == mark && board[i][j + 3] == mark
				&& j + 3 < 15)
			{
				board[i][j + 1] = 'X'; prevX[prevXIndex++] = i; prevY[prevYIndex++] = j + 1;
				return true;
			}

			if (board[i][j] == '+' && board[i][j + 1] == mark
				&& board[i][j + 2] == mark && board[i][j + 3] == mark
				&& board[i][j + 4] == '+'
				&& j + 4 < 15)
			{
				board[i][j] = 'X'; prevX[prevXIndex++] = i; prevY[prevYIndex++] = j; // or board[i][j+4]?
				return true;
			}

			if (board[i][j - 1] != mark && board[i][j] == mark
				&& board[i][j + 1] == '+' && board[i][j + 2] == mark
				&& board[i][j + 3] == '+' && board[i][j + 4] == mark
				&& board[i][j + 5] == '+' && board[i][j + 6] == mark
				&& board[i][j + 7] != mark
				&& j + 6 < 15)
			{
				board[i][j + 3] = 'X'; prevX[prevXIndex++] = i; prevY[prevYIndex++] = j + 3;
				return true;
			}

			if (board[i][j] == '+' // only needed once here, no need in vertical or diagnals
				&& board[i][j + 1] == mark && board[i][j + 2] == '+'
				&& board[i][j - 1] == mark && board[i][j - 2] == '+'
				&& board[i + 1][j] == mark && board[i + 2][j] == '+'
				&& board[i - 1][j] == mark && board[i - 2][j] == '+'
				&& i + 2 < 15 && j + 2 < 15)
			{
				board[i][j] = 'X'; prevX[prevXIndex++] = i; prevY[prevYIndex++] = j;
				return true;
			}
		}

	// vertical
	for (int j = 0; j < 15; j++)
		for (int i = 0; i < 15; i++)
		{
			if (board[j][i] == mark && board[j + 1][i] == mark
				&& board[j + 2][i] == '+' && board[j + 3][i] == mark
				&& j + 3 < 15)
			{
				board[j + 2][i] = 'X'; prevX[prevXIndex++] = j + 2; prevY[prevYIndex++] = i;
				return true;
			}

			if (board[j][i] == mark && board[j + 1][i] == '+'
				&& board[j + 2][i] == mark && board[j + 3][i] == mark
				&& j + 3 < 15)
			{
				board[j + 1][i] = 'X'; prevX[prevXIndex++] = j + 1; prevY[prevYIndex++] = i;
				return true;
			}

			if (board[j][i] == '+' && board[j + 1][i] == mark
				&& board[j + 2][i] == mark && board[j + 3][i] == mark
				&& board[j + 4][i] == '+'
				&& j + 4 < 15)
			{
				board[j + 4][i] = 'X';  prevX[prevXIndex++] = j + 4; prevY[prevYIndex++] = i; // or board[j][i] ?
				return true;
			}

			if (board[j - 1][i] != mark && board[j][i] == mark
				&& board[j + 1][i] == '+' && board[j + 2][i] == mark
				&& board[j + 3][i] == '+' && board[j + 4][i] == mark
				&& board[j + 5][i] == '+' && board[j + 6][i] == mark
				&& board[j + 7][i] != mark
				&& j + 6 < 15)
			{
				board[j + 3][i] = 'X'; prevX[prevXIndex++] = j + 3; prevY[prevYIndex++] = i;
				return true;
			}
		}

	// diagonal ascendingly left to right
	for (int i = 0; i < 15; i++)
		for (int j = 0; j < 15; j++)
		{
			if (board[i][j] == mark && board[i + 1][j + 1] == mark
				&& board[i + 2][j + 2] == '+' && board[i + 3][j + 3] == mark
				&& i + 3 < 15 && j + 3 < 15)
			{
				board[i + 2][j + 2] = 'X'; prevX[prevXIndex++] = i + 2; prevY[prevYIndex++] = j + 2;
				return true;
			}

			if (board[i][j] == mark && board[i + 1][j + 1] == '+'
				&& board[i + 2][j + 2] == mark && board[i + 3][j + 3] == mark
				&& i + 3 < 15 && j + 3 < 15)
			{
				board[i + 1][j + 1] = 'X'; prevX[prevXIndex++] = i + 1; prevY[prevYIndex++] = j + 1;
				return true;
			}

			if (board[i][j] == '+' && board[i + 1][j + 1] == mark
				&& board[i + 2][j + 2] == mark && board[i + 3][j + 3] == mark
				&& board[i + 4][j + 4] == '+'
				&& i + 4 < 15 && j + 4 < 15)
			{
				board[i][j] = 'X'; prevX[prevXIndex++] = i; prevY[prevYIndex++] = j; // or board[i+4][j+4]?
				return true;
			}

			if (board[i - 1][j - 1] != mark && board[i][j] == mark
				&& board[i + 1][j + 1] == '+' && board[i + 2][j + 2] == mark
				&& board[i + 3][j + 3] == '+' && board[i + 4][j + 4] == mark
				&& board[i + 5][j + 5] == '+' && board[i + 6][j + 6] == mark
				&& board[i + 7][j + 7] != mark
				&& i + 6 < 15 && j + 6 < 15)
			{
				board[i + 3][j + 3] = 'X'; prevX[prevXIndex++] = i + 3; prevY[prevYIndex++] = j + 3;
				return true;
			}
		}

	// diagonal ascendingly right to left
	for (int i = 0; i < 15; i++)
		for (int j = 0; j < 15; j++)
		{
			if (board[i][j] == mark && board[i - 1][j + 1] == mark
				&& board[i - 2][j + 2] == '+' && board[i - 3][j + 3] == mark
				&& j + 3 < 15)
			{
				board[i - 2][j + 2] = 'X'; prevX[prevXIndex++] = i - 2; prevY[prevYIndex++] = j + 2;
				return true;
			}

			if (board[i][j] == mark && board[i - 1][j + 1] == '+'
				&& board[i - 2][j + 2] == mark && board[i - 3][j + 3] == mark
				&& j + 3 < 15)
			{
				board[i - 1][j + 1] = 'X'; prevX[prevXIndex++] = i - 1; prevY[prevYIndex++] = j + 1;
				return true;
			}

			if (board[i][j] == '+' && board[i - 1][j + 1] == mark
				&& board[i - 2][j + 2] == mark && board[i - 3][j + 3] == mark
				&& board[i - 4][j + 4] == '+'
				&& j + 4 < 15)
			{
				board[i][j] = 'X'; prevX[prevXIndex++] = i; prevY[prevYIndex++] = j; // or board[i-4][j+4]?
				return true;
			}

			if (board[i + 1][j - 1] != mark && board[i][j] == mark
				&& board[i - 1][j + 1] == '+' && board[i - 2][j + 2] == mark
				&& board[i - 3][j + 3] == '+' && board[i - 4][j + 4] == mark
				&& board[i - 5][j + 5] == '+' && board[i - 6][j + 6] == mark
				&& (board[i - 7][j + 7] != mark || j == 15 - 6)
				&& j + 6 < 15)
			{
				board[i - 3][j + 3] = 'X'; prevX[prevXIndex++] = i - 3; prevY[prevYIndex++] = j + 3;
				return true;
			}
		}

	return false;
}

bool checkBingoIn3Turns(int who)
{
	char mark, mark2;
	if (who == 0)
		{ mark = 'X'; mark2 = 'O';}
	else
		{ mark = 'O'; mark2 = 'X'; }

	// hoziaontal
	for (int i = 0; i < 15; i++)
		for (int j = 0; j < 15; j++)
		{
			if (board[i][j] == mark2
				&& board[i][j + 1] == mark && board[i][j + 2] == mark
				&& board[i][j + 3] == mark && board[i][j + 4] == '+'
				&& j + 4 < 15)
			{
				board[i][j + 4] = 'X'; prevX[prevXIndex++] = i; prevY[prevYIndex++] = j + 4;
				return true;
			}

			if (board[i][j] == '+'
				&& board[i][j + 1] == mark && board[i][j + 2] == mark
				&& board[i][j + 3] == mark && board[i][j + 4] == mark
				&& j + 4 < 15)
			{
				board[i][j] = 'X'; prevX[prevXIndex++] = i; prevY[prevYIndex++] = j;
				return true;
			}

			if (board[i][j] == mark2 && board[i][j + 1] == mark
				&& board[i][j + 2] == mark && board[i][j + 3] == '+'
				&& board[i][j + 4] == mark && board[i][j + 5] == mark
				&& board[i][j + 6] == '+'
				&& j + 6 < 15)
			{
				board[i][j + 6] = 'X'; prevX[prevXIndex++] = i; prevY[prevYIndex++] = j + 6;
				return true;
			}

			if (board[i][j] == '+' && board[i][j + 1] == mark
				&& board[i][j + 2] == mark && board[i][j + 3] == '+'
				&& board[i][j + 4] == mark && board[i][j + 5] == mark
				&& board[i][j + 6] == mark2
				&& j + 6 < 15)
			{
				board[i][j] = 'X'; prevX[prevXIndex++] = i; prevY[prevYIndex++] = j;
				return true;
			}

			if (board[i][j] == mark2 && board[i][j + 1] == mark
				&& board[i][j + 2] == mark && board[i][j + 3] == '+'
				&& board[i][j + 4] == mark && board[i][j + 5] == '+'
				&& j + 5 < 15)
			{
				board[i][j + 5] = 'X'; prevX[prevXIndex++] = i; prevY[prevYIndex++] = j + 5;
				return true;
			}

			if (board[i][j] == '+' && board[i][j + 1] == mark
				&& board[i][j + 2] == '+' && board[i][j + 3] == mark
				&& board[i][j + 4] == mark && board[i][j + 5] == mark2
				&& j + 5 < 15)
			{
				board[i][j] = 'X'; prevX[prevXIndex++] = i; prevY[prevYIndex++] = j;
				return true;
			}

			if (board[i][j] == mark2 && board[i][j + 1] == mark
				&& board[i][j + 2] == '+' && board[i][j + 3] == mark
				&& board[i][j + 4] == mark && board[i][j + 5] == '+'
				&& j + 5 < 15)
			{
				board[i][j + 5] = 'X'; prevX[prevXIndex++] = i; prevY[prevYIndex++] = j + 5;
				return true;
			}

			if (board[i][j] == '+' && board[i][j + 1] == mark
				&& board[i][j + 2] == mark && board[i][j + 3] == '+'
				&& board[i][j + 4] == mark && board[i][j + 5] == mark2
				&& j + 5 < 15)
			{
				board[i][j] = 'X'; prevX[prevXIndex++] = i; prevY[prevYIndex++] = j;
				return true;
			}

			// the below if has 4 variations
			if (board[i][j] == '+' // only needed once here, no need in vertical or diagnals
				&& board[i][j + 1] == mark && board[i][j + 2] == mark2
				&& board[i][j - 1] == mark && board[i][j - 2] == '+'
				&& board[i + 1][j] == mark && board[i + 2][j] == '+'
				&& board[i - 1][j] == mark && board[i - 2][j] == '+'
				&& i + 2 < 15 && j + 2 < 15)
			{
				board[i][j] = 'X'; prevX[prevXIndex++] = i; prevY[prevYIndex++] = j;
				return true;
			}

			if (board[i][j] == '+' // only needed once here, no need in vertical or diagnals
				&& board[i][j + 1] == mark && board[i][j + 2] == '+'
				&& board[i][j - 1] == mark && board[i][j - 2] == mark2
				&& board[i + 1][j] == mark && board[i + 2][j] == '+'
				&& board[i - 1][j] == mark && board[i - 2][j] == '+'
				&& i + 2 < 15 && j + 2 < 15)
			{
				board[i][j] = 'X'; prevX[prevXIndex++] = i; prevY[prevYIndex++] = j;
				return true;
			}

			if (board[i][j] == '+' // only needed once here, no need in vertical or diagnals
				&& board[i][j + 1] == mark && board[i][j + 2] == '+'
				&& board[i][j - 1] == mark && board[i][j - 2] == '+'
				&& board[i + 1][j] == mark && board[i + 2][j] == mark2
				&& board[i - 1][j] == mark && board[i - 2][j] == '+'
				&& i + 2 < 15 && j + 2 < 15)
			{
				board[i][j] = 'X'; prevX[prevXIndex++] = i; prevY[prevYIndex++] = j;
				return true;
			}

			if (board[i][j] == '+' // only needed once here, no need in vertical or diagnals
				&& board[i][j + 1] == mark && board[i][j + 2] == '+'
				&& board[i][j - 1] == mark && board[i][j - 2] == '+'
				&& board[i + 1][j] == mark && board[i + 2][j] == '+'
				&& board[i - 1][j] == mark && board[i - 2][j] == mark2
				&& i + 2 < 15 && j + 2 < 15)
			{
				board[i][j] = 'X'; prevX[prevXIndex++] = i; prevY[prevYIndex++] = j;
				return true;
			}
		}

	// vertical
	for (int j = 0; j < 15; j++)
		for (int i = 0; i < 15; i++)
		{
			if (board[j][i] == mark2
				&& board[j + 1][i] == mark && board[j + 2][i] == mark
				&& board[j + 3][i] == mark && board[j + 4][i] == '+'
				&& j + 4 < 15)
			{
				board[j + 4][i] = 'X'; prevX[prevXIndex++] = j + 4; prevY[prevYIndex++] = i;
				return true;
			}

			if (board[j][i] == '+'
				&& board[j + 1][i] == mark && board[j + 2][i] == mark
				&& board[j + 3][i] == mark && board[j + 4][i] == mark
				&& j + 4 < 15)
			{
				board[j][i] = 'X'; prevX[prevXIndex++] = j; prevY[prevYIndex++] = i;
				return true;
			}

			if (board[j][i] == mark2 && board[j + 1][i] == mark
				&& board[j + 2][i] == mark && board[j + 3][i] == '+'
				&& board[j + 4][i] == mark && board[j + 5][i] == mark
				&& board[j + 6][i] == '+'
				&& j + 6 < 15)
			{
				board[j + 6][i] = 'X'; prevX[prevXIndex++] = j + 6; prevY[prevYIndex++] = i;
				return true;
			}

			if (board[j][i] == '+' && board[j + 1][i] == mark
				&& board[j + 2][i] == mark && board[j + 3][i] == '+'
				&& board[j + 4][i] == mark && board[j + 5][i] == mark
				&& board[j + 6][i] == mark2
				&& j + 6 < 15)
			{
				board[j][i] = 'X'; prevX[prevXIndex++] = j; prevY[prevYIndex++] = i;
				return true;
			}

			if (board[j][i] == mark2 && board[j + 1][i] == mark
				&& board[j + 2][i] == mark && board[j + 3][i] == '+'
				&& board[j + 4][i] == mark && board[j + 5][i] == '+'
				&& j + 5 < 15)
			{
				board[j + 5][i] = 'X'; prevX[prevXIndex++] = j + 5; prevY[prevYIndex++] = i;
				return true;
			}

			if (board[j][i] == '+' && board[j + 1][i] == mark
				&& board[j + 2][i] == '+' && board[j + 3][i] == mark
				&& board[j + 4][i] == mark && board[j + 5][i] == mark2
				&& j + 5 < 15)
			{
				board[j][i] = 'X'; prevX[prevXIndex++] = j; prevY[prevYIndex++] = i;
				return true;
			}

			if (board[j][i] == mark2 && board[j + 1][i] == mark
				&& board[j + 2][i] == '+' && board[j + 3][i] == mark
				&& board[j + 4][i] == mark && board[j + 5][i] == '+'
				&& j + 5 < 15)
			{
				board[j + 5][i] = 'X'; prevX[prevXIndex++] = j + 5; prevY[prevYIndex++] = i;
				return true;
			}

			if (board[j][i] == '+' && board[j + 1][i] == mark
				&& board[j + 2][i] == mark && board[j + 3][i] == '+'
				&& board[j + 4][i] == mark && board[j + 5][i] == mark2
				&& j + 5 < 15)
			{
				board[j][i] = 'X'; prevX[prevXIndex++] = j; prevY[prevYIndex++] = i;
				return true;
			}
		}

	// diagonal ascendingly left to right
	for (int i = 0; i < 15; i++)
		for (int j = 0; j < 15; j++)
		{
			if (board[i][j] == mark2
				&& board[i + 1][j + 1] == mark && board[i + 2][j + 2] == mark
				&& board[i + 3][j + 3] == mark && board[i + 4][j + 4] == '+'
				&& i + 4 < 15 && j + 4 < 15)
			{
				board[i + 4][j + 4] = 'X'; prevX[prevXIndex++] = i + 4; prevY[prevYIndex++] = j + 4;
				return true;
			}

			if (board[i][j] == '+'
				&& board[i + 1][j + 1] == mark && board[i + 2][j + 2] == mark
				&& board[i + 3][j + 3] == mark && board[i + 4][j + 4] == mark
				&& i + 4 < 15 && j + 4 < 15)
			{
				board[i][j] = 'X'; prevX[prevXIndex++] = i; prevY[prevYIndex++] = j;
				return true;
			}

			if (board[i][j] == mark2 && board[i + 1][j + 1] == mark
				&& board[i + 2][j + 2] == mark && board[i + 3][j + 3] == '+'
				&& board[i + 4][j + 4] == mark && board[i + 5][j + 5] == mark
				&& board[i + 6][j + 6] == '+'
				&& i + 6 < 15 && j + 6 < 15)
			{
				board[i + 6][j + 6] = 'X'; prevX[prevXIndex++] = i + 6; prevY[prevYIndex++] = j + 6;
				return true;
			}

			if (board[i][j] == '+' && board[i + 1][j + 1] == mark
				&& board[i + 2][j + 2] == mark && board[i + 3][j + 3] == '+'
				&& board[i + 4][j + 4] == mark && board[i + 5][j + 5] == mark
				&& board[i + 6][j + 6] == mark2
				&& i + 6 < 15 && j + 6 < 15)
			{
				board[i][j] = 'X'; prevX[prevXIndex++] = i; prevY[prevYIndex++] = j;
				return true;
			}

			if (board[i][j] == mark2 && board[i + 1][j + 1] == mark
				&& board[i + 2][j + 2] == mark && board[i + 3][j + 3] == '+'
				&& board[i + 4][j + 4] == mark && board[i + 5][j + 5] == '+'
				&& i + 5 < 15 && j + 5 < 15)
			{
				board[i + 5][j + 5] = 'X'; prevX[prevXIndex++] = i + 5; prevY[prevYIndex++] = j + 5;
				return true;
			}

			if (board[i][j] == '+' && board[i + 1][j + 1] == mark
				&& board[i + 2][j + 2] == '+' && board[i + 3][j + 3] == mark
				&& board[i + 4][j + 4] == mark && board[i + 5][j + 5] == mark2
				&& i + 5 < 15 && j + 5 < 15)
			{
				board[i][j] = 'X'; prevX[prevXIndex++] = i; prevY[prevYIndex++] = j;
				return true;
			}

			if (board[i][j] == mark2 && board[i + 1][j + 1] == mark
				&& board[i + 2][j + 2] == '+' && board[i + 3][j + 3] == mark
				&& board[i + 4][j + 4] == mark && board[i + 5][j + 5] == '+'
				&& i + 5 < 15 && j + 5 < 15)
			{
				board[i + 5][j + 5] = 'X'; prevX[prevXIndex++] = i + 5; prevY[prevYIndex++] = j + 5;
				return true;
			}

			if (board[i][j] == '+' && board[i + 1][j + 1] == mark
				&& board[i + 2][j + 2] == mark && board[i + 3][j + 3] == '+'
				&& board[i + 4][j + 4] == mark && board[i + 5][j + 5] == mark2
				&& i + 5 < 15 && j + 5 < 15)
			{
				board[i][j] = 'X'; prevX[prevXIndex++] = i; prevY[prevYIndex++] = j;
				return true;
			}
		}

	// diagonal ascendingly right to left
	for (int i = 0; i < 15; i++)
		for (int j = 0; j < 15; j++)
		{
			if (board[i][j] == mark2
				&& board[i - 1][j + 1] == mark && board[i - 2][j + 2] == mark
				&& board[i - 3][j + 3] == mark && board[i - 4][j + 4] == '+'
				&& j + 4 < 15)
			{
				board[i - 4][j + 4] = 'X'; prevX[prevXIndex++] = i - 4; prevY[prevYIndex++] = j + 4;
				return true;
			}

			if (board[i][j] == '+'
				&& board[i - 1][j + 1] == mark && board[i - 2][j + 2] == mark
				&& board[i - 3][j + 3] == mark && board[i - 4][j + 4] == mark
				&& j + 4 < 15)
			{
				board[i][j] = 'X'; prevX[prevXIndex++] = i; prevY[prevYIndex++] = j;
				return true;
			}

			if (board[i][j] == mark2 && board[i - 1][j + 1] == mark
				&& board[i - 2][j + 2] == mark && board[i - 3][j + 3] == '+'
				&& board[i - 4][j + 4] == mark && board[i - 5][j + 5] == mark
				&& board[i - 6][j + 6] == '+'
				&& j + 6 < 15)
			{
				board[i - 6][j + 6] = 'X'; prevX[prevXIndex++] = i - 6; prevY[prevYIndex++] = j + 6;
				return true;
			}

			if (board[i][j] == '+' && board[i - 1][j + 1] == mark
				&& board[i - 2][j + 2] == mark && board[i - 3][j + 3] == '+'
				&& board[i - 4][j + 4] == mark && board[i - 5][j + 5] == mark
				&& board[i - 6][j + 6] == mark2
				&& j + 6 < 15)
			{
				board[i][j] = 'X'; prevX[prevXIndex++] = i; prevY[prevYIndex++] = j;
				return true;
			}

			if (board[i][j] == mark2 && board[i - 1][j + 1] == mark
				&& board[i - 2][j + 2] == mark && board[i - 3][j + 3] == '+'
				&& board[i - 4][j + 4] == mark && board[i - 5][j + 5] == '+'
				&& j + 5 < 15)
			{
				board[i - 5][j + 5] = 'X'; prevX[prevXIndex++] = i - 5; prevY[prevYIndex++] = j + 5;
				return true;
			}

			if (board[i][j] == '+' && board[i - 1][j + 1] == mark
				&& board[i - 2][j + 2] == '+' && board[i - 3][j + 3] == mark
				&& board[i - 4][j + 4] == mark && board[i - 5][j + 5] == mark2
				&& j + 5 < 15)
			{
				board[i][j] = 'X'; prevX[prevXIndex++] = i; prevY[prevYIndex++] = j;
				return true;
			}

			if (board[i][j] == mark2 && board[i - 1][j + 1] == mark
				&& board[i - 2][j + 2] == '+' && board[i - 3][j + 3] == mark
				&& board[i - 4][j + 4] == mark && board[i - 5][j + 5] == '+'
				&& j + 5 < 15)
			{
				board[i - 5][j + 5] = 'X'; prevX[prevXIndex++] = i - 5; prevY[prevYIndex++] = j + 5;
				return true;
			}

			if (board[i][j] == '+' && board[i - 1][j + 1] == mark
				&& board[i - 2][j + 2] == mark && board[i - 3][j + 3] == '+'
				&& board[i - 4][j + 4] == mark && board[i - 5][j + 5] == mark2
				&& j + 5 < 15)
			{
				board[i][j] = 'X'; prevX[prevXIndex++] = i; prevY[prevYIndex++] = j;
				return true;
			}
		}

	return false;
}

bool markLongestLine()
{
	// horizontal
	bool hoziBeginE = false;
	int horiCountMax = 0, horiCount = 0;
	int horiEndI = -1, horiEndJ = -1;

	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			if (!hoziBeginE && board[i][j] == '+')
			{
				hoziBeginE = true;
			}

			if (board[i][j] == 'X' && hoziBeginE)
			{
				horiCount++;
			}
			else
			{
				if (horiCount > horiCountMax
					&& board[i][j] == '+'
					&& !(horiCount >= 6))
				{
					horiCountMax = horiCount;
					horiEndI = i;
					horiEndJ = j;
				}

				if (board[i][j] == '+') hoziBeginE = true;
				else hoziBeginE = false;

				horiCount = 0;
			}
		}

		horiCount = 0;
		hoziBeginE = false;
	}

	// vertical
	bool vertBeginE = false;
	int vertCountMax = 0, vertCount = 0;
	int vertEndI = -1, vertEndJ = -1;

	for (int j = 0; j < 15; j++)
	{
		for (int i = 0; i < 15; i++)
		{
			if (!vertBeginE && board[i][j] == '+')
			{
				vertBeginE = true;
			}

			if (board[i][j] == 'X' && vertBeginE)
			{
				vertCount++;
			}
			else
			{
				if (vertCount > vertCountMax
					&& board[i][j] == '+'
					&& !(vertCount >= 6))
				{
					vertCountMax = vertCount;
					vertEndI = i;
					vertEndJ = j;
				}

				if (board[i][j] == '+') vertBeginE = true;
				else vertBeginE = false;

				vertCount = 0;
			}
		}

		vertCount = 0;
		vertBeginE = false;
	}

	// diagonal ascendingly left to right
	bool diagLRBeginE = false;
	int diagLRCountMax = 0, diagLRCount = 0;
	int diagLREndI = -1, diagLREndJ = -1;

	for (int j = 0; j < 15; j++)
	{
		int a = 0, b = 0;

		for (int i = 0; i < 15; i++)
		{
			while (true)
			{
				if (!diagLRBeginE && board[i + a][j + b] == '+')
				{
					diagLRBeginE = true;
					a++; b++;
				}
				else if (board[i + a][j + b] == 'X' && diagLRBeginE)
				{
					diagLRCount++;
					a++; b++;
				}
				else
				{
					if (diagLRCount > diagLRCountMax
						&& board[i][j] == '+'
						&& !(diagLRCount >= 6))
					{
						diagLRCountMax = diagLRCount;
						diagLREndI = i;
						diagLREndJ = j;
					}

					diagLRBeginE = false;
					a = 0; b = 0;
					diagLRCount = 0;
					break;
				}
			}
		}

		a = 0; b = 0;
		diagLRCount = 0;
		diagLRBeginE = false;
	}

	// diagonal ascendingly right to left
	bool diagRLBeginE = false;
	int diagRLCountMax = 0, diagRLCount = 0;
	int diagRLEndI = -1, diagRLEndJ = -1;

	for (int j = 0; j < 15; j++)
	{
		int a = 0, b = 0;

		for (int i = 0; i < 15; i++)
		{
			while (true)
			{
				if (!diagRLBeginE && board[i - a][j + b] == '+')
				{
					diagRLBeginE = true;
					a++; b++;
				}
				else if (board[i - a][j + b] == 'X' && diagRLBeginE)
				{
					diagRLCount++;
					a++; b++;
				}
				else
				{
					if (diagRLCount > diagRLCountMax
						&& board[i][j] == '+'
						&& !(diagRLCount >= 6))
					{
						diagRLCountMax = diagRLCount;
						diagRLEndI = i;
						diagRLEndJ = j;
					}

					diagRLBeginE = false;
					a = 0; b = 0;
					diagRLCount = 0;
					break;
				}
			}
		}

		a = 0; b = 0;
		diagRLCount = 0;
		diagRLBeginE = false;
	}

	// below is finding the max:
	if (horiCountMax == 0 && vertCountMax == 0 && diagLRCountMax == 0 && diagRLCountMax == 0)
		return false;

	int theMax = -1;
	char indexCh;

	if (diagLRCountMax > diagRLCountMax)
	{
		theMax = diagLRCountMax;
		indexCh = 'L';
	}
	else
	{
		theMax = diagRLCountMax;
		indexCh = 'R';
	}

	if (theMax > horiCountMax)
	{
		if (theMax > vertCountMax)
		{
			if (indexCh == 'L')
			{
				board[diagLREndI][diagLREndJ] = 'X'; prevX[prevXIndex++] = diagLREndI; prevY[prevYIndex++] = diagLREndJ;
				return true;
			}
			else if (indexCh == 'R')
			{
				board[diagRLEndI][diagRLEndJ] = 'X'; prevX[prevXIndex++] = diagRLEndI; prevY[prevYIndex++] = diagRLEndJ;
				return true;
			}
			// no need of H or V here.
		}
		else
		{
			board[vertEndI][vertEndJ] = 'X'; prevX[prevXIndex++] = vertEndI; prevY[prevYIndex++] = vertEndJ;
			return true;
		}
	}
	else
	{
		theMax = horiCountMax;

		if (theMax > vertCountMax) // H
		{
			board[horiEndI][horiEndJ] = 'X'; prevX[prevXIndex++] = horiEndI; prevY[prevYIndex++] = horiEndJ;
			return true;
		}
		else // V
		{
			board[vertEndI][vertEndJ] = 'X'; prevX[prevXIndex++] = vertEndI; prevY[prevYIndex++] = vertEndJ;
			return true;
		}
	}

	return false;
}

bool markFirstTime()
{
	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			if (board[i][j] == 'O')
			{
				if (i + 1 < 15 && j + 1 < 15)
				{
					board[i + 1][j + 1] = 'X'; prevX[prevXIndex++] = i + 1; prevY[prevYIndex++] = j + 1;
					return true;
				}
				else if (i + 1 < 15 && j + 1 >= 15)
				{
					board[i + 1][j - 1] = 'X'; prevX[prevXIndex++] = i + 1; prevY[prevYIndex++] = j - 1;
					return true;
				}
				else if (i + 1 >= 15 && j + 1 < 15)
				{
					board[i - 1][j + 1] = 'X'; prevX[prevXIndex++] = i - 1; prevY[prevYIndex++] = j + 1;
					return true;
				}
				else
				{
					board[i - 1][j - 1] = 'X'; prevX[prevXIndex++] = i - 1; prevY[prevYIndex++] = j - 1;
					return true;
				}
			}
		}
	}

	return false;
}

bool checkBingo(int who)
{
	char mark;
	!who ? mark = 'X' : mark = 'O';

	// horizonntal
	for (int i = 0; i < 15; i++)
	{
		int count = 0;
		bool beginEmpty = false;

		for (int j = 0; j < 15; j++)
		{
			if (j == 0)
				beginEmpty = true;

			if (board[i][j] != mark)
			{
				count = 0;
				beginEmpty = true;
			}

			if (board[i][j] == mark && beginEmpty)
			{
				count++;

				if (count == 5)
				{
					if (j + 1 >= 15)
						return true;
					else if (board[i][j + 1] != mark)
						return true;
				}
			}
		}
	}

	// vertical
	for (int i = 0; i < 15; i++)
	{
		int count = 0;
		bool beginEmpty = false;

		for (int j = 0; j < 15; j++)
		{
			if (i == 0)
				beginEmpty = true;

			if (board[j][i] != mark)
			{
				count = 0;
				beginEmpty = true;
			}

			if (board[j][i] == mark && beginEmpty)
			{
				count++;

				if (count == 5)
				{
					if (j + 1 >= 15)
						return true;
					else if (board[j + 1][i] != mark)
						return true;
				}
			}
		}
	}

	// diagonal ascendingly left to right
	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 15; j++)
			if (board[i][j] == mark && board[i + 1][j + 1] == mark
				&& board[i + 2][j + 2] == mark && board[i + 3][j + 3] == mark
				&& board[i + 4][j + 4] == mark)
			{
				if ((j + 5 >= 15 || i + 5 >= 15) && board[i - 1][j - 1] != mark)
					return true;
				else if (board[i + 5][j + 5] != mark && board[i - 1][j - 1] != mark)
					return true;
			}
	}
	// diagonal ascendingly right to left
	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 11; j++)
			if (board[i][j] == mark && board[i - 1][j + 1] == mark
				&& board[i - 2][j + 2] == mark && board[i - 3][j + 3] == mark
				&& board[i - 4][j + 4] == mark)
			{
				if ((j + 5 >= 15 || i - 5 < 0) && board[i + 1][j - 1] != mark)
					return true;
				else if (board[i - 5][j + 5] != mark && board[i + 1][j - 1] != mark)
					return true;
			}
	}

	return false;
}

int main()
{
	printf("Gomoku is a 2-player strategy board game with 15 by 15 table.\n");
	printf("In order to win, a player must mark exactly 5 consecutive spaces horizontally, vertically, or diagonally.\n");
	printf("A player may not win if 6 or more consecutive spaces are marked.\n\n");

	printf("Your mark is 'O', program's mark is 'X', and empty space is '+'.\n");
	//printf("Your mark is '"); printf(GRN "O"); printf(NRM "', program's mark is '"); printf(RED "X"); printf(NRM "', and empty space is '+'.\n");
	printf("The program's most recent mark will be shown as 'N'.\n");
	//printf("The program's most recent mark will be shown as '"); printf(RED "N"); printf(NRM "'.\n");
	printf("To undo a move, enter in 'Z'.\n");
	printf("You may want to consider increasing font size for a bigger game board.\n");
	printf("To begin the Gomoku game, please press enter. I hope you enjoy this game!\n");
	cin.get();

	for (int i = 0; i < 15; i++) for (int j = 0; j < 15; j++) board[i][j] = '+';
	bool programTurn = false, bingo1 = false, bingo2 = false, illegalMark = false;
	int missed = 0;

	while (true)
	{
		if (checkBingo(0)) bingo1 = true;
		if (checkBingo(1)) bingo2 = true;

		if (bingo1)
		{
			board[prevX[prevXIndex - 1]][prevY[prevYIndex - 1]] = 'N';
			printBoard();
			printf("\nThe program won! Better luck next time!\n");
			printf("It took total %d turns each.\n", countTurns);
			break;
		}
		else if (bingo2)
		{
			board[prevX[prevXIndex - 1]][prevY[prevYIndex - 1]] = 'N';
			printBoard();
			printf("\nThe player won! Congratulations! You defeated the program!\n");
			printf("It took total %d turns each.\n", countTurns);
			break;
		}

		if (!programTurn && !illegalMark)
		{
			// N meaning computer's New(most recent) mark.
			if (countTurns != 0)
				board[prevX[prevXIndex - 1]][prevY[prevYIndex - 1]] = 'N';
			printf("// ----------------------------------\n");
			printBoard();
			if (countTurns != 0)
				board[prevX[prevXIndex - 1]][prevY[prevYIndex - 1]] = 'X';
		}

		if (programTurn) // program's programTurn
		{
			//if (missed++ < 4) { programTurn = false; continue; }
			countTurns++;

			// algorithm step 1
			if (checkBingoInATurn(0))
			{ printNewMarkPos(); programTurn = false; continue; }
			// algorithm step 2
			if (checkBingoInATurn(1))
			{ printNewMarkPos(); programTurn = false; continue; }
			// algorithm step 3
			if (checkBingoIn2Turns(0))
			{ printNewMarkPos(); programTurn = false; continue; }
			// algorithm step 4
			if (checkBingoIn2Turns(1))
			{ printNewMarkPos(); programTurn = false; continue; }
			// algorithm step 5
			if (checkBingoIn3Turns(0))
			{ printNewMarkPos(); programTurn = false; continue; }
			// algorithm step 6
			if (checkBingoIn3Turns(1))
			{ printNewMarkPos(); programTurn = false; continue; }
			// algorithm step 7
			if (markLongestLine())
			{ printNewMarkPos(); programTurn = false; continue; }
			// algorithm step 8
			if (markFirstTime())
			{ printNewMarkPos(); programTurn = false; continue; }
		}
		else // player's Turn
		{
			// placing user's mark properly
			printf("\nPlease enter a number followed by a character.\n");
			printf("You will place your mark on that space.\n");
			scanf("%d", &userNum[userNumIndex]);
			scanf(" %c", &userCh[userChIndex]); // space in front of char to prevent errors.
			printf("\n");

			if (userCh[userChIndex] == 'Z') // undo previous programTurn
			{
				board[prevX[--prevXIndex]][prevY[--prevYIndex]] = '+';
				board[prevX[prevXIndex - 1]][prevY[prevYIndex - 1]] = 'X';
				board[userNum[--userNumIndex] - 1][userCh[--userChIndex] - 'A'] = '+';
				countTurns--;
				illegalMark = false;

				printf("You undid the previous turn.\n");
				continue;
			}

			// if already taken by program
			if (board[userNum[userNumIndex] - 1][userCh[userChIndex] - 'A'] == 'X')
			{
				printf("Sorry but that space is already taken by the program.\n");
				printf("Please pick an empty space to mark.\n");
				illegalMark = true;
				continue;
			}
			// if he/she already marked on it
			else if (board[userNum[userNumIndex] - 1][userCh[userChIndex] - 'A'] == 'O')
			{
				printf("Sorry but you already marked on that space.\n");
				printf("Please pick an empty space to mark.\n");
				illegalMark = true;
				continue;
			}
			// if out of board boundaries
			else if (userNum[userNumIndex] < 1 || 15 < userNum[userNumIndex] || userCh[userChIndex] < 'A' || 'N' < userCh[userChIndex])
			{
				printf("Sorry but that space is out of bounds of the board.\n");
				printf("Please pick an empty space on the board.\n");
				illegalMark = true;
				continue;
			}

			board[userNum[userNumIndex] - 1][userCh[userChIndex] - 'A'] = 'O';
			userNumIndex++; userChIndex++;
			illegalMark = false;
		}

		programTurn = true;
	}

	return 0;
}
