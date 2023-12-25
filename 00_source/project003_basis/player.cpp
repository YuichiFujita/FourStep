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
	const float	KNOCK_REV	= 0.9f;		// 吹っ飛び状態時の移動量の減衰係数

	const float	SPAWN_ADD_ALPHA	= 0.03f;	// スポーン状態時の透明度の加算量
	const float	DEATH_SUB_ALPHA	= 0.05f;	// 死亡時の透明度の減算量
}

//************************************************************
//	静的メンバ変数宣言
//************************************************************
const char *CPlayer::mc_apModelFile[] =	// モデル定数
{
	"data\\MODEL\\PLAYER\\1225_pl_002.x",	// プレイヤー
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
	m_state			= STATE_NONE;	// 状態
	m_nCounterState	= 0;			// 状態管理カウンター
	m_bJump			= false;		// ジャンプ状況
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
}

//============================================================
//	更新処理
//============================================================
void CPlayer::Update(void)
{
	// 過去位置の更新
	UpdateOldPosition();

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
	// 変数を宣言
	D3DXVECTOR3 posPlayer = GetVec3Position();	// プレイヤー位置
	D3DXVECTOR3 rotPlayer = GetVec3Rotation();	// プレイヤー向き

#if 0

	if (IsDeath() != true)
	{ // 死亡フラグが立っていない場合

		if (m_state == STATE_NORMAL)
		{ // 通常状態の場合

			// カウンターを初期化
			m_nCounterState = 0;

			// 待機モーションを設定
			SetMotion(MOTION_IDOL);

			// 爆発パーティクルを生成
			CParticle3D::Create(CParticle3D::TYPE_SMALL_EXPLOSION, D3DXVECTOR3(posPlayer.x, posPlayer.y + basic::HEIGHT * 0.5f, posPlayer.z));

			// サウンドの再生
			GET_MANAGER->GetSound()->Play(CSound::LABEL_SE_HIT);	// ヒット音
		}
	}

#endif
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
	SetAlpha(1.0f);

	// プレイヤーの描画を再開
	SetEnableDraw(true);

	// 追従カメラの目標位置の設定
	GET_MANAGER->GetCamera()->SetDestFollow();

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

	// 移動操作
	UpdateMove();

	// ジャンプの更新
	UpdateJump();

	// 重力の更新
	UpdateGravity();

	// 着地判定
	UpdateLanding(posPlayer);

	// 向き更新
	UpdateRotation(rotPlayer);

	// ステージ範囲外の補正
	pStage->LimitPosition(posPlayer, RADIUS);

	// キルYとの判定
	if (pStage->CollisionKillY(posPlayer))
	{ // キルYより下の位置にいる場合

		// 死亡状態にする
		m_state = STATE_DEATH;
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

	//キーボードの移動処理
	if (GET_INPUTKEY->IsPress(DIK_W) == true)
	{
		if (GET_INPUTKEY->IsPress(DIK_A) == true)
		{
			// 移動量を更新
			m_move.x += sinf(pCamera->GetVec3Rotation().y + D3DX_PI * -0.25f) * 1.0f;
			m_move.z += cosf(pCamera->GetVec3Rotation().y + D3DX_PI * -0.25f) * 1.0f;
		}
		else if (GET_INPUTKEY->IsPress(DIK_D) == true)
		{
			// 移動量を更新
			m_move.x += sinf(pCamera->GetVec3Rotation().y + D3DX_PI * 0.25f) * 1.0f;
			m_move.z += cosf(pCamera->GetVec3Rotation().y + D3DX_PI * 0.25f) * 1.0f;
		}
		else
		{
			// 移動量を更新
			m_move.x += sinf(pCamera->GetVec3Rotation().y + D3DX_PI * 0.0f) * 1.0f;
			m_move.z += cosf(pCamera->GetVec3Rotation().y + D3DX_PI * 0.0f) * 1.0f;
		}
	}
	else if (GET_INPUTKEY->IsPress(DIK_S) == true)
	{
		if (GET_INPUTKEY->IsPress(DIK_A) == true)
		{
			// 移動量を更新
			m_move.x += sinf(pCamera->GetVec3Rotation().y + D3DX_PI * -0.75f) * 1.0f;
			m_move.z += cosf(pCamera->GetVec3Rotation().y + D3DX_PI * -0.75f) * 1.0f;
		}
		else if (GET_INPUTKEY->IsPress(DIK_D) == true)
		{
			// 移動量を更新
			m_move.x += sinf(pCamera->GetVec3Rotation().y + D3DX_PI * 0.75f) * 1.0f;
			m_move.z += cosf(pCamera->GetVec3Rotation().y + D3DX_PI * 0.75f) * 1.0f;
		}
		else
		{
			// 移動量を更新
			m_move.x += sinf(pCamera->GetVec3Rotation().y + D3DX_PI * 1.0f) * 1.0f;
			m_move.z += cosf(pCamera->GetVec3Rotation().y + D3DX_PI * 1.0f) * 1.0f;
		}
	}
	else if (GET_INPUTKEY->IsPress(DIK_A) == true)
	{
		// 移動量を更新
		m_move.x += sinf(pCamera->GetVec3Rotation().y + D3DX_PI * -0.5f) * 1.0f;
		m_move.z += cosf(pCamera->GetVec3Rotation().y + D3DX_PI * -0.5f) * 1.0f;

	}
	else if (GET_INPUTKEY->IsPress(DIK_D) == true)
	{
		// 移動量を更新
		m_move.x += sinf(pCamera->GetVec3Rotation().y + D3DX_PI * 0.5f) * 1.0f;
		m_move.z += cosf(pCamera->GetVec3Rotation().y + D3DX_PI * 0.5f) * 1.0f;
	}

	if (GET_INPUTKEY->IsPress(DIK_W) == false && GET_INPUTKEY->IsPress(DIK_A) == false && GET_INPUTKEY->IsPress(DIK_S) == false && GET_INPUTKEY->IsPress(DIK_D) == false)
	{
		// 変数を宣言
		D3DXVECTOR3 vecStickL = D3DXVECTOR3((float)GET_INPUTPAD->GetPressLStickX(), (float)GET_INPUTPAD->GetPressLStickY(), 0.0f);	// スティック各軸の倒し量
		float fStickL = sqrtf(vecStickL.x * vecStickL.x + vecStickL.y * vecStickL.y) * 0.5f;	// スティックの倒し量
		if (0.01f < fStickL)
		{ // デッドゾーン以上の場合

			// 移動量を更新
			m_move.x += sinf(GET_INPUTPAD->GetPressLStickRot()) * MOVE;
			m_move.z += cosf(GET_INPUTPAD->GetPressLStickRot()) * MOVE;
		}
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
		}
	}
}

//============================================================
//	の更新処理
//============================================================
void CPlayer::UpdateAttack(void)
{
	if (GET_INPUTKEY->IsTrigger(DIK_SPACE) ||
		GET_INPUTPAD->IsTrigger(GET_INPUTPAD->KEY_A))
	{ // 操作が行われた場合

	}
}

//============================================================
//	の更新処理
//============================================================
void CPlayer::UpdateBullet(void)
{
	if (GET_INPUTKEY->IsTrigger(DIK_SPACE) ||
		GET_INPUTPAD->IsTrigger(GET_INPUTPAD->KEY_A))
	{ // 操作が行われた場合

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
