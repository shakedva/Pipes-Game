//----------------------------------include section---------------------------------
#pragma once
#include "GameObject.h"

//---------------------------------class implementation-----------------------------
class Sink : public GameObject
{
public:
	Sink(int, int, int, int);
	virtual void rotatePipe(int) override {};
	virtual void shufflePipes() override {};
	virtual void changeExits(int) override {};
};