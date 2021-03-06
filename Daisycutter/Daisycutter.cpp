#pragma once
#include "Daisycutter.h"
#include "Framework.h"

#define CLIENT_WIDTH	1920
#define CLIENT_HEIGHT	1080

GLvoid fc_drawScene();
GLvoid fc_Keyboard(unsigned char inputKey, int x, int y);
GLvoid fc_SpecialKeyboard(int key, int x, int y);
GLvoid fc_Timer(int value);
GLvoid fc_Reshape(int w, int h);

CFramework myFramework;

class Framework_Client {
public:
	GLvoid drawScene()
	{
		myFramework.Render();
		glutPostRedisplay();
		glutSwapBuffers(); //--- 화면에 출력하기
	}

	GLvoid Keyboard(unsigned char inputKey, int x, int y)
	{
		myFramework.KeyboardMessage(inputKey);
		glutPostRedisplay();
	}

	GLvoid SpecialKeyboard(int inputKey, int x, int y)
	{
		myFramework.SpecialKeyboardMessage(inputKey);
		glutPostRedisplay();
	}

	GLvoid Timer()
	{
		myFramework.FrameAdvance();
		glutPostRedisplay();
		glutTimerFunc(10, fc_Timer, 0);
		return;
	}

	GLvoid Reshape(int w, int h)
	{
		glViewport(0, 0, w, h);
	}
};

Framework_Client* fcptr;

int main(int argc, char** argv) //--- 윈도우 출력하고 콜백함수 설정
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(200, 200);
	glutInitWindowSize(CLIENT_WIDTH, CLIENT_HEIGHT);
	glutCreateWindow("Daisycutter");

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {					// glew 초기화
		std::cerr << "Unable to initialize GLEW" << std::endl;
		exit(EXIT_FAILURE);
	}
	else {
		std::cout << "GLEW Initialized\n";
	}

	Framework_Client FC_app;
	fcptr = &FC_app;

	glewInit();

	myFramework.BindShader();

	glutDisplayFunc(fc_drawScene);
	glutKeyboardFunc(fc_Keyboard);
	glutSpecialFunc(fc_SpecialKeyboard);
	glutTimerFunc(10, fc_Timer, 0);
	glutReshapeFunc(fc_Reshape);
	glutMainLoop();
}

GLvoid fc_drawScene()
{
	fcptr->drawScene();
}

GLvoid fc_Reshape(int w, int h)        //--- 콜백 함수: 다시 그리기 콜백 함수
{
	fcptr->Reshape(w, h);
}

GLvoid fc_Keyboard(unsigned char key, int x, int y)
{
	fcptr->Keyboard(key, x, y);
}

GLvoid fc_SpecialKeyboard(int key, int x, int y)
{
	fcptr->SpecialKeyboard(key, x, y);
}

void fc_Timer(int val)
{
	fcptr->Timer();
}