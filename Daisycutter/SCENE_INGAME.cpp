#include "SCENE_INGAME.h"
#include "SCENE_TITLE.h"
#include "OBJECT_MANUAL.h"

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
	char Text[100];
	std::fstream EnemyObjectDataFile;
	iEnemyObjectNum = 0;
	sprintf(Text, "DATA\\MUSIC%d.txt", m_pFramework->GetSelectMusic() + 1);
	EnemyObjectDataFile.open(Text);
	if (EnemyObjectDataFile.is_open()) {
		while (!EnemyObjectDataFile.eof()) {
			EnemyObjectDataFile.get(cEnemyObjectData[iEnemyObjectNum]);
			iEnemyObjectNum++;
		}
	}
	EnemyObjectDataFile.close();

	fCameraPosArray[0][0] = 8.0f * (GLfloat)sin(2 * M_PI / 360 * 20) * (GLfloat)cos(2 * M_PI / 360 * 90);
	fCameraPosArray[0][1] = 8.0f * (GLfloat)sin(2 * M_PI / 360 * 20) * (GLfloat)sin(2 * M_PI / 360 * 90);
	fCameraPosArray[0][2] = 8.0f * (GLfloat)cos(2 * M_PI / 360 * 20);

	fCameraPosArray[1][0] = 8.0f * (GLfloat)sin(2 * M_PI / 360 * 20) * (GLfloat)cos(2 * M_PI / 360 * 90);
	fCameraPosArray[1][1] = 8.0f * (GLfloat)sin(2 * M_PI / 360 * 20) * (GLfloat)sin(2 * M_PI / 360 * 90);
	fCameraPosArray[1][2] = 8.0f * (GLfloat)cos(2 * M_PI / 360 * 20);

	fCameraPosArray[2][0] = 15.0f * (GLfloat)sin(2 * M_PI / 360 * 150) * (GLfloat)cos(2 * M_PI / 360 * 30);
	fCameraPosArray[2][1] = 15.0f * (GLfloat)sin(2 * M_PI / 360 * 150) * (GLfloat)sin(2 * M_PI / 360 * 30);
	fCameraPosArray[2][2] = 15.0f * (GLfloat)cos(2 * M_PI / 360 * 150);

	fCameraPosArray[3][0] = 20.0f * (GLfloat)sin(2 * M_PI / 360 * 20) * (GLfloat)cos(2 * M_PI / 360 * 90);
	fCameraPosArray[3][1] = 20.0f * (GLfloat)sin(2 * M_PI / 360 * 20) * (GLfloat)sin(2 * M_PI / 360 * 90);
	fCameraPosArray[3][2] = 20.0f * (GLfloat)cos(2 * M_PI / 360 * 20);

	m_pMusicSound = new SOUND_MUSICSOUND;
	m_pMusicSound->Init();
	m_pMusicSound->Loading();

	m_pEffectSound = new SOUND_EFFECTSOUND;
	m_pEffectSound->Init();
	m_pEffectSound->Loading();

	iCameraPosIndex = 0, iPhaseIndex = ReadyPhase, iManualIndex = -1;
	fPhaseTimer = 0.0f;
	dNextNoteReadTimer = 0.0;
	iNoteReadPoint = 0;

	this->BuildObjects();
}

void SCENE_INGAME::OnDestroy()
{
	delete field;
	delete cloud;
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
	cloud = new OBJECT_CLOUD;
	player = new OBJECT_PLAYER;
	enemy = new OBJECT_ENEMY(m_pMusicSound->Get_BPM(m_pFramework->GetSelectMusic()));
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
	cloud->initBuffer(SM.GetShader(ShaderManager::ShaderTag::NonBitmapShader));
	player->initBuffer(SM.GetShader(ShaderManager::ShaderTag::BitmapShader));
	enemy->initBuffer(SM.GetShader(ShaderManager::ShaderTag::BitmapShader));
	enemy->putParticleShader(SM.GetShader(ShaderManager::ShaderTag::NonBitmapShader));
	manual->initBuffer(SM.GetShader(ShaderManager::ShaderTag::ManualShader));
}

void SCENE_INGAME::InitTexture()
{
	field->initTexture(SM.GetShader(ShaderManager::ShaderTag::BitmapShader));
	cloud->initTexture(SM.GetShader(ShaderManager::ShaderTag::NonBitmapShader));
	player->initTexture(SM.GetShader(ShaderManager::ShaderTag::BitmapShader));
	enemy->initTexture(SM.GetShader(ShaderManager::ShaderTag::BitmapShader));
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

	//glEnable(GL_DEPTH_TEST);

	if (iManualIndex != -1) {
		manual->putFactor(glm::mat4(1.0f));
		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(manual->getFactor()));
		manual->Render(iManualIndex);
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

	enemy->Render(modelLocation);

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

	cloud->Render(modelLocation);
	enemy->ParticleRender(modelLocation);

	glDisable(GL_DEPTH_TEST);
}

void SCENE_INGAME::Update(float fTimeElapsed)
{
	field->Update(fTimeElapsed);
	cloud->Update(fTimeElapsed);
	player->Update(fTimeElapsed);
	enemy->Update(fTimeElapsed);
	manual->Update(fTimeElapsed);

	m_pMusicSound->Update();

	if (iPhaseIndex == ReadyPhase) {
		fPhaseTimer += fTimeElapsed;

		if (fPhaseTimer >= 2.0f && fPhaseTimer < 3.0f) {
			iManualIndex = OBJECT_MANUAL::ManualTag::NUMBER3;
		}
		else if (fPhaseTimer >= 3.0f && fPhaseTimer < 4.0f) {
			iManualIndex = OBJECT_MANUAL::ManualTag::NUMBER2;
		}
		else if (fPhaseTimer >= 4.0f && fPhaseTimer < 5.0f) {
			iManualIndex = OBJECT_MANUAL::ManualTag::NUMBER1;
		}
		else if (fPhaseTimer >= 5.0f && fPhaseTimer < 6.0f) {
			iManualIndex = OBJECT_MANUAL::ManualTag::OPERATION_START;
		}
		else if (fPhaseTimer >= 6.0f) {
			iManualIndex = player->getHP() + OBJECT_MANUAL::ManualTag::HP_BAR0;
			fPhaseTimer -= 6.0f;
			iPhaseIndex = GamePhase;
			m_pMusicSound->Play(m_pFramework->GetSelectMusic());
		}
	}
	else if (iPhaseIndex == GamePhase) {
		iManualIndex = player->getHP() + OBJECT_MANUAL::ManualTag::HP_BAR0;
		fPhaseTimer += fTimeElapsed;
		dNextNoteReadTimer += fTimeElapsed;

		if (dNextNoteReadTimer >= 1.0 / (m_pMusicSound->Get_BPM(m_pFramework->GetSelectMusic()) / SECOND_PER_MINITE * 4.0)) {
			dNextNoteReadTimer -= 1.0 / (m_pMusicSound->Get_BPM(m_pFramework->GetSelectMusic()) / SECOND_PER_MINITE * 4.0);
			if (cEnemyObjectData[iNoteReadPoint] >= 49 && cEnemyObjectData[iNoteReadPoint] <= 57) {
				enemy->EnemyCreate(cEnemyObjectData[iNoteReadPoint] - 48);
			}
			iNoteReadPoint++;
			if (iNoteReadPoint > iEnemyObjectNum) {
				fPhaseTimer = 0.0f;
				iPhaseIndex = ClearPhase;
				iCameraPosIndex = 1;
				m_pMusicSound->Stop();
			}
		}

		for (int i = 0; i < MAX_ENEMY_CREATE; i++) {
			if (enemy->getOz(i) >= 10.0f) {
				m_pEffectSound->Play(SOUND_EFFECTSOUND::SoundTag::HitSound);
				enemy->EnemyRemove(i);
				player->PlayerAttacked();
				if (player->getHP() == 0) {
					iManualIndex = player->getHP() + OBJECT_MANUAL::ManualTag::HP_BAR0;
					fPhaseTimer = 0.0f;
					if (iPhaseIndex != ClearPhase) {
						iPhaseIndex = DiePhase;
					}
					iCameraPosIndex = 1;
					m_pMusicSound->Stop();
				}
			}
		}
	}
	else if (iPhaseIndex == DiePhase) {
		fPhaseTimer += fTimeElapsed;

		if (fPhaseTimer >= 1.0f && fPhaseTimer < 4.0f) {
			fCameraPosArray[1][0] = fCameraPosArray[0][0] + (fCameraPosArray[2][0] - fCameraPosArray[0][0]) / 2 * (fPhaseTimer - 1.0f);
			fCameraPosArray[1][1] = fCameraPosArray[0][1] + (fCameraPosArray[2][1] - fCameraPosArray[0][1]) / 2 * (fPhaseTimer - 1.0f);
			fCameraPosArray[1][2] = fCameraPosArray[0][2] + (fCameraPosArray[2][2] - fCameraPosArray[0][2]) / 2 * (fPhaseTimer - 1.0f);
		}
		else if (fPhaseTimer >= 4.0f) {
			iCameraPosIndex = 2;
			iManualIndex = OBJECT_MANUAL::ManualTag::GAME_OVER;
		}
	}
	else if (iPhaseIndex == ClearPhase) {
		fPhaseTimer += fTimeElapsed;

		if (fPhaseTimer >= 2.0f && fPhaseTimer < 5.0f) {
			fCameraPosArray[1][0] = fCameraPosArray[0][0] + (fCameraPosArray[3][0] - fCameraPosArray[0][0]) / 3 * (fPhaseTimer - 2.0f);
			fCameraPosArray[1][1] = fCameraPosArray[0][1] + (fCameraPosArray[3][1] - fCameraPosArray[0][1]) / 3 * (fPhaseTimer - 2.0f);
			fCameraPosArray[1][2] = fCameraPosArray[0][2] + (fCameraPosArray[3][2] - fCameraPosArray[0][2]) / 3 * (fPhaseTimer - 2.0f);
		}
		else if (fPhaseTimer >= 5.0f) {
			iCameraPosIndex = 3;
			iManualIndex = OBJECT_MANUAL::ManualTag::GAME_CLEAR;
		}
	}
}

void SCENE_INGAME::KeyboardMessage(unsigned char inputKey)
{
	switch (inputKey) {
	case 32:	// 'SPACE'
		if (iPhaseIndex == GamePhase && enemy->EnemyAttacked()) {
			m_pEffectSound->Play(SOUND_EFFECTSOUND::SoundTag::AttackSound);
		}
		else {
			m_pEffectSound->Play(SOUND_EFFECTSOUND::SoundTag::SelectSound);
		}
		if (iPhaseIndex == DiePhase && fPhaseTimer >= 4.0f) {
			m_pFramework->ChangeScene(CScene::SceneTag::Title, new SCENE_TITLE(CScene::SceneTag::Title, m_pFramework));
		}
		else if (iPhaseIndex == ClearPhase && fPhaseTimer >= 4.0f) {
			m_pFramework->ChangeScene(CScene::SceneTag::Title, new SCENE_TITLE(CScene::SceneTag::Title, m_pFramework));
		}
		break;
	case 27:	// 'ESCAPE'
		m_pEffectSound->Play(SOUND_EFFECTSOUND::SoundTag::SelectSound);
		m_pFramework->ChangeScene(CScene::SceneTag::Title, new SCENE_TITLE(CScene::SceneTag::Title, m_pFramework));
		break;
	}
}

void SCENE_INGAME::SpecialKeyboardMessage(int inputKey)
{

}