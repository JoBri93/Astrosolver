#pragma once
class Player : public SceneObject
{
public:
	vec3 modelTranslation;
	vec3 modelScale;
	
	std::string textureName;

	bool hasNormals;
	bool hasTexCoords;

	GLuint displayListID;
	
	std::vector<std::vector<vec3>> modelVertices;
	std::vector<std::vector<vec3>> modelNormals;
	std::vector<std::vector<vec3>> modelUvs;

	float jumpSpeed;
	int move;
	bool walk;
	float rotate;

	bool load(int displayList, std::string filepath);
	void Render();
	void Update();

	Player(vec3,vec3,std::string);
	~Player();
};

