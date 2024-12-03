#pragma once
#include <SFML/Graphics.hpp>

class interface {
public:
	interface() = default;
	void renderInterface();
	const unsigned int WINDOW_SIZE_X = 800;
	const unsigned int WINDOW_SIZE_Y = 600;
	const float ZOOM_FACTOR = .05f;
	const float min_zoom = 0.5f;
	const float max_zoom = 10.0f;

	void zoom_zoom(sf::RenderWindow& window, sf::View& view);
private:

};