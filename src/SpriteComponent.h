#pragma once

#include <SDL.h>
#include "Component.h"
#include "Math.h"

// スプライトクラス(画像を扱う)
class SpriteComponent : public Component {
public:
	SpriteComponent(class Actor* owner, int drawOrder=100);
	~SpriteComponent();

	virtual void Draw(SDL_Renderer* renderer);

	// セッタ
	virtual void Set_Texture(SDL_Texture* texture);
	// ゲッタ
	int Get_DrawOrder() const { return mDrawOrder; }
	int Get_TexHeight() const { return mTexHeight; }
	int Get_TexWidth() const { return mTexWidth; }

protected:
	SDL_Texture* mTexture;
	int mDrawOrder;
	int mTexWidth;
	int mTexHeight;
};