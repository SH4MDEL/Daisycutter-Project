#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
#include <tchar.h>
#include <ctime>
#include <chrono>
#include <random>
#include <math.h>

#include <gl/glew.h>					// OpenGL에서 필요한 헤더파일 include
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>

#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtc/matrix_transform.hpp>

#pragma comment(lib, "winmm.lib")		// 타이머를 추가하기 위한 헤더파일 include
#include <Mmsystem.h>
		
#pragma comment (lib,"fmod64_vc.lib")	// 음악 추가하기 위한 헤더파일 include
#include "fmod.hpp"	

#define SOUND_MAX 1.0f
#define SOUND_MIN 0.0f
#define MUSICSOUND_DEFAULT 0.3f
#define EFFECTSOUND_DEFAULT 0.8f
#define SOUND_WEIGHT 0.1f

#define MAX_FPS 0.0
#define M_PI 3.1415926535897932384626433832795
#define M_GRAVITY 10
#define SECOND_PER_MINITE 60.0

#define MAX_ENEMY_CREATE 20
#define MAX_PARTICLE_CREATE 20
#define MAX_CLOUD_CREATE 100

namespace RandomDevice
{
	inline GLfloat GetRandomGLfloat(float start, float end)
	{
		std::random_device rd;
		std::default_random_engine dre(rd());

		std::uniform_real_distribution<GLfloat> value(start, end);
		return value(dre);
	}

	inline GLint GetRandomGLint(int start, int end)
	{
		std::random_device rd;
		std::default_random_engine dre(rd());

		std::uniform_int_distribution<GLint> value(start, end);
		return value(dre);
	}
}