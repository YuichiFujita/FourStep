//============================================
//
//	�}�b�v�̒��̑�C [MapCannon.h]
//	Author:sakamoto kai
//
//============================================
#ifndef _EFFECTMODEL_H_
#define _EFFECTMODEL_H_

#include "main.h"
#include "objectModel.h"

//�O���錾

//�I�u�W�F�N�g�v���C���[�N���X
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
	D3DXVECTOR3 m_move;						//�ړ���		
	int m_nLife;							//�ړ���		
	int m_nLifeMax;							//�ړ���		
	bool playerE;							//�ړ���		
};
#endif