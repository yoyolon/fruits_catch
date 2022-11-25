#pragma once

#include "Actor.h"

// プレイヤークラス
class Player : public Actor {
public:
	Player(class Game* game);

	void UpdateActor(float DeltaTime) override;

	// ゲッタ
	int Get_Score() const { return mScore; }
	float Get_Time() const { return mTimer; }

private:
	// TODO: スコア 残り時間
	class CircleComponent* mCircle;
	int mScore;
	float mTimer;
};