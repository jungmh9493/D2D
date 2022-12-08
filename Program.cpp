#include "stdafx.h"
#include "Scenes/SceneList.h"
#include "Program.h"

Program::Program()
{
	VPBuffer = new ViewProjectionBuffer();

	SetGlobalBuffers();

	Init();
}

Program::~Program()
{
	for (Scene* scene : sceneList)
		SAFE_DELETE(scene);

	SAFE_DELETE(VPBuffer);
}

void Program::Init()
{
	//sceneList.push_back(new Scene1());
	//sceneList.push_back(new Scene2());
	sceneList.push_back(new Scene3());
	sceneList.push_back(new Scene4());
	sceneList.push_back(new Scene5());

	currentScene = sceneList[2];
	currentScene->Init();
}

void Program::SetGlobalBuffers()
{
	view = XMMatrixLookAtLH(Vector3(0, 0, 0), Vector3(0, 0, 1), Vector3(0, 1, 0));		// 카메라의 시점
	projection = XMMatrixOrthographicOffCenterLH(0, gWinWidth, 0, gWinHeight, 0, 1);	// 직교 투영

	VPBuffer->SetView(view);
	VPBuffer->SetProjection(projection);
}

void Program::Update()
{
	if (INPUT->Down(VK_F1))
	{
		currentScene->Destroy();

		currentScene = sceneList[0];
		currentScene->Init();
	}
	else if (INPUT->Down(VK_F2))
	{
		currentScene->Destroy();

		currentScene = sceneList[1];
		currentScene->Init();
	}
	else if (INPUT->Down(VK_F3))
	{
		currentScene->Destroy();

		currentScene = sceneList[2];
		currentScene->Init();
	}

	currentScene->Update();
}

void Program::PreRender()
{
	currentScene->PreRender();
}

void Program::Render()
{
	VPBuffer->SetVSBuffer(1);

	currentScene->Render();
}

void Program::PostRender()
{
	currentScene->PostRender();
}
