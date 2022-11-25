#pragma once

#include <vector>
#include "Actor.h"
#include "SpriteComponent.h"

// 1枚の画像によるアニメーション
class AnimSpriteComponent : public SpriteComponent {
public:
	AnimSpriteComponent(class Actor* owner, int x, int y, int drawOrder = 100);
	// オーバーライド
	void Update(float deltaTime) override;
	void Draw(SDL_Renderer* renderer) override;
	// 入力処理
	void ProcessInput(const uint8_t* keyState) override;
	// アニメーションを変更
	void Change_Anim(float start, float end, float fps, bool flag = true);
	// セッタ
	void Set_AnimFPS(float fps) { mAnimFPS = fps; }
	void Set_AnimStart(float start) { mAnimStart = start; }
	void Set_AnimEnd(float end) { mAnimEnd = end; }
	void Set_CurrFrame(float frame) { mCurrFrame = frame; }
	void Set_mIsAnimLoop(bool flag) { mIsAnimLoop = flag; }
	// ゲッタ
	float Get_AnimFPS() const { return mAnimFPS; }

private:
	// アニメーションテクスチャ
	SDL_Texture* mAnimTextures;
	// 表示フレーム
	float mCurrFrame;
	// フレームレート
	float mAnimFPS;
	// アニメーション範囲
	float mAnimStart, mAnimEnd;
	// ループの有無
	bool mIsAnimLoop;
	// テクスチャ分割数
	int lenX, lenY;
};
