#pragma once
#include "Object.h"
#include "objRead.h"

#include "OBJECT_PARTICLE.h"

class OBJECT_ENEMY : public CObject
{
private:
	GLuint vao, vbo[3];
	unsigned int texture;
	unsigned char* image;

	int lightPosLocation[2];
	int lightColorLocation[2];
	int objColorLocation;
	int tLocation;

	class EnemyData {
	public:
		GLint iObjectStatus;
		GLfloat fObject_x, fObject_y, fObject_z;
		GLfloat DieStateTimer;
		glm::mat4 Factor;
		OBJECT_PARTICLE* particle;
	};
	EnemyData* pData;

	GLdouble m_dBPM;
	GLint iNowIndex;

	GLint m_ParticleShaderProgram;
public:
	enum EnemyStatusTag {
		NullState
		, ActiveState
		, InvincibleState
		, DieState
		, Count
	};
	static objRead objReader;
	static GLint ObjectMedel;

	OBJECT_ENEMY();
	OBJECT_ENEMY(GLdouble BPM);
	~OBJECT_ENEMY();

	void OnCreate() override;
	void initBuffer(GLint ShaderProgram) override;
	void initSubShader(GLint ShaderProgram);
	void initTexture(GLint ShaderProgram) override;	
	void Update(float fTimeElapsed) override;
	void Render() override;
	void Render(unsigned int modelLocation);
	void ParticleRender(unsigned int modelLocation);
	void putParticleShader(GLint ShaderProgram);

	void EnemyCreate(GLint Location);
	bool EnemyAttacked();
	void EnemyDie(GLint index);
	void EnemyRemove(GLint index);
	GLfloat getOz(GLint index);

	void putFactor(glm::mat4 inputFactor) override;
	glm::mat4 getFactor() override;
};

