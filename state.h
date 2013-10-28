#pragma once
#include "stdafx.h"

struct state {
	// each vector is a peg. index 0 is the bottom, and index size-1 is the top, accessible
	std::vector<std::vector<int>> pegs;

	int num_disks;

	bool operator == (const state& cmp) const;


	bool isGoal(void);

	std::vector<state> successors(void);


	state(const state &copy);
	state(int n, int problem);

	void print();
};