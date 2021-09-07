//----------------------------------include section---------------------------------
#pragma once
#include "GameObject.h"

//---------------------------------class implementation-----------------------------
class CrossPipe : public GameObject
{
public:
	CrossPipe(int, int, int);
	virtual void rotatePipe(int) override {};
	virtual void changeExits(int) override {};
};