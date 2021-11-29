#pragma once
#include "Object.h"
#include "objRead.h"

class OBJECT_PLAYER : public CObject
{
private:
	GLuint vao, vbo[3];
	int objColorLocation;
	int tLocation;

	glm::mat4 myFactor;

	GLfloat object_x, object_y, object_z;
public:
	static objRead objReader;
	static GLint ObjectMedel;

	OBJECT_PLAYER();
	~OBJECT_PLAYER();

	void OnCreate() override;
	void initBuffer(GLint ShaderProgram) override;
	void initTexture(GLint ShaderProgram) override;			// 필요치 않을지라도 추가해 줘야 함
	void Update(float fTimeElapsed) override;
	void Render() override;

	void putFactor(glm::mat4 inputFactor) override;
	glm::mat4 getFactor() override;


	GLfloat getOx();
	GLfloat getOy();
	GLfloat getOz();
};