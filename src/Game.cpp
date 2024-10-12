#include "Game.h"
#include "ResourceManager.h"
#include "imgui.h"
#include "SFML/Graphics.hpp"
#include <iostream>

Game::Game()
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	m_window.create(sf::VideoMode(1000, 1000), "Tic Tac Toe", 7U, settings);
	ImGui::SFML::Init(m_window);

	loadBoard();
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
		if (event.type == sf::Event::Closed)
			m_window.close();
		ImGui::SFML::ProcessEvent(m_window, event);
	}
}

void Game::draw()
{	
	m_window.clear({120,120,120});
	drawBoard();
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

void Game::drawBoard()
{
	{
		int k{};
		for (int i{}; i < 3; i++)
		{
			for (int j{}; j < 3; j++)
			{
				m_tiles[k].sprite.setPosition(m_boardGrid[i][j]);
				m_window.draw(m_tiles[k].sprite);
				k++;
			}
		}
	}
}

void Game::loadBoard()
{
	const int colWidth{ 25 };
	const int sprSize{ 256 };
	const int gridSize{ 3 };

	const sf::Vector2f offset{ static_cast<float>(colWidth + m_window.getSize().x/2 - (gridSize * sprSize)/2),
							   static_cast<float>(colWidth + m_window.getSize().y/2 - (gridSize * sprSize)/2)};

	for (int i{}; i < 3; i++)
	{
		for (int j{}; j < 3; j++)
		{
			m_boardGrid[i][j] = { offset.x + i * (sprSize - colWidth), offset.y + j * (sprSize - colWidth) };
		}
	}

	for (int i{}; i < 9; i++)
	{
		m_tiles[i].loadTexture("./res/sq.png");
	}
}