#include "pch.h"
#include "CObject.h"

CObject::CObject()
	: m_vPos{}
	, m_vScale{}
{

}

CObject::~CObject()
{

}

void CObject::Render(HDC _dc)
{
	Rectangle(_dc
		, static_cast<int>(m_vPos.x - m_vScale.x / 2.f)
		, static_cast<int>(m_vPos.y - m_vScale.y / 2.f)
		, static_cast<int>(m_vPos.x + m_vScale.x / 2.f)
		, static_cast<int>(m_vPos.y + m_vScale.y / 2.f));
}