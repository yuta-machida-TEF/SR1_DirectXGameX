#include <KamataEngine.h>
#include <numbers>

using namespace KamataEngine;

#pragma once
class Enemy2 
{
public:
	// 初期化
	void Initialize(Model* model);

	// 更新
	void Update();

	// 描画
	void Draw(Camera& camera);

	void Kill();

	const WorldTransform& GetWorldTransform() const { return worldTransform_; }

	const Vector3& GetSize() const { return size_; }

	bool IsAlive() const { return isAlive_; }

private:
	// モデル
	Model* model_ = nullptr;

	// 落下速度
	Vector2 velocity_ = {0.0f, 0.0f};

	// 重力
	const float gravity_ = -0.020f;

	// 地面にいるか
	bool isGround_ = true;

	// 敵が生きているか
	bool isAlive_ = true;



	// 地面の高さ
	const float groundY = -7.0f;

	Vector3 size_ = {1.0f, 1.0f, 1.0f};

	// ワールド変換
	WorldTransform worldTransform_;
};
