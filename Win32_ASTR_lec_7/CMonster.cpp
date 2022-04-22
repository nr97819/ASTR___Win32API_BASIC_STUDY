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

	// ���� ��������, �ð���, m_fSpeed ��ŭ �̵�
	vCurPos.x += fDT * m_fSpeed * m_iDir; // deltaTime * speed * direction

	// m_fMaxDistance�� �ʰ��� �� => fDist
	float fDist = abs(m_vCenterPos.x - vCurPos.x) - m_fMaxDistance;

	if (0.f < fDist)
	{
		// �ʰ��� ��ŭ, �ݴ� �������� �̵���Ŵ(�ǵ�����) -> ���� ����
		m_iDir *= -1;
		vCurPos.x += fDist * m_iDir;
	}

	SetPos(vCurPos);
}
