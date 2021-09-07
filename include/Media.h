//----------------------------------include section---------------------------------
#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
//---------------------------------class implementation-----------------------------
//Media is a Singelton pattern
class Media
{
public:
	static Media& instance();
	sf::Texture& getTexture(int);
	sf::Font& getFont();
	void playSound(int);
	void wonMsg();
	void nextLevelMsg(sf::RenderWindow&, int);
	void set_text(sf::Text&, unsigned int, float, float, sf::Color, std::string) const;

private:
	Media(); // private constructor
	void loadTextures();
	void loadAudio();

	std::vector <sf::Texture> m_textures; //vector for all textures
	sf::Font m_font; //saves the font that will be shown in the game
	std::vector <sf::Sound> m_sounds; //saves all sounds
	std::vector <sf::SoundBuffer> m_soundBuffer; //saves all sound buffers
};