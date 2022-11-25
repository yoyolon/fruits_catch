#include "Fruits.h"
#include "CircleComponent.h"
#include "Game.h"
#include "MoveComponent.h"
#include "Random.h"
#include "SpriteComponent.h"

Fruits::Fruits(Game* game)
	: Actor(game), mCircle(nullptr), mType(Fruits::FruitsType::Fruits), mPoint(0)
{
	// ランダムな位置・向きで初期化
	Vec2 randomPos = Random::GenVector(Vec2::Zero, Vec2(WINDOW_WIDTH, 0.0f));
	Set_Position(randomPos);
	Set_Rotation(-0.5 * Math::Pi);

	// 移動コンポーネントの生成
	MoveComponent* moveComp = new MoveComponent(this);
	moveComp->Set_ForwardSpeed(50.0f);

	// スプライトコンポーネントの生成
	SpriteComponent* spriteComp = new SpriteComponent(this, 120);
	int rand = Random::GenIntRange(0, 99);
	// 桃: 5%
	if (rand <= 5) {
		spriteComp->Set_Texture(game->GetTexture("assets/peach.png"));
		mPoint = 200;
		moveComp->Set_ForwardSpeed(50.0f);
	}
	// 苺: 25%
	else if (rand <= 30) {
		spriteComp->Set_Texture(game->GetTexture("assets/bery.png"));
		mPoint = 50;
		moveComp->Set_ForwardSpeed(150.0f);
	}
	// 林檎: 50%
	else if (rand <= 80) {
		spriteComp->Set_Texture(game->GetTexture("assets/apple.png"));
		mPoint = 20;
		moveComp->Set_ForwardSpeed(150.0f);
	}
	// ハズレ: 15%
	else if (rand <= 95) {
		spriteComp->Set_Texture(game->GetTexture("assets/dragon.png"));
		mPoint = -100;
		moveComp->Set_ForwardSpeed(100.0f);
	}
	// タイマー: 5%
	else {
		spriteComp->Set_Texture(game->GetTexture("assets/watch.png"));
		mType = Fruits::FruitsType::Watch;
		mPoint = 5;
		moveComp->Set_ForwardSpeed(100.0f);
	}

	// 円コンポーネントの生成(衝突判定用)
	mCircle = new CircleComponent(this);
	mCircle->Set_Radius(8.0f); // TODO: マジックナンバーの除去

	// フルーツをゲームに追加
	game->AddFruits(this);
}

Fruits::~Fruits() {
	Get_Game()->RemoveFruits(this);
}