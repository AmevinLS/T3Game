#pragma once

#include "game_base.h"
#include "t3_game.h"

namespace T3 {
	class Player : public Game::Player
	{
	public:
		virtual Move select_move(const State& state) = 0;
	};

	class HumanPlayer : public Player
	{
	public:
		virtual Move select_move(const State& state)
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

	class RandomPlayer : public Player
	{

	};
}
