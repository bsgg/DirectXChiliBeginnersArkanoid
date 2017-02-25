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
	bool DoBallCollision(Ball& ball);
	void DoWallCollision(const RectF& walls);
	void Update(const Keyboard& kb, float dt);
	RectF GetRect() const;
	void ResetCooldown();

private:

	static constexpr Color wingColor = Colors::Red;
	static constexpr Color color = Colors::White;
	// Width for the wings
	static constexpr float wingWidth = 18.0f;
	static constexpr float speed = 300.0f;

	// Control the paddle rebound behaviour
	static constexpr float maximunExitRation = 2.6f;
	static constexpr float fixedZoneWidthRation = 0.2f;
	float halfWidth;
	float halfHeight;

	// Above controls
	float exitXFactor;
	float fixedZoneHalfWidth;
	float fixedZoneExitX;

	Vec2 pos;
	// Cooldown for the collision with the ball. 
	bool isCooldown = false;
};
