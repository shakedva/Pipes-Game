//----------------------------------include section---------------------------------
#include "Sink.h"
//---------------------------------class implementation-----------------------------

//constructor that updates the exit of the sink according to the given direction
Sink::Sink(int row, int col, int index, int direction) : GameObject(row, col, index)
{
	//turn the direction of the sprite according to given direction
	if (direction == DOWN)
	{
		positionSprites((float)TILE_SIZE, (float)TILE_SIZE, DEG_180);
		m_exits[DOWN] = true;
	}
	else if (direction == RIGHT)
	{
		positionSprites(INIT_DEG, (float)TILE_SIZE, DEG_90);
		m_exits[RIGHT] = true;

	}
	else if (direction == LEFT)
	{
		positionSprites((float)TILE_SIZE, INIT_DEG, DEG_270);
		m_exits[LEFT] = true;
	}
	else
		m_exits[UP] = true;
}