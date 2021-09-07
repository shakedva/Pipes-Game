//----------------------------------include section---------------------------------
#include "Tpipe.h"

//---------------------------------class implementation-----------------------------
//constructor that updates the default exits of a t_pipe 
Tpipe::Tpipe(int row, int col, int index) : GameObject(row, col, index)
{
	m_exits[UP] = true;
	m_exits[RIGHT] = true;
	m_exits[LEFT] = true;
}