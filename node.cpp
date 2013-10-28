
#include "stdafx.h"
#include "node.h"

// for sorting by heuristic
int node::heuristicAdmissible(void) const {
	// number of disks in the incorrect location
	// never overestimates -> admissible
	int score = 0;
	for(int i = 0; i < current_state.num_disks; i++) {
		if(i >= current_state.pegs[0].size()) {
			score++;
		}
		else if(current_state.pegs[0][i] != i) {
			score++;
		}
	}
	return score;
}

int node::heuristicNonAdmissible(void) const {
	// right peg, wrong position = 1...wrong peg = 2
	// nonadmissible because it can overestimate
	int score = 0;
	for(int i = 0; i < current_state.num_disks; i++) {
		if(i >= current_state.pegs[0].size()) {
			score += 2;
		}
		else if(current_state.pegs[0][i] != i) {
			score++;
		}
	}
	return score;
}
	
// compare f(n) = g(n) + h(n)
// implemented as operator to take advantage of std::sort
bool node::operator < (const node& cmp) const {
	if(astar) {
		if(admissible) {
			return (heuristicAdmissible() + path_cost) < (cmp.heuristicAdmissible() + cmp.path_cost);
		}
		else {
			return (heuristicNonAdmissible() + path_cost) < (cmp.heuristicNonAdmissible() + cmp.path_cost);
		}
	}
	else {
		// RBFS, compare by f-val
		return f_val < cmp.f_val;
	}
}

int node::getPath() {
	return path_cost;
}

bool node::getAdmissible() {
	return admissible;
}

int node::getCost() {
	// f = g + h
	return path_cost + (admissible ? heuristicAdmissible() : heuristicNonAdmissible());
}


node::node(state initial, state cur, bool admissible, bool astar, std::vector<std::pair<int, int>> moves) :
	initial_state(initial), current_state(cur), admissible(admissible), astar(astar), moves(moves), path_cost(moves.size())
{ }

void node:: printHistory(void) {
	std::cout << "\n\nInitial state:\n";
	initial_state.print();
	std::cout << "\nMoves:\n";
	for(auto m : moves) {
		std::cout << "From peg " << m.first << " to " << m.second << "\n";
	}
	std::cout << "\nCurrent state:\n";
	current_state.print();
}