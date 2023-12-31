//============================================================
//
//	地盤ヘッダー [ground.h]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	二重インクルード防止
//************************************************************
#ifndef _GROUND_H_
#define _GROUND_H_

//************************************************************
//	インクルードファイル
//************************************************************
#include "main.h"
#include "objectMeshCube.h"

//************************************************************
//	クラス定義
//************************************************************
// 地盤クラス
class CGround : public CObjectMeshCube
{
public:

	// コンストラクタ
	CGround();

	// デストラクタ
	~CGround();

	// オーバーライド関数
	HRESULT Init(void) override;	// 初期化
	void Uninit(void) override;		// 終了
	void Update(void) override;		// 更新
	void Draw(void) override;		// 描画

	void SetWNumber(int nData) { m_WNumber = nData; }
	void SetHNumber(int nData) { m_HNumber = nData; }
	void DelColor(float Del) { m_fLife -= Del; }

	// 静的メンバ関数
	static CGround *Create	// 生成
	( // 引数
		const D3DXVECTOR3& rPos,	// 位置
		const D3DXVECTOR3& rRot,	// 向き
		const D3DXVECTOR3& rSize,	// 大きさ
		const D3DXVECTOR2& rTexPartX = VEC2_ONE,	// テクスチャ分割数X
		const D3DXVECTOR2& rTexPartY = VEC2_ONE,	// テクスチャ分割数Y
		const D3DXVECTOR2& rTexPartZ = VEC2_ONE		// テクスチャ分割数Z
	);

private:
	float m_fLife; //横番号
	int m_WNumber; //横番号
	int m_HNumber; //縦番号
};

#endif	// _GROUND_H_
