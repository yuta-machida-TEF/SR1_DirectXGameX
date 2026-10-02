#include <Windows.h>
#include<KamataEngine.h>
#include"GameScene.h"

using namespace KamataEngine;

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) {
	
	//エンジンの更新
	KamataEngine::Initialize(L"TD3_LE3D_23_マチダ_ユウタ");

	//DirectXCommonインスタンスの取得
	DirectXCommon* dxCommon = DirectXCommon::GetInstance();

	//ゲームシーン
	GameScene* gameScene = new GameScene();

	gameScene->Initialize();

	//メインループ
	while (true)
	{
		//エンジンの更新
		if (KamataEngine::Update()) {
			break;
		}

		gameScene->Update();

		

		//描画開始
		dxCommon->PreDraw();

		
		gameScene->Draw();

		//描画終了
		dxCommon->PostDraw();

	}

	//エンジンの終了処理
	KamataEngine::Finalize();

	return 0;
}
