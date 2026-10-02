#include "Enemy2.h"

void Enemy2::Initialize(Model* model) {
	model_ = model;
	worldTransform_.Initialize();

	// 初期回転
	worldTransform_.rotation_.y = std::numbers::pi_v<float> / 2.0f;
	worldTransform_.translation_ = {7.0f, 3.0f, 0};
}

void Enemy2::Update() {

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

void Enemy2::Draw(Camera& camera) 
{
	if (!isAlive_) {
		return;
	}

	model_->Draw(worldTransform_, camera);
}

void Enemy2::Kill() { isAlive_ = false; }