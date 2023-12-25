//============================================================
//
//	�G���� [enemy.cpp]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "enemy.h"
#include "manager.h"
#include "renderer.h"
#include "sound.h"
#include "enemyNormal.h"
#include "scene.h"
#include "sceneGame.h"
#include "score.h"
#include "stage.h"
#include "player.h"
#include "collision.h"
#include "effect3D.h"
#include "ground.h"
#include "map.h"
#include "gamemanager.h"

//************************************************************
//	�萔�錾
//************************************************************
namespace
{
	const int	PRIORITY = 3;		// �G�̗D�揇��
	const int	DAMAGE_FRAME = 12;	// �_���[�W��ԃt���[����

	const float	GRAVITY		= 1.0f;		// �d��
	const float	JUMP_REV	= 0.16f;	// �󒆂̈ړ��ʂ̌����W��
	const float	LAND_REV	= 0.16f;	// �n��̈ړ��ʂ̌����W��
	const float	KNOCK_REV	= 0.045f;	// ������я�Ԏ��̈ړ��ʂ̌����W��
	const float	KNOCK_UP	= 15.0f;	// �m�b�N�㏸��
	const float	KNOCK_SIDE	= 35.0f;	// �m�b�N���ړ���

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
		100.0f,	// ���a
		50.0f,	// ���a
		40.0f,	// �c��
		0.5f,	// �O�i�̈ړ���
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
	m_movePos	= D3DXVECTOR3(0.0f,100.0f,0.0f);	// �ʒu�ړ���
	m_moveRot	= VEC3_ZERO;	// �����ύX��
	m_AtkPos = VEC3_ZERO;
	m_state		= STATE_SPAWN;	// ���
	m_bJump		= false;		// �W�����v��
	m_bAttack = false;
	m_bAttackCounter = 0;
	m_nCounterState	= 0;		// ��ԊǗ��J�E���^�[

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
	m_bJump		= true;			// �W�����v��
	m_nCounterState	= 0;		// ��ԊǗ��J�E���^�[

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
void CEnemy::HitKnockBack(const int nDmg, const D3DXVECTOR3&vecKnock)
{
	if (IsDeath())
	{ // ���S�t���O�������Ă���ꍇ

		return;
	}

	if (m_state != STATE_NORMAL)
	{ // �ʏ��Ԃł͂Ȃ��ꍇ

		return;
	}

	// �ϐ���錾
	D3DXVECTOR3 posPlayer = GetVec3Position();	// �v���C���[�ʒu
	D3DXVECTOR3 rotPlayer = GetVec3Rotation();	// �v���C���[����

	// �J�E���^�[��������
	m_nCounterState = 0;

	// �m�b�N�o�b�N�ړ��ʂ�ݒ�
	m_movePos.x = KNOCK_SIDE * vecKnock.x;
	m_movePos.y = KNOCK_UP;
	m_movePos.z = KNOCK_SIDE * vecKnock.z;

	// �m�b�N�o�b�N�����Ɍ�����ݒ�
	rotPlayer.y = atan2f(vecKnock.x, vecKnock.z);	// ������ь������v�Z
	SetVec3Rotation(rotPlayer);	// ������ݒ�

	// �󒆏�Ԃɂ���
	m_bJump = true;

	// �m�b�N��Ԃ�ݒ�
	SetState(STATE_KNOCK);

	// �T�E���h�̍Đ�
	CManager::GetInstance()->GetSound()->Play(CSound::LABEL_SE_HIT);	// �q�b�g��
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
	// �ϐ���錾
	D3DXVECTOR3 posEnemy = GetVec3Position();	// �v���C���[�ʒu

	// �|�C���^��錾
	CStage *pStage = CScene::GetStage();	// �X�e�[�W���
	assert(pStage != nullptr);

	// �}�e���A����S�ݒ�
	SetAllMaterial(material::Red());	// ��

	// �d�͂�^����
	m_movePos.y -= GRAVITY;

	if (m_movePos.y < 0.0f)
	{
		// �ʏ��Ԃɂ���
		m_state = STATE_NORMAL;
	}

	// ���n����
	if (UpdateLanding(&posEnemy))
	{ // ���n�����ꍇ

	}

	// �X�e�[�W�͈͊O�̕␳
	pStage->LimitPosition(posEnemy, m_status.fRadius);

	// �L��Y�Ƃ̔���
	if (pStage->CollisionKillY(posEnemy))
	{ // �L��Y��艺�̈ʒu�ɂ���ꍇ

		// ���S��Ԃɂ���
		m_state = STATE_DEATH;

		// �}�e���A���Đݒ�
		ResetMaterial();
	}

	// �ʒu�𔽉f
	SetVec3Position(posEnemy);
}

//============================================================
//	���S��Ԏ��̍X�V
//============================================================
bool CEnemy::UpdateDeath(void)
{
	// �ϐ���錾
	D3DXVECTOR3 posEnemy = GetVec3Position();	// �G�ʒu

	// �ߋ��ʒu�̍X�V
	UpdateOldPosition();

	// �d�͂�^����
	m_movePos.y -= GRAVITY;

	// ���n�󋵂̍X�V
	UpdateLanding(&posEnemy);

	// �ʒu�𔽉f
	SetVec3Position(posEnemy);

	// �t�F�[�h�C���̍X�V
	if (UpdateFadeIn(DEATH_SUB_ALPHA))
	{ // �����ɂȂ����ꍇ

		// �G���I��
		Uninit();

		// �X�R�A���Z
		CSceneGame::GetScore()->Add(1);

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

	CStage *pStage = CScene::GetStage();	// �X�e�[�W���
	assert(pStage != nullptr);

	// �ϐ���錾
	SStatusInfo  status = GetStatusInfo();				// �G�X�e�[�^�X
	D3DXVECTOR3 posEnemy = GetVec3Position();			// �G�ʒu
	D3DXVECTOR3 rotEnemy = GetVec3Rotation();			// �G����
	D3DXVECTOR3 posLook = pPlayer->GetVec3Position();	// �v���C���[�ʒu
	float fPlayerRadius = pPlayer->GetRadius();			// �v���C���[���a

	// �}�e���A���Đݒ�
	ResetMaterial();

	// �ߋ��ʒu�̍X�V
	UpdateOldPosition();

	// �d�͂�^����
	m_movePos.y -= GRAVITY;

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

				if (pObjCheck->GetLabel() == CObject::LABEL_GROUND)
				{ // �I�u�W�F�N�g���x�����n�Ղł͂Ȃ��ꍇ

					D3DXVECTOR3 posBlock = pObjCheck->GetVec3Position();	// �G�ʒu
					CGround* pGround = (CGround*)pObjCheck;

					if (collision::Circle2D(GetVec3Position(), posBlock, 50.0f, 50.0f) == true)
					{
						pGround->DelColor(0.005f);
					}
				}

				// ���̃I�u�W�F�N�g�ւ̃|�C���^����
				pObjCheck = pObjectNext;
			}
		}
	}

	m_AtkPos.x = GetVec3Position().x + sinf(GetVec3Rotation().y) * -100.0f;
	m_AtkPos.y = 0.0f;
	m_AtkPos.z = GetVec3Position().z + cosf(GetVec3Rotation().y) * -100.0f;


	//CEffect3D::Create(m_AtkPos, 100.0f, CEffect3D::TYPE_NORMAL, 10);

	// ���F�Ώۂ̍U������
	if (pPlayer->GetState() != CPlayer::STATE_DEATH)
	{ // �v���C���[������ł��Ȃ��ꍇ
		if (m_bAttack == false)
		{
			if (!collision::Circle2D(posLook, posEnemy, fPlayerRadius, status.fAttackRadius))
			{ // �G�̍U���͈͊O�̏ꍇ

				// �Ώۂ̕�������������
				UpdateLook(posLook, posEnemy, &rotEnemy);

				// �Ώۂ̕����Ɉړ� (�O�i)
				m_movePos.x -= sinf(rotEnemy.y) * status.fForwardMove;
				m_movePos.z -= cosf(rotEnemy.y) * status.fForwardMove;
			}
			else
			{ // �G�̍U���͈͓��̏ꍇ

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

							if (pObjCheck->GetLabel() == CObject::LABEL_GROUND)
							{ // �I�u�W�F�N�g���x�����n�Ղł͂Ȃ��ꍇ

								D3DXVECTOR3 posBlock = pObjCheck->GetVec3Position();	// �G�ʒu
								CGround* pGround = (CGround*)pObjCheck;

								if (collision::Circle2D(m_AtkPos, posBlock, 100.0f, 50.0f) == true)
								{
									m_bAttack = true;
									m_bAttackCounter = 120;
									pGround->DelColor(0.3f);
								}
							}

							// ���̃I�u�W�F�N�g�ւ̃|�C���^����
							pObjCheck = pObjectNext;
						}
					}
				}
			}
		}
		else
		{
			if (m_bAttackCounter > 0)
			{
				m_bAttackCounter--;
			}
			else
			{
				m_bAttack = false;
			}
		}
	}

	// ���n�󋵂̍X�V
	UpdateLanding(&posEnemy);

	// �X�e�[�W�͈͊O�̕␳
	pStage->LimitPosition(posEnemy, m_status.fRadius);

	// �L��Y�Ƃ̔���
	if (pStage->CollisionKillY(posEnemy))
	{ // �L��Y��艺�̈ʒu�ɂ���ꍇ

		// ���S��Ԃɂ���
		m_state = STATE_DEATH;
	}

	// �ʒu�𔽉f
	SetVec3Position(posEnemy);

	// �����𔽉f
	SetVec3Rotation(rotEnemy);
}

//============================================================
//	�Ώێ��F����
//============================================================
void CEnemy::UpdateLook(const D3DXVECTOR3& rPosLook, const D3DXVECTOR3& rPosEnemy, D3DXVECTOR3 *pRotEnemy)
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
//	���n�󋵂̍X�V����
//============================================================
bool CEnemy::UpdateLanding(D3DXVECTOR3 *pPos)
{
	// �ϐ���錾
	bool bLand = false;	// ���n��

	// �W�����v���Ă����Ԃɂ���
	m_bJump = true;

	// �ʒu�̍X�V
	// �n�Ղ̓����蔻��E���n����
	if (CollisionGround(*pPos))
	{ // �n�Ղɒ��n���Ă����ꍇ

		// ���n���Ă����Ԃɂ���
		bLand = true;

		// �W�����v���Ă��Ȃ���Ԃɂ���
		m_bJump = false;
	}

	// ���n�󋵂�Ԃ�
	return bLand;
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

//============================================================
//	�n�ՂƂ̈ꎲ���Ƃ̓����蔻��
//============================================================
bool CEnemy::ResponseSingleGround(const EAxis axis, D3DXVECTOR3& rPos)
{
	// �ϐ���錾
	D3DXVECTOR3 sizeMinPlayer = D3DXVECTOR3(m_status.fFloorRadius, 0.0f,				m_status.fFloorRadius);	// �G�̍ŏ��傫��
	D3DXVECTOR3 sizeMaxPlayer = D3DXVECTOR3(m_status.fFloorRadius, m_status.fHeight, m_status.fFloorRadius);	// �G�̍ő�傫��
	bool bMin = false;	// �s�̕����̔����
	bool bMax = false;	// ���̕����̔����
	bool bHit = false;	// ���n�̔�����

	for (int nCntPri = 0; nCntPri < object::MAX_PRIO; nCntPri++)
	{ // �D�揇�ʂ̑������J��Ԃ�

		// �|�C���^��錾
		CObject *pObjectTop = CObject::GetTop(nCntPri);	// �擪�I�u�W�F�N�g

		if (pObjectTop != NULL)
		{ // �擪�����݂���ꍇ

			// �|�C���^��錾
			CObject *pObjCheck = pObjectTop;	// �I�u�W�F�N�g�m�F�p

			while (pObjCheck != NULL)
			{ // �I�u�W�F�N�g���g�p����Ă���ꍇ�J��Ԃ�

				// �ϐ���錾
				D3DXVECTOR3 posGround = VEC3_ZERO;		// �n�Ոʒu
				D3DXVECTOR3 rotGround = VEC3_ZERO;		// �n�Ռ���
				D3DXVECTOR3 sizeMinGround = VEC3_ZERO;	// �n�Սŏ��傫��
				D3DXVECTOR3 sizeMaxGround = VEC3_ZERO;	// �n�Սő�傫��

				// �|�C���^��錾
				CObject *pObjectNext = pObjCheck->GetNext();	// ���I�u�W�F�N�g

				if (pObjCheck->GetLabel() != CObject::LABEL_GROUND)
				{ // �I�u�W�F�N�g���x�����n�Ղł͂Ȃ��ꍇ

					// ���̃I�u�W�F�N�g�ւ̃|�C���^����
					pObjCheck = pObjectNext;

					// ���̌J��Ԃ��Ɉڍs
					continue;
				}

				// �n�Ղ̈ʒu��ݒ�
				posGround = pObjCheck->GetVec3Position();

				// �n�Ղ̌�����ݒ�
				rotGround = pObjCheck->GetVec3Rotation();

				// �n�Ղ̍ŏ��̑傫����ݒ�
				sizeMinGround = pObjCheck->GetVec3Sizing();
				sizeMinGround.y *= 2.0f;	// �c�̑傫����{�ɂ���

				// �n�Ղ̍ő�̑傫����ݒ�
				sizeMaxGround = pObjCheck->GetVec3Sizing();
				sizeMaxGround.y = 0.0f;		// �c�̑傫����������

				switch (axis)
				{ // ���莲���Ƃ̏���
				case AXIS_X:	// X��

					// X���̏Փ˔���
					collision::ResponseSingleX
					( // ����
						rPos,			// ����ʒu
						m_oldPos,		// ����ߋ��ʒu
						posGround,		// ����ڕW�ʒu
						sizeMaxPlayer,	// ����T�C�Y(�E�E��E��)
						sizeMinPlayer,	// ����T�C�Y(���E���E�O)
						sizeMaxGround,	// ����ڕW�T�C�Y(�E�E��E��)
						sizeMinGround,	// ����ڕW�T�C�Y(���E���E�O)
						&m_movePos		// �ړ���
					);

					break;

				case AXIS_Y:	// Y��

					// Y���̏Փ˔���
					collision::ResponseSingleY
					( // ����
						rPos,			// ����ʒu
						m_oldPos,		// ����ߋ��ʒu
						posGround,		// ����ڕW�ʒu
						sizeMaxPlayer,	// ����T�C�Y(�E�E��E��)
						sizeMinPlayer,	// ����T�C�Y(���E���E�O)
						sizeMaxGround,	// ����ڕW�T�C�Y(�E�E��E��)
						sizeMinGround,	// ����ڕW�T�C�Y(���E���E�O)
						&m_movePos,		// �ړ���
						true,			// X����
						true,			// Z����
						&bMin,			// ������̔���
						&bMax			// �ォ��̔���
					);

					if (bMax)
					{ // �ォ�瓖�����Ă����ꍇ

						// ���n���Ă���󋵂ɂ���
						bHit = true;
					}

					break;

				case AXIS_Z:	// Z��

					// Z���̏Փ˔���
					collision::ResponseSingleZ
					( // ����
						rPos,			// ����ʒu
						m_oldPos,		// ����ߋ��ʒu
						posGround,		// ����ڕW�ʒu
						sizeMaxPlayer,	// ����T�C�Y(�E�E��E��)
						sizeMinPlayer,	// ����T�C�Y(���E���E�O)
						sizeMaxGround,	// ����ڕW�T�C�Y(�E�E��E��)
						sizeMinGround,	// ����ڕW�T�C�Y(���E���E�O)
						&m_movePos		// �ړ���
					);

					break;

				default:	// ��O����
					assert(false);
					break;
				}

				// ���̃I�u�W�F�N�g�ւ̃|�C���^����
				pObjCheck = pObjectNext;
			}
		}
	}

	// �e���̔������Ԃ�
	return bHit;
}

//============================================================
//	�n�ՂƂ̓����蔻��
//============================================================
bool CEnemy::CollisionGround(D3DXVECTOR3& rPos)
{
	// �ϐ���錾
	bool bLand = false;	// ���n��

	// �ړ��ʂ����Z
	rPos.x += m_movePos.x;

	// X���̓����蔻��
	ResponseSingleGround(AXIS_X, rPos);

	// �ړ��ʂ����Z
	rPos.y += m_movePos.y;

	// Y���̓����蔻��
	bLand = ResponseSingleGround(AXIS_Y, rPos);

	// �ړ��ʂ����Z
	rPos.z += m_movePos.z;

	// Z���̓����蔻��
	ResponseSingleGround(AXIS_Z, rPos);

	if (m_state == STATE_KNOCK)
	{ // �m�b�N��Ԃ̏ꍇ

		m_movePos.x += (0.0f - m_movePos.x) * KNOCK_REV;
		m_movePos.z += (0.0f - m_movePos.z) * KNOCK_REV;
	}
	else
	{ // ����ȊO�̏�Ԃ̏ꍇ

		// �ړ��ʂ�����
		if (m_bJump)
		{ // �󒆂̏ꍇ

			m_movePos.x += (0.0f - m_movePos.x) * JUMP_REV;
			m_movePos.z += (0.0f - m_movePos.z) * JUMP_REV;
		}
		else
		{ // �n��̏ꍇ

			m_movePos.x += (0.0f - m_movePos.x) * LAND_REV;
			m_movePos.z += (0.0f - m_movePos.z) * LAND_REV;
		}
	}

	SetVec3Position(rPos);

	// ���n�󋵂�Ԃ�
	return bLand;
}
