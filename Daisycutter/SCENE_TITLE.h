#pragma once
#include "Scene.h"
#include "Framework.h"

#include "OBJECT_FIELD.h"
#include "OBJECT_CLOUD.h"
#include "OBJECT_PLAYER.h"
#include "OBJECT_MANUAL.h"

class SCENE_TITLE : public CScene
{
private:
	GLfloat fCameraPosTimer;
	GLfloat fSetGameTimer;

	GLfloat fCameraPosArray[7][3];
	GLint iCameraPosIndex;
	GLint iCameraPosForGameSet;

	GLint iPhaseIndex;

public:
	enum PhaseTag {
		TitlePhase
		, GameSetPhase
		, Music1Phase
		, Music2Phase
		, Count
	};

	SCENE_TITLE();
	SCENE_TITLE(SceneTag tag, CFramework* pFramework);
	~SCENE_TITLE() override;

	void OnCreate() override;
	void OnDestroy() override;							// 생성한 오브젝트 파괴. 동적할당 해제 해주기

	void BuildObjects() override;
	void InitBuffer() override;			// 프로그램이 실행될 때 한번 불립니다. 
	void InitTexture() override;			// 그 외 새로 오브젝트가 생성될 때는 오브젝트별로 직접 호출해줘야 합니다.
														// (어떻게 만들어야할지 모르겠다 ㅠㅠ) <- 오브젝트 자체는 씬 생성부에서 죄다 만들어놓고 그릴지 말지만 결정하면 될듯?
	void BindShader() override;
	void Render() override;								// FrameAdvanced
	void BitmapRender();
	void NonBitmapRender();
	void ManualRender();

	void Update(float fTimeElapsed) override;			// m_pCurrScene->Update();

	void KeyboardMessage(unsigned char inputKey) override;
	void SpecialKeyboardMessage(int inputKey) override;

	void SetNextCameraPos();
	void SetGameSetCameraPos(float fTimeElapsed);
private:
	OBJECT_FIELD* field = NULL;
	OBJECT_CLOUD* cloud = NULL;
	OBJECT_PLAYER* player = NULL;
	OBJECT_MANUAL* manual = NULL;

	unsigned int modelLocation;
};


