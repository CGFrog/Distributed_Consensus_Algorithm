#include <iostream>
#include "agent.h"
#include <vector>
#include <random>

int main() {
	// Declare size of network. SG 1
	// Create cyclic network with random values in user designated range.
	// std::thread so that all nodes run concurrently. SG 2
	// Achieve consensus. MVP Complete
	// Introduce Byzantine Agent. SG 3
	// Visual Element with SFML. SG 4

	std::vector<agent> network = {
		agent(1),
		agent(2),
		agent(3),
		agent(4),
		agent(5),
	};
	return 0;
}