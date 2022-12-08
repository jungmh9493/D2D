#pragma once

class Object
{
protected:
	typedef enum
	{
		COLLIDER_NONE,
		COLLIDER_RECT,
		COLLIDER_CIRCLE,
	} ColliderType;

public:
	Object& operator=(const Object& other);

public:
	Object(const Vector2& position, const Vector2& scale, const float& rotation);
	Object(const Object& other) { *this = other; }
	virtual ~Object();

	Vector2 GetPosition() { return position; }
	Vector2 GetPosition() const { return position; }
	Vector2 GetScale() { return scale; }
	Vector2 GetScale() const { return scale; }
	float GetRotation() { return rotation; }
	float GetRotation() const { return rotation; }

	Vector2 GetRightVector() { return Vector2((R * T)._11, (R * T)._12); }
	Vector2 GetRightVector() const { return Vector2((R * T)._11, (R * T)._12); }
	Vector2 GetUpVector() { return Vector2((R * T)._21, (R * T)._22); }
	Vector2 GetUpVector() const { return Vector2((R * T)._21, (R * T)._22); }

	void SetPosition(const Vector2& position)
	{
		this->position = position;
	}
	void SetScale(const Vector2& scale)
	{
		this->scale = scale;
	}
	void SetRotation(const float& rotation)
	{
		this->rotation = rotation;
	}

	void Move(const Vector2& position)
	{
		this->position += position;
	}
	void Scale(const Vector2& scale)
	{
		this->scale += scale;
	}
	void Rotate(const float& rotation)
	{
		this->rotation += rotation;
	}

	virtual void Update();
	virtual void Render();

	bool Intersect(const Vector2& coord);
	bool Intersect(const Object& other);

protected:
	Matrix world, S, R, T;
	WorldBuffer* WB = nullptr;

	Vector2 position, scale;
	float rotation;

	ColliderType colliderType = COLLIDER_NONE;
};