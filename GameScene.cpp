#include "GameScene.h"
#include <algorithm>
#include<numbers>
#include<cmath>

using namespace KamataEngine;

// デストラクタ
GameScene::~GameScene() {
	delete player_;
	delete modelPlayer_;
	delete stage_;
	delete modelBlock_;
	delete modelEnemy_;
	delete modelEnemy2_;
	delete modelParticle_;

	for (Particle* particle : particles_) {
		delete particle;
	}
}

// 初期化
void GameScene::Initialize() 
{

	// 3Dモデルの生成
	modelPlayer_ = Model::CreateFromOBJ("player");
	modelEnemy_ = Model::CreateFromOBJ("enemy");
	modelBlock_ = Model::CreateFromOBJ("block");
	modelEnemy2_ = Model::CreateFromOBJ("enemy");

	// パーティクル用モデル
	modelParticle_ = Model::CreateFromOBJ("deathParticle");

	assert(modelParticle_);

	// カメラの初期化
	camera_.translation_ = {0, 0, -20};
	camera_.Initialize();

	player_ = new Player();
	player_->Initialize(modelPlayer_);

	enemy_ = new Enemy();
	enemy_->Initialize(modelEnemy_);

	enemy2_ = new Enemy2();
	enemy2_->Initialize(modelEnemy2_);

	stage_ = new Stage();
	stage_->Initialize(modelBlock_);
}

// 更新
void GameScene::Update() {

	// プレイヤー更新
	player_->Update(stage_, enemy_, enemy2_);

	//========================================
	// 敵1が倒された瞬間
	//========================================

	if (enemyWasAlive_ && !enemy_->IsAlive()) {

		Vector3 position = enemy_->GetWorldTransform().translation_;

		CreateParticles(position);
	}

	// 現在の敵1の生存状態を保存
	enemyWasAlive_ = enemy_->IsAlive();

	//========================================
	// 敵2が倒された瞬間
	//========================================

	if (enemy2WasAlive_ && !enemy2_->IsAlive()) {

		Vector3 position = enemy2_->GetWorldTransform().translation_;

		CreateParticles(position);
	}

	// 現在の敵2の生存状態を保存
	enemy2WasAlive_ = enemy2_->IsAlive();

	//========================================
	// その他の更新
	//========================================

	stage_->Update();

	enemy_->Update();

	enemy2_->Update();

	//========================================
	// パーティクル更新
	//========================================

	for (Particle* particle : particles_) {
		particle->Update();
	}

	//========================================
	// 終了したパーティクルを削除
	//========================================

	particles_.erase(
	    std::remove_if(
	        particles_.begin(), particles_.end(),
	        [](Particle* particle) {
		        if (particle->IFinished()) {

			        delete particle;

			        return true;
		        }

		        return false;
	        }),
	    particles_.end());
}

// パーティクル生成
void GameScene::CreateParticles(const KamataEngine::Vector3& position) {

	const int particleCount = 12;

	const float speed = 0.08f;

	for (int i = 0; i < particleCount; i++) {

		Particle* particle = new Particle();

		const float angle = 2.0f * std::numbers::pi_v<float> * static_cast<float>(i) / static_cast<float>(particleCount);

		Vector3 velocity = {std::cos(angle) * speed, std::sin(angle) * speed + 0.05f, 0.0f};

		particle->Initialize(modelParticle_, position, velocity);

		particles_.push_back(particle);
	}
}

// 描画
void GameScene::Draw() {

	// DirectXCommonインスタンスの取得
	DirectXCommon* dxCommon = DirectXCommon::GetInstance();

	// スプライト描画前処理
	Sprite::PreDraw(dxCommon->GetCommandList());

	Sprite::PostDraw();

	// 深度バッファクリア
	dxCommon->ClearDepthBuffer();

	// 3Dモデル描画前処理
	Model::PreDraw();

	// プレイヤー
	player_->Draw(camera_);

	// 敵
	enemy_->Draw(camera_);
	enemy2_->Draw(camera_);

	// ステージ
	stage_->Draw(camera_);

	// パーティクル
	for (Particle* particle : particles_) {
		particle->Draw(camera_);
	}

	// 3Dモデル描画後処理
	Model::PostDraw();

	// スプライト描画前処理
	Sprite::PreDraw(dxCommon->GetCommandList());

	Sprite::PostDraw();
}