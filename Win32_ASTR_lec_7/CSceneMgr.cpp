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
	m_arrScene[(UINT)SCENE_TYPE::START]->SetName(L"Start Scene");
	// m_arrScene[(UINT)SCENE_TYPE::TOOL] = new CScene_Tool();
	// m_arrScene[(UINT)SCENE_TYPE::STAGE_01] = new CScene_Stage_01();
	// m_arrScene[(UINT)SCENE_TYPE::STAGE_02] = new CScene_Stage_02();
	// m_arrScene[(UINT)SCENE_TYPE::STAGE_03] = new CScene_Stage_03();
	
	// 현재 씬 지정
	m_pCurScene = m_arrScene[(UINT)SCENE_TYPE::START];
	m_pCurScene->Enter();
}

void CSceneMgr::Update()
{
	m_pCurScene->Update();
}

void CSceneMgr::Render(HDC _dc)
{
	m_pCurScene->Render(_dc);
}
