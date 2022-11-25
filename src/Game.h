#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include <SDL.h>


constexpr int WINDOW_WIDTH  = 640;
constexpr int WINDOW_HEIGHT = 480;

// �Q�[���̐i�s���s��
class Game {
public:
	Game();
	// ��{���\�b�h
	bool Initialize();
	void RunLoop();
	void Shutdown();
	// �A�N�^�[�֘A
	void AddActor(class Actor* actor);
	void RemoveActor(class Actor* actor);
	// �v���C���[�֘A
	int Get_Score() const;
	// �t���[�c�֘A
	void AddFruits(class Fruits* ast);
	void RemoveFruits(class Fruits* ast);
	std::vector<class Fruits*>& Get_Fruits() { return mFruits; }
	// �X�v���C�g(�摜)�֘A
	void AddSprite(class SpriteComponent* sprite);
	void RemoveSprite(class SpriteComponent* sprite);
	// �e�N�X�`���̎擾
	SDL_Texture* GetTexture(const std::string& fileName);

private:
	// ���\�b�h
	void ProcessInput();   // ���̓f�[�^�̏���
	void UpdateGame();     // �Q�[�����[���h�̍X�V
	void GenerateOutput(); // �o�̓f�[�^�̐���
	void LoadData();	   // �f�[�^�̐����E�ǂݍ���
	void UnloadData();	   // �f�[�^�̉��

	// �e�N�X�`����ۑ�����A�z�z��
	std::unordered_map<std::string, SDL_Texture*> mTextures;
	// �Q�[�����̑S�A�N�^�[
	std::vector<class Actor*> mActors;
	// �A�N�^�[�V�K�ǉ��p
	std::vector<class Actor*> mPendingActors;
	// �`��Ώۂ̑S�X�v���C�g
	std::vector<class SpriteComponent*> mSprites;
	
	SDL_Window* mWindow;
	SDL_Renderer* mRenderer;
	Uint32 mTicksCount;
	bool mIsRunning;
	bool mUpdatingActors; // �A�N�^�[���X�V���邩
	class Player* mPlayer; // �v���C���[
	class FruitsGenerator* mGenerator; // �t���[�c����
	std::vector<class Fruits*> mFruits; // �t���[�c
};