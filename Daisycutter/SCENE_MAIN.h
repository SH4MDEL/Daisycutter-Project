#pragma once
#include "Scene.h"
#include "Framework.h"
#include "OBJECT_SUN.h"
#include "OBJECT_EARTH.h"
#include "OBJECT_MOON.h"

class SCENE_MAIN : public CScene
{
public:
	SCENE_MAIN();
	SCENE_MAIN(SceneTag tag, CFramework* pFramework);
	~SCENE_MAIN() override;

	void OnCreate() override;
	void OnDestroy() override;							// ������ ������Ʈ �ı�. �����Ҵ� ���� ���ֱ�

	void BuildObjects() override;
	void InitBuffer(GLint s_program) override;			// ���α׷��� ����� �� �ѹ� �Ҹ��ϴ�. 
														// �� �� ���� ������Ʈ�� ������ ���� ������Ʈ���� ���� ȣ������� �մϴ�.
														// (��� ���������� �𸣰ڴ� �Ф�)

	void Render() override;								// FrameAdvanced
	void Update(float fTimeElapsed) override;			// m_pCurrScene->Update();

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

