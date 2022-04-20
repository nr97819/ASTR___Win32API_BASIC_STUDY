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
	// ��� �׷��(32��)�� Scene�鿡 ���ؼ� �ݺ� -> vector1[32], vector2[32], vector3[32] ...
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		// �ش� vector[i]�� ���ҵ鿡 ���ؼ� �ݺ� -> vector[1], vector[2], vector[3] ...
		for (size_t j = 0; j < m_arrObj[i].size(); ++j)
		{
			// m_arrObj[i] �׷��� vector�� 'j'��° ��ü�� �����.
			delete m_arrObj[i][j];
		}
	}

	// Scene�� �Ҹ��� ��, vector�� �ڵ����� �Ҹ��Ѵ�. (vector STL�� ��ü �Ҹ���)
	// -> �򰥸����� �������ڸ�, vector �Ҹ��� �츮�� �Ű� �Ƚᵵ �ȴ�.
	// (�츮�� �츮�� "�����Ҵ�"�� �͵鸸 �Ű澲�� �ȴ�.)
}
