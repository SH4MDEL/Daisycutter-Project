#pragma once
#include "stdafx.h"

class CObject
{
protected:
	CObject();
	~CObject();

	virtual void OnCreate() = 0;
	virtual void initBuffer(GLint s_program) = 0;
	virtual void initTexture(GLint s_program) = 0;
	virtual void Update(float fTimeElapsed) = 0;
	virtual void Render() = 0;

	virtual void putFactor(glm::mat4 inputFactor) = 0;	// 이동 정보 변경. (초기값은 반드시 원점)
	virtual glm::mat4 getFactor() = 0;					// 이동 정보 반환.

	GLint s_program;
};

