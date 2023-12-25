//============================================================
//
//	�f�[�^�ۑ��}�l�[�W���[�w�b�_�[ [retentionManager.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _RETENTION_MANAGER_H_
#define _RETENTION_MANAGER_H_

//************************************************************
//	�N���X��`
//************************************************************
// �f�[�^�ۑ��}�l�[�W���[�N���X
class CRetentionManager
{
public:
	// �R���X�g���N�^
	CRetentionManager();

	// �f�X�g���N�^
	~CRetentionManager();

	// �����o�֐�
	HRESULT Init(void);	// ������
	void Uninit(void);	// �I��

	// �ÓI�����o�֐�
	static CRetentionManager *Create(void);	// ����
	static HRESULT Release(CRetentionManager *&prRetentionManager);	// �j��

	// �����o�֐�
	void SetScore(const int nScore);	// �X�R�A�ݒ�
	int GetScore(void) const;			// �X�R�A�擾

private:
	// �����o�ϐ�
	int m_nScore;	// �X�R�A
};

#endif	// _RETENTION_MANAGER_H_
