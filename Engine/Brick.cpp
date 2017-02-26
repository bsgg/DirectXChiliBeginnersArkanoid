#include "Brick.h"
#include <assert.h>

Brick::Brick(const RectF & rect_in, Color color_in) :
	rect(rect_in),
	destroyed(false),
	bev(color_in)
{}

void Brick::Draw(Graphics & gfx) const
{
	if (!destroyed)
	{
		bev.DrawBeveledBrick(rect.GetExpanded(-padding), bevelSize, gfx);

		//gfx.DrawRect(rect.GetExpanded(-padding), color);
	}
}

bool Brick::CheckBallCollision(const Ball & ball) const
{
	return ((!destroyed) && (rect.IsOverlappingWidth(ball.GetRect())));
}

void Brick::ExecuteBallCollision(Ball & ball)
{
	assert(CheckBallCollision(ball));
	const Vec2 ballPos = ball.GetPosition();

	// Check which kind of approach are we doing (inside or outside)
	if (std::signbit( ball.GetVelocity().x ) == std::signbit( (ballPos - GetCenter()).x ))
	{
		// Aproaching from inside, will do reboundY
		ball.ReboundY();
	}
	else if (ballPos.x >= rect.left && ballPos.x <= rect.right)
	{
		ball.ReboundY();
	}
	else
	{
		ball.ReboundX();
	}
	destroyed = true;
}

Vec2 Brick::GetCenter() const
{
	return rect.GetCenter();
}
