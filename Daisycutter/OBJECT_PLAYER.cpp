#include "OBJECT_PLAYER.h"

objRead OBJECT_PLAYER::objReader;
GLint OBJECT_PLAYER::ObjectMedel = objReader.loadObj_normalize_center("GRAPHIC\\OBJECT\\PLAYER.obj");

OBJECT_PLAYER::OBJECT_PLAYER()
{
	OnCreate();
}

OBJECT_PLAYER::~OBJECT_PLAYER()
{

}

void OBJECT_PLAYER::OnCreate()
{
	object_x = 0.0f, object_y = 0.0f, object_z = 0.0f;
}

void OBJECT_PLAYER::initBuffer(GLint s_program[])
{
	this->s_program = s_program[0];
	//// 5.1. VAO 객체 생성 및 바인딩
	glGenVertexArrays(1, &vao);

	// 2 triangles for quad floor
	glUseProgram(this->s_program);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo[0]);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, objReader.outvertex.size() * sizeof(glm::vec3), &objReader.outvertex[0], GL_STATIC_DRAW);
	GLint pAttribute = glGetAttribLocation(this->s_program, "vPos");
	glVertexAttribPointer(pAttribute, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(pAttribute);

	glGenBuffers(1, &vbo[1]);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, objReader.outnormal.size() * sizeof(glm::vec3), &objReader.outnormal[0], GL_STATIC_DRAW);
	GLint nAttribute = glGetAttribLocation(this->s_program, "vNormal");
	glVertexAttribPointer(nAttribute, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(nAttribute);

	glGenBuffers(1, &vbo[2]);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
	glBufferData(GL_ARRAY_BUFFER, objReader.outuv.size() * sizeof(glm::vec3), &objReader.outuv[0], GL_STATIC_DRAW);
	GLint tAttribute = glGetAttribLocation(this->s_program, "vTexCoord");
	glVertexAttribPointer(tAttribute, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
	glEnableVertexAttribArray(tAttribute);

	objColorLocation = glGetUniformLocation(this->s_program, "objectColor"); //--- object Color값 전달
}

void OBJECT_PLAYER::initTexture(GLint s_program[])
{

}

void OBJECT_PLAYER::Render()
{
	glUniform3f(objColorLocation, 1.0f, 1.0f, 1.0f);
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, ObjectMedel);
}

void OBJECT_PLAYER::Update(float fTimeElapsed)
{

}

void OBJECT_PLAYER::putFactor(glm::mat4 inputFactor)
{
	myFactor = inputFactor;
	myFactor = glm::translate(myFactor, glm::vec3(object_x, object_y, object_z));
	//myFactor = scale(myFactor, glm::vec3(0.2f, 0.2f, 0.2f));
}

glm::mat4 OBJECT_PLAYER::getFactor()
{
	return myFactor;
}

GLfloat OBJECT_PLAYER::getOx()
{
	return object_x;
}

GLfloat OBJECT_PLAYER::getOy()
{
	return object_y;
}

GLfloat OBJECT_PLAYER::getOz()
{
	return object_z;
}