#pragma once
#include "CObject.h"

class CMissile :
	public CObject
{
private:
	//float		m_fDir;
	float		m_fTheta; // �̵� ����(����)

	Vec2		m_vDir;

public:
	void SetDir(float _fTheta) { m_fTheta = _fTheta; } // �̵� ����(����)
	void SetDir(Vec2 _vDir) 
	{ 
		m_vDir = _vDir;
		m_vDir.Normalize(); // (x, y) ���� -> Length 1�� �ش��ϴ� (x, y) ������ �ٲ㼭 ��ȯ���ش�.
		// ���̰� 1�̶� ���������� ����������. (���⵵ ����, ���̵� 1¥���� ������)
	}

public:
	virtual void Update() override;
	virtual void Render(HDC _dc) override;

public:
	CMissile();
	~CMissile();
};

