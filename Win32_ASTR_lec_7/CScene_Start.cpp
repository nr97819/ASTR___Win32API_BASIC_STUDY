#include "pch.h"
#include "CScene_Start.h"

#include "CObject.h"
#include "CPlayer.h"
#include "CMonster.h"

#include "CCore.h"

CScene_Start::CScene_Start()
{

}

CScene_Start::~CScene_Start()
{

}

void CScene_Start::Enter()
{
	// Player의 Update()는 KeyMgr가 있어서 이동함
	CObject* pObj = new CPlayer();
	pObj->SetPos(Vec2(640.f, 384.f));
	pObj->SetScale(Vec2(100.f, 100.f));
	AddObject(pObj, GROUP_TYPE::DEFAULT);

	// 여러 개(x 개)의 Montser를 배치하기
	int iMonCount = 16;
	float fMoveDist = 25.f;
	float fObjScale = 50.f;

	Vec2 vResolution = CCore::GetInst()->GetResolution();

	// Monster 5개가 움직일 공간 확보
	// 양쪽 끝을 활보공간 50에서 Monster의 중심에서의 덩치의 절반인 25만큼을 더해 75만큼에서
	// 총 150을 없애고, 그렇게 남은 공간을 4로 나눔 (5개니까)
	float fTerm = (vResolution.x - ((fMoveDist + fObjScale / 2.f) * 2)) / (float)(iMonCount - 1);

	CMonster* pMonsterObj = nullptr;

	for (int i = 0; i < iMonCount; ++i)
	{
		// Monster Object 1개씩 추가
		// Cobject에 없는 CMonster의 함수를 쓸 것이므로, CObject가 아닌, CMonster로 생성
		pMonsterObj = new CMonster();
		pMonsterObj->SetPos(Vec2((fMoveDist + fObjScale / 2.f) + (float)i * fTerm, 50.f));
		pMonsterObj->SetCenterPos(pMonsterObj->GetPos()); // 첫 위치가 곧 중심점이 되도록
		pMonsterObj->SetMoveDistance(fMoveDist);
		pMonsterObj->SetScale(Vec2(fObjScale, fObjScale));
		AddObject(pMonsterObj, GROUP_TYPE::DEFAULT); // vector에 넣기

	}
}

void CScene_Start::Exit()
{

}
