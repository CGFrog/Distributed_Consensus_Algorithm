#include "agent.h"

agent::agent(double value) {setValue(value);}
void agent::findLocalAverage(int iter) {
	std::shared_ptr<agent> leftAgent = this->getLeftNeighbor();
	std::shared_ptr<agent> rightAgent = this->getRightNeighbor();
	for (int i = 0; i < iter;i++) {
		setValue((leftAgent->getValue() + rightAgent->getValue() + this->getValue()) / 3);
		std::this_thread::sleep_for(std::chrono::seconds(0));
	}
}

void agent::setValue(double value) {this->value = value;}
void agent::setLeftNeighbor(std::shared_ptr<agent> leftNeighbor) {this->leftNeighbor = leftNeighbor;}
void agent::setRightNeighbor(std::shared_ptr<agent> rightNeighbor) {this->rightNeighbor = rightNeighbor;}
double agent::getValue() { return value; }
std::shared_ptr<agent> agent::getLeftNeighbor() { return leftNeighbor; }
std::shared_ptr<agent> agent::getRightNeighbor() { return rightNeighbor; }

