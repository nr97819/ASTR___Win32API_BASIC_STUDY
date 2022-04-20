#pragma once

// 전방선언
class CObject;

class CScene
{
private:
	// 여러 종류의 Scene들이 각각 vector을 가져야 하므로, 배열로 선언
	// 오브젝트를 저장 및 관리할 벡터를 그룹 개수만큰 선언
	// (@) vector가 여러개인 것이다. 주의. (vector[32]임)
	vector<CObject*>	m_arrObj[(UINT)GROUP_TYPE::END];
	wstring				m_strName; // Scene의 이름

public:
	void SetName(const wstring& _strName) { m_strName = _strName; }
	const wstring& GetName() { return m_strName; }

	// Update와 Render는 모든 자식 Scene들이 똑같이 쓸 것이므로, virtual 안붙임
	void Update();
	void Render(HDC _dc);

	// 부모 쪽에서는 Start()를 쓸 일이 없으므로, 순수가상함수로 만듦
	// -> 그 결과, 순수가상함수를 보유하게 된 CScene이라는 부모 클래스는, 인스턴스 생성 불가능
	// (= 추상클래스) (= interface)
	virtual void Enter() = 0; // 해당 Scene 진입 시 호출
	virtual void Exit() = 0; // 해당 Scene 탈출 시 호출

protected: // (자식에게만 공개)
	// 자식 객체가 함수를 통해서만, vector에 데이터 넣을 수 있도록 함
	// => 이렇게 해야, 추후에 버그나 나도, 호출 스택으로 찾기 쉽다. (필수)
	void AddObject(CObject* _pObj, GROUP_TYPE _eType)
	{
		// 인라인 함수 처리됨 (헤더에 정의했으니까)
		m_arrObj[(UINT)_eType].push_back(_pObj);
	}

public:
	CScene();
	virtual ~CScene();
};

