#include "Game.h"
#include "imgui.h"
#include "Utils.h"
#include "BoardSquare.h"
#include "Board.h"
#include "AiPlayer.h"
#include "GridDim.h"
#include "SFML/Graphics.hpp"
#include <iostream>
#include <optional>
#include <chrono>




Game::Game()
    :m_AiPlayer{m_board}
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    m_window.create(sf::VideoMode(1000, 1000), "Tic Tac Toe", 7U, settings);
    ImGui::SFML::Init(m_window);

    loadBoard();
}

void Game::run()
{
    m_board.loadDebug();
    auto a = m_AiPlayer.createFork(m_playerPeice);

    while (m_window.isOpen())
    {
        //process input - player move
        handleInput();
        // make ai move if it is its turn and game is still going
        if (m_turn == BoardSquare::Peices::O && m_winner == std::nullopt)
        {
            makeAiMove();
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
                CurrentTileBounds = m_board.getClickbox(i);
                if (CurrentTileBounds.contains(mousePos))
                {
                    clickCoords = Utils::remap1Dto2D(i);
                    if (m_turn == BoardSquare::Peices::X && m_board.getState(clickCoords) == BoardSquare::Peices::empty)
                    {
                        placePeice(BoardSquare::Peices::X, clickCoords);
                        m_turn = BoardSquare::Peices::O;
                        break;
                    }
                    else
                    {
                        break;
                    }
                }
            }
        }
        if (event.type == sf::Event::MouseMoved)
        {
            sf::Vector2f mousePos{ static_cast<float>(event.mouseMove.x), static_cast<float>(event.mouseMove.y) };

            for (int i{}; i < 9; i++)
            {
                sf::FloatRect bounds{ m_board.getClickbox(i) };
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
            if (ImGui::MenuItem("New Game"))
            {
                reset();
            }
            if (ImGui::MenuItem("Exit"))
            {
                m_window.close();
            }
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }
    ImGui::SFML::Render(m_window);
}

void Game::drawBoard()
{
    for (int x{}, k{}; x < 3; x++, k++)
    {
        for (int y{}; y < 3; y++)
        {
            //TODO: move the set pos to some kind of update
            m_resources.tiles[k].sprite.setPosition(m_board.getPosition({x,y}));
            m_window.draw(m_resources.tiles[k].sprite);
        }
    }
}

void Game::drawPeices()
{
    for (int x{}; x < 3; x++)
    {
        for (int y{}; y < 3; y++)
        {
            //dont draw empty tiles
            if (m_board.getState({x,y}) != BoardSquare::Peices::empty)
            {
                m_window.draw(m_board.getSpr({x,y}));
            }
        }
    }
}

void Game::loadBoard()
{
    const sf::Vector2f offset{ static_cast<float>(GridDim::colWidth + m_window.getSize().x/2 - (GridDim::gridSize * GridDim::spriteSize)/2),
                               static_cast<float>(GridDim::colWidth + m_window.getSize().y/2 - (GridDim::gridSize * GridDim::spriteSize)/2)};

    for (int y{}; y < 3; y++)
    {
        for (int x{}; x < 3; x++)
        {
            m_board.setPosition({ x,y }, { offset.x + x * (GridDim::spriteSize - GridDim::colWidth),
                                           offset.y + y * (GridDim::spriteSize - GridDim::colWidth) });
        }
    }

    //TODO:move to tileresources
    std::optional<std::string> path;
    if (path = getPath(BoardSquare::Peices::tile))
    {
        m_resources.loadTiles(9, *path);
    }
    else
    {
        std::cerr << "Could not load texture!";
    }
}

void Game::placePeice(BoardSquare::Peices peice, sf::Vector2i location)
{
    //TODO: not actually using the optional here lul
    m_board.setState(location, peice);
    m_board.load(location, *getPath(peice));
    
    
    m_turnCount++;
    m_winner = checkVictory();
    if (m_winner == BoardSquare::Peices::X)
    {
        std::cout << "X won";
    }
    else if (m_winner == BoardSquare::Peices::O)
    {
        std::cout << "O won";
    }
}

void Game::makeAiMove()
{
    static bool waitFlag{ true };
    static std::chrono::steady_clock::time_point start;
    static std::chrono::milliseconds waitTime{ 500 };


    //TODO: move the below

    if (waitFlag)
    {
        start = std::chrono::steady_clock::now();
        waitFlag = false;
    }
    auto now{ std::chrono::steady_clock::now() };
    if ((now - start) > waitTime)
    {
        placePeice(m_AiPlayer.aiPeice, m_AiPlayer.getMove());
        m_turn = BoardSquare::Peices::X;
        waitFlag = true;
        //random duration each time for better feel
        waitTime = std::chrono::milliseconds(Utils::getRandomNumber(100, 1000));
    }
}

std::optional<BoardSquare::Peices> Game::checkVictory()        // returns nullopt if no victor, otherwise returns the player that won.
{
    const BoardSquare::Peices opponentPeice{ m_playerPeice == BoardSquare::Peices::X ? BoardSquare::Peices::O : BoardSquare::Peices::X };


    //check draw
    if (m_turnCount >= 9)
    {
        std::cout << "Its a draw";
        return BoardSquare::Peices::empty;
    }


    //vertical
    for (int x{}, pSum{}, oSum{}; x < 3; x++, pSum = 0, oSum = 0)
    {
        for (int y{}; y < 3; y++)
        {
            if (m_board.getState({x,y}) == m_playerPeice)
            {
                pSum++;
            }
            else if (m_board.getState({ x,y }) == opponentPeice)
            {
                oSum++;
            }
        }
        if (pSum == 3)
        {
            return m_playerPeice;
        }
        else if (oSum == 3)
        {
            return opponentPeice;
        }
    }
    //horizontal
    for (int y{}, pSum{}, oSum{}; y < 3; y++, pSum = 0, oSum = 0)
    {
        for (int x{}; x < 3; x++)
        {
            if (m_board.getState({ x,y }) == m_playerPeice)
            {
                pSum++;
            }
            else if (m_board.getState({ x,y }) == opponentPeice)
            {
                oSum++;
            }
        }
        if (pSum == 3)
        {
            return m_playerPeice;
        }
        else if (oSum == 3)
        {
            return opponentPeice;
        }
    }
    //diagonal
    for (int i{}, pSum{}, oSum{}; i <= 8; i += 4)
    {
        if (m_board.getState(i) == m_playerPeice)
        {
            pSum++;
        }
        else if (m_board.getState(i) == opponentPeice)
        {
            oSum++;
        }

        if (pSum == 3)
        {
            return m_playerPeice;
        }
        else if (oSum == 3)
        {
            return opponentPeice;
        }
    }
    for (int i{2}, pSum{}, oSum{}; i <= 6; i += 2)
    {
        if (m_board.getState(i) == m_playerPeice)
        {
            pSum++;
        }
        else if (m_board.getState(i) == opponentPeice)
        {
            oSum++;
        }

        if (pSum == 3)
        {
            return m_playerPeice;
        }
        else if (oSum == 3)
        {
            return opponentPeice;
        }
    }


    return std::nullopt;
}

void Game::reset()
{
    //reset board
    this->m_board = {};
    m_turn = BoardSquare::Peices::X;
    this->m_turnCount = {};

    for (int i{}; i < 5; i++)
    {
        std::cout << std::endl;
    }
    std::cout << "__________New Game__________" << std::endl;

    loadBoard();
}

std::optional<const char*> Game::getPath(BoardSquare::Peices asset)
{
    switch (asset)
    {
    case BoardSquare::Peices::X:
        return "./res/x.png";
        break;
    case BoardSquare::Peices::O:
        return "./res/o.png";
        break;
    case BoardSquare::Peices::tile:
        return "./res/sq.png";
        break;
    default:
        std::cerr << "Invalid asset, could not get path!";
        return std::nullopt;
        break;
    }
    return std::nullopt;
}
