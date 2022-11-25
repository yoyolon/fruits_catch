#pragma once

#include <vector>
#include "Actor.h"
#include "SpriteComponent.h"

// 1���̉摜�ɂ��A�j���[�V����
class AnimSpriteComponent : public SpriteComponent {
public:
	AnimSpriteComponent(class Actor* owner, int x, int y, int drawOrder = 100);
	// �I�[�o�[���C�h
	void Update(float deltaTime) override;
	void Draw(SDL_Renderer* renderer) override;
	// ���͏���
	void ProcessInput(const uint8_t* keyState) override;
	// �A�j���[�V������ύX
	void Change_Anim(float start, float end, float fps, bool flag = true);
	// �Z�b�^
	void Set_AnimFPS(float fps) { mAnimFPS = fps; }
	void Set_AnimStart(float start) { mAnimStart = start; }
	void Set_AnimEnd(float end) { mAnimEnd = end; }
	void Set_CurrFrame(float frame) { mCurrFrame = frame; }
	void Set_mIsAnimLoop(bool flag) { mIsAnimLoop = flag; }
	// �Q�b�^
	float Get_AnimFPS() const { return mAnimFPS; }

private:
	// �A�j���[�V�����e�N�X�`��
	SDL_Texture* mAnimTextures;
	// �\���t���[��
	float mCurrFrame;
	// �t���[�����[�g
	float mAnimFPS;
	// �A�j���[�V�����͈�
	float mAnimStart, mAnimEnd;
	// ���[�v�̗L��
	bool mIsAnimLoop;
	// �e�N�X�`��������
	int lenX, lenY;
};
