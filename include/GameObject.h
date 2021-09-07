//----------------------------------include section---------------------------------
#pragma once
#include <iostream>
#include <set>
#include "Media.h"
#include <SFML/Graphics.hpp>
#include "macros.h"

//---------------------------------class implementation-----------------------------
class GameObject
{
public:
	GameObject() = default;
	~GameObject() = default;
	GameObject(int, int, int);
	
	std::set<GameObject*> checkConnections();
	GameObject* getNeighbor(int);
	void draw(sf::RenderWindow&) const;
	void addNeighbor(GameObject*, int);
	void changeVisited(bool);
	bool getVisited() const;
	virtual void rotatePipe(int);
	virtual void shufflePipes();

protected:
	virtual void changeExits(int);
	void positionSprites(float, float, float);

	// holds the sprites for the regular pipes and the pipes that are full of water
	sf::Sprite m_objSprite, m_blueObjSprite;
	// array that represent the 4 exits of every object, the exits: up, left, down and left
	bool m_exits[NUM_EXITS]; 

private:
	void exitsShiftRight();
	void exitsShiftLeft();

	// every game object holds the 4 objects that are the closest to it in m_neighbors
	// m_neighborMap holds the neighbors that are connected to the game object
	std::vector <GameObject*> m_neighbors;
	std::map<int, GameObject*> m_neighborMap;
	// represent if the game object is full of water
	bool m_visited; 
};

