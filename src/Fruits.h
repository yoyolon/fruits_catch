#pragma once

#include "Actor.h"

// *** フルーツオブジェクト ***
class Fruits : public Actor {
public:
	enum class FruitsType { Fruits, Watch };

	Fruits(class Game* game);
	~Fruits();
	
	void UpdateActor(float DeltaTime) override;

	// ゲッタ
	class CircleComponent* Get_Circle() const { return mCircle; }
	int Get_Point() const { return mPoint; }
	FruitsType Get_Type() const { return mType; }

private:
	class CircleComponent* mCircle; // 衝突判定コンポーネント
	int mPoint; // 得点
	FruitsType mType; // オブジェクトの種類
};