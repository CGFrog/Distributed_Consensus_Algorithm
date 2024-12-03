#include "interface.h"

interface::interface() {
    renderInterface();
}

void interface::renderInterface() {
    sf::RenderWindow window(sf::VideoMode(WINDOW_SIZE_X, WINDOW_SIZE_Y), "Graphing Calculator - Ian Cooper");
    sf::View view = window.getDefaultView();
    view.zoom(ZOOM_FACTOR); // Set initial zoom level
    window.setView(view);
    while (window.isOpen())
    {
        zoom_zoom(window, view); // Controls viewport movement
        window.clear(sf::Color::Blue); //Sets background to blue
        window.setView(view); // Sets the viewport position
        window.display(); // Renders to screen
    }
}
void interface::zoom_zoom(sf::RenderWindow & window, sf::View & view) {
    sf::Event event;
    static bool is_dragging = false;
    static sf::Vector2i drag_start_pos;
    static float zoom_level = 1.0f;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
        if (event.type == sf::Event::KeyPressed){
            if (event.key.code == sf::Keyboard::Escape)
                window.close();
            }
        if (event.type == sf::Event::MouseWheelScrolled) {
            if (event.mouseWheelScroll.delta > 0 && zoom_level > min_zoom) {
               view.zoom(0.9f);
               zoom_level *= 0.9f;
            }
            else if (event.mouseWheelScroll.delta < 0 && zoom_level < max_zoom) {
                view.zoom(1.1f);
                zoom_level *= 1.1f;
            }
        }
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            is_dragging = true;
            drag_start_pos = sf::Mouse::getPosition(window);
        }
        if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
            is_dragging = false;
        }
        if (is_dragging) {
            sf::Vector2i current_pos = sf::Mouse::getPosition(window);
            sf::Vector2f offset(
            (drag_start_pos.x - current_pos.x) * view.getSize().x / window.getSize().x,
            (drag_start_pos.y - current_pos.y) * view.getSize().y / window.getSize().y);

            view.move(offset);
            drag_start_pos = current_pos;
            }
        window.setView(view);
    }
}