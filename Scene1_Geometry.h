#pragma once

class Scene1 : public Scene
{
public:
	Scene1() = default;
	virtual ~Scene1() override;

	virtual void Init() override;
	virtual void Destroy() override;

	virtual void Update() override;
	virtual void PreRender() override {};
	virtual void Render() override;
	virtual void PostRender() override {};

private:
	ColorRect* rect = nullptr;
	Line* line = nullptr;
	Circle* circle = nullptr;

	TextureRect* texture = nullptr;
};