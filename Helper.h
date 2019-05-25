#pragma once

#include <vector>

struct Cordinate;

const char SYMBOL_ELEMENT = '0';//static_cast<char>(178);//178;
const char SYMBOL_BORDER = '#';//static_cast<char>(177);
const char SYMBOL_FIELD = '.';
const char SYMBOL_EMPTY = ' ';
const int SIZE_FIELD = 15;
const int WINDOW_WIDTH = 24;
const int WINDOW_HEIGHT = 25;
const int SCORE = 100;
const int BUFFER = 20;
const int DECIMAL_S = 10;
const int SCORE_POS_X = 12;
const int SCORE_POS_Y = WINDOW_HEIGHT - 2;
const int SIZE_FIGURE = 6;
const int SIZE_FIELD_Y = 21;
const int SIZE_FIELD_X = 16;
const int SCORE_LABEL_X = 2;
const int BOTTOM_FIELD_Y = WINDOW_HEIGHT - 5;
const int ELEMENT_SHOW_X = 19;
const int ELEMENT_SHOW_Y = 3;

enum eKey { DOWN_KEY = 80, LEFT_KEY = 75, RIGHT_KEY = 77, SPACE_KEY = 32};
enum eDir { DOWN = 0, LEFT, RIGHT, SPEED, NONE };
enum eShapeID { SQUARE_ID = 0, Z_ID = 1, INVERTZ_ID = 2, L_ID = 3, T_ID = 4, LINE_ID = 5,};
enum eShapeState {SQUARE_STATE = 1, Z_STATE = 2, INVERTZ_STATE = 2, L_STATE = 4, T_STATE = 4, LINE_STATE = 2, };

struct Cordinate
{
	int x;
	int y;
	Cordinate(int X = 7, int Y = 1) : x(X), y(Y) {}
};

const Cordinate CENTER_CORD(7, 1);

using ShapeCord = std::vector<Cordinate>;