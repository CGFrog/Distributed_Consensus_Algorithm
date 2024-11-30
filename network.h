#pragma once
#include "agent.h"
#include <vector>
class network {
public:
	network() = default;
	network(int);
	void initNodes(int);
	std::vector<agent*> getSystem();
	int findRand();
	double getGlobalAvg();
private:
	int agents;
	double globalAverage = 0;
	std::vector<std::shared_ptr<agent>> system;
	int randLower = 0;
	int randHigher = 100;
};