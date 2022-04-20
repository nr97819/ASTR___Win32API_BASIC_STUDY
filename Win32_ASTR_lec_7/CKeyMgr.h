#pragma once

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

	LAST
};

enum class KEY_STATE
{
	NONE,
	TAP,
	HOLD,
	AWAY,
};

struct tKeyInfo
{
	KEY_STATE	estate;
	bool		ePrevPush;
};

class CKeyMgr
{
	SINGLE(CKeyMgr);
private:
	vector<tKeyInfo> m_vecKey;

public:
	void Init();
	void Update();
	KEY_STATE GetKeyState(KEY _eKey) { return m_vecKey[(int)_eKey].estate; }
};

