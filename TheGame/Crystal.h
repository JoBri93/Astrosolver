#pragma once
class Crystal : public SceneObject
{
public:
	string textureName;
	bool movable;
	float speedSum;
	float movableHeight;
	bool upDown;
	float rotate;
	bool clicked;

	void Render();
	void Update();

	Crystal(vec3,vec3,vec3,float,float,float,bool,bool,int,string);
	~Crystal();
};

