//----------------------------------include section---------------------------------
#include "GameObject.h"

//---------------------------------class implementation-----------------------------

//constructor for GameObject, initializes all his members
GameObject::GameObject(int row, int col, int index) : m_visited(false)
{
	Media& tex = Media::instance();
	m_objSprite = sf::Sprite(tex.getTexture(index));
	m_blueObjSprite = sf::Sprite(tex.getTexture(index + NUM_GAME_OBJECTS));
	m_objSprite.setPosition((float)col * TILE_SIZE, (float)row * TILE_SIZE);
	m_blueObjSprite.setPosition((float)col * TILE_SIZE, (float)row * TILE_SIZE);
	for (int i = 0; i < NUM_EXITS; i++)
		m_exits[i] = false;
}

// print m_objSprite on the window received
void GameObject::draw(sf::RenderWindow& window) const
{
	if (m_visited)
		window.draw(m_blueObjSprite);
	else
		window.draw(m_objSprite);
}

//shuffle the current object sprite direction randomly
void GameObject::shufflePipes()
{
	int amount_of_rotations = rand() % (NUM_EXITS - 1);
	for (int i = 0; i < amount_of_rotations; i++)
		rotatePipe(RIGHT);
}

//reposition a sprite according to givrn coordinates and a turning degree
void GameObject::positionSprites(float originX, float originY, float rotationDeg)
{
	m_objSprite.setOrigin(originX, originY);
	m_objSprite.setRotation(rotationDeg);
	m_blueObjSprite.setOrigin(originX, originY);
	m_blueObjSprite.setRotation(rotationDeg);
}

//receive a direction to turn the object sprite accordingly
void GameObject::rotatePipe(int direction)
{

	if (m_objSprite.getRotation() == DEG_270 && direction == LEFT ||
		m_objSprite.getRotation() == DEG_90 && direction == RIGHT)
	{
		positionSprites((float)TILE_SIZE, (float)TILE_SIZE, DEG_180);
		changeExits(direction);
		return;
	}
	else if (m_objSprite.getRotation() == DEG_180 && direction == LEFT ||
		m_objSprite.getRotation() == INIT_DEG && direction == RIGHT)
	{
		positionSprites(INIT_DEG, (float)TILE_SIZE, DEG_90);
		changeExits(direction);
		return;
	}
	else if (m_objSprite.getRotation() == DEG_90 && direction == LEFT ||
		m_objSprite.getRotation() == DEG_270 && direction == RIGHT)
	{
		positionSprites(INIT_DEG, INIT_DEG, INIT_DEG);
		changeExits(direction);
		return;
	}
	else if (m_objSprite.getRotation() == INIT_DEG && direction == LEFT ||
		m_objSprite.getRotation() == DEG_180 && direction == RIGHT)
	{
		positionSprites((float)TILE_SIZE, INIT_DEG, DEG_270);
		changeExits(direction);
	}
}

//update the current exits according to a given direction that represents the shift 
void GameObject::changeExits(int dir)
{
	if (dir == RIGHT)
		exitsShiftRight();
	else if (dir == LEFT)
		exitsShiftLeft();
}

//change the object's exits when it is turned to the right side
void GameObject::exitsShiftRight()
{
	bool tempLast = m_exits[LEFT];
	for (int i = LEFT; i > UP; i--)
	{
		m_exits[i] = m_exits[i - 1];
	}
	m_exits[UP] = tempLast;
}

//change the object's exits when it is turned to the left side
void GameObject::exitsShiftLeft()
{
	bool tempFirst = m_exits[UP];
	for (int i = RIGHT; i <= LEFT; i++)
	{
		m_exits[i - 1] = m_exits[i];
	}
	m_exits[LEFT] = tempFirst;
}

//add a neighbor to the neigbors vector, and to the neigbors map, according to the direction he is in 
void GameObject::addNeighbor(GameObject* neighbor, int dir)
{
	m_neighbors.push_back(neighbor);
	m_neighborMap[dir] = neighbor;
}

//in this function we go over all the neighbors of the GameObject, and check if each of them is pointing
//to the opposite direction of the GameObject - this is how we represent connection between GameObjects.
// If so, we insert the neighbor to the set of "connected" neigbors according to his location from the GameObject.
std::set<GameObject*> GameObject::checkConnections()
{
	std::set<GameObject*> connected;
	for (int i = 0; i <= LEFT; i++)
	{
		if (m_exits[i] && m_neighborMap[i])
		{
			if (m_neighborMap[i]->m_exits[(i + 2) % NUM_EXITS]) //i+2 represents the opposite direction from each other
			{
				connected.insert(m_neighborMap[i]);
			}
		}
	}
	return connected;
}

//returns the neighbor that is located in the given direction of the GameObject
GameObject* GameObject::getNeighbor(int dir)
{
	return m_neighborMap[dir]; // return the game object if exist or null ptr if doesnt exist
}

//update the member m_visited according to the given boolean
void GameObject::changeVisited(bool b)
{
	m_visited = b;
}

bool GameObject::getVisited() const
{
	return m_visited;
}