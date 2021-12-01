#pragma once
#include "Object.h"
#include "objRead.h"

class OBJECT_PLAYER : public CObject
{
private:
	GLuint vao, vbo[3];
	unsigned int texture;
	unsigned char* image;
	glm::mat4 myFactor;

	int objColorLocation;
	int tLocation;


	GLfloat object_x, object_y, object_z;
	GLfloat ObjectSpeed;						// 플레이어는 가만히 있고 나머지 배경이 움직이기 때문에 
												// 플레이어의 속도를 받아 나머지 객체의 이동 속도를 결정한다.
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
	GLfloat getObjectSpeed();
};