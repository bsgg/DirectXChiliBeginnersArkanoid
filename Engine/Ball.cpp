#include "Ball.h"
#include "SpriteCodex.h"

Ball::Ball(const Vec2 & pos_in, const Vec2 & dir_in):
	pos(pos_in)
{
	SetDirection(dir_in);
}

void Ball::Draw(Graphics & gfx) const
{
	SpriteCodex::DrawBall(pos, gfx);
}

void Ball::Update(float dt)
{
	pos += vel * dt;
}

// Return 0: nada, 1: hit wall, 2: hit bottom 
Ball::EWallCollision  Ball::DoWallCollision(const RectF & walls)
{
	Ball::EWallCollision typeCollision = EWallCollision::NoCollision;
	const RectF rect = GetRect();
	if (rect.left < walls.left)
	{
		pos.x += walls.left - rect.left;
		ReboundX();
		typeCollision = EWallCollision::WallCollision;
	}
	else if (rect.right > walls.right)
	{
		pos.x -= rect.right - walls.right;
		ReboundX();
		typeCollision = EWallCollision::WallCollision;
	}

	if (rect.top < walls.top)
	{
		pos.y += walls.top - rect.top;
		ReboundY();
		typeCollision = EWallCollision::WallCollision;
	}
	else if (rect.bottom > walls.bottom)
	{
		pos.y -= rect.bottom - walls.bottom;
		ReboundY();
		typeCollision = EWallCollision::BottomCollision;
	}
	return typeCollision;
}

void Ball::ReboundX()
{
	vel.x = -vel.x;
}

void Ball::ReboundY()
{
	vel.y = -vel.y;
}

RectF Ball::GetRect() const
{
	return RectF::FromCenter(pos, radius, radius);
}

Vec2 Ball::GetVelocity() const
{
	return vel;
}

Vec2 Ball::GetPosition() const
{
	return pos;
}

void Ball::SetDirection(const Vec2 dir)
{
	// Velocity equals to direction * speed
	vel = dir.GetNormalized() * speed;
}
