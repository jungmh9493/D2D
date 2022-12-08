#pragma once

class Scene3 : public Scene
{
public:
	Scene3() = default;
	virtual ~Scene3() override;

	virtual void Init() override;
	virtual void Destroy() override;

	virtual void Update() override;
	virtual void PreRender() override {};
	virtual void Render() override;
	virtual void PostRender() override {};

private:
	ColorRect* rect1 = nullptr;
	ColorRect* rect2 = nullptr;
	Circle* circle = nullptr;
};