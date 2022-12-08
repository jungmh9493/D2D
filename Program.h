#pragma once

class Program
{
public:
	Program();
	~Program();

	void Init();

	void SetGlobalBuffers();

public:
	void Update();
	void PreRender();
	void Render();
	void PostRender();

private:
	ViewProjectionBuffer* VPBuffer = nullptr;

	Matrix view;
	Matrix projection;

	Scene* currentScene = nullptr;
	vector<Scene*> sceneList;
};