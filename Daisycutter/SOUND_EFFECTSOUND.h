#pragma once
#include "Sound.h"

class SOUND_EFFECTSOUND : public CSound
{
public:
	enum SoundTag {
		SelectSound
		, AttackSound
		, HitSound
		, Count			// Sound의 개수를 나타내기 위한 임시 태그이다. 지우지 말자.
	};
	SOUND_EFFECTSOUND();
	~SOUND_EFFECTSOUND();

	void init() override;
	void loading() override;
	void play(int _type) override;
	void stop(int _chNum) override;
	void Release() override;
	void update(int _chNum) override;

private:
	FMOD::System* pFmod;					 // 사운드 시스템 변수
	FMOD::Sound* Music[Count];            // 사운드 변수
	FMOD::Channel* ch[Count];				 // 채널에 담긴 변수를 통째로 컨트롤한다.
	FMOD::ChannelGroup* chGroup[Count];
	FMOD_RESULT			r;

	bool isPlaying;
};

