#include "stdafx.h"
#include "Scene3_Intersect.h"

Scene3::~Scene3()
{
	Destroy();
}

void Scene3::Init()
{
	rect1 = new ColorRect(WIN_CENTER, Vector2(100, 100), 0.0f, BLUE);
	rect2 = new ColorRect(WIN_CENTER + Vector2(200, 200), Vector2(100, 100), 30.0f);
	circle = new Circle(Vector2(200, 200), Vector2(50, 50), 0.0f, 100);
}

void Scene3::Destroy()
{
	SAFE_DELETE(circle);
	SAFE_DELETE(rect2);
	SAFE_DELETE(rect1);
}

void Scene3::Update()
{
	// 방향키에 따라서 rect 움직이기
	if (INPUT->Press('W'))
	{
		rect1->Move(Vector2(0, 200) * TIME->GetDeltaTime());
	}
	if (INPUT->Press('S'))
	{
		rect1->Move(Vector2(0, -200) * TIME->GetDeltaTime());
	}
	if (INPUT->Press('A'))
	{
		rect1->Move(Vector2(-200, 0) * TIME->GetDeltaTime());
	}
	if (INPUT->Press('D'))
	{
		rect1->Move(Vector2(200, 0) * TIME->GetDeltaTime());
	}

	if (INPUT->Press(VK_LEFT))
	{
		rect1->Rotate(-200 * TIME->GetDeltaTime());
	}
	if (INPUT->Press(VK_RIGHT))
	{
		rect1->Rotate(200 * TIME->GetDeltaTime());
	}

	if (rect1->Intersect(*rect2))
		rect2->SetColor(MAGENTA);
	else
		rect2->SetColor(RED);

	if (rect1->Intersect(*circle))
		circle->SetColor(YELLOW);
	else
		circle->SetColor(RED);

	rect1->Update();
	rect2->Update();
	circle->Update();
}

void Scene3::Render()
{
	rect1->Render();
	rect2->Render();
	circle->Render();
}
