// header.h: ǥ�� �ý��� ���� ����
// �Ǵ� ������Ʈ Ư�� ���� ������ ��� �ִ� ���� �����Դϴ�.
//

#pragma once

#define NOMINMAX

#ifdef _DEBUG	// _DEBUG : ����� ����϶� / _NDEBUG : ����� ��尡 �ƴҶ�
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")
#endif

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN             // ���� ������ �ʴ� ������ Windows ������� �����մϴ�.
// Windows ��� ����
#include <windows.h>
#include <windowsx.h>
// C ��Ÿ�� ��� �����Դϴ�.
#include <cassert>

// C++ ��Ÿ�� ��� �����Դϴ�.
#include <array>
#include <string>
#include <iostream>
#include <chrono>
#include <cmath>
#include <vector>
#include <set>
#include <random>

using namespace std;

#include <d3d11.h>
#include <d3dcompiler.h>
#pragma comment(lib, "dxgi.lib")		// ���̺귯�� ����
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")

// DirectXTK (SimpleMath)
#include "_Libraries/DirectXTK/SimpleMath.h"
using namespace DirectX;
using namespace SimpleMath;

// DirectXTex
#include "_Libraries/DirectXTex/DirectXTex.h"
#ifdef _DEBUG
#pragma comment(lib, "../_Libraries/DirectXTex/Debug/DirectXTex.lib")
#elif NDEBUG
#pragma comment(lib, "../_Libraries/DirectXTex/Release/DirectXTex.lib")
#endif


// extern global
extern HWND gHandle;
extern float gWinWidth;	// â ũ�Ⱑ ������ ���� ��� ���� ��������
extern float gWinHeight;


// macros
#define WIN_DEFAULT_WIDTH 1280.0f	// ������ â�� �⺻��
#define WIN_DEFAULT_HEIGHT 720.0f

#define WIN_CENTER_X (gWinWidth / 2)
#define WIN_CENTER_Y (gWinHeight / 2)
#define WIN_CENTER Vector2(WIN_CENTER_X, WIN_CENTER_Y)

#define RIGHT Vector2(1.0f, 0.0f)
#define UP Vector2(0.0f, 1.0f)

#define RED Color(1, 0, 0, 1)
#define GREEN Color(0, 1, 0, 1)
#define BLUE Color(0, 0, 1, 1)
#define BLACK Color(0, 0, 0, 1)
#define WHITE Color(1, 1, 1, 1)
#define YELLOW Color(1, 1, 0, 1)
#define MAGENTA Color(1, 0, 1, 1)
#define CYAN Color(0, 1, 1, 1)

#define SUPER __super

#define CHECK(hr) { assert(SUCCEEDED(hr)); }

#define SAFE_DELETE(p) { if(p) { delete(p); p = nullptr; } }
#define SAFE_DELETE_ARRAY(p) { if(p) { delete[](p); p = nullptr; } }
#define SAFE_RELEASE(p) { if(p) { p->Release(); p = nullptr; } }

#define DECLARE_SINGLETON(CLASS_NAME)						\
private:													\
CLASS_NAME();												\
~CLASS_NAME();												\
public:														\
CLASS_NAME(const CLASS_NAME& other) = delete;				\
CLASS_NAME operator=(const CLASS_NAME& other) = delete;		\
CLASS_NAME(const CLASS_NAME&& other) = delete;				\
CLASS_NAME operator=(const CLASS_NAME&& other) = delete;	\
public:														\
static void Delete()										\
{															\
	delete(instance);										\
	instance = nullptr;										\
}															\
static CLASS_NAME* Get()									\
{															\
	if (instance == nullptr)								\
		instance = new CLASS_NAME();						\
	return instance;										\
}															\
private:													\
static CLASS_NAME* instance;

// headers
#include "Systems/Input.h"
#include "Systems/Time.h"
#include "Systems/Graphics.h"

#define INPUT Input::Get()
#define TIME Time::Get()
#define GRAPHICS Graphics::Get()
#define DEVICE Graphics::Get()->GetDevice()
#define DC Graphics::Get()->GetDC()

#include "Renders/Resources/VertexType.h"
#include "Renders/IA/VertexBuffer.h"
#include "Renders/Shaders/VertexShader.h"
#include "Renders/IA/IndexBuffer.h"
#include "Renders/IA/InputLayout.h"
#include "Renders/Shaders/PixelShader.h"
#include "Renders/Resources/ShaderBuffer.h"
#include "Renders/Resources/GlobalBuffer.h"

#include "Utillities/Collision.h"
#include "Utillities/RenderTexture.h"

#include "Objects/Object.h"
#include "Objects/Drawable.h"
#include "Objects/Line.h"
#include "Objects/ColorRect.h"
#include "Objects/Circle.h"
#include "Objects/TextureRect.h"

#include "Scenes/Scene.h"