#include "network.h"

network::network(int agents) : agents(agents), barrier(agents) {
	initNodes(agents);
}

double network::getGlobalAvg() {
	return this->globalAverage;
}
int network::findRand() {
	std::random_device rd; 
	std::mt19937 generator(rd()); 
	std::uniform_int_distribution<int> distribution(randLower, randHigher);
	return distribution(generator); // Simple random number generator, not the greatest but it will do for this project.
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

void network::activateNetwork() {
	this->consensus.reserve(system.size());
	for (auto& sys : system) {
		std::cout << "thread created" << std::endl;
		consensus.emplace_back(std::thread(&agent::findLocalAverage, sys, std::ref(barrier)));
	}
	std::cout << "Here" << std::endl;
}

std::vector<std::shared_ptr<agent>> network::get_distSystem() {return system;}

void network::disableAgents() {
	for (int i = 0; i < system.size(); i++) {
		//std::cout << "Disabled" << std::endl;
		system[i]->set_Working(false);
	}
}

void network::deactivateNetwork() {
	for (int i = 0; i < consensus.size(); i++) {
		consensus[i].join();
	}
}

double network::calculateGlobalAvg() {
	double globalAvgC = 0;
	for (int i = 0; i < agents; i++) {
		globalAvgC = system[i]->getValue() + globalAvgC;
	}
	return globalAvgC / agents;
}

void network::printNodeVals() {
	for (auto i : system) {
		std::cout << i->getValue() << " | ";
	}
	std::cout << std::endl;
}
