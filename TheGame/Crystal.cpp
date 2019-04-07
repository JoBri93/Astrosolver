#include "stdafx.h"
#include "Crystal.h"

Crystal::Crystal(vec3 position, vec3 diff, vec3 amb, float w, float h, float d, bool ifPushable, bool ifMovable, int ifButton, string textureName)
{
	this->pos = position;
	this->diffuse = diff;
	this->ambient = amb;
	this->width = w;
	this->height = h;
	this->depth = d;
	this->pushable = ifPushable;
	this->movable = ifMovable;
	this->button = ifButton;
	this->textureName = textureName;

	isFalling = true;

	movableHeight = 5.0f;

	upDown = false;
	speedSum = 0.0;
	
	boundaryMax = pos + vec3(width * 0.5f, height * 0.5f, depth * 0.5f);
	boundaryMin = pos - vec3(width * 0.5f, height * 0.5f, depth * 0.5f);

	speed.x = 0.0f;
	speed.y = 0.0f;
	speed.z = 0.0f;

	exit = false;
	activPanel = false;
	isUnlocked = false;

	radius = 0.3f;

	if (button != 0)
	{
		buttonArea = false;
		isOn = false;
		clicked = false;

		if (button == 1)
		{
			rotate = 0.0f;
			buttonPos = vec3(pos.x + width * 0.5f, pos.y - height * 0.5 + 2.0f, pos.z);
		}
		else if (button == 2)
		{
			rotate = 90.0f;
			buttonPos = vec3(pos.x, pos.y - height * 0.5 + 2.0f, pos.z - depth * 0.5f);
		}
	}
}


Crystal::~Crystal()
{
}

void Crystal::Render()
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
		
		glBegin(GL_QUADS);

			glNormal3f(0.0f, -1.0f, 0.0f);
			glTexCoord2f(0, 1);
			glVertex3f(width *0.5f, -height * 0.5f, -depth * 0.5f);
			glTexCoord2f(0, 0.5);
			glVertex3f(width *0.5f, -height * 0.5f, depth *0.5f);
			glTexCoord2f(1, 0.5);
			glVertex3f(-width * 0.5f, -height * 0.5f, depth *0.5f);
			glTexCoord2f(1, 1);
			glVertex3f(-width * 0.5f, -height * 0.5f, -depth * 0.5f);

			glNormal3f(0.0f, 1.0f, 0.0f);
			glTexCoord2f(0.5, 1);
			glVertex3f(-width * 0.5f, height *0.5f, -depth * 0.5f);
			glTexCoord2f(0.5, 0.5);
			glVertex3f(-width * 0.5f, height *0.5f, depth *0.5f);
			glTexCoord2f(1, 0.5);
			glVertex3f(width *0.5f, height *0.5f, depth *0.5f);
			glTexCoord2f(1, 1);
			glVertex3f(width *0.5f, height *0.5f, -depth * 0.5f);

			glNormal3f(-1.0f, 0.0f, 0.0f);
			glTexCoord2f(0, 0.5);
			glVertex3f(-width * 0.5f, -height * 0.5f, -depth * 0.5f);
			glTexCoord2f(0.5, 0.5);
			glVertex3f(-width * 0.5f, -height * 0.5f, depth *0.5f);
			glTexCoord2f(0.5, 1);
			glVertex3f(-width * 0.5f, height *0.5f, depth *0.5f);
			glTexCoord2f(0, 1);
			glVertex3f(-width * 0.5f, height *0.5f, -depth * 0.5f);

			glNormal3f(1.0f, 0.0f, 0.0f);
			glTexCoord2f(0.5, 1);
			glVertex3f(width *0.5f, height *0.5f, -depth * 0.5f);
			glTexCoord2f(0, 1);
			glVertex3f(width *0.5f, height *0.5f, depth *0.5f);
			glTexCoord2f(0, 0.5);
			glVertex3f(width *0.5f, -height * 0.5f, depth *0.5f);
			glTexCoord2f(0.5, 0.5);
			glVertex3f(width *0.5f, -height * 0.5f, -depth * 0.5f);

			glNormal3f(0.0f, 0.0f, -1.0f);
			glTexCoord2f(0.5, 1);
			glVertex3f(-width * 0.5f, height *0.5f, -depth * 0.5f);
			glTexCoord2f(0, 1);
			glVertex3f(width *0.5f, height *0.5f, -depth * 0.5f);
			glTexCoord2f(0, 0.5);
			glVertex3f(width *0.5f, -height * 0.5f, -depth * 0.5f);
			glTexCoord2f(0.5, 0.5);
			glVertex3f(-width * 0.5f, -height * 0.5f, -depth * 0.5f);

			glNormal3f(0.0f, 0.0f, 1.0f);
			glTexCoord2f(0.5, 1);
			glVertex3f(width *0.5f, height *0.5f, depth *0.5f);
			glTexCoord2f(0, 1);
			glVertex3f(-width * 0.5f, height *0.5f, depth *0.5f);
			glTexCoord2f(0, 0.5);
			glVertex3f(-width * 0.5f, -height * 0.5f, depth *0.5f);
			glTexCoord2f(0.5, 0.5);
			glVertex3f(width *0.5f, -height * 0.5f, depth *0.5f);
			
			glEnd();
	
		glPopMatrix();

		if (button)
		{
			glPushMatrix();

			glTranslatef(buttonPos.x, buttonPos.y, buttonPos.z);
			glRotatef(rotate, 0.0f, 1.0f, 0.0f);
			
			glBegin(GL_QUADS);

			glNormal3f(0.0f, -1.0f, 0.0f);
			glTexCoord2f(0, 1);
			glVertex3f(0.125f, -1.0, -0.25f);
			glTexCoord2f(0.5, 0);
			glVertex3f(0.125f, -1.0, 0.25f);
			glTexCoord2f(0.5, 0.5);
			glVertex3f(-0.125f, -1.0, 0.25f);
			glTexCoord2f(1, 0.5);
			glVertex3f(-0.125f, -1.0, -0.25f);

			glNormal3f(0.0f, 1.0f, 0.0f);
			glTexCoord2f(0.5, 0.5);
			glVertex3f(-0.125f, 1.0, -0.25f);
			glTexCoord2f(0.5, 0);
			glVertex3f(-0.125f, 1.0, 0.25f);
			glTexCoord2f(1, 0);
			glVertex3f(0.125f, 1.0, 0.25f);
			glTexCoord2f(1, 0.5);
			glVertex3f(0.125f, 1.0, -0.25f);

			glNormal3f(-1.0f, 0.0f, 0.0f);
			glTexCoord2f(0.5, 0);
			glVertex3f(-0.125f, -1.0, -0.25f);
			glTexCoord2f(1, 0);
			glVertex3f(-0.125f, -1.0, 0.25f);
			glTexCoord2f(1, 0.5);
			glVertex3f(-0.125f, 1.0, 0.25f);
			glTexCoord2f(0.5, 0.5);
			glVertex3f(-0.125f, 1.0, -0.25f);

			glNormal3f(1.0f, 0.0f, 0.0f);
			glTexCoord2f(0.5, 0.5);
			glVertex3f(0.125f, 1.0, -0.25f);
			glTexCoord2f(0, 0.5);
			glVertex3f(0.125f, 1.0, 0.25f);
			glTexCoord2f(0, 0);
			glVertex3f(0.125f, -1.0, 0.25f);
			glTexCoord2f(0.5, 0);
			glVertex3f(0.125f, -1.0, -0.25f);

			glNormal3f(0.0f, 0.0f, -1.0f);
			glTexCoord2f(1, 0.5);
			glVertex3f(-0.125f, 1.0, -0.25f);
			glTexCoord2f(0.5, 0.5);
			glVertex3f(0.125f, 1.0, -0.25f);
			glTexCoord2f(0.5, 0);
			glVertex3f(0.125f, -1.0, -0.25f);
			glTexCoord2f(1, 0);
			glVertex3f(-0.125f, -1.0, -0.25f);

			glNormal3f(0.0f, 0.0f, 1.0f);
			glTexCoord2f(0.5, 0.5);
			glVertex3f(0.125f, 1.0, 0.25f);
			glTexCoord2f(0.5, 0);
			glVertex3f(-0.125f, 1.0, 0.25f);
			glTexCoord2f(1, 0);
			glVertex3f(-0.125f, -1.0, 0.25f);
			glTexCoord2f(1, 0.5);
			glVertex3f(0.125f, -1.0, 0.25f);

			glEnd();

			glPopMatrix();

			glDisable(GL_TEXTURE_2D);

			
		}
}

void Crystal::Update()
{
	if (movable)
	{
		boundaryMax = pos + vec3(width * 0.5f, height * 0.5f, depth * 0.5f);
		boundaryMin = pos - vec3(width * 0.5f, height * 0.5f, depth * 0.5f);

		speedSum += speed.y;
		pos.y += speed.y;
		if (speedSum < 0.0f)
			upDown = true;
		if (speedSum > movableHeight)
			upDown = false;

		if(upDown)
			speed.y = .1f;
		else
			speed.y = -.1f;
	}
	if (pushable)
	{
		pos.x += speed.x;
		pos.y += speed.y;
		pos.z += speed.z;

		boundaryMax = pos + vec3(width * 0.5f, height * 0.5f, depth * 0.5f);
		boundaryMin = pos - vec3(width * 0.5f, height * 0.5f, depth * 0.5f);
		
		speed.x = 0.0f;
		speed.y = -.2f;
		speed.z = 0.0f;
	}
	if (button != 0)
	{
		if (buttonArea)
		{
			if (button == 1)
			{
				if (isOn)	buttonPos.x = pos.x + width * 0.5f - 0.1f;
				else buttonPos.x = pos.x + width * 0.5f;
			}
			else if (button == 2)
			{
				if (isOn)	buttonPos.z = pos.z - depth * 0.5 + 0.1f;
				else buttonPos.z = pos.z - depth * 0.5f;
			}
		}
	}
}