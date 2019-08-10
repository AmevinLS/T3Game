#pragma once

#include "game_base.h"
#include "t3_game.h"
#include <ctime>
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

	class PropCompPlayer : public Player
	{
	public:
		Move select_move(const State& state) override
		{
			Game_Node* tree = build_t3_tree(state);
			assign_xots(tree);

			int best_i = 0;
			float best_val = -1;

			for (int i = 0; i < tree->childs.size(); i++)
			{
				Game_Node* child = tree->childs[i];
				Move move = tree->moves[i];
				float val_i = -1;
				if (state.get_curr_mark() == X)
				{
					val_i = float(child->xot.x_wins) / child->xot.total();
				}
				else
				{
					val_i = float(child->xot.o_wins) / child->xot.total();
				}
				if (val_i > best_val)
				{
					best_val = val_i;
					best_i = i;
				}
			}
			return tree->moves[best_i];
		}
	};
}
