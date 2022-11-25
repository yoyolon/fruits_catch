#include "FruitsGenerator.h"
#include "Fruits.h"
#include "Random.h"

// コンストラクタ
FruitsGenerator::FruitsGenerator(Game* game)
	: Actor(game), mTimer(0.0f), mDownTime(0.25f)
{}


// 更新
void FruitsGenerator::UpdateActor(float deltaTime) {
	// 一定時間経過でフルーツを生成
	mTimer += deltaTime;
	if (mTimer >= mDownTime) {
		// ランダム性を持たせる
		if (mTimer - mDownTime >= Random::GenFloatRange(0.0f, 2.0f)) {
			new Fruits(this->Get_Game());
			mTimer = 0.0f;
		}
	}
}