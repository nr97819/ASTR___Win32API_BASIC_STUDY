#pragma once
#include "CObject.h"

class CMissile :
	public CObject
{
private:
	//float		m_fDir;
	float		m_fTheta; // �̵� ����(����)

public:
	void SetDir(float _fTheta) { m_fTheta = _fTheta; } // �̵� ����(����)

public:
	virtual void Update() override;
	virtual void Render(HDC _dc) override;

public:
	CMissile();
	~CMissile();
};

