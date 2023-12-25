//============================================
//
//	たま [MapCannon.cpp]
//	Author:sakamoto kai
//
//============================================
#include "stick.h"
#include "manager.h"
#include "gamemanager.h"
#include "scene.h"
#include "player.h"

//マクロ定義
#define BLOCK_WIGHT (300.0f)		//横幅
#define BLOCK_HEIGHT (300.0f)		//縦幅
#define WALL_UPEND (20.0f)			//上昇位置

//====================================================================
//コンストラクタ
//====================================================================
CStick::CStick() : CObjectModel(CObject::LABEL_PLAYER, 3)
{
	m_nLife = 30;
	m_nLifeMax = m_nLife;
	m_AtkRot = (D3DX_PI / ((float)m_nLifeMax * 0.5f));
}

//====================================================================
//デストラクタ
//====================================================================
CStick::~CStick()
{

}

//====================================================================
//生成処理
//====================================================================
CStick* CStick::Create()
{
	// ポインタを宣言
	CStick* pBullet = nullptr;	// プレイヤー生成用

	if (pBullet == nullptr)
	{ // 使用されていない場合

		// メモリ確保
		pBullet = new CStick;	// プレイヤー
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
HRESULT CStick::Init(void)
{
	// オブジェクトモデルの初期化
	if (FAILED(CObjectModel::Init()))
	{ // 初期化に失敗した場合

		// 失敗を返す
		assert(false);
		return E_FAIL;
	}

	// モデルを読込・割当
	BindModel("data\\MODEL\\PLAYER\\kinobou.x");

	// 成功を返す
	return S_OK;
}

//====================================================================
//終了処理
//====================================================================
void CStick::Uninit(void)
{
	CObjectModel::Uninit();
}

//====================================================================
//更新処理
//====================================================================
void CStick::Update(void)
{
	D3DXVECTOR3 rot = GetVec3Rotation();

	if (m_nLife > (int)((float)m_nLifeMax * 0.5f))
	{
		rot.y += m_AtkRot;
		m_nLife--;
	}
	else if (m_nLife > 0)
	{
		rot.y -= m_AtkRot;
		m_nLife--;
	}
	else
	{
		CScene::GetPlayer()->SetAttack(false);
		Uninit();
		return;
	}

	SetVec3Position(CScene::GetPlayer()->GetVec3Position());
	SetVec3Rotation(rot);

	//頂点情報の更新
	CObjectModel::Update();
}

//====================================================================
//描画処理
//====================================================================
void CStick::Draw(void)
{
	CObjectModel::Draw();
}