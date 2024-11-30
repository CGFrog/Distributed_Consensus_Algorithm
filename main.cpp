#include <iostream>
#include "agent.h"
#include <vector>
#include "network.h"
#include <string>
#include <cmath>

int networkSize() {
	std::cout << "Enter network size between 3-50: " << std::endl;
	while (true) {
		std::string user_input;
		std::getline(std::cin, user_input);
		int network_size = stoi(user_input);
		if (network_size>2 && network_size <= 50) return network_size;
	}
	return 3;
}

void runSimulation() {
	network network(networkSize());
	double startAvg = network.getGlobalAvg();
	network.printNodeVals();
	std::cout << "The global average is " << startAvg << std::endl;
	network.activateNetwork(1000);
	std::cout << "Simulation Complete." << std::endl;
	network.printNodeVals();
}

int main() {
	// Declare size of network. SG 1 DONE
	// Create cyclic network with random values in user designated range. DONE
	// std::thread so that all nodes run concurrently. SG 2 DONE
	// Achieve consensus. MVP Complete DONE
	// Introduce Byzantine Agent. SG 3
	// Visual Element with SFML. SG 4
	runSimulation();
	return 0;
}