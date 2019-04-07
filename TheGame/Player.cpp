#include "stdafx.h"
#include "Player.h"

Player::Player(vec3 position, vec3 color, std::string textureName)
{
	this->pos = position;
	this->diffuse = color;
	this->textureName = textureName;

	this->ambient = vec3(0.05, 0.05, 0.2);

	width = 0.5f;
	height = 3.0f;
	depth = 0.5f;

	boundaryMax = pos + vec3(width * 0.5f, height * 0.5f, depth * 0.5f);
	boundaryMin = pos - vec3(width * 0.5f, height * 0.5f, depth * 0.5f);
	
	radius = width * 0.5f * sqrt(2);

	rotate = 0.0f;

	speed.x = 0.0f;
	speed.y = 0.0f;
	speed.z = 0.0f;

	jumpSpeed = 0.4f;

	pushable = true;
	isFalling = true;

	isJumping = false;
	dontJump = false;
	move = 0;

	exit = false;
	activPanel = false;
	isUnlocked = false;

	displayListID = glGenLists(51);
}


Player::~Player()
{
}

bool Player::load(int displayList, std::string filename)
{
	struct SFace {
		int v[3];
		int n[3];
		int uv[3];
	};

	FILE * fp = fopen(filename.c_str(), "r");

	if (fp == NULL) {
		printf("Nie wczytano pliku %s\n", filename.c_str());
		return false;
	}

	std::vector<vec3> loaded_vertices;
	std::vector<vec3> loaded_normals;
	std::vector<vec3> loaded_uvs;
	std::vector<SFace> loaded_faces;

	char buf[256];

	while (fgets(buf, 256, fp)) {
		if (buf[0] == 'v' && buf[1] == ' ') {
			vec3 vertex;
			sscanf(buf, "v %f %f %f", &vertex.x, &vertex.y, &vertex.z);
			loaded_vertices.push_back(vertex);
		}
		if (buf[0] == 'v' && buf[1] == 'n') {
			vec3 normal;
			sscanf(buf, "vn %f %f %f", &normal.x, &normal.y, &normal.z);
			loaded_normals.push_back(normal);
			hasNormals = true;
		}
		if (buf[0] == 'v' && buf[1] == 't') {
			vec3 vertex;
			sscanf(buf, "vt %f %f %f", &vertex.x, &vertex.y, &vertex.z);
			loaded_uvs.push_back(vertex);
			hasTexCoords = true;
		}
		if (buf[0] == 'f' && buf[1] == ' ') {
			if (!hasNormals && !hasTexCoords)
			{
				SFace face;
				sscanf(buf, "f %d %d %d",
					&face.v[0],
					&face.v[1],
					&face.v[2]);
				loaded_faces.push_back(face);
			}
			if (hasNormals && !hasTexCoords)
			{
				SFace face;
				sscanf(buf, "f %d//%d %d//%d %d//%d",
					&face.v[0], &face.n[0],
					&face.v[1], &face.n[1],
					&face.v[2], &face.n[2]);
				loaded_faces.push_back(face);
			}
			else if (hasNormals && hasTexCoords)
			{
				SFace face;
				sscanf(buf, "f %d/%d/%d %d/%d/%d %d/%d/%d",
					&face.v[0], &face.uv[0], &face.n[0],
					&face.v[1], &face.uv[1], &face.n[1],
					&face.v[2], &face.uv[2], &face.n[2]);
				loaded_faces.push_back(face);
			}
		}
	}

	fclose(fp);

	vec3 minVertex = loaded_vertices[0];
	vec3 maxVertex = loaded_vertices[1];
	
	std::vector<vec3> vertices;
	std::vector<vec3> normals;
	std::vector<vec3> uvs;

	for (int i = 0; i < loaded_faces.size(); ++i) {
		for (int j = 0; j < 3; ++j) {

			int idxV = loaded_faces[i].v[j] - 1;
			vertices.push_back(loaded_vertices[idxV]);

			if (hasNormals)
			{
				int idxN = loaded_faces[i].n[j] - 1;
				normals.push_back(loaded_normals[idxN]);
			}

			if (hasTexCoords)
			{
				int idxUV = loaded_faces[i].uv[j] - 1;
				uvs.push_back(loaded_uvs[idxUV]);
			}

			if (loaded_vertices[idxV].x < minVertex.x)
				minVertex.x = loaded_vertices[idxV].x;

			if (loaded_vertices[idxV].x > maxVertex.x)
				maxVertex.x = loaded_vertices[idxV].x;


			if (loaded_vertices[idxV].y < minVertex.y)
				minVertex.y = loaded_vertices[idxV].y;

			if (loaded_vertices[idxV].y > maxVertex.y)
				maxVertex.y = loaded_vertices[idxV].y;


			if (loaded_vertices[idxV].z < minVertex.z)
				minVertex.z = loaded_vertices[idxV].z;

			if (loaded_vertices[idxV].z > maxVertex.z)
				maxVertex.z = loaded_vertices[idxV].z;

		}
	}

	height = maxVertex.y-minVertex.y;
	
	if (maxVertex.x - minVertex.x > maxVertex.z - minVertex.z)
	{
		width = maxVertex.x - minVertex.x;
		depth = maxVertex.x - minVertex.x;
	}
	else
	{
		width = maxVertex.z - minVertex.z;
		depth = maxVertex.z - minVertex.z;
	}

	modelNormals.push_back(normals);
	modelUvs.push_back(uvs);
	modelVertices.push_back(vertices);

	glNewList(displayListID + displayList, GL_COMPILE);

	glBegin(GL_TRIANGLES);

	for (int i = 0; i < modelVertices[displayList].size(); i++)
	{
		if (hasNormals)
			glNormal3f((modelNormals[displayList])[i].x, (modelNormals[displayList])[i].y, (modelNormals[displayList])[i].z);
		if (hasTexCoords)
			glTexCoord2f((modelUvs[displayList])[i].x, (modelUvs[displayList])[i].y);
		glVertex3f((modelVertices[displayList])[i].x, (modelVertices[displayList])[i].y, (modelVertices[displayList])[i].z);
	}

	glEnd();

	glEndList();

	return true;
}

void Player::Render()
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

		glTranslatef(pos.x, pos.y-0.4f, pos.z);
		glScalef(modelScale.x, modelScale.y, modelScale.z);
		glRotatef(rotate, 0.0f, 1.0f, 0.0f);
		glCallList(displayListID+move);

		

	glPopMatrix();
	
	glDisable(GL_TEXTURE_2D);

}

void Player::Update()
{
	pos.x += speed.x;
	pos.y += speed.y;
	pos.z += speed.z;

	boundaryMax = pos + vec3(width * 0.5f, height * 0.5f, depth * 0.5f);
	boundaryMin = pos - vec3(width * 0.5f, height * 0.5f, depth * 0.5f);

	speed.x = 0.0f;
	speed.y = -.2f;
	speed.z = 0.0f;

	if (!walk) move = 0;
}
