//============================================
//
//	マップの中の大砲 [MapCannon.h]
//	Author:sakamoto kai
//
//============================================
#ifndef _EFFECTMODEL_H_
#define _EFFECTMODEL_H_

#include "main.h"
#include "objectModel.h"

//前方宣言

//オブジェクトプレイヤークラス
class CEffectModel : public CObjectModel
{
public:

	CEffectModel();
	~CEffectModel();

	static CEffectModel* Create(bool playerE);

	HRESULT Init(bool playerE);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	int GetIdxXModel(void) { return -1; }

	void SetMove(D3DXVECTOR3 Move) { m_move = Move; }
	D3DXVECTOR3 GetMove(void) { return m_move; }

private:
	D3DXVECTOR3 m_move;						//移動量		
	int m_nLife;							//移動量		
	int m_nLifeMax;							//移動量		
	bool playerE;							//移動量		
};
#endif