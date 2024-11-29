#include "network.h"
#include <memory>
#include <random>
network::network(int agents) {
	this->agents = agents;
}
void network::initNodes(int agents) {
	this->system.reserve(agents);
	std::seed_seq seed{ 42 };
	std::mt19937 rng(seed);
	std::uniform_int_distribution<int> dist(LOWER, HIGHER);
	for (int i = 0; i < agents; i++) {
		int randVal = dist(rng);
		this->system.emplace_back(new agent(randVal));
		this->globalAverage = randVal + globalAverage;
		if (i != 0 && i != agents - 1) {
			system[i]->setLeftNeighbor(std::make_shared<agent>(system[i-1]));
			system[i-1]->setRightNeighbor(std::make_shared<agent>(system[i]));
		}
		else if (i == agents-1) {
			system[i]->setLeftNeighbor(std::make_shared<agent>(system[i - 1]));
			system[i]->setRightNeighbor(std::make_shared<agent>(system[0]));
			system[i - 1]->setRightNeighbor(std::make_shared<agent>(system[i]));
			system[0]->setLeftNeighbor(std::make_shared<agent>(system[i]));
		}
	}
	this->globalAverage = globalAverage / agents;
}