#pragma once
#include "Sound.h"

class SOUND_MUSICSOUND : public CSound
{
public:
	enum SoundTag {
		Music1
		, Music2
		, Background
		, Count			// Sound의 개수를 나타내기 위한 임시 태그이다. 지우지 말자.
	};
	SOUND_MUSICSOUND();
	~SOUND_MUSICSOUND();

	void Init() override;
	void Loading() override;
	void Play(int type) override;
	void Stop() override;
	void Release() override;
	void Update() override;

	void VolumeUp() override;
	void VolumeDown() override;

	GLdouble Get_BPM(int type);

private:
	FMOD_SYSTEM* pFmod;					 // 사운드 시스템 변수
	FMOD_SOUND* pSound[Count];            // 사운드 변수
	FMOD_CHANNEL* pChannel;				 // 채널에 담긴 변수를 통째로 컨트롤한다.
	FMOD_CHANNELGROUP* pChannelGroup;
	FMOD_RESULT			r;

	GLfloat fVolume;
	GLdouble dBPM[Count];
};

