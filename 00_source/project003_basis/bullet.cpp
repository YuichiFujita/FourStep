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
CBullet* CBullet::Create()
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
		if (FAILED(pBullet->Init()))
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
HRESULT CBullet::Init(void)
{
	// オブジェクトモデルの初期化
	if (FAILED(CObjectModel::Init()))
	{ // 初期化に失敗した場合

		// 失敗を返す
		assert(false);
		return E_FAIL;
	}

	// モデルを読込・割当
	BindModel("data\\MODEL\\BULLET\\1225_pl_003.x");

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

				if (pObjCheck->GetLabel() == CObject::LABEL_ENEMY)
				{ // オブジェクトラベルが地盤ではない場合

					D3DXVECTOR3 posEnemy = pObjCheck->GetVec3Position();	// 敵位置

					if (collision::Circle3D(GetVec3Position(), posEnemy, 30.0f,30.0f) == true)
					{
						D3DXVECTOR3 vecKnock = posEnemy - GetVec3Position();	// ノックバックベクトル
						D3DXVec3Normalize(&vecKnock, &vecKnock);	// 正規化

						// プレイヤーのヒット処理
						pObjCheck->HitKnockBack(0, vecKnock);

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