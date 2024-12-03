#pragma once
#include <SFML/Graphics.hpp>
#include "network.h"
#include <cmath>
class interface {
public:
	interface();
	void renderInterface(network&, std::vector<sf::CircleShape>&);
	const unsigned int WINDOW_SIZE_X = 800;
	const unsigned int WINDOW_SIZE_Y = 600;
	const float ZOOM_FACTOR = .1f;
	const float min_zoom = 0.5f;
	const float max_zoom = 10.0f;
	


	void displayNodes(sf::RenderWindow&, std::vector<sf::CircleShape>&);
	void zoom_zoom(sf::RenderWindow& window, sf::View& view, sf::Event&);
	void set_agentsRendered();
	void displayInitialGlobalAverage(sf::RenderWindow&);


	std::vector<sf::CircleShape> generateSystem(const network&);
	sf::CircleShape renderAgent();
	std::vector <sf::CircleShape> get_agentsRendered();
private:
	std::vector <sf::CircleShape> agentsRendered;
	sf::Text initialGlobalAverage;
	sf::Text currentGlobalAverage;

};