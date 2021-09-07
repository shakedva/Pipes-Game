//----------------------------------include section---------------------------------
#pragma once
#include <iostream>

//---------------------------------class implementation-----------------------------
class FilePathException : public std::exception
{
public:
	virtual const char* what() const noexcept
	{
		return INVALID_FILE;
	}

private:
	const char* INVALID_FILE = "File can not be opened\n";
};
