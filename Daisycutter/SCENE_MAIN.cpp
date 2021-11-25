#include "SCENE_MAIN.h"

SCENE_MAIN::SCENE_MAIN()
{

}

SCENE_MAIN::SCENE_MAIN(SceneTag tag, CFramework* pFramework) : CScene(tag, pFramework)
{
	this->OnCreate();
	printf("asdf\n");
}

SCENE_MAIN::~SCENE_MAIN()
{
	this->OnDestroy();
}

void SCENE_MAIN::OnCreate()
{
	this->BuildObjects();
}

void SCENE_MAIN::OnDestroy()
{
	delete sun;
	delete earth;
	delete moon;
}

void SCENE_MAIN::BuildObjects()
{
	sun = new OBJECT_SUN;
	earth = new OBJECT_EARTH;
	moon = new OBJECT_MOON;
}

void SCENE_MAIN::InitBuffer(GLint s_program)
{
	this->s_program = s_program;

	sun->initBuffer(this->s_program);
	earth->initBuffer(this->s_program);
	moon->initBuffer(this->s_program);
}

void SCENE_MAIN::Render()
{

	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(this->s_program);

	CameraSetting();
	ProjectionSetting();

	modelLocation = glGetUniformLocation(s_program, "ModelTransform");

	glEnable(GL_DEPTH_TEST);

	sun->putFactor(glm::mat4(1.0f));
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(sun->getFactor()));
	sun->Render();

	earth->putFactor(glm::mat4(1.0f));
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(earth->getFactor()));
	earth->Render();

	moon->putFactor(glm::mat4(1.0f));
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(moon->getFactor()));
	moon->Render();

	glDisable(GL_DEPTH_TEST);
}

void SCENE_MAIN::Update(float fTimeElapsed)
{
	sun->Update(fTimeElapsed);
	earth->Update(fTimeElapsed);
	moon->Update(fTimeElapsed);
}

void SCENE_MAIN::KeyboardMessage(unsigned char inputKey)
{
	switch (inputKey) {
	case 't':
	case 'T':
		m_pFramework->ChangeScene(CScene::SceneTag::Main, new SCENE_MAIN(CScene::SceneTag::Main, m_pFramework));
		break;
	case 'r':
	case 'R':
		break;
	case 'q':	// 프로그램 종료
	case 'Q':
		glutLeaveMainLoop();
		break;
	}
}

void SCENE_MAIN::CameraSetting()
{
	glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 7.0f);				//--- 카메라 위치
	glm::vec3 cameraDirection = glm::vec3(0.0f, 0.0f, 0.0f);		//--- 카메라 바라보는 방향
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);				//--- 카메라 위쪽 방향
	glm::mat4 view = glm::mat4(1.0f);
	view = glm::lookAt(cameraPos, cameraDirection, cameraUp);
	unsigned int viewLocation = glGetUniformLocation(s_program, "viewTransform");		//--- 뷰잉 변환 설정
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &view[0][0]);
	unsigned int viewPos = glGetUniformLocation(s_program, "viewPos");					//--- 바라보는 방향 프래그먼트 셰이더로 전달
	glUniform3f(viewPos, -2.0f, 2.0f, 2.0f);
}

void SCENE_MAIN::ProjectionSetting()
{
	glm::mat4 projection = glm::mat4(1.0f);
	projection = glm::perspective(glm::radians(60.0f), (float)700.0 / (float)700.0, 0.1f, 200.0f);
	projection = glm::translate(projection, glm::vec3(0.0, 0.0, 0.2));							//--- 공간을 약간 뒤로 밀어줌. 필요없으면 제거할 것
	unsigned int projectionLocation = glGetUniformLocation(s_program, "projectionTransform");	//--- 투영 변환 값 설정
	glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, &projection[0][0]);
}

void SCENE_MAIN::LightSetting()
{

}