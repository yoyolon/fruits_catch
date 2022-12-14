#include "Actor.h"
#include "Component.h"

// コンストラクタ
Actor::Actor(Game* game)
	: mState(State::Active),
	  mPosition(Vec2::Zero),
	  mScale(1.0f),
	  mRotation(0.0f),
	  mGame(game)
{ mGame->AddActor(this); }


// デストラクタ
Actor::~Actor() {
	mGame->RemoveActor(this);
	// 各コンポーネントを削除
	// NOTE: ~ComponentがActorのメソッドを呼び出すので使えない
	while (!mComponents.empty()) {
		delete mComponents.back();
	}
}


// アクターの更新
void Actor::Update(float deltaTime) {
	if (mState == State::Active) {
		UpdateComponents(deltaTime);
		UpdateActor(deltaTime);
	}
}

// アクター固有の更新処理
void Actor::UpdateActor(float deltaTime) {

}

// 全コンポーネントの更新
void Actor::UpdateComponents(float deltaTime) {
	for (auto comp : mComponents) {
		comp->Update(deltaTime);
	}
}

// キー入力の処理
void Actor::ProcessInput(const uint8_t* keyState) {
	if (mState == State::Active) {
		if (mState == State::Active) {
			// 全コンポーネントの処理
			for (auto comp : mComponents) {
				comp->ProcessInput(keyState);
			}
			// アクター固有の処理
			ActorInput(keyState);
		}
	}
}

// アクター固有の入力処理
void Actor::ActorInput(const uint8_t* keyState) {

}


// コンポーネントの追加
void Actor::AddComponent(Component* component) {
	// mOrderに基づく位置に挿入
	int myOrder = component->Get_UpdateOrder();
	auto itr = mComponents.begin();
	while (itr != mComponents.end()) {
		if (myOrder < (*itr)->Get_UpdateOrder()) break;
		itr++;
	}
	// 挿入
	mComponents.insert(itr, component);
}


// コンポーネントの削除
void Actor::RemoveComponent(Component* component) {
	auto itr = std::find(mComponents.begin(), mComponents.end(), component);
	if (itr != mComponents.end()) {
		mComponents.erase(itr);
	}
}