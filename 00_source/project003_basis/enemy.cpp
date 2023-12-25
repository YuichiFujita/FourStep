//============================================================
//
//	敵処理 [enemy.cpp]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	インクルードファイル
//************************************************************
#include "enemy.h"
#include "manager.h"
#include "renderer.h"
#include "sound.h"
#include "enemyNormal.h"
#include "scene.h"
#include "sceneGame.h"
#include "score.h"
#include "stage.h"
#include "player.h"
#include "collision.h"
#include "effect3D.h"
#include "ground.h"
#include "map.h"
#include "gamemanager.h"

//************************************************************
//	定数宣言
//************************************************************
namespace
{
	const int	PRIORITY = 3;		// 敵の優先順位
	const int	DAMAGE_FRAME = 12;	// ダメージ状態フレーム数

	const float	GRAVITY		= 1.0f;		// 重力
	const float	JUMP_REV	= 0.16f;	// 空中の移動量の減衰係数
	const float	LAND_REV	= 0.16f;	// 地上の移動量の減衰係数
	const float	KNOCK_REV	= 0.045f;	// 吹っ飛び状態時の移動量の減衰係数
	const float	KNOCK_UP	= 15.0f;	// ノック上昇量
	const float	KNOCK_SIDE	= 35.0f;	// ノック横移動量

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
		100.0f,	// 半径
		50.0f,	// 半径
		40.0f,	// 縦幅
		0.5f,	// 前進の移動量
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
	m_movePos	= D3DXVECTOR3(0.0f,100.0f,0.0f);	// 位置移動量
	m_moveRot	= VEC3_ZERO;	// 向き変更量
	m_AtkPos = VEC3_ZERO;
	m_state		= STATE_SPAWN;	// 状態
	m_bJump		= false;		// ジャンプ状況
	m_bAttack = false;
	m_bAttackCounter = 0;
	m_nCounterState	= 0;		// 状態管理カウンター

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
	m_bJump		= true;			// ジャンプ状況
	m_nCounterState	= 0;		// 状態管理カウンター

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
void CEnemy::HitKnockBack(const int nDmg, const D3DXVECTOR3&vecKnock)
{
	if (IsDeath())
	{ // 死亡フラグが立っている場合

		return;
	}

	if (m_state != STATE_NORMAL)
	{ // 通常状態ではない場合

		return;
	}

	// 変数を宣言
	D3DXVECTOR3 posPlayer = GetVec3Position();	// プレイヤー位置
	D3DXVECTOR3 rotPlayer = GetVec3Rotation();	// プレイヤー向き

	// カウンターを初期化
	m_nCounterState = 0;

	// ノックバック移動量を設定
	m_movePos.x = KNOCK_SIDE * vecKnock.x;
	m_movePos.y = KNOCK_UP;
	m_movePos.z = KNOCK_SIDE * vecKnock.z;

	// ノックバック方向に向きを設定
	rotPlayer.y = atan2f(vecKnock.x, vecKnock.z);	// 吹っ飛び向きを計算
	SetVec3Rotation(rotPlayer);	// 向きを設定

	// 空中状態にする
	m_bJump = true;

	// ノック状態を設定
	SetState(STATE_KNOCK);

	// サウンドの再生
	CManager::GetInstance()->GetSound()->Play(CSound::LABEL_SE_HIT);	// ヒット音
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
	// 変数を宣言
	D3DXVECTOR3 posEnemy = GetVec3Position();	// プレイヤー位置

	// ポインタを宣言
	CStage *pStage = CScene::GetStage();	// ステージ情報
	assert(pStage != nullptr);

	// マテリアルを全設定
	SetAllMaterial(material::Red());	// 赤

	// 重力を与える
	m_movePos.y -= GRAVITY;

	if (m_movePos.y < 0.0f)
	{
		// 通常状態にする
		m_state = STATE_NORMAL;
	}

	// 着地判定
	if (UpdateLanding(&posEnemy))
	{ // 着地した場合

	}

	// ステージ範囲外の補正
	pStage->LimitPosition(posEnemy, m_status.fRadius);

	// キルYとの判定
	if (pStage->CollisionKillY(posEnemy))
	{ // キルYより下の位置にいる場合

		// 死亡状態にする
		m_state = STATE_DEATH;

		// マテリアル再設定
		ResetMaterial();
	}

	// 位置を反映
	SetVec3Position(posEnemy);
}

//============================================================
//	死亡状態時の更新
//============================================================
bool CEnemy::UpdateDeath(void)
{
	// 変数を宣言
	D3DXVECTOR3 posEnemy = GetVec3Position();	// 敵位置

	// 過去位置の更新
	UpdateOldPosition();

	// 重力を与える
	m_movePos.y -= GRAVITY;

	// 着地状況の更新
	UpdateLanding(&posEnemy);

	// 位置を反映
	SetVec3Position(posEnemy);

	// フェードインの更新
	if (UpdateFadeIn(DEATH_SUB_ALPHA))
	{ // 透明になった場合

		// 敵を終了
		Uninit();

		// スコア加算
		CSceneGame::GetScore()->Add(1);

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

	CStage *pStage = CScene::GetStage();	// ステージ情報
	assert(pStage != nullptr);

	// 変数を宣言
	SStatusInfo  status = GetStatusInfo();				// 敵ステータス
	D3DXVECTOR3 posEnemy = GetVec3Position();			// 敵位置
	D3DXVECTOR3 rotEnemy = GetVec3Rotation();			// 敵向き
	D3DXVECTOR3 posLook = pPlayer->GetVec3Position();	// プレイヤー位置
	float fPlayerRadius = pPlayer->GetRadius();			// プレイヤー半径

	// マテリアル再設定
	ResetMaterial();

	// 過去位置の更新
	UpdateOldPosition();

	// 重力を与える
	m_movePos.y -= GRAVITY;

	for (int nCntPri = 0; nCntPri < object::MAX_PRIO; nCntPri++)
	{ // 優先順位の総数分繰り返す
		// ポインタを宣言
		CObject* pObjectTop = CObject::GetTop(nCntPri);	// 先頭オブジェクト
		if (pObjectTop != NULL)
		{ // 先頭が存在する場合

			// ポインタを宣言
			CObject* pObjCheck = pObjectTop;	// オブジェクト確認用

			while (pObjCheck != NULL)
			{ // オブジェクトが使用されている場合繰り返す

				// ポインタを宣言
				CObject* pObjectNext = pObjCheck->GetNext();	// 次オブジェクト

				if (pObjCheck->GetLabel() == CObject::LABEL_GROUND)
				{ // オブジェクトラベルが地盤ではない場合

					D3DXVECTOR3 posBlock = pObjCheck->GetVec3Position();	// 敵位置
					CGround* pGround = (CGround*)pObjCheck;

					if (collision::Circle2D(GetVec3Position(), posBlock, 50.0f, 50.0f) == true)
					{
						pGround->DelColor(0.005f);
					}
				}

				// 次のオブジェクトへのポインタを代入
				pObjCheck = pObjectNext;
			}
		}
	}

	m_AtkPos.x = GetVec3Position().x + sinf(GetVec3Rotation().y) * -100.0f;
	m_AtkPos.y = 0.0f;
	m_AtkPos.z = GetVec3Position().z + cosf(GetVec3Rotation().y) * -100.0f;


	//CEffect3D::Create(m_AtkPos, 100.0f, CEffect3D::TYPE_NORMAL, 10);

	// 視認対象の攻撃判定
	if (pPlayer->GetState() != CPlayer::STATE_DEATH)
	{ // プレイヤーが死んでいない場合
		if (m_bAttack == false)
		{
			if (!collision::Circle2D(posLook, posEnemy, fPlayerRadius, status.fAttackRadius))
			{ // 敵の攻撃範囲外の場合

				// 対象の方向を向かせる
				UpdateLook(posLook, posEnemy, &rotEnemy);

				// 対象の方向に移動 (前進)
				m_movePos.x -= sinf(rotEnemy.y) * status.fForwardMove;
				m_movePos.z -= cosf(rotEnemy.y) * status.fForwardMove;
			}
			else
			{ // 敵の攻撃範囲内の場合

				for (int nCntPri = 0; nCntPri < object::MAX_PRIO; nCntPri++)
				{ // 優先順位の総数分繰り返す
					// ポインタを宣言
					CObject* pObjectTop = CObject::GetTop(nCntPri);	// 先頭オブジェクト
					if (pObjectTop != NULL)
					{ // 先頭が存在する場合

						// ポインタを宣言
						CObject* pObjCheck = pObjectTop;	// オブジェクト確認用

						while (pObjCheck != NULL)
						{ // オブジェクトが使用されている場合繰り返す

							// ポインタを宣言
							CObject* pObjectNext = pObjCheck->GetNext();	// 次オブジェクト

							if (pObjCheck->GetLabel() == CObject::LABEL_GROUND)
							{ // オブジェクトラベルが地盤ではない場合

								D3DXVECTOR3 posBlock = pObjCheck->GetVec3Position();	// 敵位置
								CGround* pGround = (CGround*)pObjCheck;

								if (collision::Circle2D(m_AtkPos, posBlock, 100.0f, 50.0f) == true)
								{
									m_bAttack = true;
									m_bAttackCounter = 120;
									pGround->DelColor(0.3f);
								}
							}

							// 次のオブジェクトへのポインタを代入
							pObjCheck = pObjectNext;
						}
					}
				}
			}
		}
		else
		{
			if (m_bAttackCounter > 0)
			{
				m_bAttackCounter--;
			}
			else
			{
				m_bAttack = false;
			}
		}
	}

	// 着地状況の更新
	UpdateLanding(&posEnemy);

	// ステージ範囲外の補正
	pStage->LimitPosition(posEnemy, m_status.fRadius);

	// キルYとの判定
	if (pStage->CollisionKillY(posEnemy))
	{ // キルYより下の位置にいる場合

		// 死亡状態にする
		m_state = STATE_DEATH;
	}

	// 位置を反映
	SetVec3Position(posEnemy);

	// 向きを反映
	SetVec3Rotation(rotEnemy);
}

//============================================================
//	対象視認処理
//============================================================
void CEnemy::UpdateLook(const D3DXVECTOR3& rPosLook, const D3DXVECTOR3& rPosEnemy, D3DXVECTOR3 *pRotEnemy)
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
//	着地状況の更新処理
//============================================================
bool CEnemy::UpdateLanding(D3DXVECTOR3 *pPos)
{
	// 変数を宣言
	bool bLand = false;	// 着地状況

	// ジャンプしている状態にする
	m_bJump = true;

	// 位置の更新
	// 地盤の当たり判定・着地判定
	if (CollisionGround(*pPos))
	{ // 地盤に着地していた場合

		// 着地している状態にする
		bLand = true;

		// ジャンプしていない状態にする
		m_bJump = false;
	}

	// 着地状況を返す
	return bLand;
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

//============================================================
//	地盤との一軸ごとの当たり判定
//============================================================
bool CEnemy::ResponseSingleGround(const EAxis axis, D3DXVECTOR3& rPos)
{
	// 変数を宣言
	D3DXVECTOR3 sizeMinPlayer = D3DXVECTOR3(m_status.fFloorRadius, 0.0f,				m_status.fFloorRadius);	// 敵の最小大きさ
	D3DXVECTOR3 sizeMaxPlayer = D3DXVECTOR3(m_status.fFloorRadius, m_status.fHeight, m_status.fFloorRadius);	// 敵の最大大きさ
	bool bMin = false;	// 不の方向の判定状況
	bool bMax = false;	// 正の方向の判定状況
	bool bHit = false;	// 着地の判定情報

	for (int nCntPri = 0; nCntPri < object::MAX_PRIO; nCntPri++)
	{ // 優先順位の総数分繰り返す

		// ポインタを宣言
		CObject *pObjectTop = CObject::GetTop(nCntPri);	// 先頭オブジェクト

		if (pObjectTop != NULL)
		{ // 先頭が存在する場合

			// ポインタを宣言
			CObject *pObjCheck = pObjectTop;	// オブジェクト確認用

			while (pObjCheck != NULL)
			{ // オブジェクトが使用されている場合繰り返す

				// 変数を宣言
				D3DXVECTOR3 posGround = VEC3_ZERO;		// 地盤位置
				D3DXVECTOR3 rotGround = VEC3_ZERO;		// 地盤向き
				D3DXVECTOR3 sizeMinGround = VEC3_ZERO;	// 地盤最小大きさ
				D3DXVECTOR3 sizeMaxGround = VEC3_ZERO;	// 地盤最大大きさ

				// ポインタを宣言
				CObject *pObjectNext = pObjCheck->GetNext();	// 次オブジェクト

				if (pObjCheck->GetLabel() != CObject::LABEL_GROUND)
				{ // オブジェクトラベルが地盤ではない場合

					// 次のオブジェクトへのポインタを代入
					pObjCheck = pObjectNext;

					// 次の繰り返しに移行
					continue;
				}

				// 地盤の位置を設定
				posGround = pObjCheck->GetVec3Position();

				// 地盤の向きを設定
				rotGround = pObjCheck->GetVec3Rotation();

				// 地盤の最小の大きさを設定
				sizeMinGround = pObjCheck->GetVec3Sizing();
				sizeMinGround.y *= 2.0f;	// 縦の大きさを倍にする

				// 地盤の最大の大きさを設定
				sizeMaxGround = pObjCheck->GetVec3Sizing();
				sizeMaxGround.y = 0.0f;		// 縦の大きさを初期化

				switch (axis)
				{ // 判定軸ごとの処理
				case AXIS_X:	// X軸

					// X軸の衝突判定
					collision::ResponseSingleX
					( // 引数
						rPos,			// 判定位置
						m_oldPos,		// 判定過去位置
						posGround,		// 判定目標位置
						sizeMaxPlayer,	// 判定サイズ(右・上・後)
						sizeMinPlayer,	// 判定サイズ(左・下・前)
						sizeMaxGround,	// 判定目標サイズ(右・上・後)
						sizeMinGround,	// 判定目標サイズ(左・下・前)
						&m_movePos		// 移動量
					);

					break;

				case AXIS_Y:	// Y軸

					// Y軸の衝突判定
					collision::ResponseSingleY
					( // 引数
						rPos,			// 判定位置
						m_oldPos,		// 判定過去位置
						posGround,		// 判定目標位置
						sizeMaxPlayer,	// 判定サイズ(右・上・後)
						sizeMinPlayer,	// 判定サイズ(左・下・前)
						sizeMaxGround,	// 判定目標サイズ(右・上・後)
						sizeMinGround,	// 判定目標サイズ(左・下・前)
						&m_movePos,		// 移動量
						true,			// X判定
						true,			// Z判定
						&bMin,			// 下からの判定
						&bMax			// 上からの判定
					);

					if (bMax)
					{ // 上から当たっていた場合

						// 着地している状況にする
						bHit = true;
					}

					break;

				case AXIS_Z:	// Z軸

					// Z軸の衝突判定
					collision::ResponseSingleZ
					( // 引数
						rPos,			// 判定位置
						m_oldPos,		// 判定過去位置
						posGround,		// 判定目標位置
						sizeMaxPlayer,	// 判定サイズ(右・上・後)
						sizeMinPlayer,	// 判定サイズ(左・下・前)
						sizeMaxGround,	// 判定目標サイズ(右・上・後)
						sizeMinGround,	// 判定目標サイズ(左・下・前)
						&m_movePos		// 移動量
					);

					break;

				default:	// 例外処理
					assert(false);
					break;
				}

				// 次のオブジェクトへのポインタを代入
				pObjCheck = pObjectNext;
			}
		}
	}

	// 各軸の判定情報を返す
	return bHit;
}

//============================================================
//	地盤との当たり判定
//============================================================
bool CEnemy::CollisionGround(D3DXVECTOR3& rPos)
{
	// 変数を宣言
	bool bLand = false;	// 着地状況

	// 移動量を加算
	rPos.x += m_movePos.x;

	// X軸の当たり判定
	ResponseSingleGround(AXIS_X, rPos);

	// 移動量を加算
	rPos.y += m_movePos.y;

	// Y軸の当たり判定
	bLand = ResponseSingleGround(AXIS_Y, rPos);

	// 移動量を加算
	rPos.z += m_movePos.z;

	// Z軸の当たり判定
	ResponseSingleGround(AXIS_Z, rPos);

	if (m_state == STATE_KNOCK)
	{ // ノック状態の場合

		m_movePos.x += (0.0f - m_movePos.x) * KNOCK_REV;
		m_movePos.z += (0.0f - m_movePos.z) * KNOCK_REV;
	}
	else
	{ // それ以外の状態の場合

		// 移動量を減衰
		if (m_bJump)
		{ // 空中の場合

			m_movePos.x += (0.0f - m_movePos.x) * JUMP_REV;
			m_movePos.z += (0.0f - m_movePos.z) * JUMP_REV;
		}
		else
		{ // 地上の場合

			m_movePos.x += (0.0f - m_movePos.x) * LAND_REV;
			m_movePos.z += (0.0f - m_movePos.z) * LAND_REV;
		}
	}

	SetVec3Position(rPos);

	// 着地状況を返す
	return bLand;
}
