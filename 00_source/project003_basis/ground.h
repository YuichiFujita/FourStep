//============================================================
//
//	�n�Ճw�b�_�[ [ground.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _GROUND_H_
#define _GROUND_H_

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "main.h"
#include "objectMeshCube.h"

//************************************************************
//	�N���X��`
//************************************************************
// �n�ՃN���X
class CGround : public CObjectMeshCube
{
public:

	// �R���X�g���N�^
	CGround();

	// �f�X�g���N�^
	~CGround();

	// �I�[�o�[���C�h�֐�
	HRESULT Init(void) override;	// ������
	void Uninit(void) override;		// �I��
	void Update(void) override;		// �X�V
	void Draw(void) override;		// �`��

	// �ÓI�����o�֐�
	static CGround *Create	// ����
	( // ����
		const D3DXVECTOR3& rPos,	// �ʒu
		const D3DXVECTOR3& rRot,	// ����
		const D3DXVECTOR3& rSize,	// �傫��
		const D3DXVECTOR2& rTexPartX = VEC2_ONE,	// �e�N�X�`��������X
		const D3DXVECTOR2& rTexPartY = VEC2_ONE,	// �e�N�X�`��������Y
		const D3DXVECTOR2& rTexPartZ = VEC2_ONE		// �e�N�X�`��������Z
	);

private:
};

#endif	// _GROUND_H_
