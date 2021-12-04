#pragma once
#include "Scene.h"
#include "Framework.h"

#include "OBJECT_FIELD.h"
#include "OBJECT_PLAYER.h"

class SCENE_MUSICSELECT : public CScene
{
private:
	GLfloat fCameraPosTimer;

	GLfloat fCameraPosArray[5][3];
	GLint iCameraPosIndex;

public:
	SCENE_MUSICSELECT();
	SCENE_MUSICSELECT(SceneTag tag, CFramework* pFramework);
	~SCENE_MUSICSELECT() override;

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

	unsigned int modelLocation;
};
