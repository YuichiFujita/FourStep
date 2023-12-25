//============================================================
//
//	�v���C���[�w�b�_�[ [player.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _PLAYER_H_
#define _PLAYER_H_

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "objectModel.h"

//************************************************************
//	�N���X��`
//************************************************************
// �v���C���[�N���X
class CPlayer : public CObjectModel
{
public:
	// ���f����
	enum EModel
	{
		MODEL_PLAYER = 0,	// �v���C���[
		MODEL_MAX			// ���̗񋓌^�̑���
	};

	// ��ԗ�
	enum EState
	{
		STATE_NONE = 0,	// �������Ȃ����
		STATE_SPAWN,	// �X�|�[�����
		STATE_NORMAL,	// �ʏ���
		STATE_KNOCK,	// ������я��
		STATE_DEATH,	// ���S���
		STATE_MAX		// ���̗񋓌^�̑���
	};

	// ����
	enum EAxis
	{
		AXIS_X = 0,	// X��
		AXIS_Y,		// Y��
		AXIS_Z,		// Z��
		AXIS_MAX	// ���̗񋓌^�̑���
	};

	// �R���X�g���N�^
	CPlayer();

	// �f�X�g���N�^
	~CPlayer() override;

	// �I�[�o�[���C�h�֐�
	HRESULT Init(void) override;	// ������
	void Uninit(void) override;		// �I��
	void Update(void) override;		// �X�V
	void Draw(void) override;		// �`��
	void HitKnockBack(const int nDmg, const D3DXVECTOR3 &vecKnock);	// �m�b�N�o�b�N�q�b�g

	void SetState(const int nState) override;	// ��Ԑݒ�
	int GetState(void) const override;			// ��Ԏ擾
	float GetRadius(void) const override;		// ���a�擾
	float GetHeight(void) const override;		// �c���擾

	void SetEnableUpdate(const bool bUpdate) override;	// �X�V�󋵐ݒ�
	void SetEnableDraw(const bool bDraw) override;		// �`��󋵐ݒ�
	D3DXMATRIX GetMtxWorld(void) const override;		// �}�g���b�N�X�擾

	// �ÓI�����o�֐�
	static CPlayer *Create(void);	// ����

	// �����o�֐�
	void SetSpawn(void);	// �o���ݒ�

private:
	// �����o�֐�
	void UpdateSpawn(void);		// �X�|�[����Ԏ��̍X�V
	void UpdateNormal(void);	// �ʏ��Ԏ��̍X�V
	void UpdateKnock(void);		// ������я�Ԏ��̍X�V
	void UpdateDeath(void);		// ���S��Ԏ��̍X�V

	void UpdateOldPosition(void);			// �ߋ��ʒu�̍X�V
	void UpdateMove(void);					// �ړ��ʁE�ڕW�����̍X�V
	void UpdateJump(void);					// �W�����v�̍X�V
	void UpdateAttack(void);				// �U���̍X�V
	void UpdateBullet(void);				// �ˌ��̍X�V
	void UpdateGravity(void);				// �d�͂̍X�V
	bool UpdateLanding(D3DXVECTOR3& rPos);	// ���n�󋵂̍X�V
	void UpdateRotation(D3DXVECTOR3& rRot);	// �����̍X�V
	bool UpdateFadeOut(const float fAdd);	// �t�F�[�h�A�E�g��Ԏ��̍X�V
	bool UpdateFadeIn(const float fSub);	// �t�F�[�h�C����Ԏ��̍X�V

	bool ResponseSingleGround(const EAxis axis, D3DXVECTOR3 &rPos);	// �n�ՂƂ̈ꎲ���Ƃ̓����蔻��
	bool CollisionGround(D3DXVECTOR3 &rPos);	// �n�ՂƂ̓����蔻��
	void CollisionEnemy(D3DXVECTOR3 &rPos);		// �G�Ƃ̓����蔻��

	// �ÓI�����o�ϐ�
	static const char *mc_apModelFile[];	// ���f���萔

	// �����o�ϐ�
	D3DXVECTOR3	m_oldPos;		// �ߋ��ʒu
	D3DXVECTOR3	m_move;			// �ړ���
	D3DXVECTOR3	m_destRot;		// �ڕW����
	float	m_RSrickRot;	// �E�X�e�B�b�N�̌���
	EState	m_state;			// ���
	int		m_nCounterState;	// ��ԊǗ��J�E���^�[
	bool	m_bJump;			// �W�����v��
};

#endif	// _PLAYER_H_
