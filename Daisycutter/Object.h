#pragma once
#include "stdafx.h"

class CObject
{
protected:
	CObject();
	~CObject();

	virtual void OnCreate() = 0;
	virtual void initBuffer(GLint s_program) = 0;
	virtual void Update(float fTimeElapsed) = 0;
	virtual void Render() = 0;

	virtual void putFactor(glm::mat4 inputFactor) = 0;	// 이동 정보를 바꿉니다.
	virtual glm::mat4 getFactor() = 0;					// 이동 정보를 반환합니다.

	GLint s_program;
};

