#pragma once

#include "state.h"

class node {
	
	int path_cost;
	bool admissible; // which heuristic to use
	bool astar; // true for a*, false for RBFS

	int heuristicAdmissible(void) const;
	int heuristicNonAdmissible(void) const;

	std::vector<std::pair<int, int>> moves;

public:
	state current_state;
	state initial_state;
	int f_val; // RBFS only

	bool operator < (const node& cmp) const;


	int getPath();
	int getCost();
	bool getAdmissible();
	std::vector<std::pair<int, int>> getMoves() { return moves; };

	node(state initial, state cur, bool admissible, bool astar, std::vector<std::pair<int, int>> moves = std::vector<std::pair<int, int>>());

	void printMoves();
};