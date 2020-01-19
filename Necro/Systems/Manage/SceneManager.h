#pragma once

class SceneManager
{
	SingletonHeader(SceneManager)
public:

	void Release();
	void Update(float tick);
	//void Render();
	//void ImguiRender();


	void AddScene(SceneBase* node);
	void PopScene();
	void ChangeScene(SceneBase* node);
	SceneBase* GetNowScene();
private:
	stack<SceneBase*> scenes;

	SceneBase* nowScene;
};

#define _SceneManager SceneManager::Get()
#define _GameWorld SceneManager::Get()->GetNowScene()
#define _MessagePool SceneManager::Get()->GetNowScene()->GetMessagePool()
#define _ObjectPool SceneManager::Get()->GetNowScene()->GetObjectPool()
#define _RenderPool SceneManager::Get()->GetNowScene()->GetRenderPool()
#define _BeatManager SceneManager::Get()->GetNowScene()->GetBeatManager()