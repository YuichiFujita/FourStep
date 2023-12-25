//============================================================
//
//	リザルトマネージャーヘッダー [resultManager.h]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	二重インクルード防止
//************************************************************
#ifndef _RESULTMANAGER_H_
#define _RESULTMANAGER_H_

//************************************************************
//	前方宣言
//************************************************************
class CObject2D;	// オブジェクト2Dクラス
class CMultiValue;	// マルチ数字クラス

//************************************************************
//	クラス定義
//************************************************************
// リザルトマネージャークラス
class CResultManager
{
public:
	// テクスチャ列挙
	enum ETexture
	{
		TEXTURE_SCORE = 0,	// スコアテクスチャ
		TEXTURE_MAX			// この列挙型の総数
	};

	// 状態列挙
	enum EState
	{
		STATE_NONE = 0,			// 何もしない状態
		STATE_FADEIN,			// フェードイン状態
		STATE_RESULT,			// スコア表示状態
		STATE_WAIT,				// 遷移待機状態
		STATE_MAX				// この列挙型の総数
	};

	// コンストラクタ
	CResultManager();

	// デストラクタ
	~CResultManager();

	// メンバ関数
	HRESULT Init(void);		// 初期化
	HRESULT Uninit(void);	// 終了
	void Update(void);		// 更新

	// 静的メンバ関数
	static CResultManager *Create(void);	// 生成
	static HRESULT Release(CResultManager *&prResultManager);	// 破棄

private:
	// メンバ関数
	void UpdateFade(void);			// フェードイン
	void UpdateResult(void);		// リザルト表示
	void UpdateTransition(void);	// 遷移決定
	void SkipStaging(void);			// 演出スキップ
	bool UpdateDrawWait(const int nWait);	// 表示待機

	// 静的メンバ変数
	static const char *mc_apTextureFile[];	// テクスチャ定数

	// メンバ変数
	CObject2D *m_pScoreTitle;	// スコアタイトルの情報
	CMultiValue *m_pScore;		// スコアの情報
	CObject2D *m_pFade;			// フェードの情報
	EState m_state;				// 状態
	int m_nCounterState;		// 状態管理カウンター
	float m_fScale;				// ポリゴン拡大率
};

#endif	// _RESULTMANAGER_H_
