//============================================
//
//	たま [MapCannon.cpp]
//	Author:sakamoto kai
//
//============================================
#include "EffectModel.h"
#include "manager.h"
#include "gamemanager.h"
#include "collision.h"
#include "player.h"

//マクロ定義
#define BLOCK_WIGHT (300.0f)		//横幅
#define BLOCK_HEIGHT (300.0f)		//縦幅
#define WALL_UPEND (20.0f)			//上昇位置

//====================================================================
//コンストラクタ
//====================================================================
CEffectModel::CEffectModel() : CObjectModel(CObject::LABEL_PLAYER, 3)
{
	m_nLife = 30;
	m_nLifeMax = m_nLife;
}

//====================================================================
//デストラクタ
//====================================================================
CEffectModel::~CEffectModel()
{

}

//====================================================================
//生成処理
//====================================================================
CEffectModel* CEffectModel::Create(bool playerE)
{
	// ポインタを宣言
	CEffectModel* pBullet = nullptr;	// プレイヤー生成用

	if (pBullet == nullptr)
	{ // 使用されていない場合

		// メモリ確保
		pBullet = new CEffectModel;	// プレイヤー
	}
	else { assert(false); return nullptr; }	// 使用中

	if (pBullet != nullptr)
	{ // 使用されている場合

		// プレイヤーの初期化
		if (FAILED(pBullet->Init(playerE)))
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
HRESULT CEffectModel::Init(bool playerE)
{
	// オブジェクトモデルの初期化
	if (FAILED(CObjectModel::Init()))
	{ // 初期化に失敗した場合

		// 失敗を返す
		assert(false);
		return E_FAIL;
	}

	if (playerE == false)
	{
		// モデルを読込・割当
		BindModel("data\\MODEL\\BULLET\\enemy_bullrt.x");
	}
	else
	{
		// モデルを読込・割当
		BindModel("data\\MODEL\\BULLET\\plryer_bullrt.x");
	}

	// 成功を返す
	return S_OK;
}

//====================================================================
//終了処理
//====================================================================
void CEffectModel::Uninit(void)
{
	CObjectModel::Uninit();
}

//====================================================================
//更新処理
//====================================================================
void CEffectModel::Update(void)
{
	D3DXVECTOR3 pos = GetVec3Position();

	pos += m_move;

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

	SetAlpha((float)m_nLife / (float)m_nLifeMax);

	//頂点情報の更新
	CObjectModel::Update();
}

//====================================================================
//描画処理
//====================================================================
void CEffectModel::Draw(void)
{
	CObjectModel::Draw();
}