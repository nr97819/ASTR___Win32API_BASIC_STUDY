#pragma once

struct Vec2
{
	float x;
	float y;

public:
	float Length()
	{
		return sqrt(x * x + y * y);
	}

	Vec2& Normalize()
	{
		float fLen = Length();

		assert(fLen != 0.f); // 0.f가 아니라면, assert가 trigger된다.

		x /= fLen;
		y /= fLen;

		return *this;
	}

public:
	Vec2& operator=(const POINT _pt)
	{
		x = (float)_pt.x;
		y = (float)_pt.y;
	}

public:
	Vec2()
		: x(0.f)
		, y(0.f)
	{}

	Vec2(float _x, float _y)
		: x(_x)
		, y(_y)
	{}

	Vec2(int _x, int _y)
		: x((float)_x)
		, y((float)_y)
	{}

	Vec2(const POINT _pt)
		: x((float)_pt.x)
		, y((float)_pt.y)
	{}

	~Vec2()
	{}
};