#include <iostream>
#include <map>
#include <array>


#include "t3_game.h"
#include "t3_players.h"
#include "game_tree.h"


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

int main1()
{
	system("pause");
	return 0;
}

int main()
{
	map<Mark, Player*> players;
	PropCompPlayer a;
	PropCompPlayer b;
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