#include "SCENE_INGAME.h"

SCENE_INGAME::SCENE_INGAME()
{

}

SCENE_INGAME::SCENE_INGAME(SceneTag tag, CFramework* pFramework) : CScene(tag, pFramework)
{
	this->OnCreate();
}

SCENE_INGAME::~SCENE_INGAME()
{
	this->OnDestroy();
}

void SCENE_INGAME::OnCreate()
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
	m_pMusicSound->Play(SOUND_MUSICSOUND::SoundTag::Background);

	m_pEffectSound = new SOUND_EFFECTSOUND;
	m_pEffectSound->Init();
	m_pEffectSound->Loading();

	iPhaseIndex = TitlePhase;
}

void SCENE_INGAME::OnDestroy()
{
	delete field;
	delete player;
	delete manual;

	m_pMusicSound->Stop();
	m_pMusicSound->Release();
	delete m_pMusicSound;

	m_pEffectSound->Release();
	delete m_pEffectSound;
}

void SCENE_INGAME::BuildObjects()
{
	field = new OBJECT_FIELD;
	player = new OBJECT_PLAYER;
	manual = new OBJECT_MANUAL;
}

void SCENE_INGAME::BindShader()
{
	SM.BindShader();
	InitBuffer();
	InitTexture();
}

void SCENE_INGAME::InitBuffer()
{
	field->initBuffer(SM.GetShader(ShaderManager::ShaderTag::BitmapShader));
	player->initBuffer(SM.GetShader(ShaderManager::ShaderTag::BitmapShader));
	manual->initBuffer(SM.GetShader(ShaderManager::ShaderTag::ManualShader));
}

void SCENE_INGAME::InitTexture()
{
	field->initTexture(SM.GetShader(ShaderManager::ShaderTag::BitmapShader));
	player->initTexture(SM.GetShader(ShaderManager::ShaderTag::BitmapShader));
	manual->initTexture(SM.GetShader(ShaderManager::ShaderTag::ManualShader));
}

void SCENE_INGAME::Render()
{

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	BitmapRender();
	NonBitmapRender();
	ManualRender();
}

void SCENE_INGAME::ManualRender()
{
	glUseProgram(SM.GetShader(ShaderManager::ShaderTag::ManualShader));


	glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 50.0f);
	glm::vec3 cameraDirection = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::mat4 view = glm::mat4(1.0f);
	view = glm::lookAt(cameraPos, cameraDirection, cameraUp);
	unsigned int viewLocation = glGetUniformLocation(SM.GetShader(ShaderManager::ShaderTag::ManualShader), "viewTransform");
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &view[0][0]);

	unsigned int viewPos = glGetUniformLocation(SM.GetShader(ShaderManager::ShaderTag::ManualShader), "viewPos");
	glUniform3f(viewPos, fCameraPosArray[iCameraPosIndex][0], fCameraPosArray[iCameraPosIndex][1], fCameraPosArray[iCameraPosIndex][2]);


	glm::mat4 projection = glm::mat4(1.0f);
	projection = glm::perspective(glm::radians(60.0f), 512.0f / 512.0f, 0.1f, 200.0f);
	// projection = glm::ortho(0.0f, 600.0f, 0.0f, 600.0f, 0.1f, 200.0f);

	unsigned int projectionLocation = glGetUniformLocation(SM.GetShader(ShaderManager::ShaderTag::ManualShader), "projectionTransform");	//--- 투영 변환 값 설정
	glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, &projection[0][0]);


	modelLocation = glGetUniformLocation(SM.GetShader(ShaderManager::ShaderTag::ManualShader), "ModelTransform");

	//glEnable(GL_DEPTH_TEST);   //--- 은면 제거로 인해 문제가 발생 했었음.

	if (iPhaseIndex == TitlePhase) {
		manual->putFactor(glm::mat4(1.0f));
		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(manual->getFactor()));
		manual->Render();
	}

	//glDisable(GL_DEPTH_TEST);
}

void SCENE_INGAME::BitmapRender()
{
	glUseProgram(SM.GetShader(ShaderManager::ShaderTag::BitmapShader));

	glm::vec3 cameraPos = glm::vec3(fCameraPosArray[iCameraPosIndex][0], fCameraPosArray[iCameraPosIndex][1], fCameraPosArray[iCameraPosIndex][2]);
	glm::vec3 cameraDirection = glm::vec3(player->getOx(), player->getOy(), player->getOz());
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::mat4 view = glm::mat4(1.0f);
	view = glm::lookAt(cameraPos, cameraDirection, cameraUp);
	unsigned int viewLocation = glGetUniformLocation(SM.GetShader(ShaderManager::ShaderTag::BitmapShader), "viewTransform");
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &view[0][0]);

	unsigned int viewPos = glGetUniformLocation(SM.GetShader(ShaderManager::ShaderTag::BitmapShader), "viewPos");
	glUniform3f(viewPos, fCameraPosArray[iCameraPosIndex][0], fCameraPosArray[iCameraPosIndex][1], fCameraPosArray[iCameraPosIndex][2]);


	glm::mat4 projection = glm::mat4(1.0f);
	projection = glm::perspective(glm::radians(60.0f), (float)1080.0 / (float)1920.0, 0.1f, 3000.0f);
	//projection = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f, 0.1f, 3000.0f);

	unsigned int projectionLocation = glGetUniformLocation(SM.GetShader(ShaderManager::ShaderTag::BitmapShader), "projectionTransform");	//--- 투영 변환 값 설정
	glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, &projection[0][0]);


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

void SCENE_INGAME::NonBitmapRender()
{
	glUseProgram(SM.GetShader(ShaderManager::ShaderTag::NonBitmapShader));


	glm::vec3 cameraPos = glm::vec3(fCameraPosArray[iCameraPosIndex][0], fCameraPosArray[iCameraPosIndex][1], fCameraPosArray[iCameraPosIndex][2]);
	glm::vec3 cameraDirection = glm::vec3(player->getOx(), player->getOy(), player->getOz());
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::mat4 view = glm::mat4(1.0f);
	view = glm::lookAt(cameraPos, cameraDirection, cameraUp);
	unsigned int viewLocation = glGetUniformLocation(SM.GetShader(ShaderManager::ShaderTag::NonBitmapShader), "viewTransform");
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &view[0][0]);

	unsigned int viewPos = glGetUniformLocation(SM.GetShader(ShaderManager::ShaderTag::NonBitmapShader), "viewPos");
	glUniform3f(viewPos, fCameraPosArray[iCameraPosIndex][0], fCameraPosArray[iCameraPosIndex][1], fCameraPosArray[iCameraPosIndex][2]);


	glm::mat4 projection = glm::mat4(1.0f);
	projection = glm::perspective(glm::radians(60.0f), (float)1080.0 / (float)1920.0, 0.1f, 3000.0f);
	//projection = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f, 0.1f, 3000.0f);

	unsigned int projectionLocation = glGetUniformLocation(SM.GetShader(ShaderManager::ShaderTag::NonBitmapShader), "projectionTransform");	//--- 투영 변환 값 설정
	glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, &projection[0][0]);


	modelLocation = glGetUniformLocation(SM.GetShader(ShaderManager::ShaderTag::NonBitmapShader), "ModelTransform");

	glEnable(GL_DEPTH_TEST);



	glDisable(GL_DEPTH_TEST);
}

void SCENE_INGAME::Update(float fTimeElapsed)
{
	field->Update(fTimeElapsed);
	player->Update(fTimeElapsed);
	manual->Update(fTimeElapsed);

	m_pMusicSound->Update();

	fCameraPosTimer += fTimeElapsed;
	if (fCameraPosTimer >= 3.0f) {
		fCameraPosTimer -= 3.0f;	// 초기화하지 말고 값을 빼줄것
		SetNextCameraPos();
	}

}

void SCENE_INGAME::KeyboardMessage(unsigned char inputKey)
{
	switch (inputKey) {
	case '+':
	case '=':
		m_pEffectSound->Play(SOUND_EFFECTSOUND::SoundTag::SelectSound);
		m_pMusicSound->VolumeUp();
		break;
	case '-':
	case '_':
		m_pEffectSound->Play(SOUND_EFFECTSOUND::SoundTag::SelectSound);
		m_pMusicSound->VolumeDown();
		break;
	case '}':
	case ']':
		m_pEffectSound->Play(SOUND_EFFECTSOUND::SoundTag::SelectSound);
		m_pEffectSound->VolumeUp();
		break;
	case '{':
	case '[':
		m_pEffectSound->Play(SOUND_EFFECTSOUND::SoundTag::SelectSound);
		m_pEffectSound->VolumeDown();
		break;
	case 32:	// 'SPACE'
		m_pEffectSound->Play(SOUND_EFFECTSOUND::SoundTag::SelectSound);

		if (iPhaseIndex == TitlePhase) {
			iPhaseIndex = Music1Phase;
		}
		else if (iPhaseIndex == Music1Phase) {
			m_pFramework->ChangeScene(CScene::SceneTag::Ingame, new SCENE_INGAME(CScene::SceneTag::Ingame, m_pFramework));
		}
		else if (iPhaseIndex == Music2Phase) {
			m_pFramework->ChangeScene(CScene::SceneTag::Ingame, new SCENE_INGAME(CScene::SceneTag::Ingame, m_pFramework));
		}
		break;
	case 27:	// 'ESCAPE'
		m_pEffectSound->Play(SOUND_EFFECTSOUND::SoundTag::SelectSound);
		if (iPhaseIndex == TitlePhase) {
			glutLeaveMainLoop();
		}
		else if (iPhaseIndex == Music1Phase) {
			iPhaseIndex = TitlePhase;
		}
		else if (iPhaseIndex == Music2Phase) {
			iPhaseIndex = TitlePhase;
		}
		break;
	}
}

void SCENE_INGAME::SpecialKeyboardMessage(int inputKey)
{

}

void SCENE_INGAME::SetNextCameraPos()
{
	if (iCameraPosIndex == 4) {
		iCameraPosIndex = 0;
	}
	else {
		iCameraPosIndex++;
	}
}
