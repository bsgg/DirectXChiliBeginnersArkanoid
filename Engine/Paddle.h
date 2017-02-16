#pragma once

#include "Ball.h"
#include "Vec2.h"
#include "RectF.h"
#include "Colors.h"
#include "Graphics.h"
#include "Keyboard.h"

class Paddle
{
public:
	Paddle(const Vec2& pos_in, float halfWidth_in, float halfHeight_in);
	void Draw(Graphics& gfx) const;
	bool DoBallCollision(Ball& ball) const;
	void DoWallCollision(const RectF& walls);
	void Update(const Keyboard& kb, float dt);
	RectF GetRect() const;

private:
	Color color = Colors::White;
	float speed = 300.0f;
	float halfWidth;
	float halfHeight;
	Vec2 pos;
};
