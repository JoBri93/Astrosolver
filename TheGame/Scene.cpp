#include "stdafx.h"
#include "Scene.h"


Scene::Scene()
{
	playerIsLeaving = false;
}


Scene::~Scene()
{
}

void Scene::AddObject(SceneObject* object)
{
	sceneObjects.push_back(object);
}

void Scene::DeleteObject()
{
	sceneObjects.pop_back();
}

void Scene::Render()
{
	for (unsigned int i = 0; i < sceneObjects.size(); i++)
		sceneObjects[i]->Render();
}

void Scene::Update()
{	
	SceneObject* player = sceneObjects[0];

	//kolizja z przyciskiem
	for (int i = 1; i < sceneObjects.size(); i++)
	{
		SceneObject* obj = sceneObjects[i];

		if (obj->button != 0)
		{
			float r = vec3::distance(player->pos, obj->buttonPos);
			float d = (player->radius + obj->radius) - r;

			if (d > 0)
			{	
				obj->buttonArea = true;
			}
			else
			{
				obj->buttonArea = false;
			}
		}
	}

	//kolizja z wyjœciem
	SceneObject *exit = sceneObjects[sceneObjects.size() - 1];

	if (exit->panelType == 2)
	{
		if (exit->isUnlocked)
		{
			if (player->pos.x < exit->pos.x + exit->width*0.4 && player->pos.x > exit->pos.x - exit->width*0.4 && player->pos.z < exit->pos.z + exit->depth*0.4 && player->pos.z > exit->pos.z - exit->depth*0.4f)
			{
				player->speed.y += 0.5f;
				player->pos.x = exit->pos.x;
				player->pos.z = exit->pos.z;
				playerIsLeaving = true;
			}
			else
			{
				playerIsLeaving = false;
			}
		}
	}

	//kolizja z panelem
	for (int i = 0; i < sceneObjects.size(); i++)
	{
		SceneObject* obj1 = sceneObjects[i];
		for (int j = i + 1; j < sceneObjects.size(); j++)
		{		
			SceneObject* obj2 = sceneObjects[j];

			if (obj2->panelType == 1 && obj1->pushable)
			{
				if (obj1->pos.x < obj2->pos.x + obj2->width*0.4 && obj1->pos.x > obj2->pos.x - obj2->width*0.4 && obj1->pos.z < obj2->pos.z + obj2->depth*0.4 && obj1->pos.z > obj2->pos.z - obj2->depth*0.4f && obj1->boundaryMin.y < obj2->pos.y + 2.0f)
				{
					obj2->unlocked++;
				}
			}
		}
	}
	
	for (int i = 0; i < sceneObjects.size(); i++)
	{
		SceneObject* panel = sceneObjects[i];

		if (panel->panelType == 1)
		{
			if (panel->unlocked > 0) panel->isUnlocked = true;
			else panel->isUnlocked = false;
		}
	}

	//kolizja obiektów
	for (int i = 0; i < sceneObjects.size(); i++)
	{
		for (int j = i + 1; j < sceneObjects.size(); j++)
		{
			SceneObject* obj1 = sceneObjects[i];
			SceneObject* obj2 = sceneObjects[j];

			if (obj1->panelType != 4 && obj1->panelType != 3 && obj2->panelType != 4 && obj2->panelType != 3)
			{
				//wykrywanie kolizji
				if (obj1->boundaryMax.z > obj2->boundaryMin.z && obj1->boundaryMax.x > obj2->boundaryMin.x
					&& obj1->boundaryMin.x < obj2->boundaryMax.x && obj1->boundaryMin.z < obj2->boundaryMax.z
					&& obj1->boundaryMax.y > obj2->boundaryMin.y && obj1->boundaryMin.y < obj2->boundaryMax.y)
				{
					if (obj1->boundaryMin.y < obj2->boundaryMax.y - 0.5f)
					{
						if (obj1->pos.z < (obj2->depth / obj2->width)*obj1->pos.x + (obj2->pos.z / (obj2->depth / obj2->width) - obj2->pos.x))
						{
							if (obj1->pos.x + obj1->pos.z > obj2->pos.x + obj2->pos.z)
							{
								if (obj1->pushable)
								{
									obj1->pos.x = obj2->boundaryMax.x + obj1->width * 0.5f;
								}
								if (obj2->pushable)
								{
									obj2->pos.x = obj1->boundaryMin.x - obj2->width * 0.5f;
								}
							}
							else
							{
								if (obj1->pushable)
								{
									obj1->pos.z = obj2->boundaryMin.z - obj1->depth * 0.5f;
								}
								if (obj2->pushable)
								{
									obj2->pos.z = obj1->boundaryMax.z + obj2->depth * 0.5f;
								}
							}
						}
						else
						{
							if (obj1->pos.x + obj1->pos.z < obj2->pos.x + obj2->pos.z)
							{
								if (obj1->pushable)
								{
									obj1->pos.x = obj2->boundaryMin.x - obj1->width * 0.5f;
								}
								if (obj2->pushable)
								{
									obj2->pos.x = obj1->boundaryMax.x + obj2->width * 0.5f;
								}
							}
							else
							{
								if (obj1->pushable)
								{
									obj1->pos.z = obj2->boundaryMax.z + obj1->depth * 0.5f;
								}
								if (obj2->pushable)
								{
									obj2->pos.z = obj1->boundaryMin.z - obj2->depth * 0.5f;
								}
							}
						}
					}
					else
					{

						if (obj1->pushable) obj1->isFalling = false;
						if (obj2->pushable) obj2->isFalling = false;

						obj1->dontJump = false;
						obj1->pos.y = obj2->boundaryMax.y + obj1->height*0.5f;
					}
				}
			}
		}
	}

	for (unsigned int i = 0; i < sceneObjects.size(); i++)
		sceneObjects[i]->Update();
}
