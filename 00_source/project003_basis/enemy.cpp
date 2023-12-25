//============================================================
//
//	敵処理 [enemy.cpp]
//	Author：藤田勇一
//
//============================================================
#if 1
//************************************************************
//	インクルードファイル
//************************************************************
#include "enemy.h"
#include "manager.h"
#include "renderer.h"
#include "enemyNormal.h"
#include "scene.h"
#include "player.h"
#include "collision.h"

//************************************************************
//	定数宣言
//************************************************************
namespace
{
	const int	PRIORITY = 3;		// 敵の優先順位
	const int	DAMAGE_FRAME = 12;	// ダメージ状態フレーム数

	const float	GRAVITY		= 1.0f;		// 重力
	const float	REV_MOVE	= 0.16f;	// 通常状態時の空中の移動量の減衰係数

	const float	SPAWN_ADD_ALPHA = 0.0075f;	// スポーン時の透明度の加算量
	const float	DEATH_SUB_ALPHA = 0.05f;	// 死亡時の透明度の減算量
}

//************************************************************
//	静的メンバ変数宣言
//************************************************************
CEnemy::SStatusInfo CEnemy::m_aStatusInfo[CEnemy::TYPE_MAX] =	// ステータス情報
{
	// 通常敵のステータス情報
	{
		40.0f,	// 半径
		40.0f,	// 縦幅
		2.0f,	// 前進の移動量
		2.0f,	// ジャンプ量
		100.0f,	// 攻撃範囲
		0.5f,	// 視認の補正係数
	},

	// ジャンプ敵のステータス情報
	{
		0.0f,	// 半径
		0.0f,	// 縦幅
		0.0f,	// 前進の移動量
		0.0f,	// ジャンプ量
		0.0f,	// 攻撃範囲
		0.0f,	// 視認の補正係数
	},

	// 弾発射敵のステータス情報
	{
		0.0f,	// 半径
		0.0f,	// 縦幅
		0.0f,	// 前進の移動量
		0.0f,	// ジャンプ量
		0.0f,	// 攻撃範囲
		0.0f,	// 視認の補正係数
	},
};
int CEnemy::m_nNumAll = 0;	// 敵の総数

//************************************************************
//	子クラス [CEnemy] のメンバ関数
//************************************************************
//============================================================
//	コンストラクタ
//============================================================
CEnemy::CEnemy(const EType type) : CObjectModel(CObject::LABEL_ENEMY, PRIORITY), m_type(type), m_status(m_aStatusInfo[type])
{
	// メンバ変数をクリア
	m_oldPos	= VEC3_ZERO;	// 過去位置
	m_movePos	= VEC3_ZERO;	// 位置移動量
	m_moveRot	= VEC3_ZERO;	// 向き変更量
	m_state		= STATE_SPAWN;	// 状態
	m_nCounterState = 0;		// 状態管理カウンター

	// 敵の総数を加算
	m_nNumAll++;
}

//============================================================
//	デストラクタ
//============================================================
CEnemy::~CEnemy()
{
	// 敵の総数を減算
	m_nNumAll--;
}

//============================================================
//	初期化処理
//============================================================
HRESULT CEnemy::Init(void)
{
	// メンバ変数を初期化
	m_oldPos	= VEC3_ZERO;	// 過去位置
	m_movePos	= VEC3_ZERO;	// 位置移動量
	m_moveRot	= VEC3_ZERO;	// 向き変更量
	m_state		= STATE_SPAWN;	// 状態
	m_nCounterState = 0;		// 状態管理カウンター

	// オブジェクトモデルの初期化
	if (FAILED(CObjectModel::Init()))
	{ // 初期化に失敗した場合

		// 失敗を返す
		assert(false);
		return E_FAIL;
	}

	// 成功を返す
	return S_OK;
}

//============================================================
//	終了処理
//============================================================
void CEnemy::Uninit(void)
{
	// オブジェクトモデルの終了
	CObjectModel::Uninit();
}

//============================================================
//	更新処理
//============================================================
void CEnemy::Update(void)
{
	// オブジェクトモデルの更新
	CObjectModel::Update();
}

//============================================================
//	描画処理
//============================================================
void CEnemy::Draw(void)
{
	// オブジェクトモデルの描画
	CObjectModel::Draw();
}

//============================================================
//	ノックバックヒット処理
//============================================================
void CEnemy::HitKnockBack(const int nDmg, const D3DXVECTOR3& vec)
{
#if 0
	// 変数を宣言
	D3DXVECTOR3 pos = GetVec3Position();	// 敵位置
	D3DXVECTOR3 vecKnock = vec;				// ノックバックベクトル

	if (IsDeath() != true && m_state == STATE_NORMAL)
	{ // 死亡フラグが立っていない且つ、通常状態の場合

		// レベルを加算
		m_pBubble->AddLevel(nDmg);

		if (m_pBubble->GetLevel() < m_status.nLife)
		{ // 生きている場合

			// ノックバック移動量を設定
			vecKnock.y = 0.0f;									// 縦ベクトルを初期化
			D3DXVec3Normalize(&vecKnock, &vecKnock);			// ベクトルを正規化
			m_moveKnock = vecKnock * m_status.fKnockBackSide;	// ノックバック横移動量を計算
			m_moveKnock.y = m_status.fKnockBackUp;				// ノックバック縦移動量を代入

			// カウンターを初期化
			m_nCounterState = 0;
			m_nCounterBubble = 0;

			// 状態を設定
			m_state = STATE_DAMAGE;	// ダメージ状態
		}
		else
		{ // 死んでいる場合

			// モーションを更新しない状態にする
			SetEnableMotionUpdate(false);

			// 方向表示を削除
			m_pWay->Delete();

			// 状態を設定
			m_state = STATE_DEATH;	// 死亡状態

			// サウンドの再生
			CManager::GetSound()->Play(CSound::LABEL_SE_FLY);	// 浮遊音
		}

		// パーティクル3Dオブジェクトを生成
		CParticle3D::Create(CParticle3D::TYPE_BUBBLE_EXPLOSION, pos);
	}
#endif
}

//============================================================
//	生成処理
//============================================================
CEnemy *CEnemy::Create(const EType type, const D3DXVECTOR3& rPos, const D3DXVECTOR3& rRot)
{
	// ポインタを宣言
	CEnemy *pEnemy = nullptr;	// 敵生成用

	if (pEnemy == nullptr)
	{ // 使用されていない場合

		// メモリ確保
		switch (type)
		{ // 種類ごとの処理
		case TYPE_NORMAL:

			// 通常敵を生成
			pEnemy = new CEnemyNormal(type);

			break;

		default:	// 例外処理
			assert(false);
			break;
		}
	}
	else { assert(false); return nullptr; }	// 使用中

	if (pEnemy != nullptr)
	{ // 使用されている場合
		
		// 敵の初期化
		if (FAILED(pEnemy->Init()))
		{ // 初期化に失敗した場合

			// メモリ開放
			delete pEnemy;
			pEnemy = NULL;

			// 失敗を返す
			return NULL;
		}

		// 位置を設定
		pEnemy->SetVec3Position(rPos);

		// 向きを設定
		pEnemy->SetVec3Rotation(rRot);

		// 確保したアドレスを返す
		return pEnemy;
	}
	else { assert(false); return NULL; }	// 確保失敗
}

//============================================================
//	ランダム生成処理
//============================================================
void CEnemy::RandomSpawn
(
	const int nNum,		// 生成数
	const EType type	// 種類
)
{
	// 変数を宣言
	D3DXVECTOR3 pos, rot;	// 位置・向き設定用

#if 0
	for (int nCntGrow = 0; nCntGrow < nNum; nCntGrow++)
	{ // 生成数分繰り返す

		// ターゲット位置を取得
		posTarget = pTarget->GetPosition();

		// 生成位置を設定
		pos.x = (float)(rand() % ((int)LIMIT_RADIUS * 2) - (int)LIMIT_RADIUS + 1);
		pos.y = m_aStatusInfo[type].fSpawnHeight;
		pos.z = (float)(rand() % ((int)LIMIT_RADIUS * 2) - (int)LIMIT_RADIUS + 1);

		// 生成向きを設定
		rot = VEC3_ZERO;	// 向きを初期化
		rot.y = atan2f(pos.x - posTarget.x, pos.z - posTarget.z);	// ターゲットの方向を向かせる

		// 位置を補正
		pos.x = sinf(rot.y) * (LIMIT_RADIUS - m_aStatusInfo[type].fRadius);
		pos.z = cosf(rot.y) * (LIMIT_RADIUS - m_aStatusInfo[type].fRadius);

		// 敵オブジェクトの生成
		CEnemy::Create(type, pos, rot);
	}
#endif
}

//============================================================
//	ステータス情報取得処理
//============================================================
CEnemy::SStatusInfo CEnemy::GetStatusInfo(const int nType)
{
	// 引数の種類のステータス情報を返す
	return m_aStatusInfo[nType];
}

//============================================================
//	総数取得処理
//============================================================
int CEnemy::GetNumAll(void)
{
	// 現在の敵の総数を返す
	return m_nNumAll;
}

//============================================================
//	過去位置の更新処理
//============================================================
void CEnemy::UpdateOldPosition(void)
{
	// 過去位置を更新
	m_oldPos = GetVec3Position();
}

//============================================================
//	位置移動量の設定処理
//============================================================
void CEnemy::SetMovePosition(const D3DXVECTOR3& rMove)
{
	// 引数の位置移動量を設定
	m_movePos = rMove;
}

//============================================================
//	向き変更量の設定処理
//============================================================
void CEnemy::SetMoveRotation(const D3DXVECTOR3& rMove)
{
	// 引数の向きを設定
	m_moveRot = rMove;

	// 向きの正規化
	useful::Vec3NormalizeRot(m_moveRot);
}

//============================================================
//	状態の設定処理
//============================================================
void CEnemy::SetState(const int nState)
{
	// 引数の状態を設定
	m_state = (EState)nState;
}

//============================================================
//	マトリックス取得処理
//============================================================
D3DXMATRIX CEnemy::GetMtxWorld(void) const
{
	// 変数を宣言
	D3DXMATRIX mtxRot, mtxTrans, mtxWorld;		// 計算用マトリックス
	D3DXVECTOR3 posEnemy = GetVec3Position();	// 敵位置
	D3DXVECTOR3 rotEnemy = GetVec3Rotation();	// 敵向き

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&mtxWorld);

	// 向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, rotEnemy.y, rotEnemy.x, rotEnemy.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);

	// 位置を反映
	D3DXMatrixTranslation(&mtxTrans, posEnemy.x, posEnemy.y, posEnemy.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTrans);

	// ワールドマトリックスを返す
	return mtxWorld;
}

//============================================================
//	過去位置取得処理
//============================================================
D3DXVECTOR3 CEnemy::GetOldPosition(void) const
{
	// 過去位置を返す
	return m_oldPos;
}

//============================================================
//	位置移動量取得処理
//============================================================
D3DXVECTOR3 CEnemy::GetMovePosition(void) const
{
	// 位置移動量を返す
	return m_movePos;
}

//============================================================
//	向き変更量取得処理
//============================================================
D3DXVECTOR3 CEnemy::GetMoveRotation(void) const
{
	// 向き変更量を返す
	return m_moveRot;
}

//============================================================
//	状態取得処理
//============================================================
int CEnemy::GetState(void) const
{
	// 状態を返す
	return m_state;
}

//============================================================
//	種類取得処理
//============================================================
int CEnemy::GetType(void) const
{
	// 種類を返す
	return m_type;
}

//============================================================
//	半径取得処理
//============================================================
float CEnemy::GetRadius(void) const
{
	// 半径を返す
	return m_status.fRadius;
}

//============================================================
//	縦幅取得処理
//============================================================
float CEnemy::GetHeight(void) const
{
	// 縦幅を返す
	return m_status.fHeight;
}

//============================================================
//	ステータス情報取得処理
//============================================================
CEnemy::SStatusInfo CEnemy::GetStatusInfo(void) const
{
	// ステータス情報を返す
	return m_status;
}

//============================================================
//	スポーン状態時の更新
//============================================================
void CEnemy::UpdateSpawn(void)
{
	// フェードアウトの更新
	if (UpdateFadeOut(SPAWN_ADD_ALPHA))
	{ // 不透明になった場合

		// 通常状態にする
		m_state = STATE_NORMAL;
	}
}

//============================================================
//	吹っ飛び状態時の更新
//============================================================
void CEnemy::UpdateKnock(void)
{
	if (m_nCounterState < DAMAGE_FRAME)
	{ // カウンターが一定値より小さい場合

		// カウンターを加算
		m_nCounterState++;

		// マテリアルを全設定
		SetAllMaterial(material::Red());	// 赤
	}
	else
	{ // カウンターが一定値以上の場合

		// カウンターを初期化
		m_nCounterState = 0;

		// マテリアル再設定
		ResetMaterial();

		// 通常状態にする
		m_state = STATE_NORMAL;
	}
}

//============================================================
//	死亡状態時の更新
//============================================================
bool CEnemy::UpdateDeath(void)
{
	// フェードインの更新
	if (UpdateFadeIn(DEATH_SUB_ALPHA))
	{ // 透明になった場合

		// 敵を終了
		Uninit();

		// 死亡を返す
		return true;
	}

	// 非死亡を返す
	return false;
}

//============================================================
//	敵動作の更新処理
//============================================================
void CEnemy::UpdateAction(void)
{
	// ポインタを宣言
	CPlayer *pPlayer = CScene::GetPlayer();	// プレイヤー情報
	assert(pPlayer != nullptr);

	// 変数を宣言
	SStatusInfo  status = GetStatusInfo();				// 敵ステータス
	D3DXVECTOR3 posEnemy = GetVec3Position();			// 敵位置
	D3DXVECTOR3 moveEnemy = GetMovePosition();			// 敵移動量
	D3DXVECTOR3 rotEnemy = GetVec3Rotation();			// 敵向き
	D3DXVECTOR3 posLook = pPlayer->GetVec3Position();	// プレイヤー位置
	float fPlayerRadius = pPlayer->GetRadius();			// プレイヤー半径

	// 過去位置の更新
	UpdateOldPosition();

	// 視認対象の攻撃判定
	if (!collision::Circle2D(posLook, posEnemy, fPlayerRadius, status.fAttackRadius))
	{ // 敵の攻撃範囲外の場合

		// 対象の方向を向かせる
		Look(posLook, posEnemy, &rotEnemy);

		// 対象の方向に移動 (前進)
		moveEnemy.x -= sinf(rotEnemy.y) * status.fForwardMove;
		moveEnemy.z -= cosf(rotEnemy.y) * status.fForwardMove;

		// 重力を加算
		//moveEnemy.y -= GRAVITY;

		// 移動量を加算
		posEnemy += moveEnemy;

		// 移動量を減衰
		moveEnemy.x += (0.0f - moveEnemy.x) * REV_MOVE;
		moveEnemy.z += (0.0f - moveEnemy.z) * REV_MOVE;
	}
	else
	{ // 敵の攻撃範囲内の場合


	}

	// 位置を反映
	SetVec3Position(posEnemy);

	// 位置移動量を反映
	SetMovePosition(moveEnemy);

	// 向きを反映
	SetVec3Rotation(rotEnemy);
}

//============================================================
//	対象視認処理
//============================================================
void CEnemy::Look(const D3DXVECTOR3& rPosLook, const D3DXVECTOR3& rPosEnemy, D3DXVECTOR3 *pRotEnemy)
{
	// 変数を宣言
	float fDestRot = 0.0f;	// 目標向き
	float fDiffRot = 0.0f;	// 向き

	// 視認対象の方向を代入
	fDestRot = atan2f(rPosEnemy.x - rPosLook.x, rPosEnemy.z - rPosLook.z);	// 目標向き

	// 差分向きを求める
	fDiffRot = fDestRot - pRotEnemy->y;
	useful::NormalizeRot(fDiffRot);		// 差分向きの正規化

	// 向きの更新
	pRotEnemy->y += fDiffRot * m_status.fLookRev;
	useful::NormalizeRot(pRotEnemy->y);	// 向きの正規化
}

//============================================================
//	フェードアウト状態時の更新処理
//============================================================
bool CEnemy::UpdateFadeOut(const float fAdd)
{
	// 変数を宣言
	bool bAlpha = false;		// 透明状況
	float fAlpha = GetAlpha();	// 透明度

	// プレイヤー自身の描画を再開
	CObject::SetEnableDraw(true);

	// 透明度を上げる
	fAlpha += fAdd;

	if (fAlpha >= GetMaxAlpha())
	{ // 透明度が上がり切った場合

		// 透明度を補正
		fAlpha = GetMaxAlpha();

		// 不透明になり切った状態にする
		bAlpha = true;
	}

	// 透明度を設定
	SetAlpha(fAlpha);

	// 透明状況を返す
	return bAlpha;
}

//============================================================
//	フェードイン状態時の更新処理
//============================================================
bool CEnemy::UpdateFadeIn(const float fSub)
{
	// 変数を宣言
	bool bAlpha = false;		// 透明状況
	float fAlpha = GetAlpha();	// 透明度

	// 透明度を下げる
	fAlpha -= fSub;

	if (fAlpha <= 0.0f)
	{ // 透明度が下がり切った場合

		// 透明度を補正
		fAlpha = 0.0f;

		// 透明になり切った状態にする
		bAlpha = true;

		// プレイヤー自身の描画を停止
		CObject::SetEnableDraw(false);
	}

	// 透明度を設定
	SetAlpha(fAlpha);

	// 透明状況を返す
	return bAlpha;
}
#endif
