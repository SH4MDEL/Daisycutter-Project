#pragma once
#include "Sound.h"

class SOUND_MUSICSOUND : public CSound
{
public:
	enum SoundTag {
		Background
		, Count			// Sound�� ������ ��Ÿ���� ���� �ӽ� �±��̴�. ������ ����.
	};
	SOUND_MUSICSOUND();
	~SOUND_MUSICSOUND();

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

