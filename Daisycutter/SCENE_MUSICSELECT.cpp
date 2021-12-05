#include "SCENE_MUSICSELECT.h"
#include "SCENE_TITLE.h"

SCENE_MUSICSELECT::SCENE_MUSICSELECT()
{

}

SCENE_MUSICSELECT::SCENE_MUSICSELECT(SceneTag tag, CFramework* pFramework) : CScene(tag, pFramework)
{
	this->OnCreate();
}

SCENE_MUSICSELECT::~SCENE_MUSICSELECT()
{
	this->OnDestroy();
}

void SCENE_MUSICSELECT::OnCreate()
{
	this->BuildObjects();

	fCameraPosTimer = 0.0f;
	fCameraPosArray[0][0] = 10.0f * (GLfloat)sin(2 * M_PI / 360 * 70) * (GLfloat)cos(2 * M_PI / 360 * 90);
	fCameraPosArray[0][1] = 10.0f * (GLfloat)sin(2 * M_PI / 360 * 70) * (GLfloat)sin(2 * M_PI / 360 * 90);
	fCameraPosArray[0][2] = 10.0f * (GLfloat)cos(2 * M_PI / 360 * 70);

	fCameraPosArray[1][0] = 10.0f * (GLfloat)sin(2 * M_PI / 360 * 60) * (GLfloat)cos(2 * M_PI / 360 * 165);
	fCameraPosArray[1][1] = 10.0f * (GLfloat)sin(2 * M_PI / 360 * 60) * (GLfloat)sin(2 * M_PI / 360 * 165);
	fCameraPosArray[1][2] = 10.0f * (GLfloat)cos(2 * M_PI / 360 * 60);

	fCameraPosArray[2][0] = 10.0f * (GLfloat)sin(2 * M_PI / 360 * 120) * (GLfloat)cos(2 * M_PI / 360 * 225);
	fCameraPosArray[2][1] = 10.0f * (GLfloat)sin(2 * M_PI / 360 * 120) * (GLfloat)sin(2 * M_PI / 360 * 225);
	fCameraPosArray[2][2] = 10.0f * (GLfloat)cos(2 * M_PI / 360 * 120);

	fCameraPosArray[3][0] = 10.0f * (GLfloat)sin(2 * M_PI / 360 * 80) * (GLfloat)cos(2 * M_PI / 360 * 300);
	fCameraPosArray[3][1] = 10.0f * (GLfloat)sin(2 * M_PI / 360 * 80) * (GLfloat)sin(2 * M_PI / 360 * 300);
	fCameraPosArray[3][2] = 10.0f * (GLfloat)cos(2 * M_PI / 360 * 80);

	fCameraPosArray[4][0] = 10.0f * (GLfloat)sin(2 * M_PI / 360 * 150) * (GLfloat)cos(2 * M_PI / 360 * 30);
	fCameraPosArray[4][1] = 10.0f * (GLfloat)sin(2 * M_PI / 360 * 150) * (GLfloat)sin(2 * M_PI / 360 * 30);
	fCameraPosArray[4][2] = 10.0f * (GLfloat)cos(2 * M_PI / 360 * 150);

	m_pMusicSound = new SOUND_MUSICSOUND;
	m_pMusicSound->Init();
	m_pMusicSound->Loading();
	// m_pMusicSound->Play(SOUND_MUSICSOUND::SoundTag::Background); 선택된 음악 출력해야 하니까 일단 배경음악은 출력 x

	m_pEffectSound = new SOUND_EFFECTSOUND;
	m_pEffectSound->Init();
	m_pEffectSound->Loading();
}

void SCENE_MUSICSELECT::OnDestroy()
{
	delete field;
	delete player;

	m_pMusicSound->Stop();
	m_pMusicSound->Release();
	delete m_pMusicSound;

	m_pEffectSound->Release();
	delete m_pEffectSound;
}

void SCENE_MUSICSELECT::BuildObjects()
{
	field = new OBJECT_FIELD;
	player = new OBJECT_PLAYER;
}

void SCENE_MUSICSELECT::BindShader()
{
	SM.BindShader();
	InitBuffer();
	InitTexture();
}

void SCENE_MUSICSELECT::InitBuffer()
{
	field->initBuffer(SM.GetShader(ShaderManager::ShaderTag::BitmapShader));
	player->initBuffer(SM.GetShader(ShaderManager::ShaderTag::BitmapShader));
}

void SCENE_MUSICSELECT::InitTexture()
{
	field->initTexture(SM.GetShader(ShaderManager::ShaderTag::BitmapShader));
	player->initTexture(SM.GetShader(ShaderManager::ShaderTag::BitmapShader));
}

void SCENE_MUSICSELECT::Render()
{

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	ManualRender();
	BitmapRender();
	NonBitmapRender();
}

void SCENE_MUSICSELECT::ManualRender()
{
	glUseProgram(SM.GetShader(ShaderManager::ShaderTag::ManualShader));


	modelLocation = glGetUniformLocation(SM.GetShader(ShaderManager::ShaderTag::ManualShader), "ModelTransform");

	glEnable(GL_DEPTH_TEST);


	glDisable(GL_DEPTH_TEST);
}

void SCENE_MUSICSELECT::BitmapRender()
{
	glUseProgram(SM.GetShader(ShaderManager::ShaderTag::BitmapShader));


	modelLocation = glGetUniformLocation(SM.GetShader(ShaderManager::ShaderTag::BitmapShader), "ModelTransform");

	glEnable(GL_DEPTH_TEST);

	field->putFactor(glm::mat4(1.0f));
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(field->getFactor()));
	field->Render();


	player->putFactor(glm::mat4(1.0f));
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(player->getFactor()));
	player->Render();

	glDisable(GL_DEPTH_TEST);
}

void SCENE_MUSICSELECT::NonBitmapRender()
{
	glUseProgram(SM.GetShader(ShaderManager::ShaderTag::NonBitmapShader));


	modelLocation = glGetUniformLocation(SM.GetShader(ShaderManager::ShaderTag::NonBitmapShader), "ModelTransform");

	glEnable(GL_DEPTH_TEST);


	glDisable(GL_DEPTH_TEST);
}

void SCENE_MUSICSELECT::Update(float fTimeElapsed)
{
	field->Update(fTimeElapsed);
	player->Update(fTimeElapsed);

	fCameraPosTimer += fTimeElapsed;
	if (fCameraPosTimer >= 3.0f) {
		fCameraPosTimer -= 3.0f;	// 초기화하지 말고 값을 빼줄것
		SetNextCameraPos();
	}

}

void SCENE_MUSICSELECT::KeyboardMessage(unsigned char inputKey)
{
	switch (inputKey) {
	case 32:	// 'SPACE'
		m_pEffectSound->Play(SOUND_EFFECTSOUND::SoundTag::SelectSound);
		break;
	case 27:	// 'ESCAPE'
		m_pEffectSound->Play(SOUND_EFFECTSOUND::SoundTag::SelectSound);
		m_pFramework->ChangeScene(CScene::SceneTag::Title, new SCENE_TITLE(CScene::SceneTag::Title, m_pFramework));
		break;
	}
}

void SCENE_MUSICSELECT::SpecialKeyboardMessage(int inputKey)
{

}

void SCENE_MUSICSELECT::SetNextCameraPos()
{
	if (iCameraPosIndex == 4) {
		iCameraPosIndex = 0;
	}
	else {
		iCameraPosIndex++;
	}
}
