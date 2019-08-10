#pragma once
#include <ctime>

#include "game_base.h"
#include "t3_game.h"
#include "game_tree.h"

namespace T3 {
	class Player : public Game::Player
	{
	public:
		virtual Move select_move(const State& state) = 0;
	};

	// A person chooses where to move
	class HumanPlayer : public Player
	{
	public:
		Move select_move(const State& state) override
		{
			int i = 0, j = 0;

			while (true) 
			{	
				cout << "> ";
				cin >> i >> j;
				try {

					Move res(state.get_curr_mark(), i-1, j-1);
					if (state.is_legal_move(res))
						return res;
					else
						throw invalid_move();
				}
				catch (invalid_move)
				{
					cout << "Invalid move, try again." << endl;
				}
			}			
		}
	};

	//Moves randomly
	class RandomPlayer : public Player
	{
	public:
		Move select_move(const State& state) override
		{
			int i = 0, j = 0;

			while (true)
			{
				i = rand() % 3;
				j = rand() % 3;
				try {

					Move res(state.get_curr_mark(), i, j);
					if (state.is_legal_move(res))
						return res;
					else
						throw invalid_move();
				}
				catch (invalid_move)
				{

				}
				srand(unsigned int(time(NULL)));
			}
		}
	};

	//TODO*
	struct Two_in_row
	{
		bool has_two;
		int x = -1, y = -1;
	};
	//Completes to 3 marks or else moves randomly
	class CompleteOrRandPlayer : public Player
	{
	public:
		Move select_move(const State& state) override
		{
			int i = 0, j = 0;
			bool two_in_row = false;


			//Check if there is two in a row

			if (two_in_row)
			{
				//Move to complete thee two in a row
			}
			else
			{
				while (true)
				{
					i = rand() % 3;
					j = rand() % 3;
					try {

						Move res(state.get_curr_mark(), i, j);
						if (state.is_legal_move(res))
							return res;
						else
							throw invalid_move();
					}
					catch (invalid_move)
					{

					}
					srand(unsigned int(time(NULL)));
				}
			}
		}
	};
	//*TODO

	class TreePlayer : public Player
	{
	public:
		virtual Game_Node<XOT>* build_t3_tree(const State& start_state)
		{
			Game_Node<XOT>* game_node = new Game_Node<XOT>(start_state);
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
						Game_Node<XOT>* child = build_t3_tree(next_state);
						game_node->childs.push_back(child);
						game_node->moves.push_back(curr_move);
					}
				}
			}

			return game_node;
		}
	};

	class PropCompPlayer : public TreePlayer
	{
	public:
		Move select_move(const State& state) override
		{
			Game_Node<XOT>* tree = build_t3_tree(state);
			assign_xots(tree);

			int best_i = 0;
			float best_val = -1;

			for (unsigned int i = 0; i < tree->childs.size(); i++)
			{
				Game_Node<XOT>* child = tree->childs[i];
				Move move = tree->moves[i];
				float val_i = -1;
				if (state.get_curr_mark() == X)
				{
					val_i = float(child->utility.x_wins /*+ child->xot.ties*/) / child->utility.total();
				}
				else
				{
					val_i = float(child->utility.o_wins /*+ child->xot.ties*/) / child->utility.total();
				}
				if (val_i > best_val)
				{
					best_val = val_i;
					best_i = i;
				}
				cout << "Move: " << move.i + 1 << ' ' << move.j + 1 << " Val_i: " << val_i << endl;
			}

			cout << "Best_val: " << best_val << endl;

			return tree->moves[best_i];
		}
	private:
		void assign_xots(Game_Node<XOT>* tree)
		{
			if (tree->childs.size() == 0)
			{
				Outcome outcome = tree->state.outcome();
				switch (outcome)
				{
				case X_WINS:
					tree->utility.x_wins = 1;
					break;
				case O_WINS:
					tree->utility.o_wins = 1;
					break;
				case TIE:
					tree->utility.ties = 1;
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
					tree->utility += child->utility;
				}
			}
		}
	};
}
