#pragma once
#include "Scene.h"
#include "Framework.h"

#include "OBJECT_PLAYER.h"

class SCENE_TITLE : public CScene
{
public:
	SCENE_TITLE();
	SCENE_TITLE(SceneTag tag, CFramework* pFramework);
	~SCENE_TITLE() override;

	void OnCreate() override;
	void OnDestroy() override;							// ������ ������Ʈ �ı�. �����Ҵ� ���� ���ֱ�

	void BuildObjects() override;
	void InitBuffer(GLint s_program) override;			// ���α׷��� ����� �� �ѹ� �Ҹ��ϴ�. 
														// �� �� ���� ������Ʈ�� ������ ���� ������Ʈ���� ���� ȣ������� �մϴ�.
														// (��� ���������� �𸣰ڴ� �Ф�)

	void Render() override;								// FrameAdvanced
	void Update(float fTimeElapsed) override;			// m_pCurrScene->Update();

	void KeyboardMessage(unsigned char inputKey) override;
	void SpecialKeyboardMessage(int inputKey) override;

	void CameraSetting() override;
	void ProjectionSetting() override;
	void LightSetting() override;
private:
	OBJECT_PLAYER* player = NULL;

	unsigned int modelLocation;
};


