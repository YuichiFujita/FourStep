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
#include "enemyNormal.h"
#include "manager.h"
#include "renderer.h"

//************************************************************
//	�萔�錾
//************************************************************
namespace
{

}

//************************************************************
//	�ÓI�����o�ϐ��錾
//************************************************************
const char *CEnemyNormal::mc_apModelFile[] =	// ���f���萔
{
	"data\\MODEL\\ENEMY\\escapekun.x",	// �ʏ�G
};

//************************************************************
//	�q�N���X [CEnemyNormal] �̃����o�֐�
//************************************************************
//============================================================
//	�R���X�g���N�^
//============================================================
CEnemyNormal::CEnemyNormal(const EType type) : CEnemy(type)
{
	// �����o�ϐ����N���A

}

//============================================================
//	�f�X�g���N�^
//============================================================
CEnemyNormal::~CEnemyNormal()
{

}

//============================================================
//	����������
//============================================================
HRESULT CEnemyNormal::Init(void)
{
	// �����o�ϐ���������


	// �G�̏�����
	if (FAILED(CEnemy::Init()))
	{ // �������Ɏ��s�����ꍇ

		// ���s��Ԃ�
		return E_FAIL;
	}

	// ������Ԃ�
	return S_OK;
}

//============================================================
//	�I������
//============================================================
void CEnemyNormal::Uninit(void)
{
	// �G�̏I��
	CEnemy::Uninit();
}

//============================================================
//	�X�V����
//============================================================
void CEnemyNormal::Update(void)
{
	switch (GetState())
	{ // ��Ԃ��Ƃ̏���
	case STATE_SPAWN:

		// �X�|�[������̍X�V
		Spawn();

		break;

	case STATE_NORMAL:

		// �G�̓���̍X�V
		//CollisionFind();

		break;

	case STATE_DEATH:

		// ���S����̍X�V
		if (Death())
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
void CEnemyNormal::Draw(void)
{
	// �G�̕`��
	CEnemy::Draw();
}

//============================================================
//	���m�͈͂̓����蔻��
//============================================================
#if 0
void CEnemyNormal::CollisionFind(void)
{
	// �ϐ���錾
	StatusInfo  status		= GetStatusInfo();		// �G�X�e�[�^�X
	D3DXVECTOR3 posEnemy	= GetPosition();		// �G�ʒu
	D3DXVECTOR3 moveEnemy	= GetMovePosition();	// �G�ړ���
	D3DXVECTOR3 rotEnemy	= GetRotation();		// �G����
	D3DXVECTOR3 posLook		= VEC3_ZERO;			// ���F�Ώۈʒu
	D3DXVECTOR3 rotCannon	= VEC3_ZERO;			// �L���m������
	float fLookRadius		= 0.0f;					// ���F�Ώ۔��a

	D3DXVECTOR3 posBarrier	= CScene::GetStage()->GetStageBarrierPosition();	// �o���A�ʒu
	float fPlayerRadius		= CScene::GetPlayer()->GetRadius();	// �v���C���[���a

	// �ߋ��ʒu�̍X�V
	UpdateOldPosition();

	if (CScene::GetTarget()->GetState() != CTarget::STATE_DESTROY)
	{ // �^�[�Q�b�g���󂳂�Ă��Ȃ���ꍇ

		// ���F�Ώۈʒu��ݒ�
		posLook = CScene::GetTarget()->GetPosition();	// �^�[�Q�b�g�ʒu

		// ���F�Ώ۔��a��ݒ�
		fLookRadius = CScene::GetTarget()->GetRadius();	// �^�[�Q�b�g���a

		// ���F�Ώۂ̍U������
		if (collision::Circle2D(posLook, posEnemy, fPlayerRadius, status.fAttackRadius) == false)
		{ // �G�̍U���͈͊O�̏ꍇ

			// �Ώۂ̕�������������
			Look(posLook, posEnemy, rotEnemy);

			// �Ώۂ̕����Ɉړ� (�O�i)
			moveEnemy.x -= sinf(rotEnemy.y) * status.fForwardMove;
			moveEnemy.z -= cosf(rotEnemy.y) * status.fForwardMove;

			// �d�͂����Z
			moveEnemy.y -= ENE_GRAVITY;

			// �ړ��ʂ����Z
			posEnemy += moveEnemy;

			// �m�b�N�o�b�N�̍X�V
			UpdateKnockBack(posEnemy);

			// �ړ��ʂ�����
			moveEnemy.x += (0.0f - moveEnemy.x) * ENE_REV;
			moveEnemy.z += (0.0f - moveEnemy.z) * ENE_REV;

			// �^�[�Q�b�g�Ƃ̓����蔻��
			CollisionTarget(posEnemy);

			// �ʏ��Ԃ̓G�Ƃ̓����蔻��
			CollisionNormalEnemy(posEnemy);

			// ���n����
			CScene::GetField()->LandPosition(posEnemy, moveEnemy);

			// �X�e�[�W�͈͊O�̕␳
			collision::InCirclePillar(posEnemy, posBarrier, status.fRadius, LIMIT_RADIUS);
		}
		else
		{ // �G�̍U���͈͓��̏ꍇ

			// �m�b�N�o�b�N�̍X�V
			UpdateKnockBack(posEnemy);

			// �^�[�Q�b�g�Ƃ̓����蔻��
			CollisionTarget(posEnemy);

			// �ʏ��Ԃ̓G�Ƃ̓����蔻��
			CollisionNormalEnemy(posEnemy);

			// ���n����
			CScene::GetField()->LandPosition(posEnemy, moveEnemy);

			// �X�e�[�W�͈͊O�̕␳
			collision::InCirclePillar(posEnemy, posBarrier, status.fRadius, LIMIT_RADIUS);

			// �L���m�������̐ݒ�
			if (SetRotationCannon(posLook, posEnemy, rotEnemy))
			{ // ���ˉ\��Ԃ̏ꍇ

				// �U��
				Attack(posLook, posEnemy, fLookRadius);
			}
		}
	}

	// �ʒu�𔽉f
	SetPosition(posEnemy);

	// �ʒu�ړ��ʂ𔽉f
	SetMovePosition(moveEnemy);

	// �����𔽉f
	SetRotation(rotEnemy);
}
#endif

#endif
