#pragma once

#define SINGLE(type) public:\
						static type* GetInst()\
						{\
							static type mgr;\
							return &mgr;\
						}\
					private:\
						type();\
						~type();

#define fDT CTimeMgr::GetInst()->GetfDT()
#define DT CTimeMgr::GetInst()->GetDT()


// Player, Missile, Enemy, ���� �׷����� ������ enum
enum class GROUP_TYPE
{
	DEFAULT,

	PLAYER,
	MISSILE,
	MONSTER,

	END = 32
	// ENUM�� �⺻������ �ִ� 32�� ������ �ۼ��� �����ϴ�.
	// (�� ū ����� �ʿ��ϴٸ�, ��������� ǥ���ؾ� �Ѵ�.)
};

enum class SCENE_TYPE
{
	TOOL,
	START,

	STAGE_01,
	STAGE_02,
	STAGE_03,

	END = 32
};