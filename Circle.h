#pragma once

class Circle : public Drawable
{
public:
	Circle(const Vector2& position, const Vector2& scale, const float& rotation, const int& segments, const Color& color = RED);
	virtual ~Circle() override = default;

	virtual void Update() override;
	virtual void Render() override;

	Vector2 SetVertex(const float& degrees);

private:
	vector<Vertex> vertices;
	int segments = 0;	// 정점 몇개로 그릴것이냐 -> 얼마나 정교하게 그릴것이냐
};