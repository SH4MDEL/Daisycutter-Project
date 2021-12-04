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
	// FMOD_LOOP_NORMAL : ��� �ݺ� ���	// FMOD_LOOP_OFF : �ѹ��� ���
	r = pFmod->createSound("SOUND\\MUSICSOUND\\BACKGROUND.mp3", FMOD_LOOP_NORMAL, NULL, &Music[Background]);
}

void SOUND_MUSICSOUND::play(int _type)
{
	r = pFmod->playSound(Music[_type], chGroup[_type], false, &ch[_type]);		// �뷡�� �ȳ����������� ����
}

void SOUND_MUSICSOUND::stop(int _chNum)
{
	ch[_chNum]->stop();
}

void SOUND_MUSICSOUND::Release()
{
	Music[Background]->release();			// ���� ����
	pFmod->close();							// ���� �ý��� ����
	pFmod->release();
}

void SOUND_MUSICSOUND::update(int _chNum)						// ��������� �˻��ϰ� ������̸� �ý����� ������Ʈ��
{
	chGroup[_chNum]->isPlaying(&isPlaying);
	if (isPlaying)
		pFmod->update();
}
