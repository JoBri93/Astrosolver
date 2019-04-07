#pragma once

class SceneObject
{
public:
	vec3 pos;
	vec3 speed;
	
	float width;
	float depth;
	float height;

	vec3 boundaryMax;
	vec3 boundaryMin;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	bool pushable;
	bool isJumping;
	bool dontJump;

	bool isFalling;

	int button;
	bool buttonArea;
	bool isOn;
	float radius;
	vec3 buttonPos;

	int panelType; //0 - no panel, 1 - floor panel, 2 - exit, 3 - wall panel
	bool exit;
	bool activPanel;
	bool isUnlocked;
	int unlocked;

	virtual void Render() = 0;
	virtual void Update() = 0;

	SceneObject();
	~SceneObject();
};

