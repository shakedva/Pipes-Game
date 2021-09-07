//----------------------------------include section---------------------------------
#include "Controller.h"
#include <SFML/Graphics.hpp>
#include "GameObject.h"
#include "Faucet.h"
#include "Lpipe.h"
#include "Board.h"
#include "Media.h"
#include "macros.h"

//----------------------------------const section---------------------------------
const int THICKNESS = 5;
const std::string GAME_NAME = "Pipes Game!", WELCOME = "Welcome To Pipes Game!", NEW_GAME = "New Game", EXIT_GAME = "Exit Game";

//----------------------------------functions section---------------------------------
// run the game, responsible for the game loop
void Controller::run()
{
	if (openMenu()) // if the player pressed new game on the game menu
	{
		// open the window and set its background according to its dimensions
		sf::RenderWindow window(sf::VideoMode(m_board.getWidth() * TILE_SIZE + INFO_SIZE, m_board.getHeight() * TILE_SIZE),
			GAME_NAME, sf::Style::Titlebar | sf::Style::Close);
		sf::Sprite background;
		background = sf::Sprite(Media::instance().getTexture(MENU));
		background.setPosition(0.f, 0.f);
		background.setScale(
			((float)(m_board.getWidth() * TILE_SIZE) + INFO_SIZE) / background.getLocalBounds().width,
			((float)(m_board.getHeight() * TILE_SIZE)) / background.getLocalBounds().height);

		// iterate as long as the window is open
		while (window.isOpen())
		{
			drawGame(window, background);
			window.display();
			if (auto event = sf::Event{}; window.waitEvent(event)) // receive an event
			{
				switch (event.type)
				{
				case sf::Event::Closed:
					window.close();
					break;
				case sf::Event::MouseButtonPressed:
					// save the location pressed on the window and handle the click according to left button pressed or
					// right button pressed
					auto location = window.mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y });
					if (event.mouseButton.button == sf::Mouse::Right)
						m_board.handleClick(location, RIGHT);

					else if (event.mouseButton.button == sf::Mouse::Left)
						m_board.handleClick(location, LEFT);
				}
				// if we won the current level 
				if (m_board.getNextLevel() && m_board.getLevel() > 0)
				{
					// draw the finished board for 3 seconds and show a message it is completed 
					drawGame(window, background);
					Media::instance().nextLevelMsg(window, m_board.getWidth());
					window.display();
					Sleep(THREE * MILI_SEC);  // show the message for 3 seconds

					m_board.setNextLevel(); // tells the board we received the player won the level 
					// resize the window according to the new dimensions of the new level
					window.create(sf::VideoMode(m_board.getWidth() * TILE_SIZE + INFO_SIZE, m_board.getHeight() * TILE_SIZE),
						GAME_NAME, sf::Style::Titlebar | sf::Style::Close);
					background.setScale(
						((float)(m_board.getWidth() * TILE_SIZE) + INFO_SIZE) / background.getLocalBounds().width,
						((float)(m_board.getHeight() * TILE_SIZE)) / background.getLocalBounds().height);
				}
			}
		}
	}
}

// opens the menu of the game
bool Controller::openMenu() const
{
	// opens the window of the menu and draw the backgroung texture
	sf::RenderWindow menuWindow(sf::VideoMode(1332, 850), GAME_NAME, sf::Style::Titlebar | sf::Style::Close);

	
	Media& ins = Media::instance();
	sf::Sprite menuBackground = sf::Sprite(ins.getTexture(MENU));
	menuBackground.setPosition(0.f, 0.f);

	// creates text for all the buttons and welcome message
	sf::Text welcome, newGame, exitGame;
	ins.set_text(welcome, TILE_SIZE, 200.f, 100.f, sf::Color(88, 177, 255), WELCOME);
	ins.set_text(newGame, TILE_SIZE, 500.f, 300.f, sf::Color::White, NEW_GAME);
	ins.set_text(exitGame, TILE_SIZE, 500.f, 400.f, sf::Color::White, EXIT_GAME);

	// iterate until the menu is open
	while (menuWindow.isOpen())
	{
		// draw the menus background and its buttons
		menuWindow.draw(menuBackground);
		menuWindow.draw(welcome);
		menuWindow.draw(newGame);
		menuWindow.draw(exitGame);

		sf::Event event;
		while (menuWindow.pollEvent(event))
		{
			// Window closed or escape key pressed: exit
			if ((event.type == sf::Event::Closed) ||
				((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape)))
			{
				menuWindow.close();
				return false;
			}
			// pressed on the window
			if (event.type == sf::Event::MouseButtonReleased)
			{
				// save the click location
				auto clickLocation = menuWindow.mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y });
				// pressed on "new game" return true
				if (newGame.getGlobalBounds().contains(clickLocation))
				{
					Media::instance().playSound(CLICK);
					return true;
				}
				// pressed on "exit game" return false
				if (exitGame.getGlobalBounds().contains(clickLocation))
				{
					menuWindow.close();
					return false;
				}
			}
			if (event.type == sf::Event::MouseMoved)
			{
				// get the current mouse position in the window
				sf::Vector2i pixelPos = sf::Mouse::getPosition(menuWindow);

				// convert it to world coordinates
				sf::Vector2f worldPos = menuWindow.mapPixelToCoords(pixelPos);

				// if the cursor is on "new game" then change its outline to be thick and colorful
				if (newGame.getGlobalBounds().contains(worldPos))
				{
					newGame.setOutlineColor(sf::Color(88, 177, 255));
					newGame.setOutlineThickness(THICKNESS);
				}
				else
				{
					newGame.setOutlineColor(sf::Color::Black);
					newGame.setOutlineThickness(THICKNESS);
				}
				// if the cursor is on "exit game" then change its outline to be thick and colorful
				if (exitGame.getGlobalBounds().contains(worldPos))
				{
					exitGame.setOutlineColor(sf::Color(88, 177, 255));
					exitGame.setOutlineThickness(THICKNESS);
				}
				else
				{
					exitGame.setOutlineColor(sf::Color::Black);
					exitGame.setOutlineThickness(THICKNESS);
				}
			}
		}
		menuWindow.display();
	}
}

// clears the current board and draw the new one on it
void Controller::drawGame(sf::RenderWindow& window, const sf::Sprite& background) const
{
	window.clear();
	window.draw(background);
	m_board.printBoard(window);
}