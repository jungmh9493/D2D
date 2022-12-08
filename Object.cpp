#include "stdafx.h"
#include "Object.h"

Object& Object::operator=(const Object& other)
{
	SAFE_DELETE(WB);

	position = other.position;
	scale = other.scale;
	rotation = other.rotation;

	S = XMMatrixScalingFromVector(scale);
	R = XMMatrixRotationZ(-XMConvertToRadians(rotation));
	T = XMMatrixTranslationFromVector(position);

	world = S * R * T;

	WB = new WorldBuffer();
	WB->SetWorld(world);

	return *this;
}

Object::Object(const Vector2& position, const Vector2& scale, const float& rotation)
	: position(position), scale(scale), rotation(rotation)
{
	S = XMMatrixScalingFromVector(scale);
	R = XMMatrixRotationZ(-XMConvertToRadians(rotation));
	T = XMMatrixTranslationFromVector(position);

	world = S * R * T;

	WB = new WorldBuffer();
	WB->SetWorld(world);
}

Object::~Object()
{
	SAFE_DELETE(WB);
}

void Object::Update()
{
	S = XMMatrixScalingFromVector(scale);
	R = XMMatrixRotationZ(-XMConvertToRadians(rotation));
	T = XMMatrixTranslationFromVector(position);

	world = S * R * T;

	WB->SetWorld(world);
}

void Object::Render()
{
	WB->SetVSBuffer(0);
}

bool Object::Intersect(const Vector2& coord)
{
	//using namespace Collision;
	if (colliderType == COLLIDER_RECT)
	{
		if (GetRightVector() == RIGHT)
		{
			Collision::RECT rect(position, scale);
			return Collision::IntersectRectCoord(rect, coord);
		}
		else
		{
			Vector2 rectPivot = Vector2::Transform(Vector2(0, 0), S);
			Collision::RECT rect(rectPivot, scale);
			Matrix rectInverse = (R * T).Invert();
			Vector2 transformedCoord = Vector2::Transform(coord, rectInverse);
			return Collision::IntersectRectCoord(rect, transformedCoord);
		}
	}
	else if (colliderType == COLLIDER_CIRCLE)
	{
		Collision::CIRCLE circle(position, scale);
		return Collision::IntersectCircleCoord(circle, coord);
	}

	return false;
}

bool Object::Intersect(const Object& other)
{
	if (colliderType == COLLIDER_RECT)
	{
		if (other.colliderType == COLLIDER_RECT)
		{
			if (GetRightVector() == RIGHT && other.GetRightVector() == RIGHT)
			{
				Collision::RECT rect1(position, scale);
				Collision::RECT rect2(other.position, other.scale);
				return Collision::IntersectRectRect(rect1, rect2);
			}
			else
			{
				return Collision::IntersectRectRect(*this, other);
			}
		}
		else if (other.colliderType == COLLIDER_CIRCLE)
		{
			if (GetRightVector() == RIGHT)
			{
				Collision::RECT rect(position, scale);
				Collision::CIRCLE circle(other.position, other.scale);
				return Collision::IntersectRectCircle(rect, circle);
			}
			else
			{
				Vector2 rectPivot = Vector2::Transform(Vector2(0, 0), S);
				Matrix rectInverse = (R * T).Invert();
				Vector2 circlePivot = Vector2::Transform(other.position, rectInverse);

				Collision::RECT rect(rectPivot, scale);
				Collision::CIRCLE circle(circlePivot, other.scale);
				return Collision::IntersectRectCircle(rect, circle);
			}
		}
	}
	else if (colliderType == COLLIDER_CIRCLE)
	{
		if (other.colliderType == COLLIDER_RECT)
		{
			if (other.GetRightVector() == RIGHT)
			{
				Collision::CIRCLE circle(position, scale);
				Collision::RECT rect(other.position, other.scale);
				return Collision::IntersectRectCircle(rect, circle);
			}
			else
			{
				Vector2 rectPivot = Vector2::Transform(Vector2(0, 0), S);
				Matrix rectInverse = (other.R * other.T).Invert();
				Vector2 circlePivot = Vector2::Transform(position, rectInverse);

				Collision::RECT rect(rectPivot, other.scale);
				Collision::CIRCLE circle(circlePivot, scale);

				return Collision::IntersectRectCircle(rect, circle);
			}
		}
		else if (other.colliderType == COLLIDER_CIRCLE)
		{
			Collision::CIRCLE circle1(position, scale);
			Collision::CIRCLE circle2(other.position, other.scale);
			return Collision::IntersectCircleCircle(circle1, circle2);
		}
	}

	return false;
}
