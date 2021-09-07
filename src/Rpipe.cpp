//----------------------------------include section---------------------------------
#include "Rpipe.h"

//---------------------------------class implementation-----------------------------

//constructor that updates the default exits of a r_pipe 
Rpipe::Rpipe(int row, int col, int index) : GameObject(row, col, index)
{
	m_exits[DOWN] = true;
	m_exits[LEFT] = true;
}