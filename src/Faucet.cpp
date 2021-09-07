//----------------------------------include section---------------------------------
#include "Faucet.h"
//---------------------------------class implementation-----------------------------

//constructor that updates the default exit of a Faucet
Faucet::Faucet(int row, int col, int index) : GameObject(row, col, index)
{
	m_exits[RIGHT] = true;
}