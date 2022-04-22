#pragma once

class CObject
{
private:
	Vec2	m_vPos;
	Vec2	m_vScale;

public:
	void SetPos(Vec2 _vPos) { m_vPos = _vPos; }
	void SetScale(Vec2 _vScale) { m_vScale = _vScale; }

	Vec2 GetPos() { return m_vPos; }
	Vec2 GetScale() { return m_vScale; }

public:
	// 순수가상함수를 만들어서, => 추상클래스로 만듦
	virtual void Update() = 0; // 자식 객체만의 update가 필요
	void Render(HDC _dc);

public:
	CObject();
	virtual ~CObject();
};

