# T3Game

## Types of players
- `HumanPlayer` - human; enters moves in cmd
- `RandomPlayer` - bot; chooses move randomly
- `CompleteOrRandPlayer` - bot; completes 3-in-a-row if availabe, otherwise - chooses randomly
- `PropCompPlayer` - bot; calculates ratio of utilities between node and child in tree or smth (IDK, this was a long time ago)
- `MiniMaxPlayer` - bot; moves according to the MiniMax algorithm

## Usage
```cpp
#include "t3_game.h"
#include "t3_players.h"
#include "game_tree.h"

using namespace std;
using namespace T3;

int main()
{
	map<Mark, Player*> players;
	MiniMaxPlayer a;
	HumanPlayer b;
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
```
