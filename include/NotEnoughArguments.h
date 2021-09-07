//----------------------------------include section---------------------------------
#pragma once
#include <iostream>

//---------------------------------class implementation-----------------------------
class NotEnoughArguments : public std::exception
{
public:
	virtual const char* what() const noexcept
	{
		return FEW_ARGS;
	}
private:
	const char* FEW_ARGS = "There are not enough arguments in one line\n";
};