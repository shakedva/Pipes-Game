//----------------------------------include section---------------------------------
#pragma once
#include "Graph.h"
#include "GameObject.h"
#include <iostream>
#include <fstream>
#include "Faucet.h"
#include "Sink.h"

//---------------------------------class implementation-----------------------------
class Board
{
public:
	Board();
	~Board();
	void printBoard(sf::RenderWindow&) const;
	void handleClick(const sf::Vector2f&, int);
	void setNextLevel();
	int getHeight() const;
	int getWidth() const;
	bool getNextLevel() const;
	int getLevel() const;
private:
	void readLevel();
	void initBoard(int);
	bool isBufferEmpty();
	bool checkIfInteger(char*) const;
	void shufflePipes();
	
	// represent information on the current level
	int m_level, m_height, m_width, m_tapCount;
	bool m_nextLevel = false; // represent if we passed the current level
	Graph<GameObject> m_graph; // holds all the game objects of the game within a graph
	std::fstream m_file; // hold the file we read the levels from
	// pointers to the sink and faucet which are the game's source and target
	Faucet *m_faucet;
	Sink *m_sink;
};