#include "Paddle.h"

Paddle::Paddle(const Vec2 & pos_in, float halfWidth_in, float halfHeight_in)
	:pos(pos_in),
	halfWidth(halfWidth_in),
	halfHeight(halfHeight_in),
	exitXFactor( maximunExitRation / halfWidth ),
	fixedZoneHalfWidth( halfWidth * fixedZoneWidthRation ),
	fixedZoneExitX( fixedZoneHalfWidth * exitXFactor )
{}

void Paddle::Draw(Graphics & gfx) const
{
	RectF rect = GetRect();
	gfx.DrawRect(rect, wingColor);

	rect.left += wingWidth;
	rect.right -= wingWidth;
	gfx.DrawRect(rect, color);
}

bool Paddle::DoBallCollision(Ball & ball)
{
	if (!isCooldown)
	{
		const RectF rect = GetRect();
		if (GetRect().IsOverlappingWidth(ball.GetRect()))
		{
			const Vec2 ballPos = ball.GetPosition();

			// Check which kind of approach are we doing (inside or outside)
			if ((std::signbit(ball.GetVelocity().x) == std::signbit((ballPos - pos).x)) ||
				(ballPos.x >= rect.left && ballPos.x <= rect.right))
			{
				
				// Reflected angle
				// For the x component, de new direction will be the difference between the ball and the center of the paddle
				// This gives us a X component dependant on the long of the paddle.
				// For example if the paddle is 50 width, (25 in the middle) and the ball hits in the left edge of the paddle,
				// The X component is too long. (ballPos.x = 100, pos.x = 250 --> xDifference = 150)
				// We need to reescale this component to align with y.
				Vec2 dir;
				const float xDifference = ballPos.x - pos.x;

				// Avoid the ball straight vertical when hits in the middle of the paddle 
				// Y component will be always -1
				// if the xDifference is less than the zone in the half for the const vector
				if (std::abs(xDifference) < fixedZoneHalfWidth)
				{
					// Depend on the side, the x will be left or right
					if (xDifference < 0.0f)
					{
						dir = Vec2(-fixedZoneExitX, -1.0f);
					}
					else
					{
						dir = Vec2(fixedZoneExitX, -1.0f);
					}
				}
				else
				{
					dir = Vec2 (xDifference * exitXFactor, -1.0f);
				}

				ball.SetDirection(dir);
				
			}			
			else
			{
				ball.ReboundX();
			}

			isCooldown = true;
			return true;
		}
	}
	return false;
}

void Paddle::DoWallCollision(const RectF & walls)
{
	const RectF rect = GetRect();
	if (rect.left < walls.left)
	{
		pos.x += walls.left - rect.left;
	}
	else if (rect.right > walls.right)
	{
		pos.x -= rect.right - walls.right;
	}
}

void Paddle::Update(const Keyboard& kb, float dt)
{
	if (kb.KeyIsPressed(VK_LEFT))
	{
		pos.x -= speed * dt;
	}

	if (kb.KeyIsPressed(VK_RIGHT))
	{
		pos.x += speed * dt;
	}
}

RectF Paddle::GetRect() const
{
	return RectF::FromCenter(pos, halfWidth, halfHeight);
}

void Paddle::ResetCooldown()
{
	isCooldown = false;
}
