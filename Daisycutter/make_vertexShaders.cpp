#include "make_vertexShaders.h"

void make_vertexShaders(GLchar* myvertexSource, GLuint& myvertexShader, const char* shader_name)
{
	myvertexSource = filetobuf(shader_name);
	//--- 버텍스 세이더 객체 만들기
	myvertexShader = glCreateShader(GL_VERTEX_SHADER);
	//--- 세이더 코드를 세이더 객체에 넣기
	glShaderSource(myvertexShader, 1, (const GLchar**)&myvertexSource, 0);
	//--- 버텍스 세이더 컴파일하기
	glCompileShader(myvertexShader);
	//--- 컴파일이 제대로 되지 않은 경우: 에러 체크
	GLint result;
	GLchar errorLog[512];
	glGetShaderiv(myvertexShader, GL_COMPILE_STATUS, &result);
	if (!result) {
		glGetShaderInfoLog(myvertexShader, 512, NULL, errorLog);
		std::cerr << "ERROR: vertex shader 컴파일 실패\n" << errorLog << std::endl;
		return;
	}
}
