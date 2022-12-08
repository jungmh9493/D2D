#pragma once

class ColorRect : public Drawable
{
public:
	ColorRect(const Vector2& position, const Vector2& scale, const float& rotation, const Color& color = RED);
	virtual ~ColorRect() override = default;

	virtual void Update() override;
	virtual void Render() override;

private:
	vector<Vertex> vertices;
};