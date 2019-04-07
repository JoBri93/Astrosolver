#include "stdafx.h"
#include "Level.h"

Level::Level()
{
	int checkValue;
	ifstream check("../Resources/UnlockedLevels.txt");
	check >> checkValue;
	check.close();

	for (int i = 0; i < 8; i++) loadLevel[i] = false;
	loadLevel[checkValue] = true;
	
	loadedLevel = checkValue+1;

	for (int i = 0; i < 8; i++) unloadLevel[i] = false;

	for (int i = 0; i < checkValue; i++) byebye[i] = false;
	for (int i = checkValue; i < 8; i++) byebye[i] = true;

}

void Level::LoadLevel(int levelNum)
{
	switch(levelNum)
	{
	case 1:
		brickAmount = 6;
		pos = new vec3[brickAmount];

		pos[0] = vec3(0.0f, 17.25f, 3.75f);

		pos[1] = vec3(-3.75f, 15.75f, 3.75f);
		pos[2] = vec3(3.75f, 15.75f, 3.75f);

		pos[3] = vec3(0.0f, 1.5f, 2.5f);
		pos[4] = vec3(0.0f, 1.5f, -2.5f);
		pos[5] = vec3(0.0f, -9.25f, 0.0f);

		diff = new vec3[brickAmount];
		for (int i = 0; i < brickAmount; i++) diff[i] = vec3(0.25, 0.75, 1.0);

		amb = new vec3[brickAmount];
		for (int i = 0; i < brickAmount; i++) amb[i] = vec3(0.1, 0.1, 0.0);

		size = new vec3[brickAmount];

		size[0] = vec3(2.5f, 30.0f, 2.5f);

		size[1] = vec3(2.5f, 30.0f, 2.5f);
		size[2] = vec3(2.5f, 30.0f, 2.5f);

		size[3] = vec3(5.0f, 1.5f, 5.0f);
		size[4] = vec3(5.0f, 1.5f, 5.0f);
		size[5] = vec3(10.0f, 20.0f, 10.0f);

		pushable = new bool[brickAmount];
		for (int i = 0; i<brickAmount; i++) pushable[i] = false;

		movable = new bool[brickAmount];
		for (int i = 0; i<brickAmount; i++) movable[i] = false;

		button = new int[brickAmount];
		for (int i = 0; i<brickAmount; i++) button[i] = 0;
		button[0] = 2;

		texID = new string[brickAmount];
		texID[0] = "tex44";
		texID[1] = "tex44";
		texID[2] = "tex44";
		texID[3] = "tex42";
		texID[4] = "tex42";
		texID[5] = "tex41";

		break;

	case 2:
		brickAmount = 9;

		pos = new vec3[brickAmount];

		pos[0] = vec3(0.5f, 4.125f, 2.5f);
		pos[1] = vec3(0.0f, -9.25f, 0.0f);
		pos[2] = vec3(-2.5f, 4.0f, 2.5f);
		pos[3] = vec3(-3.75f, 1.5f, -1.25f);
		pos[4] = vec3(-1.25f, 1.5f, -1.25f);
		pos[5] = vec3(1.25f, 1.5f, -1.25f);
		pos[6] = vec3(3.75f, 1.5f, -1.25f);
		pos[7] = vec3(0.5f, 4.0f, 4.5f);
		pos[8] = vec3(0.5f, 4.0f, 0.5f);

		diff = new vec3[brickAmount];
		for (int i = 0; i < brickAmount; i++) diff[i] = vec3(0.75, 0.25, 1.0);

		amb = new vec3[brickAmount];
		for (int i = 0; i < brickAmount; i++) amb[i] = vec3(0.1, 0.1, 0.0);

		size = new vec3[brickAmount];
		size[0] =  vec3(1.0, 6.75, 1.0);
		size[1] = vec3(10.0f, 20.0f, 10.0f);
		size[2] = vec3(5.0f, 6.5f, 5.0f);
		size[3] = vec3(2.5f, 1.5f, 2.5f);
		size[4] = vec3(2.5f, 1.5f, 2.5f);
		size[5] = vec3(2.5f, 1.5f, 2.5f);
		size[6] = vec3(2.5f, 1.5f, 2.5f);
		size[7] = vec3(1.0, 6.5, 1.0);
		size[8] = vec3(1.0, 6.5, 1.0);

		pushable = new bool[brickAmount];
		for (int i = 0; i<brickAmount; i++) pushable[i] = false;
		pushable[0] = true;

		movable = new bool[brickAmount];
		for (int i = 0; i<brickAmount; i++) movable[i] = false;

		button = new int[brickAmount];
		for (int i = 0; i<brickAmount; i++) button[i] = 0;
		button[2] = 1;

		texID = new string[brickAmount];
		texID[0] = "tex410";
		texID[1] = "tex41";
		texID[2] = "tex42";
		texID[3] = "tex44";
		texID[4] = "tex44";
		texID[5] = "tex44";
		texID[6] = "tex44";
		texID[7] = "tex410";
		texID[8] = "tex410";

		break;

	case 3:
		brickAmount = 19;

		pos = new vec3[brickAmount];

		pos[0] = vec3(-2.0, -3.5f, 4.0);
		pos[1] = vec3(-2.0, -2.75f, 2.0);
		pos[2] = vec3(-2.0, -2.0f, 0.0);
		pos[3] = vec3(-2.0, -1.25f, -2.0);
		pos[4] = vec3(-2.0, -0.5f, -4.0);

		pos[5] = vec3(-3.0, 1.75f, -4.0);
		pos[6] = vec3(-3.0, 1.75f, -2.0);
		pos[7] = vec3(-3.0, 1.75f, 0.0);
		pos[8] = vec3(-3.0, 1.75f, 2.0);
		pos[9] = vec3(-3.0, 1.75f, 4.0);

		pos[10] = vec3(-4.0, 10.75f, -4.0);
		pos[11] = vec3(-4.0, 10.75f, -2.0);
		pos[12] = vec3(-4.0, 10.75f, 0.0);
		pos[13] = vec3(-4.0, 10.75f, 2.0);
		pos[14] = vec3(-4.0, 10.75f, 4.0);

		pos[15] = vec3(3.0, -3.5f, -3.0);
		pos[16] = vec3(3.0, -3.5f, 0.0);
		pos[17] = vec3(3.0,-3.5f,3.0);
		pos[18] = vec3(0.0f, -14.25f, 0.0f);

		diff = new vec3[brickAmount];
		for (int i = 0; i < brickAmount; i++) diff[i] = vec3(1.0, 0.25, 0.75);

		amb = new vec3[brickAmount];
		for (int i = 0; i < brickAmount; i++) amb[i] = vec3(0.0, 0.1, 0.1);

		size = new vec3[brickAmount];

		size[0] = vec3(1.0f, 1.5f, 1.0f);
		size[1] = vec3(1.0f, 3.f, 1.0f);
		size[2] = vec3(1.0f, 4.5f, 1.0f);
		size[3] = vec3(1.0f, 6.f, 1.0f);
		size[4] = vec3(1.0f, 7.5f, 1.0f);

		size[5] = vec3(1.0f, 12.f, 1.0f);
		size[6] = vec3(1.0f, 12.f, 1.0f);
		size[7] = vec3(1.0f, 12.f, 1.0f);
		size[8] = vec3(1.0f, 12.f, 1.0f);
		size[9] = vec3(1.0f, 12.f, 1.0f);

		size[10] = vec3(1.0f, 30.0f, 1.0f);
		size[11] = vec3(1.0f, 30.0f, 1.0f);
		size[12] = vec3(1.0f, 30.0f, 1.0f);
		size[13] = vec3(1.0f, 30.0f, 1.0f);
		size[14] = vec3(1.0f, 30.0f, 1.0f);

		size[15] = vec3(3.0f, 1.5f, 3.0f);
		size[16] = vec3(3.0f, 1.5f, 3.0f);
		size[17] = vec3(3.0f, 1.5f, 3.0f);

		size[18] = vec3(9.0f, 20.0f, 9.0f);

		pushable = new bool[brickAmount];
		for(int i = 0; i<brickAmount; i++) pushable[i] = false;

		movable = new bool[brickAmount];
		for (int i = 0; i<brickAmount; i++) movable[i] = false;

		button = new int[brickAmount];
		for (int i = 0; i<brickAmount; i++) button[i] = 0;
		button[7] = 1;
		button[10] = 1;

		texID = new string[brickAmount];
		texID[0] = "tex39";
		texID[1] = "tex39";
		texID[2] = "tex39";
		texID[3] = "tex39";
		texID[4] = "tex39";
		texID[5] = "tex39";
		texID[6] = "tex39";
		texID[7] = "tex39";
		texID[8] = "tex39";
		texID[9] = "tex39";
		texID[10] = "tex39";
		texID[11] = "tex39";
		texID[12] = "tex39";
		texID[13] = "tex39";
		texID[14] = "tex39";
		texID[15] = "tex33";
		texID[16] = "tex33";
		texID[17] = "tex33";
		texID[18] = "tex31";

		break;

	case 4:
		brickAmount = 20;

		pos = new vec3[brickAmount];
		
		pos[0] = vec3(3.0, -3.5f, 4.0);
		pos[1] = vec3(3.0, -3.5f, 3.0);
		pos[2] = vec3(3.0, -3.375f, 2.0);

		pos[3] = vec3(-4.0, -0.5f, -2.0);

		pos[4] = vec3(0.0, 2.75f, 3.0);
		pos[5] = vec3(-3.0, 1.75f, 0.0);
		pos[6] = vec3(-3.0, 3.75f, 3.0);

		pos[7]= vec3(2.0, 0.5f, 4.0);
		pos[8]= vec3(2.0, 0.5f, 3.0);
		pos[9]= vec3(2.0, 0.5f, 2.0);

		pos[10] = vec3(-2.0, -3.5f, -2.0);
		pos[11] = vec3(-3.0, -2.75f, -2.0);
		pos[12] = vec3(-4.0, -2.75, -2.0);

		pos[13] = vec3(-2.0, -3.5f, -3.0);
		pos[14] = vec3(-3.0, -2.75f, -3.0);
		pos[15] = vec3(-4.0, -2.75, -3.0);

		pos[16] = vec3(-2.0, -3.5f, -4.0);
		pos[17] = vec3(-3.0, -3.5f, -4.0);
		pos[18] = vec3(-4.0, -3.5f, -4.0);

		pos[19] = vec3(0.0f, -14.25f, 0.0f);

		diff = new vec3[brickAmount];
		for (int i = 0; i < brickAmount; i++) diff[i] = vec3(1.0, 0.75, 0.25);

		amb = new vec3[brickAmount];
		for (int i = 0; i < brickAmount; i++) amb[i] = vec3(0.0, 0.1, 0.1);

		size = new vec3[brickAmount];

		size[0] = vec3(1.0f, 1.5f, 1.0f);
		size[1] = vec3(1.0f, 1.5f, 1.0f);
		size[2] = vec3(1.0f, 1.75f, 1.0f);

		size[3] = vec3(1.0f, 1.5f, 1.0f);

		size[4] = vec3(3.0f, 14.0f, 3.0f);
		size[5] = vec3(3.0f, 12.0f, 3.0f);
		size[6] = vec3(3.0f, 16.0f, 3.0f);

		size[7] = vec3(1.0f, 9.5f, 1.0f);
		size[8] = vec3(1.0f, 9.5f, 1.0f);
		size[9] = vec3(1.0f, 9.5f, 1.0f);

		size[10] = vec3(1.0f, 1.5f, 1.0f);
		size[11] = vec3(1.0f, 3.0f, 1.0f);
		size[12] = vec3(1.0f, 3.0f, 1.0f);

		size[13] = vec3(1.0f, 1.5f, 1.0f);
		size[14] = vec3(1.0f, 3.0f, 1.0f);
		size[15] = vec3(1.0f, 3.0f, 1.0f);

		size[16] = vec3(1.0f, 1.5f, 1.0f);
		size[17] = vec3(1.0f, 1.5f, 1.0f);
		size[18] = vec3(1.0f, 1.5f, 1.0f);

		size[19] = vec3(9.0f, 20.0f, 9.0f);

		pushable = new bool[brickAmount];
		for (int i = 0; i<brickAmount; i++) pushable[i] = false;
		pushable[2] = true;

		movable = new bool[brickAmount];
		for (int i = 0; i<brickAmount; i++) movable[i] = false;

		button = new int[brickAmount];
		for (int i = 0; i<brickAmount; i++) button[i] = 0;
		button[4] = 1;
		button[6] = 2;
		
		texID = new string[brickAmount];
		texID[0] = "tex39";
		texID[1] = "tex39";
		texID[2] = "tex39";
		texID[3] = "tex39";
		texID[4] = "tex33";
		texID[5] = "tex33";
		texID[6] = "tex33";
		texID[7] = "tex39";
		texID[8] = "tex39";
		texID[9] = "tex39";
		texID[10] = "tex39";
		texID[11] = "tex39";
		texID[12] = "tex39";
		texID[13] = "tex39";
		texID[14] = "tex39";
		texID[15] = "tex39";
		texID[16] = "tex39";
		texID[17] = "tex39";
		texID[18] = "tex39";
		texID[19] = "tex31";

		break;

	case 5:
		brickAmount = 13;

		pos = new vec3[brickAmount];

		pos[0] = vec3(-2.0, 3.375f, 3.75);

		pos[1] = vec3(3.75, -3.0f, -1.25);
		pos[2] = vec3(3.75, -1.75f, 1.25);
		pos[3] = vec3(3.75, 2.75f, 3.75);

		pos[4] = vec3(-3.75, 1.75f, 3.75);

		pos[5] = vec3(-1.25, -3.5f, 3.75);
		pos[6] = vec3(-1.25, -3.5f, 1.25);
		pos[7] = vec3(-1.25, -3.5f, -1.25);
		pos[8] = vec3(-1.25, -3.5f, -3.75);

		pos[9] = vec3(-3.75, -2.0f, 1.25);
		pos[10] = vec3(-3.75, -2.75f, -1.25);
		pos[11] = vec3(-3.75, -3.5f, -3.75);

		pos[12] = vec3(0.0f, -14.25f, 0.0f);

		diff = new vec3[brickAmount];
		for (int i = 0; i < brickAmount; i++) diff[i] = vec3(0.75, 1.0, 0.25);

		amb = new vec3[brickAmount];
		for (int i = 0; i < brickAmount; i++) amb[i] = vec3(0.1, 0.0, 0.1);

		size = new vec3[brickAmount];

		size[0] = vec3(1.0f, 10.75f, 1.0f);

		size[1] = vec3(2.5f, 2.5f, 2.5f);
		size[2] = vec3(2.5f, 5.0f, 2.5f);
		size[3] = vec3(2.5f, 14.0f, 2.5f);

		size[4] = vec3(2.5f, 12.0f, 2.5f);

		size[5] = vec3(2.5f, 1.5f, 2.5f);
		size[6] = vec3(2.5f, 1.5f, 2.5f);
		size[7] = vec3(2.5f, 1.5f, 2.5f);
		size[8] = vec3(2.5f, 1.5f, 2.5f);

		size[9] = vec3(2.5f, 4.5f, 2.5f);
		size[10] = vec3(2.5f, 3.0f, 2.5f);
		size[11] = vec3(2.5f, 1.5f, 2.5f);

		size[12] = vec3(10.0f, 20.0f, 10.0f);

		pushable = new bool[brickAmount];
		for (int i = 0; i<brickAmount; i++) pushable[i] = false;
		pushable[0] = true;

		movable = new bool[brickAmount];
		for (int i = 0; i<brickAmount; i++) movable[i] = false;

		button = new int[brickAmount];
		for (int i = 0; i<brickAmount; i++) button[i] = 0;
		button[4] = 1;
		button[3] = 2;

		texID = new string[brickAmount];
		texID[0] = "tex410";
		texID[1] = "tex44";
		texID[2] = "tex44";
		texID[3] = "tex44";
		texID[4] = "tex44";
		texID[5] = "tex44";
		texID[6] = "tex44";
		texID[7] = "tex44";
		texID[8] = "tex44";
		texID[9] = "tex44";
		texID[10] = "tex44";
		texID[11] = "tex44";
		texID[12] = "tex41";

		break;

	case 6:
		brickAmount = 11;

		pos = new vec3[brickAmount];

		pos[0] = vec3(-3.0, 23.75f, -3.0);

		pos[1] = vec3(-4.0, 14.75f, 4.0);

		pos[2] = vec3(-4.0, 0.25f, 4.0);
		pos[3] = vec3(-3.0, 0.25f, 4.0);
		pos[4] = vec3(-2.0, -1.25f, 4.0);

		pos[5] = vec3(3.0, 3.75f, 3.0);

		pos[6] = vec3(0.0, -3.5f, 3.0);
		pos[7] = vec3(0.0, -3.5f, 0.0);
		pos[8] = vec3(-3.0, -3.5f, 0.0);

		pos[9] = vec3(-3.0, -0.25f, -3.0);

		pos[10] = vec3(0.0f, -14.25f, 0.0f);

		diff = new vec3[brickAmount];
		for (int i = 0; i < brickAmount; i++) diff[i] = vec3(0.25, 1.0, 0.75);

		amb = new vec3[brickAmount];
		for (int i = 0; i < brickAmount; i++) amb[i] = vec3(0.1, 0.0, 0.1);

		size = new vec3[brickAmount];

		size[0] = vec3(1.0f, 40.0f, 1.0f);

		size[1] = vec3(1.0f, 20.0f, 1.0f);

		size[2] = vec3(1.0f, 9.0f, 1.0f);
		size[3] = vec3(1.0f, 9.0f, 1.0f);
		size[4] = vec3(1.0f, 6.0f, 1.0f);

		size[5] = vec3(3.0f, 16.0f, 3.0f);

		size[6] = vec3(3.0f, 1.5f, 3.0f);
		size[7] = vec3(3.0f, 1.5f, 3.0f);
		size[8] = vec3(3.0f, 1.5f, 3.0f);

		size[9] = vec3(3.0f, 8.0f, 3.0f);

		size[10] = vec3(9.0f, 20.0f, 9.0f);

		pushable = new bool[brickAmount];
		for (int i = 0; i<brickAmount; i++) pushable[i] = false;
		pushable[0] = true;

		movable = new bool[brickAmount];
		for (int i = 0; i<brickAmount; i++) movable[i] = false;

		button = new int[brickAmount];
		for (int i = 0; i<brickAmount; i++) button[i] = 0;
		button[2] = 2;
		button[3] = 2;
		button[4] = 2;
		button[1] = 1;

		texID = new string[brickAmount];
		texID[0] = "tex39";
		texID[1] = "tex39";
		texID[2] = "tex39";
		texID[3] = "tex39";
		texID[4] = "tex39";
		texID[5] = "tex33";
		texID[6] = "tex33";
		texID[7] = "tex33";
		texID[8] = "tex33";
		texID[9] = "tex33";
		texID[10] = "tex31";


		break;

	case 7:
		brickAmount = 17;

		pos = new vec3[brickAmount];

		pos[0] = vec3(2.0, -1.75f, -1.0);
		pos[1] = vec3(2.0, -0.75f, 0.0);
		pos[2] = vec3(2.0, -1.75f, 1.0);

		pos[3] = vec3(-4.0, 20.25f, 1.0);
		pos[4] = vec3(-4.0, 20.25f, 0.0);
		pos[5] = vec3(-4.0, 20.25f, -1.0);

		pos[6] = vec3(0.0, 7.0f, 0.0);

		pos[7] = vec3(-3.0, 3.0f, 3.0);
		pos[8] = vec3(-3.0, 3.0f, 0.0);
		pos[9] = vec3(-3.0, 3.0f, -3.0);

		pos[10] = vec3(0.0f, -0.25f, -3.0f);
		pos[11] = vec3(0.0f, -0.25f, 0.0f);
		pos[12] = vec3(0.0f, -0.25f, 3.0f);

		pos[13] = vec3(3.0f, -3.5f, 3.0f);
		pos[14] = vec3(3.0f, -3.5f, 0.0f);
		pos[15] = vec3(3.0f, -3.5f, -3.0f);

		pos[16] = vec3(0.0f, -14.25f, 0.0f);

		diff = new vec3[brickAmount];
		for (int i = 0; i < brickAmount; i++) diff[i] = vec3(0.25, 0.75, 1.0);

		amb = new vec3[brickAmount];
		for (int i = 0; i < brickAmount; i++) amb[i] = vec3(0.1, 0.1, 0.0);

		size = new vec3[brickAmount];

		size[0] = vec3(1.0f, 2.0f, 1.0f);
		size[1] = vec3(1.0f, 4.0f, 1.0f);
		size[2] = vec3(1.0f, 2.0f, 1.0f);

		size[3] = vec3(1.0f, 20.0f, 1.0f);
		size[4] = vec3(1.0f, 20.0f, 1.0f);
		size[5] = vec3(1.0f, 20.0f, 1.0f);

		size[6] = vec3(3.0f, 6.5f, 3.0f);

		size[7] = vec3(3.0f, 14.5f, 3.0f);
		size[8] = vec3(3.0f, 14.5f, 3.0f);
		size[9] = vec3(3.0f, 14.5f, 3.0f);

		size[10] = vec3(3.0f, 8.0f, 3.0f);
		size[11] = vec3(3.0f, 8.0f, 3.0f);
		size[12] = vec3(3.0f, 8.0f, 3.0f);

		size[13] = vec3(3.0f, 1.5f, 3.0f);
		size[14] = vec3(3.0f, 1.5f, 3.0f);
		size[15] = vec3(3.0f, 1.5f, 3.0f);

		size[16] = vec3(9.0f, 20.0f, 9.0f);

		pushable = new bool[brickAmount];
		for (int i = 0; i<brickAmount; i++) pushable[i] = false;
		pushable[0] = true;
		pushable[1] = true;

		movable = new bool[brickAmount];
		for (int i = 0; i<brickAmount; i++) movable[i] = false;

		button = new int[brickAmount];
		for (int i = 0; i<brickAmount; i++) button[i] = 0;
		button[6] = 2;
		button[3] = 1;
		button[4] = 1;
		button[5] = 1;

		texID = new string[brickAmount];
		texID[0] = "tex39";
		texID[1] = "tex39";
		texID[2] = "tex39";
		texID[3] = "tex39";
		texID[4] = "tex39";
		texID[5] = "tex39";
		texID[6] = "tex33";
		texID[7] = "tex33";
		texID[8] = "tex33";
		texID[9] = "tex33";
		texID[10] = "tex33";
		texID[11] = "tex33";
		texID[12] = "tex33";
		texID[13] = "tex33";
		texID[14] = "tex33";
		texID[15] = "tex33";
		texID[16] = "tex31";

		break;

	case 8:
		brickAmount = 20;

		pos = new vec3[brickAmount];

		pos[0] = vec3(-1.875, 2.5f, 4.375);
		pos[1] = vec3(-1.875, 2.5f, 3.125);

		pos[2] = vec3(-4.375, 16.75f, -4.375);
		pos[3] = vec3(-4.375, 16.75f, -3.125);
		pos[4] = vec3(-4.375, 16.75f, -1.875);
		pos[5] = vec3(-4.375, 16.75f, -0.625);
		pos[6] = vec3(-4.375, 16.75f, 0.625);
		pos[7] = vec3(-4.375, 16.75f, 1.875);

		pos[8] = vec3(-3.75f, -1.25f, 1.25);
		pos[9] = vec3(-3.75f, -1.25f, -1.25);
		pos[10] = vec3(-3.75f, -1.25f, -3.75f);

		pos[11] = vec3(-3.75, 2.0f, 3.75);

		pos[12] = vec3(-1.25, -1.25f, 3.75);
		pos[13] = vec3(1.25f, -1.25f, 3.75f);

		pos[14] = vec3(3.75f, 15.75f, 3.75f);

		pos[15] = vec3(1.25f, -3.5f, -1.25f);
		pos[16] = vec3(3.75f, -3.5f, 1.25f);
		pos[17] = vec3(3.75f, -3.5f, -1.25f);
		pos[18] = vec3(3.75f, -3.5f, -3.75f);

		pos[19] = vec3(0.0f, -14.25f, 0.0f);

		diff = new vec3[brickAmount];
		for (int i = 0; i < brickAmount; i++) diff[i] = vec3(0.75, 0.25, 1.0);

		amb = new vec3[brickAmount];
		for (int i = 0; i < brickAmount; i++) amb[i] = vec3(0.1, 0.1, 0.0);

		size = new vec3[brickAmount];

		size[0] = vec3(1.25f, 1.5f, 1.25f);
		size[1] = vec3(1.25f, 1.5f, 1.25f);

		size[2] = vec3(1.25f, 30.0f, 1.25f);
		size[3] = vec3(1.25f, 30.0f, 1.25f);
		size[4] = vec3(1.25f, 30.0f, 1.25f);
		size[5] = vec3(1.25f, 30.0f, 1.25f);
		size[6] = vec3(1.25f, 30.0f, 1.25f);
		size[7] = vec3(1.25f, 30.0f, 1.25f);

		size[8] = vec3(2.5f, 6.0f, 2.5f);
		size[9] = vec3(2.5f, 6.0f, 2.5f);
		size[10] = vec3(2.5f, 6.0f, 2.5f);

		size[11] = vec3(2.5f, 12.5f, 2.5f);

		size[12] = vec3(2.5f, 6.0f, 2.5f);
		size[13] = vec3(2.5f, 6.0f, 2.5f);

		size[14] = vec3(2.5f, 40.0f, 2.5f);

		size[15] = vec3(2.5f, 1.5f, 2.5f);
		size[16] = vec3(2.5f, 1.5f, 2.5f);
		size[17] = vec3(2.5f, 1.5f, 2.5f);
		size[18] = vec3(2.5f, 1.5f, 2.5f);

		size[19] = vec3(10.0f, 20.0f, 10.0f);

		pushable = new bool[brickAmount];
		for (int i = 0; i<brickAmount; i++) pushable[i] = false;

		movable = new bool[brickAmount];
		for (int i = 0; i<brickAmount; i++) movable[i] = false;

		button = new int[brickAmount];
		for (int i = 0; i<brickAmount; i++) button[i] = 0;
		button[2] = 1;
		button[3] = 1;
		button[5] = 2;
		button[6] = 1;
		button[7] = 1;

		button[8] = 1;
		button[9] = 1;
		button[10] = 1;

		texID = new string[brickAmount];
		texID[0] = "tex48";
		texID[1] = "tex48";
		texID[2] = "tex48";
		texID[3] = "tex48";
		texID[4] = "tex48";
		texID[5] = "tex48";
		texID[6] = "tex48";
		texID[7] = "tex48";
		texID[8] = "tex44";
		texID[9] = "tex44";
		texID[10] = "tex44";
		texID[11] = "tex44";
		texID[12] = "tex44";
		texID[13] = "tex44";
		texID[14] = "tex44";
		texID[15] = "tex44";
		texID[16] = "tex44";
		texID[17] = "tex44";
		texID[18] = "tex44";
		texID[19] = "tex41";

		break;
	}
}

void Level::UnloadLevel()
{
	delete[] pos;
	delete[] diff;
	delete[] amb;
	delete[] size;
	delete[] pushable;
	delete[] movable;
	delete[] button;
	delete[] texID;

	int checkValue;
	ifstream check("../Resources/UnlockedLevels.txt");
	check >> checkValue;
	check.close();
	if (loadedLevel > checkValue)
	{
		ofstream saveUnlockedLevels("../Resources/UnlockedLevels.txt");
		if (checkValue == 7) saveUnlockedLevels << 0 << endl;
		else saveUnlockedLevels << loadedLevel << endl;
		saveUnlockedLevels.close();
	}
	
}


Level::~Level()
{
}
