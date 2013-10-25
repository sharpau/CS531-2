#pragma once

#include "state.h"

class node {
	
	int path_cost;
	bool admissible;
	bool include_path;

	int heuristicAdmissible(void) const;
	int heuristicNonAdmissible(void) const;

public:
	state this_state;


	bool operator < (const node& cmp) const;
	int getPath();

	node(state st, bool admissible, bool greedy, int cost);
};