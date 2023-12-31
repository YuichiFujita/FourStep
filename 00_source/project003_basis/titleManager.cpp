//============================================================
//
//	タイトルマネージャー処理 [titleManager.cpp]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	インクルードファイル
//************************************************************
#include "titleManager.h"
#include "manager.h"
#include "sound.h"
#include "camera.h"
#include "fade.h"
#include "texture.h"
#include "model.h"
#include "object2D.h"

//************************************************************
//	マクロ定義
//************************************************************
#define TITLE_PRIO	(14)	// タイトルの優先順位

#define POS_LOGO_NEVER	(D3DXVECTOR3(340.0f,  140.0f, 0.0f))	// タイトルロゴの位置 (NEVER)
#define POS_LOGO_GIVE	(D3DXVECTOR3(710.0f,  310.0f, 0.0f))	// タイトルロゴの位置 (GIVE)
#define POS_LOGO_UP		(D3DXVECTOR3(1050.0f, 320.0f, 0.0f))	// タイトルロゴの位置 (UP!)

#define POS_TITLE	(D3DXVECTOR3(SCREEN_CENT.x, 240.0f, 0.0f))	// タイトルロゴの位置
#define SIZE_TITLE	(D3DXVECTOR3(512.0f, 202.0f, 0.0f)*1.35f)	// タイトルロゴの大きさ
#define INIT_SCALE	(15.0f)	// タイトルロゴの初期拡大率
#define SUB_SCALE	(0.65f)	// タイトルロゴ拡大率の減算量

#define COL_FADE	(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.5f))	// タイトルフェードの色
#define SUB_ALPHA	(0.008f)	// α値の減算量

#define POS_SELECTBG	(D3DXVECTOR3(640.0f, 560.0f, 0.0f))					// 選択背景の位置
#define SIZE_SELECTBG	(D3DXVECTOR3((float)SCREEN_WIDTH, 120.0f, 0.0f))	// 選択背景の大きさ
#define COL_SELECTBG	(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.5f))					// 選択背景の色

#define POS_SELECT		(D3DXVECTOR3(350.0f, 560.0f, 0.0f))	// 選択の位置
#define SPACE_SELECT	(D3DXVECTOR3(560.0f, 0.0f, 0.0f))	// 選択の空間
#define SIZE_SELECT		(D3DXVECTOR3(420.0f, 140.0f, 0.0f))	// 選択の大きさ

#define CHOICE_COL	(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f))	// 選択中カラー
#define DEFAULT_COL	(D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f))	// 非選択中カラー

//************************************************************
//	静的メンバ変数宣言
//************************************************************
const char *CTitleManager::mc_apTextureFile[] =	// ロゴテクスチャ定数
{
	"data\\TEXTURE\\title000.png",	// 背景テクスチャ
	"data\\TEXTURE\\title001.png",	// タイトルテクスチャ
};
const char *CTitleManager::mc_apSelectTextureFile[] =	// 選択テクスチャ定数
{
	"data\\TEXTURE\\title003.png",	// STARTテクスチャ
	"data\\TEXTURE\\title004.png",	// MANUALテクスチャ
};

//************************************************************
//	親クラス [CTitleManager] のメンバ関数
//************************************************************
//============================================================
//	コンストラクタ
//============================================================
CTitleManager::CTitleManager()
{
	// メンバ変数をクリア
	memset(&m_apSelect[0], 0, sizeof(m_apSelect));	// 選択表示の情報
	m_pLogo = nullptr;		// タイトルの情報
	m_pFade = nullptr;		// フェードの情報
	m_pBG = nullptr;		// 背景の情報
	m_pSelectBG = nullptr;	// 選択背景の情報
	m_state = STATE_NONE;	// 状態
	m_fScale = 0.0f;		// タイトル拡大率
	m_nSelect = 0;			// 現在の選択
	m_nOldSelect = 0;		// 前回の選択
}

//============================================================
//	デストラクタ
//============================================================
CTitleManager::~CTitleManager()
{

}

//============================================================
//	初期化処理
//============================================================
HRESULT CTitleManager::Init(void)
{
	// ポインタを宣言
	CTexture *pTexture = GET_MANAGER->GetTexture();	// テクスチャへのポインタ

	// メンバ変数を初期化
	memset(&m_apSelect[0], 0, sizeof(m_apSelect));	// 選択表示の情報
	m_pLogo = nullptr;			// タイトルの情報
	m_pFade = nullptr;			// フェードの情報
	m_pBG = nullptr;			// 背景の情報
	m_pSelectBG = nullptr;		// 選択背景の情報
	m_state = STATE_FADEOUT;	// 状態
	m_fScale = INIT_SCALE;		// タイトル拡大率
	m_nSelect = 0;				// 現在の選択
	m_nOldSelect = 0;			// 前回の選択

	//--------------------------------------------------------
	//	選択背景の生成・設定
	//--------------------------------------------------------
	// 選択背景の生成
	m_pBG = CObject2D::Create
	( // 引数
		SCREEN_CENT,	// 位置
		SCREEN_SIZE		// 大きさ
	);
	if (m_pBG == nullptr)
	{ // 生成に失敗した場合

		// 失敗を返す
		assert(false);
		return E_FAIL;
	}

	// テクスチャを登録・割当
	m_pBG->BindTexture(pTexture->Regist(mc_apTextureFile[TEXTURE_BG]));

	// 優先順位を設定
	m_pBG->SetPriority(TITLE_PRIO);

	//--------------------------------------------------------
	//	選択背景の生成・設定
	//--------------------------------------------------------
	// 選択背景の生成
	m_pSelectBG = CObject2D::Create
	( // 引数
		POS_SELECTBG,	// 位置
		SIZE_SELECTBG,	// 大きさ
		VEC3_ZERO,		// 向き
		COL_SELECTBG	// 色
	);
	if (m_pSelectBG == nullptr)
	{ // 生成に失敗した場合

		// 失敗を返す
		assert(false);
		return E_FAIL;
	}

	// 優先順位を設定
	m_pSelectBG->SetPriority(TITLE_PRIO);

	// 描画をしない設定にする
	m_pSelectBG->SetEnableDraw(false);

	//--------------------------------------------------------
	//	選択表示の生成・設定
	//--------------------------------------------------------
	for (int nCntTitle = 0; nCntTitle < SELECT_MAX; nCntTitle++)
	{ // 選択項目の総数分繰り返す

		// 選択表示の生成
		m_apSelect[nCntTitle] = CObject2D::Create
		( // 引数
			POS_SELECT + (SPACE_SELECT * (float)nCntTitle),	// 位置
			SIZE_SELECT,	// 大きさ
			VEC3_ZERO,		// 向き
			DEFAULT_COL		// 色
		);
		if (m_apSelect[nCntTitle] == nullptr)
		{ // 生成に失敗した場合

			// 失敗を返す
			assert(false);
			return E_FAIL;
		}

		// テクスチャを登録・割当
		m_apSelect[nCntTitle]->BindTexture(pTexture->Regist(mc_apSelectTextureFile[nCntTitle]));

		// 優先順位を設定
		m_apSelect[nCntTitle]->SetPriority(TITLE_PRIO);

		// 描画をしない設定にする
		m_apSelect[nCntTitle]->SetEnableDraw(false);
	}

	//--------------------------------------------------------
	//	タイトルロゴの生成・設定
	//--------------------------------------------------------
	// タイトルロゴの生成
	m_pLogo = CObject2D::Create
	( // 引数
		POS_TITLE,	// 位置
		SIZE_TITLE * INIT_SCALE	// 大きさ
	);
	if (m_pLogo == nullptr)
	{ // 生成に失敗した場合

		// 失敗を返す
		assert(false);
		return E_FAIL;
	}

	// テクスチャを登録・割当
	m_pLogo->BindTexture(pTexture->Regist(mc_apTextureFile[TEXTURE_LOGO]));

	// 優先順位を設定
	m_pLogo->SetPriority(TITLE_PRIO);

	// 描画をしない設定にする
	m_pLogo->SetEnableDraw(false);

	//--------------------------------------------------------
	//	フェードの生成・設定
	//--------------------------------------------------------
	// フェードの生成
	m_pFade = CObject2D::Create
	( // 引数
		SCREEN_CENT,	// 位置
		SCREEN_SIZE,	// 大きさ
		VEC3_ZERO,		// 向き
		COL_FADE		// 色
	);
	if (m_pFade == nullptr)
	{ // 生成に失敗した場合

		// 失敗を返す
		assert(false);
		return E_FAIL;
	}

	// 優先順位を設定
	m_pFade->SetPriority(TITLE_PRIO);

	// 成功を返す
	return S_OK;
}

//============================================================
//	終了処理
//============================================================
void CTitleManager::Uninit(void)
{
	// 選択背景の終了
	m_pBG->Uninit();

	// タイトルロゴの終了
	m_pLogo->Uninit();

	for (int nCntTitle = 0; nCntTitle < SELECT_MAX; nCntTitle++)
	{ // 選択項目の総数分繰り返す

		// 選択表示の終了
		m_apSelect[nCntTitle]->Uninit();
	}

	// フェードの終了
	m_pFade->Uninit();

	// 選択背景の終了
	m_pSelectBG->Uninit();
}

//============================================================
//	更新処理
//============================================================
void CTitleManager::Update(void)
{
	// 遷移決定の更新
	UpdateStart();

	switch (m_state)
	{ // 状態ごとの処理
	case STATE_NONE:	// 何もしない状態

		// 無し

		break;

	case STATE_FADEOUT:	// フェードアウト状態

		// フェードアウトの更新
		UpdateFade();

		break;

	case STATE_MOVE:	// タイトル縮小状態

		// タイトル移動の更新
		UpdateMove();

		break;

	case STATE_WAIT:	// 遷移待機状態

		// 選択操作
		ActSelect();

		break;

	default:	// 例外処理
		assert(false);
		break;
	}

	// 選択背景の更新
	m_pBG->Update();

	// タイトルロゴの更新
	m_pLogo->Update();

	for (int nCntTitle = 0; nCntTitle < SELECT_MAX; nCntTitle++)
	{ // 選択項目の総数分繰り返す

		// 選択表示の更新
		m_apSelect[nCntTitle]->Update();
	}

	// フェードの更新
	m_pFade->Update();

	// 選択背景の更新
	m_pSelectBG->Update();
}

//============================================================
//	生成処理
//============================================================
CTitleManager *CTitleManager::Create(void)
{
	// ポインタを宣言
	CTitleManager *pTitleManager = nullptr;	// タイトルマネージャー生成用

	if (pTitleManager == nullptr)
	{ // 使用されていない場合

		// メモリ確保
		pTitleManager = new CTitleManager;	// タイトルマネージャー
	}
	else { assert(false); return nullptr; }	// 使用中

	if (pTitleManager != nullptr)
	{ // 使用されている場合
		
		// タイトルマネージャーの初期化
		if (FAILED(pTitleManager->Init()))
		{ // 初期化に失敗した場合

			// メモリ開放
			delete pTitleManager;
			pTitleManager = nullptr;

			// 失敗を返す
			return nullptr;
		}

		// 確保したアドレスを返す
		return pTitleManager;
	}
	else { assert(false); return nullptr; }	// 確保失敗
}

//============================================================
//	破棄処理
//============================================================
HRESULT CTitleManager::Release(CTitleManager *&prTitleManager)
{
	if (prTitleManager != nullptr)
	{ // 使用中の場合

		// タイトルマネージャーの終了
		prTitleManager->Uninit();

		// メモリ開放
		delete prTitleManager;
		prTitleManager = nullptr;

		// 成功を返す
		return S_OK;
	}
	else { assert(false); return E_FAIL; }	// 非使用中
}

//============================================================
//	フェードアウトの更新処理
//============================================================
void CTitleManager::UpdateFade(void)
{
	// 変数を宣言
	D3DXCOLOR colFade = m_pFade->GetColor();	// フェードの色

	if (colFade.a > 0.0f)
	{ // 透明になっていない場合

		// 透明度を減算
		colFade.a -= SUB_ALPHA;
	}
	else
	{ // 透明になった場合

		// 透明度を補正
		colFade.a = 0.0f;

		// 描画をする設定にする
		m_pLogo->SetEnableDraw(true);

		for (int nCntTitle = 0; nCntTitle < SELECT_MAX; nCntTitle++)
		{ // 選択項目の総数分繰り返す

			// 選択表示を描画する設定にする
			m_apSelect[nCntTitle]->SetEnableDraw(true);
		}

		// 選択背景を描画する設定にする
		m_pSelectBG->SetEnableDraw(true);

		// 状態を変更
		m_state = STATE_MOVE;	// タイトル移動状態
	}

	// 透明度を反映
	m_pFade->SetColor(colFade);
}

//============================================================
//	タイトル移動の更新処理
//============================================================
void CTitleManager::UpdateMove(void)
{
	if (m_fScale > 1.0f)
	{ // 拡大率が最小値より大きい場合

		// 拡大率を減算
		m_fScale -= SUB_SCALE;

		// タイトルロゴの大きさを設定
		m_pLogo->SetVec3Sizing(SIZE_TITLE * m_fScale);
	}
	else
	{ // 拡大率が最小値以下の場合

		// 拡大率を補正
		m_fScale = 1.0f;

		// タイトルロゴの大きさを設定
		m_pLogo->SetVec3Sizing(SIZE_TITLE);

		// 状態を変更
		m_state = STATE_WAIT;	// 遷移待機状態

		// カメラの更新を再開
		GET_MANAGER->GetCamera()->SetEnableUpdate(true);

		// サウンドの再生
		GET_MANAGER->GetSound()->Play(CSound::LABEL_SE_DECISION_001);	// 決定音01
	}
}

//============================================================
//	遷移決定の更新処理
//============================================================
void CTitleManager::UpdateStart(void)
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

				switch (m_nSelect)
				{ // 選択ごとの処理
				case SELECT_GAME:

					// シーンの設定
					GET_MANAGER->SetScene(CScene::MODE_GAME);	// ゲーム画面

					break;

				case SELECT_TUTORIAL:

					// シーンの設定
					GET_MANAGER->SetScene(CScene::MODE_TUTORIAL);	// チュートリアル画面

					break;

				default:
					assert(false);
					break;
				}

				// サウンドの再生
				GET_MANAGER->GetSound()->Play(CSound::LABEL_SE_DECISION_000);	// 決定音00
			}
		}
	}
}

//============================================================
//	選択操作処理
//============================================================
void CTitleManager::ActSelect(void)
{
	// ポインタを宣言
	CInputKeyboard	*pKeyboard	= GET_INPUTKEY;	// キーボード
	CInputPad		*pPad		= GET_INPUTPAD;		// パッド

	if (GET_MANAGER->GetFade()->GetState() == CFade::FADE_NONE)
	{ // フェード中ではない場合

		if (pKeyboard->IsTrigger(DIK_A)
		||  pKeyboard->IsTrigger(DIK_LEFT)
		||  pPad->IsTrigger(CInputPad::KEY_LEFT))
		{ // 左移動の操作が行われた場合

			// 左に選択をずらす
			m_nSelect = (m_nSelect + (SELECT_MAX - 1)) % SELECT_MAX;

			// サウンドの再生
			GET_MANAGER->GetSound()->Play(CSound::LABEL_SE_SELECT_000);	// 選択操作音00
		}
		if (pKeyboard->IsTrigger(DIK_D)
		||  pKeyboard->IsTrigger(DIK_RIGHT)
		||  pPad->IsTrigger(CInputPad::KEY_RIGHT))
		{ // 右移動の操作が行われた場合

			// 右に選択をずらす
			m_nSelect = (m_nSelect + 1) % SELECT_MAX;

			// サウンドの再生
			GET_MANAGER->GetSound()->Play(CSound::LABEL_SE_SELECT_000);	// 選択操作音00
		}

		// 前回の選択要素の色を黒に設定
		m_apSelect[m_nOldSelect]->SetColor(DEFAULT_COL);

		// 現在の選択要素の色を白に設定
		m_apSelect[m_nSelect]->SetColor(CHOICE_COL);

		// 現在の選択要素を代入
		m_nOldSelect = m_nSelect;
	}
}

//============================================================
//	演出スキップ処理
//============================================================
void CTitleManager::SkipStaging(void)
{
	// タイトルロゴを表示状態に設定・大きさを正規化
	// タイトルロゴの大きさを設定
	m_pLogo->SetVec3Sizing(SIZE_TITLE);

	// 描画をする設定にする
	m_pLogo->SetEnableDraw(true);

	// 選択表示を描画する設定にする
	for (int nCntTitle = 0; nCntTitle < SELECT_MAX; nCntTitle++)
	{ // 選択項目の総数分繰り返す

		m_apSelect[nCntTitle]->SetEnableDraw(true);
	}

	// フェードを透明にする
	m_pFade->SetColor(XCOL_ABLACK);

	// 選択背景を描画する設定にする
	m_pSelectBG->SetEnableDraw(true);

	// カメラの更新を再開
	GET_MANAGER->GetCamera()->SetEnableUpdate(true);

	// 状態を変更
	m_state = STATE_WAIT;	// 遷移待機状態
}
