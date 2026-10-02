#include "Particle.h"
#include <algorithm>
#include <math/MathUtility.h>
using namespace MathUtility;

void Particle::Initialize(Model* model, Vector3 position, Vector3 velocity) {
	// NuLLポインタチェック
	assert(model);

	// 引数をメンバー変数として受け取るところ
	model_ = model;
	velocity_ = velocity;

	// 大きさ
	worldTransform_.scale_ = {1.0f, 1.0f, 1.0f};

	// ワールドトランスフォームの初期化
	worldTransform_.translation_ = position;

	worldTransform_.Initialize();

	// 色の設定
	color_ = {1, 1, 0, 1};
}

void Particle::Update() {
	// 終了なら何もしない
	if (isFinished_) {
		return;
	}

	// カウントを1フレームを秒数で進める
	counter_ += 1.0f / 60.0f;

	// 存続時間に上限に達したら
	if (counter_ >= kDuration) {
		counter_ += kDuration;
		// 終了フラグ
		isFinished_ = true;
	}

	// フェード処理
	color_.w = std::clamp(1.0f - counter_ / kDuration, 0.0f, 1.0f);

	// 行列を定数バッファに転送
	worldTransform_.TransferMatrix();

	worldTransform_.UpdateMatrix();

	

	worldTransform_.translation_ += velocity_;
}

void Particle::Draw(Camera& camera) {
	// 3Dモデルを描画
	model_->Draw(worldTransform_, camera);
}