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
#ifndef _ENEMY_NORMAL_H_
#define _ENEMY_NORMAL_H_

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "enemy.h"

//************************************************************
//	�N���X��`
//************************************************************
// �ʏ�G�N���X
class CEnemyNormal : public CEnemy
{
public:
	// ��ޗ�
	enum EModel
	{
		MODEL_NORMAL = 0,	// �ʏ�
		MODEL_MAX			// ���̗񋓌^�̑���
	};

	// �R���X�g���N�^
	explicit CEnemyNormal(const EType type);

	// �f�X�g���N�^
	~CEnemyNormal() override;

	// �I�[�o�[���C�h�֐�
	HRESULT Init(void) override;	// ������
	void Uninit(void) override;		// �I��
	void Update(void) override;		// �X�V
	void Draw(void) override;		// �`��

private:
	// �ÓI�����o�ϐ�
	static const char *mc_apModelFile[];	// ���f���萔

	// �����o�ϐ�

};

#endif	// _ENEMY_H_
#endif