#pragma once
#include "Object.h"

class OBJECT_FIELD : public CObject
{
private:
	GLuint vao[6], vbo[6][3];			// 한 면의 크기와 색상 정보가 vao에 바인딩됩니다.
	unsigned int texture[6];
	unsigned char* image[6];
	glm::mat4 myFactor;

	int objColorLocation;
	int tLocation;

public:
	static GLfloat data[6][2][2][3][3];		// 모든 FIELD 오브젝트가 공유해도 상관 없음.
	static GLfloat texture_data[6][2][3][2];

	OBJECT_FIELD();
	~OBJECT_FIELD();

	void OnCreate() override;
	void initBuffer(GLint s_program) override;
	void initTexture(GLint s_program) override;
	void Update(float fTimeElapsed) override;
	void Render() override;

	void putFactor(glm::mat4 inputFactor) override;
	glm::mat4 getFactor() override;
};

