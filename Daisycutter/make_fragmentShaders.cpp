#pragma once
#include "make_fragmentShaders.h"
#include "filetobuf.h"

void make_fragmentShaders(GLchar* myfragmentSource, GLuint& myfragmentShader, const char* shader_name)
{
	//--- 외부에서 쉐이더의 이름을 받아 오도록 변경
	myfragmentSource = filetobuf(shader_name);
	//--- 프래그먼트 세이더 객체 만들기
	myfragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	//--- 세이더 코드를 세이더 객체에 넣기
	glShaderSource(myfragmentShader, 1, (const GLchar**)&myfragmentSource, 0);
	//--- 프래그먼트 세이더 컴파일
	glCompileShader(myfragmentShader);
	//--- 컴파일이 제대로 되지 않은 경우: 컴파일 에러 체크
	GLint result;
	GLchar errorLog[512];
	glGetShaderiv(myfragmentShader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(myfragmentShader, 512, NULL, errorLog);
		std::cerr << "ERROR: fragment shader 컴파일 실패\n" << shader_name << errorLog << std::endl;
		return;
	}
}