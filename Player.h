#pragma once

#include <KamataEngine.h>
#include"Stage.h"
#include"Particle.h"
#include <numbers>

using namespace KamataEngine;

class Enemy;

class Enemy2;

class Player {
public:

	// パーティクル3Dモデルデータ
	Model* modelParticle_ = nullptr;
	// パーティクル
	std::list<Particle*> particles_;

	~Player();

	// 初期化
	void Initialize(Model* model);

	// 更新
	void Update(Stage* stage,Enemy* enemy,Enemy2* enemy2);

	// 描画
	void Draw(Camera& camera);

	bool CheckCollision(const KamataEngine::WorldTransform& platform, const KamataEngine::Vector3& platformSize,
		                const KamataEngine::Vector3& previousPosition);

	bool CheckEnemyCollision(const KamataEngine::WorldTransform& enemy, const KamataEngine::Vector3& enemySize, 
		                     const KamataEngine::Vector3& previousPosition, Enemy* enemyObject);

	bool CheckEnemy2Collision(const KamataEngine::WorldTransform& enemy2, const KamataEngine::Vector3& enemySize,
		                     const KamataEngine::Vector3& previousPosition, Enemy2* enemyObject2);

	const WorldTransform& GetWorldTransform() const { return worldTransform_; }

private:
	// モデル
	Model* model_ = nullptr;

	// 落下速度
	Vector2 velocity_ = {0.0f, 0.0f};

	// 重力
	const float gravity_ = -0.020f;

	// 地面にいるか
	bool isGround_ = true;

	// 地面の高さ
	const float groundY = -7.0f;

	float previousBottom_ = 0.0f;

	// ジャンプ力
	const float jumpPower_ = 0.38f;

	const float moveSpeed_ = 0.20f;

	 // プレイヤーが生きているか
    bool isAlive_ = true;

	// ワールド変換
	WorldTransform worldTransform_;
};