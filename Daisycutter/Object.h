#pragma once
#include "stdafx.h"

class CObject
{
public:
	CObject();
	~CObject();

	virtual void Update(float fTimeElapsed) = 0;
	virtual void Render() = 0;
};

