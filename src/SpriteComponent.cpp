#include "SpriteComponent.h"
#include "Actor.h"
#include "Game.h"

// コンストラクタ
SpriteComponent::SpriteComponent(Actor* owner, int drawOrder)
	:Component(owner),
	 mTexture(nullptr),
	 mDrawOrder(drawOrder),
	 mTexWidth(0),
	 mTexHeight(0)
{
	mOwner->Get_Game()->AddSprite(this);
}

// デストラクタ
SpriteComponent::~SpriteComponent() {
	mOwner->Get_Game()->RemoveSprite(this);
}

// コンポーネントの描画
void SpriteComponent::Draw(SDL_Renderer* renderer) {
	if (mTexture) {
		SDL_Rect r; // 長方形
		// スケーリング
		r.w = static_cast<int>(mTexWidth * mOwner->Get_Scale());
		r.h = static_cast<int>(mTexHeight * mOwner->Get_Scale());
		// 位置を長方形の中央に
		r.x = static_cast<int>(mOwner->Get_Position().x - r.w / 2);
		r.y = static_cast<int>(mOwner->Get_Position().y - r.h / 2);
		// 指定したレンダリングコンテキスト(renderer)にテクスチャ描画
		SDL_RenderCopyEx(
			renderer,
			mTexture,
			nullptr,
			&r,
			0,
			nullptr,
			SDL_FLIP_NONE);

		// DEBUG: 交差判定円の描画
		//float x = mOwner->Get_Position().x;
		//float y = mOwner->Get_Position().y;
		//SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
		//DrawCircle(renderer, 8, Vec2(x, y), false);
		//SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		//DrawCircle(renderer, 2, Vec2(x, y));
	}
}

// テクスチャをセット
void SpriteComponent::Set_Texture(SDL_Texture* texture) {
	mTexture = texture;
	// テクスチャの幅と高さを設定
	SDL_QueryTexture(texture, nullptr, nullptr, &mTexWidth, &mTexHeight);
}