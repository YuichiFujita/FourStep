//============================================================
//
//	通常敵処理 [enemyNormal.cpp]
//	Author：藤田勇一
//
//============================================================
#if 1
//************************************************************
//	インクルードファイル
//************************************************************
#include "enemyNormal.h"
#include "manager.h"
#include "renderer.h"

//************************************************************
//	定数宣言
//************************************************************
namespace
{

}

//************************************************************
//	静的メンバ変数宣言
//************************************************************
const char *CEnemyNormal::mc_apModelFile[] =	// モデル定数
{
	"data\\MODEL\\ENEMY\\1225_en_003.x",	// 通常敵
};

//************************************************************
//	子クラス [CEnemyNormal] のメンバ関数
//************************************************************
//============================================================
//	コンストラクタ
//============================================================
CEnemyNormal::CEnemyNormal(const EType type) : CEnemy(type)
{
	// メンバ変数をクリア

}

//============================================================
//	デストラクタ
//============================================================
CEnemyNormal::~CEnemyNormal()
{

}

//============================================================
//	初期化処理
//============================================================
HRESULT CEnemyNormal::Init(void)
{
	// メンバ変数を初期化


	// 敵の初期化
	if (FAILED(CEnemy::Init()))
	{ // 初期化に失敗した場合

		// 失敗を返す
		return E_FAIL;
	}

	// モデルを読込・割当
	BindModel(mc_apModelFile[MODEL_NORMAL]);

	SetAlpha(0.0f);

	// 成功を返す
	return S_OK;
}

//============================================================
//	終了処理
//============================================================
void CEnemyNormal::Uninit(void)
{
	// 敵の終了
	CEnemy::Uninit();
}

//============================================================
//	更新処理
//============================================================
void CEnemyNormal::Update(void)
{
	switch (GetState())
	{ // 状態ごとの処理
	case STATE_SPAWN:

		// スポーン動作の更新
		UpdateSpawn();

		break;

	case STATE_NORMAL:

		// 敵動作の更新
		UpdateAction();

		break;

	case STATE_KNOCK:

		// 吹っ飛び時の更新
		UpdateKnock();

		break;

	case STATE_DEATH:

		// 死亡動作の更新
		if (UpdateDeath())
		{ // 死亡した場合

			// 処理を抜ける
			return;
		}

		break;

	default:	// 例外処理
		assert(false);
		break;
	}

	// 敵の更新
	CEnemy::Update();
}

//============================================================
//	描画処理
//============================================================
void CEnemyNormal::Draw(void)
{
	// 敵の描画
	CEnemy::Draw();
}
#endif
