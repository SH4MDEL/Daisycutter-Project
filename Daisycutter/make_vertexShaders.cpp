#include "make_vertexShaders.h"

void make_vertexShaders(GLchar* myvertexSource, GLuint& myvertexShader)
{
	myvertexSource = filetobuf("vertex.glsl");
	//--- ���ؽ� ���̴� ��ü �����
	myvertexShader = glCreateShader(GL_VERTEX_SHADER);
	//--- ���̴� �ڵ带 ���̴� ��ü�� �ֱ�
	glShaderSource(myvertexShader, 1, (const GLchar**)&myvertexSource, 0);
	//--- ���ؽ� ���̴� �������ϱ�
	glCompileShader(myvertexShader);
	//--- �������� ����� ���� ���� ���: ���� üũ
	GLint result;
	GLchar errorLog[512];
	glGetShaderiv(myvertexShader, GL_COMPILE_STATUS, &result);
	if (!result) {
		glGetShaderInfoLog(myvertexShader, 512, NULL, errorLog);
		std::cerr << "ERROR: vertex shader ������ ����\n" << errorLog << std::endl;
		return;
	}
}
