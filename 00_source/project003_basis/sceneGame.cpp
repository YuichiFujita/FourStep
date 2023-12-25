//============================================================
//
//	�Q�[����ʏ��� [sceneGame.cpp]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "sceneGame.h"
#include "manager.h"
#include "sound.h"
#include "camera.h"

#include "gameManager.h"
#include "stage.h"
#include "score.h"
#include "pause.h"
#include "player.h"
#include "enemy.h"

//************************************************************
//	�}�N����`
//************************************************************


//************************************************************
//	�ÓI�����o�ϐ��錾
//************************************************************
CGameManager	*CSceneGame::m_pGameManager  = nullptr;	// �Q�[���}�l�[�W���[
CScore	*CSceneGame::m_pScore	= nullptr;	// �^�C�}�[�}�l�[�W���[
CPause	*CSceneGame::m_pPause	= nullptr;	// �|�[�Y

bool CSceneGame::m_bControlCamera = false;	// �J�����̑����
bool CSceneGame::m_bDrawUI = true;			// UI�̕`���
bool CSceneGame::m_bDrawPause = true;		// �|�[�Y�̕`���

//************************************************************
//	�q�N���X [CSceneGame] �̃����o�֐�
//************************************************************
//============================================================
//	�R���X�g���N�^
//============================================================
CSceneGame::CSceneGame(const EMode mode) : CScene(mode)
{

}

//============================================================
//	�f�X�g���N�^
//============================================================
CSceneGame::~CSceneGame()
{

}

//============================================================
//	����������
//============================================================
HRESULT CSceneGame::Init(void)
{
	//--------------------------------------------------------
	//	��������
	//--------------------------------------------------------
	// �X�R�A�̐���
	m_pScore = CScore::Create(D3DXVECTOR3(790.0f, 430.0f, 0.0f), VEC3_ONE, D3DXVECTOR3(140.0f, 0.0f, 0.0f));
	if (m_pScore == nullptr)
	{ // ��g�p���̏ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	// �V�[���̏�����
	CScene::Init();		// �X�e�[�W�E�v���C���[�̐���

	// �Q�[���}�l�[�W���[�̐���
	m_pGameManager = CGameManager::Create();
	if (m_pGameManager == nullptr)
	{ // ��g�p���̏ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	// �|�[�Y�̐���
	m_pPause = CPause::Create();
	if (m_pPause == nullptr)
	{ // ��g�p���̏ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	//--------------------------------------------------------
	//	�����ݒ�
	//--------------------------------------------------------
	// �J������ݒ�
	GET_MANAGER->GetCamera()->SetState(CCamera::STATE_UPCAMERA);	// �J������Ǐ]��Ԃɐݒ�

	// �v���C���[���o��
	CScene::GetPlayer()->SetSpawn();
	CScene::GetPlayer()->SetEnableDraw(false);	// �`���OFF�ɂ���

	// UI�̕`��󋵂�ݒ�
	SetEnableDrawUI(m_bDrawUI);

	// �|�[�Y�̕`��󋵂�ݒ�
	SetEnableDrawPause(m_bDrawPause);

	// BGM�̍Đ�
	GET_MANAGER->GetSound()->Play(CSound::LABEL_BGM_GAME);

	// ������Ԃ�
	return S_OK;
}

//============================================================
//	�I������
//============================================================
HRESULT CSceneGame::Uninit(void)
{
	// �Q�[���}�l�[�W���[�̔j��
	if (FAILED(CGameManager::Release(m_pGameManager)))
	{ // �j���Ɏ��s�����ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	// �|�[�Y�̔j��
	if (FAILED(CPause::Release(m_pPause)))
	{ // �j���Ɏ��s�����ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	if (m_pScore != nullptr)
	{
		m_pScore->Uninit();
	}

	// �V�[���̏I��
	CScene::Uninit();

	// ������Ԃ�
	return S_OK;
}

//============================================================
//	�X�V����
//============================================================
void CSceneGame::Update(void)
{
#if _DEBUG

	if (GET_INPUTKEY->IsTrigger(DIK_F2))
	{
		// �G�f�B�b�g�󋵂𔽓]
		//CGameManager::GetEditStage()->SetEnableEdit((!CGameManager::GetEditStage()->IsEdit()) ? true : false);
	}
	if (GET_INPUTKEY->IsTrigger(DIK_F3))
	{
		// UI�̕`��󋵂𔽓]
		SetEnableDrawUI((!m_bDrawUI) ? true : false);
	}
	else if (GET_INPUTKEY->IsTrigger(DIK_F4))
	{
		// �|�[�Y�̕`��󋵂𔽓]
		SetEnableDrawPause((!m_bDrawPause) ? true : false);
	}
	else if (GET_INPUTKEY->IsTrigger(DIK_F5))
	{
		// �J�����̑���󋵂𔽓]
		SetEnableControlCamera((!m_bControlCamera) ? true : false);
	}
	else if (GET_INPUTKEY->IsTrigger(DIK_F6))
	{
		// �v���C���[�̏o����ݒ�
		CScene::GetPlayer()->SetSpawn();
	}
	else if (GET_INPUTKEY->IsTrigger(DIK_F7))
	{
		// TODO�F��ŏ����G�l�~�[����
		CEnemy::Create(CEnemy::TYPE_NORMAL, VEC3_ZERO, VEC3_ZERO);
	}
	else if (GET_INPUTKEY->IsPress(DIK_F8))
	{
		// TODO�F��ŏ����X�R�A�㏸
		m_pScore->Add(1);
	}

	// �f�o�b�O�\��
	GET_MANAGER->GetDebugProc()->Print(CDebugProc::POINT_LEFT, "======================================\n");
	GET_MANAGER->GetDebugProc()->Print(CDebugProc::POINT_LEFT, "�@[�f�o�b�O����]\n");
	GET_MANAGER->GetDebugProc()->Print(CDebugProc::POINT_LEFT, "======================================\n");
	GET_MANAGER->GetDebugProc()->Print(CDebugProc::POINT_LEFT, "[F1]�F�f�o�b�O�\����ON/OFF\n");
	GET_MANAGER->GetDebugProc()->Print(CDebugProc::POINT_LEFT, "[F2]�F�G�f�B�b�g���[�h��ON/OFF\n");
	GET_MANAGER->GetDebugProc()->Print(CDebugProc::POINT_LEFT, "[F3]�FUI�`���ON/OFF\n");
	GET_MANAGER->GetDebugProc()->Print(CDebugProc::POINT_LEFT, "[F4]�F�|�[�Y�`���ON/OFF\n");
	GET_MANAGER->GetDebugProc()->Print(CDebugProc::POINT_LEFT, "[F5]�F�J���������ON/OFF\n");
	GET_MANAGER->GetDebugProc()->Print(CDebugProc::POINT_LEFT, "[F6]�F�v���C���[�X�|�[��\n");
	GET_MANAGER->GetDebugProc()->Print(CDebugProc::POINT_LEFT, "[F7]�F�G�o���`��\n");
	GET_MANAGER->GetDebugProc()->Print(CDebugProc::POINT_LEFT, "[F8]�F�X�R�A���Z�`\n");

	GET_MANAGER->GetDebugProc()->Print(CDebugProc::POINT_LEFT, "======================================\n");
	GET_MANAGER->GetDebugProc()->Print(CDebugProc::POINT_LEFT, "�@[�f�o�b�O���]\n");
	GET_MANAGER->GetDebugProc()->Print(CDebugProc::POINT_LEFT, "======================================\n");

#endif

	if (m_pGameManager != nullptr)
	{ // �g�p���̏ꍇ

		// �Q�[���}�l�[�W���[�̍X�V
		m_pGameManager->Update();
	}
	else { assert(false); }	// ��g�p��

	if (m_pGameManager->GetState() == CGameManager::STATE_NORMAL)
	{ // �Q�[���}�l�[�W���[���ʏ��Ԃ̏ꍇ

		if (m_pPause != nullptr)
		{ // �g�p���̏ꍇ

			// �|�[�Y�̍X�V
			m_pPause->Update();
		}
		else { assert(false); }	// ��g�p��

		if (!m_pPause->IsPause())
		{ // �|�[�Y���ł͂Ȃ��ꍇ

			// �V�[���̍X�V
			CScene::Update();

			if (m_pScore != nullptr)
			{
				m_pScore->Update();
			}
		}

#if _DEBUG

		else
		{ // �|�[�Y���̏ꍇ

			if (GET_MANAGER->GetCamera()->GetState() == CCamera::STATE_CONTROL)
			{ // �J�����������Ԃ̏ꍇ

				// �J�����̍X�V
				GET_MANAGER->GetCamera()->Update();
			}
		}

#endif	// _DEBUG

	}
}

//============================================================
//	�`�揈��
//============================================================
void CSceneGame::Draw(void)
{

}

//============================================================
//	�Q�[���}�l�[�W���[�擾����
//============================================================
CGameManager *CSceneGame::GetGameManager(void)
{
	// �Q�[���}�l�[�W���[�̃|�C���^��Ԃ�
	return m_pGameManager;
}

//============================================================
//	�^�C�}�[�}�l�[�W���[�擾����
//============================================================
CScore *CSceneGame::GetScore(void)
{
	// �X�R�A�̃|�C���^��Ԃ�
	return m_pScore;
}

//============================================================
//	�|�[�Y�擾����
//============================================================
CPause *CSceneGame::GetPause(void)
{
	// �|�[�Y�̃|�C���^��Ԃ�
	return m_pPause;
}

//============================================================
//	UI�̕`��󋵂̐ݒ菈��
//============================================================
void CSceneGame::SetEnableDrawUI(const bool bDraw)
{
	// ������UI�̕`��󋵂�ݒ�
	m_bDrawUI = bDraw;
}

//============================================================
//	UI�̕`��󋵎擾����
//============================================================
bool CSceneGame::IsDrawUI(void)
{
	// UI�̕`��󋵂�Ԃ�
	return m_bDrawUI;
}

//============================================================
//	�|�[�Y�̕`��󋵂̐ݒ菈��
//============================================================
void CSceneGame::SetEnableDrawPause(const bool bDraw)
{
	// �����̃|�[�Y�̕`��󋵂�ݒ�
	m_bDrawPause = bDraw;

	// �|�[�Y�̕`��󋵂�ݒ�
	m_pPause->SetEnableDraw(m_pPause->IsPause());
}

//============================================================
//	�|�[�Y�̕`��󋵎擾����
//============================================================
bool CSceneGame::IsDrawPause(void)
{
	// �|�[�Y�̕`��󋵂�Ԃ�
	return m_bDrawPause;
}

//============================================================
//	�J�����̑���󋵂̐ݒ菈��
//============================================================
void CSceneGame::SetEnableControlCamera(const bool bControl)
{
	// �����̃J��������󋵂�ݒ�
	m_bControlCamera = bControl;

	// �J�����̑���󋵂�ݒ�
	if (bControl)
	{ // ���삷��󋵂̏ꍇ

		// �����ԂɕύX
		GET_MANAGER->GetCamera()->SetState(CCamera::STATE_CONTROL);
	}
	else
	{ // ���삵�Ȃ��󋵂̏ꍇ

		// �Ǐ]��ԂɕύX
		GET_MANAGER->GetCamera()->SetState(CCamera::STATE_FOLLOW);
	}
}
