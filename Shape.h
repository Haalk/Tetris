#pragma once

#include "Helper.h"

class Shape
{
public:
	Shape(Cordinate leftTop, int max_state=1, int id=1);
	virtual ~Shape();
	virtual void rotate(ShapeCord rotCord) = 0;
	ShapeCord getShapeCord();
	void setLeftTop(Cordinate);
	Cordinate getLeftTop() const;
	int getShapeId() const;
	static Shape * getShape(int id, bool toMove = false);
	void decState();
protected:
	ShapeCord mCoord;
	int mState;
	const int MAX_STATE;
	Cordinate mleftTop;
	int ID;
};

class ShapeSquare : public Shape	
{									
public:
	ShapeSquare(Cordinate leftTop);
	void rotate(ShapeCord rotCord);
};

class ShapeLine : public Shape
{
public:							
	ShapeLine(Cordinate leftTop);
	void rotate(ShapeCord rotCord);
};									

class ShapeZ : public Shape	
{	
public:
	ShapeZ(Cordinate leftTop);	
	void rotate(ShapeCord rotCord);
};									

class ShapeInvZ : public Shape	
{	
public:
	ShapeInvZ(Cordinate leftTop);
	void rotate(ShapeCord rotCord);
};									

class ShapeL : public Shape		    
{		
public:	
	ShapeL(Cordinate leftTop);		
	void rotate(ShapeCord rotCord);		
};						

class ShapeT : public Shape
{	
public:					
	ShapeT(Cordinate leftTop);	
	void rotate(ShapeCord rotCord);
};