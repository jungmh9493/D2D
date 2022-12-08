#pragma once

class Scene4 : public Scene
{
public:
	Scene4() = default;
	virtual ~Scene4() override;

	virtual void Init() override;
	virtual void Destroy() override;

	virtual void Update() override;
	virtual void PreRender() override;
	virtual void Render() override;
	virtual void PostRender() override;

private:
	ColorRect* rect = nullptr;
	Line* line = nullptr;
	Circle* circle = nullptr;

	RenderTexture* RTT = nullptr;

	TextureRect* renderingTexture = nullptr;
};