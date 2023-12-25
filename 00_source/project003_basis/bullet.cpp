//============================================
//
//	���� [MapCannon.cpp]
//	Author:sakamoto kai
//
//============================================
#include "bullet.h"
#include "manager.h"
#include "gamemanager.h"
#include "collision.h"
#include "player.h"
#include "effectmodel.h"

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
	m_PlayerBullet = false;
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
CBullet* CBullet::Create(bool PlayerBullet)
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
		if (FAILED(pBullet->Init(PlayerBullet)))
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
HRESULT CBullet::Init(bool PlayerBullet)
{
	// �I�u�W�F�N�g���f���̏�����
	if (FAILED(CObjectModel::Init()))
	{ // �������Ɏ��s�����ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	m_PlayerBullet = PlayerBullet;

	if (m_PlayerBullet == true)
	{
		// ���f����Ǎ��E����
		BindModel("data\\MODEL\\BULLET\\plryer_bullrt.x");
	}
	else
	{
		// ���f����Ǎ��E����
		BindModel("data\\MODEL\\BULLET\\enemy_bullrt.x");
	}
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

	for (int nCntPri = 0; nCntPri < object::MAX_PRIO; nCntPri++)
	{ // �D�揇�ʂ̑������J��Ԃ�
		// �|�C���^��錾
		CObject* pObjectTop = CObject::GetTop(nCntPri);	// �擪�I�u�W�F�N�g
		if (pObjectTop != NULL)
		{ // �擪�����݂���ꍇ

			// �|�C���^��錾
			CObject* pObjCheck = pObjectTop;	// �I�u�W�F�N�g�m�F�p

			while (pObjCheck != NULL)
			{ // �I�u�W�F�N�g���g�p����Ă���ꍇ�J��Ԃ�

				// �|�C���^��錾
				CObject* pObjectNext = pObjCheck->GetNext();	// ���I�u�W�F�N�g

				if (pObjCheck->GetLabel() == CObject::LABEL_ENEMY && m_PlayerBullet == true)
				{ // �I�u�W�F�N�g���x�����n�Ղł͂Ȃ��ꍇ

					D3DXVECTOR3 posEnemy = pObjCheck->GetVec3Position();	// �G�ʒu

					if (collision::Circle3D(GetVec3Position(), posEnemy, 30.0f,50.0f) == true)
					{
						D3DXVECTOR3 vecKnock = posEnemy - GetVec3Position();	// �m�b�N�o�b�N�x�N�g��
						D3DXVec3Normalize(&vecKnock, &vecKnock);	// ���K��

						// �v���C���[�̃q�b�g����
						pObjCheck->HitKnockBack(0, vecKnock);

						// �ϐ���錾
						D3DXVECTOR3 vec = VEC3_ZERO;	// �x�N�g���̐ݒ�p
						D3DXVECTOR3 pos = VEC3_ZERO;	// �ʒu�̑���p
						D3DXVECTOR3 move = VEC3_ZERO;	// �ړ��ʂ̑���p
						D3DXVECTOR3 rot = VEC3_ZERO;	// �����̑���p

						for (int nCntPart = 0; nCntPart < 15; nCntPart++)
						{ // ���������G�t�F�N�g�����J��Ԃ�

							// �x�N�g���������_���ɐݒ�
							vec.x = sinf((float)(rand() % 629 - 314) / 100.0f) * 1.0f;
							vec.y = cosf((float)(rand() % 629 - 314) / 100.0f) * 1.0f;
							vec.z = cosf((float)(rand() % 629 - 314) / 100.0f) * 1.0f;

							// �x�N�g���𐳋K��
							D3DXVec3Normalize(&vec, &vec);

							// �ړ��ʂ�ݒ�
							move = vec * 10.0f;

							CEffectModel* pModel = CEffectModel::Create(true);
							pModel->SetVec3Position(posEnemy);
							pModel->SetMove(move);
							pModel->SetVec3Scaling(D3DXVECTOR3(0.4f, 0.4f, 0.4f));
						}

						// ���g�̋ʂ̏I��
						Uninit();
						return;
					}
				}
				// ���̃I�u�W�F�N�g�ւ̃|�C���^����
				pObjCheck = pObjectNext;
			}
		}
	}

	if (m_PlayerBullet == false)
	{ // �I�u�W�F�N�g���x�����n�Ղł͂Ȃ��ꍇ

		CPlayer* pPlayer = CScene::GetPlayer();

		if (collision::Circle3D(GetVec3Position(), pPlayer->GetVec3Position(), 30.0f, 50.0f) == true)
		{
			D3DXVECTOR3 vecKnock = pPlayer->GetVec3Position() - GetVec3Position();	// �m�b�N�o�b�N�x�N�g��
			D3DXVec3Normalize(&vecKnock, &vecKnock);	// ���K��

						// �ϐ���錾
			D3DXVECTOR3 vec = VEC3_ZERO;	// �x�N�g���̐ݒ�p
			D3DXVECTOR3 pos = VEC3_ZERO;	// �ʒu�̑���p
			D3DXVECTOR3 move = VEC3_ZERO;	// �ړ��ʂ̑���p
			D3DXVECTOR3 rot = VEC3_ZERO;	// �����̑���p

			for (int nCntPart = 0; nCntPart < 15; nCntPart++)
			{ // ���������G�t�F�N�g�����J��Ԃ�

				// �x�N�g���������_���ɐݒ�
				vec.x = sinf((float)(rand() % 629 - 314) / 100.0f) * 1.0f;
				vec.y = cosf((float)(rand() % 629 - 314) / 100.0f) * 1.0f;
				vec.z = cosf((float)(rand() % 629 - 314) / 100.0f) * 1.0f;

				// �x�N�g���𐳋K��
				D3DXVec3Normalize(&vec, &vec);

				// �ړ��ʂ�ݒ�
				move = vec * 10.0f;

				CEffectModel* pModel = CEffectModel::Create(false);
				pModel->SetVec3Position(pPlayer->GetVec3Position());
				pModel->SetMove(move);
				pModel->SetVec3Scaling(D3DXVECTOR3(0.4f, 0.4f, 0.4f));
			}

			// �v���C���[�̃q�b�g����
			pPlayer->HitKnockBack(0, vecKnock);

			// ���g�̋ʂ̏I��
			Uninit();
			return;
		}
	}

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