#include "pch.h"
#include "CScene.h"

#include "CObject.h"

void CScene::Update()
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		for (size_t j = 0; j < m_arrObj[i].size(); ++j)
		{
			m_arrObj[i][j]->Update();
		}
	}
}

void CScene::Render(HDC _dc)
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		for (size_t j = 0; j < m_arrObj[i].size(); ++j)
		{
			m_arrObj[i][j]->Render(_dc);
		}
	}
}

CScene::CScene()
{

}

CScene::~CScene()
{
	// 모든 그룹들(32개)의 Scene들에 대해서 반복 -> vector1[32], vector2[32], vector3[32] ...
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		// 해당 vector[i]의 원소들에 대해서 반복 -> vector[1], vector[2], vector[3] ...
		for (size_t j = 0; j < m_arrObj[i].size(); ++j)
		{
			// m_arrObj[i] 그룹의 vector의 'j'번째 물체를 지운다.
			delete m_arrObj[i][j];
		}
	}

	// Scene이 소멸할 때, vector는 자동으로 소멸한다. (vector STL의 자체 소멸자)
	// -> 헷갈리지만 정리하자면, vector 소멸은 우리가 신경 안써도 된다.
	// (우리는 우리가 "동적할당"한 것들만 신경쓰면 된다.)
}
