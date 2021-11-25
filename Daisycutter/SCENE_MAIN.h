#pragma once
#include "Scene.h"
#include "OBJECT_SUN.h"
#include "OBJECT_EARTH.h"
#include "OBJECT_MOON.h"

class SCENE_MAIN : public CScene
{
public:
	SCENE_MAIN();
	SCENE_MAIN(SceneTag tag, CFramework* pFramework);
	~SCENE_MAIN();

	void OnCreate() override;	// 장면 선언 함수
	void OnDestroy() override;			// 만들때 선언한것 해제용 함수

	void BuildObjects() override;
	void InitBuffer(GLint s_program) override;

	void Render() override;				// FrameAdvanced
	void Update(float fTimeElapsed) override;	// m_pCurrScene->Update();

	void KeyboardMessage(unsigned char inputKey) override;

	void CameraSetting() override;
	void ProjectionSetting() override;
	void LightSetting() override;
private:
	OBJECT_SUN* sun = NULL;
	OBJECT_EARTH* earth = NULL;
	OBJECT_MOON* moon = NULL;

	unsigned int modelLocation;
};

