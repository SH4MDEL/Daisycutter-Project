#pragma once
#include "stdafx.h"

class CFramework
{
private:
	std::chrono::system_clock::time_point m_cuttent_time;
	std::chrono::duration<double> m_timeElapsed;		// �ð��� �󸶳� �����°�
	double m_fps;

public:
	CFramework();
	~CFramework();


};

