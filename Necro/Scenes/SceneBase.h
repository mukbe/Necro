#pragma once


class SceneBase 
{
public:
	SceneBase();
	virtual ~SceneBase();

	virtual void Init();
	virtual void Release();
	
	virtual void ControlUpdate();
	virtual void Update(float tick);


	virtual void ObjectRender();
	virtual void LightRender();
	virtual void UIRender();
	virtual void ImguiRender();




	class MessageManager* GetMessagePool() { return messageManager; }
	class ObjectManager* GetObjectPool() { return objectManager; }
	class RenderManager* GetRenderPool() { return renderManager; }
	class BeatManager* GetBeatManager() { return beatManager; }
	class TileManager* GetTileManager() { return tileManager; }
protected:
	class MessageManager* messageManager;
	class ObjectManager* objectManager;
	class RenderManager* renderManager;
	class BeatManager* beatManager;
	class TileManager* tileManager;

};

