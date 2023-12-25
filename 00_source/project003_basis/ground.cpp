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
#include "manager.h"
#include "renderer.h"
#include "texture.h"
#include "gamemanager.h"
#include "map.h"

//************************************************************
//	マクロ定義
//************************************************************
#define GROUND_PRIO	(1)	// 地盤の優先順位

//************************************************************
//	静的メンバ変数宣言
//************************************************************

//************************************************************
//	子クラス [CGround] のメンバ関数
//************************************************************
//============================================================
//	コンストラクタ
//============================================================
CGround::CGround() : CObjectMeshCube(CObject::LABEL_GROUND, GROUND_PRIO)
{
	// メンバ変数をクリア
}

//============================================================
//	デストラクタ
//============================================================
CGround::~CGround()
{

}

//============================================================
//	初期化処理
//============================================================
HRESULT CGround::Init(void)
{
	// メンバ変数を初期化
	m_WNumber = -1;
	m_HNumber = -1;

	// オブジェクトメッシュキューブの初期化
	if (FAILED(CObjectMeshCube::Init()))
	{ // 初期化に失敗した場合

		// 失敗を返す
		assert(false);
		return E_FAIL;
	}

	// 原点を設定
	SetOrigin(CObjectMeshCube::ORIGIN_UP);

	// キューブ色を設定
	SetColor(XCOL_WHITE);

	// 縁取り色を設定
	SetBorderColor(XCOL_WHITE);

	// 縁取りの状態を設定
	if (FAILED(SetBorderState(CObjectMeshCube::BORDER_OFF)))
	{ // 分割数の設定に失敗した場合

		// 失敗を返す
		assert(false);
		return E_FAIL;
	}

	// 縁取りの太さを設定
	SetBorderThick(0.0f);

	// テクスチャの状態を設定
	SetTextureState(CObjectMeshCube::TEXSTATE_SELECT);

	// カリングを設定
	SetCulling(D3DCULL_CCW);

	// ライティングを設定
	SetLighting(true);

	// 成功を返す
	return S_OK;
}

//============================================================
//	終了処理
//============================================================
void CGround::Uninit(void)
{
	CGameManager::GetMap()->FalseUseBlock(m_WNumber, m_HNumber);
	// オブジェクトメッシュキューブの終了
	CObjectMeshCube::Uninit();
}

//============================================================
//	更新処理
//============================================================
void CGround::Update(void)
{
	// オブジェクトメッシュキューブの更新
	CObjectMeshCube::Update();
}

//============================================================
//	描画処理
//============================================================
void CGround::Draw(void)
{
	// オブジェクトメッシュキューブの描画
	CObjectMeshCube::Draw();
}

//============================================================
//	生成処理
//============================================================
CGround *CGround::Create
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
	CGround *pGround = NULL;	// 地盤生成用

	if (pGround == NULL)
	{ // 使用されていない場合

		// メモリ確保
		pGround = new CGround;	// 地盤
	}
	else { assert(false); return NULL; }	// 使用中

	if (pGround != NULL)
	{ // 確保に成功している場合

		// 地盤の初期化
		if (FAILED(pGround->Init()))
		{ // 初期化に失敗した場合

			// メモリ開放
			delete pGround;
			pGround = NULL;

			// 失敗を返す
			return NULL;
		}

		// 位置を設定
		pGround->SetVec3Position(rPos);

		// 向きを設定
		pGround->SetVec3Rotation(rRot);

		// 大きさを設定
		pGround->SetVec3Sizing(rSize);

		// テクスチャの分割数Xを設定
		pGround->SetTexturePatternX(rTexPartX);

		// テクスチャの分割数Yを設定
		pGround->SetTexturePatternY(rTexPartY);

		// テクスチャの分割数Zを設定
		pGround->SetTexturePatternZ(rTexPartZ);

		// 確保したアドレスを返す
		return pGround;
	}
	else { assert(false); return NULL; }	// 確保失敗
}
