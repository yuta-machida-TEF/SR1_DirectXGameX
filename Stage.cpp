#include "Stage.h"

void Stage::Initialize(Model* model) {

	model_ = model;

	for (int y = 0; y < kMapHeight; y++) {
		for (int x = 0; x < kMapWidth; x++) {

			worldTransform_[y][x].Initialize();

			worldTransform_[y][x].translation_ = {-15.0f + x * 1.0f, 8.0f - y * 1.0f, 0.0f};

			worldTransform_[y][x].UpdateMatrix();
		}
	}
}

void Stage::Update() {}

void Stage::Draw(Camera& camera) {

	for (int y = 0; y < kMapHeight; y++) {
		for (int x = 0; x < kMapWidth; x++) {

			if (mapData_[y][x] == 1) {
				model_->Draw(worldTransform_[y][x], camera);
			}
		}
	}
}

const WorldTransform& Stage::GetWorldTransform(int y, int x) const { return worldTransform_[y][x]; }

const Vector3& Stage::GetPlatformSize() const { return platformSize_; }

Stage::~Stage() {}