#include "Game.h"
#include "imgui.h"

Game::Game()
	:m_window{ sf::RenderWindow(sf::VideoMode(1000, 1000), "Tic Tac Toe") }
{
	ImGui::SFML::Init(m_window);
}

void Game::run()
{
	while (m_window.isOpen())
	{
		//process input
		handleInput();
		//update stuff

		//draw stuff
		draw();
	}
}

void Game::handleInput()
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		ImGui::SFML::ProcessEvent(m_window, event);
		if (event.type == sf::Event::Closed)
			m_window.close();
	}
}

void Game::draw()
{	
	m_window.clear();
	drawUI();
	m_window.display();
}

void Game::drawUI()
{
	ImGui::SFML::Update(m_window, m_deltaClock.restart());

	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("Options"))
		{
			if (ImGui::MenuItem("New Game", "CTRL+R")) {}
			if (ImGui::MenuItem("Exit", "CTRL+R")) {}
			ImGui::EndMenu();
		}
		ImGui::EndMainMenuBar();
	}
	ImGui::SFML::Render(m_window);
}