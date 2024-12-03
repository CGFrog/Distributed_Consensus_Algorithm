#include "agent.h"

agent::agent(double value) {setValue(value);}

void agent::findLocalAverage(std::barrier<>& sync_point) {
    std::this_thread::sleep_for(std::chrono::milliseconds(10000));
    while(working){
        double newValue = (getLeftNeighbor()->getValue() + getRightNeighbor()->getValue() + getValue()) / 3;
        sync_point.arrive_and_wait(); // Arrive and wait signals to the thread that it needs to hold on until the other threads have finished their iterations.
        setValue(newValue);
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
        sync_point.arrive_and_wait();
    }
}

bool agent::get_Working() { return working;  }
void agent::set_Working(bool working) { this->working = working; }

void agent::setValue(double value) {
    std::lock_guard<std::mutex> lock(mtx); //When a thread calls this lockguard it is saying to the other threads, this is mine, dont mess with it until im done.
	this->value = value;
}
void agent::setLeftNeighbor(std::shared_ptr<agent> leftNeighbor) {this->leftNeighbor = leftNeighbor;}
void agent::setRightNeighbor(std::shared_ptr<agent> rightNeighbor) {this->rightNeighbor = rightNeighbor;}

double agent::getValue() {
    std::lock_guard<std::mutex> lock(mtx);
    return value; 
}

std::shared_ptr<agent> agent::getLeftNeighbor() { return leftNeighbor; }
std::shared_ptr<agent> agent::getRightNeighbor() { return rightNeighbor; }