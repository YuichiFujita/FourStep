//============================================================
//
//	�G���� [enemy.cpp]
//	Author�F���c�E��
//
//============================================================
#if 1
//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "enemy.h"
#include "manager.h"
#include "renderer.h"
#include "enemyNormal.h"
#include "scene.h"
#include "player.h"
#include "collision.h"

//************************************************************
//	�萔�錾
//************************************************************
namespace
{
	const int	PRIORITY = 3;		// �G�̗D�揇��
	const int	DAMAGE_FRAME = 12;	// �_���[�W��ԃt���[����

	const float	GRAVITY		= 1.0f;		// �d��
	const float	REV_MOVE	= 0.16f;	// �ʏ��Ԏ��̋󒆂̈ړ��ʂ̌����W��

	const float	SPAWN_ADD_ALPHA = 0.0075f;	// �X�|�[�����̓����x�̉��Z��
	const float	DEATH_SUB_ALPHA = 0.05f;	// ���S���̓����x�̌��Z��
}

//************************************************************
//	�ÓI�����o�ϐ��錾
//************************************************************
CEnemy::SStatusInfo CEnemy::m_aStatusInfo[CEnemy::TYPE_MAX] =	// �X�e�[�^�X���
{
	// �ʏ�G�̃X�e�[�^�X���
	{
		40.0f,	// ���a
		40.0f,	// �c��
		2.0f,	// �O�i�̈ړ���
		2.0f,	// �W�����v��
		100.0f,	// �U���͈�
		0.5f,	// ���F�̕␳�W��
	},

	// �W�����v�G�̃X�e�[�^�X���
	{
		0.0f,	// ���a
		0.0f,	// �c��
		0.0f,	// �O�i�̈ړ���
		0.0f,	// �W�����v��
		0.0f,	// �U���͈�
		0.0f,	// ���F�̕␳�W��
	},

	// �e���˓G�̃X�e�[�^�X���
	{
		0.0f,	// ���a
		0.0f,	// �c��
		0.0f,	// �O�i�̈ړ���
		0.0f,	// �W�����v��
		0.0f,	// �U���͈�
		0.0f,	// ���F�̕␳�W��
	},
};
int CEnemy::m_nNumAll = 0;	// �G�̑���

//************************************************************
//	�q�N���X [CEnemy] �̃����o�֐�
//************************************************************
//============================================================
//	�R���X�g���N�^
//============================================================
CEnemy::CEnemy(const EType type) : CObjectModel(CObject::LABEL_ENEMY, PRIORITY), m_type(type), m_status(m_aStatusInfo[type])
{
	// �����o�ϐ����N���A
	m_oldPos	= VEC3_ZERO;	// �ߋ��ʒu
	m_movePos	= VEC3_ZERO;	// �ʒu�ړ���
	m_moveRot	= VEC3_ZERO;	// �����ύX��
	m_state		= STATE_SPAWN;	// ���
	m_nCounterState = 0;		// ��ԊǗ��J�E���^�[

	// �G�̑��������Z
	m_nNumAll++;
}

//============================================================
//	�f�X�g���N�^
//============================================================
CEnemy::~CEnemy()
{
	// �G�̑��������Z
	m_nNumAll--;
}

//============================================================
//	����������
//============================================================
HRESULT CEnemy::Init(void)
{
	// �����o�ϐ���������
	m_oldPos	= VEC3_ZERO;	// �ߋ��ʒu
	m_movePos	= VEC3_ZERO;	// �ʒu�ړ���
	m_moveRot	= VEC3_ZERO;	// �����ύX��
	m_state		= STATE_SPAWN;	// ���
	m_nCounterState = 0;		// ��ԊǗ��J�E���^�[

	// �I�u�W�F�N�g���f���̏�����
	if (FAILED(CObjectModel::Init()))
	{ // �������Ɏ��s�����ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	// ������Ԃ�
	return S_OK;
}

//============================================================
//	�I������
//============================================================
void CEnemy::Uninit(void)
{
	// �I�u�W�F�N�g���f���̏I��
	CObjectModel::Uninit();
}

//============================================================
//	�X�V����
//============================================================
void CEnemy::Update(void)
{
	// �I�u�W�F�N�g���f���̍X�V
	CObjectModel::Update();
}

//============================================================
//	�`�揈��
//============================================================
void CEnemy::Draw(void)
{
	// �I�u�W�F�N�g���f���̕`��
	CObjectModel::Draw();
}

//============================================================
//	�m�b�N�o�b�N�q�b�g����
//============================================================
void CEnemy::HitKnockBack(const int nDmg, const D3DXVECTOR3& vec)
{
#if 0
	// �ϐ���錾
	D3DXVECTOR3 pos = GetVec3Position();	// �G�ʒu
	D3DXVECTOR3 vecKnock = vec;				// �m�b�N�o�b�N�x�N�g��

	if (IsDeath() != true && m_state == STATE_NORMAL)
	{ // ���S�t���O�������Ă��Ȃ����A�ʏ��Ԃ̏ꍇ

		// ���x�������Z
		m_pBubble->AddLevel(nDmg);

		if (m_pBubble->GetLevel() < m_status.nLife)
		{ // �����Ă���ꍇ

			// �m�b�N�o�b�N�ړ��ʂ�ݒ�
			vecKnock.y = 0.0f;									// �c�x�N�g����������
			D3DXVec3Normalize(&vecKnock, &vecKnock);			// �x�N�g���𐳋K��
			m_moveKnock = vecKnock * m_status.fKnockBackSide;	// �m�b�N�o�b�N���ړ��ʂ��v�Z
			m_moveKnock.y = m_status.fKnockBackUp;				// �m�b�N�o�b�N�c�ړ��ʂ���

			// �J�E���^�[��������
			m_nCounterState = 0;
			m_nCounterBubble = 0;

			// ��Ԃ�ݒ�
			m_state = STATE_DAMAGE;	// �_���[�W���
		}
		else
		{ // ����ł���ꍇ

			// ���[�V�������X�V���Ȃ���Ԃɂ���
			SetEnableMotionUpdate(false);

			// �����\�����폜
			m_pWay->Delete();

			// ��Ԃ�ݒ�
			m_state = STATE_DEATH;	// ���S���

			// �T�E���h�̍Đ�
			CManager::GetSound()->Play(CSound::LABEL_SE_FLY);	// ���V��
		}

		// �p�[�e�B�N��3D�I�u�W�F�N�g�𐶐�
		CParticle3D::Create(CParticle3D::TYPE_BUBBLE_EXPLOSION, pos);
	}
#endif
}

//============================================================
//	��������
//============================================================
CEnemy *CEnemy::Create(const EType type, const D3DXVECTOR3& rPos, const D3DXVECTOR3& rRot)
{
	// �|�C���^��錾
	CEnemy *pEnemy = nullptr;	// �G�����p

	if (pEnemy == nullptr)
	{ // �g�p����Ă��Ȃ��ꍇ

		// �������m��
		switch (type)
		{ // ��ނ��Ƃ̏���
		case TYPE_NORMAL:

			// �ʏ�G�𐶐�
			pEnemy = new CEnemyNormal(type);

			break;

		default:	// ��O����
			assert(false);
			break;
		}
	}
	else { assert(false); return nullptr; }	// �g�p��

	if (pEnemy != nullptr)
	{ // �g�p����Ă���ꍇ
		
		// �G�̏�����
		if (FAILED(pEnemy->Init()))
		{ // �������Ɏ��s�����ꍇ

			// �������J��
			delete pEnemy;
			pEnemy = NULL;

			// ���s��Ԃ�
			return NULL;
		}

		// �ʒu��ݒ�
		pEnemy->SetVec3Position(rPos);

		// ������ݒ�
		pEnemy->SetVec3Rotation(rRot);

		// �m�ۂ����A�h���X��Ԃ�
		return pEnemy;
	}
	else { assert(false); return NULL; }	// �m�ێ��s
}

//============================================================
//	�����_����������
//============================================================
void CEnemy::RandomSpawn
(
	const int nNum,		// ������
	const EType type	// ���
)
{
	// �ϐ���錾
	D3DXVECTOR3 pos, rot;	// �ʒu�E�����ݒ�p

#if 0
	for (int nCntGrow = 0; nCntGrow < nNum; nCntGrow++)
	{ // ���������J��Ԃ�

		// �^�[�Q�b�g�ʒu���擾
		posTarget = pTarget->GetPosition();

		// �����ʒu��ݒ�
		pos.x = (float)(rand() % ((int)LIMIT_RADIUS * 2) - (int)LIMIT_RADIUS + 1);
		pos.y = m_aStatusInfo[type].fSpawnHeight;
		pos.z = (float)(rand() % ((int)LIMIT_RADIUS * 2) - (int)LIMIT_RADIUS + 1);

		// ����������ݒ�
		rot = VEC3_ZERO;	// ������������
		rot.y = atan2f(pos.x - posTarget.x, pos.z - posTarget.z);	// �^�[�Q�b�g�̕�������������

		// �ʒu��␳
		pos.x = sinf(rot.y) * (LIMIT_RADIUS - m_aStatusInfo[type].fRadius);
		pos.z = cosf(rot.y) * (LIMIT_RADIUS - m_aStatusInfo[type].fRadius);

		// �G�I�u�W�F�N�g�̐���
		CEnemy::Create(type, pos, rot);
	}
#endif
}

//============================================================
//	�X�e�[�^�X���擾����
//============================================================
CEnemy::SStatusInfo CEnemy::GetStatusInfo(const int nType)
{
	// �����̎�ނ̃X�e�[�^�X����Ԃ�
	return m_aStatusInfo[nType];
}

//============================================================
//	�����擾����
//============================================================
int CEnemy::GetNumAll(void)
{
	// ���݂̓G�̑�����Ԃ�
	return m_nNumAll;
}

//============================================================
//	�ߋ��ʒu�̍X�V����
//============================================================
void CEnemy::UpdateOldPosition(void)
{
	// �ߋ��ʒu���X�V
	m_oldPos = GetVec3Position();
}

//============================================================
//	�ʒu�ړ��ʂ̐ݒ菈��
//============================================================
void CEnemy::SetMovePosition(const D3DXVECTOR3& rMove)
{
	// �����̈ʒu�ړ��ʂ�ݒ�
	m_movePos = rMove;
}

//============================================================
//	�����ύX�ʂ̐ݒ菈��
//============================================================
void CEnemy::SetMoveRotation(const D3DXVECTOR3& rMove)
{
	// �����̌�����ݒ�
	m_moveRot = rMove;

	// �����̐��K��
	useful::Vec3NormalizeRot(m_moveRot);
}

//============================================================
//	��Ԃ̐ݒ菈��
//============================================================
void CEnemy::SetState(const int nState)
{
	// �����̏�Ԃ�ݒ�
	m_state = (EState)nState;
}

//============================================================
//	�}�g���b�N�X�擾����
//============================================================
D3DXMATRIX CEnemy::GetMtxWorld(void) const
{
	// �ϐ���錾
	D3DXMATRIX mtxRot, mtxTrans, mtxWorld;		// �v�Z�p�}�g���b�N�X
	D3DXVECTOR3 posEnemy = GetVec3Position();	// �G�ʒu
	D3DXVECTOR3 rotEnemy = GetVec3Rotation();	// �G����

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&mtxWorld);

	// �����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, rotEnemy.y, rotEnemy.x, rotEnemy.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, posEnemy.x, posEnemy.y, posEnemy.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTrans);

	// ���[���h�}�g���b�N�X��Ԃ�
	return mtxWorld;
}

//============================================================
//	�ߋ��ʒu�擾����
//============================================================
D3DXVECTOR3 CEnemy::GetOldPosition(void) const
{
	// �ߋ��ʒu��Ԃ�
	return m_oldPos;
}

//============================================================
//	�ʒu�ړ��ʎ擾����
//============================================================
D3DXVECTOR3 CEnemy::GetMovePosition(void) const
{
	// �ʒu�ړ��ʂ�Ԃ�
	return m_movePos;
}

//============================================================
//	�����ύX�ʎ擾����
//============================================================
D3DXVECTOR3 CEnemy::GetMoveRotation(void) const
{
	// �����ύX�ʂ�Ԃ�
	return m_moveRot;
}

//============================================================
//	��Ԏ擾����
//============================================================
int CEnemy::GetState(void) const
{
	// ��Ԃ�Ԃ�
	return m_state;
}

//============================================================
//	��ގ擾����
//============================================================
int CEnemy::GetType(void) const
{
	// ��ނ�Ԃ�
	return m_type;
}

//============================================================
//	���a�擾����
//============================================================
float CEnemy::GetRadius(void) const
{
	// ���a��Ԃ�
	return m_status.fRadius;
}

//============================================================
//	�c���擾����
//============================================================
float CEnemy::GetHeight(void) const
{
	// �c����Ԃ�
	return m_status.fHeight;
}

//============================================================
//	�X�e�[�^�X���擾����
//============================================================
CEnemy::SStatusInfo CEnemy::GetStatusInfo(void) const
{
	// �X�e�[�^�X����Ԃ�
	return m_status;
}

//============================================================
//	�X�|�[����Ԏ��̍X�V
//============================================================
void CEnemy::UpdateSpawn(void)
{
	// �t�F�[�h�A�E�g�̍X�V
	if (UpdateFadeOut(SPAWN_ADD_ALPHA))
	{ // �s�����ɂȂ����ꍇ

		// �ʏ��Ԃɂ���
		m_state = STATE_NORMAL;
	}
}

//============================================================
//	������я�Ԏ��̍X�V
//============================================================
void CEnemy::UpdateKnock(void)
{
	if (m_nCounterState < DAMAGE_FRAME)
	{ // �J�E���^�[�����l��菬�����ꍇ

		// �J�E���^�[�����Z
		m_nCounterState++;

		// �}�e���A����S�ݒ�
		SetAllMaterial(material::Red());	// ��
	}
	else
	{ // �J�E���^�[�����l�ȏ�̏ꍇ

		// �J�E���^�[��������
		m_nCounterState = 0;

		// �}�e���A���Đݒ�
		ResetMaterial();

		// �ʏ��Ԃɂ���
		m_state = STATE_NORMAL;
	}
}

//============================================================
//	���S��Ԏ��̍X�V
//============================================================
bool CEnemy::UpdateDeath(void)
{
	// �t�F�[�h�C���̍X�V
	if (UpdateFadeIn(DEATH_SUB_ALPHA))
	{ // �����ɂȂ����ꍇ

		// �G���I��
		Uninit();

		// ���S��Ԃ�
		return true;
	}

	// �񎀖S��Ԃ�
	return false;
}

//============================================================
//	�G����̍X�V����
//============================================================
void CEnemy::UpdateAction(void)
{
	// �|�C���^��錾
	CPlayer *pPlayer = CScene::GetPlayer();	// �v���C���[���
	assert(pPlayer != nullptr);

	// �ϐ���錾
	SStatusInfo  status = GetStatusInfo();				// �G�X�e�[�^�X
	D3DXVECTOR3 posEnemy = GetVec3Position();			// �G�ʒu
	D3DXVECTOR3 moveEnemy = GetMovePosition();			// �G�ړ���
	D3DXVECTOR3 rotEnemy = GetVec3Rotation();			// �G����
	D3DXVECTOR3 posLook = pPlayer->GetVec3Position();	// �v���C���[�ʒu
	float fPlayerRadius = pPlayer->GetRadius();			// �v���C���[���a

	// �ߋ��ʒu�̍X�V
	UpdateOldPosition();

	// ���F�Ώۂ̍U������
	if (!collision::Circle2D(posLook, posEnemy, fPlayerRadius, status.fAttackRadius))
	{ // �G�̍U���͈͊O�̏ꍇ

		// �Ώۂ̕�������������
		Look(posLook, posEnemy, &rotEnemy);

		// �Ώۂ̕����Ɉړ� (�O�i)
		moveEnemy.x -= sinf(rotEnemy.y) * status.fForwardMove;
		moveEnemy.z -= cosf(rotEnemy.y) * status.fForwardMove;

		// �d�͂����Z
		//moveEnemy.y -= GRAVITY;

		// �ړ��ʂ����Z
		posEnemy += moveEnemy;

		// �ړ��ʂ�����
		moveEnemy.x += (0.0f - moveEnemy.x) * REV_MOVE;
		moveEnemy.z += (0.0f - moveEnemy.z) * REV_MOVE;
	}
	else
	{ // �G�̍U���͈͓��̏ꍇ


	}

	// �ʒu�𔽉f
	SetVec3Position(posEnemy);

	// �ʒu�ړ��ʂ𔽉f
	SetMovePosition(moveEnemy);

	// �����𔽉f
	SetVec3Rotation(rotEnemy);
}

//============================================================
//	�Ώێ��F����
//============================================================
void CEnemy::Look(const D3DXVECTOR3& rPosLook, const D3DXVECTOR3& rPosEnemy, D3DXVECTOR3 *pRotEnemy)
{
	// �ϐ���錾
	float fDestRot = 0.0f;	// �ڕW����
	float fDiffRot = 0.0f;	// ����

	// ���F�Ώۂ̕�������
	fDestRot = atan2f(rPosEnemy.x - rPosLook.x, rPosEnemy.z - rPosLook.z);	// �ڕW����

	// �������������߂�
	fDiffRot = fDestRot - pRotEnemy->y;
	useful::NormalizeRot(fDiffRot);		// ���������̐��K��

	// �����̍X�V
	pRotEnemy->y += fDiffRot * m_status.fLookRev;
	useful::NormalizeRot(pRotEnemy->y);	// �����̐��K��
}

//============================================================
//	�t�F�[�h�A�E�g��Ԏ��̍X�V����
//============================================================
bool CEnemy::UpdateFadeOut(const float fAdd)
{
	// �ϐ���錾
	bool bAlpha = false;		// ������
	float fAlpha = GetAlpha();	// �����x

	// �v���C���[���g�̕`����ĊJ
	CObject::SetEnableDraw(true);

	// �����x���グ��
	fAlpha += fAdd;

	if (fAlpha >= GetMaxAlpha())
	{ // �����x���オ��؂����ꍇ

		// �����x��␳
		fAlpha = GetMaxAlpha();

		// �s�����ɂȂ�؂�����Ԃɂ���
		bAlpha = true;
	}

	// �����x��ݒ�
	SetAlpha(fAlpha);

	// �����󋵂�Ԃ�
	return bAlpha;
}

//============================================================
//	�t�F�[�h�C����Ԏ��̍X�V����
//============================================================
bool CEnemy::UpdateFadeIn(const float fSub)
{
	// �ϐ���錾
	bool bAlpha = false;		// ������
	float fAlpha = GetAlpha();	// �����x

	// �����x��������
	fAlpha -= fSub;

	if (fAlpha <= 0.0f)
	{ // �����x��������؂����ꍇ

		// �����x��␳
		fAlpha = 0.0f;

		// �����ɂȂ�؂�����Ԃɂ���
		bAlpha = true;

		// �v���C���[���g�̕`����~
		CObject::SetEnableDraw(false);
	}

	// �����x��ݒ�
	SetAlpha(fAlpha);

	// �����󋵂�Ԃ�
	return bAlpha;
}
#endif
