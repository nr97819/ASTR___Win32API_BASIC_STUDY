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

	// 진행 방향으로, 시간당, m_fSpeed 만큼 이동
	vCurPos.x += fDT * m_fSpeed * m_iDir; // deltaTime * speed * direction

	// m_fMaxDistance를 초과한 양 => fDist
	float fDist = abs(m_vCenterPos.x - vCurPos.x) - m_fMaxDistance;

	if (0.f < fDist)
	{
		// 초과한 만큼, 반대 방향으로 이동시킴(되돌려줌) -> 오차 방지
		m_iDir *= -1;
		vCurPos.x += fDist * m_iDir;
	}

	SetPos(vCurPos);
}
