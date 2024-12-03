#include "interface.h"
#define pi 3.14159265
interface::interface() {
    sf::Font font;
    if (!font.loadFromFile("font.ttf")) {
        throw std::runtime_error("Font cannot be found");
    }
    int totalAgents = 50;
    network currentNetwork(totalAgents);
    std::thread t(&network::activateNetwork, &currentNetwork);
    std::vector <sf::CircleShape> visuals = generateSystem(currentNetwork);
    renderInterface(currentNetwork, visuals);
    currentNetwork.disableAgents();
    currentNetwork.deactivateNetwork();
    t.join();
}

void interface::displayNodes(sf::RenderWindow& window, std::vector<sf::CircleShape>& visuals) {
    for (size_t i = 0; i < visuals.size(); i++) {
        visuals[i].setPosition(WINDOW_SIZE_X / 2 + 50 * cos(i * pi / 25), 50 * sin(i * pi / 25) + WINDOW_SIZE_Y / 2); // Adjust if needed
        window.draw(visuals[i]);
    }
}

void interface::renderInterface(network& currentNetwork, std::vector<sf::CircleShape>& visuals) {
    sf::RenderWindow window(sf::VideoMode(WINDOW_SIZE_X, WINDOW_SIZE_Y), "Distributed System Simulation");
    sf::View view = window.getDefaultView();
    view.zoom(ZOOM_FACTOR);
    window.setView(view);
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            zoom_zoom(window, view, event); // Pass event here
        }
        window.clear(sf::Color::Blue);
        displayNodes(window, visuals);
        window.setView(view);
        window.display();
    }
}

void interface::zoom_zoom(sf::RenderWindow& window, sf::View& view, sf::Event& event) {
    static bool is_dragging = false;
    static sf::Vector2i drag_start_pos;
    static float zoom_level = 1.0f;
    if (event.type == sf::Event::MouseWheelScrolled) {
        if (event.mouseWheelScroll.delta > 0 && zoom_level > min_zoom) {
            view.zoom(0.9f);
            zoom_level *= 0.9f;
        }
        else if (event.mouseWheelScroll.delta < 0 && zoom_level < max_zoom) {
            view.zoom(1.1f);
            zoom_level *= 1.1f;
        }
        zoom_level = std::clamp(zoom_level, min_zoom, max_zoom);
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
        const float sensitivity = 1.0f / zoom_level; 
        sf::Vector2f offset(
            (drag_start_pos.x - current_pos.x) * view.getSize().x / (window.getSize().x * sensitivity),
            (drag_start_pos.y - current_pos.y) * view.getSize().y / (window.getSize().y * sensitivity)
        );
        view.move(offset);
        drag_start_pos = current_pos;
    }
    window.setView(view);
}

sf::CircleShape interface::renderAgent() {
    sf::CircleShape shape(2);
    shape.setFillColor(sf::Color(150, 50, 250));
    shape.setOutlineThickness(.2);
    shape.setOutlineColor(sf::Color(250, 150, 100));
    return shape;
}

std::vector<sf::CircleShape> interface::generateSystem(const network& currentNetwork) {
    std::vector <sf::CircleShape> agentsRendered;
    agentsRendered.reserve(50);
    for (int i = 0; i < 50; i++) {
        agentsRendered.emplace_back(renderAgent());
    }
    return agentsRendered;
}

