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
	"data\\MODEL\\ENEMY\\escapekun.x",	// 通常敵
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
		Spawn();

		break;

	case STATE_NORMAL:

		// 敵の動作の更新
		//CollisionFind();

		break;

	case STATE_DEATH:

		// 死亡動作の更新
		if (Death())
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

//============================================================
//	検知範囲の当たり判定
//============================================================
#if 0
void CEnemyNormal::CollisionFind(void)
{
	// 変数を宣言
	StatusInfo  status		= GetStatusInfo();		// 敵ステータス
	D3DXVECTOR3 posEnemy	= GetPosition();		// 敵位置
	D3DXVECTOR3 moveEnemy	= GetMovePosition();	// 敵移動量
	D3DXVECTOR3 rotEnemy	= GetRotation();		// 敵向き
	D3DXVECTOR3 posLook		= VEC3_ZERO;			// 視認対象位置
	D3DXVECTOR3 rotCannon	= VEC3_ZERO;			// キャノン向き
	float fLookRadius		= 0.0f;					// 視認対象半径

	D3DXVECTOR3 posBarrier	= CScene::GetStage()->GetStageBarrierPosition();	// バリア位置
	float fPlayerRadius		= CScene::GetPlayer()->GetRadius();	// プレイヤー半径

	// 過去位置の更新
	UpdateOldPosition();

	if (CScene::GetTarget()->GetState() != CTarget::STATE_DESTROY)
	{ // ターゲットが壊されていないる場合

		// 視認対象位置を設定
		posLook = CScene::GetTarget()->GetPosition();	// ターゲット位置

		// 視認対象半径を設定
		fLookRadius = CScene::GetTarget()->GetRadius();	// ターゲット半径

		// 視認対象の攻撃判定
		if (collision::Circle2D(posLook, posEnemy, fPlayerRadius, status.fAttackRadius) == false)
		{ // 敵の攻撃範囲外の場合

			// 対象の方向を向かせる
			Look(posLook, posEnemy, rotEnemy);

			// 対象の方向に移動 (前進)
			moveEnemy.x -= sinf(rotEnemy.y) * status.fForwardMove;
			moveEnemy.z -= cosf(rotEnemy.y) * status.fForwardMove;

			// 重力を加算
			moveEnemy.y -= ENE_GRAVITY;

			// 移動量を加算
			posEnemy += moveEnemy;

			// ノックバックの更新
			UpdateKnockBack(posEnemy);

			// 移動量を減衰
			moveEnemy.x += (0.0f - moveEnemy.x) * ENE_REV;
			moveEnemy.z += (0.0f - moveEnemy.z) * ENE_REV;

			// ターゲットとの当たり判定
			CollisionTarget(posEnemy);

			// 通常状態の敵との当たり判定
			CollisionNormalEnemy(posEnemy);

			// 着地判定
			CScene::GetField()->LandPosition(posEnemy, moveEnemy);

			// ステージ範囲外の補正
			collision::InCirclePillar(posEnemy, posBarrier, status.fRadius, LIMIT_RADIUS);
		}
		else
		{ // 敵の攻撃範囲内の場合

			// ノックバックの更新
			UpdateKnockBack(posEnemy);

			// ターゲットとの当たり判定
			CollisionTarget(posEnemy);

			// 通常状態の敵との当たり判定
			CollisionNormalEnemy(posEnemy);

			// 着地判定
			CScene::GetField()->LandPosition(posEnemy, moveEnemy);

			// ステージ範囲外の補正
			collision::InCirclePillar(posEnemy, posBarrier, status.fRadius, LIMIT_RADIUS);

			// キャノン向きの設定
			if (SetRotationCannon(posLook, posEnemy, rotEnemy))
			{ // 発射可能状態の場合

				// 攻撃
				Attack(posLook, posEnemy, fLookRadius);
			}
		}
	}

	// 位置を反映
	SetPosition(posEnemy);

	// 位置移動量を反映
	SetMovePosition(moveEnemy);

	// 向きを反映
	SetRotation(rotEnemy);
}
#endif

#endif
