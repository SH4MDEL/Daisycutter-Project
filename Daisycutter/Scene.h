#pragma once
#include "Object.h"

class CFramework;

class CScene
{
public:
	// CScene::SceneTag:: 형식으로 불러서 외울 필요도 define할 필요도 없이 안의 내용물을 쓸 수 있다. 이 헤더파일만 include 하자.
	enum SceneTag {
		Title
		, Main
		, Ingame
		, Count			// Scene의 개수를 나타내기 위한 임시 태그이다. 지우지 말자.
	};
public:
	CScene();
	CScene(SceneTag tag, CFramework* pFramework);
	virtual ~CScene();	// CScene을 상속받은 타이틀씬의 소멸자도 ~CScene();이 된다. 그럼 타이틀씬이 소멸할 때 이 소멸자도 받아온다.
						// 이미 소멸자가 있는데 타이틀씬이 상위계층을 신경써서 지울 필요가 없다. 따라서, virtual을 붙여 상속받아 소멸시킨다.
						// virtual 타고 상위 클래스의 끝까지 올라간 다음, 하위 소멸자를 전부 호출해서 상속받은 클래스를 한번에 소멸시키는 것이다.

	virtual void OnCreate() = 0;		// 만들때 선언용 함수
	virtual void OnDestroy() = 0;		// 삭제

	virtual void BuildObjects() = 0;
	virtual void InitBuffer(GLint s_program) = 0;
	virtual void InitTexture(GLint s_program) = 0;

	virtual void Update(float fTimeElapsed) = 0;
	virtual void Render() = 0;

	virtual void KeyboardMessage(unsigned char inputKey) = 0;
	virtual void SpecialKeyboardMessage(int inputKey) = 0;

	virtual void CameraSetting() = 0;
	virtual void ProjectionSetting() = 0;
	virtual void LightSetting() = 0;

protected:
	SceneTag m_Tag;
	CFramework* m_pFramework;	// 인자로 받아오는게 아니라 동적할당을 해온다.

	GLint s_program;
};

