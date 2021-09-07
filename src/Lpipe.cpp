//----------------------------------include section---------------------------------
#include "Lpipe.h"

//---------------------------------class implementation-----------------------------

//constructor that updates the default exits of a l_pipe 
Lpipe::Lpipe(int row, int col, int index) : GameObject(row, col, index)
{
	m_exits[RIGHT] = true;
	m_exits[LEFT] = true;

}