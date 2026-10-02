#include "Enemy.h"

void Enemy::Initialize(Model* model)
{
	model_ = model;
	worldTransform_.Initialize();

	// 初期回転
	worldTransform_.rotation_.y = std::numbers::pi_v<float> / 2.0f;
	worldTransform_.translation_ = {10.0f, -3.0f, 0};
}

void Enemy::Update() 
{
	if (!isAlive_) {
		return;
	}


	//====================
	// 重力計算
	//====================
	velocity_.y += gravity_;
	worldTransform_.translation_.y += velocity_.y;

	//====================
	// 地面判定&&重力判定
	//====================
	if (worldTransform_.translation_.y <= groundY) {
		worldTransform_.translation_.y = groundY;
		velocity_.y = 0.0f;
		isGround_ = true;
	}
	worldTransform_.UpdateMatrix();

}

void Enemy::Draw(Camera& camera)
{
	if (!isAlive_) {
		return;
	}

	model_->Draw(worldTransform_, camera);
}

void Enemy::Kill() 
{
	if (!isAlive_)
	{
		return;
	}

	isAlive_ = false;

	//死亡した瞬間のフラグ
	deathFlag_ = true;
}


