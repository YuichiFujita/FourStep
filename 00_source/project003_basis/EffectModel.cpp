//============================================
//
//	���� [MapCannon.cpp]
//	Author:sakamoto kai
//
//============================================
#include "EffectModel.h"
#include "manager.h"
#include "gamemanager.h"
#include "collision.h"
#include "player.h"

//�}�N����`
#define BLOCK_WIGHT (300.0f)		//����
#define BLOCK_HEIGHT (300.0f)		//�c��
#define WALL_UPEND (20.0f)			//�㏸�ʒu

//====================================================================
//�R���X�g���N�^
//====================================================================
CEffectModel::CEffectModel() : CObjectModel(CObject::LABEL_PLAYER, 3)
{
	m_nLife = 30;
	m_nLifeMax = m_nLife;
}

//====================================================================
//�f�X�g���N�^
//====================================================================
CEffectModel::~CEffectModel()
{

}

//====================================================================
//��������
//====================================================================
CEffectModel* CEffectModel::Create(bool playerE)
{
	// �|�C���^��錾
	CEffectModel* pBullet = nullptr;	// �v���C���[�����p

	if (pBullet == nullptr)
	{ // �g�p����Ă��Ȃ��ꍇ

		// �������m��
		pBullet = new CEffectModel;	// �v���C���[
	}
	else { assert(false); return nullptr; }	// �g�p��

	if (pBullet != nullptr)
	{ // �g�p����Ă���ꍇ

		// �v���C���[�̏�����
		if (FAILED(pBullet->Init(playerE)))
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
HRESULT CEffectModel::Init(bool playerE)
{
	// �I�u�W�F�N�g���f���̏�����
	if (FAILED(CObjectModel::Init()))
	{ // �������Ɏ��s�����ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	if (playerE == false)
	{
		// ���f����Ǎ��E����
		BindModel("data\\MODEL\\BULLET\\enemy_bullrt.x");
	}
	else
	{
		// ���f����Ǎ��E����
		BindModel("data\\MODEL\\BULLET\\plryer_bullrt.x");
	}

	// ������Ԃ�
	return S_OK;
}

//====================================================================
//�I������
//====================================================================
void CEffectModel::Uninit(void)
{
	CObjectModel::Uninit();
}

//====================================================================
//�X�V����
//====================================================================
void CEffectModel::Update(void)
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

	SetAlpha((float)m_nLife / (float)m_nLifeMax);

	//���_���̍X�V
	CObjectModel::Update();
}

//====================================================================
//�`�揈��
//====================================================================
void CEffectModel::Draw(void)
{
	CObjectModel::Draw();
}