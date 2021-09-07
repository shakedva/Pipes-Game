//----------------------------------include section---------------------------------
#include "Media.h"
#include <Windows.h>
#include "macros.h"
//----------------------------------functions section---------------------------------
const std::string COMPLETE = "\tComplete!", WON = " You\nWon!", FINISHED = "Finished Game";

//----------------------------------functions section---------------------------------
// constructor that opens all the files needed for the game
Media::Media()
{
	m_font.loadFromFile("resources/Bubblegum.ttf");
	loadTextures();
	loadAudio();
}
// load all the textures for the game and push it into m_textures
void Media::loadTextures()
{
	sf::Texture cross_pipe, faucet, l_pipe, r_pipe, sink, t_pipe,
		b_cross_pipe, b_faucet, b_l_pipe, b_r_pipe, b_sink, b_t_pipe, background, menu;
	cross_pipe.loadFromFile("cross_pipe.png");
	faucet.loadFromFile("faucet.png");
	l_pipe.loadFromFile("l_pipe.png");
	r_pipe.loadFromFile("r_pipe.png");
	sink.loadFromFile("sink.png");
	t_pipe.loadFromFile("t_pipe.png");

	b_cross_pipe.loadFromFile("BLUE_CROSS.png");
	b_faucet.loadFromFile("BLUE_FAUCET.png");
	b_l_pipe.loadFromFile("BLUE_L.png");
	b_r_pipe.loadFromFile("BLUE_R.png");
	b_sink.loadFromFile("BLUE_SINK.png");
	b_t_pipe.loadFromFile("BLUE_T.png");

	menu.loadFromFile("4453388.jpg");

	// push into Texture vector 
	m_textures.push_back(faucet);
	m_textures.push_back(sink);
	m_textures.push_back(cross_pipe);
	m_textures.push_back(l_pipe);
	m_textures.push_back(r_pipe);
	m_textures.push_back(t_pipe);

	m_textures.push_back(b_faucet);
	m_textures.push_back(b_sink);
	m_textures.push_back(b_cross_pipe);
	m_textures.push_back(b_l_pipe);
	m_textures.push_back(b_r_pipe);
	m_textures.push_back(b_t_pipe);

	m_textures.push_back(menu);

}

//load all the audio for the game and saves it the the class's members
void Media::loadAudio()
{
	sf::SoundBuffer clickSoundBuffer, finishedGameSoundBuffer, waterPourSoundBuffer;

	clickSoundBuffer.loadFromFile("resources/click.wav");
	finishedGameSoundBuffer.loadFromFile("resources/finished_game.wav");
	waterPourSoundBuffer.loadFromFile("resources/water_pour.wav");

	m_soundBuffer.push_back(clickSoundBuffer);
	m_soundBuffer.push_back(finishedGameSoundBuffer);
	m_soundBuffer.push_back(waterPourSoundBuffer);

	for (int i = 0; i < m_soundBuffer.size(); i++)
	{
		m_sounds.push_back(sf::Sound(m_soundBuffer[i]));
	}
}

Media& Media::instance()
{
	// the object inst is created once and can be reached everywhere in the game
	static Media inst;
	return inst;
}

// returns the wanted texture
sf::Texture& Media::getTexture(int index)
{
	return m_textures[index];
}

// returns the wanted font
sf::Font& Media::getFont()
{
	return m_font;
}

// playes the wanted sound effect 
void Media::playSound(int index)
{
	m_sounds[index].play();
}

//when the player wins the game, a message will pop on the screen
void Media::wonMsg()
{
	sf::RenderWindow window(sf::VideoMode(300.f, 300.f), FINISHED);
	sf::Text text;
	set_text(text, 30, 100.f, 100.f, sf::Color(88, 177, 255), WON);
	Media::instance().playSound(FINISHED_GAME);
	window.draw(text);
	window.display();
	Sleep(THREE * MILI_SEC); // show the message for 3 seconds
}

//when the player ends a level, a message will pop on the screen
void Media::nextLevelMsg(sf::RenderWindow& window, int width)
{
	sf::Text nextLevel;
	set_text(nextLevel, 30, (float)TILE_SIZE * width, 100.f, sf::Color(88, 177, 255), COMPLETE);
	Media::instance().playSound(WATER_POUR);
	window.draw(nextLevel);
}

//receeive a text, and update its characters and wanted features
void Media::set_text(sf::Text& txt, unsigned int size, float posX, float posY, sf::Color fillColor, std::string str) const
{
	txt.setFont(Media::instance().getFont());
	txt.setCharacterSize(size);
	txt.setPosition(posX, posY);
	txt.setFillColor(fillColor);
	txt.setString(str);
}