#pragma once
#include "stdafx.h"

class CSound
{
public:
	enum SoundTag {
		MainSound
		, bbkkbkk
		, TrueBlue
		, Select
		, MusicStart
		, GameStart
		, Hitsound
		, Count			// Sound의 개수를 나타내기 위한 임시 태그이다. 지우지 말자.
	};

	CSound();
	~CSound();

	virtual void init() = 0;
	virtual void loading() = 0;
	virtual void play(int _type) = 0;
	virtual void stop(int _chNum) = 0;
	virtual void Release() = 0;
	virtual void update(int _chNum) = 0;
};

