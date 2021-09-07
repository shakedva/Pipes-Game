#pragma once

//enum for texures vector
enum GameObjects
{
	FAUCET, SINK, CROSS_PIPE, L_PIPE, R_PIPE, T_PIPE, 
	B_FAUCET, B_SINK, B_CROSS_PIPE, B_L_PIPE, B_R_PIPE, B_T_PIPE, MENU, NEXT_LEVEL, YOU_WON
};

// enum for the sound vector
enum E_MediaSound
{
	CLICK, FINISHED_GAME, WATER_POUR
};

enum Directions
{
	UP, RIGHT, DOWN, LEFT
};

const int TILE_SIZE = 80, INFO_SIZE = 250, NUM_EXITS = 4, INIT = 0, NUM_GAME_OBJECTS = 6, MILI_SEC = 1000, THREE = 3, CHAR_SIZE = 30;
const float INIT_DEG = 0,DEG_90 = 90, DEG_180 = 180 , DEG_270 = 270;
