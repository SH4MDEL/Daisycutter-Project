#pragma once
#include "Object.h"

class OBJECT_MANUAL : public CObject
{
private:
	GLuint vao, vbo[3];			// �� ���� ũ��� ���� ������ vao�� ���ε��˴ϴ�.
	unsigned int texture;
	unsigned char* image;
	glm::mat4 myFactor;

	int objColorLocation;
	int tLocation;

public:
	static GLfloat data[2][2][3][3];		// ��� FIELD ������Ʈ�� �����ص� ��� ����.
	static GLfloat texture_data[2][3][2];

	OBJECT_MANUAL();
	~OBJECT_MANUAL();

	void OnCreate() override;
	void initBuffer(GLint ShaderProgram) override;
	void initTexture(GLint ShaderProgram) override;
	void Update(float fTimeElapsed) override;
	void Render() override;

	void putFactor(glm::mat4 inputFactor) override;
	glm::mat4 getFactor() override;
};
