#pragma once
#include "Object.h"

class CFramework;

class CScene
{
public:
	// CScene::SceneTag:: �������� �ҷ��� �ܿ� �ʿ䵵 define�� �ʿ䵵 ���� ���� ���빰�� �� �� �ִ�. �� ������ϸ� include ����.
	enum SceneTag {
		Title
		, Main
		, Ingame
		, Count			// Scene�� ������ ��Ÿ���� ���� �ӽ� �±��̴�. ������ ����.
	};
public:
	CScene();
	CScene(SceneTag tag, CFramework* pFramework);
	virtual ~CScene();	// CScene�� ��ӹ��� Ÿ��Ʋ���� �Ҹ��ڵ� ~CScene();�� �ȴ�. �׷� Ÿ��Ʋ���� �Ҹ��� �� �� �Ҹ��ڵ� �޾ƿ´�.
						// �̹� �Ҹ��ڰ� �ִµ� Ÿ��Ʋ���� ���������� �Ű�Ἥ ���� �ʿ䰡 ����. ����, virtual�� �ٿ� ��ӹ޾� �Ҹ��Ų��.
						// virtual Ÿ�� ���� Ŭ������ ������ �ö� ����, ���� �Ҹ��ڸ� ���� ȣ���ؼ� ��ӹ��� Ŭ������ �ѹ��� �Ҹ��Ű�� ���̴�.

	virtual void OnCreate() = 0;		// ���鶧 ����� �Լ�
	virtual void OnDestroy() = 0;		// ����

	virtual void BuildObjects() = 0;
	virtual void InitBuffer(GLint s_program) = 0;
	virtual void InitTexture(GLint s_program) = 0;

	virtual void Update(float fTimeElapsed) = 0;
	virtual void Render() = 0;

	virtual void KeyboardMessage(unsigned char inputKey) = 0;
	virtual void SpecialKeyboardMessage(int inputKey) = 0;

	virtual void CameraSetting() = 0;
	virtual void ProjectionSetting() = 0;
	virtual void LightSetting() = 0;

protected:
	SceneTag m_Tag;
	CFramework* m_pFramework;	// ���ڷ� �޾ƿ��°� �ƴ϶� �����Ҵ��� �ؿ´�.

	GLint s_program;
};

