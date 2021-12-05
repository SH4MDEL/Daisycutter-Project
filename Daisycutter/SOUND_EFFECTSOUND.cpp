#include "SOUND_EFFECTSOUND.h"

SOUND_EFFECTSOUND::SOUND_EFFECTSOUND()
{
	fVolume = EFFECTSOUND_DEFAULT;
}


SOUND_EFFECTSOUND::~SOUND_EFFECTSOUND()
{
}

void SOUND_EFFECTSOUND::Init()
{
	r = FMOD_System_Create(&pFmod);
	r = FMOD_System_Init(pFmod, 16, FMOD_INIT_NORMAL, NULL);
}

void SOUND_EFFECTSOUND::Loading()
{
	// FMOD_LOOP_NORMAL : 계속 반복 재생	// FMOD_LOOP_OFF : 한번만 재생
	r = FMOD_System_CreateSound(pFmod, "SOUND\\EFFECTSOUND\\SELECT.mp3", FMOD_LOOP_OFF, NULL, &pSound[SelectSound]);
	r = FMOD_System_CreateSound(pFmod, "SOUND\\EFFECTSOUND\\ATTACK.mp3", FMOD_LOOP_OFF, NULL, &pSound[AttackSound]);
	r = FMOD_System_CreateSound(pFmod, "SOUND\\EFFECTSOUND\\HIT.mp3", FMOD_LOOP_OFF, NULL, &pSound[HitSound]);
}

void SOUND_EFFECTSOUND::Play(int type)
{
	r = FMOD_System_PlaySound(pFmod, pSound[type], pChannelGroup, false, &pChannel);		// 노래가 안나오고있으면 시작
	FMOD_Channel_SetVolume(pChannel, fVolume);
}

void SOUND_EFFECTSOUND::Stop()
{
	FMOD_Channel_Stop(pChannel);
}

void SOUND_EFFECTSOUND::Release()
{
	for (int i = 0; i < Count; i++) {
		FMOD_Sound_Release(pSound[i]);
	}
	FMOD_System_Close(pFmod);
	FMOD_System_Release(pFmod);
}

void SOUND_EFFECTSOUND::Update()						// 출력중인지 검사하고 출력중이면 시스템을 업데이트함
{
	FMOD_System_Update(pFmod);
}

void SOUND_EFFECTSOUND::VolumeUp()
{
	if (fVolume < SOUND_MAX) {
		fVolume += SOUND_WEIGHT;
		FMOD_Channel_SetVolume(pChannel, fVolume);
	}
}

void SOUND_EFFECTSOUND::VolumeDown()
{
	if (fVolume > SOUND_MIN) {
		fVolume -= SOUND_WEIGHT;
		FMOD_Channel_SetVolume(pChannel, fVolume);
	}
}
