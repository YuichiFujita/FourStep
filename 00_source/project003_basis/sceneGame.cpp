//============================================================
//
//	ゲーム画面処理 [sceneGame.cpp]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	インクルードファイル
//************************************************************
#include "sceneGame.h"
#include "manager.h"
#include "sound.h"
#include "camera.h"

#include "gameManager.h"
#include "stage.h"
#include "score.h"
#include "player.h"
#include "enemy.h"

//************************************************************
//	マクロ定義
//************************************************************


//************************************************************
//	静的メンバ変数宣言
//************************************************************
CGameManager	*CSceneGame::m_pGameManager  = nullptr;	// ゲームマネージャー
CScore	*CSceneGame::m_pScore	= nullptr;	// タイマーマネージャー

bool CSceneGame::m_bControlCamera = false;	// カメラの操作状況
bool CSceneGame::m_bDrawUI = true;			// UIの描画状況

//************************************************************
//	子クラス [CSceneGame] のメンバ関数
//************************************************************
//============================================================
//	コンストラクタ
//============================================================
CSceneGame::CSceneGame(const EMode mode) : CScene(mode)
{

}

//============================================================
//	デストラクタ
//============================================================
CSceneGame::~CSceneGame()
{

}

//============================================================
//	初期化処理
//============================================================
HRESULT CSceneGame::Init(void)
{
	//--------------------------------------------------------
	//	初期生成
	//--------------------------------------------------------
	// スコアの生成
	m_pScore = CScore::Create(D3DXVECTOR3(790.0f, 430.0f, 0.0f), VEC3_ONE, D3DXVECTOR3(140.0f, 0.0f, 0.0f));
	if (m_pScore == nullptr)
	{ // 非使用中の場合

		// 失敗を返す
		assert(false);
		return E_FAIL;
	}

	// シーンの初期化
	CScene::Init();		// ステージ・プレイヤーの生成

	// ゲームマネージャーの生成
	m_pGameManager = CGameManager::Create();
	if (m_pGameManager == nullptr)
	{ // 非使用中の場合

		// 失敗を返す
		assert(false);
		return E_FAIL;
	}

	//--------------------------------------------------------
	//	初期設定
	//--------------------------------------------------------
	// カメラを設定
	GET_MANAGER->GetCamera()->SetState(CCamera::STATE_UPCAMERA);	// カメラを追従状態に設定

	// プレイヤーを出現
	CScene::GetPlayer()->SetSpawn();
	CScene::GetPlayer()->SetEnableDraw(false);	// 描画はOFFにする

	// UIの描画状況を設定
	SetEnableDrawUI(m_bDrawUI);

	// BGMの再生
	GET_MANAGER->GetSound()->Play(CSound::LABEL_BGM_GAME);

	// 成功を返す
	return S_OK;
}

//============================================================
//	終了処理
//============================================================
HRESULT CSceneGame::Uninit(void)
{
	// ゲームマネージャーの破棄
	if (FAILED(CGameManager::Release(m_pGameManager)))
	{ // 破棄に失敗した場合

		// 失敗を返す
		assert(false);
		return E_FAIL;
	}

	if (m_pScore != nullptr)
	{
		m_pScore->Uninit();
	}

	// シーンの終了
	CScene::Uninit();

	// 成功を返す
	return S_OK;
}

//============================================================
//	更新処理
//============================================================
void CSceneGame::Update(void)
{
#if _DEBUG

	if (GET_INPUTKEY->IsTrigger(DIK_F2))
	{
		// エディット状況を反転
		//CGameManager::GetEditStage()->SetEnableEdit((!CGameManager::GetEditStage()->IsEdit()) ? true : false);
	}
	if (GET_INPUTKEY->IsTrigger(DIK_F3))
	{
		// UIの描画状況を反転
		SetEnableDrawUI((!m_bDrawUI) ? true : false);
	}
	else if (GET_INPUTKEY->IsTrigger(DIK_F4))
	{

	}
	else if (GET_INPUTKEY->IsTrigger(DIK_F5))
	{
		// カメラの操作状況を反転
		SetEnableControlCamera((!m_bControlCamera) ? true : false);
	}
	else if (GET_INPUTKEY->IsTrigger(DIK_F6))
	{
		// プレイヤーの出現を設定
		CScene::GetPlayer()->SetSpawn();
	}
	else if (GET_INPUTKEY->IsTrigger(DIK_F7))
	{
		// TODO：後で消すエネミー生成
		CEnemy::Create(CEnemy::TYPE_NORMAL, VEC3_ZERO, VEC3_ZERO);
	}
	else if (GET_INPUTKEY->IsPress(DIK_F8))
	{
		// TODO：後で消すスコア上昇
		m_pScore->Add(1);
	}

	// デバッグ表示
	GET_MANAGER->GetDebugProc()->Print(CDebugProc::POINT_LEFT, "======================================\n");
	GET_MANAGER->GetDebugProc()->Print(CDebugProc::POINT_LEFT, "　[デバッグ操作]\n");
	GET_MANAGER->GetDebugProc()->Print(CDebugProc::POINT_LEFT, "======================================\n");
	GET_MANAGER->GetDebugProc()->Print(CDebugProc::POINT_LEFT, "[F1]：デバッグ表示のON/OFF\n");
	GET_MANAGER->GetDebugProc()->Print(CDebugProc::POINT_LEFT, "[F2]：エディットモードのON/OFF\n");
	GET_MANAGER->GetDebugProc()->Print(CDebugProc::POINT_LEFT, "[F3]：UI描画のON/OFF\n");
	GET_MANAGER->GetDebugProc()->Print(CDebugProc::POINT_LEFT, "[F4]：ポーズ描画のON/OFF\n");
	GET_MANAGER->GetDebugProc()->Print(CDebugProc::POINT_LEFT, "[F5]：カメラ操作のON/OFF\n");
	GET_MANAGER->GetDebugProc()->Print(CDebugProc::POINT_LEFT, "[F6]：プレイヤースポーン\n");
	GET_MANAGER->GetDebugProc()->Print(CDebugProc::POINT_LEFT, "[F7]：敵出るよ〜ん\n");
	GET_MANAGER->GetDebugProc()->Print(CDebugProc::POINT_LEFT, "[F8]：スコア加算〜\n");

	GET_MANAGER->GetDebugProc()->Print(CDebugProc::POINT_LEFT, "======================================\n");
	GET_MANAGER->GetDebugProc()->Print(CDebugProc::POINT_LEFT, "　[デバッグ情報]\n");
	GET_MANAGER->GetDebugProc()->Print(CDebugProc::POINT_LEFT, "======================================\n");

#endif

	if (m_pGameManager != nullptr)
	{ // 使用中の場合

		// ゲームマネージャーの更新
		m_pGameManager->Update();
	}
	else { assert(false); }	// 非使用中

	// シーンの更新
	CScene::Update();

	if (m_pScore != nullptr)
	{
		m_pScore->Update();
	}

#if _DEBUG

	if (GET_MANAGER->GetCamera()->GetState() == CCamera::STATE_CONTROL)
	{ // カメラが操作状態の場合

		// カメラの更新
		GET_MANAGER->GetCamera()->Update();
	}

#endif	// _DEBUG

}

//============================================================
//	描画処理
//============================================================
void CSceneGame::Draw(void)
{

}

//============================================================
//	ゲームマネージャー取得処理
//============================================================
CGameManager *CSceneGame::GetGameManager(void)
{
	// ゲームマネージャーのポインタを返す
	return m_pGameManager;
}

//============================================================
//	タイマーマネージャー取得処理
//============================================================
CScore *CSceneGame::GetScore(void)
{
	// スコアのポインタを返す
	return m_pScore;
}

//============================================================
//	UIの描画状況の設定処理
//============================================================
void CSceneGame::SetEnableDrawUI(const bool bDraw)
{
	// 引数のUIの描画状況を設定
	m_bDrawUI = bDraw;
}

//============================================================
//	UIの描画状況取得処理
//============================================================
bool CSceneGame::IsDrawUI(void)
{
	// UIの描画状況を返す
	return m_bDrawUI;
}

//============================================================
//	カメラの操作状況の設定処理
//============================================================
void CSceneGame::SetEnableControlCamera(const bool bControl)
{
	// 引数のカメラ操作状況を設定
	m_bControlCamera = bControl;

	// カメラの操作状況を設定
	if (bControl)
	{ // 操作する状況の場合

		// 操作状態に変更
		GET_MANAGER->GetCamera()->SetState(CCamera::STATE_CONTROL);
	}
	else
	{ // 操作しない状況の場合

		// 追従状態に変更
		GET_MANAGER->GetCamera()->SetState(CCamera::STATE_FOLLOW);
	}
}
