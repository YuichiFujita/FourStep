//============================================================
//
//	���U���g�}�l�[�W���[�w�b�_�[ [resultManager.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _RESULTMANAGER_H_
#define _RESULTMANAGER_H_

//************************************************************
//	�O���錾
//************************************************************
class CObject2D;	// �I�u�W�F�N�g2D�N���X
class CMultiValue;	// �}���`�����N���X

//************************************************************
//	�N���X��`
//************************************************************
// ���U���g�}�l�[�W���[�N���X
class CResultManager
{
public:
	// �e�N�X�`����
	enum ETexture
	{
		TEXTURE_SCORE = 0,	// �X�R�A�e�N�X�`��
		TEXTURE_CONTINUE,	// �R���e�j���[�\���e�N�X�`��
		TEXTURE_YES,		// YES�e�N�X�`��
		TEXTURE_NO,			// NO�e�N�X�`��
		TEXTURE_MAX			// ���̗񋓌^�̑���
	};

	// ��ԗ�
	enum EState
	{
		STATE_NONE = 0,			// �������Ȃ����
		STATE_FADEIN,			// �t�F�[�h�C�����
		STATE_RESULT,			// �X�R�A�\�����
		STATE_CONTINUE_WAIT,	// �R���e�j���[�\���ҋ@���
		STATE_CONTINUE,			// �R���e�j���[�\�����
		STATE_WAIT,				// �J�ڑҋ@���
		STATE_MAX				// ���̗񋓌^�̑���
	};

	// �I���
	enum ESelect
	{
		SELECT_YES = 0,	// YES
		SELECT_NO,		// NO
		SELECT_MAX		// ���̗񋓌^�̑���
	};

	// �R���X�g���N�^
	CResultManager();

	// �f�X�g���N�^
	~CResultManager();

	// �����o�֐�
	HRESULT Init(void);		// ������
	HRESULT Uninit(void);	// �I��
	void Update(void);		// �X�V

	// �ÓI�����o�֐�
	static CResultManager *Create(void);	// ����
	static HRESULT Release(CResultManager *&prResultManager);	// �j��

private:
	// �����o�֐�
	void UpdateFade(void);			// �t�F�[�h�C��
	void UpdateResult(void);		// ���U���g�\��
	void UpdateContinue(void);		// �R���e�j���[�\��
	void UpdateSelect(void);		// �I���X�V
	void UpdateTransition(void);	// �J�ڌ���
	void SkipStaging(void);			// ���o�X�L�b�v
	bool UpdateDrawWait(const int nWait);	// �\���ҋ@

	// �ÓI�����o�ϐ�
	static const char *mc_apTextureFile[];	// �e�N�X�`���萔

	// �����o�ϐ�
	CObject2D *m_apContinue[SELECT_MAX];	// �R���e�j���[�\���̏��
	CObject2D *m_pScoreTitle;	// �X�R�A�^�C�g���̏��
	CMultiValue *m_pScore;		// �X�R�A�̏��
	CObject2D *m_pContLogo;		// �R���e�j���[���S�̏��
	CObject2D *m_pFade;			// �t�F�[�h�̏��
	EState m_state;				// ���
	int m_nCounterState;		// ��ԊǗ��J�E���^�[
	int m_nSelect;				// ���݂̑I��
	int m_nOldSelect;			// �O��̑I��
	float m_fScale;				// �|���S���g�嗦
};

#endif	// _RESULTMANAGER_H_
