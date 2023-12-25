//============================================================
//
//	�n�Ճw�b�_�[ [ground.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _MAP_H_
#define _MAP_H_

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "main.h"
#include "objectMeshCube.h"

//************************************************************
//	�}�N����`
//************************************************************
#define BLOCK_WIGHT		(10)
#define BLOCK_HEIGHT	(10)

//************************************************************
//	�N���X��`
//************************************************************
// �n�ՃN���X
class CMap
{
public:
	// �R���X�g���N�^
	CMap();

	// �f�X�g���N�^
	~CMap();

	// �I�[�o�[���C�h�֐�
	HRESULT Init(void);	// ������
	void Uninit(void);		// �I��
	void Update(void);		// �X�V
	void Draw(void);		// �`��

	// �ÓI�����o�֐�
	static CMap* Create	// ����
	( // ����
		const D3DXVECTOR3& rPos,	// �ʒu
		const D3DXVECTOR3& rRot,	// ����
		const D3DXVECTOR3& rSize,	// �傫��
		const D3DXVECTOR2& rTexPartX = VEC2_ONE,	// �e�N�X�`��������X
		const D3DXVECTOR2& rTexPartY = VEC2_ONE,	// �e�N�X�`��������Y
		const D3DXVECTOR2& rTexPartZ = VEC2_ONE		// �e�N�X�`��������Z
	);

private:

	void SetGround(
		const D3DXVECTOR3& rPos,	// �ʒu
		const D3DXVECTOR3& rRot,	// ����
		const D3DXVECTOR3& rSize,	// �傫��
		const D3DXVECTOR2& rTexPartX = VEC2_ONE,	// �e�N�X�`��������X
		const D3DXVECTOR2& rTexPartY = VEC2_ONE,	// �e�N�X�`��������Y
		const D3DXVECTOR2& rTexPartZ = VEC2_ONE		// �e�N�X�`��������Z
	);	// �u���b�N�̐ݒu

	bool m_bUseBlock[BLOCK_WIGHT][BLOCK_HEIGHT];
};

#endif	// _GROUND_H_
