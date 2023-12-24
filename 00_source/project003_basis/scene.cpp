//============================================================
//
//	�V�[������ [scene.cpp]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "scene.h"
#include "manager.h"
#include "renderer.h"
#include "light.h"
#include "camera.h"
#include "sceneTitle.h"
#include "sceneTutorial.h"
#include "sceneGame.h"
#include "sceneResult.h"
#include "sceneRanking.h"

#include "stage.h"
#include "player.h"

//************************************************************
//	�ÓI�����o�ϐ��錾
//************************************************************
CStage *CScene::m_pStage = nullptr;	// �X�e�[�W
CPlayer	*CScene::m_pPlayer = nullptr;	// �v���C���[�I�u�W�F�N�g

//************************************************************
//	�e�N���X [CScene] �̃����o�֐�
//************************************************************
//============================================================
//	�R���X�g���N�^
//============================================================
CScene::CScene(const EMode mode)
{
	// �����o�ϐ����N���A
	m_mode = mode;	// ���[�h
}

//============================================================
//	�f�X�g���N�^
//============================================================
CScene::~CScene()
{

}

//============================================================
//	����������
//============================================================
HRESULT CScene::Init(void)
{
	// �X�e�[�W�̐���
	m_pStage = CStage::Create(m_mode);
	if (m_pStage == nullptr)
	{ // ��g�p���̏ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	// �v���C���[�I�u�W�F�N�g�̐���
	m_pPlayer = CPlayer::Create(m_mode);

	// ������Ԃ�
	return S_OK;
}

//============================================================
//	�I������
//============================================================
HRESULT CScene::Uninit(void)
{
	// �X�e�[�W�̔j��
	if (FAILED(CStage::Release(m_pStage)))
	{ // �j���Ɏ��s�����ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	// �I���ς݂̃I�u�W�F�N�g�|�C���^��nullptr�ɂ���
	m_pPlayer = nullptr;	// �v���C���[�I�u�W�F�N�g

	// ������Ԃ�
	return S_OK;
}

//============================================================
//	�X�V����
//============================================================
void CScene::Update(void)
{
	if (m_pStage != nullptr)
	{ // �g�p���̏ꍇ

		// �X�e�[�W�̍X�V
		m_pStage->Update();
	}
	else { assert(false); }	// ��g�p��

	if (GET_MANAGER->GetLight() != nullptr)
	{ // �g�p���̏ꍇ

		// ���C�g�̍X�V
		GET_MANAGER->GetLight()->Update();
	}
	else { assert(false); }	// ��g�p��

	if (GET_MANAGER->GetCamera() != nullptr)
	{ // �g�p���̏ꍇ

		// �J�����̍X�V
		GET_MANAGER->GetCamera()->Update();
	}
	else { assert(false); }	// ��g�p��

	if (GET_MANAGER->GetRenderer() != nullptr)
	{ // �g�p���̏ꍇ

		// �����_���[�̍X�V
		GET_MANAGER->GetRenderer()->Update();
	}
	else { assert(false); }	// ��g�p��
}

//============================================================
//	��������
//============================================================
CScene *CScene::Create(EMode mode)
{
	// �|�C���^��錾
	CScene *pScene = nullptr;	// �V�[�������p

	if (pScene == nullptr)
	{ // �g�p����Ă��Ȃ��ꍇ

		// �������m��
		switch (mode)
		{ // ���[�h���Ƃ̏���
		case MODE_TITLE:

			// �^�C�g����ʂ𐶐�
			pScene = new CSceneTitle(mode);

			break;

		case MODE_TUTORIAL:

			// �`���[�g���A����ʂ𐶐�
			pScene = new CSceneTutorial(mode);

			break;

		case MODE_GAME:

			// �Q�[����ʂ𐶐�
			pScene = new CSceneGame(mode);

			break;

		case MODE_RESULT:

			// ���U���g��ʂ𐶐�
			pScene = new CSceneResult(mode);

			break;

		case MODE_RANKING:

			// �����L���O��ʂ𐶐�
			pScene = new CSceneRanking(mode);

			break;

		default:	// ��O����
			assert(false);
			break;
		}
	}
	else { assert(false); return nullptr; }	// �g�p��

	if (pScene != nullptr)
	{ // �m�ۂɐ������Ă���ꍇ

		// �V�[���̏�����
		if (FAILED(pScene->Init()))
		{ // �������Ɏ��s�����ꍇ

			// �V�[���̏I��
			if (FAILED(pScene->Uninit()))
			{ // �V�[���̏I���Ɏ��s�����ꍇ

				// �������J��
				delete pScene;
				pScene = nullptr;

				// ���s��Ԃ�
				assert(false);
				return nullptr;
			}

			// �������J��
			delete pScene;
			pScene = nullptr;

			// ���s��Ԃ�
			assert(false);
			return nullptr;
		}

		// �m�ۂ����A�h���X��Ԃ�
		return pScene;
	}
	else { assert(false); return nullptr; }	// �m�ێ��s
}

//============================================================
//	�j������
//============================================================
HRESULT CScene::Release(CScene *&prScene)
{
	if (prScene != nullptr)
	{ // �g�p���̏ꍇ

		// �V�[���̏I��
		if (FAILED(prScene->Uninit()))
		{ // �V�[���̏I���Ɏ��s�����ꍇ

			// ���s��Ԃ�
			assert(false);
			return E_FAIL;
		}

		// �������J��
		delete prScene;
		prScene = nullptr;

		// ������Ԃ�
		return S_OK;
	}
	else { assert(false); return E_FAIL; }	// ��g�p��
}

//============================================================
//	�X�e�[�W�擾����
//============================================================
CStage *CScene::GetStage(void)
{
	// �X�e�[�W�̃|�C���^��Ԃ�
	return m_pStage;
}

//============================================================
//	�v���C���[�擾����
//============================================================
CPlayer *CScene::GetPlayer(void)
{
	// �v���C���[�̃|�C���^��Ԃ�
	return m_pPlayer;
}

//============================================================
//	���[�h�̐ݒ菈��
//============================================================
void CScene::SetMode(const EMode mode)
{
	// �����̃��[�h��ݒ�
	m_mode = mode;
}

//============================================================
//	���[�h�擾����
//============================================================
CScene::EMode CScene::GetMode(void) const
{
	// ���݂̃��[�h��Ԃ�
	return m_mode;
}
