#pragma once

#include <cstdint>

// コンポーネント
class Component {
public:
	Component(class Actor* owner, int updateOrder=100);
	virtual ~Component();
	// コンポーネントの更新
	virtual void Update(float deltaTime);
	// 入力処理
	virtual void ProcessInput(const uint8_t* keyState);

	// 更新順序の取得
	int Get_UpdateOrder() const { return mUpdateOrder; }

// 
protected:
	// 所有者
	class Actor* mOwner;
	// 更新順序
	int mUpdateOrder;
};
