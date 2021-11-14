#pragma once
#include "Daisycutter.h"
#include "make_vertexShaders.h"
#include "make_fragmentShaders.h"
#include "make_shaderProgram.h"

#include "Framework.h"

#define M_PI 3.1415926535897932384626433832795
#define CLIENT_WIDTH	1920
#define CLIENT_HEIGHT	1080


GLvoid drawScene();
GLvoid Keyboard(unsigned char inputKey, int x, int y);
GLvoid TimerFunction(int value);
GLvoid Reshape(int w, int h);

GLchar* vertexSource, * fragmentSource; //--- �ҽ��ڵ� ���� ����
GLuint vertexShader, fragmentShader; //--- ���̴� ��ü
GLuint s_program;

int main(int argc, char** argv) //--- ������ ����ϰ� �ݹ��Լ� ����
{
	//--- �����츦 �����մϴ�.
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(200, 200);
	glutInitWindowSize(CLIENT_WIDTH, CLIENT_HEIGHT);
	glutCreateWindow("Daisycutter");

	//--- GLEW �ʱ�ȭ�ϱ�
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {					// glew �ʱ�ȭ
		std::cerr << "Unable to initialize GLEW" << std::endl;
		exit(EXIT_FAILURE);
	}
	else {
		std::cout << "GLEW Initialized\n";
	}
	mm.initMyBuffer();

	glewInit();
	make_vertexShaders(vertexSource, vertexShader);
	make_fragmentShaders(fragmentSource, fragmentShader);
	s_program = make_shaderProgram(vertexShader, fragmentShader);

	glutDisplayFunc(drawScene);

	glutKeyboardFunc(Keyboard);
	glutTimerFunc(10, TimerFunction, 1);

	glutReshapeFunc(Reshape);
	glutMainLoop();
}

GLvoid drawScene()
{
	//--- ����� ���� ����
	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//--- ������ ���������ο� ���̴� �ҷ�����
	glUseProgram(s_program);

	glViewport(0, 0, 900, 900);

	glm::vec3 cameraPos;
	glm::vec3 cameraDirection;
	if (rc.quarterview) {
		cameraPos = glm::vec3(
			(3.0f + rc.perspectiveZPos) * sin(2 * M_PI / 360.0f * rc.rotationYPos) * cos(2 * M_PI / 360.0f * rc.rotationXPos),
			(3.0f + rc.perspectiveZPos) * cos(2 * M_PI / 360.0f * rc.rotationYPos),
			(3.0f + rc.perspectiveZPos) * sin(2 * M_PI / 360.0f * rc.rotationYPos) * sin(2 * M_PI / 360.0f * rc.rotationXPos)); //--- ī�޶� ��ġ
		cameraDirection = glm::vec3((GLfloat)mm.vertical / 20.0f, 0.0f, (GLfloat)mm.horizontal / 20.0f); //--- ī�޶� �ٶ󺸴� ����
	}
	else {
		if (rm.robot.movement == 0 || rm.robot.movement == 1) {
			cameraPos = glm::vec3(rm.robot.xPos, 0.1f, rm.robot.zPos); //--- ī�޶� ��ġ
			cameraDirection = glm::vec3(20.0f, 1.0f, 0.0f); //--- ī�޶� �ٶ󺸴� ����
		}
		else if (rm.robot.movement == 2) {
			cameraPos = glm::vec3(rm.robot.xPos, 0.1f, rm.robot.zPos); //--- ī�޶� ��ġ
			cameraDirection = glm::vec3(-20.0f, 1.0f, 0.0f); //--- ī�޶� �ٶ󺸴� ����
		}
		else if (rm.robot.movement == 3) {
			cameraPos = glm::vec3(rm.robot.xPos, 0.1f, rm.robot.zPos); //--- ī�޶� ��ġ
			cameraDirection = glm::vec3(0.0f, 1.0f, -20.0f); //--- ī�޶� �ٶ󺸴� ����
		}
		else if (rm.robot.movement == 4) {
			cameraPos = glm::vec3(rm.robot.xPos, 0.1f, rm.robot.zPos); //--- ī�޶� ��ġ
			cameraDirection = glm::vec3(0.0f, 1.0f, 20.0f); //--- ī�޶� �ٶ󺸴� ����
		}
	}
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f); //--- ī�޶� ���� ����

	glm::mat4 view = glm::mat4(1.0f);
	view = glm::lookAt(cameraPos, cameraDirection, cameraUp);
	unsigned int viewLocation = glGetUniformLocation(s_program, "viewTransform"); //--- ���� ��ȯ ����
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &view[0][0]);


	glm::mat4 projection = glm::mat4(1.0f);
	if (!rc.quarterview) {
		projection = glm::perspective(glm::radians(60.0f), (float)700.0 / (float)700.0, 0.1f, 10.0f);
		projection = glm::translate(projection, glm::vec3(0.0, 0.0, -0.05)); //--- ������ �ణ �ڷ� �о���
	}
	else if (rc.perspective) {
		projection = glm::perspective(glm::radians(60.0f), (float)700.0 / (float)700.0, 0.1f, 200.0f);
		projection = glm::translate(projection, glm::vec3(0.0, 0.0, 0.2)); //--- ������ �ణ �ڷ� �о���
	}
	else {
		projection = glm::ortho(-2.0f, 2.0f, -2.0f, 2.0f, -3.0f, 3.0f);
		projection = glm::translate(projection, glm::vec3(0.0, 0.0, 0.2)); //--- ������ �ణ �ڷ� �о���
	}
	unsigned int projectionLocation = glGetUniformLocation(s_program, "projectionTransform"); //--- ���� ��ȯ �� ����
	glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, &projection[0][0]);

	glEnable(GL_DEPTH_TEST);

	unsigned int modelLocation = glGetUniformLocation(s_program, "ModelTransform"); //--- ���ؽ� ���̴����� �𵨸� ��ȯ ��ġ ��������

	mm.field.putFactor(glm::mat4(1.0f));
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(mm.field.getFactor()));
	mm.field.draw();

	glDisable(GL_DEPTH_TEST);

	glutSwapBuffers(); //--- ȭ�鿡 ����ϱ�
}

GLvoid Keyboard(unsigned char inputKey, int x, int y)
{
	switch (inputKey) {
	
	}
	glutPostRedisplay();
}

GLvoid TimerFunction(int value)
{
	

	glutPostRedisplay();
	glutTimerFunc(10, TimerFunction, value);
	return;
}

GLvoid Reshape(int w, int h) //--- �ݹ� �Լ�: �ٽ� �׸��� �ݹ� �Լ�
{
	glViewport(0, 0, w, h);
}