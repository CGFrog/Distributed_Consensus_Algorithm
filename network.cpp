#include "network.h"
#include <memory>
#include <random>
#include <iostream>
#include <ctime>
#include <chrono>

network::network(int agents) {
	this->agents = agents;
	initNodes(agents);
}
double network::getGlobalAvg() {
	return this->globalAverage;
}
int network::findRand() {
	std::random_device rd; 
	std::mt19937 generator(rd()); 
	std::uniform_int_distribution<int> distribution(randLower, randHigher);
	return distribution(generator);
}

void network::initNodes(int agents) {
	this->system.reserve(agents);
	for (int i = 0; i < agents; i++) {
		int randVal = findRand();
		this->system.emplace_back(std::make_shared<agent>(randVal));
		this->globalAverage = randVal + globalAverage;
		if (i != 0 && i != agents - 1) {
			system[i]->setLeftNeighbor(system[i - 1]);
			system[i-1]->setRightNeighbor(system[i]);
		}
		else if (i == agents-1) {
			system[i]->setLeftNeighbor(system[i - 1]);
			system[i]->setRightNeighbor(system[0]);
			system[i - 1]->setRightNeighbor(system[i]);
			system[0]->setLeftNeighbor(system[i]);
		}
	}
	this->globalAverage = globalAverage / agents;
}