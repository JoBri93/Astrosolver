// TheGame.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

CreateGame game;

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);

	game.Create();

	glutMainLoop();
	return 0;
}




