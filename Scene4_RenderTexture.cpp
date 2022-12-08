#include "stdafx.h"
#include "Scene4_RenderTexture.h"

Scene4::~Scene4()
{
	Destroy();
}

void Scene4::Init()
{
	rect = new ColorRect(WIN_CENTER, Vector2(100, 100), 0.0f);
	line = new Line(WIN_CENTER, 200.0f, 45.0f, CYAN);
	circle = new Circle(WIN_CENTER, Vector2(100, 100), 0.0f, 100);

	RTT = new RenderTexture();
	RTT->Initialize();

	Vector2 size = { gWinWidth, gWinHeight };
	renderingTexture = new TextureRect(size / 2, size, 0);
	renderingTexture->SetSRV(RTT->GetSRV());
}

void Scene4::Destroy()
{
	SAFE_DELETE(renderingTexture);

	SAFE_DELETE(RTT);

	SAFE_DELETE(circle);
	SAFE_DELETE(line);
	SAFE_DELETE(rect);
}

void Scene4::Update()
{
	if (INPUT->Down('Q'))
	{
		if (rect->GetColor() == RED)
			rect->SetColor(GREEN);
		else if (rect->GetColor() == GREEN)
			rect->SetColor(BLUE);
		else if (rect->GetColor() == BLUE)
			rect->SetColor(YELLOW);
		else if (rect->GetColor() == YELLOW)
			rect->SetColor(MAGENTA);
		else if (rect->GetColor() == MAGENTA)
			rect->SetColor(CYAN);
		else if (rect->GetColor() == CYAN)
			rect->SetColor(RED);
	}

	if (INPUT->Press('W'))
	{
		rect->Move(Vector2(0, 200) * TIME->GetDeltaTime());
	}
	if (INPUT->Press('S'))
	{
		rect->Move(Vector2(0, -200) * TIME->GetDeltaTime());
	}
	if (INPUT->Press('A'))
	{
		rect->Move(Vector2(-200, 0) * TIME->GetDeltaTime());
	}
	if (INPUT->Press('D'))
	{
		rect->Move(Vector2(200, 0) * TIME->GetDeltaTime());
	}

	if (INPUT->Press(VK_UP))
	{
		rect->Scale(Vector2(150, 150) * TIME->GetDeltaTime());
	}
	if (INPUT->Press(VK_DOWN))
	{
		rect->Scale(Vector2(-150, -150) * TIME->GetDeltaTime());
	}

	if (INPUT->Press(VK_LEFT))
	{
		rect->Rotate(-200 * TIME->GetDeltaTime());
	}
	if (INPUT->Press(VK_RIGHT))
	{
		rect->Rotate(200 * TIME->GetDeltaTime());
	}

	rect->Update();
	line->Update();
	circle->Update();

	renderingTexture->Update();

	if (INPUT->Down(VK_F11))
		RTT->SaveTexture(L"../_ScreenShots/ScreenShot.bmp");
}

void Scene4::PreRender()
{
	GRAPHICS->SetViewport();	// 메인 화면에서 해주던 것을 별도의 공간에서 해준다.
	RTT->RenderToTexture();
	{	// 새로 세팅된 도화지에 렌더링 해주고싶은 것들을 렌더링
		rect->Render();
		line->Render();
		circle->Render();
	}
	GRAPHICS->SetBackbufferToRTV();
}

void Scene4::Render()
{
	renderingTexture->Render();
}

void Scene4::PostRender()
{
}
