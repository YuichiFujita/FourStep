//============================================================
//
//	プレイヤーヘッダー [player.h]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	二重インクルード防止
//************************************************************
#ifndef _PLAYER_H_
#define _PLAYER_H_

//************************************************************
//	インクルードファイル
//************************************************************
#include "objectModel.h"

//************************************************************
//	クラス定義
//************************************************************
// プレイヤークラス
class CPlayer : public CObjectModel
{
public:
	// モデル列挙
	enum EModel
	{
		MODEL_PLAYER = 0,	// プレイヤー
		MODEL_MAX			// この列挙型の総数
	};

	// 状態列挙
	enum EState
	{
		STATE_NONE = 0,	// 何もしない状態
		STATE_SPAWN,	// スポーン状態
		STATE_NORMAL,	// 通常状態
		STATE_KNOCK,	// 吹っ飛び状態
		STATE_DEATH,	// 死亡状態
		STATE_MAX		// この列挙型の総数
	};

	// 軸列挙
	enum EAxis
	{
		AXIS_X = 0,	// X軸
		AXIS_Y,		// Y軸
		AXIS_Z,		// Z軸
		AXIS_MAX	// この列挙型の総数
	};

	// コンストラクタ
	CPlayer();

	// デストラクタ
	~CPlayer() override;

	// オーバーライド関数
	HRESULT Init(void) override;	// 初期化
	void Uninit(void) override;		// 終了
	void Update(void) override;		// 更新
	void Draw(void) override;		// 描画
	void HitKnockBack(const int nDmg, const D3DXVECTOR3 &vecKnock);	// ノックバックヒット

	void SetState(const int nState) override;	// 状態設定
	int GetState(void) const override;			// 状態取得
	float GetRadius(void) const override;		// 半径取得
	float GetHeight(void) const override;		// 縦幅取得

	void SetEnableUpdate(const bool bUpdate) override;	// 更新状況設定
	void SetEnableDraw(const bool bDraw) override;		// 描画状況設定
	D3DXMATRIX GetMtxWorld(void) const override;		// マトリックス取得

	// 静的メンバ関数
	static CPlayer *Create(void);	// 生成

	// メンバ関数
	void SetSpawn(void);	// 出現設定

private:
	// メンバ関数
	void UpdateSpawn(void);		// スポーン状態時の更新
	void UpdateNormal(void);	// 通常状態時の更新
	void UpdateKnock(void);		// 吹っ飛び状態時の更新
	void UpdateDeath(void);		// 死亡状態時の更新

	void UpdateOldPosition(void);			// 過去位置の更新
	void UpdateMove(void);					// 移動量・目標向きの更新
	void UpdateJump(void);					// ジャンプの更新
	void UpdateAttack(void);				// 攻撃の更新
	void UpdateBullet(void);				// 射撃の更新
	void UpdateGravity(void);				// 重力の更新
	bool UpdateLanding(D3DXVECTOR3& rPos);	// 着地状況の更新
	void UpdateRotation(D3DXVECTOR3& rRot);	// 向きの更新
	bool UpdateFadeOut(const float fAdd);	// フェードアウト状態時の更新
	bool UpdateFadeIn(const float fSub);	// フェードイン状態時の更新

	bool ResponseSingleGround(const EAxis axis, D3DXVECTOR3 &rPos);	// 地盤との一軸ごとの当たり判定
	bool CollisionGround(D3DXVECTOR3 &rPos);	// 地盤との当たり判定
	void CollisionEnemy(D3DXVECTOR3 &rPos);		// 敵との当たり判定

	// 静的メンバ変数
	static const char *mc_apModelFile[];	// モデル定数

	// メンバ変数
	D3DXVECTOR3	m_oldPos;		// 過去位置
	D3DXVECTOR3	m_move;			// 移動量
	D3DXVECTOR3	m_destRot;		// 目標向き
	float	m_RSrickRot;	// 右スティックの向き
	EState	m_state;			// 状態
	int		m_nCounterState;	// 状態管理カウンター
	bool	m_bJump;			// ジャンプ状況
};

#endif	// _PLAYER_H_
