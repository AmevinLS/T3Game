#pragma once
#include "t3_game.h"
#include <vector>

using namespace std;
using namespace T3;

namespace T3
{
	class Game_Node
	{
	public:
		Game_Node()
		{

		}
		Game_Node(const State& st)
		{
			state = st;
		}

		State state;
		vector<Game_Node*> childs;
	};

	Game_Node* build_t3_tree(const State& start_state)
	{
		Game_Node* game_node = new Game_Node(start_state);
		if (start_state.outcome() != UNFINISHED)
		{
			return game_node;
		}

		Mark start_mark = start_state.get_curr_mark();
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				Move curr_move = Move(start_mark, i, j);
				if (start_state.is_legal_move(curr_move))
				{
					State next_state = start_state + curr_move;
					Game_Node* child = build_t3_tree(next_state);
					game_node->childs.push_back(child);
				}
			}
		}

		return game_node;
	}
}