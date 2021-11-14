#pragma once
#include "stdafx.h"

class CFramework
{
private:
	std::chrono::system_clock::time_point m_cuttent_time;
	std::chrono::duration<double> m_timeElapsed;		// 시간이 얼마나 지났는가
	double m_fps;

public:
	CFramework();
	~CFramework();


};

