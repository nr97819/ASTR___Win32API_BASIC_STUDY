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


// Player, Missile, Enemy, 등을 그룹으로 나누는 enum
enum class GROUP_TYPE
{
	DEFAULT,

	PLAYER,
	MISSILE,
	MONSTER,

	END = 32
	// ENUM은 기본적으로 최대 32개 까지만 작성이 가능하다.
	// (더 큰 사이즈가 필요하다면, 명시적으로 표시해야 한다.)
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