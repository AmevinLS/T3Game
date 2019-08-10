#pragma once
#include "t3_game.h"
#include <vector>

using namespace std;
using namespace T3;

namespace T3
{
	//Structure with wins/losses/ties
	struct XOT
	{

		void operator+=(const XOT& wlt)
		{
			x_wins += wlt.x_wins;
			o_wins += wlt.o_wins;
			ties += wlt.ties;
		}

		int x_wins;
		int o_wins;
		int ties;
	};

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
		XOT xot;
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

	void assign_xots(Game_Node* tree)
	{
		if (tree->childs.size() == 0)
		{
			Outcome outcome = tree->state.outcome();
			switch (outcome)
			{
			case X_WINS:
				tree->xot.x_wins = 1;
				break;
			case O_WINS:
				tree->xot.o_wins = 1;
				break;
			case TIE:
				tree->xot.ties = 1;
				break;
			case UNFINISHED:
				throw;
			}
		}
		else
		{
			for (auto child : tree->childs)
			{
				assign_xots(child);
				tree->xot += child->xot;
			}
		}
	}
}