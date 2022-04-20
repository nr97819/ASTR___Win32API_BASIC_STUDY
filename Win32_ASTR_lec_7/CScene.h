#pragma once

// ���漱��
class CObject;

class CScene
{
private:
	// ���� ������ Scene���� ���� vector�� ������ �ϹǷ�, �迭�� ����
	// ������Ʈ�� ���� �� ������ ���͸� �׷� ������ū ����
	// (@) vector�� �������� ���̴�. ����. (vector[32]��)
	vector<CObject*>	m_arrObj[(UINT)GROUP_TYPE::END];
	wstring				m_strName; // Scene�� �̸�

public:
	void SetName(const wstring& _strName) { m_strName = _strName; }
	const wstring& GetName() { return m_strName; }

	// Update�� Render�� ��� �ڽ� Scene���� �Ȱ��� �� ���̹Ƿ�, virtual �Ⱥ���
	void Update();
	void Render(HDC _dc);

	// �θ� �ʿ����� Start()�� �� ���� �����Ƿ�, ���������Լ��� ����
	// -> �� ���, ���������Լ��� �����ϰ� �� CScene�̶�� �θ� Ŭ������, �ν��Ͻ� ���� �Ұ���
	// (= �߻�Ŭ����) (= interface)
	virtual void Enter() = 0; // �ش� Scene ���� �� ȣ��
	virtual void Exit() = 0; // �ش� Scene Ż�� �� ȣ��

protected: // (�ڽĿ��Ը� ����)
	// �ڽ� ��ü�� �Լ��� ���ؼ���, vector�� ������ ���� �� �ֵ��� ��
	// => �̷��� �ؾ�, ���Ŀ� ���׳� ����, ȣ�� �������� ã�� ����. (�ʼ�)
	void AddObject(CObject* _pObj, GROUP_TYPE _eType)
	{
		// �ζ��� �Լ� ó���� (����� ���������ϱ�)
		m_arrObj[(UINT)_eType].push_back(_pObj);
	}

public:
	CScene();
	virtual ~CScene();
};

