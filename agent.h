#pragma once
#include "agent.h"
#include <memory>
#include <thread>
#include <chrono>
#include <functional>
class agent {
public:
	agent() = default;
	agent(double);
	void setValue(double);
	void setLeftNeighbor(std::shared_ptr<agent>);
	void setRightNeighbor(std::shared_ptr<agent>);
	double getValue();
	std::shared_ptr<agent> getLeftNeighbor();
	std::shared_ptr<agent> getRightNeighbor();
	void findLocalAverage(int iter);


private:
	double value;
	std::shared_ptr<agent> leftNeighbor;
	std::shared_ptr<agent> rightNeighbor;
};