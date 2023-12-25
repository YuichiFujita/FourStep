//============================================================
//
//	�v���C���[���� [player.cpp]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "player.h"
#include "manager.h"
#include "sceneGame.h"
#include "gameManager.h"
#include "renderer.h"
#include "sound.h"
#include "camera.h"
#include "texture.h"
#include "collision.h"
#include "fade.h"
#include "stage.h"
#include "bullet.h"
#include "enemy.h"
#include "stick.h"
#include "ground.h"
#include "EffectModel.h"

//************************************************************
//	�萔�錾
//************************************************************
namespace
{
	const int PRIORITY = 3;	// �v���C���[�̗D�揇��

	const float	MOVE		= 2.8f;		// �ړ���
	const float	JUMP		= 21.0f;	// �W�����v�㏸��
	const float	GRAVITY		= 1.0f;		// �d��
	const float	RADIUS		= 20.0f;	// ���a
	const float	HEIGHT		= 100.0f;	// �c��
	const float	REV_ROTA	= 0.15f;	// �����ύX�̕␳�W��
	const float	ADD_MOVE	= 0.08f;	// ��A�N�V�������̑��x���Z��
	const float	JUMP_REV	= 0.16f;	// �󒆂̈ړ��ʂ̌����W��
	const float	LAND_REV	= 0.16f;	// �n��̈ړ��ʂ̌����W��
	const float	KNOCK_REV	= 0.08f;	// ������я�Ԏ��̈ړ��ʂ̌����W��
	const float	KNOCK_UP	= 15.0f;	// �m�b�N�㏸��
	const float	KNOCK_SIDE	= 35.0f;	// �m�b�N���ړ���
	const float	SPAWN_ADD_ALPHA	= 0.03f;	// �X�|�[����Ԏ��̓����x�̉��Z��
	const float	DEATH_SUB_ALPHA	= 0.05f;	// ���S���̓����x�̌��Z��
}

//************************************************************
//	�ÓI�����o�ϐ��錾
//************************************************************
const char *CPlayer::mc_apModelFile[] =	// ���f���萔
{
	"data\\MODEL\\PLAYER\\1225_pl_003.x",	// �v���C���[
};

//************************************************************
//	�q�N���X [CPlayer] �̃����o�֐�
//************************************************************
//============================================================
//	�R���X�g���N�^
//============================================================
CPlayer::CPlayer() : CObjectModel(CObject::LABEL_PLAYER, PRIORITY)
{
	// �����o�ϐ����N���A
	m_oldPos		= VEC3_ZERO;	// �ߋ��ʒu
	m_move			= VEC3_ZERO;	// �ړ���
	m_destRot		= VEC3_ZERO;	// �ڕW����
	m_RSrickRot		= 0.0f;
	m_state			= STATE_NONE;	// ���
	m_nCounterState	= 0;			// ��ԊǗ��J�E���^�[
	m_bJump			= false;		// �W�����v��
	m_bAttack = false;
	m_pAtkUI = nullptr;
	m_pShadow = nullptr;
}

//============================================================
//	�f�X�g���N�^
//============================================================
CPlayer::~CPlayer()
{

}

//============================================================
//	����������
//============================================================
HRESULT CPlayer::Init(void)
{
	// �����o�ϐ���������
	m_oldPos		= VEC3_ZERO;	// �ߋ��ʒu
	m_move			= VEC3_ZERO;	// �ړ���
	m_destRot		= VEC3_ZERO;	// �ڕW����
	m_state			= STATE_NONE;	// ���
	m_nCounterState	= 0;			// ��ԊǗ��J�E���^�[
	m_bJump			= true;			// �W�����v��

	// �I�u�W�F�N�g���f���̏�����
	if (FAILED(CObjectModel::Init()))
	{ // �������Ɏ��s�����ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	// ���f����Ǎ��E����
	BindModel(mc_apModelFile[MODEL_PLAYER]);

	if (m_pAtkUI == nullptr)
	{
		m_pAtkUI = CObjectModel::Create(VEC3_ZERO, VEC3_ZERO);
		m_pAtkUI->CObjectModel::SetLabel(LABEL_UI);
		m_pAtkUI->BindModel("data\\MODEL\\PLAYER\\sankakumodel.x");
	}

	if (m_pShadow == nullptr)
	{
		m_pShadow = CObjectModel::Create(VEC3_ZERO, VEC3_ZERO);
		m_pShadow->CObjectModel::SetLabel(LABEL_UI);
		m_pShadow->BindModel("data\\MODEL\\PLAYER\\player_shadow.x");
	}

	// ������Ԃ�
	return S_OK;
}

//============================================================
//	�I������
//============================================================
void CPlayer::Uninit(void)
{
	// �I�u�W�F�N�g���f���̏I��
	CObjectModel::Uninit();

	if (m_pAtkUI != nullptr)
	{
		m_pAtkUI->Uninit();
		m_pAtkUI = nullptr;
	}
}

//============================================================
//	�X�V����
//============================================================
void CPlayer::Update(void)
{
	// �ߋ��ʒu�̍X�V
	UpdateOldPosition();

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

	switch (m_state)
	{ // ��Ԃ��Ƃ̏���
	case STATE_NONE:
		break;

	case STATE_SPAWN:

		// �X�|�[����Ԏ��̍X�V
		UpdateSpawn();

		break;

	case STATE_NORMAL:

		// �ʏ��Ԃ̍X�V
		UpdateNormal();

		break;

	case STATE_KNOCK:

		// ������я�Ԏ��̍X�V
		UpdateKnock();

		break;

	case STATE_DEATH:

		// ���S��Ԏ��̍X�V
		UpdateDeath();

		break;

	default:
		assert(false);
		break;
	}

	// �I�u�W�F�N�g���f���̍X�V
	CObjectModel::Update();
}

//============================================================
//	�`�揈��
//============================================================
void CPlayer::Draw(void)
{
	// �I�u�W�F�N�g���f���̕`��
	CObjectModel::Draw();
}

//============================================================
//	�m�b�N�o�b�N�q�b�g����
//============================================================
void CPlayer::HitKnockBack(const int nDmg, const D3DXVECTOR3 &vecKnock)
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
	m_move.x = KNOCK_SIDE * vecKnock.x;
	m_move.y = KNOCK_UP;
	m_move.z = KNOCK_SIDE * vecKnock.z;

	// �m�b�N�o�b�N�����Ɍ�����ݒ�
	rotPlayer.y = atan2f(vecKnock.x, vecKnock.z);	// ������ь������v�Z
	m_destRot.y = rotPlayer.y;	// �ڕW������ݒ�
	SetVec3Rotation(rotPlayer);	// ������ݒ�

	// �󒆏�Ԃɂ���
	m_bJump = true;

	// �m�b�N��Ԃ�ݒ�
	SetState(STATE_KNOCK);

	if (m_pShadow != nullptr)
	{
		m_pShadow->SetEnableDraw(false);
	}
	if (m_pAtkUI != nullptr)
	{
		m_pAtkUI->SetEnableDraw(false);
	}


	// �T�E���h�̍Đ�
	CManager::GetInstance()->GetSound()->Play(CSound::LABEL_SE_HIT);	// �q�b�g��
}

//============================================================
//	��Ԃ̐ݒ菈��
//============================================================
void CPlayer::SetState(const int nState)
{
	if (nState > NONE_IDX && nState < STATE_MAX)
	{ // �͈͓��̏ꍇ

		// �����̏�Ԃ�ݒ�
		m_state = (EState)nState;
	}
	else { assert(false); }
}

//============================================================
//	��Ԏ擾����
//============================================================
int CPlayer::GetState(void) const
{
	// ��Ԃ�Ԃ�
	return m_state;
}

//============================================================
//	���a�擾����
//============================================================
float CPlayer::GetRadius(void) const
{
	// ���a��Ԃ�
	return RADIUS;
}

//============================================================
//	�c���擾����
//============================================================
float CPlayer::GetHeight(void) const
{
	// �c����Ԃ�
	return HEIGHT;
}

//============================================================
//	�X�V�󋵂̐ݒ菈��
//============================================================
void CPlayer::SetEnableUpdate(const bool bUpdate)
{
	// �����̍X�V�󋵂�ݒ�
	CObject::SetEnableUpdate(bUpdate);	// ���g
}

//============================================================
//	�`��󋵂̐ݒ菈��
//============================================================
void CPlayer::SetEnableDraw(const bool bDraw)
{
	// �����̕`��󋵂�ݒ�
	CObject::SetEnableDraw(bDraw);	// ���g
}

//============================================================
//	�}�g���b�N�X�擾����
//============================================================
D3DXMATRIX CPlayer::GetMtxWorld(void) const
{
	// �ϐ���錾
	D3DXMATRIX  mtxRot, mtxTrans, mtxWorld;		// �v�Z�p�}�g���b�N�X
	D3DXVECTOR3 posPlayer = GetVec3Position();	// �v���C���[�ʒu
	D3DXVECTOR3 rotPlayer = GetVec3Rotation();	// �v���C���[����

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&mtxWorld);

	// �����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, rotPlayer.y, rotPlayer.x, rotPlayer.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, posPlayer.x, posPlayer.y, posPlayer.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTrans);

	// ���[���h�}�g���b�N�X��Ԃ�
	return mtxWorld;
}

//============================================================
//	��������
//============================================================
CPlayer *CPlayer::Create(void)
{
	// �|�C���^��錾
	CPlayer *pPlayer = nullptr;	// �v���C���[�����p

	if (pPlayer == nullptr)
	{ // �g�p����Ă��Ȃ��ꍇ

		// �������m��
		pPlayer = new CPlayer;	// �v���C���[
	}
	else { assert(false); return nullptr; }	// �g�p��

	if (pPlayer != nullptr)
	{ // �g�p����Ă���ꍇ

		// �v���C���[�̏�����
		if (FAILED(pPlayer->Init()))
		{ // �������Ɏ��s�����ꍇ

			// �������J��
			delete pPlayer;
			pPlayer = nullptr;

			// ���s��Ԃ�
			return nullptr;
		}
	}

	// �m�ۂ����A�h���X��Ԃ�
	return pPlayer;
}

//============================================================
//	�o���̐ݒ菈��
//============================================================
void CPlayer::SetSpawn(void)
{
	// �ϐ���錾
	D3DXVECTOR3 set = VEC3_ZERO;	// �����ݒ�p

	// ����������
	SetState(STATE_SPAWN);	// �X�|�[����Ԃ̐ݒ�

	// �J�E���^�[��������
	m_nCounterState = 0;	// ��ԊǗ��J�E���^�[

	// �ʒu��ݒ�
	SetVec3Position(set);

	// ������ݒ�
	SetVec3Rotation(set);
	m_destRot = set;

	// �ړ��ʂ�������
	m_move = VEC3_ZERO;

	// �}�e���A�����Đݒ�
	ResetMaterial();

	// �����x�𓧖��ɍĐݒ�
	SetAlpha(0.0f);

	// �v���C���[�̕`����ĊJ
	SetEnableDraw(true);

	//// �Ǐ]�J�����̖ڕW�ʒu�̐ݒ�
	//GET_MANAGER->GetCamera()->SetDestFollow();

	// �T�E���h�̍Đ�
	GET_MANAGER->GetSound()->Play(CSound::LABEL_SE_SPAWN);	// ������
}

//============================================================
//	�X�|�[����Ԏ��̍X�V����
//============================================================
void CPlayer::UpdateSpawn(void)
{
	// �t�F�[�h�A�E�g��Ԏ��̍X�V
	if (UpdateFadeOut(SPAWN_ADD_ALPHA))
	{ // �s�����ɂȂ�؂����ꍇ

		// ��Ԃ�ݒ�
		SetState(STATE_NORMAL);
	}
}

//============================================================
//	�ʏ��Ԏ��̍X�V����
//============================================================
void CPlayer::UpdateNormal(void)
{
	// �ϐ���錾
	D3DXVECTOR3 posPlayer = GetVec3Position();	// �v���C���[�ʒu
	D3DXVECTOR3 rotPlayer = GetVec3Rotation();	// �v���C���[����

	// �|�C���^��錾
	CStage *pStage = CScene::GetStage();	// �X�e�[�W���
	if (pStage == nullptr)
	{ // �X�e�[�W���g�p����Ă��Ȃ��ꍇ

		// �����𔲂���
		assert(false);
		return;
	}


	// �}�e���A���Đݒ�
	ResetMaterial();

	// �ϐ���錾
	D3DXVECTOR3 vecStickR = D3DXVECTOR3((float)GET_INPUTPAD->GetPressRStickX(), (float)GET_INPUTPAD->GetPressRStickY(), 0.0f);	// �X�e�B�b�N�e���̓|����
	float fStickR = sqrtf(vecStickR.x * vecStickR.x + vecStickR.y * vecStickR.y) * 0.5f;	// �X�e�B�b�N�̓|����
	if (0.8f < fStickR)
	{ // �f�b�h�]�[���ȏ�̏ꍇ

		m_RSrickRot = GET_INPUTPAD->GetPressRStickRot();

	}

	// �ړ�����
	UpdateMove();

	// �W�����v�̍X�V
	UpdateJump();

	// �U���̍X�V
	UpdateAttack();

	// �ˌ��̍X�V
	UpdateBullet();

	// �d�͂̍X�V
	UpdateGravity();

	// ���n����
	UpdateLanding(posPlayer);

	// �G�Ƃ̓����蔻��
	CollisionEnemy(posPlayer);

	// �����X�V
	UpdateRotation(rotPlayer);

	// �X�e�[�W�͈͊O�̕␳
	pStage->LimitPosition(posPlayer, RADIUS);

	// �L��Y�Ƃ̔���
	if (pStage->CollisionKillY(posPlayer))
	{ // �L��Y��艺�̈ʒu�ɂ���ꍇ

		// ���S��Ԃɂ���
		m_state = STATE_DEATH;

		// �T�E���h�̍Đ�
		GET_MANAGER->GetSound()->Play(CSound::LABEL_SE_FALL);	// ������
	}

	if (m_bAttack == false)
	{
		if (m_pAtkUI != nullptr)
		{
			m_pAtkUI->SetVec3Position(GetVec3Position());
			m_pAtkUI->SetVec3Rotation(D3DXVECTOR3(0.0f, m_RSrickRot + D3DX_PI * 0.5f, 0.0f));
		}
	}

	if (m_pShadow != nullptr)
	{
		m_pShadow->SetVec3Position(D3DXVECTOR3(GetVec3Position().x, 0.0f, GetVec3Position().z));
	}

	if (posPlayer.y < 0.0f)
	{
		if (m_pShadow != nullptr)
		{
			m_pShadow->SetEnableDraw(false);
		}
		if (m_pAtkUI != nullptr)
		{
			m_pAtkUI->SetEnableDraw(false);
		}
	}

	// �ʒu�𔽉f
	SetVec3Position(posPlayer);

	// �����𔽉f
	SetVec3Rotation(rotPlayer);
}

//============================================================
//	������я�Ԏ��̍X�V����
//============================================================
void CPlayer::UpdateKnock(void)
{
	// �ϐ���錾
	D3DXVECTOR3 posPlayer = GetVec3Position();	// �v���C���[�ʒu
	D3DXVECTOR3 rotPlayer = GetVec3Rotation();	// �v���C���[����

	// �|�C���^��錾
	CStage *pStage = CScene::GetStage();	// �X�e�[�W���
	assert(pStage != nullptr);

	// �}�e���A����S�ݒ�
	SetAllMaterial(material::Red());	// ��

	// �d�͂̍X�V
	UpdateGravity();

	// ���n����
	if (UpdateLanding(posPlayer))
	{ // ���n�����ꍇ

		// �ʏ��Ԃɂ���
		m_state = STATE_NORMAL;
	}

	// �����X�V
	UpdateRotation(rotPlayer);

	// �X�e�[�W�͈͊O�̕␳
	pStage->LimitPosition(posPlayer, RADIUS);

	// �L��Y�Ƃ̔���
	if (pStage->CollisionKillY(posPlayer))
	{ // �L��Y��艺�̈ʒu�ɂ���ꍇ

		// ���S��Ԃɂ���
		m_state = STATE_DEATH;

		// �}�e���A���Đݒ�
		ResetMaterial();

		// �T�E���h�̍Đ�
		GET_MANAGER->GetSound()->Play(CSound::LABEL_SE_FALL);	// ������
	}

	// �ʒu�𔽉f
	SetVec3Position(posPlayer);

	// �����𔽉f
	SetVec3Rotation(rotPlayer);
}

//============================================================
//	���S��Ԏ��̍X�V����
//============================================================
void CPlayer::UpdateDeath(void)
{
	// �ϐ���錾
	D3DXVECTOR3 posPlayer = GetVec3Position();	// �G�ʒu

	// �ߋ��ʒu�̍X�V
	UpdateOldPosition();

	// �d�͂�^����
	m_move.y -= GRAVITY;

	// ���n�󋵂̍X�V
	UpdateLanding(posPlayer);

	// �ʒu�𔽉f
	SetVec3Position(posPlayer);

	// �t�F�[�h�C���̍X�V
	UpdateFadeIn(DEATH_SUB_ALPHA);
}

//============================================================
//	�ߋ��ʒu�̍X�V����
//============================================================
void CPlayer::UpdateOldPosition(void)
{
	// �ߋ��ʒu���X�V
	m_oldPos = GetVec3Position();
}

//============================================================
//	�ړ��ʁE�ڕW�����̍X�V����
//============================================================
void CPlayer::UpdateMove(void)
{
	CCamera* pCamera = GET_MANAGER->GetCamera();


	// �ϐ���錾
	D3DXVECTOR3 vecStickL = D3DXVECTOR3((float)GET_INPUTPAD->GetPressLStickX(), (float)GET_INPUTPAD->GetPressLStickY(), 0.0f);	// �X�e�B�b�N�e���̓|����
	float fStickL = sqrtf(vecStickL.x * vecStickL.x + vecStickL.y * vecStickL.y) * 0.5f;	// �X�e�B�b�N�̓|����
	if (0.01f < fStickL)
	{ // �f�b�h�]�[���ȏ�̏ꍇ

		// �ړ��ʂ��X�V
		m_move.x += sinf(pCamera->GetVec3Rotation().y + GET_INPUTPAD->GetPressLStickRot() + D3DX_PI * 0.5f) * MOVE;
		m_move.z += cosf(pCamera->GetVec3Rotation().y + GET_INPUTPAD->GetPressLStickRot() + D3DX_PI * 0.5f) * MOVE;
	}

	// �ڕW������ݒ�
	m_destRot.y = atan2f(-m_move.x, -m_move.z);
}

//============================================================
//	�W�����v�̍X�V����
//============================================================
void CPlayer::UpdateJump(void)
{
	if (!m_bJump)
	{ // �W�����v���Ă��Ȃ��ꍇ

		if (GET_INPUTKEY->IsTrigger(DIK_SPACE) ||
			GET_INPUTPAD->IsTrigger(GET_INPUTPAD->KEY_A))
		{ // �W�����v���삪�s��ꂽ�ꍇ

			// �W�����v�t���O��ON�ɂ���
			m_bJump = true;

			// ��ړ��ʂ����Z
			m_move.y += JUMP;

			// �T�E���h�̍Đ�
			GET_MANAGER->GetSound()->Play(CSound::LABEL_SE_FLY);	// ������
		}
	}
}

//============================================================
//	�̍X�V����
//============================================================
void CPlayer::UpdateAttack(void)
{
	// �ϐ���錾
	D3DXVECTOR3 vecStickR = D3DXVECTOR3((float)GET_INPUTPAD->GetPressRStickX(), (float)GET_INPUTPAD->GetPressRStickY(), 0.0f);	// �X�e�B�b�N�e���̓|����
	float fStickR = sqrtf(vecStickR.x * vecStickR.x + vecStickR.y * vecStickR.y) * 0.5f;	// �X�e�B�b�N�̓|����
	if (0.8f < fStickR)
	{ // �f�b�h�]�[���ȏ�̏ꍇ

		m_RSrickRot = GET_INPUTPAD->GetPressRStickRot();

	}

	if (m_bAttack == false)
	{
		if (GET_INPUTKEY->IsTrigger(DIK_Y) ||
			GET_INPUTPAD->IsTrigger(GET_INPUTPAD->KEY_L1))
		{ // ���삪�s��ꂽ�ꍇ
			CStick* pStick = CStick::Create();
			pStick->SetVec3Rotation(D3DXVECTOR3(0.0f, m_RSrickRot, 0.0f));
			pStick->SetVec3Position(GetVec3Position());
			m_bAttack = true;

			// �T�E���h�̍Đ�
			GET_MANAGER->GetSound()->Play(CSound::LABEL_SE_SLASH);	// ������
		}

		if (m_pShadow != nullptr)
		{
			m_pShadow->SetEnableDraw(true);
		}

		if (m_pAtkUI != nullptr)
		{
			m_pAtkUI->SetEnableDraw(true);
			m_pAtkUI->SetVec3Position(GetVec3Position());
			m_pAtkUI->SetVec3Rotation(D3DXVECTOR3(0.0f, m_RSrickRot + D3DX_PI * 0.5f, 0.0f));
		}
	}
	else
	{
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

					if (pObjCheck->GetLabel() == CObject::LABEL_ENEMY)
					{ // �I�u�W�F�N�g���x�����n�Ղł͂Ȃ��ꍇ

						D3DXVECTOR3 posEnemy = pObjCheck->GetVec3Position();	// �G�ʒu

						if (collision::Sector(GetVec3Position(), posEnemy, m_RSrickRot + D3DX_PI * -0.5f, 200.0f, D3DX_PI) == true)
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
						}
					}

					// ���̃I�u�W�F�N�g�ւ̃|�C���^����
					pObjCheck = pObjectNext;
				}
			}
		}
		if (m_pAtkUI != nullptr)
		{
			m_pAtkUI->SetEnableDraw(false);
		}
	}
}

//============================================================
//	�̍X�V����
//============================================================
void CPlayer::UpdateBullet(void)
{
	if (GET_INPUTKEY->IsTrigger(DIK_B) ||
		GET_INPUTPAD->IsTrigger(GET_INPUTPAD->KEY_R1))
	{ // ���삪�s��ꂽ�ꍇ

		CBullet* pBullet = CBullet::Create(true);
		pBullet->SetVec3Position(GetVec3Position());
		pBullet->SetMove(D3DXVECTOR3(
			-cosf(m_RSrickRot) * 25.0f,
			0.0f,
			sinf(m_RSrickRot) * 25.0f
		));

		// �T�E���h�̍Đ�
		GET_MANAGER->GetSound()->Play(CSound::LABEL_SE_SHOT);	// ������
	}
}

//============================================================
//	�d�͂̍X�V����
//============================================================
void CPlayer::UpdateGravity(void)
{
	// �d�͂����Z
	m_move.y -= GRAVITY;
}

//============================================================
//	���n�󋵂̍X�V����
//============================================================
bool CPlayer::UpdateLanding(D3DXVECTOR3& rPos)
{
	// �ϐ���錾
	bool bLand = false;	// ���n��

	// �W�����v���Ă����Ԃɂ���
	m_bJump = true;

	// �ʒu�̍X�V
	// �n�Ղ̓����蔻��E���n����
	if (CollisionGround(rPos))
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
//	�����̍X�V����
//============================================================
void CPlayer::UpdateRotation(D3DXVECTOR3& rRot)
{
	// �ϐ���錾
	float fDiffRot = 0.0f;	// ��������

	// �ڕW�����̐��K��
	useful::NormalizeRot(m_destRot.y);

	// �ڕW�����܂ł̍������v�Z
	fDiffRot = m_destRot.y - rRot.y;

	// ���������̐��K��
	useful::NormalizeRot(fDiffRot);

	// �����̍X�V
	rRot.y += fDiffRot * REV_ROTA;

	// �����̐��K��
	useful::NormalizeRot(rRot.y);
}

//============================================================
//	�t�F�[�h�A�E�g��Ԏ��̍X�V����
//============================================================
bool CPlayer::UpdateFadeOut(const float fAdd)
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
bool CPlayer::UpdateFadeIn(const float fSub)
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
bool CPlayer::ResponseSingleGround(const EAxis axis, D3DXVECTOR3& rPos)
{
	// �ϐ���錾
	D3DXVECTOR3 sizeMinPlayer = D3DXVECTOR3(RADIUS, 0.0f, RADIUS);		// �v���C���[�ŏ��傫��
	D3DXVECTOR3 sizeMaxPlayer = D3DXVECTOR3(RADIUS, HEIGHT, RADIUS);	// �v���C���[�ő�傫��
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
						&m_move			// �ړ���
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
						&m_move,		// �ړ���
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
						&m_move			// �ړ���
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
bool CPlayer::CollisionGround(D3DXVECTOR3& rPos)
{
	// �ϐ���錾
	bool bLand = false;	// ���n��

	// �ړ��ʂ����Z
	rPos.x += m_move.x;

	// X���̓����蔻��
	ResponseSingleGround(AXIS_X, rPos);

	// �ړ��ʂ����Z
	rPos.y += m_move.y;

	// Y���̓����蔻��
	bLand = ResponseSingleGround(AXIS_Y, rPos);

	// �ړ��ʂ����Z
	rPos.z += m_move.z;

	// Z���̓����蔻��
	ResponseSingleGround(AXIS_Z, rPos);

	if (m_state == STATE_KNOCK)
	{ // �m�b�N��Ԃ̏ꍇ

		m_move.x += (0.0f - m_move.x) * KNOCK_REV;
		m_move.z += (0.0f - m_move.z) * KNOCK_REV;
	}
	else
	{ // ����ȊO�̏�Ԃ̏ꍇ

		// �ړ��ʂ�����
		if (m_bJump)
		{ // �󒆂̏ꍇ

			m_move.x += (0.0f - m_move.x) * JUMP_REV;
			m_move.z += (0.0f - m_move.z) * JUMP_REV;
		}
		else
		{ // �n��̏ꍇ

			m_move.x += (0.0f - m_move.x) * LAND_REV;
			m_move.z += (0.0f - m_move.z) * LAND_REV;
		}
	}

	// ���n�󋵂�Ԃ�
	return bLand;
}

//============================================================
//	�G�Ƃ̓����蔻��
//============================================================
void CPlayer::CollisionEnemy(D3DXVECTOR3 &rPos)
{
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
				D3DXVECTOR3 posEnemy = VEC3_ZERO;	// �G�ʒu

				// �|�C���^��錾
				CObject *pObjectNext = pObjCheck->GetNext();	// ���I�u�W�F�N�g

				if (pObjCheck->GetLabel() != CObject::LABEL_ENEMY)
				{ // �I�u�W�F�N�g���x�����n�Ղł͂Ȃ��ꍇ

					// ���̃I�u�W�F�N�g�ւ̃|�C���^����
					pObjCheck = pObjectNext;

					// ���̌J��Ԃ��Ɉڍs
					continue;
				}

				if (pObjCheck->GetState() != CEnemy::STATE_NORMAL)
				{ // ��Ԃ��ʏ�ł͂Ȃ��ꍇ

					// ���̃I�u�W�F�N�g�ւ̃|�C���^����
					pObjCheck = pObjectNext;

					// ���̌J��Ԃ��Ɉڍs
					continue;
				}

				// �n�Ղ̈ʒu��ݒ�
				posEnemy = pObjCheck->GetVec3Position();

				// �~���̏Փ˔���
				bool bHit = collision::CirclePillar
				( // ����
					rPos,					// ����ʒu
					posEnemy,				// ����ڕW�ʒu
					RADIUS,					// ���蔼�a
					pObjCheck->GetRadius()	// ����ڕW���a
				);
				if (bHit)
				{ // �������Ă����ꍇ

					D3DXVECTOR3 vecKnock = rPos - posEnemy;		// �m�b�N�o�b�N�x�N�g��
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
						pModel->SetVec3Position(GetVec3Position());
						pModel->SetMove(move);
						pModel->SetVec3Scaling(D3DXVECTOR3(0.4f, 0.4f, 0.4f));
					}

					// �v���C���[�̃q�b�g����
					HitKnockBack(0, vecKnock);

					// �֐��𔲂���
					return;
				}

				// ���̃I�u�W�F�N�g�ւ̃|�C���^����
				pObjCheck = pObjectNext;
			}
		}
	}
}
