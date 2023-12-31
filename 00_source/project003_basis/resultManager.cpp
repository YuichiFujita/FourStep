//============================================================
//
//	リザルトマネージャー処理 [resultManager.cpp]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	インクルードファイル
//************************************************************
#include "resultManager.h"
#include "manager.h"
#include "sound.h"
#include "camera.h"
#include "fade.h"
#include "texture.h"
#include "model.h"
#include "object2D.h"
#include "retentionManager.h"
#include "multivalue.h"

//************************************************************
//	マクロ定義
//************************************************************
#define RESULT_PRIO	(14)	// リザルトの優先順位

#define SETCOL_FADE		(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.6f))	// α値の停止値
#define SIZE_FADE		(SCREEN_SIZE * 0.95f)	// フェードの大きさ
#define INITCOL_FADE	(XCOL_AWHITE)	// α値の初期値
#define ADD_ALPHA		(0.008f)		// α値の加算量

#define POS_RESULT_MISSION	(D3DXVECTOR3(440.0f, SCREEN_CENT.y, 0.0f))	// リザルト表示の遅刻回避の位置
#define POS_RESULT_RESULT	(D3DXVECTOR3(840.0f, SCREEN_CENT.y, 0.0f))	// リザルト表示の成功失敗の位置
#define SIZE_RESULT			(D3DXVECTOR3(1280.0f, 260.0f, 0.0f)*0.5f)	// リザルト表示の大きさ
#define SIZE_VALUE			(D3DXVECTOR3(120.0f, 140.0f, 0.0f))
#define SPACE_VALUE			(D3DXVECTOR3(100.0f, 0.0f, 0.0f))
#define SET_RESULT_SCALE	(15.0f)	// リザルト表示の初期拡大率
#define SUB_RESULT_SCALE	(0.65f)	// リザルト表示拡大率の減算量

#define POS_TIME_LOGO	(D3DXVECTOR3(290.0f, 330.0f, 0.0f))	// タイムロゴ位置
#define SIZE_TIME_LOGO	(D3DXVECTOR3(487.5f, 154.7f, 0.0f))	// タイムロゴ大きさ
#define POS_TIME		(D3DXVECTOR3(555.0f, 330.0f, 0.0f))	// タイム位置
#define SIZE_TIME_VAL	(D3DXVECTOR3(98.0f, 117.0f, 0.0f))	// タイム数字大きさ
#define SIZE_TIME_PART	(D3DXVECTOR3(50.0f, 117.0f, 0.0f))	// タイム区切り大きさ
#define SPACE_TIME_VAL	(D3DXVECTOR3(SIZE_TIME_VAL.x  * 0.85f, 0.0f, 0.0f))	// タイム数字空白
#define SPACE_TIME_PART	(D3DXVECTOR3(SIZE_TIME_PART.x * 0.85f, 0.0f, 0.0f))	// タイム区切り空白
#define SET_TIME_SCALE	(8.0f)	// タイム表示の初期拡大率
#define SUB_TIME_SCALE	(0.3f)	// タイム表示拡大率の減算量
#define TIME_WAIT_CNT	(3)		// タイム表示状態への変更待機フレーム数

#define POS_CONT_LOGO	(D3DXVECTOR3(SCREEN_CENT.x, 490.0f, 0.0f))	// コンテニューロゴ位置
#define SIZE_CONT_LOGO	(D3DXVECTOR3(576.0f, 172.0f, 0.0f))	// コンテニューロゴ大きさ
#define POS_CONT_YES	(D3DXVECTOR3(400.0f, 610.0f, 0.0f))	// コンテニュー表示のYESの位置
#define POS_CONT_NO		(D3DXVECTOR3(880.0f, 610.0f, 0.0f))	// コンテニュー表示のNOの位置
#define SIZE_CONT		(D3DXVECTOR3(222.0f, 94.0f, 0.0f))	// コンテニュー表示の大きさ
#define SET_CONT_SCALE	(8.0f)	// コンテニュー表示の初期拡大率
#define SUB_CONT_SCALE	(0.3f)	// コンテニュー表示拡大率の減算量
#define CONT_WAIT_CNT	(3)		// コンテニュー表示状態への変更待機フレーム数

#define CHOICE_COL	(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f))	// 選択中カラー
#define DEFAULT_COL	(D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f))	// 非選択中カラー

//************************************************************
//	静的メンバ変数宣言
//************************************************************
const char *CResultManager::mc_apTextureFile[] =	// テクスチャ定数
{
	"data\\TEXTURE\\result000.png",		// 遅刻回避テクスチャ
};

//************************************************************
//	親クラス [CResultManager] のメンバ関数
//************************************************************
//============================================================
//	コンストラクタ
//============================================================
CResultManager::CResultManager()
{
	// メンバ変数をクリア
	m_pScoreTitle	= nullptr;		// スコアタイトルの情報
	m_pScore		= nullptr;		// スコアの情報
	m_pFade			= nullptr;		// フェードの情報
	m_state			= STATE_NONE;	// 状態
	m_nCounterState	= 0;			// 状態管理カウンター
	m_fScale		= 0.0f;			// ポリゴン拡大率
}

//============================================================
//	デストラクタ
//============================================================
CResultManager::~CResultManager()
{

}

//============================================================
//	初期化処理
//============================================================
HRESULT CResultManager::Init(void)
{
	// 変数配列を宣言
	static D3DXVECTOR3 aPosContinue[] =	// コンテニューの位置
	{
		POS_CONT_YES,	// YES位置
		POS_CONT_NO	,	// NO位置
	};

	// ポインタを宣言
	CTexture *pTexture = GET_MANAGER->GetTexture();	// テクスチャへのポインタ

	// メンバ変数を初期化
	m_pScoreTitle	= nullptr;		// スコアタイトルの情報
	m_pScore		= nullptr;		// スコアの情報
	m_pFade			= nullptr;		// フェードの情報
	m_state			= STATE_FADEIN;	// 状態
	m_nCounterState	= 0;			// 状態管理カウンター
	m_fScale		= 0.0f;			// ポリゴン拡大率

	//--------------------------------------------------------
	//	フェードの生成・設定
	//--------------------------------------------------------
	// フェードの生成
	m_pFade = CObject2D::Create
	( // 引数
		SCREEN_CENT,	// 位置
		SIZE_FADE,		// 大きさ
		VEC3_ZERO,		// 向き
		INITCOL_FADE	// 色
	);
	if (m_pFade == nullptr)
	{ // 生成に失敗した場合

		// 失敗を返す
		assert(false);
		return E_FAIL;
	}

	// 優先順位を設定
	m_pFade->SetPriority(RESULT_PRIO);

	//--------------------------------------------------------
	//	リザルト表示の生成・設定
	//--------------------------------------------------------
	// リザルト表示の生成
	m_pScoreTitle = CObject2D::Create
	( // 引数
		POS_RESULT_MISSION,				// 位置
		SIZE_RESULT * SET_RESULT_SCALE	// 大きさ
	);
	if (m_pScoreTitle == nullptr)
	{ // 生成に失敗した場合

		// 失敗を返す
		assert(false);
		return E_FAIL;
	}

	// テクスチャを登録・割当
	m_pScoreTitle->BindTexture(pTexture->Regist(mc_apTextureFile[TEXTURE_SCORE]));

	// 優先順位を設定
	m_pScoreTitle->SetPriority(RESULT_PRIO);

	// 描画をしない設定にする
	m_pScoreTitle->SetEnableDraw(false);

	// リザルト表示の生成
	m_pScore = CMultiValue::Create
	( // 引数
		CValue::TEXTURE_NORMAL,
		GET_RETENTION->GetScore(),
		3,
		POS_RESULT_RESULT,				// 位置
		SIZE_VALUE * SET_RESULT_SCALE,	// 大きさ
		SPACE_VALUE
	);
	if (m_pScore == nullptr)
	{ // 生成に失敗した場合

		// 失敗を返す
		assert(false);
		return E_FAIL;
	}

	// 優先順位を設定
	m_pScore->SetPriority(RESULT_PRIO);

	// 描画をしない設定にする
	m_pScore->SetEnableDraw(false);

	// 成功を返す
	return S_OK;
}

//============================================================
//	終了処理
//============================================================
HRESULT CResultManager::Uninit(void)
{
	// スコアタイトル表示の終了
	m_pScoreTitle->Uninit();

	// スコアの終了
	m_pScore->Uninit();

	// フェードの終了
	m_pFade->Uninit();

	// 成功を返す
	return S_OK;
}

//============================================================
//	更新処理
//============================================================
void CResultManager::Update(void)
{
	switch (m_state)
	{ // 状態ごとの処理
	case STATE_NONE:	// 何もしない状態

		// 無し

		break;

	case STATE_FADEIN:	// フェードイン状態

		// フェードインの更新
		UpdateFade();

		break;

	case STATE_RESULT:	// リザルト表示状態

		// リザルト表示の更新
		UpdateResult();

		break;

	case STATE_WAIT:	// 遷移待機状態
		break;

	default:	// 例外処理
		assert(false);
		break;
	}

	// 遷移決定の更新
	UpdateTransition();

	// スコアタイトル表示の更新
	m_pScoreTitle->Update();

	// スコアの更新
	m_pScore->Update();

	// フェードの更新
	m_pFade->Update();
}

//============================================================
//	生成処理
//============================================================
CResultManager *CResultManager::Create(void)
{
	// ポインタを宣言
	CResultManager *pResultManager = nullptr;	// リザルトマネージャー生成用

	if (pResultManager == nullptr)
	{ // 使用されていない場合

		// メモリ確保
		pResultManager = new CResultManager;	// リザルトマネージャー
	}
	else { assert(false); return nullptr; }	// 使用中

	if (pResultManager != nullptr)
	{ // 使用されている場合
		
		// リザルトマネージャーの初期化
		if (FAILED(pResultManager->Init()))
		{ // 初期化に失敗した場合

			// メモリ開放
			delete pResultManager;
			pResultManager = nullptr;

			// 失敗を返す
			return nullptr;
		}

		// 確保したアドレスを返す
		return pResultManager;
	}
	else { assert(false); return nullptr; }	// 確保失敗
}

//============================================================
//	破棄処理
//============================================================
HRESULT CResultManager::Release(CResultManager *&prResultManager)
{
	if (prResultManager != nullptr)
	{ // 使用中の場合

		// リザルトマネージャーの終了
		if (FAILED(prResultManager->Uninit()))
		{ // 破棄に失敗した場合

			// メモリ開放
			delete prResultManager;
			prResultManager = nullptr;

			// 失敗を返す
			assert(false);
			return E_FAIL;
		}

		// メモリ開放
		delete prResultManager;
		prResultManager = nullptr;

		// 成功を返す
		return S_OK;
	}
	else { assert(false); return E_FAIL; }	// 非使用中
}

//============================================================
//	フェードインの更新処理
//============================================================
void CResultManager::UpdateFade(void)
{
	// 変数を宣言
	D3DXCOLOR colFade = m_pFade->GetColor();	// フェードの色

	if (colFade.a < SETCOL_FADE.a)
	{ // 透明量が設定値未満の場合

		// 透明度を加算
		colFade.a += ADD_ALPHA;
	}
	else
	{ // 透明量が設定値以上の場合

		// 透明度を補正
		colFade.a = SETCOL_FADE.a;

		// スコアタイトル表示の描画開始
		m_pScoreTitle->SetEnableDraw(true);

		// スコアの描画開始
		m_pScore->SetEnableDraw(true);

		// リザルト表示の拡大率を設定
		m_fScale = SET_RESULT_SCALE;

		// 状態を変更
		m_state = STATE_RESULT;	// リザルト表示状態
	}

	// 透明度を反映
	m_pFade->SetColor(colFade);
}

//============================================================
//	リザルト表示の更新処理
//============================================================
void CResultManager::UpdateResult(void)
{
	if (m_fScale > 1.0f)
	{ // 拡大率が最小値より大きい場合

		// 拡大率を減算
		m_fScale -= SUB_RESULT_SCALE;

		// スコアタイトル表示の大きさを設定
		m_pScoreTitle->SetVec3Sizing(SIZE_RESULT * m_fScale);

		// スコアの大きさを設定
		m_pScore->SetVec3Sizing(SIZE_VALUE * m_fScale);
	}
	else
	{ // 拡大率が最小値以下の場合

		// スコアタイトル表示の大きさを設定
		m_pScoreTitle->SetVec3Sizing(SIZE_RESULT);

		// スコアの大きさを設定
		m_pScore->SetVec3Sizing(SIZE_VALUE);

		// 状態を変更
		m_state = STATE_WAIT;	// コンテニュー表示待機状態

		// サウンドの再生
		GET_MANAGER->GetSound()->Play(CSound::LABEL_SE_DECISION_001);	// 決定音01
	}
}

//============================================================
//	遷移決定の更新処理
//============================================================
void CResultManager::UpdateTransition(void)
{
	// ポインタを宣言
	CInputKeyboard	*pKeyboard	= GET_INPUTKEY;	// キーボード
	CInputPad		*pPad		= GET_INPUTPAD;		// パッド

	if (pKeyboard->IsTrigger(DIK_RETURN)
	||  pKeyboard->IsTrigger(DIK_SPACE)
	||  pPad->IsTrigger(CInputPad::KEY_A)
	||  pPad->IsTrigger(CInputPad::KEY_B)
	||  pPad->IsTrigger(CInputPad::KEY_X)
	||  pPad->IsTrigger(CInputPad::KEY_Y)
	||  pPad->IsTrigger(CInputPad::KEY_START))
	{
		if (m_state != STATE_WAIT)
		{ // 遷移待機状態ではない場合

			// 演出スキップ
			SkipStaging();

			// サウンドの再生
			GET_MANAGER->GetSound()->Play(CSound::LABEL_SE_DECISION_001);	// 決定音01
		}
		else
		{ // 遷移待機状態の場合

			if (GET_MANAGER->GetFade()->GetState() == CFade::FADE_NONE)
			{ // フェード中ではない場合

				// シーンの設定
				GET_MANAGER->SetScene(CScene::MODE_RANKING);	// ランキング画面

				// サウンドの再生
				GET_MANAGER->GetSound()->Play(CSound::LABEL_SE_DECISION_000);	// 決定音00
			}
		}
	}
}

//============================================================
//	演出スキップ処理
//============================================================
void CResultManager::SkipStaging(void)
{
	// リザルト表示の描画をONにし、大きさを設定
	// スコアタイトル表示の描画開始
	m_pScoreTitle->SetEnableDraw(true);

	// スコアの描画開始
	m_pScore->SetEnableDraw(true);

	// スコアタイトル表示の大きさを設定
	m_pScoreTitle->SetVec3Sizing(SIZE_RESULT);

	// スコアの大きさを設定
	m_pScore->SetVec3Sizing(SIZE_VALUE);

	// フェードの透明度を設定
	m_pFade->SetColor(SETCOL_FADE);

	// 状態を変更
	m_state = STATE_WAIT;	// 遷移待機状態
}

//============================================================
//	表示待機処理
//============================================================
bool CResultManager::UpdateDrawWait(const int nWait)
{
	if (m_nCounterState < nWait)
	{ // カウンターが待機カウントまで達していない場合

		// カウンターを加算
		m_nCounterState++;

		// 待機未完了を返す
		return false;
	}
	else
	{ // カウンターが待機完了した場合

		// カウンターを初期化
		m_nCounterState = 0;

		// 待機完了を返す
		return true;
	}
}
