//============================================================
//
//	敵ヘッダー [enemy.h]
//	Author：藤田勇一
//
//============================================================
#if 1
//************************************************************
//	二重インクルード防止
//************************************************************
#ifndef _ENEMY_H_
#define _ENEMY_H_

//************************************************************
//	インクルードファイル
//************************************************************
#include "objectModel.h"

//************************************************************
//	クラス定義
//************************************************************
// 敵クラス
class CEnemy : public CObjectModel
{
public:
	// TODO：吹っ飛びと死亡を管理

	// 種類列挙
	enum EType
	{
		TYPE_NORMAL = 0,	// 通常敵
		TYPE_JUMP,			// ジャンプ敵
		TYPE_BULLET,		// 弾発射敵
		TYPE_MAX			// この列挙型の総数
	};

	// 状態列挙
	enum EState
	{
		STATE_SPAWN = 0,	// スポーン状態
		STATE_NORMAL,		// 通常状態
		STATE_KNOCK,		// ノックバック状態
		STATE_DEATH,		// 死亡状態
		STATE_MAX			// この列挙型の総数
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
	explicit CEnemy(const EType type);

	// デストラクタ
	virtual ~CEnemy();

	// ステータス構造体
	struct SStatusInfo
	{
		float fFloorRadius;			// 床半径
		float fRadius;			// 半径
		float fHeight;			// 縦幅
		float fForwardMove;		// 前進の移動量
		float fJump;			// ジャンプ量
		float fAttackRadius;	// 攻撃範囲
		float fLookRev;			// 視認の補正係数
	};

	// オーバーライド関数
	HRESULT Init(void) override;	// 初期化
	void Uninit(void) override;		// 終了
	void Update(void) override;		// 更新
	void Draw(void) override;		// 描画
	void HitKnockBack(const int nDmg, const D3DXVECTOR3& vecKnock) override;	// ノックバックヒット

	void SetState(const int nState) override;		// 状態設定
	int GetState(void) const override;				// 状態取得
	int GetType(void) const override;				// 種類取得
	float GetRadius(void) const override;			// 半径取得
	float GetHeight(void) const override;			// 縦幅取得
	D3DXMATRIX GetMtxWorld(void) const override;	// マトリックス取得

	// 静的メンバ関数
	static CEnemy *Create	// 生成
	( // 引数
		const EType type,			// 種類
		const D3DXVECTOR3& rPos,	// 位置
		const D3DXVECTOR3& rRot		// 向き
	);
	static void RandomSpawn	// ランダム生成
	( // 引数
		const int nNum,		// 生成数
		const EType type	// 種類
	);
	static SStatusInfo GetStatusInfo(const int nType);	// ステータス情報取得
	static int GetNumAll(void);		// 総数取得

	// メンバ関数
	void UpdateOldPosition(void);					// 過去位置更新
	void SetMovePosition(const D3DXVECTOR3& rMove);	// 位置移動量設定
	void SetMoveRotation(const D3DXVECTOR3& rMove);	// 向き変更量設定
	D3DXVECTOR3 GetOldPosition(void) const;			// 過去位置取得
	D3DXVECTOR3 GetMovePosition(void) const;		// 位置移動量取得
	D3DXVECTOR3 GetMoveRotation(void) const;		// 向き変更量取得
	SStatusInfo GetStatusInfo(void) const;			// ステータス情報取得

protected:
	// 仮想関数
	virtual void UpdateSpawn(void);		// スポーン状態時の更新
	virtual void UpdateKnock(void);		// 吹っ飛び状態時の更新
	virtual bool UpdateDeath(void);		// 死亡状態時の更新
	virtual void UpdateAction(void);	// 敵の動作の更新

	// メンバ関数
	void UpdateLook	// 対象視認
	( // 引数
		const D3DXVECTOR3& rPosLook,	// 視認対象位置
		const D3DXVECTOR3& rPosEnemy,	// 敵位置
		D3DXVECTOR3 *pRotEnemy			// 敵向き
	);
	bool UpdateLanding(D3DXVECTOR3 *pPos);	// 着地状況の更新

private:
	// メンバ関数
	bool UpdateFadeOut(const float fAdd);	// フェードアウト状態時の更新
	bool UpdateFadeIn(const float fSub);	// フェードイン状態時の更新

	bool ResponseSingleGround(const EAxis axis, D3DXVECTOR3 &rPos);	// 地盤との一軸ごとの当たり判定
	bool CollisionGround(D3DXVECTOR3 &rPos);	// 地盤との当たり判定

	// 静的メンバ変数
	static SStatusInfo m_aStatusInfo[TYPE_MAX];	// ステータス情報
	static int m_nNumAll;	// 敵の総数

	// メンバ変数
	D3DXVECTOR3	m_oldPos;		// 過去位置
	D3DXVECTOR3	m_movePos;		// 位置移動量
	D3DXVECTOR3	m_moveRot;		// 向き移動量
	D3DXVECTOR3	m_AtkPos;		// 向き移動量
	EState	m_state;			// 状態
	int		m_nCounterState;	// 状態管理カウンター
	bool	m_bJump;			// ジャンプ状況
	bool	m_bAttack;			// こうげき状況
	int	m_bAttackCounter;			// こうげき状況
	const EType m_type;			// 種類定数
	const SStatusInfo m_status;	// ステータス定数
};

#endif	// _ENEMY_H_
#endif
