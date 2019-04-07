#pragma once
class Background : public SceneObject
{
public:
	std::string textureName;

	void Render();
	void Update();

	Background(std::string);
	~Background();
};

