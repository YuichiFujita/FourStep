//============================================
//
//	���� [MapCannon.cpp]
//	Author:sakamoto kai
//
//============================================
#include "bullet.h"
#include "manager.h"
#include "gamemanager.h"

//�}�N����`
#define BLOCK_WIGHT (300.0f)		//����
#define BLOCK_HEIGHT (300.0f)		//�c��
#define WALL_UPEND (20.0f)			//�㏸�ʒu

//====================================================================
//�R���X�g���N�^
//====================================================================
CBullet::CBullet() : CObjectModel(CObject::LABEL_PLAYER, 3)
{
	m_nLife = 120;
}

//====================================================================
//�f�X�g���N�^
//====================================================================
CBullet::~CBullet()
{

}

//====================================================================
//��������
//====================================================================
CBullet* CBullet::Create()
{
	// �|�C���^��錾
	CBullet* pBullet = nullptr;	// �v���C���[�����p

	if (pBullet == nullptr)
	{ // �g�p����Ă��Ȃ��ꍇ

		// �������m��
		pBullet = new CBullet;	// �v���C���[
	}
	else { assert(false); return nullptr; }	// �g�p��

	if (pBullet != nullptr)
	{ // �g�p����Ă���ꍇ

		// �v���C���[�̏�����
		if (FAILED(pBullet->Init()))
		{ // �������Ɏ��s�����ꍇ

			// �������J��
			delete pBullet;
			pBullet = nullptr;

			// ���s��Ԃ�
			return nullptr;
		}
	}

	// �m�ۂ����A�h���X��Ԃ�
	return pBullet;
}

//====================================================================
//����������
//====================================================================
HRESULT CBullet::Init(void)
{
	// �I�u�W�F�N�g���f���̏�����
	if (FAILED(CObjectModel::Init()))
	{ // �������Ɏ��s�����ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	// ���f����Ǎ��E����
	BindModel("data\\MODEL\\BULLET\\1225_pl_003.x");

	// ������Ԃ�
	return S_OK;
}

//====================================================================
//�I������
//====================================================================
void CBullet::Uninit(void)
{
	CObjectModel::Uninit();
}

//====================================================================
//�X�V����
//====================================================================
void CBullet::Update(void)
{
	D3DXVECTOR3 pos = GetVec3Position();

	pos += m_move;

	SetVec3Position(pos);

	if (m_nLife > 0)
	{
		m_nLife--;
	}
	else
	{
		Uninit();
		return;
	}

	//���_���̍X�V
	CObjectModel::Update();
}

//====================================================================
//�`�揈��
//====================================================================
void CBullet::Draw(void)
{
	CObjectModel::Draw();
}