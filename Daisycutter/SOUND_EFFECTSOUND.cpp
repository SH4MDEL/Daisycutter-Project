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
	// FMOD_LOOP_NORMAL : ��� �ݺ� ���	// FMOD_LOOP_OFF : �ѹ��� ���
	r = pFmod->createSound("SOUND\\EFFECTSOUND\\SELECT.mp3", FMOD_LOOP_OFF, NULL, &Music[SelectSound]);
	r = pFmod->createSound("SOUND\\EFFECTSOUND\\ATTACK.mp3", FMOD_LOOP_OFF, NULL, &Music[AttackSound]);
	r = pFmod->createSound("Sound\\EFFECTSOUND\\HIT.mp3", FMOD_LOOP_OFF, NULL, &Music[HitSound]);
}

void SOUND_EFFECTSOUND::play(int _type)
{
	r = pFmod->playSound(Music[_type], chGroup[_type], false, &ch[_type]);		// �뷡�� �ȳ����������� ����
}

void SOUND_EFFECTSOUND::stop(int _chNum)
{
	ch[_chNum]->stop();
}

void SOUND_EFFECTSOUND::Release()
{
	Music[SelectSound]->release();			// ���� ����
	Music[AttackSound]->release();
	Music[HitSound]->release();
	pFmod->close();									// ���� �ý��� ����
	pFmod->release();
}

void SOUND_EFFECTSOUND::update(int _chNum)						// ��������� �˻��ϰ� ������̸� �ý����� ������Ʈ��
{
	chGroup[_chNum]->isPlaying(&isPlaying);
	if (isPlaying)
		pFmod->update();
}
