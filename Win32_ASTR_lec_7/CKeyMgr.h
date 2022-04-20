#pragma once

// 가상키 값이 아닌, 내가 자체적으로 정의
enum class KEY
{
	LEFT, 
	RIGHT, 
	UP, 
	DOWN,
	Q, W, E, R, T,
	Y, U, I, O, P,
	A, S, D, F, G,
	Z, X, C, V, B,
	ALT, 
	CTRL, 
	LSHIFT, 
	SPACE, 
	ENTER, 
	ESC,

	LAST // 반복문(for)에서 쉽게 LAST 원소를 지정하기 위함
};

enum class KEY_STATE
{
	NONE,	// 계속 안눌린 있는 상태
	TAP,	// 막 누른 시점
	HOLD,	// 계속 눌린 상태
	AWAY,	// 막 뗀 시점
};

struct tKeyInfo
{
	KEY_STATE	estate;
	bool		ePrevPush; // 이전 프레임에 눌린 상태였는지
};

class CKeyMgr
{
	SINGLE(CKeyMgr);
private:
	// vector 내의 index가 곧, enum class KEY의 값이다.
	vector<tKeyInfo> m_vecKey;

public:
	void Init();
	void Update();
	KEY_STATE GetKeyState(KEY _eKey) { return m_vecKey[(int)_eKey].estate; }
};

