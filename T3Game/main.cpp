#include <iostream>
//#include <vector>
#include <array>

#include "t3_game.h"

using namespace std;
using namespace T3;

int main()
{
	State testState;
	int i, j;
	Mark mark;
	int counter = 0;
	Outcome outcome = UNFINISHED;

	while (outcome == UNFINISHED && cin >> i >> j)
	{
		if (counter % 2 == 0)
			mark = X;
		else
			mark = O;

		try
		{
			Move move(mark, i - 1, j - 1);
			testState += move;
			counter++;
			cout << testState;
			outcome = testState.outcome();			
		}
		catch (invalid_move)
		{
			cout << "Invalid move" << endl;
		}
	}

	switch (outcome)
	{
	case TIE:
		cout << "Tied game!" << endl;
		break;
	case X_WINS:
		cout << "X wins!" << endl;
		break;
	case O_WINS:
		cout << "O wins!" << endl;
		break;
	case UNFINISHED:
		cout << "Game did not finish." << endl;
		break;
	}

	system("pause");
	return 0;
}