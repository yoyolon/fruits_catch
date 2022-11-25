#pragma once

#include <cstdint>

// �R���|�[�l���g
class Component {
public:
	Component(class Actor* owner, int updateOrder=100);
	virtual ~Component();
	// �R���|�[�l���g�̍X�V
	virtual void Update(float deltaTime);
	// ���͏���
	virtual void ProcessInput(const uint8_t* keyState);

	// �X�V�����̎擾
	int Get_UpdateOrder() const { return mUpdateOrder; }

// 
protected:
	// ���L��
	class Actor* mOwner;
	// �X�V����
	int mUpdateOrder;
};
