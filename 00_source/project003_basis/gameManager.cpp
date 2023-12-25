//============================================================
//
//	�Q�[���}�l�[�W���[���� [gameManager.cpp]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "gameManager.h"
#include "manager.h"
#include "scene.h"
#include "sceneGame.h"
#include "camera.h"
#include "player.h"
#include "map.h"
#include "retentionManager.h"
#include "score.h"

//************************************************************
//	�ÓI�����o�ϐ��錾
//************************************************************
CMap* CGameManager::m_pMap = nullptr;

//************************************************************
//	�e�N���X [CGameManager] �̃����o�֐�
//************************************************************
//============================================================
//	�R���X�g���N�^
//============================================================
CGameManager::CGameManager()
{
	// �����o�ϐ����N���A
	m_state = STATE_NONE;	// ���
	m_pMap = nullptr;
}

//============================================================
//	�f�X�g���N�^
//============================================================
CGameManager::~CGameManager()
{

}

//============================================================
//	����������
//============================================================
HRESULT CGameManager::Init(void)
{
	// �����o�ϐ���������
	m_state = STATE_NORMAL;	// ���

	if (m_pMap == nullptr)
	{
		m_pMap = CMap::Create(D3DXVECTOR3(-1000.0f,0.0f,-1000.0f), VEC3_ZERO, D3DXVECTOR3(50.0f, 50.0f, 50.0f), VEC2_ONE, VEC2_ONE, VEC2_ONE);
		m_pMap->Init();
	}

	// ������Ԃ�
	return S_OK;
}

//============================================================
//	�I������
//============================================================
void CGameManager::Uninit(void)
{
	if (m_pMap != nullptr)
	{
		m_pMap->Uninit();
		m_pMap = nullptr;
	}
}

//============================================================
//	�X�V����
//============================================================
void CGameManager::Update(void)
{
	switch (m_state)
	{ // ��Ԃ��Ƃ̏���
	case STATE_NONE:

		// ����

		break;

	case STATE_NORMAL:

		m_pMap->Update();

		if (CScene::GetPlayer()->GetState() == CPlayer::STATE_DEATH)
		{ // ���S�����ꍇ

			// �X�R�A��ݒ�
			GET_RETENTION->SetScore(CSceneGame::GetScore()->Get());

			// �V�[���J��
			GET_MANAGER->SetScene(CScene::MODE_RESULT, 60);
		}

		break;

	case STATE_END:

		// ����

		break;

	default:	// ��O����
		assert(false);
		break;
	}
}

//============================================================
//	��Ԃ̐ݒ菈��
//============================================================
void CGameManager::SetState(const EState state)
{
	if (state > NONE_IDX && state < STATE_MAX)
	{ // �͈͓��̏ꍇ

		// ��Ԃ�ݒ�
		m_state = state;
	}
	else { assert(false); }	// �͈͊O
}

//============================================================
//	��Ԏ擾����
//============================================================
CGameManager::EState CGameManager::GetState(void) const
{
	// ��Ԃ�Ԃ�
	return m_state;
}

//============================================================
//	��������
//============================================================
CGameManager *CGameManager::Create(void)
{
	// �|�C���^��錾
	CGameManager *pGameManager = nullptr;	// �Q�[���}�l�[�W���[�����p

	if (pGameManager == nullptr)
	{ // �g�p����Ă��Ȃ��ꍇ

		// �������m��
		pGameManager = new CGameManager;	// �Q�[���}�l�[�W���[
	}
	else { assert(false); return nullptr; }	// �g�p��

	if (pGameManager != nullptr)
	{ // �g�p����Ă���ꍇ
		
		// �Q�[���}�l�[�W���[�̏�����
		if (FAILED(pGameManager->Init()))
		{ // �������Ɏ��s�����ꍇ

			// �������J��
			delete pGameManager;
			pGameManager = nullptr;

			// ���s��Ԃ�
			return nullptr;
		}

		// �m�ۂ����A�h���X��Ԃ�
		return pGameManager;
	}
	else { assert(false); return nullptr; }	// �m�ێ��s
}

//============================================================
//	�j������
//============================================================
HRESULT CGameManager::Release(CGameManager *&prGameManager)
{
	if (prGameManager != nullptr)
	{ // �g�p���̏ꍇ

		// �Q�[���}�l�[�W���[�̏I��
		prGameManager->Uninit();

		// �������J��
		delete prGameManager;
		prGameManager = nullptr;

		// ������Ԃ�
		return S_OK;
	}
	else { assert(false); return E_FAIL; }	// ��g�p��
}

//============================================================
//	�}�b�v�擾����
//============================================================
CMap *CGameManager::GetMap(void)
{
	return m_pMap;
}
