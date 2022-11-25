#pragma once

#include "Actor.h"

// *** フルーツオブジェクトのジェネレータ ***
class FruitsGenerator : public Actor {
public:
	FruitsGenerator(Game* game);
	// 時間の更新
	void UpdateActor(float deltaTime) override;

private:
	float mTimer; // 経過時間
	float mDownTime; // 生成可能時間
};
