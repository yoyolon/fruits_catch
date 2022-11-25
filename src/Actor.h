#pragma once

#include <algorithm>
#include <cstdint>
#include <vector>
#include "Game.h"
#include "Math.h"
#include "Utility.h"

// *** アクタークラス ***
class Actor {
public:
	enum class State { Active, Pause, Dead };

	Actor(class Game* game);
	virtual ~Actor(); // デストラクタ

	void Update(float deltaTime);
	void UpdateComponents(float deltaTime);
	void ProcessInput(const uint8_t* keyState);
	virtual void UpdateActor(float deltaTime);
	virtual void ActorInput(const uint8_t* keyState);

	// アクセッサ
	const Vec2& Get_Position() const { return mPosition; }
	void Set_Position(const Vec2& position) { mPosition = position; }
	float Get_Scale() const { return mScale; }
	void Set_Scale(float scale) { mScale = scale; }
	float Get_Rotation() const { return mRotation; }
	void Set_Rotation(float rotation) { mRotation = rotation; }
	Vec2 Get_Forward() const { return Vec2(std::cos(mRotation), -std::sin(mRotation)); }
	State Get_State() const { return mState; }
	void Set_State(State state) { mState = state; }
	class Game* Get_Game() { return mGame; }

	// コンポーネントの追加/削除
	void AddComponent(class Component* component);
	void RemoveComponent(class Component* component);

private:
	// アクターの状態
	State mState;
	// トランスフォーム
	Vec2 mPosition;
	float mScale;
	float mRotation;
	// アクターのコンポーネント
	std::vector<class Component*> mComponents;
	// ゲーム
	class Game* mGame;
};