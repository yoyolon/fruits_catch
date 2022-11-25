#include "AnimSpriteComponent.h"
#include "Math.h"

// コンストラクタ
AnimSpriteComponent::AnimSpriteComponent(Actor* owner, int x, int y, int drawOrder)
	: SpriteComponent(owner, drawOrder),
	mAnimTextures(nullptr),
	lenX(x),
	lenY(y),
	mCurrFrame(0.0f),
	mAnimFPS(24.0f),
	mAnimStart(0),
	mAnimEnd(x*y-1),
	mIsAnimLoop(true)
{}

// 更新(オーバーライド)
void AnimSpriteComponent::Update(float deltaTime) {
	SpriteComponent::Update(deltaTime);
	// フレームの更新
	mCurrFrame += mAnimFPS * deltaTime;
	if (!mIsAnimLoop) mCurrFrame = std::min(mCurrFrame, mAnimEnd);
	float diffFrame = mCurrFrame - mAnimEnd;
	// フレームをループさせる
	if (diffFrame -1.0f >= 0.0f) {
		int range = std::max(1, int(mAnimEnd - mAnimStart));
		int offset = int(diffFrame) / range;
		mCurrFrame = mAnimStart + (offset % range);
	}
}

// キーボード入力処理(オーバーライド)
// TODO: マジックナンバーの除去(汎用的な実装にする)
void AnimSpriteComponent::ProcessInput(const uint8_t* keyState) {
	SpriteComponent::ProcessInput(keyState);
	// 同時押しは停止
	if (keyState[SDL_SCANCODE_LEFT] && keyState[SDL_SCANCODE_RIGHT]) {
		Set_AnimStart(6);
		Set_AnimEnd(8);
		Set_CurrFrame(6);
	}
	// 左キー
	else if (keyState[SDL_SCANCODE_LEFT] && mAnimStart != 3) {
		Set_AnimStart(3);
		Set_AnimEnd(5);
		Set_CurrFrame(3);
	}
	// キー
	else if (keyState[SDL_SCANCODE_RIGHT] && mAnimStart != 9) {
		Set_AnimStart(9);
		Set_AnimEnd(11);
		Set_CurrFrame(9);
	}
	// キーを押していないときの処理
	else if (mAnimStart == 3 && !keyState[SDL_SCANCODE_LEFT]){
		Set_AnimStart(6);
		Set_AnimEnd(8);
		Set_CurrFrame(6);
	}
	else if (mAnimStart == 9 && !keyState[SDL_SCANCODE_RIGHT]) {
		Set_AnimStart(6);
		Set_AnimEnd(8);
		Set_CurrFrame(6);
	}
}

// 描画(オーバーライド)
void AnimSpriteComponent::Draw(SDL_Renderer* renderer) {
	int SizeX = mTexWidth / lenX;
	int SizeY = mTexHeight / lenY;

	if (mTexture) {
		// 描画先の取得
		SDL_Rect r_dst;
		r_dst.w = SizeX * mOwner->Get_Scale(); // タイル幅
		r_dst.h = SizeY * mOwner->Get_Scale(); // タイル高さ
		r_dst.x = static_cast<int>(mOwner->Get_Position().x) - r_dst.w / 2;
		r_dst.y = static_cast<int>(mOwner->Get_Position().y) - r_dst.h / 2;

		// 描画元の取得(テクスチャからフェッチ)
		SDL_Rect r_src;
		r_src.w = SizeX;
		r_src.h = SizeY;
		// 矩形の中心位置を取得
		r_src.x = r_src.w * (int(mCurrFrame) % lenX);
		r_src.y = int(mCurrFrame) / (lenY-1) * r_src.h;
		// 指定したレンダリングコンテキスト(renderer)にテクスチャを描画
		SDL_RenderCopyEx(
			renderer,
			mTexture,
			&r_src,
			&r_dst,
			-Math::Rad2Deg(mOwner->Get_Rotation()),
			nullptr,
			SDL_FLIP_NONE);

		//// DEGUG: 交差判定円の描画
		//float x = mOwner->Get_Position().x;
		//float y = mOwner->Get_Position().y - 10.0f;
		//SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
		//DrawCircle(renderer, 8, Vec2(x, y), false);
		//SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		//DrawCircle(renderer, 2, Vec2(x, y));
	}
}

// アニメーションを変更(範囲とフレームレートとループの有無を指定)
void AnimSpriteComponent::Change_Anim(float start, float end, float fps, bool flag) {
	Set_AnimStart(start);
	Set_AnimEnd(end);
	Set_AnimFPS(fps);
	Set_CurrFrame(start);
	Set_mIsAnimLoop(flag);
}