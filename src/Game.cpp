#include <algorithm>
#include <sstream>
#include <iomanip>
#include <SDL2/SDL_image.h>
#include "Game.h"
#include "Actor.h"
#include "Fruits.h"
#include "Player.h"
#include "FruitsGenerator.h"
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

// ゲームの初期化
bool Game::Initialize() {
	// SDLライブラリの初期化
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
		SDL_Log("Cannot initialize SDL: %s", SDL_GetError());
		return false;
	}
	// SDL_imageライブラリの初期化
	if (IMG_Init(IMG_INIT_PNG) == 0) {
		SDL_Log("Cannot initialize SDL_image: %s", SDL_GetError());
		return false;
	}
	// ウィンドウ初期化
	mWindow = SDL_CreateWindow("Chapter2", 100, 100, WINDOWWIDTH, WINDOWHEIGHT, 0);
	if (!mWindow) {
		SDL_Log("Failed to create window: %s", SDL_GetError());
		return false;
	}
	// レンダラーの初期化
	mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!mRenderer) {
		SDL_Log("Failed to create renderer: %s", SDL_GetError());
		return false;
	}

	// アセットの読み込み
	LoadData();

	// ライブラリ初期化からの時間を取得
	mTicksCount = SDL_GetTicks();
	return true;
}

// ゲームの終了
void Game::Shutdown() {
	UnloadData();
	IMG_Quit();
	SDL_DestroyRenderer(mRenderer);
	SDL_DestroyWindow(mWindow);
	SDL_Quit();
}

// ゲームループの実行
void Game::RunLoop() {
	while (mIsRunning) {
		ProcessInput();
		UpdateGame();
		GenerateOutput();
	}
}

// 入力データの処理
void Game::ProcessInput() {
	SDL_Event event;
	// 全イベントを取得して処理
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			mIsRunning = false;
			break;
		}
	}

	// キーボード入力を取得して処理
	const uint8_t* keyState = SDL_GetKeyboardState(NULL); // キーボード全体の状態
	// Escキーが押されている場合
	if (keyState[SDL_SCANCODE_ESCAPE]) {
		mIsRunning = false;
	}

	// 全アクターの入力処理
	mUpdatingActors = true;
	for (auto actor : mActors) {
		actor->ProcessInput(keyState);
	}
	mUpdatingActors = false;
}

// ゲームの更新
void Game::UpdateGame() {
	// 16msまで待機
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16));
	// デルタタイムの計算(単位: 秒)
	float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;
	deltaTime = (deltaTime > 0.05f) ? 0.05f : deltaTime;
	mTicksCount = SDL_GetTicks(); 

	// 全アクターの更新
	mUpdatingActors = true; // アクターの更新の有無
	for (auto actor : mActors) {
		actor->Update(deltaTime);
	}
	mUpdatingActors = false;

	// 保留アクターをアクターに移動
	for (auto pending : mPendingActors) {
		mActors.emplace_back(pending);
	}
	mPendingActors.clear();

	// EDead状態のアクターを削除
	std::vector<Actor*> deadActors;
	for (auto actor : mActors) {
		if (actor->Get_State() == Actor::EDead) {
			deadActors.emplace_back(actor);
		}
	}
	for (auto actor : deadActors) {
		delete actor;
	}
}

// 出力データの生成(ディスプレイへの描画)
void Game::GenerateOutput() {
	// バックバッファを単色でクリア
	SDL_SetRenderDrawColor(mRenderer, 220, 220, 220, 255);
	SDL_RenderClear(mRenderer);

	// 全スプライトをバックバッファに描画
	for (auto sprite : mSprites) {
		sprite->Draw(mRenderer);
	}

	// フロントバッファとバックバッファを交換
	SDL_RenderPresent(mRenderer);
}

// データの作成・読み込み
void Game::LoadData() {
	// プレイヤーの作成
	mPlayer = new Player(this);
	mPlayer->Set_Position(Vec2(WINDOWWIDTH/2, WINDOWHEIGHT - 64));
	mPlayer->Set_Scale(2.0f);

	// フルーツジェネレータの生成
	mGenerator = new FruitsGenerator(this);

	// フルーツの作成
	constexpr int numFruitss = 1;
	for (int i = 0; i < numFruitss; i++) {
		new Fruits(this);
	}

	// 背景の作成
	Actor* actbg = new Actor(this);
	actbg->Set_Position(Vec2(WINDOWWIDTH / 2, WINDOWHEIGHT / 2));
	SpriteComponent* bg = new SpriteComponent(actbg, 10);
	bg->Set_Texture(GetTexture("Assets/bg.png"));
}

// データの解放
void Game::UnloadData() {
	// アクターの削除
	// ~Actor(デストラクタ)がRemoveActorを呼び出すので別のループを使用
	while (!mActors.empty()) {
		delete mActors.back();
	}

	// テクスチャの削除
	for (auto& tex : mTextures) {
		SDL_DestroyTexture(tex.second);
	}
	mTextures.clear();
}

// テクスチャの取得
SDL_Texture* Game::GetTexture(const std::string& fileName) {
	SDL_Texture* tex = nullptr;
	// テクスチャが読み込み済み
	auto itr = mTextures.find(fileName);
	if (itr != mTextures.end()) {
		tex = itr->second; // テクスチャへのポインタを取得
	}
	else {
		// 画像ファイルの読み込み(SDL_Surfaceはバッファ)
		SDL_Surface* surf = IMG_Load(fileName.c_str());
		if (!surf) {
			SDL_Log("Failed to load texture: %s", fileName.c_str());
			return nullptr;
		}

		// テクスチャをバッファから生成
		tex = SDL_CreateTextureFromSurface(mRenderer, surf);
		SDL_FreeSurface(surf); // バッファのメモリを解放
		if (!tex) {
			SDL_Log("Failed to convert surface to texture for %s", fileName.c_str());
			return nullptr;
		}
		// 連想配列にテクスチャを追加
		mTextures.emplace(fileName, tex);
	}
	return tex;
}

// フルーツ(敵)の追加
void Game::AddFruits(Fruits* ast) {
	mFruits.emplace_back(ast);
}

// フルーツ(敵)の削除
void Game::RemoveFruits(Fruits* ast) {
	// 削除対象をフルーツ配列から除外
	auto itr = std::find(mFruits.begin(), mFruits.end(), ast);
	if (itr != mFruits.end()) {
		mFruits.erase(itr);
	}
}

// アクターの追加
void Game::AddActor(Actor* actor) {
	// アクターが更新中の場合，保留に追加
	if (mUpdatingActors) {
		mPendingActors.emplace_back(actor);
	}
	else {
		mActors.emplace_back(actor);
	}
	
}

// アクターの削除
void Game::RemoveActor(Actor* actor) {
	// 削除対象を保留アクター配列から除外
	auto itr = std::find(mPendingActors.begin(), mPendingActors.end(), actor);
	if (itr != mPendingActors.end()) {
		mPendingActors.erase(itr);		
	}
	// 削除対象をアクター配列から除外
	itr = std::find(mActors.begin(), mActors.end(), actor);
	if (itr != mActors.end()) {
		mActors.erase(itr);
	}
}

// スプライトの追加
void Game::AddSprite(SpriteComponent* sprite) {
	// 追加するスプライトの描画順
	int myDrawOrder = sprite->Get_DrawOrder();
	// 描画順に基づき配列に格納
	auto itr = mSprites.begin();
	while (itr != mSprites.end()) {
		if (myDrawOrder < (*itr)->Get_DrawOrder()) break;
		itr++;
	}
	// スプライトの挿入
	mSprites.insert(itr, sprite);
}

// スプライトの削除
void Game::RemoveSprite(SpriteComponent* sprite) {
	auto itr = std::find(mSprites.begin(), mSprites.end(), sprite);
	if (itr != mSprites.end()) {
		mSprites.erase(itr);
	}
}

// 得点の取得
int Game::Get_Score() const { return mPlayer->Get_Score(); }
