//============================================
//
//	マップの中の大砲 [MapCannon.h]
//	Author:sakamoto kai
//
//============================================
#ifndef _CANNONBULLET_H_
#define _CANNONBULLET_H_

#include "main.h"
#include "objectModel.h"

//前方宣言

//オブジェクトプレイヤークラス
class CBullet : public CObjectModel
{
public:

	CBullet();
	~CBullet();

	static CBullet* Create();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	int GetIdxXModel(void) { return -1; }

	void SetMove(D3DXVECTOR3 Move) { m_move = Move; }
	D3DXVECTOR3 GetMove(void) { return m_move; }

private:
	D3DXVECTOR3 m_move;						//移動量		
	int m_nLife;							//移動量		
};
#endif