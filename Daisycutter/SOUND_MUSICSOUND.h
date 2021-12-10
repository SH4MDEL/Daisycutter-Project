#pragma once
#include "Sound.h"

class SOUND_MUSICSOUND : public CSound
{
public:
	enum SoundTag {
		Music1
		, Music2
		, Background
		, Count			// Sound�� ������ ��Ÿ���� ���� �ӽ� �±��̴�. ������ ����.
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
	FMOD_SYSTEM* pFmod;					 // ���� �ý��� ����
	FMOD_SOUND* pSound[Count];            // ���� ����
	FMOD_CHANNEL* pChannel;				 // ä�ο� ��� ������ ��°�� ��Ʈ���Ѵ�.
	FMOD_CHANNELGROUP* pChannelGroup;
	FMOD_RESULT			r;

	GLfloat fVolume;
	GLdouble dBPM[Count];
};

