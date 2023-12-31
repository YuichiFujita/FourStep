//============================================================
//
//	スコア処理 [score.cpp]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	インクルードファイル
//************************************************************
#include "score.h"
#include "manager.h"
#include "renderer.h"
#include "modelUI.h"

//************************************************************
//	定数宣言
//************************************************************
namespace
{
	const char *MODEL_FILE[] =	// 数字モデル
	{
		"data\\MODEL\\SCORE\\suuji_0.x",
		"data\\MODEL\\SCORE\\suuji_1.x",
		"data\\MODEL\\SCORE\\suuji_2.x",
		"data\\MODEL\\SCORE\\suuji_3.x",
		"data\\MODEL\\SCORE\\suuji_4.x",
		"data\\MODEL\\SCORE\\suuji_5.x",
		"data\\MODEL\\SCORE\\suuji_6.x",
		"data\\MODEL\\SCORE\\suuji_7.x",
		"data\\MODEL\\SCORE\\suuji_8.x",
		"data\\MODEL\\SCORE\\suuji_9.x",
	};

	const char *MODEL_FILE_LOGO = "data\\MODEL\\SCORE\\moji_score.x";
}

//************************************************************
//	マクロ定義
//************************************************************
#define SCORE_PRIO	(12)	// スコアの優先順位

#define SCO_NUMMIN	(0)		// 最少スコア
#define SCO_NUMMAX	(999)	// 最大スコア

//************************************************************
//	子クラス [CScore] のメンバ関数
//************************************************************
//============================================================
//	コンストラクタ
//============================================================
CScore::CScore() : CObject(CObject::LABEL_NONE, SCORE_PRIO)
{
	// メンバ変数をクリア
	memset(&m_apValue[0], 0, sizeof(m_apValue));	// 数値の情報
	m_pLogo	= nullptr;		// ロゴの情報
	m_pos	= VEC3_ZERO;	// 位置
	m_scale	= VEC3_ZERO;	// 大きさ
	m_space	= VEC3_ZERO;	// 空白
	m_nNum	= 0;			// スコア
}

//============================================================
//	デストラクタ
//============================================================
CScore::~CScore()
{

}

//============================================================
//	初期化処理
//============================================================
HRESULT CScore::Init(void)
{
	// メンバ変数を初期化
	memset(&m_apValue[0], 0, sizeof(m_apValue));	// 数値の情報
	m_pLogo	= nullptr;		// ロゴの情報
	m_pos	= VEC3_ZERO;	// 位置
	m_scale	= VEC3_ZERO;	// 大きさ
	m_space	= VEC3_ZERO;	// 空白
	m_nNum	= 0;			// スコア

	// 数字の生成
	m_pLogo = CModelUI::Create(VEC3_ZERO);
	if (m_pLogo == nullptr)
	{ // 生成に失敗した場合

		// 失敗を返す
		assert(false);
		return E_FAIL;
	}

	// 優先順位を設定
	m_pLogo->SetPriority(SCORE_PRIO);

	// 数字の設定
	m_pLogo->BindModel(MODEL_FILE_LOGO);

	for (int nCntScore = 0; nCntScore < MAX_SCORE; nCntScore++)
	{ // スコアの桁数分繰り返す

		// 数字の生成
		m_apValue[nCntScore] = CModelUI::Create(VEC3_ZERO);
		if (m_apValue[nCntScore] == nullptr)
		{ // 生成に失敗した場合

			// 失敗を返す
			assert(false);
			return E_FAIL;
		}

		// 優先順位を設定
		m_apValue[nCntScore]->SetPriority(SCORE_PRIO);

		// 数字の設定
		m_apValue[nCntScore]->BindModel(MODEL_FILE[0]);
	}

	// 成功を返す
	return S_OK;
}

//============================================================
//	終了処理
//============================================================
void CScore::Uninit(void)
{
	// 数字オブジェクトを破棄
	for (int nCntScore = 0; nCntScore < MAX_SCORE; nCntScore++)
	{ // スコアの桁数分繰り返す

		// 数字の終了
		m_apValue[nCntScore]->Uninit();
	}

	// 数字の終了
	m_pLogo->Uninit();

	// 自身のオブジェクトを破棄
	Release();
}

//============================================================
//	更新処理
//============================================================
void CScore::Update(void)
{
	for (int nCntScore = 0; nCntScore < MAX_SCORE; nCntScore++)
	{ // スコアの桁数分繰り返す

		// 数字の更新
		m_apValue[nCntScore]->Update();
	}

	// 数字の更新
	m_pLogo->Update();
}

//============================================================
//	描画処理
//============================================================
void CScore::Draw(void)
{

}

//============================================================
//	生成処理
//============================================================
CScore *CScore::Create
(
	const D3DXVECTOR3& rPos,	// 位置
	const D3DXVECTOR3& rScale,	// 大きさ
	const D3DXVECTOR3& rSpace	// 空白
)
{
	// ポインタを宣言
	CScore *pScore = NULL;		// スコア生成用

	if (pScore == nullptr)
	{ // 使用されていない場合

		// メモリ確保
		pScore = new CScore;	// スコア
	}
	else { assert(false); return NULL; }	// 使用中

	if (pScore != nullptr)
	{ // 確保に成功している場合

		// スコアの初期化
		if (FAILED(pScore->Init()))
		{ // 初期化に失敗した場合

			// メモリ開放
			delete pScore;
			pScore = NULL;

			// 失敗を返す
			return NULL;
		}

		// 位置を設定
		pScore->SetVec3Position(rPos);

		// 大きさを設定
		pScore->SetVec3Scaling(rScale);

		// 空白を設定
		pScore->SetSpace(rSpace);

		// 確保したアドレスを返す
		return pScore;
	}
	else { assert(false); return NULL; }	// 確保失敗
}

//============================================================
//	加算処理
//============================================================
void CScore::Add(const int nNum)
{
	// スコアを引数分加算
	m_nNum += nNum;

	// スコアの補正
	useful::LimitNum(m_nNum, SCO_NUMMIN, SCO_NUMMAX);

	// 数字のテクスチャ座標の設定
	SetTexNum();
}

//============================================================
//	設定処理
//============================================================
void CScore::Set(const int nNum)
{
	// スコアを引数の値に設定
	m_nNum = nNum;

	// スコアの補正
	useful::LimitNum(m_nNum, SCO_NUMMIN, SCO_NUMMAX);

	// 数字のテクスチャ座標の設定
	SetTexNum();
}

//============================================================
//	取得処理
//============================================================
int CScore::Get(void)
{
	// スコアの値を返す
	return m_nNum;
}

//============================================================
//	位置の設定処理
//============================================================
void CScore::SetVec3Position(const D3DXVECTOR3& rPos)
{
	// 引数の位置を設定
	m_pos = rPos;

	// 数字の表示設定
	SetDrawValue();
}

//============================================================
//	大きさの設定処理
//============================================================
void CScore::SetVec3Scaling(const D3DXVECTOR3& rScale)
{
	// 引数の拡大率を設定
	m_scale = rScale;

	// 数字の表示設定
	SetDrawValue();
}

//============================================================
//	空白の設定処理
//============================================================
void CScore::SetSpace(const D3DXVECTOR3& rSpace)
{
	// 引数の空白を設定
	m_space = rSpace;

	// 数字の表示設定
	SetDrawValue();
}

//============================================================
//	優先順位の設定処理
//============================================================
void CScore::SetPriority(const int nPriority)
{
	// 自身の優先順位を設定
	CObject::SetPriority(nPriority);

	if (m_apValue[0] != nullptr)
	{ // スコアの先頭の数値が使用されている場合

		// 数字オブジェクトの優先順位を設定
		for (int nCntScore = 0; nCntScore < MAX_SCORE; nCntScore++)
		{ // スコアの桁数分繰り返す

			m_apValue[nCntScore]->SetPriority(nPriority);
		}
	}
	else { assert(false); }	// 非使用中
}

//============================================================
//	更新状況の設定処理
//============================================================
void CScore::SetEnableUpdate(const bool bUpdate)
{
	// 自身の更新状況を設定
	CObject::SetEnableUpdate(bUpdate);

	if (m_apValue[0] != nullptr)
	{ // スコアの先頭の数値が使用されている場合

		// 数字オブジェクトの更新状況を設定
		for (int nCntScore = 0; nCntScore < MAX_SCORE; nCntScore++)
		{ // スコアの桁数分繰り返す

			m_apValue[nCntScore]->SetEnableUpdate(bUpdate);
		}
	}
	else { assert(false); }	// 非使用中
}

//============================================================
//	描画状況の設定処理
//============================================================
void CScore::SetEnableDraw(const bool bDraw)
{
	// 自身の描画状況を設定
	CObject::SetEnableDraw(bDraw);

	if (m_apValue[0] != nullptr)
	{ // スコアの先頭の数値が使用されている場合

		// 数字オブジェクトの描画状況を設定
		for (int nCntScore = 0; nCntScore < MAX_SCORE; nCntScore++)
		{ // スコアの桁数分繰り返す

			m_apValue[nCntScore]->SetEnableDraw(bDraw);
		}
	}
	else { assert(false); }	// 非使用中
}

//============================================================
//	位置取得処理
//============================================================
D3DXVECTOR3 CScore::GetVec3Position(void) const
{
	// 位置を返す
	return m_pos;
}

//============================================================
//	大きさ取得処理
//============================================================
D3DXVECTOR3 CScore::GetVec3Scaling(void) const
{
	// 拡大率を返す
	return m_scale;
}

//============================================================
//	空白取得処理
//============================================================
D3DXVECTOR3 CScore::GetSpace(void) const
{
	// 空白を返す
	return m_space;
}

//============================================================
//	破棄処理
//============================================================
void CScore::Release(void)
{
	// オブジェクトの破棄
	CObject::Release();
}

//============================================================
//	数字の表示設定処理
//============================================================
void CScore::SetDrawValue(void)
{
	if (m_apValue[0] != nullptr)
	{ // スコアの先頭の数値が使用されている場合

		for (int nCntScore = 0; nCntScore < MAX_SCORE; nCntScore++)
		{ // スコアの桁数分繰り返す

			// 数字の位置を設定
			m_apValue[nCntScore]->SetVec3Position(m_pos + (m_space * (float)nCntScore));

			// 数字の大きさを設定
			m_apValue[nCntScore]->SetVec3Scaling(m_scale);
		}
	}
	else { assert(false); }	// 非使用中

	// 数字の位置を設定
	m_pLogo->SetVec3Position(m_pos - D3DXVECTOR3(500.0f, -10.0f, 0.0f));

	// 数字の大きさを設定
	m_pLogo->SetVec3Scaling(m_scale * 0.8f);
}

//============================================================
//	数字のテクスチャ座標の設定処理
//============================================================
void CScore::SetTexNum(void)
{
	// 変数を宣言
	int aNumDivide[MAX_SCORE];	// 桁数ごとの分解用

	// スコアを桁数ごとに分解
	useful::DivideDigitNum
	( // 引数
		&aNumDivide[0],	// 分解結果の格納配列
		m_nNum,			// 分解する数値
		MAX_SCORE		// 分解する数字の桁数
	);

	for (int nCntScore = 0; nCntScore < MAX_SCORE; nCntScore++)
	{ // スコアの桁数分繰り返す

		// 数字の設定
		m_apValue[nCntScore]->BindModel(MODEL_FILE[aNumDivide[nCntScore]]);
	}
}
