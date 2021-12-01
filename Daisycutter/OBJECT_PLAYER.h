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
	GLfloat ObjectSpeed;						// �÷��̾�� ������ �ְ� ������ ����� �����̱� ������ 
												// �÷��̾��� �ӵ��� �޾� ������ ��ü�� �̵� �ӵ��� �����Ѵ�.
public:
	static objRead objReader;
	static GLint ObjectMedel;

	OBJECT_PLAYER();
	~OBJECT_PLAYER();

	void OnCreate() override;
	void initBuffer(GLint ShaderProgram) override;
	void initTexture(GLint ShaderProgram) override;			// �ʿ�ġ �������� �߰��� ��� ��
	void Update(float fTimeElapsed) override;
	void Render() override;

	void putFactor(glm::mat4 inputFactor) override;
	glm::mat4 getFactor() override;


	GLfloat getOx();
	GLfloat getOy();
	GLfloat getOz();
	GLfloat getObjectSpeed();
};