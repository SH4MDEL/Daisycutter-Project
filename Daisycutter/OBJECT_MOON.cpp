#include "OBJECT_MOON.h"

objRead OBJECT_MOON::objReader;
GLint OBJECT_MOON::object = objReader.loadObj_normalize_center("sphere.obj");

OBJECT_MOON::OBJECT_MOON()
{
	OnCreate();
}

OBJECT_MOON::~OBJECT_MOON()
{

}

void OBJECT_MOON::OnCreate()
{

}

void OBJECT_MOON::initBuffer(GLint s_program)
{
	this->s_program = s_program;
	//// 5.1. VAO 객체 생성 및 바인딩
	glGenVertexArrays(3, vao);
	glGenBuffers(3, vbo[0]);
	glGenBuffers(3, vbo[1]);

	// 2 triangles for quad floor
	glUseProgram(this->s_program);
	glBindVertexArray(vao[0]);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0][0]);
	glBufferData(GL_ARRAY_BUFFER, objReader.outvertex.size() * sizeof(glm::vec3), &objReader.outvertex[0], GL_STATIC_DRAW);
	GLint pAttribute = glGetAttribLocation(this->s_program, "vPos");
	glVertexAttribPointer(pAttribute, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(pAttribute);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[1][0]);
	glBufferData(GL_ARRAY_BUFFER, objReader.outnormal.size() * sizeof(glm::vec3), &objReader.outnormal[0], GL_STATIC_DRAW);
	GLint nAttribute = glGetAttribLocation(this->s_program, "vNormal");
	glVertexAttribPointer(nAttribute, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(nAttribute);

	objColorLocation = glGetUniformLocation(this->s_program, "objectColor"); //--- object Color값 전달
}

void OBJECT_MOON::Render()
{
	glUniform3f(objColorLocation, 1.0f, 1.0f, 0.1f);
	glBindVertexArray(vao[0]);
	glDrawArrays(GL_TRIANGLES, 0, object);
}

void OBJECT_MOON::Update(float fTimeElapsed)
{

}

void OBJECT_MOON::putFactor(glm::mat4 inputFactor)
{
	myFactor = inputFactor;
	myFactor = glm::translate(myFactor, glm::vec3(-2.0f, 0.0f, 0.0f));
	myFactor = scale(myFactor, glm::vec3(0.1f, 0.1f, 0.1f));
}

glm::mat4 OBJECT_MOON::getFactor()
{
	return myFactor;
}
