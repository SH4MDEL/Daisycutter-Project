#pragma once
#include "stdafx.h"

class CSound
{
public:

	CSound();
	~CSound();

	virtual void Init() = 0;
	virtual void Loading() = 0;
	virtual void Play(int type) = 0;
	virtual void Stop() = 0;
	virtual void Release() = 0;
	virtual void Update() = 0;

	virtual void VolumeUp() = 0;
	virtual void VolumeDown() = 0;
};

