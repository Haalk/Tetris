// Copyright 2009-2014 Blam Games, Inc. All Rights Reserved.

#include "MyTestApp.h"
#include <stdlib.h>
#include <random>
#include <ctime>

MyTestApp::MyTestApp() : Parent(WINDOW_WIDTH, WINDOW_HEIGHT)
{
	mDirection = false;
	dir = DOWN;
	drawBorder();
	mScore = -SCORE;

	mNextShape = nullptr;
	mShape = nullptr;
	mNextShape = randomNextShape();
	mShape = randomNextShape();
	mShape->setLeftTop(CENTER_CORD);
	drawShape(mNextShape->getShapeCord());
	drawShape(shapeCord);
	upScore();

	isFast = false;

	mTimeUpdate = 0.0F;
	//srand(time(0));
}

MyTestApp::~MyTestApp()
{
	delete mNextShape;
	delete mShape;
}

void MyTestApp::KeyPressed(int btnCode)
{
	if (!isFast)
	{
		switch (btnCode)
		{
		case LEFT_KEY:dir = LEFT; break;
		case RIGHT_KEY:dir = RIGHT; break;
		case SPACE_KEY:rotate(); break;
		case DOWN_KEY:isFast = true; break;
		}
	}
}

void MyTestApp::UpdateF(float deltaTime)
{
	if (isFast && mDirection)
	{
			moveShape(DOWN);
	}
	else
	{
		moveShape(dir);
		mTimeUpdate += deltaTime;
		if (mTimeUpdate > 0.45)
		{
			mTimeUpdate = 0.0F;
			moveShape(DOWN);
		}
	}

	if (!mDirection)
	{
		exit();
		mDirection = true;
		clearShape(mNextShape->getShapeCord(),true);
		delete mShape;
		mShape = Shape::getShape(mNextShape->getShapeId(),true);
		delete mNextShape;
		mNextShape = randomNextShape();
		shapeCord = mShape->getShapeCord();
		drawShape(mNextShape->getShapeCord());
		drawShape(shapeCord);
	}
	checkLine();
}

void MyTestApp::exit()
{
	if (isMyCord(mNextShape->getShapeCord(),CENTER_CORD))
	{
		delete mShape;
		delete mNextShape;
		mShape = nullptr;
		mNextShape = nullptr;
		::exit(0);
	}
}

void MyTestApp::checkLine()
{
	int counter = 0;

	for (int i = SIZE_FIELD_Y-1; i > 0; --i)
	{
		for (int j = 1; j <= SIZE_FIELD; ++j)
		{
			wchar_t returned = GetChar(j, i);
			if (returned != static_cast<wchar_t>(SYMBOL_ELEMENT))
			{
				break;
			}
			else
			{
				++counter;
			}
		}
		if (counter == SIZE_FIELD)
		{
			upScore();
			int t = i;
			for (int k = t - 1; k > 0; --k)
			{
				for (int j = 1; j <= SIZE_FIELD; ++j)
				{
					wchar_t returned = GetChar(j, k);
					SetChar(j, t, returned);
				}
				--t;
			}
			--i;
		}
		counter = 0;
	}
}

void MyTestApp::upScore()
{
	mScore += SCORE;
	char buffer[BUFFER];
	char *p = _itoa(mScore, buffer, DECIMAL_S);
	SetString(SCORE_POS_X, SCORE_POS_Y, static_cast<string>(p));
}

bool MyTestApp::moveShape(eDir direction)
{
	int moveX = 0;
	int moveY = 0;
	bool isMove = true;

	switch (direction)
	{
		case LEFT:moveX =- 1; break;
		case RIGHT:moveX = 1; break;
		case SPEED:direction = DOWN; break;
		default:break;
	}

	clearShape(shapeCord);

	for (u_int i = 0; i < shapeCord.size(); ++i)
	{
		if (direction == DOWN)
		{
			moveY = 1;
			if (GetChar(shapeCord[i].x, shapeCord[i].y + moveY) != SYMBOL_FIELD)
			{
				mDirection = false;
				isFast = false;
			}
		}
		else if (direction == LEFT)
		{
			if (shapeCord[i].x + moveX < 1 || (GetChar(shapeCord[i].x + moveX, shapeCord[i].y) == SYMBOL_ELEMENT && !isMyCord(shapeCord,static_cast<Cordinate>(shapeCord[i].x + moveX, shapeCord[i].y))))
			{
				moveX = 0;
			}
		}
		else if (direction == RIGHT)
		{
			if (shapeCord[i].x + moveX > SIZE_FIELD || (GetChar(shapeCord[i].x + moveX, shapeCord[i].y) == SYMBOL_ELEMENT && !isMyCord(shapeCord,static_cast<Cordinate>(shapeCord[i].x + moveX, shapeCord[i].y))))
			{
				moveX = 0;
			}
		}
		else
		{
			if (shapeCord[i].x < 1 || shapeCord[i].x > SIZE_FIELD)
			{
				return false;
			}
		}
	}

	if (direction == DOWN && mDirection)
	{
		for (u_int i = 0; i < shapeCord.size(); i++)
		{
			shapeCord[i].y += moveY;
		}
	}

	else if (isMove)
	{
		for (u_int i = 0; i < shapeCord.size(); i++)
		{
			shapeCord[i].x += moveX;
		}	
	}

	dir = NONE;
	
	drawShape(shapeCord);
	return isMove;
}

bool MyTestApp::isMyCord(ShapeCord cordinates, Cordinate cord)
{
	bool isContain = false;
	for (u_int i = 0; i < shapeCord.size(); ++i)
	{
		if (shapeCord[i].x == cord.x && shapeCord[i].y == cord.y)
		{
			isContain = true;
			break;
		}
	}
	return isContain;
}

void MyTestApp::drawShape(ShapeCord cordinate)
{
	for (u_int i = 0; i < cordinate.size(); ++i)
	{
		SetChar(cordinate[i].x, cordinate[i].y, static_cast<char>(SYMBOL_ELEMENT));
	}
}

void MyTestApp::clearShape(ShapeCord cordinate, bool isShow)
{
	char symbol = isShow ? SYMBOL_EMPTY : SYMBOL_FIELD;
	for (u_int i = 0; i < cordinate.size(); ++i)
	{
		SetChar(cordinate[i].x, cordinate[i].y, symbol);
	}
}

Shape* MyTestApp::randomNextShape()
{
	return Shape::getShape(std::rand() % SIZE_FIGURE, false);
}

void MyTestApp::drawBorder()
{
	for (int i = 0; i <= Y_SIZE; ++i)
	{
		for (int j = 0; j <= X_SIZE; ++j)
		{
			if (i == 0 || i == SIZE_FIELD_Y || i == Y_SIZE || j == 0 || (j == SIZE_FIELD_X && i < SIZE_FIELD_Y) || j == X_SIZE)
			{
				SetChar(j, i, static_cast<char>(SYMBOL_BORDER));
			}
			else if (i > SIZE_FIELD_Y-1 || j > SIZE_FIELD_X)
			{
				SetChar(j, i, SYMBOL_EMPTY);
			}
			else
			{
				SetChar(j, i, SYMBOL_FIELD);
			}
		}
	}

	SetString(2, SCORE_POS_Y, "> Score: ");
}

void MyTestApp::rotate()
{
	bool checkRotate = true;
	mShape->rotate(shapeCord);
	ShapeCord lastCord = mShape->getShapeCord();

	for (int i = 0; i < lastCord.size(); ++i)
	{
		if (lastCord[i].x >= SIZE_FIELD_X || lastCord[i].x < 1 || lastCord[i].y > SIZE_FIELD_Y)
		{
			checkRotate = false;
		}
	}
	clearShape(shapeCord);
	if (!checkRotate)
	{
		mShape->decState();
	}
	else
	{
		shapeCord = lastCord;
	}
	drawShape(shapeCord);
}

void MyTestApp::SetString(int startX, int startY, string str)
{
	for (u_int i = 0; i < str.length(); ++i)
		SetChar(startX + i, startY, static_cast<wchar_t>(str[i]));
}