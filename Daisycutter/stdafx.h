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

#define MAX_FPS 0.0
#define M_PI 3.1415926535897932384626433832795

