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
#include "enemy.h"

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
	for (int nCntW = 0; nCntW < BLOCK_WIGHT; nCntW++)
	{
		for (int nCntH = 0; nCntH < BLOCK_HEIGHT; nCntH++)
		{
			m_bUseBlock[nCntW][nCntH] = false;
		}
	}
	nCntTime = 0;
	nSpwnEnemy = 4;
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
	if (nCntTime % 300 == 0)
	{
		int nCntEnemy = 0;
		for (int nCntW = 0; nCntW < BLOCK_WIGHT; nCntW++)
		{
			for (int nCntH = 0; nCntH < BLOCK_HEIGHT; nCntH++)
			{
				if (nCntEnemy < nSpwnEnemy)
				{
					int Rand = rand() % 100;
					if (Rand >= 98)
					{
						nCntEnemy++;
						CEnemy::Create(CEnemy::TYPE_NORMAL, D3DXVECTOR3(-1000.0f + nCntW * 110.0f, 0.0f, -1000.0f + nCntH * 110.0f), VEC3_ZERO);
					}
				}
			}
		}
	}

	nCntTime++;
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
			CGround *pGround = CGround::Create(D3DXVECTOR3(-1000.0f + nCntW * 110.0f, rPos.y, -1000.0f + nCntH * 110.0f), rRot, rSize, rTexPartX, rTexPartY, rTexPartZ);
			pGround->SetWNumber(nCntW);
			pGround->SetHNumber(nCntH);
			m_bUseBlock[nCntW][nCntH] = true;
		}
	}
}