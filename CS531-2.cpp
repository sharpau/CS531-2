// CS531-2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

class state {
	// each vector is a peg. index 0 is the bottom, and index size-1 is the top, accessible
	std::vector<std::vector<int>> pegs;

	int num_disks;
	int path_cost;
	bool admissible;

	// for sorting by heuristic
	int heuristicAdmissible(void) const {
		// number of disks in the incorrect location
		// never overestimates -> admissible
		int score = 0;
		for(int i = 0; i < num_disks; i++) {
			if(i >= pegs[0].size()) {
				score++;
			}
			else if(pegs[0][i] != i) {
				score++;
			}
		}
		return score;
	}

	int heuristicNonAdmissible(void) const {
		// right peg, wrong position = 1...wrong peg = 2
		// nonadmissible because it can overestimate
		int score = 0;
		for(int i = 0; i < num_disks; i++) {
			if(i >= pegs[0].size()) {
				score += 2;
			}
			else if(pegs[0][i] != i) {
				score++;
			}
		}
		return score;
	}

public:
	// compare f(n) = g(n) + h(n)
	// implemented as operator to take advantage of std::sort
	bool operator < (const state& cmp) const {
		if(admissible) {
			return (heuristicAdmissible() + path_cost) < (cmp.heuristicAdmissible() + path_cost);
		}
		else {
			return (heuristicNonAdmissible() + path_cost) < (cmp.heuristicNonAdmissible() + path_cost);
		}
	}

	// checking if states have already been explored
	bool operator == (const state& cmp) const {
		for(int i = 0; i < pegs.size(); i++) {
			if(pegs[i] != cmp.pegs[i]) {
				return false;
			}
		}
		return true;
	}

	void addPath() {
		path_cost++;
	}

	bool isGoal(void) {
		for(int i = 0; i < pegs[0].size(); i++) {
			if(pegs[0][i] != i) {
				return false;
			}
		}
		return true;
	};

	std::vector<state> successors(void) {
		std::vector<state> succs;
		for(int i = 0; i < pegs.size(); i++) {
			if(pegs[i].size() > 0) {
				for(int j = 0; j < pegs.size(); j++) {
					if(i != j) {
						state new_state_1 = *this;
						new_state_1.pegs[j].push_back(new_state_1.pegs[i].back());
						new_state_1.pegs[i].pop_back();

						succs.push_back(new_state_1);
					}
				}
			}
		}
		return succs;
	};


	state(const state &copy) : pegs(copy.pegs), num_disks(copy.num_disks), path_cost(copy.path_cost), admissible(copy.admissible) {};

	state(int n, int problem, bool heuristic) : num_disks(n), admissible(heuristic), path_cost(0) {
		// hard-coded problems for different sizes
		static const int size4[20][4] = {
			{2,0,1,3},
			{2,0,3,1},
			{2,3,1,0},
			{1,3,2,0},
			{1,2,3,0},
			{0,1,2,3},
			{3,1,2,0},
			{2,1,3,0},
			{1,3,0,2},
			{1,0,3,2},
			{0,2,1,3},
			{3,2,0,1},
			{1,2,0,3},
			{0,3,1,2},
			{3,1,0,2},
			{0,3,2,1},
			{3,0,2,1},
			{0,1,3,2},
			{2,3,0,1},
			{2,1,0,3}};

		static const int size6[20][6] = {
			{2,0,3,5,1,4},
			{2,1,4,5,3,0},
			{2,5,0,1,3,4},
			{5,0,3,4,1,2},
			{1,4,3,0,2,5},
			{4,3,0,5,2,1},
			{5,0,4,2,1,3},
			{3,4,1,2,0,5},
			{0,3,4,1,5,2},
			{0,3,1,5,2,4},
			{4,3,1,0,5,2},
			{2,1,0,3,4,5},
			{5,3,4,2,0,1},
			{2,5,3,4,1,0},
			{0,3,1,5,4,2},
			{1,2,4,0,3,5},
			{4,3,2,1,0,5},
			{4,1,0,5,3,2},
			{1,4,2,3,0,5},
			{1,4,3,2,0,5}};

		static const int size8[20][8] = {
			{5,7,3,0,2,4,1,6},
			{0,6,7,5,3,1,4,2},
			{7,1,2,3,4,6,5,0},
			{3,4,0,2,6,1,5,7},
			{3,7,6,0,4,1,5,2},
			{7,2,3,0,6,1,4,5},
			{3,4,6,5,2,1,7,0},
			{1,6,7,2,5,3,4,0},
			{5,4,3,2,6,7,1,0},
			{4,2,6,5,1,7,0,3},
			{1,6,0,5,7,3,2,4},
			{3,2,6,7,1,4,5,0},
			{4,3,7,0,5,1,2,6},
			{1,3,0,6,2,7,4,5},
			{1,4,0,3,7,2,6,5},
			{5,4,2,6,3,7,1,0},
			{2,4,3,5,7,6,0,1},
			{0,5,3,4,2,1,6,7},
			{5,4,6,1,7,0,3,2},
			{1,3,0,6,5,2,4,7}};

		static const int size10[20][10] = {
			{7,1,2,6,0,4,9,8,5,3},
			{6,3,9,4,8,1,2,5,0,7},
			{0,4,1,9,8,6,2,7,3,5},
			{3,4,7,6,9,2,8,0,5,1},
			{4,7,3,8,1,9,0,6,5,2},
			{0,2,3,7,8,6,4,5,1,9},
			{6,9,3,2,4,1,8,7,5,0},
			{5,9,7,4,1,8,3,2,0,6},
			{4,1,9,8,2,0,7,3,6,5},
			{9,7,1,0,3,6,4,2,5,8},
			{4,5,8,3,9,0,6,1,2,7},
			{2,4,0,7,8,6,5,9,3,1},
			{0,8,6,9,4,1,2,3,5,7},
			{0,8,6,7,1,2,3,4,9,5},
			{6,7,2,9,3,8,1,4,0,5},
			{2,0,1,4,8,9,7,3,6,5},
			{0,7,2,6,3,1,5,9,4,8},
			{1,3,4,5,6,9,8,7,2,0},
			{4,7,9,6,2,5,1,0,3,8},
			{3,6,8,5,7,9,0,1,2,4}};

		for(int i = 0; i < 3; i++) {
			pegs.push_back(std::vector<int>());
		}

		// initialize A with the selected size and problem
		switch(n) {
		case 4: 
			for(int i = 0; i < 4; i++) {
				pegs[0].push_back(size4[problem][i]);
			}
			break;
		case 6: 
			for(int i = 0; i < 6; i++) {
				pegs[0].push_back(size6[problem][i]);
			}
			break;
		case 8: 
			for(int i = 0; i < 8; i++) {
				pegs[0].push_back(size8[problem][i]);
			}
			break;
		case 10: 
			for(int i = 0; i < 10; i++) {
				pegs[0].push_back(size10[problem][i]);
			}
			break;
		}
	};
};


bool aStar(state initial) {
	std::vector<state> frontier;	
	std::vector<state> explored;
	explored.push_back(initial);
	state current = initial;

	while(!current.isGoal()) {
		// add current node to 
		auto succs = current.successors();
		for(auto succ : succs) {
			succ.addPath();
		}

		// make sure we haven't already looked at this successor - if we can't find it in explored, add to frontier
		for(int i = 0; i < succs.size(); i++) {
			if(std::find(explored.begin(), explored.end(), succs[i]) == explored.end()) {
				frontier.push_back(succs[i]);
			}
		}

		// find and expand best node
		if(frontier.size() == 0) {
			return false;
		}
		std::sort(frontier.begin(), frontier.end());
		current = frontier.back();
		frontier.pop_back();
		explored.push_back(current);
	} 
	return true;
}


int _tmain(int argc, _TCHAR* argv[])
{
	state test = state(4, 4, true);
	aStar(test);

	return 0;
}
