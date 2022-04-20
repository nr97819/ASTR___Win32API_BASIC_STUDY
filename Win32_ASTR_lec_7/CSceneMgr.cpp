#include "pch.h"
#include "CSceneMgr.h"

#include "CScene_Start.h"

CSceneMgr::CSceneMgr()
	: m_arrScene{}
	, m_pCurScene(nullptr)
{

}

CSceneMgr::~CSceneMgr()
{
	// Scene 전부 삭제 (자식들)
	for (UINT i = 0; i < (UINT)SCENE_TYPE::END; ++i)
	{
		if (nullptr != m_arrScene[i])
		{
			delete m_arrScene[i];
		}
	}
}

void CSceneMgr::Init()
{
	// Scene 생성
	m_arrScene[(UINT)SCENE_TYPE::START] = new CScene_Start();
	// m_arrScene[(UINT)SCENE_TYPE::TOOL] = new CScene_Tool();
	// m_arrScene[(UINT)SCENE_TYPE::STAGE_01] = new CScene_Stage_01();
	// m_arrScene[(UINT)SCENE_TYPE::STAGE_02] = new CScene_Stage_02();
	// m_arrScene[(UINT)SCENE_TYPE::STAGE_03] = new CScene_Stage_03();
	
	// Scene 이름 지정
	m_arrScene[(UINT)SCENE_TYPE::START]->SetName(L"Start Scene");


	// 현재 Scene 지정
	// (임시로 Start_Scene을 지정해놓은 것)
	m_pCurScene = m_arrScene[(UINT)SCENE_TYPE::START];

	// 해당 Scene에 진입하면서, 필요한 Object들 생성
	m_pCurScene->Enter();
}

// 현재 Scene을 Update 하게 된다.
void CSceneMgr::Update()
{
	m_pCurScene->Update();
}

// 현재 Scene을 Render 하게 된다.
void CSceneMgr::Render(HDC _dc)
{
	// Core로부터 계속 전달받아 넘어온 m_memDC 전달
	m_pCurScene->Render(_dc);
}
