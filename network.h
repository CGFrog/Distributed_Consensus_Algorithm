#pragma once
#include "agent.h"
#include <vector>
#include <memory>
#include <random>
#include <iostream>
#include <chrono>
#include <thread>
#include <functional>
#include <barrier>
class network {
public:
	network() = default;
	network(int);
	void initNodes(int);
	int findRand();
	double getGlobalAvg();
	void activateNetwork(int);
	void deactivateNetwork();
	double calculateGlobalAvg();
	void printErrorRange();
	void printNodeVals();
private:
	int agents;
	double globalAverage = 0;
	std::vector<std::shared_ptr<agent>> system;
	int randLower = 0;
	int randHigher = 100;
	std::vector<std::thread> consensus;
};