#include "stdafx.h"
#include "CreateGame.h"

#include <string>
#include <iostream>
using namespace std;

Scene CreateGame::scene;
Camera CreateGame::cam;
bool CreateGame::keystate[256];
Player *CreateGame::player;
Menu *CreateGame::menu;
Background *CreateGame::background;
Background *CreateGame::whichLevel;
Crystal **CreateGame::block;
Panel **CreateGame::panel;
Panel *CreateGame::exit;

Background *CreateGame::goodbyeScreen;

Level CreateGame::level;

bool loadPlayer = false;
bool blockMovement = false;

bool menuOnOff = true;
bool controls = false;

bool loadBG = false;
bool isJumping = false;

bool gameEnding;

LPCWSTR GameplayTheme = L"../Resources/Audio/Ambiance1.wav";

bool CreateGame::light1state =  true;
bool CreateGame::light2state = true;

void CreateGame::OnRender() {
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-10.0f, 10.0f, -10.0f, 10.0f, -50.0f, 50.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Ustawienie kamery na podstawie jej stanu przechowywanego w zmiennej player.
	gluLookAt(
		cam.pos.x, cam.pos.y, cam.pos.z,
		cam.pos.x + cam.dir.x, cam.pos.y + cam.dir.y, cam.pos.z + cam.dir.z,
		0.0f, 1.0f, 0.0f
	);
	glRotatef(35.0f, 1.0f, 0.0f, 0.0f);
	glRotatef(-45.0f, 0.0f, 1.0f, 0.0f);
	glScalef(1.0f, 1.0f, -1.0f);

	if (light1state)
	{
		GLfloat l0_ambient[] = {  1.0f, 0.0f, 0.0f };
		GLfloat l0_diffuse[] = { 0.2f, 0.2f, 0.5f };
		GLfloat l0_specular[] = { 0.0f,0.0f, 0.0f };
		GLfloat l0_position[] = { -5.0, 10.0, -5.0, 0.0f };

		glEnable(GL_LIGHT0);
		glLightfv(GL_LIGHT0, GL_AMBIENT, l0_ambient);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, l0_diffuse);
		glLightfv(GL_LIGHT0, GL_SPECULAR, l0_specular);
		glLightfv(GL_LIGHT0, GL_POSITION, l0_position);
		glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 0);
		glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.2);
		glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0);
	}
	else
	{
		glDisable(GL_LIGHT0);
	}

	if (light2state)
	{
		GLfloat l0_ambient[] = { 0.5f, 0.5f, 1.0f };
		GLfloat l0_diffuse[] = { 0.5f, 0.5f, 1.0f };
		GLfloat l0_specular[] = { 1.0f, 1.0f, 1.0f };
		GLfloat l0_position[] = {5.0, 10.0, 5.0, 0.0f };

		glEnable(GL_LIGHT1);
		glLightfv(GL_LIGHT1, GL_AMBIENT, l0_ambient);
		glLightfv(GL_LIGHT1, GL_DIFFUSE, l0_diffuse);
		glLightfv(GL_LIGHT1, GL_SPECULAR, l0_specular);
		glLightfv(GL_LIGHT1, GL_POSITION, l0_position);
		glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 0.0);
		glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.2);
		glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0.0);
	}
	else
	{
		glDisable(GL_LIGHT1);
	}

	menu->Render();
	background->Render();
	whichLevel->Render();
	goodbyeScreen->Render();

	scene.Render();
	
	glFlush();
	glutSwapBuffers();
	glutPostRedisplay();

}

void CreateGame::OnReshape(int width, int height) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, width, height);
	gluPerspective(60.0f, (float)width / height, .01f, 100.0f);
}

void CreateGame::OnKeyPress(unsigned char key, int x, int y) {
	if (!keystate[key]) {
		OnKeyDown(key, x, y); // Emulacja zdarzenia zwi¹zanego z pojedynczym wciœniêciem klawisza
	}
	keystate[key] = true;
}

// Obs³uga naszego w³asnego zdarzenia, gdy zostanie po raz pierwszy wciœniêty klawisz - zdarzenie odporne na repetycjê.
void CreateGame::OnKeyDown(unsigned char key, int x, int y) {
	if (key == 'w')
	{	
		if(menuOnOff && !controls)	menu->whichPos = (menu->whichPos + 1) % 3;
	}
	if (key == 's')
	{
		if (menuOnOff && !controls)	menu->whichPos = (menu->whichPos - 1) % -3;
	}
	if (key == 27)
	{
		menuOnOff = !menuOnOff;
		if (gameEnding) glutLeaveMainLoop();
	}
	if (key == 'e')
	{
		if(menuOnOff)
		{
			if (menu->whichPos == 0) glutLeaveMainLoop();
			if (menu->whichPos == 2)
			{
				menuOnOff = false;
			}
			if (menu->whichPos == 1)
			{
				controls = !controls;
				if(controls) menu->textureName = "controls";
				if(!controls) menu->textureName = "menu";
			}
		}
		if (level.loadedLevel == 1)
		{
			if (block[0]->buttonArea)
			{
				block[0]->isOn = !block[0]->isOn;
			}
		}
		if (level.loadedLevel == 2)
		{
			if (block[2]->buttonArea)
			{
				block[2]->isOn = !block[2]->isOn;
			}
		}
		if (level.loadedLevel == 3)
		{
			if (block[7]->buttonArea)
			{
				block[7]->isOn = !block[7]->isOn;
			}
			if (block[10]->buttonArea)
			{
				block[10]->isOn = !block[10]->isOn;
			}
		}
		if (level.loadedLevel == 4)
		{
			if (block[4]->buttonArea)
			{
				block[4]->isOn = !block[4]->isOn;
			}
			if (block[6]->buttonArea)
			{
				block[6]->isOn = !block[6]->isOn;
			}
		}
		if (level.loadedLevel == 5)
		{
			if (block[4]->buttonArea)
			{
				block[4]->isOn = !block[4]->isOn;
			}
			if (block[3]->buttonArea)
			{
				block[3]->isOn = !block[3]->isOn;
			}
		}
		if (level.loadedLevel == 6)
		{
			if (block[1]->buttonArea)
			{
				block[1]->isOn = !block[1]->isOn;
			}
			if (block[2]->buttonArea)
			{
				block[2]->isOn = !block[2]->isOn;
				block[2]->clicked = true;
			}
			if (block[3]->buttonArea)
			{
				block[3]->isOn = !block[3]->isOn;
				block[3]->clicked = true;
			}
			if (block[4]->buttonArea)
			{
				block[4]->isOn = !block[4]->isOn;
				block[4]->clicked = true;
			}
		}
		if (level.loadedLevel == 7)
		{
			if (block[6]->buttonArea)
			{
				block[6]->isOn = !block[6]->isOn;
			}

			if (block[3]->buttonArea)
			{
				block[3]->isOn = !block[3]->isOn;
				block[3]->clicked = true;
			}
			if (block[4]->buttonArea)
			{
				block[4]->isOn = !block[4]->isOn;
				block[4]->clicked = true;
			}
			if (block[5]->buttonArea)
			{
				block[5]->isOn = !block[5]->isOn;
				block[5]->clicked = true;
			}
		}
		if (level.loadedLevel == 8)
		{
			if (block[2]->buttonArea)
			{
				block[2]->isOn = !block[2]->isOn;
				block[2]->clicked = true;
			}
			if (block[3]->buttonArea)
			{
				block[3]->isOn = !block[3]->isOn;
				block[3]->clicked = true;
			}
			if (block[6]->buttonArea)
			{
				block[6]->isOn = !block[6]->isOn;
				block[6]->clicked = true;
			}
			if (block[7]->buttonArea)
			{
				block[7]->isOn = !block[7]->isOn;
				block[7]->clicked = true;
			}

			if (block[8]->buttonArea)
			{
				block[8]->isOn = !block[8]->isOn;
				block[8]->clicked = true;
			}
			if (block[9]->buttonArea)
			{
				block[9]->isOn = !block[9]->isOn;
				block[9]->clicked = true;
			}
			if (block[10]->buttonArea)
			{
				block[10]->isOn = !block[10]->isOn;
				block[10]->clicked = true;
			}
			if (block[5]->buttonArea)
			{
				block[5]->isOn = !block[5]->isOn;
			}
		}
	}

	if (key == 32)
	{
		if(!player->dontJump) player->isJumping = true;
	}
}

void CreateGame::OnKeyUp(unsigned char key, int x, int y) {
	keystate[key] = false;
}

void CreateGame::OnTimer(int id) {

	if (level.loadLevel[0])
	{
		level.LoadLevel(1);
		block = new Crystal *[level.brickAmount];
		for (int i = 0; i < level.brickAmount; i++)
		{
			block[i] = new Crystal(level.pos[i], level.diff[i], level.amb[i], level.size[i].x, level.size[i].y, level.size[i].z, level.pushable[i], level.movable[i], level.button[i], level.texID[i]);	
			scene.AddObject(block[i]);		
		}
		background->textureName = "bg1";
		whichLevel->textureName = "level1";

		exit = new Panel(vec3(0.0, 2.3, -4.0), vec3(0.05, 0.05, 0.2), 2, "exit");
		scene.AddObject(exit);
		level.loadLevel[0] = false;
		level.loadedLevel = 1;
	}

	if (level.loadedLevel == 1)
	{
		if (block[0]->isOn)
		{
			exit->isUnlocked = true;
		}
		if (player->pos.y > 40.f && level.byebye[0])
		{
			level.unloadLevel[0] = true;
			level.byebye[0] = false;
		}
	}

	if (level.unloadLevel[0])
	{	
		scene.DeleteObject();
		delete exit;
		for (int i = 0; i < level.brickAmount; i++)
		{
			scene.DeleteObject();
			delete block[i];
		}

		level.UnloadLevel();

		level.unloadLevel[0] = false;
		level.loadLevel[1] = true;
	}

	//Level 2
	if (level.loadLevel[1])
	{
		level.LoadLevel(2);
		player->pos = vec3(-4.0, 30.0, -4.0);
		player->isFalling = true;
		player->diffuse = vec3(0.7, 0.2, 0.9);
		player->ambient = vec3(0.1, 0.1, 0.0);

		block = new Crystal *[level.brickAmount];
		for (int i = 0; i < level.brickAmount; i++)
		{
			block[i] = new Crystal(level.pos[i], level.diff[i], level.amb[i], level.size[i].x, level.size[i].y, level.size[i].z, level.pushable[i], level.movable[i], level.button[i], level.texID[i]);
			scene.AddObject(block[i]);

		}
		background->textureName = "bg2";
		whichLevel->textureName = "level2";

		exit = new Panel(vec3(-4.0, 7.3, 4.0), vec3(0.05, 0.05, 0.2), 2, "exit");
		scene.AddObject(exit);

		level.loadLevel[1] = false;
		level.loadedLevel = 2;

	}

	if (level.loadedLevel == 2)
	{
		if (block[2]->isOn)
		{
			exit->isUnlocked = true;
			block[3]->movable = true;
			block[4]->movable = true;
		}
		if (player->pos.y > 40.f && level.byebye[1])
		{
			level.unloadLevel[1] = true;
			level.byebye[1] = false;
		}
	}

	if (level.unloadLevel[1])
	{
		scene.DeleteObject();
		delete exit;
		for (int i = 0; i < level.brickAmount; i++)
		{
			scene.DeleteObject();
			delete block[i];
		}

		level.UnloadLevel();

		level.unloadLevel[1] = false;
		level.loadLevel[2] = true;
	}

	//Level 3
	if (level.loadLevel[2])
	{
		level.LoadLevel(3);
		player->pos = vec3(3.0, 30.0, 0.0);
		player->isFalling = true;
		player->diffuse = vec3(0.9, 0.2, 0.7);
		player->ambient = vec3(0.0, 0.1, 0.1);

		block = new Crystal *[level.brickAmount];
		for (int i = 0; i < level.brickAmount; i++)
		{
			block[i] = new Crystal(level.pos[i], level.diff[i], level.amb[i], level.size[i].x, level.size[i].y, level.size[i].z, level.pushable[i], level.movable[i], level.button[i], level.texID[i]);
			scene.AddObject(block[i]);

		}
		background->textureName = "bg3";
		whichLevel->textureName = "level3";

		block[10]->buttonPos.y = block[10]->pos.y - block[10]->height * 0.5 + 14.0f;
		block[0]->movableHeight = 10.5f;
		block[2]->movableHeight = 7.5f;

		panel = new Panel *[1];
		panel[0] = new Panel(vec3(3.0, -2.6, -3.0), vec3(0.05, 0.05, 0.2), 1, "panel");
		scene.AddObject(panel[0]);

		exit = new Panel(vec3(3.0, -2.6, 3.0), vec3(0.05, 0.05, 0.2), 2, "exit");
		scene.AddObject(exit);

		level.loadLevel[2] = false;
		level.loadedLevel = 3;

	}

	if (level.loadedLevel == 3)
	{
		if (panel[0]->isUnlocked)
		{
			block[2]->movable = true;
		}
		else
		{
			block[2]->movable = false;
		}
		if (block[7]->isOn)
		{
			block[0]->movable = true;
		}

		if (block[10]->isOn)
		{
			exit->isUnlocked = true;
		}

		if (player->pos.y > 40.f && level.byebye[2])
		{
			level.unloadLevel[2] = true;
			level.byebye[2] = false;
		}
	}

	if (level.unloadLevel[2])
	{
		scene.DeleteObject();
		delete exit;

		scene.DeleteObject();
		delete panel[0];
		delete[] panel;

		for (int i = 0; i < level.brickAmount; i++)
		{
			scene.DeleteObject();
			delete block[i];
		}	

		level.UnloadLevel();

		level.unloadLevel[2] = false;
		level.loadLevel[3] = true;
	}

	//Level 4
	if (level.loadLevel[3])
	{
		level.LoadLevel(4);
		player->pos = vec3(3.0, 30.0, -3.0);
		player->isFalling = true;
		player->diffuse = vec3(0.9, 0.7, 0.2);
		player->ambient = vec3(0.0, 0.1, 0.1);

		block = new Crystal *[level.brickAmount];
		for (int i = 0; i < level.brickAmount; i++)
		{
			block[i] = new Crystal(level.pos[i], level.diff[i], level.amb[i], level.size[i].x, level.size[i].y, level.size[i].z, level.pushable[i], level.movable[i], level.button[i], level.texID[i]);
			scene.AddObject(block[i]);

		}
		background->textureName = "bg4";
		whichLevel->textureName = "level4";

		block[4]->buttonPos.y = block[4]->pos.y - block[4]->height * 0.5 + 11.5f;
		block[6]->buttonPos.y = block[6]->pos.y - block[6]->height * 0.5 + 14.0f;

		block[3]->movableHeight = 7.5f;
		block[0]->movableHeight = 8.0f;
		block[1]->movableHeight = 8.0f;

		panel = new Panel *[1];
		panel[0] = new Panel(vec3(0.0, -4.2, 0.0), vec3(0.05, 0.05, 0.2), 1, "panel");
		scene.AddObject(panel[0]);

		exit = new Panel(vec3(-3.0,11.8, 3.0), vec3(0.05, 0.05, 0.2), 2, "exit");
		scene.AddObject(exit);

		level.loadLevel[3] = false;
		level.loadedLevel = 4;
	}

	if (level.loadedLevel == 4)
	{
		if (block[4]->isOn)
		{
			block[3]->movable = true;
		}
		if (panel[0]->isUnlocked)
		{
			block[0]->movable = true;
			block[1]->movable = true;
		}
		else
		{
			block[0]->movable = false;
			block[1]->movable = false;
		}
		if (block[6]->isOn)
		{
			exit->isUnlocked = true;
		}

		if (player->pos.y > 40.f && level.byebye[3])
		{
			level.unloadLevel[3] = true;
			level.byebye[3] = false;
		}
	}

	if (level.unloadLevel[3])
	{
		scene.DeleteObject();
		delete exit;

		scene.DeleteObject();
		delete panel[0];
		delete[] panel;

		for (int i = 0; i < level.brickAmount; i++)
		{
			scene.DeleteObject();
			delete block[i];
		}

		level.UnloadLevel();

		level.unloadLevel[3] = false;
		level.loadLevel[4] = true;
	}

	//Level 5
	if (level.loadLevel[4])
	{
		level.LoadLevel(5);
		player->isFalling = true;
		player->pos = vec3(-1.25, 30.0, 1.25);
		player->diffuse = vec3(0.7, 0.9, 0.2);
		player->ambient = vec3(0.1, 0.0, 0.1);

		block = new Crystal *[level.brickAmount];
		for (int i = 0; i < level.brickAmount; i++)
		{
			block[i] = new Crystal(level.pos[i], level.diff[i], level.amb[i], level.size[i].x, level.size[i].y, level.size[i].z, level.pushable[i], level.movable[i], level.button[i], level.texID[i]);
			scene.AddObject(block[i]);

		}
		background->textureName = "bg1";
		whichLevel->textureName = "level5";

		block[2]->movableHeight = 9.0f;
		block[9]->movableHeight = 10.5f;
		block[10]->movableHeight = 10.5f;
		block[11]->movableHeight = 10.5f;

		block[4]->buttonPos.y = block[4]->pos.y - block[4]->height * 0.5 + 3.5f;

		panel = new Panel *[3];
		panel[0] = new Panel(vec3(3.75, -4.2, -3.75), vec3(0.05, 0.05, 0.2), 1, "panel");
		scene.AddObject(panel[0]);
		
		panel[1] = new Panel(vec3(-3.75, 7.8, 3.75), vec3(0.05, 0.05, 0.2), 1, "panel");
		scene.AddObject(panel[1]);

		exit = new Panel(vec3(3.75, 9.8, 3.75), vec3(0.05, 0.05, 0.2), 2, "exit");
		scene.AddObject(exit);

		level.loadLevel[4] = false;
		level.loadedLevel = 5;
	}

	if (level.loadedLevel == 5)
	{
		if (block[4]->isOn)
		{
			block[9]->movable = true;
			block[11]->movable = true;
		}
		if (block[3]->isOn)
		{
			exit->isUnlocked = true;
		}
		if (panel[0]->isUnlocked)
		{
			block[10]->movable = true;
		}
		else
		{
			block[10]->movable = false;
		}
		if (panel[1]->isUnlocked)
		{
			block[2]->movable = true;
		}
		else
		{
			block[2]->movable = false;
		}
		if (player->pos.y > 40.f && level.byebye[4])
		{
			level.unloadLevel[4] = true;
			level.byebye[4] = false;
		}
	}

	if (level.unloadLevel[4])
	{
		scene.DeleteObject();
		delete exit;

		scene.DeleteObject();
		delete panel[1];
		scene.DeleteObject();
		delete panel[0];
		
		delete[] panel;
		for (int i = 0; i < level.brickAmount; i++)
		{
			scene.DeleteObject();
			delete block[i];
		}

		level.UnloadLevel();
		level.unloadLevel[4] = false;
		level.loadLevel[5] = true;
	}
	
	//Level 6
	if (level.loadLevel[5])
	{
		level.LoadLevel(6);
		player->isFalling = true;
		player->pos = vec3(0.0, 30.0, 0.0);
		player->diffuse = vec3(0.2, 0.9, 0.7);
		player->ambient = vec3(0.1, 0.0, 0.1);

		block = new Crystal *[level.brickAmount];
		for (int i = 0; i < level.brickAmount; i++)
		{
			block[i] = new Crystal(level.pos[i], level.diff[i], level.amb[i], level.size[i].x, level.size[i].y, level.size[i].z, level.pushable[i], level.movable[i], level.button[i], level.texID[i]);
			scene.AddObject(block[i]);
		}
		background->textureName = "bg2";
		whichLevel->textureName = "level6";

		block[8]->movableHeight = 6.5f;
		block[6]->movableHeight = 14.5f;

		panel = new Panel *[4];
		panel[0] = new Panel(vec3(2.0, -2.0, 1.45), vec3(0.05, 0.05, 0.2), 3, "panel");
		scene.AddObject(panel[0]);

		panel[1] = new Panel(vec3(3.0, -2.0, 1.45), vec3(0.05, 0.05, 0.2), 3, "panel");
		scene.AddObject(panel[1]);

		panel[2] = new Panel(vec3(4.0, -2.0, 1.45), vec3(0.05, 0.05, 0.2), 3, "panel");
		scene.AddObject(panel[2]);

		panel[3] = new Panel(vec3(0.0, -4.2, -3.0), vec3(0.05, 0.05, 0.2), 1, "panel");
		scene.AddObject(panel[3]);

		exit = new Panel(vec3(3.0, 11.8, 3.0), vec3(0.05, 0.05, 0.2), 2, "exit");
		scene.AddObject(exit);

		level.loadLevel[5] = false;
		level.loadedLevel = 6;
	}

	if (level.loadedLevel == 6)
	{
		//block[2]: xor 101
		//block[3]: and 010
		//block[4]: xor 110

		if (block[2]->clicked)
		{
			panel[0]->isUnlocked = !panel[0]->isUnlocked;
			panel[2]->isUnlocked = !panel[2]->isUnlocked;
			block[2]->clicked = false;
		}

		if (block[3]->clicked)
		{
			panel[0]->isUnlocked = !panel[0]->isUnlocked;
			panel[1]->isUnlocked = !panel[1]->isUnlocked;
			block[3]->clicked= false;
		}

		if (block[4]->clicked)
		{
			panel[0]->isUnlocked *= true;
			panel[1]->isUnlocked *= false;
			panel[2]->isUnlocked *= true;
			block[4]->clicked = false;
		}

		if (panel[0]->isUnlocked && panel[1]->isUnlocked && panel[2]->isUnlocked)
		{
			block[8]->movable = true;
		}

		if (panel[3]->isUnlocked)
		{
			block[6]->movable = true;
		}
		else
		{
			block[6]->movable = false;
		}
		if (block[1]->isOn)
		{
			exit->isUnlocked = true;
		}


		if (player->pos.y > 40.f && level.byebye[5])
		{
			level.unloadLevel[5] = true;
			level.byebye[5] = false;
		}
	}

	if (level.unloadLevel[5])
	{
		scene.DeleteObject();
		delete exit;

		scene.DeleteObject();
		delete panel[3];
		scene.DeleteObject();
		delete panel[2];
		scene.DeleteObject();
		delete panel[1];
		scene.DeleteObject();
		delete panel[0];

		delete[] panel;
		for (int i = 0; i < level.brickAmount; i++)
		{
			scene.DeleteObject();
			delete block[i];
		}

		level.UnloadLevel();
		level.unloadLevel[5] = false;
		level.loadLevel[6] = true;
	}

	//Level 7
	if (level.loadLevel[6])
	{
		level.LoadLevel(7);
		player->pos = vec3(3.0, 30.0, 0.0);
		player->isFalling = true;
		player->diffuse = vec3(0.2, 0.7, 0.9);
		player->ambient = vec3(0.1, 0.1, 0.0);

		block = new Crystal *[level.brickAmount];
		for (int i = 0; i < level.brickAmount; i++)
		{
			block[i] = new Crystal(level.pos[i], level.diff[i], level.amb[i], level.size[i].x, level.size[i].y, level.size[i].z, level.pushable[i], level.movable[i], level.button[i], level.texID[i]);
			scene.AddObject(block[i]);
		}
		background->textureName = "bg3";
		whichLevel->textureName = "level7";

		block[15]->movableHeight = 10.0f;

		panel = new Panel *[4];
		panel[0] = new Panel(vec3(1.55, 7.0, 0.5), vec3(0.05, 0.05, 0.2), 4, "panel");
		scene.AddObject(panel[0]);

		panel[1] = new Panel(vec3(1.55, 7.0, -0.5), vec3(0.05, 0.05, 0.2), 4, "panel");
		scene.AddObject(panel[1]);

		panel[2] = new Panel(vec3(1.55, 4.0, 0.5), vec3(0.05, 0.05, 0.2), 4, "panel");
		scene.AddObject(panel[2]);

		panel[3] = new Panel(vec3(1.55, 4.0, -0.5), vec3(0.05, 0.05, 0.2), 4, "panel");
		scene.AddObject(panel[3]);

		exit = new Panel(vec3(0.0, 3.8, 3.0), vec3(0.05, 0.05, 0.2), 2, "exit");
		scene.AddObject(exit);

		level.loadLevel[6] = false;
		level.loadedLevel = 7;
	}

	if (level.loadedLevel == 7)
	{
		if (block[6]->isOn)
		{
			block[15]->movable = true;
		}

		if (block[3]->clicked)
		{
			panel[0]->isUnlocked = !panel[0]->isUnlocked;
			panel[1]->isUnlocked = !panel[1]->isUnlocked;
			panel[2]->isUnlocked = !panel[2]->isUnlocked;
			block[3]->clicked = false;
		}
		if (block[4]->clicked)
		{
			panel[2]->isUnlocked = !panel[2]->isUnlocked;
			panel[3]->isUnlocked = !panel[3]->isUnlocked;
			block[4]->clicked = false;
		}
		if (block[5]->clicked)
		{
			panel[0]->isUnlocked *= true;
			panel[1]->isUnlocked *= false;
			panel[2]->isUnlocked *= true;
			panel[3]->isUnlocked *= false;
			block[5]->clicked = false;
		}

		if (panel[0]->isUnlocked && panel[1]->isUnlocked && panel[2]->isUnlocked && panel[3]->isUnlocked)
		{
			exit->isUnlocked = true;
		}

		if (player->pos.y > 40.f && level.byebye[6])
		{
			level.unloadLevel[6] = true;
			level.byebye[6] = false;
		}
	}

	if (level.unloadLevel[6])
	{
		scene.DeleteObject();
		delete exit;

		scene.DeleteObject();
		delete panel[3];
		scene.DeleteObject();
		delete panel[2];
		scene.DeleteObject();
		delete panel[1];
		scene.DeleteObject();
		delete panel[0];

		for (int i = 0; i < level.brickAmount; i++)
		{
			scene.DeleteObject();
			delete block[i];
		}

		level.UnloadLevel();
		level.unloadLevel[6] = false;
		level.loadLevel[7] = true;
	}

	//Level 8
	if (level.loadLevel[7])
	{
		level.LoadLevel(8);
		player->pos = vec3(0.0, 30.0, -3.75);
		player->isFalling = true;
		player->diffuse = vec3(0.7, 0.2, 0.9);
		player->ambient = vec3(0.1, 0.1, 0.0);

		block = new Crystal *[level.brickAmount];
		for (int i = 0; i < level.brickAmount; i++)
		{
			block[i] = new Crystal(level.pos[i], level.diff[i], level.amb[i], level.size[i].x, level.size[i].y, level.size[i].z, level.pushable[i], level.movable[i], level.button[i], level.texID[i]);
			scene.AddObject(block[i]);
		}
		background->textureName = "bg4";
		whichLevel->textureName = "level8";

		block[4]->movableHeight = 7.0f;

		block[16]->movableHeight = 4.5f;

		panel = new Panel *[10];
		panel[0] = new Panel(vec3(-1.5, -1.0, 2.45), vec3(0.05, 0.05, 0.2), 3, "panel");
		scene.AddObject(panel[0]);

		panel[1] = new Panel(vec3(-0.5, -1.0, 2.45), vec3(0.05, 0.05, 0.2), 3, "panel");
		scene.AddObject(panel[1]);

		panel[2] = new Panel(vec3(0.5, -1.0, 2.45), vec3(0.05, 0.05, 0.2), 3, "panel");
		scene.AddObject(panel[2]);

		panel[3] = new Panel(vec3(1.5, -1.0, 2.45), vec3(0.05, 0.05, 0.2), 3, "panel");
		scene.AddObject(panel[3]);
		

		panel[4] = new Panel(vec3(3.75, 16.0, 2.45), vec3(0.05, 0.05, 0.2), 3, "panel");
		scene.AddObject(panel[4]);

		panel[5] = new Panel(vec3(3.75, 13.0, 2.45), vec3(0.05, 0.05, 0.2), 3, "panel");
		scene.AddObject(panel[5]);

		panel[6] = new Panel(vec3(3.75, 10.0, 2.45), vec3(0.05, 0.05, 0.2), 3, "panel");
		scene.AddObject(panel[6]);

		panel[7] = new Panel(vec3(3.75, 7.0, 2.45), vec3(0.05, 0.05, 0.2), 3, "panel");
		scene.AddObject(panel[7]);

		panel[8] = new Panel(vec3(3.75, 4.0, 2.45), vec3(0.05, 0.05, 0.2), 3, "panel");
		scene.AddObject(panel[8]);
		
		panel[9] = new Panel(vec3(-3.75, 8.3, 3.75), vec3(0.05, 0.05, 0.2), 1, "panel");
		scene.AddObject(panel[9]);

		exit = new Panel(vec3(1.25, -2.7, -1.25), vec3(0.05, 0.05, 0.2), 2, "exit");
		scene.AddObject(exit);

		TextureManager::getInstance()->LoadTexture("space", "../Resources/Textures/space2.jpg", GL_NEAREST, GL_NEAREST);
		level.loadLevel[7] = false;
		level.loadedLevel = 8;
	}

	if (level.loadedLevel == 8)
	{
		if (block[10]->clicked)
		{
			panel[0]->isUnlocked *= false;
			panel[1]->isUnlocked *= false;
			panel[2]->isUnlocked *= true;
			panel[3]->isUnlocked *= true;
			block[10]->clicked = false;
		}
		if (block[9]->clicked)
		{
			panel[1]->isUnlocked = !panel[1]->isUnlocked;
			panel[2]->isUnlocked = !panel[2]->isUnlocked;
			panel[3]->isUnlocked = !panel[3]->isUnlocked;
			block[9]->clicked = false;
		}
		if (block[8]->clicked)
		{
			panel[0]->isUnlocked = !panel[0]->isUnlocked;
			panel[3]->isUnlocked = !panel[3]->isUnlocked;
			block[8]->clicked = false;
		}
		if (panel[0]->isUnlocked && panel[1]->isUnlocked && panel[2]->isUnlocked && panel[3]->isUnlocked)
		{
			block[16]->movable = true;
		}


		if (block[2]->clicked)
		{
			panel[4]->isUnlocked = !panel[4]->isUnlocked;
			panel[5]->isUnlocked = !panel[5]->isUnlocked;
			panel[6]->isUnlocked = !panel[6]->isUnlocked;

			block[2]->clicked = false;
		}
		if (block[3]->clicked)
		{
			panel[6]->isUnlocked = !panel[6]->isUnlocked;
			panel[7]->isUnlocked = !panel[7]->isUnlocked;

			block[3]->clicked = false;
		}
		if (block[6]->clicked)
		{
			panel[4]->isUnlocked = !panel[4]->isUnlocked;
			panel[8]->isUnlocked = !panel[8]->isUnlocked;

			block[6]->clicked = false;
		}
		if (block[7]->clicked)
		{
			panel[4]->isUnlocked *= true;
			panel[5]->isUnlocked *= false;
			panel[6]->isUnlocked *= false;
			panel[7]->isUnlocked *= true;
			panel[8]->isUnlocked *= false;

			block[7]->clicked = false;
		}
		if (panel[4]->isUnlocked && panel[5]->isUnlocked && panel[6]->isUnlocked && panel[7]->isUnlocked && panel[8]->isUnlocked)
		{
			block[0]->movable = true;
			block[1]->movable = true;
		}

		if(panel[9]->isUnlocked)
		{
			block[4]->movable = true;
		}
		else
		{
			block[4]->movable = false;
		}

		if (block[5]->isOn)
		{
			exit->isUnlocked = true;
		}

		if (player->pos.y > 40.f && level.byebye[7])
		{
			level.unloadLevel[7] = true;
			level.byebye[7] = false;
		}
	}

	if (level.unloadLevel[7])
	{
		scene.DeleteObject();
		delete exit;

		for (int i = 0; i < 10; i++)
		{
			scene.DeleteObject();
			delete panel[i];
		}

		delete[] panel;

		for (int i = 0; i < level.brickAmount; i++)
		{
			scene.DeleteObject();
			delete block[i];
		}

		level.UnloadLevel();
		level.loadedLevel = 9;

		goodbyeScreen->pos.y -= 45.0f;
		gameEnding = true;
		
		level.unloadLevel[7] = false;
	}

	if (!menuOnOff)
	{
		menu->menuOnOff = 45.0f;

		if (!player->isFalling)
		{
			if (keystate['w']) {
				player->walk = true;
				player->rotate = 135.0f;

				player->speed.x -= 0.05;
				player->speed.z += 0.05;
			}

			if (keystate['s']) {
				player->walk = true;
				player->rotate = -45.0f;

				player->speed.x += 0.05;
				player->speed.z -= 0.05;
			}
			
			if (keystate['a']) {
				player->walk = true;
				player->rotate = 45.0f;

				player->speed.x -= 0.05;
				player->speed.z -= 0.05;
			}

			if (keystate['d']) {
				player->walk = true;
				player->rotate = -135.0f;

				player->speed.x += 0.05f;
				player->speed.z += 0.05f;
			}

			if (!keystate['w'] && !keystate['s'] && !keystate['a'] && !keystate['d'])
			{
				player->walk = false;
			}
			if (keystate['w'] || keystate['s'] || keystate['a'] || keystate['d'])
			{
				player->move = (player->move + 1) % 50 + 1;
			}

			if (keystate['w'] && keystate['a'])
			{
				player->rotate = 90.0f;
				player->speed.x += 0.025f;
			}
			if (keystate['w'] && keystate['d'])
			{
				player->rotate = 180.0f;
				player->speed.z -= 0.025f;
			}
			if (keystate['s'] && keystate['a'])
			{
				player->rotate = 0.0f;
				player->speed.z += 0.025f;
			}
			if (keystate['s'] && keystate['d'])
			{
				player->rotate = -90.0f;
				player->speed.x -= 0.025f;
			}

			if (player->isJumping)
			{
				player->dontJump = true;
				player->walk = false;
				player->speed.y += player->jumpSpeed;
				player->speed.x = player->speed.x*0.85f;
				player->speed.z = player->speed.z*0.85f;
				player->jumpSpeed = player->jumpSpeed - .0075f;
				if (player->jumpSpeed < 0.0f)
				{
					player->jumpSpeed = 0.4f;
					player->isJumping = false;
				}
			}
		}
	}
	if (menuOnOff)
	{
		menu->menuOnOff = 0.0f;
		player->speed.y += 0.2f;
	}

	scene.Update();
	menu->Update();
	background->Update();
	whichLevel->Update();

	glutTimerFunc(17, OnTimer, 0);
}

void CreateGame::Create()
{
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(1200, 675);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

	glutCreateWindow("ASTROSOLVER");
	
	PlaySound(GameplayTheme, NULL, SND_ASYNC | SND_FILENAME | SND_LOOP);

	menu = new Menu("menu");

	goodbyeScreen = new Background("goodbye");
	goodbyeScreen->diffuse = vec3(1.0f, 1.0f, 1.0f);
	goodbyeScreen->pos = vec3(5.5, 64.0f, -5.5);
	goodbyeScreen->width = 7.5;
	goodbyeScreen->depth = 7.5;
	goodbyeScreen->height = 22.5;

	background = new Background("bg1");
	background->diffuse = vec3(1.0f, 1.0f, 1.0f);

	whichLevel = new Background("level1");
	whichLevel->diffuse = vec3(1.0f, 1.0f, 1.0f);
	whichLevel->pos = vec3(-5.2, 23.0f, -6.2);
	whichLevel->width = 1.0;
	whichLevel->depth = 1.0;
	whichLevel->height = 1.0;

	player = new Player(vec3(0.0f,30.0f, 0.0f), vec3(0.2, 0.7, 0.9), "player");
	player->ambient = vec3(0.1, 0.1, 0.0);
	player->load(0, "../Resources/Models/astronaut.obj");
	string f1;
	string f2;
	string f3;
	f1 = "../Resources/Models/walk/walking";
	f3 = ".obj";
	for (int i = 12; i < 63; i++)
	{
		f2 = to_string(i);
		player->load(i-11, f1+f2+f3);
	}
	player->textureName = "astro";
	player->modelScale = vec3(0.05, 0.15, 0.05);
	player->width = player->width * 0.05 * 0.50;
	player->height = player->height * 0.15;
	player->depth = player->depth * 0.05 * 0.5;
	player->radius = player->width * 0.5f * sqrt(2);
	scene.AddObject(player);

	glutDisplayFunc(OnRender);
	glutReshapeFunc(OnReshape);
	glutKeyboardFunc(OnKeyPress);
	glutKeyboardUpFunc(OnKeyUp);
	glutTimerFunc(17, OnTimer, 0);

	glClearColor(0.1f, 0.0f, 0.3f, 0.0);

	glEnable(GL_DEPTH_TEST);

	glEnable(GL_LIGHTING);
	glShadeModel(GL_SMOOTH);

	TextureManager::getInstance()->LoadTexture("menu", "../Resources/Textures/astromenu1.jpg", GL_NEAREST, GL_NEAREST);
	TextureManager::getInstance()->LoadTexture("controls", "../Resources/Textures/controlz.jpg", GL_NEAREST, GL_NEAREST);

	TextureManager::getInstance()->LoadTexture("level1", "../Resources/Textures/level1.jpg", GL_NEAREST, GL_NEAREST);
	TextureManager::getInstance()->LoadTexture("level2", "../Resources/Textures/level2.jpg", GL_NEAREST, GL_NEAREST);
	TextureManager::getInstance()->LoadTexture("level3", "../Resources/Textures/level3.jpg", GL_NEAREST, GL_NEAREST);
	TextureManager::getInstance()->LoadTexture("level4", "../Resources/Textures/level4.jpg", GL_NEAREST, GL_NEAREST);
	TextureManager::getInstance()->LoadTexture("level5", "../Resources/Textures/level5.jpg", GL_NEAREST, GL_NEAREST);
	TextureManager::getInstance()->LoadTexture("level6", "../Resources/Textures/level6.jpg", GL_NEAREST, GL_NEAREST);
	TextureManager::getInstance()->LoadTexture("level7", "../Resources/Textures/level7.jpg", GL_NEAREST, GL_NEAREST);
	TextureManager::getInstance()->LoadTexture("level8", "../Resources/Textures/level8.jpg", GL_NEAREST, GL_NEAREST);

	TextureManager::getInstance()->LoadTexture("bg1", "../Resources/Textures/bg1.jpg", GL_NEAREST, GL_NEAREST);
	TextureManager::getInstance()->LoadTexture("bg2", "../Resources/Textures/bg2.jpg", GL_NEAREST, GL_NEAREST);
	TextureManager::getInstance()->LoadTexture("bg3", "../Resources/Textures/bg3.jpg", GL_NEAREST, GL_NEAREST);
	TextureManager::getInstance()->LoadTexture("bg4", "../Resources/Textures/bg4.jpg", GL_NEAREST, GL_NEAREST);

	TextureManager::getInstance()->LoadTexture("panel", "../Resources/Textures/panel.jpg", GL_NEAREST, GL_NEAREST);
	TextureManager::getInstance()->LoadTexture("exit", "../Resources/Textures/exit.jpg", GL_NEAREST, GL_NEAREST);
	TextureManager::getInstance()->LoadTexture("astro", "../Resources/Textures/astro.jpeg", GL_NEAREST, GL_NEAREST);	

	TextureManager::getInstance()->LoadTexture("tex41", "../Resources/Textures/Tex4/TexMain.jpg", GL_NEAREST, GL_NEAREST);
	TextureManager::getInstance()->LoadTexture("tex42", "../Resources/Textures/Tex4/TexHalf1.jpg", GL_NEAREST, GL_NEAREST);
	TextureManager::getInstance()->LoadTexture("tex44", "../Resources/Textures/Tex4/TexFourth1.jpg", GL_NEAREST, GL_NEAREST);
	TextureManager::getInstance()->LoadTexture("tex48", "../Resources/Textures/Tex4/TexEight1.jpg", GL_NEAREST, GL_NEAREST);
	TextureManager::getInstance()->LoadTexture("tex410", "../Resources/Textures/Tex4/TexTenth1.jpg", GL_NEAREST, GL_NEAREST);

	TextureManager::getInstance()->LoadTexture("tex31", "../Resources/Textures/Tex3/TexMain.jpg", GL_NEAREST, GL_NEAREST);
	TextureManager::getInstance()->LoadTexture("tex33", "../Resources/Textures/Tex3/TexThird1.jpg", GL_NEAREST, GL_NEAREST);
	TextureManager::getInstance()->LoadTexture("tex39", "../Resources/Textures/Tex3/TexNinth1.jpg", GL_NEAREST, GL_NEAREST);

	TextureManager::getInstance()->LoadTexture("goodbye", "../Resources/Textures/end.jpg", GL_NEAREST, GL_NEAREST);
}


CreateGame::CreateGame()
{
}


CreateGame::~CreateGame()
{
}