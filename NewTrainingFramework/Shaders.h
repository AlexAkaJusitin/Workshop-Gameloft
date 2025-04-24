#pragma once
#include "../Utilities/utilities.h"

class Shaders 
{
public:
	GLint program, vertexShader, fragmentShader, colorAttribute, positionAttribute, matrixUniform;
	char fileVS[260];
	char fileFS[260];

	int Init(char * fileVertexShader, char * fileFragmentShader);
	~Shaders();
};