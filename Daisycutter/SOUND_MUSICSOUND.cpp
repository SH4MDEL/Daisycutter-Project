#include "SOUND_MUSICSOUND.h"

SOUND_MUSICSOUND::SOUND_MUSICSOUND()
{
}


SOUND_MUSICSOUND::~SOUND_MUSICSOUND()
{
}

void SOUND_MUSICSOUND::init()
{
	r = FMOD::System_Create(&pFmod);
	r = pFmod->init(100, FMOD_INIT_NORMAL, NULL);
}

void SOUND_MUSICSOUND::loading()
{
	// FMOD_LOOP_NORMAL : 계속 반복 재생	// FMOD_LOOP_OFF : 한번만 재생
	r = pFmod->createSound("SOUND\\MUSICSOUND\\BACKGROUND.mp3", FMOD_LOOP_NORMAL, NULL, &Music[Background]);
}

void SOUND_MUSICSOUND::play(int _type)
{
	r = pFmod->playSound(Music[_type], chGroup[_type], false, &ch[_type]);		// 노래가 안나오고있으면 시작
}

void SOUND_MUSICSOUND::stop(int _chNum)
{
	ch[_chNum]->stop();
}

void SOUND_MUSICSOUND::Release()
{
	Music[Background]->release();			// 사운드 해제
	pFmod->close();							// 사운드 시스템 해제
	pFmod->release();
}

void SOUND_MUSICSOUND::update(int _chNum)						// 출력중인지 검사하고 출력중이면 시스템을 업데이트함
{
	chGroup[_chNum]->isPlaying(&isPlaying);
	if (isPlaying)
		pFmod->update();
}
