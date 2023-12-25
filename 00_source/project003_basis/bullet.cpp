//============================================
//
//	たま [MapCannon.cpp]
//	Author:sakamoto kai
//
//============================================
#include "bullet.h"
#include "manager.h"
#include "gamemanager.h"
#include "collision.h"
#include "player.h"
#include "effectmodel.h"

//マクロ定義
#define BLOCK_WIGHT (300.0f)		//横幅
#define BLOCK_HEIGHT (300.0f)		//縦幅
#define WALL_UPEND (20.0f)			//上昇位置

//====================================================================
//コンストラクタ
//====================================================================
CBullet::CBullet() : CObjectModel(CObject::LABEL_PLAYER, 3)
{
	m_nLife = 120;
	m_PlayerBullet = false;
}

//====================================================================
//デストラクタ
//====================================================================
CBullet::~CBullet()
{

}

//====================================================================
//生成処理
//====================================================================
CBullet* CBullet::Create(bool PlayerBullet)
{
	// ポインタを宣言
	CBullet* pBullet = nullptr;	// プレイヤー生成用

	if (pBullet == nullptr)
	{ // 使用されていない場合

		// メモリ確保
		pBullet = new CBullet;	// プレイヤー
	}
	else { assert(false); return nullptr; }	// 使用中

	if (pBullet != nullptr)
	{ // 使用されている場合

		// プレイヤーの初期化
		if (FAILED(pBullet->Init(PlayerBullet)))
		{ // 初期化に失敗した場合

			// メモリ開放
			delete pBullet;
			pBullet = nullptr;

			// 失敗を返す
			return nullptr;
		}
	}

	// 確保したアドレスを返す
	return pBullet;
}

//====================================================================
//初期化処理
//====================================================================
HRESULT CBullet::Init(bool PlayerBullet)
{
	// オブジェクトモデルの初期化
	if (FAILED(CObjectModel::Init()))
	{ // 初期化に失敗した場合

		// 失敗を返す
		assert(false);
		return E_FAIL;
	}

	m_PlayerBullet = PlayerBullet;

	if (m_PlayerBullet == true)
	{
		// モデルを読込・割当
		BindModel("data\\MODEL\\BULLET\\plryer_bullrt.x");
	}
	else
	{
		// モデルを読込・割当
		BindModel("data\\MODEL\\BULLET\\enemy_bullrt.x");
	}
	// 成功を返す
	return S_OK;
}

//====================================================================
//終了処理
//====================================================================
void CBullet::Uninit(void)
{
	CObjectModel::Uninit();
}

//====================================================================
//更新処理
//====================================================================
void CBullet::Update(void)
{
	D3DXVECTOR3 pos = GetVec3Position();

	pos += m_move;

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

				if (pObjCheck->GetLabel() == CObject::LABEL_ENEMY && m_PlayerBullet == true)
				{ // オブジェクトラベルが地盤ではない場合

					D3DXVECTOR3 posEnemy = pObjCheck->GetVec3Position();	// 敵位置

					if (collision::Circle3D(GetVec3Position(), posEnemy, 30.0f,50.0f) == true)
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

						// 自身の玉の終了
						Uninit();
						return;
					}
				}
				// 次のオブジェクトへのポインタを代入
				pObjCheck = pObjectNext;
			}
		}
	}

	if (m_PlayerBullet == false)
	{ // オブジェクトラベルが地盤ではない場合

		CPlayer* pPlayer = CScene::GetPlayer();

		if (collision::Circle3D(GetVec3Position(), pPlayer->GetVec3Position(), 30.0f, 50.0f) == true)
		{
			D3DXVECTOR3 vecKnock = pPlayer->GetVec3Position() - GetVec3Position();	// ノックバックベクトル
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
				pModel->SetVec3Position(pPlayer->GetVec3Position());
				pModel->SetMove(move);
				pModel->SetVec3Scaling(D3DXVECTOR3(0.4f, 0.4f, 0.4f));
			}

			// プレイヤーのヒット処理
			pPlayer->HitKnockBack(0, vecKnock);

			// 自身の玉の終了
			Uninit();
			return;
		}
	}

	SetVec3Position(pos);

	if (m_nLife > 0)
	{
		m_nLife--;
	}
	else
	{
		Uninit();
		return;
	}

	//頂点情報の更新
	CObjectModel::Update();
}

//====================================================================
//描画処理
//====================================================================
void CBullet::Draw(void)
{
	CObjectModel::Draw();
}