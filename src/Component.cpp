#include "Component.h"
#include "Actor.h"
#include <SDL.h>

// コンストラクタ
Component::Component(Actor* owner, int updateOrder)
	: mOwner(owner),
	  mUpdateOrder(updateOrder)
{
	// アクター(所有者)に自身を追加
	mOwner->AddComponent(this);
}

// デストラクタ
Component::~Component() {
	// アクター(所有者)から自身を削除
	mOwner->RemoveComponent(this);
}

// 更新
void Component::Update(float deltaTime) {
	// オーバーライド
}

// 入力処理
void Component::ProcessInput(const uint8_t* keyState) {
	// オーバーライド
}