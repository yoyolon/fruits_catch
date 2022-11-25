#include "Player.h"
#include <algorithm>
#include "AnimSpriteComponent.h"
#include "CircleComponent.h"
#include "Fruits.h"
#include "Game.h"
#include "InputComponent.h"

// コンストラクタ
Player::Player(Game* game)
	: Actor(game), mCircle(nullptr), mScore(0), mTimer(30.0f)
{
	// プレイヤーテクスチャ(本体)
	AnimSpriteComponent* asc = new AnimSpriteComponent(this, 3, 4);
	asc->Set_Texture(game->GetTexture("assets/player_walk.png"));
	asc->Change_Anim(6, 8, 8);

	// プレイヤーテクスチャ(籠)
	AnimSpriteComponent* ascFront = new AnimSpriteComponent(this, 3, 4, 150);
	ascFront->Set_Texture(game->GetTexture("assets/player_basket.png"));
	ascFront->Change_Anim(6, 8, 8);

	// 入力処理コンポーネントの生成
	InputComponent* inputComp = new InputComponent(this);
	inputComp->Set_ForwardKey(SDL_SCANCODE_RIGHT);
	inputComp->Set_BackKey(SDL_SCANCODE_LEFT);
	inputComp->Set_ClockwiseKey(SDL_SCANCODE_A);
	inputComp->Set_CounterClockwiseKey(SDL_SCANCODE_D);
	inputComp->Set_MaxForwardSpeed(150.0f);
	inputComp->Set_MaxAngularSpeed(0.0f * Math::Pi);

	// 円コンポーネントの生成(衝突判定用)
	mCircle = new CircleComponent(this);
	mCircle->Set_Radius(8.0f); // TODO: マジックナンバーの除去
	mCircle->Set_Offset(Vec2(0.0, -10.0));
}

// アクターの更新
void Player::UpdateActor(float deltaTime) {
	// 時間の更新
	mTimer -= deltaTime;
	// 位置の更新
	Vec2 pos = Get_Position();
	pos.x = std::clamp(pos.x, 0.0f, float(WINDOW_WIDTH));
	Set_Position(pos);

	// プレイヤーとフルーツの交差判定
	for (auto fruit : Get_Game()->Get_Fruits()) {
		if (Intersect(*mCircle, *(fruit->Get_Circle()))) {
			// スコアと残り時間の追加
			Fruits::FruitsType type = fruit->Get_Type();
			if (type == Fruits::FruitsType::Fruits) mScore += fruit->Get_Point();
			else if (type == Fruits::FruitsType::Watch) mTimer += fruit->Get_Point();
			// フルーツの除去
			fruit->Set_State(State::Dead);
			break;
		}
	}
}