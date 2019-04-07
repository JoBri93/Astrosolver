#pragma once
class Level
{
public:
	bool loadLevel[8];
	int loadedLevel;
	bool unloadLevel[8];
	bool byebye[8];
	bool reloadLevel[8];

	int brickAmount;
	vec3 *pos;
	vec3 *diff;
	vec3 *amb;
	vec3 *size;
	bool *pushable;
	bool *movable;
	int *button;
	string *texID;

	void LoadLevel(int);
	void UnloadLevel();

	Level();
	~Level();
};

