//============================================================
//
//	地盤処理 [ground.cpp]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	インクルードファイル
//************************************************************
#include "ground.h"
#include "map.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"
#include "enemy.h"

//************************************************************
//	マクロ定義
//************************************************************
#define GROUND_PRIO	(1)	// 地盤の優先順位

//************************************************************
//	子クラス [CMap] のメンバ関数
//************************************************************
//============================================================
//	コンストラクタ
//============================================================
CMap::CMap()
{
	// メンバ変数をクリア
	for (int nCntW = 0; nCntW < BLOCK_WIGHT; nCntW++)
	{
		for (int nCntH = 0; nCntH < BLOCK_HEIGHT; nCntH++)
		{
			m_bUseBlock[nCntW][nCntH] = false;
		}
	}
	nCntTime = 0;
	nSpwnEnemy = 4;
}

//============================================================
//	デストラクタ
//============================================================
CMap::~CMap()
{

}

//============================================================
//	初期化処理
//============================================================
HRESULT CMap::Init(void)
{
	// 成功を返す
	return S_OK;
}

//============================================================
//	終了処理
//============================================================
void CMap::Uninit(void)
{
	delete this;
}

//============================================================
//	更新処理
//============================================================
void CMap::Update(void)
{
	if (nCntTime % 300 == 0)
	{
		int nCntEnemy = 0;
		for (int nCntW = 0; nCntW < BLOCK_WIGHT; nCntW++)
		{
			for (int nCntH = 0; nCntH < BLOCK_HEIGHT; nCntH++)
			{
				if (nCntEnemy < nSpwnEnemy)
				{
					int Rand = rand() % 100;
					if (Rand >= 98)
					{
						nCntEnemy++;
						CEnemy::Create(CEnemy::TYPE_NORMAL, D3DXVECTOR3(-1000.0f + nCntW * 110.0f, 0.0f, -1000.0f + nCntH * 110.0f), VEC3_ZERO);
					}
				}
			}
		}
	}

	nCntTime++;
}

//============================================================
//	描画処理
//============================================================
void CMap::Draw(void)
{

}

//============================================================
//	生成処理
//============================================================
CMap* CMap::Create
(
	const D3DXVECTOR3& rPos,		// 位置
	const D3DXVECTOR3& rRot,		// 向き
	const D3DXVECTOR3& rSize,		// 大きさ
	const D3DXVECTOR2& rTexPartX,	// テクスチャ分割数X
	const D3DXVECTOR2& rTexPartY,	// テクスチャ分割数Y
	const D3DXVECTOR2& rTexPartZ	// テクスチャ分割数Z
)
{
	// ポインタを宣言
	CMap* pMap = NULL;	// 地盤生成用

	if (pMap == NULL)
	{ // 使用されていない場合

		// メモリ確保
		pMap = new CMap;	// 地盤
	}
	else { assert(false); return NULL; }	// 使用中

	if (pMap != NULL)
	{ // 確保に成功している場合

		// 地盤の初期化
		if (FAILED(pMap->Init()))
		{ // 初期化に失敗した場合

			// メモリ開放
			delete pMap;
			pMap = NULL;

			// 失敗を返す
			return NULL;
		}

		//ブロックの設置
		pMap->SetGround(rPos, rRot, rSize, rTexPartX, rTexPartY, rTexPartZ);

		// 確保したアドレスを返す
		return pMap;
	}
	else { assert(false); return NULL; }	// 確保失敗
}

//============================================================
//	生成処理
//============================================================
void CMap::SetGround
(
	const D3DXVECTOR3& rPos,		// 位置
	const D3DXVECTOR3& rRot,		// 向き
	const D3DXVECTOR3& rSize,		// 大きさ
	const D3DXVECTOR2& rTexPartX,	// テクスチャ分割数X
	const D3DXVECTOR2& rTexPartY,	// テクスチャ分割数Y
	const D3DXVECTOR2& rTexPartZ	// テクスチャ分割数Z
)
{
	for (int nCntW = 0; nCntW < BLOCK_WIGHT; nCntW++)
	{
		for (int nCntH = 0; nCntH < BLOCK_HEIGHT; nCntH++)
		{
			CGround *pGround = CGround::Create(D3DXVECTOR3(-1000.0f + nCntW * 110.0f, rPos.y, -1000.0f + nCntH * 110.0f), rRot, rSize, rTexPartX, rTexPartY, rTexPartZ);
			pGround->SetWNumber(nCntW);
			pGround->SetHNumber(nCntH);
			m_bUseBlock[nCntW][nCntH] = true;
		}
	}
}