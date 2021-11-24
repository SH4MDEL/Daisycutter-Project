#include "Framework.h"

// 타이틀 씬 등을 include

CFramework::CFramework()
{

}

CFramework::~CFramework()
{
	OnDestroy();
}

bool CFramework::OnCreate(const RECT& rc)
{
	m_current_time = std::chrono::system_clock::now();
	m_fps = 0;
}

bool CFramework::OnDestroy()
{
	delete m_pCurrScene;
}

void CFramework::Update(float fTimeElapsed)
{
	m_pCurrScene->Update(fTimeElapsed);
}

void CFramework::Render()
{
	m_pCurrScene->Render();
}

void CFramework::ChangeScene(CScene::SceneTag tag, CScene* NowScene)
{
	m_pCurrScene->OnDestroy();
	m_pCurrScene = NowScene;
}