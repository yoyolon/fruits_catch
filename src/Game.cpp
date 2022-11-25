#include "Game.h"
#include <algorithm>
#include <iomanip>
#include <sstream>
#include <SDL2/SDL_image.h>
#include "Actor.h"
#include "Fruits.h"
#include "FruitsGenerator.h"
#include "Player.h"
#include "SpriteComponent.h"

Game::Game() 
	: mWindow(nullptr), 
	  mRenderer(nullptr),
	  mIsRunning(true),
	  mUpdatingActors(false),
	  mGenerator(nullptr),
	  mPlayer(nullptr),
	  mTicksCount(0)
{}


// �Q�[���̏�����
bool Game::Initialize() {
	// SDL���C�u�����̏�����
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
		SDL_Log("Cannot initialize SDL: %s", SDL_GetError());
		return false;
	}
	// SDL_image���C�u�����̏�����
	if (IMG_Init(IMG_INIT_PNG) == 0) {
		SDL_Log("Cannot initialize SDL_image: %s", SDL_GetError());
		return false;
	}
	// �E�B���h�E������
	mWindow = SDL_CreateWindow("Chapter2", 100, 100, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
	if (!mWindow) {
		SDL_Log("Failed to create window: %s", SDL_GetError());
		return false;
	}
	// �����_���[�̏�����
	mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!mRenderer) {
		SDL_Log("Failed to create renderer: %s", SDL_GetError());
		return false;
	}

	LoadData();
	mTicksCount = SDL_GetTicks();
	return true;
}


// �Q�[���̏I��
void Game::Shutdown() {
	UnloadData(); // �������̉��
	IMG_Quit();
	SDL_DestroyRenderer(mRenderer);
	SDL_DestroyWindow(mWindow);
	SDL_Quit();
}


// �Q�[�����[�v�̎��s
void Game::RunLoop() {
	while (mIsRunning) {
		ProcessInput();
		UpdateGame();
		GenerateOutput();
	}
}


// ���̓f�[�^�̏���
void Game::ProcessInput() {
	SDL_Event event;
	// �S�C�x���g���擾���ď���
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			mIsRunning = false;
			break;
		default:
			break;
		}
	}
	// �L�[�{�[�h���͂��擾���ď���
	const uint8_t* keyState = SDL_GetKeyboardState(NULL); // �L�[�{�[�h�S�̂̏��
	if (keyState[SDL_SCANCODE_ESCAPE]) {
		mIsRunning = false;
	}
	// �S�A�N�^�[�̓��͏���
	mUpdatingActors = true;
	for (auto actor : mActors) {
		actor->ProcessInput(keyState);
	}
	mUpdatingActors = false;
}


// �Q�[���̍X�V
void Game::UpdateGame() {
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16)); // �t���[�����Ԓ���

	// �f���^�^�C���̌v�Z(�P��: �b)
	float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;
	deltaTime = (deltaTime > 0.05f) ? 0.05f : deltaTime; // �ő�l�𐧌�
	mTicksCount = SDL_GetTicks(); 

	// �S�A�N�^�[�̍X�V
	mUpdatingActors = true; // �A�N�^�[�̍X�V�̗L��
	for (auto actor : mActors) {
		actor->Update(deltaTime);
	}
	mUpdatingActors = false;
	// �ۗ��A�N�^�[���A�N�^�[�Ɉړ�
	for (auto pending : mPendingActors) {
		mActors.emplace_back(pending);
	}
	mPendingActors.clear();
	// State::Dead��Ԃ̃A�N�^�[���폜
	std::vector<Actor*> deadActors;
	for (auto actor : mActors) {
		if (actor->Get_State() == Actor::State::Dead) {
			deadActors.emplace_back(actor);
		}
	}
	for (auto actor : deadActors) {
		delete actor;
	}
}


// �f�B�X�v���C�ւ̏o��
void Game::GenerateOutput() {
	// �o�b�N�o�b�t�@��P�F�ŃN���A
	SDL_SetRenderDrawColor(mRenderer, 220, 220, 220, 255);
	SDL_RenderClear(mRenderer);

	// �S�X�v���C�g���o�b�N�o�b�t�@�ɕ`��
	for (auto sprite : mSprites) {
		sprite->Draw(mRenderer);
	}

	// �o�b�N�o�b�t�@���f�B�X�v���C�ɕ\��
	SDL_RenderPresent(mRenderer);
}


// �f�[�^�̃������m��
void Game::LoadData() {
	// �v���C���[�̍쐬
	mPlayer = new Player(this);
	mPlayer->Set_Position(Vec2(WINDOW_WIDTH/2, WINDOW_HEIGHT - 64));
	mPlayer->Set_Scale(2.0f);

	// �t���[�c�W�F�l���[�^�̐���
	mGenerator = new FruitsGenerator(this);

	// �t���[�c�̍쐬
	constexpr int numFruitss = 2;
	for (int i = 0; i < numFruitss; i++) {
		new Fruits(this);
	}

	// �w�i�̍쐬
	Actor* actbg = new Actor(this);
	actbg->Set_Position(Vec2(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2));
	SpriteComponent* bg = new SpriteComponent(actbg, 10); // �w�i�摜
	bg->Set_Texture(GetTexture("Assets/bg.png"));
}


// �f�[�^�̃��������
void Game::UnloadData() {
	// �A�N�^�[�̍폜
	// ~Actor(�f�X�g���N�^)��RemoveActor���Ăяo���̂ŕʂ̃��[�v���g�p
	while (!mActors.empty()) {
		delete mActors.back();
	}

	// �e�N�X�`���̍폜
	for (auto& tex : mTextures) {
		SDL_DestroyTexture(tex.second);
	}
	mTextures.clear();
}


// �e�N�X�`���̎擾
SDL_Texture* Game::GetTexture(const std::string& fileName) {
	SDL_Texture* tex = nullptr;
	// �e�N�X�`�����ǂݍ��ݍς�
	auto itr = mTextures.find(fileName);
	if (itr != mTextures.end()) {
		tex = itr->second; // �e�N�X�`���ւ̃|�C���^���擾
	}
	else {
		// �摜�t�@�C���̓ǂݍ���(SDL_Surface�̓o�b�t�@)
		SDL_Surface* surf = IMG_Load(fileName.c_str());
		if (!surf) {
			SDL_Log("Failed to load texture: %s", fileName.c_str());
			return nullptr;
		}
		// �e�N�X�`���𐶐�
		tex = SDL_CreateTextureFromSurface(mRenderer, surf);
		SDL_FreeSurface(surf); // �o�b�t�@�̃����������
		if (!tex) {
			SDL_Log("Failed to convert surface to texture for %s", fileName.c_str());
			return nullptr;
		}
		// �A�z�z��Ƀe�N�X�`����ǉ�
		mTextures.emplace(fileName, tex);
	}
	return tex;
}


// �t���[�c�̒ǉ�
void Game::AddFruits(Fruits* frutis) {
	mFruits.emplace_back(frutis);
}


// �t���[�c�̍폜
void Game::RemoveFruits(Fruits* frutis) {
	// �폜�Ώۂ��t���[�c�z�񂩂珜�O
	auto itr = std::find(mFruits.begin(), mFruits.end(), frutis);
	if (itr != mFruits.end()) {
		mFruits.erase(itr);
	}
}


// �A�N�^�[�̒ǉ�
void Game::AddActor(Actor* actor) {
	// �A�N�^�[���X�V���̏ꍇ�C�ۗ��ɒǉ�
	if (mUpdatingActors) {
		mPendingActors.emplace_back(actor);
	}
	else {
		mActors.emplace_back(actor);
	}
	
}


// �A�N�^�[�̍폜
void Game::RemoveActor(Actor* actor) {
	// �폜�Ώۂ�ۗ��A�N�^�[�z�񂩂珜�O
	auto itr = std::find(mPendingActors.begin(), mPendingActors.end(), actor);
	if (itr != mPendingActors.end()) {
		mPendingActors.erase(itr);		
	}
	// �폜�Ώۂ��A�N�^�[�z�񂩂珜�O
	itr = std::find(mActors.begin(), mActors.end(), actor);
	if (itr != mActors.end()) {
		mActors.erase(itr);
	}
}


// �X�v���C�g�̒ǉ�
void Game::AddSprite(SpriteComponent* sprite) {
	// �`�揇�Ɋ�Â��z��ɑ}��
	int myDrawOrder = sprite->Get_DrawOrder();
	auto itr = mSprites.begin();
	while (itr != mSprites.end()) {
		if (myDrawOrder < (*itr)->Get_DrawOrder()) break;
		itr++;
	}
	mSprites.insert(itr, sprite);
}


// �X�v���C�g�̍폜
void Game::RemoveSprite(SpriteComponent* sprite) {
	auto itr = std::find(mSprites.begin(), mSprites.end(), sprite);
	if (itr != mSprites.end()) {
		mSprites.erase(itr);
	}
}


// ���_�̎擾
int Game::Get_Score() const { return mPlayer->Get_Score(); }
