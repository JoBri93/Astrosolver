#pragma once
class Crystal : public SceneObject
{
public:

	void Render();
	void Update();

	Crystal(vec3,vec3,float,float,float,bool);
	~Crystal();
};

