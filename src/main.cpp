#include <SFML/Graphics.hpp>
#include "Controller.h"

const std::string OUT_FILE_PATH = "log.txt";

int main()
{
	srand(time(NULL));
	try
	{
		Controller c;
		c.run();
	}
	//catch any error that occured in the code and save its description in the log output file
	catch (std::exception& exp)
	{
		std::ofstream file;
		file.open(OUT_FILE_PATH);
		file << exp.what();
		file.close();
	}
}