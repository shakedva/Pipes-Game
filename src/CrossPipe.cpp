//----------------------------------include section---------------------------------
#include "CrossPipe.h"
//---------------------------------class implementation-----------------------------

//constructor that updates the default exit of a CrossPipe
CrossPipe::CrossPipe(int row, int col, int index) : GameObject(row, col, index)
{
	for (int i = 0; i < NUM_EXITS; i++)
		m_exits[i] = true;
}