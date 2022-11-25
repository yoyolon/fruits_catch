#pragma once

#include <algorithm>
#include <cstdint>
#include <vector>
#include "Game.h"
#include "Math.h"
#include "Utility.h"

// アクタークラス
class Actor {
public:
	enum State { EActive, Epause, EDead };

	Actor(class Game* game);
	virtual ~Actor(); // デストラクタ

	// アクターの更新(Gameから呼び出す)
	void Update(float deltaTime);
	// アクターが持つコンポーネントを更新
	void UpdateComponents(float deltaTime);
	// アクターのみの更新(オーバーライドして使う)
	virtual void UpdateActor(float deltaTime);

	// ゲームからの入力を処理
	void ProcessInput(const uint8_t* keyState);
	// アクター固有の入力処理(オーバーライドして使う)
	virtual void ActorInput(const uint8_t* keyState);

	// ゲッタ/セッタ
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

	// アクターの追加/削除
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