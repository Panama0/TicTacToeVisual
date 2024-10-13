#include "Game.h"
#include "imgui.h"
#include "SFML/Graphics.hpp"
#include <iostream>
#include <optional>

enum Game::Peice
{
	empty,
	X,
	O,
	tile,
};


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
		if (event.type == sf::Event::MouseButtonReleased)
		{
			sf::Vector2f mousePos{ static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y) };

			for (int i{}; i < 9; i++)
			{
				sf::FloatRect bounds{ m_resources.tiles[i].sprite.getGlobalBounds()};
				bounds.height -= grid.colWidth*2;
				bounds.width -= grid.colWidth*2;
				bounds.left += grid.colWidth;
				bounds.top += grid.colWidth;
				if (bounds.contains(mousePos))
				{
					std::cout << i;
				}

			}
		}
		if (event.type == sf::Event::MouseMoved)
		{
			sf::Vector2f mousePos{ static_cast<float>(event.mouseMove.x), static_cast<float>(event.mouseMove.y) };

			for (int i{}; i < 9; i++)
			{
				//TODO: surely we can make this use the gridpos member var instrad of all this bounds checking
				sf::FloatRect bounds{ m_resources.tiles[i].sprite.getGlobalBounds() };
				bounds.height -= grid.colWidth * 2;
				bounds.width -= grid.colWidth * 2;
				bounds.left += grid.colWidth;
				bounds.top += grid.colWidth;
				if (bounds.contains(mousePos))
				{
					m_resources.highlight.setSize({ bounds.height, bounds.width });
					m_resources.highlight.setPosition(bounds.getPosition());
					m_resources.highlight.setFillColor({ 0,0,255,10 });
					break;
				}
				else
				{
					m_resources.highlight.setFillColor({ 0,0,0,0 });
				}

			}
		}

		if (event.type == sf::Event::Closed)
		{
			m_window.close();
		}
		ImGui::SFML::ProcessEvent(m_window, event);
	}
}

void Game::draw()
{	
	m_window.clear({120,120,120});
	drawBoard();
	drawUI();
	m_window.draw(m_resources.highlight);
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
				//TODO: move the set pos to some kind of update
				m_resources.tiles[k].sprite.setPosition(m_boardGrid[i][j]);
				m_window.draw(m_resources.tiles[k].sprite);
				k++;
			}
		}
	}
}

void Game::loadBoard()
{


	const sf::Vector2f offset{ static_cast<float>(grid.colWidth + m_window.getSize().x/2 - (grid.gridSize * grid.spriteSize)/2),
							   static_cast<float>(grid.colWidth + m_window.getSize().y/2 - (grid.gridSize * grid.spriteSize)/2)};

	for (int i{}; i < 3; i++)
	{
		for (int j{}; j < 3; j++)
		{
			m_boardGrid[i][j] = { offset.x + i * (grid.spriteSize - grid.colWidth), offset.y + j * (grid.spriteSize - grid.colWidth) };
		}
	}

	std::optional<std::string> path;
	if (path = getPath(Peice::tile))
	{
		m_resources.loadTiles(9, *path);
	}
	else
	{
		std::cerr << "Could not load texture!";
	}
}

std::optional<const char*> Game::getPath(Game::Peice asset)
{
	switch (asset)
	{
	case Game::X:
		break;
	case Game::O:
		return "./res/o.png";
		break;
	case Game::tile:
		return "./res/sq.png";
		break;
	default:
		std::cerr << "Invalid asset, could not get path!";
		return std::nullopt;
		break;
	}
	return std::nullopt;
}
