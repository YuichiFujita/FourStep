//============================================================
//
//	地盤ヘッダー [ground.h]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	二重インクルード防止
//************************************************************
#ifndef _MAP_H_
#define _MAP_H_

//************************************************************
//	インクルードファイル
//************************************************************
#include "main.h"
#include "objectMeshCube.h"

//************************************************************
//	マクロ定義
//************************************************************
#define BLOCK_WIGHT		(10)
#define BLOCK_HEIGHT	(10)

//************************************************************
//	クラス定義
//************************************************************
// 地盤クラス
class CMap
{
public:
	// コンストラクタ
	CMap();

	// デストラクタ
	~CMap();

	// オーバーライド関数
	HRESULT Init(void);	// 初期化
	void Uninit(void);		// 終了
	void Update(void);		// 更新
	void Draw(void);		// 描画

	// 静的メンバ関数
	static CMap* Create	// 生成
	( // 引数
		const D3DXVECTOR3& rPos,	// 位置
		const D3DXVECTOR3& rRot,	// 向き
		const D3DXVECTOR3& rSize,	// 大きさ
		const D3DXVECTOR2& rTexPartX = VEC2_ONE,	// テクスチャ分割数X
		const D3DXVECTOR2& rTexPartY = VEC2_ONE,	// テクスチャ分割数Y
		const D3DXVECTOR2& rTexPartZ = VEC2_ONE		// テクスチャ分割数Z
	);

private:

	void SetGround(
		const D3DXVECTOR3& rPos,	// 位置
		const D3DXVECTOR3& rRot,	// 向き
		const D3DXVECTOR3& rSize,	// 大きさ
		const D3DXVECTOR2& rTexPartX = VEC2_ONE,	// テクスチャ分割数X
		const D3DXVECTOR2& rTexPartY = VEC2_ONE,	// テクスチャ分割数Y
		const D3DXVECTOR2& rTexPartZ = VEC2_ONE		// テクスチャ分割数Z
	);	// ブロックの設置

	bool m_bUseBlock[BLOCK_WIGHT][BLOCK_HEIGHT];
};

#endif	// _GROUND_H_
