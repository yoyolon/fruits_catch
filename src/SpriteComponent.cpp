#include "SpriteComponent.h"
#include "Actor.h"
#include "Game.h"

// �R���X�g���N�^
SpriteComponent::SpriteComponent(Actor* owner, int drawOrder)
	:Component(owner),
	 mTexture(nullptr),
	 mDrawOrder(drawOrder),
	 mTexWidth(0),
	 mTexHeight(0)
{
	mOwner->Get_Game()->AddSprite(this);
}

// �f�X�g���N�^
SpriteComponent::~SpriteComponent() {
	mOwner->Get_Game()->RemoveSprite(this);
}

// �R���|�[�l���g�̕`��
void SpriteComponent::Draw(SDL_Renderer* renderer) {
	if (mTexture) {
		SDL_Rect r; // �����`
		// �X�P�[�����O
		r.w = static_cast<int>(mTexWidth * mOwner->Get_Scale());
		r.h = static_cast<int>(mTexHeight * mOwner->Get_Scale());
		// �ʒu�𒷕��`�̒�����
		r.x = static_cast<int>(mOwner->Get_Position().x - r.w / 2);
		r.y = static_cast<int>(mOwner->Get_Position().y - r.h / 2);
		// �w�肵�������_�����O�R���e�L�X�g(renderer)�Ƀe�N�X�`���`��
		SDL_RenderCopyEx(
			renderer,
			mTexture,
			nullptr,
			&r,
			0,
			nullptr,
			SDL_FLIP_NONE);

		// DEBUG: ��������~�̕`��
		//float x = mOwner->Get_Position().x;
		//float y = mOwner->Get_Position().y;
		//SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
		//DrawCircle(renderer, 8, Vec2(x, y), false);
		//SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		//DrawCircle(renderer, 2, Vec2(x, y));
	}
}

// �e�N�X�`�����Z�b�g
void SpriteComponent::Set_Texture(SDL_Texture* texture) {
	mTexture = texture;
	// �e�N�X�`���̕��ƍ�����ݒ�
	SDL_QueryTexture(texture, nullptr, nullptr, &mTexWidth, &mTexHeight);
}