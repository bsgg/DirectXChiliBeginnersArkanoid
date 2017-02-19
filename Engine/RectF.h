#pragma once

#include "Vec2.h"

class RectF
{

public:
	// Default constructor, including this function, the compiler won't deactivate the default compilare when there is 
	// another compiler with params.
	RectF() = default;	
	RectF(float left_in, float right_in, float top_in, float bottom_in);
	RectF(const Vec2& topLeft, const Vec2& bottomRight);
	RectF(const Vec2& topLeft, float width, float height);
	bool IsOverlappingWidth(const RectF& other) const;
	static RectF FromCenter(const Vec2& center, float halfwidth, float halfHeight);
	RectF GetExpanded(float offset) const;

public:
	float left;
	float right;
	float top;
	float bottom;	 
};
