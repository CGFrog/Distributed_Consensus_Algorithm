#include "agent.h"

agent::agent(double value) {
	setValue(value);
}

double agent::find_LocalAverage() {
	std::shared_ptr<agent> leftAgent = this->getLeftNeighbor();
	std::shared_ptr<agent> rightAgent = this->getRightNeighbor();
	return (leftAgent->getValue() + rightAgent->getValue() + this->getValue()) / 3;
}

void agent::setValue(double value) {
	this->value = value;
}

void agent::setLeftNeighbor(std::shared_ptr<agent> leftNeighbor) {
	this->leftNeighbor = leftNeighbor;
}

void agent::setRightNeighbor(std::shared_ptr<agent> rightNeighbor) {
	this->rightNeighbor = rightNeighbor;
}

double agent::getValue() { return value; }
std::shared_ptr<agent> agent::getLeftNeighbor() { return leftNeighbor; }
std::shared_ptr<agent> agent::getRightNeighbor() { return rightNeighbor; }

