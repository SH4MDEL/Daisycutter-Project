#include "SOUND_EFFECTSOUND.h"

SOUND_EFFECTSOUND::SOUND_EFFECTSOUND()
{
}


SOUND_EFFECTSOUND::~SOUND_EFFECTSOUND()
{
}

void SOUND_EFFECTSOUND::init()
{
	r = FMOD::System_Create(&pFmod);
	r = pFmod->init(100, FMOD_INIT_NORMAL, NULL);
}

void SOUND_EFFECTSOUND::loading()
{
	// FMOD_LOOP_NORMAL : 계속 반복 재생	// FMOD_LOOP_OFF : 한번만 재생
	r = pFmod->createSound("SOUND\\EFFECTSOUND\\SELECT.mp3", FMOD_LOOP_OFF, NULL, &Music[SelectSound]);
	r = pFmod->createSound("SOUND\\EFFECTSOUND\\ATTACK.mp3", FMOD_LOOP_OFF, NULL, &Music[AttackSound]);
	r = pFmod->createSound("Sound\\EFFECTSOUND\\HIT.mp3", FMOD_LOOP_OFF, NULL, &Music[HitSound]);
}

void SOUND_EFFECTSOUND::play(int _type)
{
	r = pFmod->playSound(Music[_type], chGroup[_type], false, &ch[_type]);		// 노래가 안나오고있으면 시작
}

void SOUND_EFFECTSOUND::stop(int _chNum)
{
	ch[_chNum]->stop();
}

void SOUND_EFFECTSOUND::Release()
{
	Music[SelectSound]->release();			// 사운드 해제
	Music[AttackSound]->release();
	Music[HitSound]->release();
	pFmod->close();									// 사운드 시스템 해제
	pFmod->release();
}

void SOUND_EFFECTSOUND::update(int _chNum)						// 출력중인지 검사하고 출력중이면 시스템을 업데이트함
{
	chGroup[_chNum]->isPlaying(&isPlaying);
	if (isPlaying)
		pFmod->update();
}
