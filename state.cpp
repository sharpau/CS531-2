
#include "stdafx.h"
#include "state.h"



// checking if states have already been explored
bool state::operator == (const state& cmp) const {
	for(int i = 0; i < pegs.size(); i++) {
		if(pegs[i] != cmp.pegs[i]) {
			return false;
		}
	}
	return true;
}

bool state::isGoal(void) {
	if(pegs[0].size() != num_disks) {
		return false;
	}
	for(int i = 0; i < pegs[0].size(); i++) {
		if(pegs[0][i] != i) {
			return false;
		}
	}
	return true;
};

std::vector<state> state::successors(void) {
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


state::state(const state &copy) : pegs(copy.pegs), num_disks(copy.num_disks) {};

state::state(int n, int problem) : num_disks(n) {
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

	static const int size5[20][5] = {
		{0,1,3,4,2},
		{2,3,4,1,0},
		{4,0,2,1,3},
		{2,1,4,0,3},
		{0,3,4,1,2},
		{3,0,1,4,2},
		{0,4,1,2,3},
		{3,4,2,1,0},
		{1,0,3,2,4},
		{0,4,2,1,3},
		{0,1,2,4,3},
		{3,2,0,1,4},
		{1,4,0,2,3},
		{1,0,3,4,2},
		{2,0,3,1,4},
		{1,2,0,3,4},
		{4,0,1,3,2},
		{1,2,3,4,0},
		{1,2,0,4,3},
		{4,3,1,0,2}};

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

	static const int size7[20][7] = {
		{5,4,6,2,0,3,1},
		{2,3,6,4,1,5,0},
		{0,6,2,3,5,4,1},
		{4,0,6,1,5,3,2},
		{6,3,4,2,1,0,5},
		{1,6,2,5,0,4,3},
		{2,3,6,5,0,1,4},
		{6,0,1,3,2,5,4},
		{4,0,3,1,2,6,5},
		{3,2,0,6,1,5,4},
		{1,3,0,6,4,2,5},
		{0,3,5,4,2,1,6},
		{4,1,0,6,2,3,5},
		{3,1,0,5,2,4,6},
		{5,2,1,3,4,0,6},
		{4,6,2,3,0,5,1},
		{2,4,6,3,1,5,0},
		{5,6,0,3,4,2,1},
		{1,2,5,6,3,0,4},
		{2,1,0,4,3,5,6}};

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
	case 5: 
		for(int i = 0; i < 5; i++) {
			pegs[0].push_back(size5[problem][i]);
		}
		break;
	case 6: 
		for(int i = 0; i < 6; i++) {
			pegs[0].push_back(size6[problem][i]);
		}
		break;
	case 7: 
		for(int i = 0; i < 7; i++) {
			pegs[0].push_back(size7[problem][i]);
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

void state::print(void) {
	std::cout << "A: ";
	for(auto i : pegs[0]) {
		std::cout << i << ", ";
	}
	std::cout << "\nB: ";
	for(auto i : pegs[1]) {
		std::cout << i << ", ";
	}
	std::cout << "\nC: ";
	for(auto i : pegs[2]) {
		std::cout << i << ", ";
	}
}