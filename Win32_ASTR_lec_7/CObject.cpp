#include "pch.h"
#include "CObject.h"

#include "CKeyMgr.h"
#include "CTimeMgr.h"

CObject::CObject()
	: m_vPos{}
	, m_vScale{}
{

}

CObject::~CObject()
{

}

void CObject::Update()
{
	// CCore::Update()로 부터 가져왔다.

	if (CKeyMgr::GetInst()->GetKeyState(KEY::W) == KEY_STATE::HOLD)
	{
		//vPos.y -= 200.f * CTimeMgr::GetInst()->GetfDT();
		m_vPos.y -= 200.f * fDT;
	}
	if (CKeyMgr::GetInst()->GetKeyState(KEY::S) == KEY_STATE::HOLD)
	{
		m_vPos.y += 200.f * fDT;
	}
	if (CKeyMgr::GetInst()->GetKeyState(KEY::A) == KEY_STATE::HOLD)
	{
		m_vPos.x -= 200.f * fDT;
	}
	if (CKeyMgr::GetInst()->GetKeyState(KEY::D) == KEY_STATE::HOLD)
	{
		m_vPos.x += 200.f * fDT;
	}
}

void CObject::Render(HDC _dc)
{
	// CCore::Render로 부터 가져왔다.

	Rectangle(_dc
		, static_cast<int>(m_vPos.x - m_vScale.x / 2.f)
		, static_cast<int>(m_vPos.y - m_vScale.y / 2.f)
		, static_cast<int>(m_vPos.x + m_vScale.x / 2.f)
		, static_cast<int>(m_vPos.y + m_vScale.y / 2.f));
}