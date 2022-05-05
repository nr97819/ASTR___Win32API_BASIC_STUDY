#include "pch.h"
#include "CMissile.h"

#include "CTimeMgr.h"

CMissile::CMissile()
	: m_fTheta(PI / 4.f)
	, m_vDir(Vec2(1.f, 1.f)) // 45도 방향을 나타냄
{
	m_vDir.Normalize();
}

CMissile::~CMissile()
{

}

void CMissile::Update()
{
	Vec2 vPos = GetPos();

	//vPos.y += 600.f * fDT * m_fDir;
	
	//vPos.x += 600.f * cosf(m_fTheta) * fDT; // x방향 : COS(theta)
	//vPos.y -= 600.f * sinf(m_fTheta) * fDT; // y방향 : SIN(theta) (- theta 음수로)
	SetDir(Vec2(-1.f, -7.f));

	vPos.x += 600.f * m_vDir.x * fDT;
	vPos.y += 600.f * m_vDir.y * fDT;


	SetPos(vPos);
}

void CMissile::Render(HDC _dc)
{
	Vec2 vPos = GetPos();
	Vec2 vScale = GetScale();

	Ellipse(_dc 
		, static_cast<int>(vPos.x - vScale.x / 2.f)
		, static_cast<int>(vPos.y - vScale.y / 2.f)
		, static_cast<int>(vPos.x + vScale.x / 2.f)
		, static_cast<int>(vPos.y + vScale.y / 2.f));
}
