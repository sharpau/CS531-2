
#include "stdafx.h"
#include "node.h"

// for sorting by heuristic
int node::heuristicAdmissible(void) const {
	// number of disks in the incorrect location
	// never overestimates -> admissible
	int score = 0;
	for(int i = 0; i < this_state.num_disks; i++) {
		if(i >= this_state.pegs[0].size()) {
			score++;
		}
		else if(this_state.pegs[0][i] != i) {
			score++;
		}
	}
	return score;
}

int node::heuristicNonAdmissible(void) const {
	// right peg, wrong position = 1...wrong peg = 2
	// nonadmissible because it can overestimate
	int score = 0;
	for(int i = 0; i < this_state.num_disks; i++) {
		if(i >= this_state.pegs[0].size()) {
			score += 2;
		}
		else if(this_state.pegs[0][i] != i) {
			score++;
		}
	}
	return score;
}
	
// compare f(n) = g(n) + h(n)
// implemented as operator to take advantage of std::sort
bool node::operator < (const node& cmp) const {
	if(include_path) {
		if(admissible) {
			return (heuristicAdmissible() + path_cost) < (cmp.heuristicAdmissible() + cmp.path_cost);
		}
		else {
			return (heuristicNonAdmissible() + path_cost) < (cmp.heuristicNonAdmissible() + cmp.path_cost);
		}
	}
	else {
		if(admissible) {
			return heuristicAdmissible() < cmp.heuristicAdmissible();
		}
		else {
			return heuristicNonAdmissible() < cmp.heuristicNonAdmissible();
		}
	}
}

int node::getPath() {
	return path_cost;
}


node::node(state st, bool admissible, bool greedy, int cost) :
	this_state(st), admissible(admissible), include_path(greedy), path_cost(cost)
{ }