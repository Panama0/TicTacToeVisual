#include "Game.h"
#include "imgui.h"
#include "Utils.h"
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
	:turn{Peice::X}
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
			sf::FloatRect CurrentTileBounds;
			sf::Vector2i clickCoords{};

			for (int i{}; i < 9; i++)
			{
				//check if click collides
				CurrentTileBounds = m_resources.tiles[i].getClickbox();
				if (CurrentTileBounds.contains(mousePos))
				{
					clickCoords = remap1Dto2D(i);
					if (turn == Peice::X && m_boardState[clickCoords.x][clickCoords.y] == Peice::empty)
					{
						//create a new spr for the X
						m_resources.addSpr(*getPath(Peice::X));
						//edit state
						placePeice(Peice::X, clickCoords);
						turn = Peice::O;
					}
				}
			}
		}
		if (event.type == sf::Event::MouseMoved)
		{
			sf::Vector2f mousePos{ static_cast<float>(event.mouseMove.x), static_cast<float>(event.mouseMove.y) };

			for (int i{}; i < 9; i++)
			{
				sf::FloatRect bounds{ m_resources.tiles[i].getClickbox()};
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
	drawPeices();
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
			if (ImGui::MenuItem("New Game")) {}
			if (ImGui::MenuItem("Exit")) {}
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

void Game::drawPeices()
{
	int counter{};
	for (int i{}; i < GridDim::gridSquares; i++)
	{
		sf::Vector2i remapI{ remap1Dto2D(i) };
				//test

		switch (m_boardState[remapI.x][remapI.y])
		{
		case Peice::X:
			m_resources.PeicesX[counter].sprite.setPosition(m_boardGrid[remapI.x][remapI.y]);
			m_window.draw(m_resources.PeicesX[counter].sprite);
			counter++;
			break;
		case Peice::O:
			m_resources.PeicesO[counter].sprite.setPosition(m_boardGrid[remapI.x][remapI.y]);
			m_window.draw(m_resources.PeicesO[counter].sprite);
			counter++;
			break;
		default:
			break;
		}
	}
}

void Game::loadBoard()
{
	const sf::Vector2f offset{ static_cast<float>(GridDim::colWidth + m_window.getSize().x/2 - (GridDim::gridSize * GridDim::spriteSize)/2),
							   static_cast<float>(GridDim::colWidth + m_window.getSize().y/2 - (GridDim::gridSize * GridDim::spriteSize)/2)};

	for (int i{}; i < 3; i++)
	{
		for (int j{}; j < 3; j++)
		{
			m_boardGrid[j][i] = { offset.x + i * (GridDim::spriteSize - GridDim::colWidth), offset.y + j * (GridDim::spriteSize - GridDim::colWidth) };
		}
	}

	//TODO:move to resman
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

void Game::placePeice(Peice peice, sf::Vector2i location)
{
	m_boardState[location.x][location.y] = peice;
}

std::optional<const char*> Game::getPath(Game::Peice asset)
{
	switch (asset)
	{
	case Game::X:
		return "./res/x.png";
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
