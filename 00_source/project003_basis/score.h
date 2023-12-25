//============================================================
//
//	スコアヘッダー [score.h]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	二重インクルード防止
//************************************************************
#ifndef _SCORE_H_
#define _SCORE_H_

//************************************************************
//	インクルードファイル
//************************************************************
#include "object.h"

//************************************************************
//	マクロ定義
//************************************************************
#define MAX_SCORE	(3)	// スコアの桁数

//************************************************************
//	前方宣言
//************************************************************
class CModelUI;	// モデルUIクラス

//************************************************************
//	クラス定義
//************************************************************
// スコアクラス
class CScore : public CObject
{
public:
	// コンストラクタ
	CScore();

	// デストラクタ
	~CScore();

	// オーバーライド関数
	HRESULT Init(void) override;	// 初期化
	void Uninit(void) override;		// 終了
	void Update(void) override;		// 更新
	void Draw(void) override;		// 描画
	void SetVec3Position(const D3DXVECTOR3& rPos) override;		// 位置設定
	void SetVec3Scaling(const D3DXVECTOR3& rScale) override;	// 拡大率設定
	void SetPriority(const int nPriority) override;				// 優先順位設定
	void SetEnableUpdate(const bool bUpdate) override;			// 更新状況設定
	void SetEnableDraw(const bool bDraw) override;				// 描画状況設定
	D3DXVECTOR3 GetVec3Position(void) const override;			// 位置取得
	D3DXVECTOR3 GetVec3Scaling(void) const override;			// 拡大率取得

	// 静的メンバ関数
	static CScore *Create	// 生成
	( // 引数
		const D3DXVECTOR3& rPos,	// 位置
		const D3DXVECTOR3& rScale,	// 大きさ
		const D3DXVECTOR3& rSpace	// 空白
	);

	// メンバ関数
	void Add(const int nNum);	// 加算
	void Set(const int nNum);	// 設定
	int  Get(void);				// 取得
	void SetSpace(const D3DXVECTOR3 &rSpace);	// 空白設定
	D3DXVECTOR3 GetSpace(void) const;			// 空白取得

private:
	// オーバーライド関数
	void Release(void) override;	// 破棄

	// メンバ関数
	void SetDrawValue(void);	// 数字の表示設定
	void SetTexNum(void);		// 数字のテクスチャ座標設定

	// メンバ変数
	CModelUI *m_apValue[MAX_SCORE];	// 数値の情報
	D3DXVECTOR3 m_pos;		// 位置
	D3DXVECTOR3 m_scale;	// 大きさ
	D3DXVECTOR3 m_space;	// 空白
	int m_nNum;				// スコア
};

#endif	// _SCORE_H_
