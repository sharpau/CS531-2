// CS531-2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "state.h"
#include "node.h"

extern unsigned long long heuristic_time;

struct result {
	node final_node; // contains initial state, final state, moves, success/fail
	unsigned long long cpu_total;
	unsigned long long cpu_heuristic;

	result(node final_n, unsigned long long heur_t, unsigned long long cpu_t) : final_node(final_n), cpu_total(cpu_t), cpu_heuristic(heur_t) {};
};


node aStar(state initial, bool admissible) {
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
			return current;
		}
		std::sort(frontier.begin(), frontier.end());
		current = frontier.front();
		frontier.pop_front();
		explored.push_back(current.current_state);
	} 
	// current is our solution! print out initial, moves, and final state
	current.printHistory();
	current.solved = true;
	return current;
}

node RBFS(node current, int f_limit, int & f_retval) {
	if(current.current_state.isGoal()) {
		current.printHistory();
		current.solved = true;
		return current;
	}

	auto succs = current.current_state.successors();
	if(succs.size() == 0) {
		f_retval = INT_MAX;
		return current;
	}

	std::deque<node> nodes;
	for(auto s : succs) {
		//update moves
		auto moves = current.getMoves();
		int take, put;
		for(int peg = 0; peg < 3; peg++) {
			if(current.current_state.pegs[peg].size() + 1 == s.pegs[peg].size()) {
				put = peg;
			}
			else if(current.current_state.pegs[peg].size() - 1 == s.pegs[peg].size()) {
				take = peg;
			}
		}
		moves.push_back(std::make_pair(take, put));


		nodes.push_back(node(current.initial_state, s, current.getAdmissible(), false, moves));
		nodes.back().f_val = std::max(nodes.back().getCost(), current.f_val);
	}

	node returned = current;
	while(!returned.solved) {
		std::sort(nodes.begin(), nodes.end());
		node & best = nodes.front();
		if(best.f_val > f_limit) {
			f_retval = best.f_val;
			return returned;
		}
		int second = nodes[1].f_val;
		returned = RBFS(best, std::min(f_limit, second), f_retval);
		best.f_val = f_retval;
	}
	// something was returned with solved == true, pass it up the call stack
	return returned;
}

node RBFS_start(state initial, bool admissible) {
	int f_ret;
	return RBFS(node(initial, initial, admissible, false), INT_MAX, f_ret);
}


int _tmain(int argc, _TCHAR* argv[])
{
	/*state test = state(4, 4);
	aStar(test, true);
	aStar(test, false);

	int f_ret = INT_MAX;
	node n_ret = node(test, test, false, false);
	n_ret.f_val = n_ret.getCost();
	RBFS(n_ret, INT_MAX, f_ret, n_ret);*/

	std::vector<result> astar_results;
	std::vector<result> rbfs_results;

	// permutations of inputs
	bool heur_vals[2] = {true, false};
	int size_vals[4] = {4, 5, 6, 7};

	for(auto hv : heur_vals) {
		for(auto sz : size_vals) {
			for(int prob_num = 0; prob_num < 20; prob_num++) {
				heuristic_time = 0;
				state initial = state(sz, prob_num);
				clock_t a_start = clock();
				node a_solution = aStar(initial, hv);
				astar_results.push_back(result(a_solution, heuristic_time, clock() - a_start));
				
				heuristic_time = 0;
				clock_t b_start = clock();
				node b_solution = RBFS_start(initial, hv);
				rbfs_results.push_back(result(b_solution, heuristic_time, clock() - b_start));

			}
		}
	}


	return 0;
}
