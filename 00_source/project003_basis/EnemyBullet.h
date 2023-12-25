//============================================================
//
//	�ʏ�G�w�b�_�[ [enemyNormal.h]
//	Author�F���c�E��
//
//============================================================
#if 1
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _ENEMY_BULLET_H_
#define _ENEMY_BULLET_H_

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "enemy.h"

//************************************************************
//	�N���X��`
//************************************************************
// �ʏ�G�N���X
class CEnemyBullet : public CEnemy
{
public:
	// ��ޗ�
	enum EModel
	{
		MODEL_NORMAL = 0,	// �ʏ�
		MODEL_MAX			// ���̗񋓌^�̑���
	};

	// �R���X�g���N�^
	explicit CEnemyBullet(const EType type);

	// �f�X�g���N�^
	~CEnemyBullet() override;

	// �I�[�o�[���C�h�֐�
	HRESULT Init(void) override;	// ������
	void Uninit(void) override;		// �I��
	void Update(void) override;		// �X�V
	void Draw(void) override;		// �`��

private:
	// �ÓI�����o�ϐ�
	static const char* mc_apModelFile[];	// ���f���萔

	// �����o�ϐ�
	int m_nCntBullet;
};

#endif	// _ENEMY_H_
#endif
