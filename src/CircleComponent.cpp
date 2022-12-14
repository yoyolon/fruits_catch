#include "CircleComponent.h"
#include "Actor.h"

CircleComponent::CircleComponent(Actor* owner)
	:Component(owner), mRadius(0.0f), mOffset(Vec2::Zero)
{}

float CircleComponent::Get_Radius() const {
	return mOwner->Get_Scale() * mRadius;
}

const Vec2& CircleComponent::Get_Center() const {
	return mOwner->Get_Position() + mOffset;
}

// 二つの円の交差判定(両辺を二乗することで高速化)
bool Intersect(const CircleComponent& a, const CircleComponent& b) {
	// 距離の二乗を計算
	float distance = (a.Get_Center() - b.Get_Center()).Length2();
	// 球の半径の和の二乗を計算
	float radius = a.Get_Radius() + b.Get_Radius();
	radius *= radius;

	return distance <= radius;
}
