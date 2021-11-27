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
}

void SCENE_TITLE::OnDestroy()
{
	delete player;
}

void SCENE_TITLE::BuildObjects()
{
	player = new OBJECT_PLAYER;
}

void SCENE_TITLE::InitBuffer(GLint s_program)
{
	this->s_program = s_program;

	player->initBuffer(this->s_program);
}

void SCENE_TITLE::Render()
{

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(this->s_program);

	CameraSetting();
	ProjectionSetting();

	modelLocation = glGetUniformLocation(s_program, "ModelTransform");

	glEnable(GL_DEPTH_TEST);

	player->putFactor(glm::mat4(1.0f));
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(player->getFactor()));
	player->Render();

	glDisable(GL_DEPTH_TEST);
}

void SCENE_TITLE::Update(float fTimeElapsed)
{
	player->Update(fTimeElapsed);
}

void SCENE_TITLE::KeyboardMessage(unsigned char inputKey)
{
	switch (inputKey) {
	
	case 27:	// 'ESCAPE'
		glutLeaveMainLoop();
		break;
	}
}

void SCENE_TITLE::SpecialKeyboardMessage(int inputKey)
{

}

void SCENE_TITLE::CameraSetting()
{
	glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 7.0f);				//--- ī�޶� ��ġ
	glm::vec3 cameraDirection = glm::vec3(0.0f, 0.0f, 0.0f);		//--- ī�޶� �ٶ󺸴� ����
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);				//--- ī�޶� ���� ����
	glm::mat4 view = glm::mat4(1.0f);
	view = glm::lookAt(cameraPos, cameraDirection, cameraUp);
	unsigned int viewLocation = glGetUniformLocation(s_program, "viewTransform");		//--- ���� ��ȯ ����
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &view[0][0]);
	unsigned int viewPos = glGetUniformLocation(s_program, "viewPos");					//--- �ٶ󺸴� ���� �����׸�Ʈ ���̴��� ����
	glUniform3f(viewPos, -2.0f, 2.0f, 2.0f);
}

void SCENE_TITLE::ProjectionSetting()
{
	glm::mat4 projection = glm::mat4(1.0f);
	projection = glm::perspective(glm::radians(60.0f), (float)700.0 / (float)700.0, 0.1f, 200.0f);
	projection = glm::translate(projection, glm::vec3(0.0, 0.0, 0.2));							//--- ������ �ణ �ڷ� �о���. �ʿ������ ������ ��
	unsigned int projectionLocation = glGetUniformLocation(s_program, "projectionTransform");	//--- ���� ��ȯ �� ����
	glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, &projection[0][0]);
}

void SCENE_TITLE::LightSetting()
{

}
