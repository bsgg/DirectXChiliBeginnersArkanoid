#include "Brick.h"

Brick::Brick(const RectF & rect_in, Color color_in)
{
}

void Brick::Draw(Graphics & gfx) const
{
	gfx.DrawRect(rect, color);
}