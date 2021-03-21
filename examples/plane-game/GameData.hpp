#ifndef GAMEDATA_HPP_
#define GAMEDATA_HPP_

#include <bitset>

enum class Input { Right, Left };
enum class State { Start, Playing, Scoreboard };

struct GameData {
	State m_state{State::Playing};
	std::bitset<2> m_input;  // [left, right]
	int m_score{0};
	int m_bestScore{0};
	int m_targetScore{10};
};

#endif
