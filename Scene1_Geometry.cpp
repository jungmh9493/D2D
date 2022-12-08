#include "stdafx.h"
#include "Scene1_Geometry.h"

Scene1::~Scene1()
{
	Destroy();
}

void Scene1::Init()
{
	rect = new ColorRect(WIN_CENTER, Vector2(100, 100), 0.0f);
	line = new Line(WIN_CENTER, 200.0f, 45.0f, CYAN);
	circle = new Circle(WIN_CENTER, Vector2(100, 100), 0.0f, 100);

	Vector2 size = { gWinWidth / 3, gWinHeight / 3 };
	texture = new TextureRect(size / 2, size, 0, L"../_Textures/bk.bmp");
}

void Scene1::Destroy()
{
	SAFE_DELETE(texture);
	SAFE_DELETE(circle);
	SAFE_DELETE(line);
	SAFE_DELETE(rect);
}

void Scene1::Update()
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
	// 방향키에 따라서 rect 움직이기
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

	texture->Update();
}

void Scene1::Render()
{
	rect->Render();
	line->Render();
	circle->Render();

	texture->Render();
}
