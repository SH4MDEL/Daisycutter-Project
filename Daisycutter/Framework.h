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

	void Update(float fTimeElapsed);
	void Render();

	//void curSceneCreate();
	//void BuildScene(CScene::SceneTag tag);
	void ChangeScene(CScene::SceneTag tag, CScene* NowScene);
private:
	//CScene* arrScene[CScene::SceneTag::Count];
	CScene* m_pCurrScene;
};

