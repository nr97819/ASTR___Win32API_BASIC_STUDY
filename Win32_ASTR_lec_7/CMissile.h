#pragma once
#include "CObject.h"

class CMissile :
	public CObject
{
private:
	//float		m_fDir;
	float		m_fTheta; // 이동 방향(각도)

	Vec2		m_vDir;

public:
	void SetDir(float _fTheta) { m_fTheta = _fTheta; } // 이동 방향(각도)
	void SetDir(Vec2 _vDir) 
	{ 
		m_vDir = _vDir;
		m_vDir.Normalize(); // (x, y) 값이 -> Length 1에 해당하는 (x, y) 값으로 바꿔서 반환해준다.
		// 길이가 1이라서 단위연산이 가능해진다. (방향도 갖고, 길이도 1짜리라서 편해짐)
	}

public:
	virtual void Update() override;
	virtual void Render(HDC _dc) override;

public:
	CMissile();
	~CMissile();
};

