#include "SCENE_TITLE.h"

SCENE_TITLE::SCENE_TITLE()
{

}

SCENE_TITLE::SCENE_TITLE(SceneTag tag, CFramework* pFramework) : CScene(tag, pFramework)
{
	this->OnCreate();
}

SCENE_TITLE::~SCENE_TITLE()
{
	this->OnDestroy();
}

void SCENE_TITLE::OnCreate()
{
	this->BuildObjects();

	fCameraPosTimer = 0.0f;
	fCameraPosArray[0][0] = 5.0f * (GLfloat)sin(2 * M_PI / 360 * 80) * (GLfloat)cos(2 * M_PI / 360 * 90);
	fCameraPosArray[0][1] = 5.0f * (GLfloat)sin(2 * M_PI / 360 * 80) * (GLfloat)sin(2 * M_PI / 360 * 90);
	fCameraPosArray[0][2] = 5.0f * (GLfloat)cos(2 * M_PI / 360 * 80);

	fCameraPosArray[1][0] = 5.0f * (GLfloat)sin(2 * M_PI / 360 * 60) * (GLfloat)cos(2 * M_PI / 360 * 165);
	fCameraPosArray[1][1] = 5.0f * (GLfloat)sin(2 * M_PI / 360 * 60) * (GLfloat)sin(2 * M_PI / 360 * 165);
	fCameraPosArray[1][2] = 5.0f * (GLfloat)cos(2 * M_PI / 360 * 60);

	fCameraPosArray[2][0] = 5.0f * (GLfloat)sin(2 * M_PI / 360 * 120) * (GLfloat)cos(2 * M_PI / 360 * 225);
	fCameraPosArray[2][1] = 5.0f * (GLfloat)sin(2 * M_PI / 360 * 120) * (GLfloat)sin(2 * M_PI / 360 * 225);
	fCameraPosArray[2][2] = 5.0f * (GLfloat)cos(2 * M_PI / 360 * 120);

	fCameraPosArray[3][0] = 5.0f * (GLfloat)sin(2 * M_PI / 360 * 80) * (GLfloat)cos(2 * M_PI / 360 * 300);
	fCameraPosArray[3][1] = 5.0f * (GLfloat)sin(2 * M_PI / 360 * 80) * (GLfloat)sin(2 * M_PI / 360 * 300);
	fCameraPosArray[3][2] = 5.0f * (GLfloat)cos(2 * M_PI / 360 * 80);

	fCameraPosArray[4][0] = 5.0f * (GLfloat)sin(2 * M_PI / 360 * 150) * (GLfloat)cos(2 * M_PI / 360 * 30);
	fCameraPosArray[4][1] = 5.0f * (GLfloat)sin(2 * M_PI / 360 * 150) * (GLfloat)sin(2 * M_PI / 360 * 30);
	fCameraPosArray[4][2] = 5.0f * (GLfloat)cos(2 * M_PI / 360 * 150);
}

void SCENE_TITLE::OnDestroy()
{
	delete field;
	delete player;
}

void SCENE_TITLE::BuildObjects()
{
	field = new OBJECT_FIELD;
	player = new OBJECT_PLAYER;
}

void SCENE_TITLE::BindShader()
{
	SM.BindShader();
	InitBuffer();
	InitTexture();
}

void SCENE_TITLE::InitBuffer()
{
	field->initBuffer(SM.GetShader(ShaderManager::ShaderTag::BitmapShader));
	player->initBuffer(SM.GetShader(ShaderManager::ShaderTag::NonBitmapShader));
}

void SCENE_TITLE::InitTexture()
{
	field->initTexture(SM.GetShader(ShaderManager::ShaderTag::BitmapShader));
	player->initTexture(SM.GetShader(ShaderManager::ShaderTag::NonBitmapShader));
}

void SCENE_TITLE::Render()
{

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	ManualRender();
	BitmapRender();
	NonBitmapRender();
}

void SCENE_TITLE::ManualRender()
{
	glUseProgram(SM.GetShader(ShaderManager::ShaderTag::ManualShader));
	CameraSetting(SM.GetShader(ShaderManager::ShaderTag::ManualShader));
	ProjectionSetting(SM.GetShader(ShaderManager::ShaderTag::ManualShader));

	modelLocation = glGetUniformLocation(SM.GetShader(ShaderManager::ShaderTag::ManualShader), "ModelTransform");

	glEnable(GL_DEPTH_TEST);


	glDisable(GL_DEPTH_TEST);
}

void SCENE_TITLE::BitmapRender()
{
	glUseProgram(SM.GetShader(ShaderManager::ShaderTag::BitmapShader));
	CameraSetting(SM.GetShader(ShaderManager::ShaderTag::BitmapShader));
	ProjectionSetting(SM.GetShader(ShaderManager::ShaderTag::BitmapShader));

	modelLocation = glGetUniformLocation(SM.GetShader(ShaderManager::ShaderTag::BitmapShader), "ModelTransform");

	glEnable(GL_DEPTH_TEST);

	field->putFactor(glm::mat4(1.0f));
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(field->getFactor()));
	field->Render();

	glDisable(GL_DEPTH_TEST);
}

void SCENE_TITLE::NonBitmapRender()
{
	glUseProgram(SM.GetShader(ShaderManager::ShaderTag::NonBitmapShader));
	CameraSetting(SM.GetShader(ShaderManager::ShaderTag::NonBitmapShader));
	ProjectionSetting(SM.GetShader(ShaderManager::ShaderTag::NonBitmapShader));

	modelLocation = glGetUniformLocation(SM.GetShader(ShaderManager::ShaderTag::NonBitmapShader), "ModelTransform");

	glEnable(GL_DEPTH_TEST);

	player->putFactor(glm::mat4(1.0f));
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(player->getFactor()));
	player->Render();

	glDisable(GL_DEPTH_TEST);
}

void SCENE_TITLE::Update(float fTimeElapsed)
{
	field->Update(fTimeElapsed);
	player->Update(fTimeElapsed);

	fCameraPosTimer += fTimeElapsed;
	if (fCameraPosTimer >= 3.0f) {
		fCameraPosTimer -= 3.0f;	// �ʱ�ȭ���� ���� ���� ���ٰ�
		SetNextCameraPos();
	}

}

void SCENE_TITLE::KeyboardMessage(unsigned char inputKey)
{
	switch (inputKey) {
	case 32:	// 'SPACE'
		break;
	case 27:	// 'ESCAPE'
		glutLeaveMainLoop();
		break;
	}
}

void SCENE_TITLE::SpecialKeyboardMessage(int inputKey)
{

}

void SCENE_TITLE::CameraSetting(GLint ShaderProgram)
{
	glm::vec3 cameraPos = glm::vec3(fCameraPosArray[iCameraPosIndex][0], fCameraPosArray[iCameraPosIndex][1], fCameraPosArray[iCameraPosIndex][2]);
	glm::vec3 cameraDirection = glm::vec3(player->getOx(), player->getOy(), player->getOz());
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::mat4 view = glm::mat4(1.0f);
	view = glm::lookAt(cameraPos, cameraDirection, cameraUp);
	unsigned int viewLocation = glGetUniformLocation(ShaderProgram, "viewTransform");
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &view[0][0]);

	unsigned int viewPos = glGetUniformLocation(ShaderProgram, "viewPos");
	glUniform3f(viewPos, fCameraPosArray[iCameraPosIndex][0], fCameraPosArray[iCameraPosIndex][1], fCameraPosArray[iCameraPosIndex][2]);
}

void SCENE_TITLE::ProjectionSetting(GLint ShaderProgram)
{
	glm::mat4 projection = glm::mat4(1.0f);
	projection = glm::perspective(glm::radians(60.0f), (float)700.0 / (float)700.0, 0.1f, 3000.0f);
	//projection = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f, 0.1f, 3000.0f);

	unsigned int projectionLocation = glGetUniformLocation(ShaderProgram, "projectionTransform");	//--- ���� ��ȯ �� ����
	glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, &projection[0][0]);
}

void SCENE_TITLE::LightSetting(GLint ShaderProgram)
{

}

void SCENE_TITLE::SetNextCameraPos()
{
	if (iCameraPosIndex == 4) {
		iCameraPosIndex = 0;
	}
	else {
		iCameraPosIndex++;
	}
}