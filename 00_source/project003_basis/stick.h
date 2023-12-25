//============================================
//
//	マップの中の大砲 [MapCannon.h]
//	Author:sakamoto kai
//
//============================================
#ifndef _STICK_H_
#define _STICK_H_

#include "main.h"
#include "objectModel.h"

//前方宣言

//オブジェクトプレイヤークラス
class CStick : public CObjectModel
{
public:

	CStick();
	~CStick();

	static CStick* Create();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	int GetIdxXModel(void) { return -1; }

	void SetMove(D3DXVECTOR3 Move) { m_move = Move; }
	D3DXVECTOR3 GetMove(void) { return m_move; }

private:
	D3DXVECTOR3 m_move;						//移動量		
	float m_AtkRot;					//攻撃の時の向き		
	int m_nLifeMax;							//移動量		
	int m_nLife;							//移動量		
};
#endif