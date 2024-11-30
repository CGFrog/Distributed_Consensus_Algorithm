#include <iostream>
#include "agent.h"
#include <vector>
#include "network.h"
#include <string>

int networkSize() {
	bool invalidNS = true;
	std::cout << "Enter network size between 1-20: " << std::endl;
	while (invalidNS) {
		std::string user_input;
		std::getline(std::cin, user_input);
		int network_size = stoi(user_input);
		if (network_size>0 && network_size < 20) return network_size;
	}
}

int main() {
	// Declare size of network. SG 1 DONE
	// Create cyclic network with random values in user designated range. DONE
	// std::thread so that all nodes run concurrently. SG 2
	// Achieve consensus. MVP Complete
	// Introduce Byzantine Agent. SG 3
	// Visual Element with SFML. SG 4

	network network(networkSize());
	double startAvg = network.getGlobalAvg();
	std::cout << "The global average is " << startAvg;
	network.activateNetwork(3);
	std::cout << "Simulation Complete. New Global Average is " << network.calculateGlobalAvg() << std::endl;
	return 0;
}