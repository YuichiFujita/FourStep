//============================================================
//
//	�n�Տ��� [ground.cpp]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "ground.h"
#include "map.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"

//************************************************************
//	�}�N����`
//************************************************************
#define GROUND_PRIO	(1)	// �n�Ղ̗D�揇��

//************************************************************
//	�q�N���X [CMap] �̃����o�֐�
//************************************************************
//============================================================
//	�R���X�g���N�^
//============================================================
CMap::CMap()
{
	// �����o�ϐ����N���A
}

//============================================================
//	�f�X�g���N�^
//============================================================
CMap::~CMap()
{

}

//============================================================
//	����������
//============================================================
HRESULT CMap::Init(void)
{
	// ������Ԃ�
	return S_OK;
}

//============================================================
//	�I������
//============================================================
void CMap::Uninit(void)
{
	delete this;
}

//============================================================
//	�X�V����
//============================================================
void CMap::Update(void)
{

}

//============================================================
//	�`�揈��
//============================================================
void CMap::Draw(void)
{

}

//============================================================
//	��������
//============================================================
CMap* CMap::Create
(
	const D3DXVECTOR3& rPos,		// �ʒu
	const D3DXVECTOR3& rRot,		// ����
	const D3DXVECTOR3& rSize,		// �傫��
	const D3DXVECTOR2& rTexPartX,	// �e�N�X�`��������X
	const D3DXVECTOR2& rTexPartY,	// �e�N�X�`��������Y
	const D3DXVECTOR2& rTexPartZ	// �e�N�X�`��������Z
)
{
	// �|�C���^��錾
	CMap* pMap = NULL;	// �n�Ր����p

	if (pMap == NULL)
	{ // �g�p����Ă��Ȃ��ꍇ

		// �������m��
		pMap = new CMap;	// �n��
	}
	else { assert(false); return NULL; }	// �g�p��

	if (pMap != NULL)
	{ // �m�ۂɐ������Ă���ꍇ

		// �n�Ղ̏�����
		if (FAILED(pMap->Init()))
		{ // �������Ɏ��s�����ꍇ

			// �������J��
			delete pMap;
			pMap = NULL;

			// ���s��Ԃ�
			return NULL;
		}

		//�u���b�N�̐ݒu
		pMap->SetGround(rPos, rRot, rSize, rTexPartX, rTexPartY, rTexPartZ);

		// �m�ۂ����A�h���X��Ԃ�
		return pMap;
	}
	else { assert(false); return NULL; }	// �m�ێ��s
}

//============================================================
//	��������
//============================================================
void CMap::SetGround
(
	const D3DXVECTOR3& rPos,		// �ʒu
	const D3DXVECTOR3& rRot,		// ����
	const D3DXVECTOR3& rSize,		// �傫��
	const D3DXVECTOR2& rTexPartX,	// �e�N�X�`��������X
	const D3DXVECTOR2& rTexPartY,	// �e�N�X�`��������Y
	const D3DXVECTOR2& rTexPartZ	// �e�N�X�`��������Z
)
{
	for (int nCntW = 0; nCntW < BLOCK_WIGHT; nCntW++)
	{
		for (int nCntH = 0; nCntH < BLOCK_HEIGHT; nCntH++)
		{
			m_bUseBlock[nCntW][nCntH] = false;
			CGround::Create(D3DXVECTOR3(rPos.x + nCntW * 110.0f, rPos.y, rPos.z + nCntH * 110.0f), rRot, rSize, rTexPartX, rTexPartY, rTexPartZ);
		}
	}
}