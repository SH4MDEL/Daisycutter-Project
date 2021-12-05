#pragma once
#include "Scene.h"
#include "Framework.h"

#include "OBJECT_FIELD.h"
#include "OBJECT_PLAYER.h"
#include "OBJECT_MANUAL.h"

class SCENE_TITLE : public CScene
{
private:
	GLfloat fCameraPosTimer;

	GLfloat fCameraPosArray[5][3];
	GLint iCameraPosIndex;

	GLint iPhaseIndex;
public:
	enum PhaseTag {
		TitlePhase
		, Music1Phase
		, Music2Phase
		, Count
	};

	SCENE_TITLE();
	SCENE_TITLE(SceneTag tag, CFramework* pFramework);
	~SCENE_TITLE() override;

	void OnCreate() override;
	void OnDestroy() override;							// ������ ������Ʈ �ı�. �����Ҵ� ���� ���ֱ�

	void BuildObjects() override;
	void InitBuffer() override;			// ���α׷��� ����� �� �ѹ� �Ҹ��ϴ�. 
	void InitTexture() override;			// �� �� ���� ������Ʈ�� ������ ���� ������Ʈ���� ���� ȣ������� �մϴ�.
														// (��� ���������� �𸣰ڴ� �Ф�)
	void BindShader() override;
	void Render() override;								// FrameAdvanced
	void BitmapRender();
	void NonBitmapRender();
	void ManualRender();

	void Update(float fTimeElapsed) override;			// m_pCurrScene->Update();

	void KeyboardMessage(unsigned char inputKey) override;
	void SpecialKeyboardMessage(int inputKey) override;

	void SetNextCameraPos();
private:
	OBJECT_FIELD* field = NULL;
	OBJECT_PLAYER* player = NULL;
	OBJECT_MANUAL* manual = NULL;

	unsigned int modelLocation;
};


