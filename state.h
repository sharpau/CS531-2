#pragma once
#include "stdafx.h"

class state {
	friend class node;
	// each vector is a peg. index 0 is the bottom, and index size-1 is the top, accessible
	std::vector<std::vector<int>> pegs;

	int num_disks;
public:
	bool operator == (const state& cmp) const;


	bool isGoal(void);

	std::vector<state> successors(void);


	state(const state &copy);
	state(int n, int problem);
};