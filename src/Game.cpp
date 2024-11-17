#include "Game.h"
#include "imgui.h"
#include "Utils.h"
#include "AiPlayer.h"
#include "SFML/Graphics.hpp"
#include <iostream>
#include <optional>




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
#define debug0
#ifdef debug1
		Board debugBoard = { {{{ Peices::O,		Peices::O,		Peices::empty }},
							  {{ Peices::X,		Peices::X,		Peices::empty }},
							  {{ Peices::empty,	Peices::empty,	Peices::empty }}}};;
		AiPlayer ai(&debugBoard);
		ai.makeMove();
#endif // debug1

		//temp?
		AiPlayer ai(&m_board);

		//process input
		handleInput();
		//update stuff

		//TODO: move the below
		if (m_turn == Peice::Peices::O)
		{
			ai.makeMove();
			//m_resources.addSpr(*getPath(Peice::Peices::O));
			m_turn = Peice::Peices::X;
		}
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
					if (m_turn == Peice::Peices::X && m_board[clickCoords.x][clickCoords.y].corePeice == Peice::Peices::empty)
					{
						placePeice(Peice::Peices::X, clickCoords);
						//the below line creates undefined behavoiur and i am not sure why
						//m_turn = Peice::Peices::O;
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
	//loop through the board and draw the peices found.
	for (int x{}; x < 3; x++)
	{
		for (int y{}; y < 3; y++)
		{
			//dont draw empty tiles
			if (m_board[x][y].corePeice != Peice::Peices::empty)
			{
				m_board[x][y].getSpr().setPosition(m_boardGrid[x][y]);
				m_window.draw(m_board[x][y].getSpr());
			}
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
			m_boardGrid[i][j] = { offset.x + i * (GridDim::spriteSize - GridDim::colWidth), offset.y + j * (GridDim::spriteSize - GridDim::colWidth) };
		}
	}

	//TODO:move to tileresources
	std::optional<std::string> path;
	if (path = getPath(Peice::Peices::tile))
	{
		m_resources.loadTiles(9, *path);
	}
	else
	{
		std::cerr << "Could not load texture!";
	}
}

//this thing sucks
void Game::placePeice(Peice::Peices peice, sf::Vector2i location)
{
	//TODO: not actually using the optional here lul
	//m_resources.addSpr(*getPath(peice));
	m_board[location.x][location.y].corePeice = peice;

	m_board[location.x][location.y].load(*getPath(peice));
}

std::optional<const char*> Game::getPath(Peice::Peices asset)
{
	switch (asset)
	{
	case Peice::Peices::X:
		return "./res/x.png";
		break;
	case Peice::Peices::O:
		return "./res/o.png";
		break;
	case Peice::Peices::tile:
		return "./res/sq.png";
		break;
	default:
		std::cerr << "Invalid asset, could not get path!";
		return std::nullopt;
		break;
	}
	return std::nullopt;
}
