#pragma once
class Panel : public SceneObject
{
public:
	string textureName;

	void Render();
	void Update();

	Panel(vec3, vec3, int, string);
	~Panel();
};

