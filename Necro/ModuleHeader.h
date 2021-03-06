#pragma once
#include "./Utilities/Logging.h"

//Manager
#include "./Systems/Keyboard.h"
#include "./Systems/Mouse.h"
#include "./Systems/Time.h"
#include "./Systems/Manage/SoundManager.h"
#include "./Systems/Message/DataContext.h"
#include "./Scenes/SceneBase.h"
#include "./Systems/Manage/MessageManager.h"
#include "./Systems/Manage/SceneManager.h"
#include "./Systems/Manage/BeatManager.h"
#include "./Systems/Manage/ObjectManager.h"
#include "./Systems/Manage/RenderManager.h"
#include "./Systems/Manage/TileManager.h"
//#include "./Systems/Manage/TextManager.h"
#include "./Utilities/Matrix2D.h"
#include "./Utilities/Matrix2x2.h"


#include "./Render/BufferManager.h"
#include "./Render/VertexLayout.h"
#include "./Render/States.h"
#include "./Render/ShaderBuffer.h"
#include "./Render/Shader.h"
#include "./Render/ShaderManager.h"
#include "./Render/Texture.h"
#include "./Render/ImageManager.h"

#include "./Systems/Manage/EffectManager.h"

#include "./View/CameraManager.h"

#include "./Utilities/Line.h"
#include "./Utilities/Math.h"
#include "./Utilities/Json.h"
#include "./Utilities/String.h"
#include "./Utilities/Path.h"
#include "./Utilities/Buffer.h"

#define KeyCode Keyboard::Get()
#define GameMouse Mouse::Get()
#define DeltaTime Time::Delta()

