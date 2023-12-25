//============================================================
//
//	通常敵ヘッダー [enemyNormal.h]
//	Author：藤田勇一
//
//============================================================
#if 1
//************************************************************
//	二重インクルード防止
//************************************************************
#ifndef _ENEMY_NORMAL_H_
#define _ENEMY_NORMAL_H_

//************************************************************
//	インクルードファイル
//************************************************************
#include "enemy.h"

//************************************************************
//	クラス定義
//************************************************************
// 通常敵クラス
class CEnemyNormal : public CEnemy
{
public:
	// 種類列挙
	enum EModel
	{
		MODEL_NORMAL = 0,	// 通常
		MODEL_MAX			// この列挙型の総数
	};

	// コンストラクタ
	explicit CEnemyNormal(const EType type);

	// デストラクタ
	~CEnemyNormal() override;

	// オーバーライド関数
	HRESULT Init(void) override;	// 初期化
	void Uninit(void) override;		// 終了
	void Update(void) override;		// 更新
	void Draw(void) override;		// 描画

private:
	// 静的メンバ変数
	static const char *mc_apModelFile[];	// モデル定数

	// メンバ変数

};

#endif	// _ENEMY_H_
#endif
