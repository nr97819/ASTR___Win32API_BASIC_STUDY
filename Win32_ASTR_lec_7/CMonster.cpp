#include "pch.h"
#include "CMonster.h"

#include "CTimeMgr.h"

CMonster::CMonster()
	: m_vCenterPos(Vec2(0.f, 0.f))
	, m_fSpeed(100.f)
	, m_fMaxDistance(50.f)
	, m_iDir(1)
{

}

CMonster::~CMonster()
{

}

void CMonster::Update()
{
	Vec2 vCurPos = GetPos();

	vCurPos.x += fDT * m_fSpeed * m_iDir;
	float fDist = abs(m_vCenterPos.x - vCurPos.x) - m_fMaxDistance;

	if (0.f < fDist)
	{
		m_iDir *= -1;
		vCurPos.x += fDist * m_iDir;
	}

	SetPos(vCurPos);
}
