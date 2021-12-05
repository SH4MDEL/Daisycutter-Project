#include "SOUND_MUSICSOUND.h"

SOUND_MUSICSOUND::SOUND_MUSICSOUND()
{
	fVolume = EFFECTSOUND_DEFAULT;
}


SOUND_MUSICSOUND::~SOUND_MUSICSOUND()
{
}

void SOUND_MUSICSOUND::Init()
{
	r = FMOD_System_Create(&pFmod);
	r = FMOD_System_Init(pFmod, 16, FMOD_INIT_NORMAL, NULL);
}

void SOUND_MUSICSOUND::Loading()
{
	// FMOD_LOOP_NORMAL : ��� �ݺ� ���	// FMOD_LOOP_OFF : �ѹ��� ���
	r = FMOD_System_CreateSound(pFmod, "SOUND\\MUSICSOUND\\BACKGROUND.mp3", FMOD_LOOP_NORMAL, NULL, &pSound[Background]);
}

void SOUND_MUSICSOUND::Play(int type)
{
	r = FMOD_System_PlaySound(pFmod, pSound[type], pChannelGroup, false, &pChannel);		// �뷡�� �ȳ����������� ����
	FMOD_Channel_SetVolume(pChannel, fVolume);
}

void SOUND_MUSICSOUND::Stop()
{
	FMOD_Channel_Stop(pChannel);
}

void SOUND_MUSICSOUND::Release()
{
	for (int i = 0; i < Count; i++) {
		FMOD_Sound_Release(pSound[i]);
	}
	FMOD_System_Close(pFmod);
	FMOD_System_Release(pFmod);
}

void SOUND_MUSICSOUND::Update()						// ��������� �˻��ϰ� ������̸� �ý����� ������Ʈ��
{
	FMOD_System_Update(pFmod);
}

void SOUND_MUSICSOUND::VolumeUp()
{
	if (fVolume < SOUND_MAX) {
		fVolume += SOUND_WEIGHT;
		FMOD_Channel_SetVolume(pChannel, fVolume);
	}
}

void SOUND_MUSICSOUND::VolumeDown()
{
	if (fVolume > SOUND_MIN) {
		fVolume -= SOUND_WEIGHT;
		FMOD_Channel_SetVolume(pChannel, fVolume);
	}
}