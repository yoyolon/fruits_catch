#pragma once

#include "Component.h"
#include "Math.h"

class CircleComponent : public Component {
public:
	CircleComponent(class Actor* owner);

	// セッタ・ゲッタ
	float Get_Radius() const;
	void Set_Radius(float radius) { mRadius = radius; }
	const Vec2& Get_Center() const;
	void Set_Offset(Vec2 offset) { mOffset = offset; }
	const Vec2& Get_Offset() const {return mOffset; }

private:
	float mRadius;
	Vec2 mOffset;
};

// 交差判定
bool Intersect(const CircleComponent& a, const CircleComponent& b);