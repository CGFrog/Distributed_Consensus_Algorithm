#pragma once
#include "agent.h"
#include <vector>
class network {
public:
	network() = default;
	network(int);
	void initNodes(int);
	std::vector<agent*> getSystem();
private:
	int agents;
	double globalAverage = 0;
	std::vector<agent*> system;
	int LOWER = 0;
	int HIGHER = 100;
};