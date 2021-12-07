#pragma once
#include "Object.h"

class OBJECT_MANUAL : public CObject
{
public:
	enum ManualTag {
		MainTitle
		, MusicSelect
		, Count			// Sound�� ������ ��Ÿ���� ���� �ӽ� �±��̴�. ������ ����.
	};
private:
	GLuint vao, vbo[3];			// �� ���� ũ��� ���� ������ vao�� ���ε��˴ϴ�.
	unsigned int texture[Count];
	unsigned char* image[Count];
	glm::mat4 myFactor;

	int objColorLocation;
	int tLocation;

public:
	static GLfloat data[2][2][3][3];		// ��� MANUAL ������Ʈ�� �����ص� ��� ����.
	static GLfloat texture_data[2][3][2];

	OBJECT_MANUAL();
	~OBJECT_MANUAL();

	void OnCreate() override;
	void initBuffer(GLint ShaderProgram) override;
	void initTexture(GLint ShaderProgram) override;
	void Update(float fTimeElapsed) override;
	void Render() override;
	void Render(GLint type);

	void putFactor(glm::mat4 inputFactor) override;
	glm::mat4 getFactor() override;
};
