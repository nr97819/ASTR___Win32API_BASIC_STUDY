#include "pch.h"
#include "CMissile.h"

#include "CTimeMgr.h"

CMissile::CMissile()
	: m_fDir(1.f) // À§ : 1, ¾Æ·¡ ; -1 (°ö¼ÀÀ» À§ÇÔ)
{

}

CMissile::~CMissile()
{

}

void CMissile::Update()
{
	Vec2 vPos = GetPos();
	vPos.y += 600.f * fDT * m_fDir;
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
