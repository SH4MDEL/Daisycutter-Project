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

	void OnCreate() override;	// ��� ���� �Լ�
	void OnDestroy() override;			// ���鶧 �����Ѱ� ������ �Լ�

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

