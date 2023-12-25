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
#include "manager.h"
#include "renderer.h"
#include "texture.h"
#include "gamemanager.h"
#include "map.h"

//************************************************************
//	�}�N����`
//************************************************************
#define GROUND_PRIO	(1)	// �n�Ղ̗D�揇��

//************************************************************
//	�ÓI�����o�ϐ��錾
//************************************************************

//************************************************************
//	�q�N���X [CGround] �̃����o�֐�
//************************************************************
//============================================================
//	�R���X�g���N�^
//============================================================
CGround::CGround() : CObjectMeshCube(CObject::LABEL_GROUND, GROUND_PRIO)
{
	// �����o�ϐ����N���A
}

//============================================================
//	�f�X�g���N�^
//============================================================
CGround::~CGround()
{

}

//============================================================
//	����������
//============================================================
HRESULT CGround::Init(void)
{
	// �����o�ϐ���������
	m_WNumber = -1;
	m_HNumber = -1;

	// �I�u�W�F�N�g���b�V���L���[�u�̏�����
	if (FAILED(CObjectMeshCube::Init()))
	{ // �������Ɏ��s�����ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	// ���_��ݒ�
	SetOrigin(CObjectMeshCube::ORIGIN_UP);

	// �L���[�u�F��ݒ�
	SetColor(XCOL_WHITE);

	// �����F��ݒ�
	SetBorderColor(XCOL_WHITE);

	// �����̏�Ԃ�ݒ�
	if (FAILED(SetBorderState(CObjectMeshCube::BORDER_OFF)))
	{ // �������̐ݒ�Ɏ��s�����ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	// �����̑�����ݒ�
	SetBorderThick(0.0f);

	// �e�N�X�`���̏�Ԃ�ݒ�
	SetTextureState(CObjectMeshCube::TEXSTATE_SELECT);

	// �J�����O��ݒ�
	SetCulling(D3DCULL_CCW);

	// ���C�e�B���O��ݒ�
	SetLighting(true);

	// ������Ԃ�
	return S_OK;
}

//============================================================
//	�I������
//============================================================
void CGround::Uninit(void)
{
	CGameManager::GetMap()->FalseUseBlock(m_WNumber, m_HNumber);
	// �I�u�W�F�N�g���b�V���L���[�u�̏I��
	CObjectMeshCube::Uninit();
}

//============================================================
//	�X�V����
//============================================================
void CGround::Update(void)
{
	// �I�u�W�F�N�g���b�V���L���[�u�̍X�V
	CObjectMeshCube::Update();
}

//============================================================
//	�`�揈��
//============================================================
void CGround::Draw(void)
{
	// �I�u�W�F�N�g���b�V���L���[�u�̕`��
	CObjectMeshCube::Draw();
}

//============================================================
//	��������
//============================================================
CGround *CGround::Create
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
	CGround *pGround = NULL;	// �n�Ր����p

	if (pGround == NULL)
	{ // �g�p����Ă��Ȃ��ꍇ

		// �������m��
		pGround = new CGround;	// �n��
	}
	else { assert(false); return NULL; }	// �g�p��

	if (pGround != NULL)
	{ // �m�ۂɐ������Ă���ꍇ

		// �n�Ղ̏�����
		if (FAILED(pGround->Init()))
		{ // �������Ɏ��s�����ꍇ

			// �������J��
			delete pGround;
			pGround = NULL;

			// ���s��Ԃ�
			return NULL;
		}

		// �ʒu��ݒ�
		pGround->SetVec3Position(rPos);

		// ������ݒ�
		pGround->SetVec3Rotation(rRot);

		// �傫����ݒ�
		pGround->SetVec3Sizing(rSize);

		// �e�N�X�`���̕�����X��ݒ�
		pGround->SetTexturePatternX(rTexPartX);

		// �e�N�X�`���̕�����Y��ݒ�
		pGround->SetTexturePatternY(rTexPartY);

		// �e�N�X�`���̕�����Z��ݒ�
		pGround->SetTexturePatternZ(rTexPartZ);

		// �m�ۂ����A�h���X��Ԃ�
		return pGround;
	}
	else { assert(false); return NULL; }	// �m�ێ��s
}
