#include "pch.h"
#include "CScene_Start.h"

#include "CObject.h"

void CScene_Start::Enter()
{

}

void CScene_Start::Exit()
{

}

CScene_Start::CScene_Start()
{
	// Object�� �߰�
	CObject* pObj = new CObject;

	pObj->SetPos(Vec2(640.f, 384.f)); // 1280 * 780�� �߰�
	pObj->SetScale(Vec2(100.f, 100.f));

	AddObject(pObj, GROUP_TYPE::DEFAULT);
}

CScene_Start::~CScene_Start()
{

}
