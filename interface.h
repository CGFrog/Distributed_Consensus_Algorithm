#pragma once
#include <SFML/Graphics.hpp>
#include "network.h"
#include <cmath>
#include <string>

class interface {
public:
	interface();
	void renderInterface(network&, std::vector<sf::CircleShape>&, sf::Font&);
	const unsigned int WINDOW_SIZE_X = 1200;
	const unsigned int WINDOW_SIZE_Y = 800;
	const float ZOOM_FACTOR = 1.f;
	const float min_zoom = 0.5f;
	const float max_zoom = 5.0f;
	

	int get_AmountAgents();
	void set_AmountAgents(int);
	void displayNodes(sf::RenderWindow&, std::vector<sf::CircleShape>&, network&, sf::Font&);
	void zoom_zoom(sf::RenderWindow& window, sf::View& view, sf::Event&);
	void set_agentsRendered();
	sf::Text initialGlobalAverage(sf::Font&, network&);

	sf::Text agentLabel(std::shared_ptr<agent>, sf::Font&);
	std::vector<sf::CircleShape> generateSystem(const network&);
	sf::CircleShape renderAgent();
	std::vector <sf::CircleShape> get_agentsRendered();
private:
	std::vector <sf::CircleShape> agentsRendered;
	int totalAgents;
};