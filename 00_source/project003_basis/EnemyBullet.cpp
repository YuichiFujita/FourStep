//============================================================
//
//	�ʏ�G���� [enemyNormal.cpp]
//	Author�F���c�E��
//
//============================================================
#if 1
//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "EnemyBullet.h"
#include "manager.h"
#include "renderer.h"
#include "bullet.h"

//************************************************************
//	�萔�錾
//************************************************************
namespace
{

}

//************************************************************
//	�ÓI�����o�ϐ��錾
//************************************************************
const char* CEnemyBullet::mc_apModelFile[] =	// ���f���萔
{
	"data\\MODEL\\ENEMY\\1225_tama_003.x",	// �ʏ�G
};

//************************************************************
//	�q�N���X [CEnemyBullet] �̃����o�֐�
//************************************************************
//============================================================
//	�R���X�g���N�^
//============================================================
CEnemyBullet::CEnemyBullet(const EType type) : CEnemy(type)
{
	// �����o�ϐ����N���A
	m_nCntBullet = 0;

}

//============================================================
//	�f�X�g���N�^
//============================================================
CEnemyBullet::~CEnemyBullet()
{

}

//============================================================
//	����������
//============================================================
HRESULT CEnemyBullet::Init(void)
{
	// �����o�ϐ���������


	// �G�̏�����
	if (FAILED(CEnemy::Init()))
	{ // �������Ɏ��s�����ꍇ

		// ���s��Ԃ�
		return E_FAIL;
	}

	// ���f����Ǎ��E����
	BindModel("data\\MODEL\\ENEMY\\1225_tama_003.x");

	SetAlpha(0.0f);

	// ������Ԃ�
	return S_OK;
}

//============================================================
//	�I������
//============================================================
void CEnemyBullet::Uninit(void)
{
	// �G�̏I��
	CEnemy::Uninit();
}

//============================================================
//	�X�V����
//============================================================
void CEnemyBullet::Update(void)
{
	switch (GetState())
	{ // ��Ԃ��Ƃ̏���
	case STATE_SPAWN:

		// �X�|�[������̍X�V
		UpdateSpawn();

		break;

	case STATE_NORMAL:

		// �G����̍X�V
		UpdateAction();

		m_nCntBullet++;

		if (m_nCntBullet % 180 == 0)
		{
			CBullet* pBullet = CBullet::Create(false);
			pBullet->SetVec3Position(GetVec3Position());
			pBullet->SetMove(D3DXVECTOR3(
				-cosf(GetVec3Rotation().y + D3DX_PI * -0.5f) * 25.0f,
				0.0f,
				sinf(GetVec3Rotation().y + D3DX_PI * -0.5f) * 25.0f
			));
		}

		break;

	case STATE_KNOCK:

		// ������ю��̍X�V
		UpdateKnock();

		break;

	case STATE_DEATH:

		// ���S����̍X�V
		if (UpdateDeath())
		{ // ���S�����ꍇ

			// �����𔲂���
			return;
		}

		break;

	default:	// ��O����
		assert(false);
		break;
	}

	// �G�̍X�V
	CEnemy::Update();
}

//============================================================
//	�`�揈��
//============================================================
void CEnemyBullet::Draw(void)
{
	// �G�̕`��
	CEnemy::Draw();
}
#endif