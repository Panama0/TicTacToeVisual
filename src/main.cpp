#include "imgui.h"
#include "imgui-SFML.h"
#include "SFML/Graphics.hpp"


int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 800), "Window Title");
    ImGui::SFML::Init(window);

    sf::CircleShape shape(200.f, 100);
    shape.setFillColor(sf::Color(204, 77, 5)); // Color circle
    shape.setPosition(200, 200); // Center circle

    sf::Clock deltaClock;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            ImGui::SFML::ProcessEvent(window, event);
            if (event.type == sf::Event::Closed)
                window.close();
        }
        ImGui::SFML::Update(window, deltaClock.restart());

        ImGui::Begin("Window title");
        ImGui::Text("window text");
        ImGui::End();

        window.clear(sf::Color(18, 33, 43)); // Color background
        shape.setFillColor(sf::Color(204, 77, 5,32));
        window.draw(shape);

        ImGui::SFML::Render(window);
        window.display();
    }
    ImGui::SFML::Shutdown();
    return 0;
}
