//============================================================
//
//	ゲームマネージャー処理 [gameManager.cpp]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	インクルードファイル
//************************************************************
#include "gameManager.h"
#include "manager.h"
#include "scene.h"
#include "sceneGame.h"
#include "camera.h"
#include "player.h"
#include "map.h"
#include "retentionManager.h"
#include "score.h"

//************************************************************
//	静的メンバ変数宣言
//************************************************************
CMap* CGameManager::m_pMap = nullptr;

//************************************************************
//	親クラス [CGameManager] のメンバ関数
//************************************************************
//============================================================
//	コンストラクタ
//============================================================
CGameManager::CGameManager()
{
	// メンバ変数をクリア
	m_state = STATE_NONE;	// 状態
	m_pMap = nullptr;
}

//============================================================
//	デストラクタ
//============================================================
CGameManager::~CGameManager()
{

}

//============================================================
//	初期化処理
//============================================================
HRESULT CGameManager::Init(void)
{
	// メンバ変数を初期化
	m_state = STATE_NORMAL;	// 状態

	if (m_pMap == nullptr)
	{
		m_pMap = CMap::Create(VEC3_ZERO, VEC3_ZERO, D3DXVECTOR3(50.0f, 50.0f, 50.0f), VEC2_ONE, VEC2_ONE, VEC2_ONE);
		m_pMap->Init();
	}

	// 成功を返す
	return S_OK;
}

//============================================================
//	終了処理
//============================================================
void CGameManager::Uninit(void)
{
	if (m_pMap != nullptr)
	{
		m_pMap->Uninit();
		m_pMap = nullptr;
	}
}

//============================================================
//	更新処理
//============================================================
void CGameManager::Update(void)
{
	switch (m_state)
	{ // 状態ごとの処理
	case STATE_NONE:

		// 無し

		break;

	case STATE_NORMAL:

		m_pMap->Update();

		if (CScene::GetPlayer()->GetState() == CPlayer::STATE_DEATH)
		{ // 死亡した場合

			// スコアを設定
			GET_RETENTION->SetScore(CSceneGame::GetScore()->Get());

			// シーン遷移
			GET_MANAGER->SetScene(CScene::MODE_RESULT, 60);
		}

		break;

	case STATE_END:

		// 無し

		break;

	default:	// 例外処理
		assert(false);
		break;
	}
}

//============================================================
//	状態の設定処理
//============================================================
void CGameManager::SetState(const EState state)
{
	if (state > NONE_IDX && state < STATE_MAX)
	{ // 範囲内の場合

		// 状態を設定
		m_state = state;
	}
	else { assert(false); }	// 範囲外
}

//============================================================
//	状態取得処理
//============================================================
CGameManager::EState CGameManager::GetState(void) const
{
	// 状態を返す
	return m_state;
}

//============================================================
//	生成処理
//============================================================
CGameManager *CGameManager::Create(void)
{
	// ポインタを宣言
	CGameManager *pGameManager = nullptr;	// ゲームマネージャー生成用

	if (pGameManager == nullptr)
	{ // 使用されていない場合

		// メモリ確保
		pGameManager = new CGameManager;	// ゲームマネージャー
	}
	else { assert(false); return nullptr; }	// 使用中

	if (pGameManager != nullptr)
	{ // 使用されている場合
		
		// ゲームマネージャーの初期化
		if (FAILED(pGameManager->Init()))
		{ // 初期化に失敗した場合

			// メモリ開放
			delete pGameManager;
			pGameManager = nullptr;

			// 失敗を返す
			return nullptr;
		}

		// 確保したアドレスを返す
		return pGameManager;
	}
	else { assert(false); return nullptr; }	// 確保失敗
}

//============================================================
//	破棄処理
//============================================================
HRESULT CGameManager::Release(CGameManager *&prGameManager)
{
	if (prGameManager != nullptr)
	{ // 使用中の場合

		// ゲームマネージャーの終了
		prGameManager->Uninit();

		// メモリ開放
		delete prGameManager;
		prGameManager = nullptr;

		// 成功を返す
		return S_OK;
	}
	else { assert(false); return E_FAIL; }	// 非使用中
}

//============================================================
//	マップ取得処理
//============================================================
CMap *CGameManager::GetMap(void)
{
	return m_pMap;
}
