//============================================================
//
//	データ保存マネージャー処理 [retentionManager.cpp]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	インクルードファイル
//************************************************************
#include "retentionManager.h"
#include "manager.h"

//************************************************************
//	親クラス [CRetentionManager] のメンバ関数
//************************************************************
//============================================================
//	コンストラクタ
//============================================================
CRetentionManager::CRetentionManager()
{
	// メンバ変数をクリア
	m_nScore = 0;
}

//============================================================
//	デストラクタ
//============================================================
CRetentionManager::~CRetentionManager()
{

}

//============================================================
//	初期化処理
//============================================================
HRESULT CRetentionManager::Init(void)
{
	// メンバ変数を初期化
	m_nScore = 0;

	// 成功を返す
	return S_OK;
}

//============================================================
//	終了処理
//============================================================
void CRetentionManager::Uninit(void)
{

}

//============================================================
//	生成処理
//============================================================
CRetentionManager *CRetentionManager::Create(void)
{
	// ポインタを宣言
	CRetentionManager *pRetentionManager = nullptr;	// データ保存マネージャー生成用

	if (pRetentionManager == nullptr)
	{ // 使用されていない場合

		// メモリ確保
		pRetentionManager = new CRetentionManager;	// データ保存マネージャー
	}
	else { assert(false); return nullptr; }	// 使用中

	if (pRetentionManager != nullptr)
	{ // 使用されている場合
		
		// データ保存マネージャーの初期化
		if (FAILED(pRetentionManager->Init()))
		{ // 初期化に失敗した場合

			// メモリ開放
			delete pRetentionManager;
			pRetentionManager = nullptr;

			// 失敗を返す
			return nullptr;
		}

		// 確保したアドレスを返す
		return pRetentionManager;
	}
	else { assert(false); return nullptr; }	// 確保失敗
}

//============================================================
//	破棄処理
//============================================================
HRESULT CRetentionManager::Release(CRetentionManager *&prRetentionManager)
{
	if (prRetentionManager != nullptr)
	{ // 使用中の場合

		// データ保存マネージャーの終了
		prRetentionManager->Uninit();

		// メモリ開放
		delete prRetentionManager;
		prRetentionManager = nullptr;

		// 成功を返す
		return S_OK;
	}
	else { assert(false); return E_FAIL; }	// 非使用中
}

//============================================================
//	スコアの設定処理
//============================================================
void CRetentionManager::SetScore(const int nScore)
{
	// 引数のスコアを設定
	m_nScore = nScore;
}

//============================================================
//	スコア取得処理
//============================================================
int CRetentionManager::GetScore(void) const
{
	// スコアを返す
	return m_nScore;
}
