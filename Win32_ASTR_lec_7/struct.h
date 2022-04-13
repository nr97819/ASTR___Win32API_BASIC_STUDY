#pragma once

// 우리가 직접 설계한 구조체들을 모아놓는 header 파일이다.

// 크기(scala), 방향(Direct)을 동시에 나타내는 수학적 기호 Vector로 네이밍
struct Vec2
{
	float x;
	float y;

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

	~Vec2()
	{}
};