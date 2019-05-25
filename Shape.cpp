#include "Shape.h"

Shape::Shape(Cordinate leftTop,int max_state, int id) : MAX_STATE(max_state+1), mleftTop(leftTop), mState(1), ID(id)
{
	mCoord.clear();
	mCoord.resize(0);
}

Shape::~Shape()
{
}

ShapeCord Shape::getShapeCord()
{
	return mCoord;
}

void Shape::setLeftTop(Cordinate cord)
{
	mleftTop.x = cord.x;
	mleftTop.y = cord.y;
	mCoord.clear();
	mCoord.push_back(Cordinate(mleftTop.x, mleftTop.y));
	mCoord.push_back(Cordinate(mleftTop.x + 1, mleftTop.y));
	mCoord.push_back(Cordinate(mleftTop.x, mleftTop.y + 1));
	mCoord.push_back(Cordinate(mleftTop.x + 1, mleftTop.y + 1));
}

Cordinate Shape::getLeftTop() const
{
	return Cordinate(mCoord[0]);
}

int Shape::getShapeId() const
{
	return ID;
}

Shape * Shape::getShape(int id, bool toMove)
{
	Cordinate cordStart = (toMove ? CENTER_CORD : Cordinate(ELEMENT_SHOW_X, ELEMENT_SHOW_Y));

	if (id == 5 && !toMove)
	{
		cordStart.x++;
	}

	switch (id)
	{
	case 0:return new ShapeSquare(cordStart); break;
	case 1:return new ShapeZ(cordStart); break;
	case 2:return new ShapeInvZ(cordStart); break;
	case 3:return new ShapeL(cordStart); break;
	case 4:return new ShapeT(cordStart); break;
	case 5:return new ShapeLine(cordStart); break;
	}
}

void Shape::decState()
{
	if (--mState == 0)
	{
		mState = MAX_STATE-1;
	}
}

///////////////////////////////////////////

ShapeSquare::ShapeSquare(Cordinate cord) : Shape( cord,SQUARE_STATE, SQUARE_ID)
{
	mCoord.push_back(Cordinate(cord.x, cord.y));
	mCoord.push_back(Cordinate(cord.x + 1, cord.y));
	mCoord.push_back(Cordinate(cord.x, cord.y + 1));
	mCoord.push_back(Cordinate(cord.x + 1, cord.y + 1));
}

void ShapeSquare::rotate(ShapeCord rotCord)
{
	mCoord = rotCord;
}

///////////////////////////////////////////

ShapeLine::ShapeLine(Cordinate cord) : Shape(cord, LINE_STATE, LINE_ID)
{
	mCoord.push_back(Cordinate(cord.x, cord.y));
	mCoord.push_back(Cordinate(cord.x, cord.y + 1));
	mCoord.push_back(Cordinate(cord.x, cord.y + 2));
	mCoord.push_back(Cordinate(cord.x, cord.y + 3));
}

void ShapeLine::rotate(ShapeCord rotCord)
{
	if (++mState == MAX_STATE)
	{
		mState = 1;
	}

	mCoord.clear();

	switch (mState)
	{
	case 1:
		mCoord.push_back(Cordinate(rotCord[0].x+1, rotCord[0].y));
		mCoord.push_back(Cordinate(rotCord[1].x, rotCord[1].y + 1));
		mCoord.push_back(Cordinate(rotCord[2].x-1, rotCord[2].y + 2));
		mCoord.push_back(Cordinate(rotCord[3].x-2, rotCord[3].y + 3));
		break;
	case 2:
		mCoord.push_back(Cordinate(rotCord[0].x - 1, rotCord[0].y));
		mCoord.push_back(Cordinate(rotCord[1].x,     rotCord[1].y-1));
		mCoord.push_back(Cordinate(rotCord[2].x + 1, rotCord[2].y-2));
		mCoord.push_back(Cordinate(rotCord[3].x + 2, rotCord[3].y-3));
		break;
	}
}

///////////////////////////////////////////

ShapeZ::ShapeZ(Cordinate cord) : Shape(cord,Z_STATE,Z_ID)
{
	mCoord.push_back(Cordinate(cord.x, cord.y));
	mCoord.push_back(Cordinate(cord.x + 1, cord.y));
	mCoord.push_back(Cordinate(cord.x + 1, cord.y + 1));
	mCoord.push_back(Cordinate(cord.x + 2, cord.y + 1));
}

void ShapeZ::rotate(ShapeCord rotCord)
{
	if (++mState == MAX_STATE)
	{
		mState = 1;
	}

	mCoord.clear();

	switch (mState)
	{
	case 1:
		mCoord.push_back(Cordinate(rotCord[0].x -2 ,     rotCord[0].y));
		mCoord.push_back(Cordinate(rotCord[1].x, rotCord[1].y-1));
		mCoord.push_back(Cordinate(rotCord[2].x-1, rotCord[2].y ));
		mCoord.push_back(Cordinate(rotCord[3].x+1 , rotCord[3].y-1));
		break;
	case 2:
		mCoord.push_back(Cordinate(rotCord[0].x+2 , rotCord[0].y));
		mCoord.push_back(Cordinate(rotCord[1].x,     rotCord[1].y + 1));
		mCoord.push_back(Cordinate(rotCord[2].x+1 , rotCord[2].y));
		mCoord.push_back(Cordinate(rotCord[3].x -1, rotCord[3].y+1));
		break;
	}
}

///////////////////////////////////////////

ShapeInvZ::ShapeInvZ(Cordinate cord) : Shape(cord,INVERTZ_STATE,INVERTZ_ID)
{
	mCoord.push_back(Cordinate(cord.x, cord.y + 1));
	mCoord.push_back(Cordinate(cord.x + 1, cord.y));
	mCoord.push_back(Cordinate(cord.x + 1, cord.y + 1));
	mCoord.push_back(Cordinate(cord.x + 2, cord.y));
}

void ShapeInvZ::rotate(ShapeCord rotCord)
{
	if (++mState == MAX_STATE)
	{
		mState = 1;
	}

	mCoord.clear();

	switch (mState)
	{
	case 1:
		mCoord.push_back(Cordinate(rotCord[0].x ,     rotCord[0].y));
		mCoord.push_back(Cordinate(rotCord[1].x+1, rotCord[1].y));
		mCoord.push_back(Cordinate(rotCord[2].x , rotCord[2].y));
		mCoord.push_back(Cordinate(rotCord[3].x+1, rotCord[3].y-2));
		break;
	case 2:
		mCoord.push_back(Cordinate(rotCord[0].x , rotCord[0].y));
		mCoord.push_back(Cordinate(rotCord[1].x-1, rotCord[1].y));
		mCoord.push_back(Cordinate(rotCord[2].x, rotCord[2].y ));
		mCoord.push_back(Cordinate(rotCord[3].x-1, rotCord[3].y+2));
		break;
	}
}

///////////////////////////////////////////

ShapeL::ShapeL(Cordinate cord) : Shape(cord,L_STATE,L_ID)
{
	mCoord.push_back(Cordinate(cord.x + 1, cord.y));
	mCoord.push_back(Cordinate(cord.x + 1, cord.y + 1));
	mCoord.push_back(Cordinate(cord.x + 1, cord.y + 2));
	mCoord.push_back(Cordinate(cord.x, cord.y + 2));
}

void ShapeL::rotate(ShapeCord rotCord)
{
	if (++mState == MAX_STATE)
	{
		mState = 1;
	}

	mCoord.clear();

	switch (mState)
	{
	case 1:
		mCoord.push_back(Cordinate(rotCord[0].x, rotCord[0].y));
		mCoord.push_back(Cordinate(rotCord[1].x, rotCord[1].y ));
		mCoord.push_back(Cordinate(rotCord[2].x - 1, rotCord[2].y + 1));
		mCoord.push_back(Cordinate(rotCord[3].x - 3, rotCord[3].y + 1));
		break;
	case 2:
		mCoord.push_back(Cordinate(rotCord[0].x,     rotCord[0].y));
		mCoord.push_back(Cordinate(rotCord[1].x+1 , rotCord[1].y-1));
		mCoord.push_back(Cordinate(rotCord[2].x + 2, rotCord[2].y-2));
		mCoord.push_back(Cordinate(rotCord[3].x + 3, rotCord[3].y - 1));
		break;
	case 3:
		mCoord.push_back(Cordinate(rotCord[0].x+1,     rotCord[0].y));
		mCoord.push_back(Cordinate(rotCord[1].x-1 , rotCord[1].y));
		mCoord.push_back(Cordinate(rotCord[2].x-2,     rotCord[2].y + 1));
		mCoord.push_back(Cordinate(rotCord[3].x-2,     rotCord[3].y + 1));
		break;
	case 4:
		mCoord.push_back(Cordinate(rotCord[0].x-1,     rotCord[0].y));
		mCoord.push_back(Cordinate(rotCord[1].x,     rotCord[1].y + 1));
		mCoord.push_back(Cordinate(rotCord[2].x + 1, rotCord[2].y));
		mCoord.push_back(Cordinate(rotCord[3].x + 2, rotCord[3].y - 1));
		break;
	}
}

///////////////////////////////////////////

ShapeT::ShapeT(Cordinate cord) : Shape(cord,T_STATE,T_ID)
{
	mCoord.push_back(Cordinate(cord.x + 1, cord.y));
	mCoord.push_back(Cordinate(cord.x, cord.y + 1));
	mCoord.push_back(Cordinate(cord.x + 1, cord.y + 1));
	mCoord.push_back(Cordinate(cord.x + 2, cord.y + 1));
}

void ShapeT::rotate(ShapeCord rotCord)
{
	if (++mState == MAX_STATE)
	{
		mState = 1;
	}

	mCoord.clear();

	switch (mState)
	{
	case 1:
		mCoord.push_back(Cordinate(rotCord[0].x, rotCord[0].y));
		mCoord.push_back(Cordinate(rotCord[1].x-1,     rotCord[1].y));
		mCoord.push_back(Cordinate(rotCord[2].x-1, rotCord[2].y));
		mCoord.push_back(Cordinate(rotCord[3].x + 1, rotCord[3].y - 1));
		break;
	case 2:
		mCoord.push_back(Cordinate(rotCord[0].x, rotCord[0].y));
		mCoord.push_back(Cordinate(rotCord[1].x,     rotCord[1].y));
		mCoord.push_back(Cordinate(rotCord[2].x, rotCord[2].y));
		mCoord.push_back(Cordinate(rotCord[3].x - 1, rotCord[3].y +1));
		break;
	case 3:
		mCoord.push_back(Cordinate(rotCord[0].x-1,     rotCord[0].y));
		mCoord.push_back(Cordinate(rotCord[1].x + 1, rotCord[1].y-1));
		mCoord.push_back(Cordinate(rotCord[2].x, rotCord[2].y));
		mCoord.push_back(Cordinate(rotCord[3].x + 1, rotCord[3].y -2));
		break;
	case 4:
		mCoord.push_back(Cordinate(rotCord[0].x+1,    rotCord[0].y));
		mCoord.push_back(Cordinate(rotCord[1].x,    rotCord[1].y + 1));
		mCoord.push_back(Cordinate(rotCord[2].x+1,rotCord[2].y));
		mCoord.push_back(Cordinate(rotCord[3].x-1,    rotCord[3].y + 2));
		break;
	}
}