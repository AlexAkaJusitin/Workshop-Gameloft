﻿// NewTrainingFramework.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../Utilities/utilities.h" // if you use STL, please include this line AFTER all other include
#include "Vertex.h"
#include "Shaders.h"
#include <conio.h>
#include "Globals.h"
#include <iostream>
#define PI 3.14159265359

GLuint vboId;
Shaders myShaders;
float angle = 0;
float step = 0.01;

int Init ( ESContext *esContext )
{
	glClearColor ( 0.0f, 0.0f, 0.0f, 0.0f );

	//triangle data (heap)
	Vertex verticesData[3];
	verticesData[0].pos.x =  0.0f;  verticesData[0].pos.y =  0.5f;  verticesData[0].pos.z =  0.0f;
	verticesData[1].pos.x = -0.5f;  verticesData[1].pos.y = -0.5f;  verticesData[1].pos.z =  0.0f;
	verticesData[2].pos.x =  0.5f;  verticesData[2].pos.y = -0.5f;  verticesData[2].pos.z =  0.0f;
	
	//red green blue
	verticesData[0].color.x = 1.0f; verticesData[0].color.y = 0.0f; verticesData[0].color.z = 0.0f;
	verticesData[1].color.x = 0.0f; verticesData[1].color.y = 1.0f; verticesData[1].color.z = 0.0f;
	verticesData[2].color.x = 0.0f; verticesData[2].color.y = 0.0f; verticesData[2].color.z = 1.0f;


	//buffer object
	//generate buffer
	glGenBuffers(1, &vboId);
	//bind buffer
	glBindBuffer(GL_ARRAY_BUFFER, vboId);
	//put data into buffer
	//the buffer won't change so we use GL_STATIC_DRAW
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesData), verticesData, GL_STATIC_DRAW);
	//set the vertex attribute pointer
	//close the buffer
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//creation of shaders and program 
	return myShaders.Init("../Resources/Shaders/TriangleShaderVS.vs", "../Resources/Shaders/TriangleShaderFS.fs");

}

void Draw ( ESContext *esContext )
{
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(myShaders.program);

	glBindBuffer(GL_ARRAY_BUFFER, vboId);

	Matrix mRotation;
	mRotation.SetRotationZ(angle);
	//rotate on z
	if(myShaders.positionAttribute != -1)
	{
		glEnableVertexAttribArray(myShaders.positionAttribute);
		glVertexAttribPointer(myShaders.positionAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	}

	if (myShaders.colorAttribute != -1)
	{
		glEnableVertexAttribArray(myShaders.colorAttribute);
		glVertexAttribPointer(myShaders.colorAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)sizeof(Vector3));
	}

	if (myShaders.matrixUniform != -1)
	{
		glUniformMatrix4fv(myShaders.matrixUniform, 1, GL_FALSE, (GLfloat*)mRotation.m);
	}

	glDrawArrays(GL_TRIANGLES, 0, 3);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	eglSwapBuffers ( esContext->eglDisplay, esContext->eglSurface );
}

void Update ( ESContext *esContext, float deltaTime )
{
	angle += step;
	
	if (angle >= 2 * PI)
		angle -= 2 * PI;


}

void Key ( ESContext *esContext, unsigned char key, bool bIsPressed)
{
	//evenimente de tastatura
}

void CleanUp()
{
	glDeleteBuffers(1, &vboId);
}

int _tmain(int argc, _TCHAR* argv[])
{
	//identifying memory leaks
	_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF ); 

	ESContext esContext;

    esInitContext ( &esContext );

	esCreateWindow ( &esContext, "GAME ENGINE!!!", Globals::screenWidth, Globals::screenHeight, ES_WINDOW_ALPHA | ES_WINDOW_DEPTH);

	if ( Init ( &esContext ) != 0 )
		return 0;

	esRegisterDrawFunc ( &esContext, Draw );
	esRegisterUpdateFunc ( &esContext, Update );
	esRegisterKeyFunc ( &esContext, Key);

	esMainLoop ( &esContext );

	//releasing OpenGL resources
	CleanUp();


	printf("Press any key...\n");
	_getch();

	
	return 0;
}

