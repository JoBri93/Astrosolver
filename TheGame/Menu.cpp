#include "stdafx.h"
#include "Menu.h"

Menu::Menu(string textureName)
{
	this->textureName = textureName;
	pos.x = 6.0f;
	pos.y = 19.0f;
	pos.z = -6.0f;

	pointerPos = vec3(5.2, 0.0, 5.7);
	whichPos = 2;

	diffuse = vec3(1.0f, 1.0f, 1.0f);
	ambient = vec3(1.0f, 1.0f, 1.0f);
	specular = vec3(1.0f, 1.0f, 1.0f);

	menuOnOff = 0.0f;
}

void Menu::Render()
{
	if (!textureName.empty())
	{
		glEnable(GL_TEXTURE_2D);
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		TextureManager::getInstance()->BindTexture(textureName);
	}

	glMaterialfv(GL_FRONT, GL_AMBIENT, &ambient.x);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, &diffuse.x);
	glMaterialfv(GL_FRONT, GL_SPECULAR, &specular.x);

	glPushMatrix();

	glTranslatef(pos.x, pos.y+menuOnOff, pos.z);

	glBegin(GL_QUADS);
	{
		glTexCoord2f(0, 0);
		glVertex3f(-7.5f, -22.0f, -7.5f);
		glTexCoord2f(0, 1);
		glVertex3f(-7.5f, 22.0f, -7.5f);
		glTexCoord2f(1, 1);
		glVertex3f(7.5f, 22.0f, 7.5f);
		glTexCoord2f(1, 0);
		glVertex3f(7.5f, -22.0f, 7.5f);
	}
	glEnd();

	glPopMatrix();
	
	glDisable(GL_TEXTURE_2D);

	glPushMatrix();

	glTranslatef(pos.x-pointerPos.x, pos.y-pointerPos.y + menuOnOff, pos.z-pointerPos.z);

	glBegin(GL_QUADS);
	{
		glVertex3f(-0.2f, -1.0f, -0.2f);
		glVertex3f(-0.2f, 1.0f, -0.2f);
		glVertex3f(0.2f, 1.0f, 0.2f);
		glVertex3f(0.2f, -1.0f, 0.2f);
	}
	glEnd();

	glPopMatrix();

}

void Menu::Update()
{
	if (whichPos == 0) pointerPos.y = 15.25;
	if (whichPos == 1) pointerPos.y = 11.5;
	if (whichPos == 2) pointerPos.y = 7.75;
}


Menu::~Menu()
{
}
