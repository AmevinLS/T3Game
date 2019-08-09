#pragma once

#include <iostream>
#include <array>
#include "game_base.h"

namespace T3
{
	class invalid_move : public Game::invalid_move
	{

	};

	enum Mark
	{
		EMPTY = 0,
		X = 1,
		O = -1,
	};
	enum T3Outcome
	{
		TIE,
		X_WINS,
		O_WINS,
		UNFINISHED
	};


	class T3Move :public Game::Move
	{
	public:
		T3Move(Mark m, int a, int b)
			:mark(m), i(a), j(b)
		{
			if (i < 0 || i>2 || j < 0 || j>2)
			{
				throw invalid_move();
			}
		}

		const Mark mark;
		const int i, j;
	};


	class T3State : public Game::State
	{
	public:
		T3State()
		{
			for (int i = 0; i < 3; i++)
				for (int j = 0; j < 3; j++)
					grid[i][j] = EMPTY;
		}
		T3State(const T3State& state)
		{
			for (int i = 0; i < 3; i++)
				for (int j = 0; j < 3; j++)
					grid[i][j] = state.grid[i][j];
		}

		T3Outcome outcome() const
		{
			bool has_empty = false;

			//ROWS
			for (int i = 0; i < 3; i++)
			{
				int sum_row = 0;
				for (int j = 0; j < 3; j++)
				{
					sum_row += grid[i][j];

					if (grid[i][j] == EMPTY)
						has_empty = true;
				}
				if (sum_row == -3)
					return O_WINS;
				if (sum_row == 3)
					return X_WINS;
			}

			//COLS
			for (int j = 0; j < 3; j++)
			{
				int sum_col = 0;
				for (int i = 0; i < 3; i++)
				{
					sum_col += grid[i][j];
				}
				if (sum_col == -3)
					return O_WINS;
				if (sum_col == 3)
					return X_WINS;
			}

			//DIAGONALS
			int sum_main = 0;
			int sum_second = 0;
			for (int i = 0; i < 3; i++)
			{
				sum_main += grid[i][i];
				sum_second += grid[i][2 - i];
			}

			if (sum_main == -3 || sum_second == -3)
				return O_WINS;
			if (sum_main == 3 || sum_second == 3)
				return X_WINS;

			if (has_empty)
				return UNFINISHED;
			else
				return TIE;
		}

		friend ostream& operator<<(ostream& os, const T3State& state)
		{
			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					switch (state.grid[i][j])
					{
					case EMPTY:
						os << '.' << ' ';
						break;
					case X:
						os << 'X' << ' ';
						break;
					case O:
						os << 'O' << ' ';
						break;
					default:
						os << 'U';

					}
				}
				os << endl;
			}
			return os;
		}
		friend void operator+=(T3State& state, const T3Move& move)
		{
			int i = move.i;
			int j = move.j;
			Mark mark = move.mark;

			if (state(i, j) != EMPTY)
			{
				//INVALID MOVE, do smth
				throw invalid_move();
			}
			else
			{
				state.set(i, j, mark);
			}
		}

		Mark operator()(int i, int j) const
		{
			return grid[i][j];
		}

	private:
		void set(int i, int j, Mark mark)
		{
			grid[i][j] = mark;
		}

		array<array<Mark, 3>, 3> grid;
	};
}