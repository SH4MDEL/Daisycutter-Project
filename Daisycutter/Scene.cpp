#include "Scene.h"

//ShaderManager CScene::SM;

CScene::CScene()
{
}

CScene::~CScene()
{
}

CScene::CScene(SceneTag tag, CFramework* pFramework)
{
	m_Tag = tag;
	m_pFramework = pFramework;
}
