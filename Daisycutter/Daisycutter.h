#pragma once
#include "stdafx.h"

const int NUMBER_OF_SHADER = 2;

const char vert_shader_name[NUMBER_OF_SHADER][32] = {
	"vertex.glsl",
	"player_vertex.glsl"
};

const char frag_shader_name[NUMBER_OF_SHADER][32] = {
	"fragment.glsl",
	"player_fragment.glsl"
};