//----------------------------------include section---------------------------------
#pragma once
#include "Board.h"
#include <Windows.h>

//---------------------------------class implementation-----------------------------
class Controller
{
public:
	Controller() = default;
	void run();
private:
	void drawGame(sf::RenderWindow&, const sf::Sprite&) const;
	bool openMenu() const;

	// holds the game board
	Board m_board;
};