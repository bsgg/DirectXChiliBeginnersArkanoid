#pragma once

#include "Ball.h"
#include "Vec2.h"
#include "RectF.h"
#include "Colors.h"
#include "Graphics.h"

class Paddle
{
public:

private:
	Color color = Colors::White;
	float halfWidth;
	float halfHeight;
	Vec2 pos;
};
