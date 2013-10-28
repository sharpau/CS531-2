// CS531-2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "state.h"
#include "node.h"


bool aStar(state initial, bool admissible) {
	std::deque<node> frontier;	
	std::vector<state> explored;
	explored.push_back(initial);
	node current = node(initial, initial, admissible, true);

	while(!current.current_state.isGoal()) {
		// add current node to 
		auto succs = current.current_state.successors();

		// make sure we haven't already looked at this successor - if we can't find it in explored, add to frontier
		for(int i = 0; i < succs.size(); i++) {
			if(std::find(explored.begin(), explored.end(), succs[i]) == explored.end()) {
				// add move to list
				auto moves = current.getMoves();
				int take, put;
				for(int peg = 0; peg < 3; peg++) {
					if(current.current_state.pegs[peg].size() + 1 == succs[i].pegs[peg].size()) {
						put = peg;
					}
					else if(current.current_state.pegs[peg].size() - 1 == succs[i].pegs[peg].size()) {
						take = peg;
					}
				}
				moves.push_back(std::make_pair(take, put));

				// put new node in list
				frontier.push_back(node(initial, succs[i], admissible, true, moves));
			}
		}

		// find and expand best node
		if(frontier.size() == 0) {
			return false;
		}
		std::sort(frontier.begin(), frontier.end());
		current = frontier.front();
		frontier.pop_front();
		explored.push_back(current.current_state);
	} 
	// current is our solution! print out initial, moves, and final state
	current.printHistory();
	return true;
}

int f_limit;

bool RBFS(node current, int & f_retval, node & n_retval) {
	if(current.current_state.isGoal()) {
		return true;
	}

	auto succs = current.current_state.successors();
	if(succs.size() == 0) {
		f_retval = INT_MAX;
		return false;
	}

	std::vector<node> nodes;
	for(auto s : succs) {
		//update moves
		auto moves = current.getMoves();
		int take, put;
		for(int peg = 0; peg < 3; peg++) {
			if(current.current_state.pegs[peg].size() + 1 == s.pegs[peg].size()) {
				take = peg;
			}
			else if(current.current_state.pegs[peg].size() - 1 == s.pegs[peg].size()) {
				put = peg;
			}
		}
		moves.push_back(std::make_pair(take, put));


		nodes.push_back(node(current.initial_state, s, current.getAdmissible(), false, moves));
		nodes.back().f_val = std::max(nodes.back().getCost(), current.f_val);
	}

	bool result = false;
	while(!result) {
		std::sort(nodes.begin(), nodes.end());
		node & best = nodes.back();
		if(best.f_val > f_limit) {
			f_retval = best.f_val;
			return false;
		}
		int second = nodes[nodes.size() - 2].f_val;
		f_limit = std::min(f_limit, second);
		result = RBFS(best, f_retval, n_retval);
		best.f_val = f_retval;
		f_limit = f_retval;
	}
	return true;
}


int _tmain(int argc, _TCHAR* argv[])
{
	state test = state(4, 4);
	aStar(test, true);
	aStar(test, false);

	int f_ret = INT_MAX;
	node n_ret = node(test, test, true, false);
	f_limit = INT_MAX;
	n_ret.f_val = n_ret.getCost();
	RBFS(n_ret, f_ret, n_ret);

	return 0;
}
