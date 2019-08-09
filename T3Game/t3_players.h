#pragma once

#include "game_base.h"
#include "t3_game.h"
#include <ctime>

namespace T3 {
	class Player : public Game::Player
	{
	public:
		virtual Move select_move(const State& state) = 0;
	};

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
					//cout << "Invalid move, try again." << endl;
				}
				srand(time(NULL));
			}
		}
	};
}
