#pragma once


class Line : public Drawable
{
public:
	Line(const Vector2& position, const float& length, const float& rotation, const Color& color = RED);
	virtual ~Line() override = default;

	virtual void Update() override;
	virtual void Render() override;

private:
	vector<Vertex> vertices;
};