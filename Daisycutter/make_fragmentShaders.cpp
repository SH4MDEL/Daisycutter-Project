#pragma once
#include "make_fragmentShaders.h"
#include "filetobuf.h"

void make_fragmentShaders(GLchar* myfragmentSource, GLuint& myfragmentShader)
{
	myfragmentSource = filetobuf("fragment.glsl");
	//--- �����׸�Ʈ ���̴� ��ü �����
	myfragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	//--- ���̴� �ڵ带 ���̴� ��ü�� �ֱ�
	glShaderSource(myfragmentShader, 1, (const GLchar**)&myfragmentSource, 0);
	//--- �����׸�Ʈ ���̴� ������
	glCompileShader(myfragmentShader);
	//--- �������� ����� ���� ���� ���: ������ ���� üũ
	GLint result;
	GLchar errorLog[512];
	glGetShaderiv(myfragmentShader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(myfragmentShader, 512, NULL, errorLog);
		std::cerr << "ERROR: fragment shader ������ ����\n" << errorLog << std::endl;
		return;
	}
}