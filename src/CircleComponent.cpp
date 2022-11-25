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

// ��̉~�̌�������(���ӂ��悷�邱�Ƃō�����)
bool Intersect(const CircleComponent& a, const CircleComponent& b) {
	// �����̓����v�Z
	float distance = (a.Get_Center() - b.Get_Center()).Length2();
	// ���̔��a�̘a�̓����v�Z
	float radius = a.Get_Radius() + b.Get_Radius();
	radius *= radius;

	return distance <= radius;
}
