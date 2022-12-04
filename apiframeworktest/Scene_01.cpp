#include "pch.h"
#include "Scene_01.h"
#include "KeyMgr.h"
Scene_01::Scene_01()
{
}

Scene_01::~Scene_01()
{
}

void Scene_01::Enter()
{
}

void Scene_01::Exit()
{
}

void Scene_01::Update()
{
	Scene::Update();
	if (KEY_TAP(KEY::ENTER))
	{
		ChangeScene(SCENE_TYPE::START);
	}
}
