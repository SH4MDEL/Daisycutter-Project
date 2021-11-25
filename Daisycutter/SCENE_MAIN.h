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
	void OnDestroy() override;							// 생성한 오브젝트 파괴. 동적할당 해제 해주기

	void BuildObjects() override;
	void InitBuffer(GLint s_program) override;			// 프로그램이 실행될 때 한번 불립니다. 
														// 그 외 새로 오브젝트가 생성될 때는 오브젝트별로 직접 호출해줘야 합니다.
														// (어떻게 만들어야할지 모르겠다 ㅠㅠ)

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

