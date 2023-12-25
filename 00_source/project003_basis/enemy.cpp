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

//************************************************************
//	定数宣言
//************************************************************
namespace
{
	const int PRIORITY = 3;			// 敵の優先順位
	const int DAMAGE_FRAME = 12;	// ダメージ状態フレーム数
}

//************************************************************
//	静的メンバ変数宣言
//************************************************************
CEnemy::StatusInfo CEnemy::m_aStatusInfo[CEnemy::TYPE_MAX] = {};	// ステータス情報
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
CEnemy::StatusInfo CEnemy::GetStatusInfo(const int nType)
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
CEnemy::StatusInfo CEnemy::GetStatusInfo(void) const
{
	// ステータス情報を返す
	return m_status;
}

//============================================================
//	スポーン動作
//============================================================
void CEnemy::Spawn(void)
{

}

//============================================================
//	ダメージ動作
//============================================================
void CEnemy::Damage(void)
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

		// 状態を設定
		m_state = STATE_NORMAL;	// 通常状態
	}
}

//============================================================
//	死亡動作
//============================================================
bool CEnemy::Death(void)
{
	return true;
}

//============================================================
//	対象視認処理
//============================================================
void CEnemy::Look(const D3DXVECTOR3& rPosLook, const D3DXVECTOR3& rPosEnemy, D3DXVECTOR3& rRotEnemy)
{
	// 変数を宣言
	float fDestRot = 0.0f;	// 目標向き
	float fDiffRot = 0.0f;	// 向き

	// 視認対象の方向を代入
	fDestRot = atan2f(rPosEnemy.x - rPosLook.x, rPosEnemy.z - rPosLook.z);	// 目標向き

	// 差分向きを求める
	fDiffRot = fDestRot - rRotEnemy.y;
	useful::NormalizeRot(fDiffRot);		// 差分向きの正規化

	// 向きの更新
	rRotEnemy.y += fDiffRot * m_status.fLookRev;
	useful::NormalizeRot(rRotEnemy.y);	// 向きの正規化
}
#endif
