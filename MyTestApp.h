// Copyright 2009-2014 Blam Games, Inc. All Rights Reserved.

#pragma once

#include "BaseApp.h"
#include "Shape.h"
#include "Helper.h"

class MyTestApp : public BaseApp
{
	typedef BaseApp Parent;

public:
	MyTestApp();
	~MyTestApp();
	virtual void KeyPressed(int btnCode);
	virtual void UpdateF(float deltaTime);
	void exit();
private:
	void SetString(int startX, int startY, string str);
	void drawShape(ShapeCord cordinate);
	void clearShape(ShapeCord cordinate,bool isShow = false);
	Shape* randomNextShape();
	void checkLine();
	void upScore();
	bool moveShape(eDir direction);
	bool isMyCord(ShapeCord cordinates, Cordinate cord);
	void drawBorder();
	void rotate();
private:
	bool mDirection;
	bool isFast;
	int mScore;
	eDir dir;
	Shape *mShape;
	Shape *mNextShape;
	ShapeCord shapeCord;
	float mTimeUpdate;
};
