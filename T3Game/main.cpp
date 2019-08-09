#include <iostream>
#include <map>
//#include <vector>
#include <array>

#include "t3_game.h"
#include "t3_players.h"


using namespace std;
using namespace T3;

Outcome run_game(map<Mark, Player*> players)
{
	State current_state;
	Outcome outcome = UNFINISHED;
	int counter = 0;
	while (outcome == UNFINISHED)
	{
		cout << current_state << endl;

		// Choose player to move
		Player& curr_player = *players[current_state.get_curr_mark()];

		// Player selects a move
		current_state += curr_player.select_move(current_state);

		//Get current outcome
		outcome = current_state.outcome();

		// Swap players
		++counter;
	}
	
	cout << current_state;

	return outcome;
}

int main()
{
	//State testState;
	//int i, j;
	//Mark mark;
	//int counter = 0;
	//Outcome outcome = UNFINISHED;

	//while (outcome == UNFINISHED && cin >> i >> j)
	//{
	//	if (counter % 2 == 0)
	//		mark = X;
	//	else
	//		mark = O;

	//	//mark = (counter % 2 == 0) ? X : O;

	//	try
	//	{
	//		Move move(mark, i - 1, j - 1);
	//		testState += move;
	//		counter++;
	//		cout << testState;
	//		outcome = testState.outcome();			
	//	}
	//	catch (invalid_move)
	//	{
	//		cout << "Invalid move" << endl;
	//	}
	//}

	map<Mark, Player*> players;
	RandomPlayer a;
	RandomPlayer b;
	players[X] = &a;
	players[O] = &b;
	Outcome outcome = run_game(players);


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