#pragma once
#include "Object.h"

class OBJECT_MANUAL : public CObject
{
public:
	enum ManualTag {
		MainTitle
		, MusicJacket1
		, MusicJacket2
		, OPERATION_START
		, NUMBER1
		, NUMBER2
		, NUMBER3
		, HP_BAR0
		, HP_BAR1
		, HP_BAR2
		, HP_BAR3
		, HP_BAR4
		, HP_BAR5
		, HP_BAR6
		, HP_BAR7
		, HP_BAR8
		, HP_BAR9
		, HP_BAR10
		, GAME_CLEAR
		, GAME_OVER
		, Count			// Sound의 개수를 나타내기 위한 임시 태그이다. 지우지 말자.
	};
private:
	GLuint vao, vbo[3];			// 한 면의 크기와 색상 정보가 vao에 바인딩됩니다.
	static unsigned int texture[Count];
	static unsigned char* image[Count];
	glm::mat4 myFactor;

	int objColorLocation;
	int tLocation;

public:
	static GLfloat data[2][2][3][3];		// 모든 MANUAL 오브젝트가 공유해도 상관 없음.
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
