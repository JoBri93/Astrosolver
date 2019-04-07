#include "stdafx.h"
#include "Panel.h"


Panel::Panel(vec3 pos, vec3 amb, int type, string textureName)
{
	this->panelType = type;

	this->pos = pos;
	this->ambient = amb;
	this->textureName = textureName;

	isUnlocked = false;
	unlocked = 0;

	if (type == 1 || type == 2)
	{
		width = 1.0f;
		height = 0.0f;
		depth = 1.0f;
	}

	if (type == 3)
	{
		width = 1.0f;
		height = 1.0f;
		depth = 0.0f;
	}

	if (type == 4)
	{
		width = 0.0f;
		height = 1.0f;
		depth = 1.0f;
	}
	

	boundaryMax = pos + vec3(width * 0.5f, height * 0.5f, depth * 0.5f);
	boundaryMin = pos - vec3(width * 0.5f, height * 0.5f, depth * 0.5f);
	
	pushable = false;
}

void Panel::Render()
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

		glTranslatef(pos.x, pos.y, pos.z);

		if(panelType == 1 || panelType == 2)
		{
			glBegin(GL_QUADS);

			glNormal3f(0.0f, 1.0f, 0.0f);
			glTexCoord2f(0, 1);
			glVertex3f(-width * 0.5f, 0, -depth * 0.5f);
			glTexCoord2f(0, 0);
			glVertex3f(-width * 0.5f, 0, depth *0.5f);
			glTexCoord2f(1, 0);
			glVertex3f(width *0.5f, 0, depth *0.5f);
			glTexCoord2f(1, 1);
			glVertex3f(width *0.5f, 0, -depth * 0.5f);

			glEnd();
		}
		if (panelType == 3 || panelType == 4)
		{
			glBegin(GL_QUADS);

			glNormal3f(0.0f, 1.0f, 0.0f);
			glTexCoord2f(0, 1);
			glVertex3f(-width * 0.5f, -height*1.5, depth * 0.5f);
			glTexCoord2f(0, 0);
			glVertex3f(-width * 0.5f, height*1.5, depth * 0.5f);
			glTexCoord2f(1, 0);
			glVertex3f(width *0.5f, height*1.5, -depth * 0.5f);
			glTexCoord2f(1, 1);
			glVertex3f(width *0.5f, -height*1.5, -depth * 0.5f);

			glEnd();
		}

	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
}

void Panel::Update()
{
	unlocked = 0;
	if (isUnlocked)
	{
		diffuse = vec3(0, 1, 0);
	}
	else
	{
		diffuse = vec3(1, 0, 0);
	}
}

Panel::~Panel()
{
}
