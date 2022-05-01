#include "pch.h"
#include "CPlayer.h"

#include "CSceneMgr.h"
#include "CKeyMgr.h"
#include "CTimeMgr.h"

#include "CMissile.h"
#include "CScene.h"

CPlayer::CPlayer()
{

}

CPlayer::~CPlayer()
{

}

void CPlayer::Update()
{
	Vec2 vPos = GetPos();

	if (KEY_HOLD(KEY::W))
	{
		vPos.y -= 200.f * fDT;
	}
	if (KEY_HOLD(KEY::S))
	{
		vPos.y += 200.f * fDT;
	}
	if (KEY_HOLD(KEY::A))
	{
		vPos.x -= 200.f * fDT;
	}
	if (KEY_HOLD(KEY::D))
	{
		vPos.x += 200.f * fDT;
	}

	// 미사일 발사
	if (KEY_TAP(KEY::SPACE))
	{
		CreateMissile();
	}

	SetPos(vPos);
}

void CPlayer::CreateMissile()
{
	Vec2 vMisslePos = GetPos();
	vMisslePos.y -= GetScale().y / 2.f;

	// Player의 주둥이에서 missle이 나가도록
	CMissile* pMissile = new CMissile();
	pMissile->SetPos(vMisslePos);
	pMissile->SetScale(Vec2(25.f, 25.f));
	pMissile->SetDir(true); // 위로 발사

	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
	pCurScene->AddObject(pMissile, GROUP_TYPE::DEFAULT);
}
