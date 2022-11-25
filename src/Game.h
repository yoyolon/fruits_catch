#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include <SDL.h>


constexpr int WINDOW_WIDTH  = 640;
constexpr int WINDOW_HEIGHT = 480;

// ゲームの進行を行う
class Game {
public:
	Game();
	// 基本メソッド
	bool Initialize();
	void RunLoop();
	void Shutdown();
	// アクター関連
	void AddActor(class Actor* actor);
	void RemoveActor(class Actor* actor);
	// プレイヤー関連
	int Get_Score() const;
	// フルーツ関連
	void AddFruits(class Fruits* ast);
	void RemoveFruits(class Fruits* ast);
	std::vector<class Fruits*>& Get_Fruits() { return mFruits; }
	// スプライト(画像)関連
	void AddSprite(class SpriteComponent* sprite);
	void RemoveSprite(class SpriteComponent* sprite);
	// テクスチャの取得
	SDL_Texture* GetTexture(const std::string& fileName);

private:
	// メソッド
	void ProcessInput();   // 入力データの処理
	void UpdateGame();     // ゲームワールドの更新
	void GenerateOutput(); // 出力データの生成
	void LoadData();	   // データの生成・読み込み
	void UnloadData();	   // データの解放

	// テクスチャを保存する連想配列
	std::unordered_map<std::string, SDL_Texture*> mTextures;
	// ゲーム中の全アクター
	std::vector<class Actor*> mActors;
	// アクター新規追加用
	std::vector<class Actor*> mPendingActors;
	// 描画対象の全スプライト
	std::vector<class SpriteComponent*> mSprites;
	
	SDL_Window* mWindow;
	SDL_Renderer* mRenderer;
	Uint32 mTicksCount;
	bool mIsRunning;
	bool mUpdatingActors; // アクターを更新するか
	class Player* mPlayer; // プレイヤー
	class FruitsGenerator* mGenerator; // フルーツ生成
	std::vector<class Fruits*> mFruits; // フルーツ
};