//============================================================
//
//	チュートリアル画面処理 [sceneTutorial.cpp]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	インクルードファイル
//************************************************************
#include "sceneTutorial.h"
#include "manager.h"
#include "sound.h"
#include "camera.h"
#include "tutorialManager.h"

#include "player.h"
#include "stage.h"
#include "wall.h"
#include "scenery.h"
#include "sky.h"

//************************************************************
//	静的メンバ変数宣言
//************************************************************
CTutorialManager *CSceneTutorial::m_pTutorialManager = nullptr;	// チュートリアルマネージャー

//************************************************************
//	子クラス [CSceneTutorial] のメンバ関数
//************************************************************
//============================================================
//	コンストラクタ
//============================================================
CSceneTutorial::CSceneTutorial(const EMode mode) : CScene(mode)
{

}

//============================================================
//	デストラクタ
//============================================================
CSceneTutorial::~CSceneTutorial()
{

}

//============================================================
//	初期化処理
//============================================================
HRESULT CSceneTutorial::Init(void)
{
	//--------------------------------------------------------
	//	チュートリアルの初期化
	//--------------------------------------------------------
	// チュートリアルマネージャーの生成
	m_pTutorialManager = CTutorialManager::Create();
	if (m_pTutorialManager == nullptr)
	{ // 非使用中の場合

		// 失敗を返す
		assert(false);
		return E_FAIL;
	}

	// シーンの初期化
	CScene::Init();

	//--------------------------------------------------------
	//	初期設定
	//--------------------------------------------------------
	// BGMの再生
	GET_MANAGER->GetSound()->Play(CSound::LABEL_BGM_GENERAL);

	// 成功を返す
	return S_OK;
}

//============================================================
//	終了処理
//============================================================
HRESULT CSceneTutorial::Uninit(void)
{
	// チュートリアルマネージャーの破棄
	if (FAILED(CTutorialManager::Release(m_pTutorialManager)))
	{ // 破棄に失敗した場合

		// 失敗を返す
		assert(false);
		return E_FAIL;
	}

	// シーンの終了
	CScene::Uninit();

	// 成功を返す
	return S_OK;
}

//============================================================
//	更新処理
//============================================================
void CSceneTutorial::Update(void)
{
	// デバッグ表示
	GET_MANAGER->GetDebugProc()->Print(CDebugProc::POINT_LEFT, "======================================\n");
	GET_MANAGER->GetDebugProc()->Print(CDebugProc::POINT_LEFT, "　[デバッグ情報]\n");
	GET_MANAGER->GetDebugProc()->Print(CDebugProc::POINT_LEFT, "======================================\n");

	if (m_pTutorialManager != nullptr)
	{ // 使用中の場合

		// チュートリアルマネージャーの更新
		m_pTutorialManager->Update();
	}
	else { assert(false); }	// 非使用中

	// シーンの更新
	CScene::Update();
}

//============================================================
//	描画処理
//============================================================
void CSceneTutorial::Draw(void)
{

}

//============================================================
//	チュートリアルマネージャー取得処理
//============================================================
CTutorialManager *CSceneTutorial::GetTutorialManager(void)
{
	// チュートリアルマネージャーのポインタを返す
	return m_pTutorialManager;
}
