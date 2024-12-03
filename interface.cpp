#include "interface.h"
#define pi 3.14159265
interface::interface() {
    sf::Font font;
    if (!font.loadFromFile("font.ttf")) {
        throw std::runtime_error("Font cannot be found");
    }
    set_AmountAgents(100);
    network currentNetwork(totalAgents);
    std::thread t(&network::activateNetwork, &currentNetwork);
    std::vector <sf::CircleShape> visuals = generateSystem(currentNetwork);
    renderInterface(currentNetwork, visuals, font);
    currentNetwork.disableAgents();
    currentNetwork.deactivateNetwork();
    t.join();
}

int interface::get_AmountAgents() { return totalAgents; }
void interface::set_AmountAgents(int totalAgents) { this->totalAgents = totalAgents; }

sf::Text interface::initialGlobalAverage(sf::Font& font, network& currentNetwork) {
    std::string valueStr = std::to_string(currentNetwork.calculateGlobalAvg());
    sf::Text globalAverage;
    globalAverage.setFont(font);
    globalAverage.setString(valueStr);
    int originalSize = 50;
    globalAverage.setCharacterSize(static_cast<unsigned int>(originalSize * 0.75));
    globalAverage.setFillColor(sf::Color::White);
    globalAverage.setOutlineColor(sf::Color::Black);
    globalAverage.setOutlineThickness(1);
    return globalAverage;
}

sf::Text interface::agentLabel(std::shared_ptr<agent> agent, sf::Font& font) {
    std::string valueStr = std::to_string(agent->getValue());
    sf::Text agentVal;
    agentVal.setFont(font);
    agentVal.setString(valueStr);
    int originalSize = 20;
    agentVal.setCharacterSize(static_cast<unsigned int>(originalSize * 0.75));
    agentVal.setFillColor(sf::Color::White);
    agentVal.setOutlineColor(sf::Color::Black);
    agentVal.setOutlineThickness(1);

    sf::FloatRect textBounds = agentVal.getLocalBounds();
    float textCenterX = textBounds.left + textBounds.width / 2.0f;
    float textCenterY = textBounds.top + textBounds.height / 2.0f;
    return agentVal;
}

void interface::displayNodes(sf::RenderWindow& window, std::vector<sf::CircleShape>& visuals, network& currentNetwork, sf::Font& font) {
    std::vector<std::shared_ptr<agent>> distAgents = currentNetwork.get_distSystem();
    size_t numCircles = visuals.size();

    for (size_t i = 0; i < numCircles; i++) {
        visuals[i].setPosition(WINDOW_SIZE_X / 2 + 500 * cos(i * pi / (totalAgents/2)), 500 * sin(i * pi / (totalAgents/2)) + WINDOW_SIZE_Y / 2);
        sf::Text agentVal = agentLabel(distAgents[i], font);

        sf::FloatRect textBounds = agentVal.getLocalBounds();
        float textCenterX = textBounds.left + textBounds.width / 2.0f;
        float textCenterY = textBounds.top + textBounds.height / 2.0f;

        sf::Vector2f circleCenter = visuals[i].getPosition();
        circleCenter.x += visuals[i].getRadius();
        circleCenter.y += visuals[i].getRadius();
        agentVal.setPosition(circleCenter.x - textCenterX, circleCenter.y - textCenterY);
        
        size_t leftNeighborIndex = (i == 0) ? numCircles - 1 : i - 1;
        sf::Vector2f leftNeighborPos = visuals[leftNeighborIndex].getPosition();
        leftNeighborPos.x += visuals[leftNeighborIndex].getRadius();
        leftNeighborPos.y += visuals[leftNeighborIndex].getRadius();

        sf::VertexArray lineToLeft(sf::Lines, 2);
        lineToLeft[0].position = circleCenter;
        lineToLeft[1].position = leftNeighborPos;

        lineToLeft[0].color = sf::Color(255, i * 10 % 256, 128);
        lineToLeft[1].color = lineToLeft[0].color;
        

        size_t rightNeighborIndex = (i == numCircles - 1) ? 0 : i + 1;
        sf::Vector2f rightNeighborPos = visuals[rightNeighborIndex].getPosition();
        rightNeighborPos.x += visuals[rightNeighborIndex].getRadius();
        rightNeighborPos.y += visuals[rightNeighborIndex].getRadius();

        sf::VertexArray lineToRight(sf::Lines, 2);
        lineToRight[0].position = circleCenter;
        lineToRight[1].position = rightNeighborPos;

        lineToRight[0].color = sf::Color(0, 255, i * 20 % 256);
        lineToRight[1].color = lineToRight[0].color;
        window.draw(lineToLeft);
        window.draw(lineToRight);
        window.draw(visuals[i]);
        window.draw(agentVal);

    }
}


void interface::renderInterface(network& currentNetwork, std::vector<sf::CircleShape>& visuals, sf::Font& font) {
    sf::RenderWindow window(sf::VideoMode(WINDOW_SIZE_X, WINDOW_SIZE_Y), "Distributed System Simulation");
    sf::View view = window.getDefaultView();
    view.zoom(ZOOM_FACTOR);
    window.setView(view);
    sf::Text initGlobalAverage = initialGlobalAverage(font, currentNetwork);
    initGlobalAverage.setPosition((WINDOW_SIZE_X / 2)-50, (WINDOW_SIZE_Y / 2) - 50);
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            zoom_zoom(window, view, event); // Pass event here
        }
        window.clear(sf::Color::Black);
        displayNodes(window, visuals, currentNetwork, font);
        window.draw(initGlobalAverage);
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
    sf::CircleShape shape(20);
    shape.setFillColor(sf::Color(150, 50, 250));
    shape.setOutlineThickness(5);
    shape.setOutlineColor(sf::Color(250, 150, 100));
    return shape;
}

std::vector<sf::CircleShape> interface::generateSystem(const network& currentNetwork) {
    std::vector <sf::CircleShape> agentsRendered;
    agentsRendered.reserve(totalAgents);
    for (int i = 0; i < totalAgents; i++) {
        agentsRendered.emplace_back(renderAgent());
    }
    return agentsRendered;
}

