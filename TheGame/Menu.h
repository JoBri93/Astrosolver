#pragma once
class Menu:public SceneObject
{
public:
	std::string textureName;

	float menuOnOff;
	vec3 pointerPos;
	unsigned int whichPos;

	void Render();
	void Update();

	Menu(string);
	~Menu();
};

