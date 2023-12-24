//============================================================
//
//	���U���g��ʏ��� [sceneResult.cpp]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "sceneResult.h"
#include "manager.h"
#include "texture.h"
#include "sound.h"
#include "camera.h"
#include "resultManager.h"

//************************************************************
//	�ÓI�����o�ϐ��錾
//************************************************************
CResultManager *CSceneResult::m_pResultManager = nullptr;	// ���U���g�}�l�[�W���[

//************************************************************
//	�q�N���X [CSceneResult] �̃����o�֐�
//************************************************************
//============================================================
//	�R���X�g���N�^
//============================================================
CSceneResult::CSceneResult(const EMode mode) : CScene(mode)
{

}

//============================================================
//	�f�X�g���N�^
//============================================================
CSceneResult::~CSceneResult()
{

}

//============================================================
//	����������
//============================================================
HRESULT CSceneResult::Init(void)
{
	//--------------------------------------------------------
	//	���U���g�̏�����
	//--------------------------------------------------------
	// ���U���g�}�l�[�W���[�̐���
	m_pResultManager = CResultManager::Create();
	if (m_pResultManager == nullptr)
	{ // ��g�p���̏ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	// �V�[���̏�����
	CScene::Init();

	//--------------------------------------------------------
	//	�����ݒ�
	//--------------------------------------------------------
	// �J������ݒ�
	GET_MANAGER->GetCamera()->SetState(CCamera::STATE_ROTATE);	// �J��������]��Ԃɐݒ�
	GET_MANAGER->GetCamera()->SetDestRotate();	// �ڕW�ʒu��ݒ�

	// BGM�̍Đ�
	GET_MANAGER->GetSound()->Play(CSound::LABEL_BGM_GENERAL);

	// ������Ԃ�
	return S_OK;
}

//============================================================
//	�I������
//============================================================
HRESULT CSceneResult::Uninit(void)
{
	// ���U���g�}�l�[�W���[�̔j��
	if (FAILED(CResultManager::Release(m_pResultManager)))
	{ // �j���Ɏ��s�����ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	// �V�[���̏I��
	CScene::Uninit();

	// ������Ԃ�
	return S_OK;
}

//============================================================
//	�X�V����
//============================================================
void CSceneResult::Update(void)
{
	// �f�o�b�O�\��
	GET_MANAGER->GetDebugProc()->Print(CDebugProc::POINT_LEFT, "======================================\n");
	GET_MANAGER->GetDebugProc()->Print(CDebugProc::POINT_LEFT, "�@[�f�o�b�O���]\n");
	GET_MANAGER->GetDebugProc()->Print(CDebugProc::POINT_LEFT, "======================================\n");

	if (m_pResultManager != nullptr)
	{ // �g�p���̏ꍇ

		// ���U���g�}�l�[�W���[�̍X�V
		m_pResultManager->Update();
	}
	else { assert(false); }	// ��g�p��

	// �V�[���̍X�V
	CScene::Update();
}

//============================================================
//	�`�揈��
//============================================================
void CSceneResult::Draw(void)
{

}

//============================================================
//	���U���g�}�l�[�W���[�擾����
//============================================================
CResultManager *CSceneResult::GetResultManager(void)
{
	// ���U���g�}�l�[�W���[��Ԃ�
	return m_pResultManager;
}
