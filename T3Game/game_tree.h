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

		int total() const
		{
			return x_wins + o_wins + ties;
		}

		int x_wins;
		int o_wins;
		int ties;
	};

	template<typename T>
	class Game_Node
	{
	public:
		//Game_Node<XOT>()
		//{

		//}
		Game_Node(const State& st)
			: state(st)
		{}

		State state;
		vector<Game_Node<T>*> childs;
		vector<Move> moves;
		T utility;
	};
}