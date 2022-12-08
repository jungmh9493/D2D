#pragma once

class Object;	// ���� ���� - extern�� ���� �����Ϸ����� Ŭ������ ���縦 �̸� �˷���

namespace Collision
{
	struct RECT		// �簢�� ������ �˱� ���� ����ü
	{
		Vector2 min;	// ���ϴ�
		Vector2 max;	// ����
		RECT(Vector2 position, Vector2 scale);
	};
	struct CIRCLE
	{
		Vector2 pivot;	// �߽���
		float radius;	// ������
		CIRCLE(Vector2 position, Vector2 scale);
	};

	bool IntersectRectCoord(const RECT& rect, const Vector2& coord);
	bool IntersectCircleCoord(const CIRCLE& circle, const Vector2& coord);

	bool IntersectRectRect(const RECT& rect1, const RECT& rect2);
	bool IntersectRectRect(const Object& object1, const Object& object2);

	bool IntersectCircleCircle(const CIRCLE& circle1, const CIRCLE& circle2);
	bool IntersectRectCircle(const RECT& rect, const CIRCLE& circle);
}