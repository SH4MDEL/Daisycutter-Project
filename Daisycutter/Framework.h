#pragma once
#include "stdafx.h"
#include "Scene.h"


class CFramework
{
private:
	std::chrono::system_clock::time_point m_current_time;
	std::chrono::duration<double> m_timeElapsed;		// �ð��� �󸶳� �����°�
	double m_fps;

public:
	CFramework();
	~CFramework();

	bool OnCreate(const RECT &rc);
	bool OnDestroy();

	void InitBuffer(GLint s_program);
	void Update(float fTimeElapsed);
	void Render();

	void FrameAdvance();

	void KeyboardMessage(unsigned char inputKey);
	void SpecialKeyboardMessage(int inputKey);

	//void curSceneCreate();
	//void BuildScene(CScene::SceneTag tag);
	void ChangeScene(CScene::SceneTag tag, CScene* NowScene);		// ���ο� ������ ��ȯ. ���� ���� �ı��ϰ� �Է��� ���� m_pCurrScene�� ����մϴ�.
private:
	//CScene* arrScene[CScene::SceneTag::Count];
	CScene* m_pCurrScene;											// ���� ���� ����Ű�� �ִ� ������.

	GLint s_program;
};

