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
	// Scene ���� ���� (�ڽĵ�)
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
	// Scene ����
	m_arrScene[(UINT)SCENE_TYPE::START] = new CScene_Start();
	// m_arrScene[(UINT)SCENE_TYPE::TOOL] = new CScene_Tool();
	// m_arrScene[(UINT)SCENE_TYPE::STAGE_01] = new CScene_Stage_01();
	// m_arrScene[(UINT)SCENE_TYPE::STAGE_02] = new CScene_Stage_02();
	// m_arrScene[(UINT)SCENE_TYPE::STAGE_03] = new CScene_Stage_03();
	
	// Scene �̸� ����
	m_arrScene[(UINT)SCENE_TYPE::START]->SetName(L"Start Scene");


	// ���� Scene ����
	// (�ӽ÷� Start_Scene�� �����س��� ��)
	m_pCurScene = m_arrScene[(UINT)SCENE_TYPE::START];

	// �ش� Scene�� �����ϸ鼭, �ʿ��� Object�� ����
	m_pCurScene->Enter();
}

// ���� Scene�� Update �ϰ� �ȴ�.
void CSceneMgr::Update()
{
	m_pCurScene->Update();
}

// ���� Scene�� Render �ϰ� �ȴ�.
void CSceneMgr::Render(HDC _dc)
{
	// Core�κ��� ��� ���޹޾� �Ѿ�� m_memDC ����
	m_pCurScene->Render(_dc);
}
