//----------------------------------include section---------------------------------
#include "Board.h"
#include "CrossPipe.h"
#include "Lpipe.h"
#include "Tpipe.h"
#include "Rpipe.h"
#include "macros.h"
#include "FilePathException.h"
#include "NotEnoughArguments.h"

//----------------------------------const section---------------------------------
const char C_CROSS = '+', C_T_PIPE = 't', C_L_PIPE = 'l', C_R_PIPE = 'r', C_SINK = 's', C_FAUCET = 'o', WS = ' ', END_STR = '\0';
const std::string FILE_PATH = "Board.txt" , INVALID_EXC = "Invalid game board";
const int MAX_STR = 50;

//----------------------------------functions section---------------------------------

// constructor - initialize all the members
Board::Board() : m_faucet(nullptr), m_sink(nullptr), m_height(INIT), m_width(INIT), m_tapCount(INIT), m_level(INIT)
{
	// opening the file that holds all the levels
	std::string path = FILE_PATH;
	m_file.open(path);
	
	// if the file did not open - throw an exception
	if (!m_file.is_open())
		throw FilePathException();
	try
	{
		readLevel(); // read the first level
	}
	catch (std::exception& exp)
	{
		throw(exp);
	}
}
// destructor - delete the pointers allocation
Board::~Board()
{
	delete m_faucet;
	delete m_sink;
}
// read a new level
void Board::readLevel()
{
	// if there is a whitespace eat it
	if(m_file.peek() == WS)
		m_file.get(); 
	
	// if reached to the end of the file - player won
	if (m_file.eof()) 
	{
		Media::instance().wonMsg();
		m_file.close(); // closing the file 
		exit(EXIT_SUCCESS);  
	}

	// read from file sink direction, height and width
	// before reading check if the buffer empty and throw an exception if so
	char sinkDir[MAX_STR], height[MAX_STR], width[MAX_STR];

	if (isBufferEmpty())
		throw NotEnoughArguments();
	m_file >> sinkDir;

	if (isBufferEmpty())
		throw NotEnoughArguments();
	m_file >> height;

	if (isBufferEmpty())
		throw NotEnoughArguments();
	m_file >> width;

	//check if they are not numbers
	if (checkIfInteger(sinkDir) && checkIfInteger(height) && checkIfInteger(width))
	{
		// convert
		m_height = atoi(height); 
		m_width = atoi(width);
	}
	// clear all the game objects in the graph before we save the new level in it
	m_graph.clearGraph();
	m_graph.setNumOfVertices(m_height, m_width);
	m_tapCount = INIT;
	m_level++;
	try
	{
		initBoard(atoi(sinkDir));
	}
	catch(std::exception &exp)
	{
		throw(exp);
	}
}
// initialize the game board according to the file received
void Board::initBoard(int sinkDirection)
{
	char curr;
	//iterate through the level's board in the file
	for (int i = 0; i < m_height; i++)
	{
		for (int j = 0; j < m_width; j++)
		{
			// reached to the end of the file before it should happen
			if(isBufferEmpty())
				throw std::invalid_argument(INVALID_EXC);
			m_file >> curr;
			// checks the digit and send it to the graph as a new vertex
			switch (curr)
			{
			case C_CROSS:
			{
				auto cp = std::make_unique <CrossPipe>(i, j, CROSS_PIPE);
				m_graph.addVertex(cp.release(), i, j);
				break;
			}
			case C_FAUCET:
			{
				auto fa = std::make_unique <Faucet>(i, j, FAUCET);
				delete m_faucet; // delete the memory already in m_faucet
				m_faucet = fa.get();
				m_graph.addVertex(fa.release(), i, j);
				break;
			}
			case C_L_PIPE:
			{
				auto lp = std::make_unique <Lpipe>(i, j, L_PIPE);
				m_graph.addVertex(lp.release(), i, j);
				break;
			}
				
			case C_R_PIPE:
			{
				auto rp = std::make_unique <Rpipe>(i, j, R_PIPE);
				m_graph.addVertex(rp.release(), i, j);
				break;
			}
			case C_T_PIPE:
			{
				auto tp = std::make_unique <Tpipe>(i, j, T_PIPE);
				m_graph.addVertex(tp.release(), i, j);
				break;
			}
			case C_SINK:
			{
				auto s = std::make_unique <Sink>(i, j, SINK, sinkDirection);
				delete m_sink; // delete the memory already in m_sink
				m_sink = s.get();
				m_graph.addVertex(s.release(), i, j);
				break;
			}
			default: // received a digit which does not represent anything in the game
				throw std::invalid_argument(INVALID_EXC);
			}

		}
	}
	shufflePipes(); 
	m_graph.saveEdges(); // saves the adjacency list
	// check if the first shuffle won the game and if so continue to shuffle until there is unsolved board
	m_graph.BFS(m_faucet, m_sink);
	while (m_graph.getIfFoundTarget())
		shufflePipes();

}

// prints the board game 
void Board::printBoard(sf::RenderWindow& window) const
{
	//print the vertices
	m_graph.printGraph(window);

	// print the tap conuter
	Media& ins = Media::instance();
	sf::Text info;
	// convert m_tapCount to char*
	char tapCount[MAX_STR] = "\tTap Count: \n\t\t\t";
	char tapCountString[MAX_STR];
	itoa(m_tapCount, tapCountString, 10);
	strcat(tapCount, tapCountString);
	
	ins.set_text(info, CHAR_SIZE, (float)TILE_SIZE * m_width, 0.f, sf::Color(88, 177, 255), tapCount);

	window.draw(info);
	
}
// receives the location of the click in the window and check whick tile was pressed on
void Board::handleClick(const sf::Vector2f& clickLocation, int dir)
{
	int posX = (int)clickLocation.x / TILE_SIZE, posY = (int)clickLocation.y / TILE_SIZE;
	// if trying to press outside the game tiles then return
	if (!m_graph.getVertex(posY, posX))
		return;
	// if pressed on a tile that can be rotated then add 1 to tapCount, rotate the pipe and check with bfs
	// if there is a path from the faucet to the sink by the connection of the vertices
	if (m_graph.getVertex(posY, posX) != m_sink)
	{
		m_tapCount++;
		Media::instance().playSound(CLICK);
		m_graph.getVertex(posY, posX)->rotatePipe(dir);
		m_graph.updateAdjList(m_graph.getVertex(posY, posX));

		m_graph.BFS(m_faucet, m_sink);
		if (m_graph.getIfFoundTarget())
		{
			m_nextLevel = true;
		}
	}
	
}

// check if a buffer is empty
bool Board::isBufferEmpty() 
{
	m_file >> std::ws;  // eat up any leading white spaces
	char c = m_file.peek(); // save the next char
	return c == EOF;
}
// check if received an integer number
bool Board::checkIfInteger(char* str) const
{
	int index = 0;
	// iterate through the char and check if there is a non digit char in it
	// through an exception if found any
	while (str[index] != END_STR)
	{
		if (!isdigit(str[index]))
			throw std::invalid_argument(INVALID_EXC);
		index++;
	}
	return true;
}
// shuffle all the pipes
void Board::shufflePipes()
{
	for (int i = 0; i < m_height; i++)
	{
		for (int j = 0; j < m_width; j++)
			m_graph.getVertex(i, j)->shufflePipes();
	}
}
// called from the controller, it represent that the controller knows we finished the current level and request
// to read the next one
void Board::setNextLevel()
{
	m_nextLevel = false;
	readLevel();
}

//----------------------------------get functions---------------------------------

// m_nextLevel tells the controller if we read a new level so it could receive the new time limitation
// on the current level
bool Board::getNextLevel() const
{
	return m_nextLevel;
}

int Board::getLevel() const
{ 
	return m_level;
}

int Board::getHeight() const
{ 
	return m_height;
}

int Board::getWidth() const
{ 
	return m_width;
}
