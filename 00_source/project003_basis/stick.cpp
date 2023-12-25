//============================================
//
//	���� [MapCannon.cpp]
//	Author:sakamoto kai
//
//============================================
#include "stick.h"
#include "manager.h"
#include "gamemanager.h"
#include "scene.h"
#include "player.h"

//�}�N����`
#define BLOCK_WIGHT (300.0f)		//����
#define BLOCK_HEIGHT (300.0f)		//�c��
#define WALL_UPEND (20.0f)			//�㏸�ʒu

//====================================================================
//�R���X�g���N�^
//====================================================================
CStick::CStick() : CObjectModel(CObject::LABEL_PLAYER, 3)
{
	m_nLife = 30;
	m_nLifeMax = m_nLife;
	m_AtkRot = (D3DX_PI / ((float)m_nLifeMax * 0.5f));
}

//====================================================================
//�f�X�g���N�^
//====================================================================
CStick::~CStick()
{

}

//====================================================================
//��������
//====================================================================
CStick* CStick::Create()
{
	// �|�C���^��錾
	CStick* pBullet = nullptr;	// �v���C���[�����p

	if (pBullet == nullptr)
	{ // �g�p����Ă��Ȃ��ꍇ

		// �������m��
		pBullet = new CStick;	// �v���C���[
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
HRESULT CStick::Init(void)
{
	// �I�u�W�F�N�g���f���̏�����
	if (FAILED(CObjectModel::Init()))
	{ // �������Ɏ��s�����ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	// ���f����Ǎ��E����
	BindModel("data\\MODEL\\PLAYER\\kinobou.x");

	// ������Ԃ�
	return S_OK;
}

//====================================================================
//�I������
//====================================================================
void CStick::Uninit(void)
{
	CObjectModel::Uninit();
}

//====================================================================
//�X�V����
//====================================================================
void CStick::Update(void)
{
	D3DXVECTOR3 rot = GetVec3Rotation();

	if (m_nLife > (int)((float)m_nLifeMax * 0.5f))
	{
		rot.y += m_AtkRot;
		m_nLife--;
	}
	else if (m_nLife > 0)
	{
		rot.y -= m_AtkRot;
		m_nLife--;
	}
	else
	{
		CScene::GetPlayer()->SetAttack(false);
		Uninit();
		return;
	}

	SetVec3Position(CScene::GetPlayer()->GetVec3Position());
	SetVec3Rotation(rot);

	//���_���̍X�V
	CObjectModel::Update();
}

//====================================================================
//�`�揈��
//====================================================================
void CStick::Draw(void)
{
	CObjectModel::Draw();
}