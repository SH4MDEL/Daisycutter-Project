#pragma once
#include "stdafx.h"
#include "Scene.h"


class CFramework
{
private:
	std::chrono::system_clock::time_point m_current_time;
	std::chrono::duration<double> m_timeElapsed;		// 시간이 얼마나 지났는가
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
	void ChangeScene(CScene::SceneTag tag, CScene* NowScene);		// 새로운 씬으로 전환. 현재 씬을 파괴하고 입력한 씬을 m_pCurrScene에 등록합니다.
private:
	//CScene* arrScene[CScene::SceneTag::Count];
	CScene* m_pCurrScene;											// 현재 씬을 가리키고 있는 포인터.

	GLint s_program;
};

