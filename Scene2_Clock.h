#pragma once

class Scene2 : public Scene
{
public:
	Scene2() = default;
	virtual ~Scene2() override;

	virtual void Init() override;
	virtual void Destroy() override;

	virtual void Update() override;
	virtual void PreRender() override {};
	virtual void Render() override;
	virtual void PostRender() override {};

private:
	SYSTEMTIME time = { 0 };

	Circle* clock = nullptr;

	Line* hour = nullptr;
	Line* min = nullptr;
	Line* sec = nullptr;
};