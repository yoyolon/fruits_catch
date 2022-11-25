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

// “ñ‚Â‚Ì‰~‚ÌŒğ·”»’è
bool Intersect(const CircleComponent& a, const CircleComponent& b) {
	// ‹——£‚Ì“ñæ‚ğŒvZ
	float distance = (a.Get_Center() - b.Get_Center()).Length2();

	// ‹…‚Ì”¼Œa‚Ì˜a‚Ì“ñæ‚ğŒvZ
	float radii = a.Get_Radius() + b.Get_Radius();
	radii *= radii;

	return distance <= radii;
}
