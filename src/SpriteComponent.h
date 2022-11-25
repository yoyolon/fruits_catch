#pragma once

#include <SDL.h>
#include "Component.h"
#include "Math.h"

// �X�v���C�g�N���X(�摜������)
class SpriteComponent : public Component {
public:
	SpriteComponent(class Actor* owner, int drawOrder=100);
	~SpriteComponent();

	virtual void Draw(SDL_Renderer* renderer);

	// �Z�b�^
	virtual void Set_Texture(SDL_Texture* texture);
	// �Q�b�^
	int Get_DrawOrder() const { return mDrawOrder; }
	int Get_TexHeight() const { return mTexHeight; }
	int Get_TexWidth() const { return mTexWidth; }

protected:
	SDL_Texture* mTexture;
	int mDrawOrder;
	int mTexWidth;
	int mTexHeight;
};