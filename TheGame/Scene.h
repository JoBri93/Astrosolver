#pragma once
class Scene
{
public:
	bool playerIsLeaving;

	Scene();
	~Scene();

	void Render();
	void Update();

	void AddObject(SceneObject* object);
	void DeleteObject();

private:
	vector<SceneObject*> sceneObjects;
};

