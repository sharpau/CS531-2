// CS531-2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "state.h"
#include "node.h"


bool aStar(state initial, bool admissible) {
	std::vector<node> frontier;	
	std::vector<state> explored;
	explored.push_back(initial);
	node current = node(initial, admissible, false, 0);

	while(!current.this_state.isGoal()) {
		// add current node to 
		auto succs = current.this_state.successors();

		// make sure we haven't already looked at this successor - if we can't find it in explored, add to frontier
		for(int i = 0; i < succs.size(); i++) {
			if(std::find(explored.begin(), explored.end(), succs[i]) == explored.end()) {
				frontier.push_back(node(succs[i], admissible, false, current.getPath()));
			}
		}

		// find and expand best node
		if(frontier.size() == 0) {
			return false;
		}
		std::sort(frontier.begin(), frontier.end());
		current = frontier.back();
		frontier.pop_back();
		explored.push_back(current.this_state);
	} 
	return true;
}


int _tmain(int argc, _TCHAR* argv[])
{
	state test = state(4, 4);
	aStar(test, true);
	aStar(test, false);

	return 0;
}
