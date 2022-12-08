#pragma once

class Object;	// 전방 선언 - extern과 같이 컴파일러에게 클래스의 존재를 미리 알려줌

namespace Collision
{
	struct RECT		// 사각형 영역을 알기 위한 구조체
	{
		Vector2 min;	// 좌하단
		Vector2 max;	// 우상단
		RECT(Vector2 position, Vector2 scale);
	};
	struct CIRCLE
	{
		Vector2 pivot;	// 중심점
		float radius;	// 반지름
		CIRCLE(Vector2 position, Vector2 scale);
	};

	bool IntersectRectCoord(const RECT& rect, const Vector2& coord);
	bool IntersectCircleCoord(const CIRCLE& circle, const Vector2& coord);

	bool IntersectRectRect(const RECT& rect1, const RECT& rect2);
	bool IntersectRectRect(const Object& object1, const Object& object2);

	bool IntersectCircleCircle(const CIRCLE& circle1, const CIRCLE& circle2);
	bool IntersectRectCircle(const RECT& rect, const CIRCLE& circle);
}