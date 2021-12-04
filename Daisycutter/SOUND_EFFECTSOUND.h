#pragma once
#include "Sound.h"

class SOUND_EFFECTSOUND : public CSound
{
public:
	enum SoundTag {
		SelectSound
		, AttackSound
		, HitSound
		, Count			// Sound�� ������ ��Ÿ���� ���� �ӽ� �±��̴�. ������ ����.
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
	FMOD::System* pFmod;					 // ���� �ý��� ����
	FMOD::Sound* Music[Count];            // ���� ����
	FMOD::Channel* ch[Count];				 // ä�ο� ��� ������ ��°�� ��Ʈ���Ѵ�.
	FMOD::ChannelGroup* chGroup[Count];
	FMOD_RESULT			r;

	bool isPlaying;
};

