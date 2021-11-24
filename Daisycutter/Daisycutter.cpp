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

CFramework myFramework;

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

	glEnable(GL_DEPTH_TEST);

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

//struct RGBA
//{
//    GLfloat red;
//    GLfloat green;
//    GLfloat blue;
//    GLfloat alpha;
//};
//
//std::default_random_engine dre;
//std::uniform_real_distribution<double> urd(0.0, 1.0);
//
//GLvoid do_drawScene(GLvoid);
//GLvoid do_Reshape(int w, int h);
//GLvoid do_Keyboard(unsigned char key, int x, int y);
//void do_Timer(int val);
//
//bool flag_timer = false;
//
//class GL_App
//{
//public:
//    RGBA color = { 1.0f, 1.0f, 1.0f, 1.0f };
//
//    void drawScene(GLvoid)
//    {
//        //--- ����� ���� ����
//        glClearColor(color.red, color.green, color.blue, color.alpha);    // �������� ����
//        glClear(GL_COLOR_BUFFER_BIT);            // ������ ������ ��ü�� ĥ�ϱ�
//        glutSwapBuffers();                        // ȭ�鿡 ����ϱ�
//    }
//
//    void Reshape(int w, int h)
//    {
//        glViewport(0, 0, w, h);
//    }
//
//    void Keyboard(unsigned char key, int x, int y)
//    {
//        switch (key) {
//        case 'R':
//        case 'r':
//            color = { 1.0f, 0.0f, 0.0f, 1.0f };
//            break;    //--- ������ ���������� ����
//
//        case 'G':
//        case 'g':
//            color = { 0.0f, 1.0f, 0.0f, 1.0f };
//            break;    //--- ������ �ʷϻ����� ����
//
//        case 'B':
//        case 'b':
//            color = { 0.0f, 0.0f, 1.0f, 1.0f };
//            break;    //--- ������ �Ķ������� ����
//
//        case 'A':
//        case 'a':
//            color = { GLfloat(urd(dre)), GLfloat(urd(dre)) , GLfloat(urd(dre)) , 1.0f };
//            break;
//
//        case 'W':
//        case 'w':
//            color = { 1.0f, 1.0f, 1.0f, 1.0f };
//            break;
//
//        case 'K':
//        case 'k':
//            color = { 0.0f, 0.0f, 0.0f, 1.0f };
//            break;
//
//        case 'T':
//        case 't':
//            flag_timer = true;
//            glutTimerFunc(100, do_Timer, 0);
//            break;
//
//        case 'S':
//        case 's':
//            flag_timer = false;
//            break;
//
//        case 'Q':
//        case 'q':
//            std::cout << "Bye Bye~!" << std::endl;
//            glutLeaveMainLoop();
//            exit(0);
//            break;
//        }
//        glutPostRedisplay(); //--- ������ �ٲ𶧸��� ��� �ݹ��Լ��� ȣ���Ͽ� ȭ���� refresh �Ѵ�
//    }
//
//    void Timer()
//    {
//        color = { GLfloat(urd(dre)), GLfloat(urd(dre)) , GLfloat(urd(dre)) , 1.0f };
//        glutPostRedisplay();
//        if (flag_timer)
//            glutTimerFunc(100, do_Timer, 0);
//    }
//};
//
//
//GL_App* glptr;
//
//
//int main(int argc, char** argv) //--- ������ ����ϰ� �ݹ��Լ� ����
//{
//    //--- ������ �����ϱ�
//    glutInit(&argc, argv); // glut �ʱ�ȭ
//    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); // ���÷��� ��� ����
//    glutInitWindowPosition(0, 0);    // �������� ��ġ ����
//    glutInitWindowSize(800, 600);    // �������� ũ�� ����
//    glutCreateWindow("Example1");    // ������ ����(������ �̸�)
//
//    //--- GLEW �ʱ�ȭ�ϱ�
//    glewExperimental = GL_TRUE;
//    if (glewInit() != GLEW_OK)        // glew �ʱ�ȭ
//    {
//        std::cerr << "Unable to initialize GLEW" << std::endl;
//        exit(EXIT_FAILURE);
//    }
//    else
//        std::cout << "GLEW Initialized\n";
//
//    // ������ ����
//    GL_App gl_app;
//    glptr = &gl_app;
//
//    glutDisplayFunc(do_drawScene);    // ��� �ݹ��Լ��� ����
//    glutReshapeFunc(do_Reshape);    // �ٽ� �׸��� �ݹ��Լ� ����
//    glutKeyboardFunc(do_Keyboard); // Ű���� �Է� �ݹ��Լ� ����
//    glutMainLoop();                // �̺�Ʈ ó�� ����
//}
//
//GLvoid do_drawScene() //--- �ݹ� �Լ�: �׸��� �ݹ� �Լ�
//{
//    glptr->drawScene();
//}
//
//GLvoid do_Reshape(int w, int h)        //--- �ݹ� �Լ�: �ٽ� �׸��� �ݹ� �Լ�
//{
//    glptr->Reshape(w, h);
//}
//
//GLvoid do_Keyboard(unsigned char key, int x, int y)
//{
//    glptr->Keyboard(key, x, y);
//}
//
//void do_Timer(int val)
//{
//    glptr->Timer();
//}