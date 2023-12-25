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
	const float	JUMP_REV	= 0.16f;	// �ʏ��Ԏ��̋󒆂̈ړ��ʂ̌����W��
	const float	LAND_REV	= 0.16f;	// �ʏ��Ԏ��̒n��̈ړ��ʂ̌����W��

	const float	SPAWN_ADD_ALPHA	= 0.03f;	// �X�|�[����Ԏ��̓����x�̉��Z��
}

//************************************************************
//	�ÓI�����o�ϐ��錾
//************************************************************
const char *CPlayer::mc_apModelFile[] =	// ���f���萔
{
	"data\\MODEL\\PLAYER\\1225_pl_002.x",	// �v���C���[
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
	m_state			= STATE_NONE;	// ���
	m_nCounterState	= 0;			// ��ԊǗ��J�E���^�[
	m_bJump			= false;		// �W�����v��
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
}

//============================================================
//	�X�V����
//============================================================
void CPlayer::Update(void)
{
	// �ߋ��ʒu�̍X�V
	UpdateOldPosition();

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
	// �ϐ���錾
	D3DXVECTOR3 posPlayer = GetVec3Position();	// �v���C���[�ʒu
	D3DXVECTOR3 rotPlayer = GetVec3Rotation();	// �v���C���[����

#if 0

	if (IsDeath() != true)
	{ // ���S�t���O�������Ă��Ȃ��ꍇ

		if (m_state == STATE_NORMAL)
		{ // �ʏ��Ԃ̏ꍇ

			// �J�E���^�[��������
			m_nCounterState = 0;

			// �ҋ@���[�V������ݒ�
			SetMotion(MOTION_IDOL);

			// �����p�[�e�B�N���𐶐�
			CParticle3D::Create(CParticle3D::TYPE_SMALL_EXPLOSION, D3DXVECTOR3(posPlayer.x, posPlayer.y + basic::HEIGHT * 0.5f, posPlayer.z));

			// �T�E���h�̍Đ�
			GET_MANAGER->GetSound()->Play(CSound::LABEL_SE_HIT);	// �q�b�g��
		}
	}

#endif
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
	SetAlpha(1.0f);

	// �v���C���[�̕`����ĊJ
	SetEnableDraw(true);

	// �Ǐ]�J�����̖ڕW�ʒu�̐ݒ�
	GET_MANAGER->GetCamera()->SetDestFollow();

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

	// �ړ�����
	UpdateMove();

	// �W�����v�̍X�V
	UpdateJump();

	// �d�͂̍X�V
	UpdateGravity();

	// �ʒu�X�V
	UpdatePosition(posPlayer);

	// ���n����
	UpdateLanding(posPlayer);

	// �����X�V
	UpdateRotation(rotPlayer);

	// �X�e�[�W�͈͊O�̕␳
	pStage->LimitPosition(posPlayer, RADIUS);

	// �L��Y�Ƃ̔���
	if (pStage->CollisionKillY(posPlayer))
	{ // �L��Y��艺�̈ʒu�ɂ���ꍇ

		// TODO�F�����ɗ�������
	}

	// �ʒu�𔽉f
	SetVec3Position(posPlayer);

	// �����𔽉f
	SetVec3Rotation(rotPlayer);
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

	//�L�[�{�[�h�̈ړ�����
	if (GET_INPUTKEY->IsPress(DIK_W) == true)
	{
		if (GET_INPUTKEY->IsPress(DIK_A) == true)
		{
			// �ړ��ʂ��X�V
			m_move.x += sinf(pCamera->GetVec3Rotation().y + D3DX_PI * -0.25f) * 1.0f;
			m_move.z += cosf(pCamera->GetVec3Rotation().y + D3DX_PI * -0.25f) * 1.0f;
		}
		else if (GET_INPUTKEY->IsPress(DIK_D) == true)
		{
			// �ړ��ʂ��X�V
			m_move.x += sinf(pCamera->GetVec3Rotation().y + D3DX_PI * 0.25f) * 1.0f;
			m_move.z += cosf(pCamera->GetVec3Rotation().y + D3DX_PI * 0.25f) * 1.0f;
		}
		else
		{
			// �ړ��ʂ��X�V
			m_move.x += sinf(pCamera->GetVec3Rotation().y + D3DX_PI * 0.0f) * 1.0f;
			m_move.z += cosf(pCamera->GetVec3Rotation().y + D3DX_PI * 0.0f) * 1.0f;
		}
	}
	else if (GET_INPUTKEY->IsPress(DIK_S) == true)
	{
		if (GET_INPUTKEY->IsPress(DIK_A) == true)
		{
			// �ړ��ʂ��X�V
			m_move.x += sinf(pCamera->GetVec3Rotation().y + D3DX_PI * -0.75f) * 1.0f;
			m_move.z += cosf(pCamera->GetVec3Rotation().y + D3DX_PI * -0.75f) * 1.0f;
		}
		else if (GET_INPUTKEY->IsPress(DIK_D) == true)
		{
			// �ړ��ʂ��X�V
			m_move.x += sinf(pCamera->GetVec3Rotation().y + D3DX_PI * 0.75f) * 1.0f;
			m_move.z += cosf(pCamera->GetVec3Rotation().y + D3DX_PI * 0.75f) * 1.0f;
		}
		else
		{
			// �ړ��ʂ��X�V
			m_move.x += sinf(pCamera->GetVec3Rotation().y + D3DX_PI * 1.0f) * 1.0f;
			m_move.z += cosf(pCamera->GetVec3Rotation().y + D3DX_PI * 1.0f) * 1.0f;
		}
	}
	else if (GET_INPUTKEY->IsPress(DIK_A) == true)
	{
		// �ړ��ʂ��X�V
		m_move.x += sinf(pCamera->GetVec3Rotation().y + D3DX_PI * -0.5f) * 1.0f;
		m_move.z += cosf(pCamera->GetVec3Rotation().y + D3DX_PI * -0.5f) * 1.0f;

	}
	else if (GET_INPUTKEY->IsPress(DIK_D) == true)
	{
		// �ړ��ʂ��X�V
		m_move.x += sinf(pCamera->GetVec3Rotation().y + D3DX_PI * 0.5f) * 1.0f;
		m_move.z += cosf(pCamera->GetVec3Rotation().y + D3DX_PI * 0.5f) * 1.0f;
	}

	if (GET_INPUTKEY->IsPress(DIK_W) == false && GET_INPUTKEY->IsPress(DIK_A) == false && GET_INPUTKEY->IsPress(DIK_S) == false && GET_INPUTKEY->IsPress(DIK_D) == false)
	{
		// �ϐ���錾
		D3DXVECTOR3 vecStickL = D3DXVECTOR3((float)GET_INPUTPAD->GetPressLStickX(), (float)GET_INPUTPAD->GetPressLStickY(), 0.0f);	// �X�e�B�b�N�e���̓|����
		float fStickL = sqrtf(vecStickL.x * vecStickL.x + vecStickL.y * vecStickL.y) * 0.5f;	// �X�e�B�b�N�̓|����
		if (0.01f < fStickL)
		{ // �f�b�h�]�[���ȏ�̏ꍇ

			// �ړ��ʂ��X�V
			m_move.x += sinf(GET_INPUTPAD->GetPressLStickRot()) * MOVE;
			m_move.z += cosf(GET_INPUTPAD->GetPressLStickRot()) * MOVE;
		}
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
		}
	}
}

//============================================================
//	�̍X�V����
//============================================================
void CPlayer::UpdateAttack(void)
{
	if (GET_INPUTKEY->IsTrigger(DIK_SPACE) ||
		GET_INPUTPAD->IsTrigger(GET_INPUTPAD->KEY_A))
	{ // ���삪�s��ꂽ�ꍇ

	}
}

//============================================================
//	�̍X�V����
//============================================================
void CPlayer::UpdateBullet(void)
{
	if (GET_INPUTKEY->IsTrigger(DIK_SPACE) ||
		GET_INPUTPAD->IsTrigger(GET_INPUTPAD->KEY_A))
	{ // ���삪�s��ꂽ�ꍇ

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

	// �n�ʁE�����ʒu�̒��n����
	if (CScene::GetStage()->LandFieldPosition(rPos, m_move)
	||  CScene::GetStage()->LandLimitPosition(rPos, m_move, 0.0f))
	{ // �v���C���[�����n���Ă����ꍇ

		// ���n���Ă����Ԃɂ���
		bLand = true;

		// �W�����v���Ă��Ȃ���Ԃɂ���
		m_bJump = false;
	}

	// ���n�󋵂�Ԃ�
	return bLand;
}

//============================================================
//	�ʒu�̍X�V����
//============================================================
void CPlayer::UpdatePosition(D3DXVECTOR3& rPos)
{
	// �ړ��ʂ����Z
	rPos += m_move;

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
