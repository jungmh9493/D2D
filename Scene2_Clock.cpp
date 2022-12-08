#include "stdafx.h"
#include "Scene2_Clock.h"

Scene2::~Scene2()
{
	Destroy();
}

void Scene2::Init()
{
	clock = new Circle(WIN_CENTER, Vector2(gWinHeight / 2.3f, gWinHeight / 2.3f), 0.0f, 100, WHITE);

	hour = new Line(WIN_CENTER, gWinHeight / 4.0f, 0, RED);
	min = new Line(WIN_CENTER, gWinHeight / 3.0f, 0, GREEN);
	sec = new Line(WIN_CENTER, gWinHeight / 2.5f, 0, BLUE);
}

void Scene2::Destroy()
{
	SAFE_DELETE(sec);
	SAFE_DELETE(min);
	SAFE_DELETE(hour);

	SAFE_DELETE(clock);
}

void Scene2::Update()
{
	GetLocalTime(&time);	// local time : 우리 컴퓨터의 시간

	cout << time.wYear << "년 ";
	cout << time.wMonth << "월 ";
	cout << time.wDay << "일 ";
	switch (time.wDayOfWeek)
	{
	case 0:
		cout << "일요일 ";
		break;
	case 1:
		cout << "월요일 ";
		break;
	case 2:
		cout << "화요일 ";
		break;
	case 3:
		cout << "수요일 ";
		break;
	case 4:
		cout << "목요일 ";
		break;
	case 5:
		cout << "금요일 ";
		break;
	case 6:
		cout << "토요일 ";
		break;
	}
	cout << time.wHour << "시 ";
	cout << time.wMinute << "분 ";
	cout << time.wSecond << "초 ";
	cout << time.wMilliseconds << "밀리초" << '\n';

	hour->SetRotation(time.wHour * 30.0f + time.wMinute * 30.0f / 60.0f + time.wSecond * 30.0f / 60.0f / 60.0f + time.wMilliseconds * 30.0f / 60.0f / 60.0f / 1000.0f - 90.0f);
	min->SetRotation(time.wMinute * 6.0f + time.wSecond * 6.0f / 60.0f + time.wMilliseconds * 6.0f / 60.0f / 1000.0f - 90.0f);
	sec->SetRotation(time.wSecond * 6.0f + time.wMilliseconds * 6.0f / 1000.0f - 90.0f);

	clock->Update();

	hour->Update();
	min->Update();
	sec->Update();
}

void Scene2::Render()
{
	clock->Render();

	hour->Render();
	min->Render();
	sec->Render();
}
