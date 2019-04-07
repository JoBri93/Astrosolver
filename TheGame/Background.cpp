#include "stdafx.h"
#include "Background.h"


Background::Background(std::string textureName)
{
	this->textureName = textureName;
	pos.x = -6.0f;
	pos.y = -12.5f;
	pos.z = 6.0f;

	width = 8.0f;
	depth = 8.0f;
	height = 22.0f;
}

void Background::Render()
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
		{
			float ambient[] = { 1.0f, 1.0f, 1.0f };
			float diffuse[] = { 1.0f, 1.0f, 1.0f };
			float specular[] = { 1.0f, 1.0f, 1.0f };

			glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
			glMaterialfv(GL_FRONT, GL_SPECULAR, specular);

			glTexCoord2f(0, 0);
			glVertex3f(-width, -height, -depth);
			glTexCoord2f(0, 1);
			glVertex3f(-width, height, -depth);
			glTexCoord2f(1, 1);
			glVertex3f(width, height, depth);
			glTexCoord2f(1, 0);
			glVertex3f(width, -height, depth);
		}
		glEnd();
		
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
}

void Background::Update()
{
}

Background::~Background()
{
}