//============================================================
//
//	プレイヤー処理 [player.cpp]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	インクルードファイル
//************************************************************
#include "player.h"
#include "manager.h"
#include "sceneGame.h"
#include "gameManager.h"
#include "renderer.h"
#include "sound.h"
#include "camera.h"
#include "texture.h"
#include "collision.h"
#include "fade.h"
#include "stage.h"
#include "bullet.h"
#include "enemy.h"
#include "stick.h"
#include "ground.h"
#include "EffectModel.h"

//************************************************************
//	定数宣言
//************************************************************
namespace
{
	const int PRIORITY = 3;	// プレイヤーの優先順位

	const float	MOVE		= 2.8f;		// 移動量
	const float	JUMP		= 21.0f;	// ジャンプ上昇量
	const float	GRAVITY		= 1.0f;		// 重力
	const float	RADIUS		= 20.0f;	// 半径
	const float	HEIGHT		= 100.0f;	// 縦幅
	const float	REV_ROTA	= 0.15f;	// 向き変更の補正係数
	const float	ADD_MOVE	= 0.08f;	// 非アクション時の速度加算量
	const float	JUMP_REV	= 0.16f;	// 空中の移動量の減衰係数
	const float	LAND_REV	= 0.16f;	// 地上の移動量の減衰係数
	const float	KNOCK_REV	= 0.08f;	// 吹っ飛び状態時の移動量の減衰係数
	const float	KNOCK_UP	= 15.0f;	// ノック上昇量
	const float	KNOCK_SIDE	= 35.0f;	// ノック横移動量
	const float	SPAWN_ADD_ALPHA	= 0.03f;	// スポーン状態時の透明度の加算量
	const float	DEATH_SUB_ALPHA	= 0.05f;	// 死亡時の透明度の減算量
}

//************************************************************
//	静的メンバ変数宣言
//************************************************************
const char *CPlayer::mc_apModelFile[] =	// モデル定数
{
	"data\\MODEL\\PLAYER\\1225_pl_003.x",	// プレイヤー
};

//************************************************************
//	子クラス [CPlayer] のメンバ関数
//************************************************************
//============================================================
//	コンストラクタ
//============================================================
CPlayer::CPlayer() : CObjectModel(CObject::LABEL_PLAYER, PRIORITY)
{
	// メンバ変数をクリア
	m_oldPos		= VEC3_ZERO;	// 過去位置
	m_move			= VEC3_ZERO;	// 移動量
	m_destRot		= VEC3_ZERO;	// 目標向き
	m_RSrickRot		= 0.0f;
	m_state			= STATE_NONE;	// 状態
	m_nCounterState	= 0;			// 状態管理カウンター
	m_bJump			= false;		// ジャンプ状況
	m_bAttack = false;
	m_pAtkUI = nullptr;
	m_pShadow = nullptr;
}

//============================================================
//	デストラクタ
//============================================================
CPlayer::~CPlayer()
{

}

//============================================================
//	初期化処理
//============================================================
HRESULT CPlayer::Init(void)
{
	// メンバ変数を初期化
	m_oldPos		= VEC3_ZERO;	// 過去位置
	m_move			= VEC3_ZERO;	// 移動量
	m_destRot		= VEC3_ZERO;	// 目標向き
	m_state			= STATE_NONE;	// 状態
	m_nCounterState	= 0;			// 状態管理カウンター
	m_bJump			= true;			// ジャンプ状況

	// オブジェクトモデルの初期化
	if (FAILED(CObjectModel::Init()))
	{ // 初期化に失敗した場合

		// 失敗を返す
		assert(false);
		return E_FAIL;
	}

	// モデルを読込・割当
	BindModel(mc_apModelFile[MODEL_PLAYER]);

	if (m_pAtkUI == nullptr)
	{
		m_pAtkUI = CObjectModel::Create(VEC3_ZERO, VEC3_ZERO);
		m_pAtkUI->CObjectModel::SetLabel(LABEL_UI);
		m_pAtkUI->BindModel("data\\MODEL\\PLAYER\\sankakumodel.x");
	}

	if (m_pShadow == nullptr)
	{
		m_pShadow = CObjectModel::Create(VEC3_ZERO, VEC3_ZERO);
		m_pShadow->CObjectModel::SetLabel(LABEL_UI);
		m_pShadow->BindModel("data\\MODEL\\PLAYER\\player_shadow.x");
	}

	// 成功を返す
	return S_OK;
}

//============================================================
//	終了処理
//============================================================
void CPlayer::Uninit(void)
{
	// オブジェクトモデルの終了
	CObjectModel::Uninit();

	if (m_pAtkUI != nullptr)
	{
		m_pAtkUI->Uninit();
		m_pAtkUI = nullptr;
	}
}

//============================================================
//	更新処理
//============================================================
void CPlayer::Update(void)
{
	// 過去位置の更新
	UpdateOldPosition();

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

	switch (m_state)
	{ // 状態ごとの処理
	case STATE_NONE:
		break;

	case STATE_SPAWN:

		// スポーン状態時の更新
		UpdateSpawn();

		break;

	case STATE_NORMAL:

		// 通常状態の更新
		UpdateNormal();

		break;

	case STATE_KNOCK:

		// 吹っ飛び状態時の更新
		UpdateKnock();

		break;

	case STATE_DEATH:

		// 死亡状態時の更新
		UpdateDeath();

		break;

	default:
		assert(false);
		break;
	}

	// オブジェクトモデルの更新
	CObjectModel::Update();
}

//============================================================
//	描画処理
//============================================================
void CPlayer::Draw(void)
{
	// オブジェクトモデルの描画
	CObjectModel::Draw();
}

//============================================================
//	ノックバックヒット処理
//============================================================
void CPlayer::HitKnockBack(const int nDmg, const D3DXVECTOR3 &vecKnock)
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
	m_move.x = KNOCK_SIDE * vecKnock.x;
	m_move.y = KNOCK_UP;
	m_move.z = KNOCK_SIDE * vecKnock.z;

	// ノックバック方向に向きを設定
	rotPlayer.y = atan2f(vecKnock.x, vecKnock.z);	// 吹っ飛び向きを計算
	m_destRot.y = rotPlayer.y;	// 目標向きを設定
	SetVec3Rotation(rotPlayer);	// 向きを設定

	// 空中状態にする
	m_bJump = true;

	// ノック状態を設定
	SetState(STATE_KNOCK);

	if (m_pShadow != nullptr)
	{
		m_pShadow->SetEnableDraw(false);
	}
	if (m_pAtkUI != nullptr)
	{
		m_pAtkUI->SetEnableDraw(false);
	}


	// サウンドの再生
	CManager::GetInstance()->GetSound()->Play(CSound::LABEL_SE_HIT);	// ヒット音
}

//============================================================
//	状態の設定処理
//============================================================
void CPlayer::SetState(const int nState)
{
	if (nState > NONE_IDX && nState < STATE_MAX)
	{ // 範囲内の場合

		// 引数の状態を設定
		m_state = (EState)nState;
	}
	else { assert(false); }
}

//============================================================
//	状態取得処理
//============================================================
int CPlayer::GetState(void) const
{
	// 状態を返す
	return m_state;
}

//============================================================
//	半径取得処理
//============================================================
float CPlayer::GetRadius(void) const
{
	// 半径を返す
	return RADIUS;
}

//============================================================
//	縦幅取得処理
//============================================================
float CPlayer::GetHeight(void) const
{
	// 縦幅を返す
	return HEIGHT;
}

//============================================================
//	更新状況の設定処理
//============================================================
void CPlayer::SetEnableUpdate(const bool bUpdate)
{
	// 引数の更新状況を設定
	CObject::SetEnableUpdate(bUpdate);	// 自身
}

//============================================================
//	描画状況の設定処理
//============================================================
void CPlayer::SetEnableDraw(const bool bDraw)
{
	// 引数の描画状況を設定
	CObject::SetEnableDraw(bDraw);	// 自身
}

//============================================================
//	マトリックス取得処理
//============================================================
D3DXMATRIX CPlayer::GetMtxWorld(void) const
{
	// 変数を宣言
	D3DXMATRIX  mtxRot, mtxTrans, mtxWorld;		// 計算用マトリックス
	D3DXVECTOR3 posPlayer = GetVec3Position();	// プレイヤー位置
	D3DXVECTOR3 rotPlayer = GetVec3Rotation();	// プレイヤー向き

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&mtxWorld);

	// 向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, rotPlayer.y, rotPlayer.x, rotPlayer.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);

	// 位置を反映
	D3DXMatrixTranslation(&mtxTrans, posPlayer.x, posPlayer.y, posPlayer.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTrans);

	// ワールドマトリックスを返す
	return mtxWorld;
}

//============================================================
//	生成処理
//============================================================
CPlayer *CPlayer::Create(void)
{
	// ポインタを宣言
	CPlayer *pPlayer = nullptr;	// プレイヤー生成用

	if (pPlayer == nullptr)
	{ // 使用されていない場合

		// メモリ確保
		pPlayer = new CPlayer;	// プレイヤー
	}
	else { assert(false); return nullptr; }	// 使用中

	if (pPlayer != nullptr)
	{ // 使用されている場合

		// プレイヤーの初期化
		if (FAILED(pPlayer->Init()))
		{ // 初期化に失敗した場合

			// メモリ開放
			delete pPlayer;
			pPlayer = nullptr;

			// 失敗を返す
			return nullptr;
		}
	}

	// 確保したアドレスを返す
	return pPlayer;
}

//============================================================
//	出現の設定処理
//============================================================
void CPlayer::SetSpawn(void)
{
	// 変数を宣言
	D3DXVECTOR3 set = VEC3_ZERO;	// 引数設定用

	// 情報を初期化
	SetState(STATE_SPAWN);	// スポーン状態の設定

	// カウンターを初期化
	m_nCounterState = 0;	// 状態管理カウンター

	// 位置を設定
	SetVec3Position(set);

	// 向きを設定
	SetVec3Rotation(set);
	m_destRot = set;

	// 移動量を初期化
	m_move = VEC3_ZERO;

	// マテリアルを再設定
	ResetMaterial();

	// 透明度を透明に再設定
	SetAlpha(0.0f);

	// プレイヤーの描画を再開
	SetEnableDraw(true);

	//// 追従カメラの目標位置の設定
	//GET_MANAGER->GetCamera()->SetDestFollow();

	// サウンドの再生
	GET_MANAGER->GetSound()->Play(CSound::LABEL_SE_SPAWN);	// 生成音
}

//============================================================
//	スポーン状態時の更新処理
//============================================================
void CPlayer::UpdateSpawn(void)
{
	// フェードアウト状態時の更新
	if (UpdateFadeOut(SPAWN_ADD_ALPHA))
	{ // 不透明になり切った場合

		// 状態を設定
		SetState(STATE_NORMAL);
	}
}

//============================================================
//	通常状態時の更新処理
//============================================================
void CPlayer::UpdateNormal(void)
{
	// 変数を宣言
	D3DXVECTOR3 posPlayer = GetVec3Position();	// プレイヤー位置
	D3DXVECTOR3 rotPlayer = GetVec3Rotation();	// プレイヤー向き

	// ポインタを宣言
	CStage *pStage = CScene::GetStage();	// ステージ情報
	if (pStage == nullptr)
	{ // ステージが使用されていない場合

		// 処理を抜ける
		assert(false);
		return;
	}


	// マテリアル再設定
	ResetMaterial();

	// 変数を宣言
	D3DXVECTOR3 vecStickR = D3DXVECTOR3((float)GET_INPUTPAD->GetPressRStickX(), (float)GET_INPUTPAD->GetPressRStickY(), 0.0f);	// スティック各軸の倒し量
	float fStickR = sqrtf(vecStickR.x * vecStickR.x + vecStickR.y * vecStickR.y) * 0.5f;	// スティックの倒し量
	if (0.8f < fStickR)
	{ // デッドゾーン以上の場合

		m_RSrickRot = GET_INPUTPAD->GetPressRStickRot();

	}

	// 移動操作
	UpdateMove();

	// ジャンプの更新
	UpdateJump();

	// 攻撃の更新
	UpdateAttack();

	// 射撃の更新
	UpdateBullet();

	// 重力の更新
	UpdateGravity();

	// 着地判定
	UpdateLanding(posPlayer);

	// 敵との当たり判定
	CollisionEnemy(posPlayer);

	// 向き更新
	UpdateRotation(rotPlayer);

	// ステージ範囲外の補正
	pStage->LimitPosition(posPlayer, RADIUS);

	// キルYとの判定
	if (pStage->CollisionKillY(posPlayer))
	{ // キルYより下の位置にいる場合

		// 死亡状態にする
		m_state = STATE_DEATH;

		// サウンドの再生
		GET_MANAGER->GetSound()->Play(CSound::LABEL_SE_FALL);	// 生成音
	}

	if (m_bAttack == false)
	{
		if (m_pAtkUI != nullptr)
		{
			m_pAtkUI->SetVec3Position(GetVec3Position());
			m_pAtkUI->SetVec3Rotation(D3DXVECTOR3(0.0f, m_RSrickRot + D3DX_PI * 0.5f, 0.0f));
		}
	}

	if (m_pShadow != nullptr)
	{
		m_pShadow->SetVec3Position(D3DXVECTOR3(GetVec3Position().x, 0.0f, GetVec3Position().z));
	}

	if (posPlayer.y < 0.0f)
	{
		if (m_pShadow != nullptr)
		{
			m_pShadow->SetEnableDraw(false);
		}
		if (m_pAtkUI != nullptr)
		{
			m_pAtkUI->SetEnableDraw(false);
		}
	}

	// 位置を反映
	SetVec3Position(posPlayer);

	// 向きを反映
	SetVec3Rotation(rotPlayer);
}

//============================================================
//	吹っ飛び状態時の更新処理
//============================================================
void CPlayer::UpdateKnock(void)
{
	// 変数を宣言
	D3DXVECTOR3 posPlayer = GetVec3Position();	// プレイヤー位置
	D3DXVECTOR3 rotPlayer = GetVec3Rotation();	// プレイヤー向き

	// ポインタを宣言
	CStage *pStage = CScene::GetStage();	// ステージ情報
	assert(pStage != nullptr);

	// マテリアルを全設定
	SetAllMaterial(material::Red());	// 赤

	// 重力の更新
	UpdateGravity();

	// 着地判定
	if (UpdateLanding(posPlayer))
	{ // 着地した場合

		// 通常状態にする
		m_state = STATE_NORMAL;
	}

	// 向き更新
	UpdateRotation(rotPlayer);

	// ステージ範囲外の補正
	pStage->LimitPosition(posPlayer, RADIUS);

	// キルYとの判定
	if (pStage->CollisionKillY(posPlayer))
	{ // キルYより下の位置にいる場合

		// 死亡状態にする
		m_state = STATE_DEATH;

		// マテリアル再設定
		ResetMaterial();

		// サウンドの再生
		GET_MANAGER->GetSound()->Play(CSound::LABEL_SE_FALL);	// 生成音
	}

	// 位置を反映
	SetVec3Position(posPlayer);

	// 向きを反映
	SetVec3Rotation(rotPlayer);
}

//============================================================
//	死亡状態時の更新処理
//============================================================
void CPlayer::UpdateDeath(void)
{
	// 変数を宣言
	D3DXVECTOR3 posPlayer = GetVec3Position();	// 敵位置

	// 過去位置の更新
	UpdateOldPosition();

	// 重力を与える
	m_move.y -= GRAVITY;

	// 着地状況の更新
	UpdateLanding(posPlayer);

	// 位置を反映
	SetVec3Position(posPlayer);

	// フェードインの更新
	UpdateFadeIn(DEATH_SUB_ALPHA);
}

//============================================================
//	過去位置の更新処理
//============================================================
void CPlayer::UpdateOldPosition(void)
{
	// 過去位置を更新
	m_oldPos = GetVec3Position();
}

//============================================================
//	移動量・目標向きの更新処理
//============================================================
void CPlayer::UpdateMove(void)
{
	CCamera* pCamera = GET_MANAGER->GetCamera();


	// 変数を宣言
	D3DXVECTOR3 vecStickL = D3DXVECTOR3((float)GET_INPUTPAD->GetPressLStickX(), (float)GET_INPUTPAD->GetPressLStickY(), 0.0f);	// スティック各軸の倒し量
	float fStickL = sqrtf(vecStickL.x * vecStickL.x + vecStickL.y * vecStickL.y) * 0.5f;	// スティックの倒し量
	if (0.01f < fStickL)
	{ // デッドゾーン以上の場合

		// 移動量を更新
		m_move.x += sinf(pCamera->GetVec3Rotation().y + GET_INPUTPAD->GetPressLStickRot() + D3DX_PI * 0.5f) * MOVE;
		m_move.z += cosf(pCamera->GetVec3Rotation().y + GET_INPUTPAD->GetPressLStickRot() + D3DX_PI * 0.5f) * MOVE;
	}

	// 目標向きを設定
	m_destRot.y = atan2f(-m_move.x, -m_move.z);
}

//============================================================
//	ジャンプの更新処理
//============================================================
void CPlayer::UpdateJump(void)
{
	if (!m_bJump)
	{ // ジャンプしていない場合

		if (GET_INPUTKEY->IsTrigger(DIK_SPACE) ||
			GET_INPUTPAD->IsTrigger(GET_INPUTPAD->KEY_A))
		{ // ジャンプ操作が行われた場合

			// ジャンプフラグをONにする
			m_bJump = true;

			// 上移動量を加算
			m_move.y += JUMP;

			// サウンドの再生
			GET_MANAGER->GetSound()->Play(CSound::LABEL_SE_FLY);	// 生成音
		}
	}
}

//============================================================
//	の更新処理
//============================================================
void CPlayer::UpdateAttack(void)
{
	// 変数を宣言
	D3DXVECTOR3 vecStickR = D3DXVECTOR3((float)GET_INPUTPAD->GetPressRStickX(), (float)GET_INPUTPAD->GetPressRStickY(), 0.0f);	// スティック各軸の倒し量
	float fStickR = sqrtf(vecStickR.x * vecStickR.x + vecStickR.y * vecStickR.y) * 0.5f;	// スティックの倒し量
	if (0.8f < fStickR)
	{ // デッドゾーン以上の場合

		m_RSrickRot = GET_INPUTPAD->GetPressRStickRot();

	}

	if (m_bAttack == false)
	{
		if (GET_INPUTKEY->IsTrigger(DIK_Y) ||
			GET_INPUTPAD->IsTrigger(GET_INPUTPAD->KEY_L1))
		{ // 操作が行われた場合
			CStick* pStick = CStick::Create();
			pStick->SetVec3Rotation(D3DXVECTOR3(0.0f, m_RSrickRot, 0.0f));
			pStick->SetVec3Position(GetVec3Position());
			m_bAttack = true;

			// サウンドの再生
			GET_MANAGER->GetSound()->Play(CSound::LABEL_SE_SLASH);	// 生成音
		}

		if (m_pShadow != nullptr)
		{
			m_pShadow->SetEnableDraw(true);
		}

		if (m_pAtkUI != nullptr)
		{
			m_pAtkUI->SetEnableDraw(true);
			m_pAtkUI->SetVec3Position(GetVec3Position());
			m_pAtkUI->SetVec3Rotation(D3DXVECTOR3(0.0f, m_RSrickRot + D3DX_PI * 0.5f, 0.0f));
		}
	}
	else
	{
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

					if (pObjCheck->GetLabel() == CObject::LABEL_ENEMY)
					{ // オブジェクトラベルが地盤ではない場合

						D3DXVECTOR3 posEnemy = pObjCheck->GetVec3Position();	// 敵位置

						if (collision::Sector(GetVec3Position(), posEnemy, m_RSrickRot + D3DX_PI * -0.5f, 200.0f, D3DX_PI) == true)
						{
							D3DXVECTOR3 vecKnock = posEnemy - GetVec3Position();	// ノックバックベクトル
							D3DXVec3Normalize(&vecKnock, &vecKnock);	// 正規化

							// プレイヤーのヒット処理
							pObjCheck->HitKnockBack(0, vecKnock);

							// 変数を宣言
							D3DXVECTOR3 vec = VEC3_ZERO;	// ベクトルの設定用
							D3DXVECTOR3 pos = VEC3_ZERO;	// 位置の代入用
							D3DXVECTOR3 move = VEC3_ZERO;	// 移動量の代入用
							D3DXVECTOR3 rot = VEC3_ZERO;	// 向きの代入用

							for (int nCntPart = 0; nCntPart < 15; nCntPart++)
							{ // 生成されるエフェクト数分繰り返す

								// ベクトルをランダムに設定
								vec.x = sinf((float)(rand() % 629 - 314) / 100.0f) * 1.0f;
								vec.y = cosf((float)(rand() % 629 - 314) / 100.0f) * 1.0f;
								vec.z = cosf((float)(rand() % 629 - 314) / 100.0f) * 1.0f;

								// ベクトルを正規化
								D3DXVec3Normalize(&vec, &vec);

								// 移動量を設定
								move = vec * 10.0f;

								CEffectModel* pModel = CEffectModel::Create(true);
								pModel->SetVec3Position(posEnemy);
								pModel->SetMove(move);
								pModel->SetVec3Scaling(D3DXVECTOR3(0.4f, 0.4f, 0.4f));
							}
						}
					}

					// 次のオブジェクトへのポインタを代入
					pObjCheck = pObjectNext;
				}
			}
		}
		if (m_pAtkUI != nullptr)
		{
			m_pAtkUI->SetEnableDraw(false);
		}
	}
}

//============================================================
//	の更新処理
//============================================================
void CPlayer::UpdateBullet(void)
{
	if (GET_INPUTKEY->IsTrigger(DIK_B) ||
		GET_INPUTPAD->IsTrigger(GET_INPUTPAD->KEY_R1))
	{ // 操作が行われた場合

		CBullet* pBullet = CBullet::Create(true);
		pBullet->SetVec3Position(GetVec3Position());
		pBullet->SetMove(D3DXVECTOR3(
			-cosf(m_RSrickRot) * 25.0f,
			0.0f,
			sinf(m_RSrickRot) * 25.0f
		));

		// サウンドの再生
		GET_MANAGER->GetSound()->Play(CSound::LABEL_SE_SHOT);	// 生成音
	}
}

//============================================================
//	重力の更新処理
//============================================================
void CPlayer::UpdateGravity(void)
{
	// 重力を加算
	m_move.y -= GRAVITY;
}

//============================================================
//	着地状況の更新処理
//============================================================
bool CPlayer::UpdateLanding(D3DXVECTOR3& rPos)
{
	// 変数を宣言
	bool bLand = false;	// 着地状況

	// ジャンプしている状態にする
	m_bJump = true;

	// 位置の更新
	// 地盤の当たり判定・着地判定
	if (CollisionGround(rPos))
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
//	向きの更新処理
//============================================================
void CPlayer::UpdateRotation(D3DXVECTOR3& rRot)
{
	// 変数を宣言
	float fDiffRot = 0.0f;	// 差分向き

	// 目標向きの正規化
	useful::NormalizeRot(m_destRot.y);

	// 目標向きまでの差分を計算
	fDiffRot = m_destRot.y - rRot.y;

	// 差分向きの正規化
	useful::NormalizeRot(fDiffRot);

	// 向きの更新
	rRot.y += fDiffRot * REV_ROTA;

	// 向きの正規化
	useful::NormalizeRot(rRot.y);
}

//============================================================
//	フェードアウト状態時の更新処理
//============================================================
bool CPlayer::UpdateFadeOut(const float fAdd)
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
bool CPlayer::UpdateFadeIn(const float fSub)
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
bool CPlayer::ResponseSingleGround(const EAxis axis, D3DXVECTOR3& rPos)
{
	// 変数を宣言
	D3DXVECTOR3 sizeMinPlayer = D3DXVECTOR3(RADIUS, 0.0f, RADIUS);		// プレイヤー最小大きさ
	D3DXVECTOR3 sizeMaxPlayer = D3DXVECTOR3(RADIUS, HEIGHT, RADIUS);	// プレイヤー最大大きさ
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
						&m_move			// 移動量
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
						&m_move,		// 移動量
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
						&m_move			// 移動量
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
bool CPlayer::CollisionGround(D3DXVECTOR3& rPos)
{
	// 変数を宣言
	bool bLand = false;	// 着地状況

	// 移動量を加算
	rPos.x += m_move.x;

	// X軸の当たり判定
	ResponseSingleGround(AXIS_X, rPos);

	// 移動量を加算
	rPos.y += m_move.y;

	// Y軸の当たり判定
	bLand = ResponseSingleGround(AXIS_Y, rPos);

	// 移動量を加算
	rPos.z += m_move.z;

	// Z軸の当たり判定
	ResponseSingleGround(AXIS_Z, rPos);

	if (m_state == STATE_KNOCK)
	{ // ノック状態の場合

		m_move.x += (0.0f - m_move.x) * KNOCK_REV;
		m_move.z += (0.0f - m_move.z) * KNOCK_REV;
	}
	else
	{ // それ以外の状態の場合

		// 移動量を減衰
		if (m_bJump)
		{ // 空中の場合

			m_move.x += (0.0f - m_move.x) * JUMP_REV;
			m_move.z += (0.0f - m_move.z) * JUMP_REV;
		}
		else
		{ // 地上の場合

			m_move.x += (0.0f - m_move.x) * LAND_REV;
			m_move.z += (0.0f - m_move.z) * LAND_REV;
		}
	}

	// 着地状況を返す
	return bLand;
}

//============================================================
//	敵との当たり判定
//============================================================
void CPlayer::CollisionEnemy(D3DXVECTOR3 &rPos)
{
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
				D3DXVECTOR3 posEnemy = VEC3_ZERO;	// 敵位置

				// ポインタを宣言
				CObject *pObjectNext = pObjCheck->GetNext();	// 次オブジェクト

				if (pObjCheck->GetLabel() != CObject::LABEL_ENEMY)
				{ // オブジェクトラベルが地盤ではない場合

					// 次のオブジェクトへのポインタを代入
					pObjCheck = pObjectNext;

					// 次の繰り返しに移行
					continue;
				}

				if (pObjCheck->GetState() != CEnemy::STATE_NORMAL)
				{ // 状態が通常ではない場合

					// 次のオブジェクトへのポインタを代入
					pObjCheck = pObjectNext;

					// 次の繰り返しに移行
					continue;
				}

				// 地盤の位置を設定
				posEnemy = pObjCheck->GetVec3Position();

				// 円柱の衝突判定
				bool bHit = collision::CirclePillar
				( // 引数
					rPos,					// 判定位置
					posEnemy,				// 判定目標位置
					RADIUS,					// 判定半径
					pObjCheck->GetRadius()	// 判定目標半径
				);
				if (bHit)
				{ // 当たっていた場合

					D3DXVECTOR3 vecKnock = rPos - posEnemy;		// ノックバックベクトル
					D3DXVec3Normalize(&vecKnock, &vecKnock);	// 正規化

											// 変数を宣言
					D3DXVECTOR3 vec = VEC3_ZERO;	// ベクトルの設定用
					D3DXVECTOR3 pos = VEC3_ZERO;	// 位置の代入用
					D3DXVECTOR3 move = VEC3_ZERO;	// 移動量の代入用
					D3DXVECTOR3 rot = VEC3_ZERO;	// 向きの代入用

					for (int nCntPart = 0; nCntPart < 15; nCntPart++)
					{ // 生成されるエフェクト数分繰り返す

						// ベクトルをランダムに設定
						vec.x = sinf((float)(rand() % 629 - 314) / 100.0f) * 1.0f;
						vec.y = cosf((float)(rand() % 629 - 314) / 100.0f) * 1.0f;
						vec.z = cosf((float)(rand() % 629 - 314) / 100.0f) * 1.0f;

						// ベクトルを正規化
						D3DXVec3Normalize(&vec, &vec);

						// 移動量を設定
						move = vec * 10.0f;

						CEffectModel* pModel = CEffectModel::Create(false);
						pModel->SetVec3Position(GetVec3Position());
						pModel->SetMove(move);
						pModel->SetVec3Scaling(D3DXVECTOR3(0.4f, 0.4f, 0.4f));
					}

					// プレイヤーのヒット処理
					HitKnockBack(0, vecKnock);

					// 関数を抜ける
					return;
				}

				// 次のオブジェクトへのポインタを代入
				pObjCheck = pObjectNext;
			}
		}
	}
}
