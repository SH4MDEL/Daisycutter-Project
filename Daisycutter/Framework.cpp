#include "Framework.h"

#include "SCENE_TITLE.h"

CFramework::CFramework()
{
	m_pCurrScene = new SCENE_TITLE(CScene::SceneTag::Main, this);
}

CFramework::~CFramework()
{
	OnDestroy();
}

bool CFramework::OnCreate(const RECT& rc)
{
	m_current_time = std::chrono::system_clock::now();
	m_fps = 0;
	return true;
}

bool CFramework::OnDestroy()
{
	m_pCurrScene->~CScene();
	return true;
}

void CFramework::InitBuffer(GLint s_program)
{
	this->s_program = s_program;
	m_pCurrScene->InitBuffer(s_program);
}

void CFramework::Update(float fTimeElapsed)
{
	m_pCurrScene->Update(fTimeElapsed);
}

void CFramework::Render()
{
	m_pCurrScene->Render();
}

void CFramework::FrameAdvance()
{
	m_timeElapsed = std::chrono::system_clock::now() - m_current_time;
	if (m_timeElapsed.count() > MAX_FPS)
	{
		m_current_time = std::chrono::system_clock::now();

		Update((float)m_timeElapsed.count());

		if (m_timeElapsed.count() > 0.0)
			m_fps = 1.0 / m_timeElapsed.count();
	}
}

void CFramework::KeyboardMessage(unsigned char inputKey)
{
	m_pCurrScene->KeyboardMessage(inputKey);
}

void CFramework::SpecialKeyboardMessage(int inputKey)
{
	m_pCurrScene->SpecialKeyboardMessage(inputKey);
}

void CFramework::ChangeScene(CScene::SceneTag tag, CScene* NowScene)
{
	delete m_pCurrScene;
	NowScene->InitBuffer(this->s_program);
	m_pCurrScene = NowScene;
}