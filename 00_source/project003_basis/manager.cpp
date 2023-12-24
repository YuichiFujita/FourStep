//============================================================
//
//	�}�l�[�W���[���� [manager.cpp]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "manager.h"
#include "renderer.h"
#include "sound.h"
#include "camera.h"
#include "light.h"
#include "fade.h"
#include "texture.h"
#include "model.h"
#include "retentionManager.h"
#include "object.h"

#ifdef _DEBUG	// �f�o�b�O����

#include "debug.h"

#endif	// _DEBUG

//************************************************************
//	�ÓI�����o�ϐ��錾
//************************************************************
CManager *CManager::m_pManager = nullptr;	// �}�l�[�W���[�I�u�W�F�N�g

//************************************************************
//	�e�N���X [CManager] �̃����o�֐�
//************************************************************
//============================================================
//	�R���X�g���N�^
//============================================================
CManager::CManager()
{
	// �����o�ϐ����N���A
	m_pRenderer	= nullptr;	// �����_���[�I�u�W�F�N�g
	m_pKeyboard	= nullptr;	// �L�[�{�[�h�I�u�W�F�N�g
	m_pMouse	= nullptr;	// �}�E�X�I�u�W�F�N�g
	m_pPad		= nullptr;	// �p�b�h�I�u�W�F�N�g
	m_pSound	= nullptr;	// �T�E���h�I�u�W�F�N�g
	m_pCamera	= nullptr;	// �J�����I�u�W�F�N�g
	m_pLight	= nullptr;	// ���C�g�I�u�W�F�N�g
	m_pTexture	= nullptr;	// �e�N�X�`���I�u�W�F�N�g
	m_pModel	= nullptr;	// ���f���I�u�W�F�N�g
	m_pFade		= nullptr;	// �t�F�[�h�I�u�W�F�N�g
	m_pScene	= nullptr;	// �V�[���I�u�W�F�N�g
	m_pRetentionManager	= nullptr;	// �f�[�^�ۑ��}�l�[�W���[
	m_pDebugProc		= nullptr;	// �f�o�b�O�\��

#ifdef _DEBUG	// �f�o�b�O����

	// �����o�ϐ����N���A
	m_pDebug = nullptr;	// �f�o�b�O

#endif	// _DEBUG
}

//============================================================
//	�f�X�g���N�^
//============================================================
CManager::~CManager()
{

}

//============================================================
//	����������
//============================================================
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	//--------------------------------------------------------
	//	�����o�ϐ���������
	//--------------------------------------------------------
	m_pRenderer	= nullptr;	// �����_���[�I�u�W�F�N�g
	m_pKeyboard	= nullptr;	// �L�[�{�[�h�I�u�W�F�N�g
	m_pMouse	= nullptr;	// �}�E�X�I�u�W�F�N�g
	m_pPad		= nullptr;	// �p�b�h�I�u�W�F�N�g
	m_pSound	= nullptr;	// �T�E���h�I�u�W�F�N�g
	m_pCamera	= nullptr;	// �J�����I�u�W�F�N�g
	m_pLight	= nullptr;	// ���C�g�I�u�W�F�N�g
	m_pTexture	= nullptr;	// �e�N�X�`���I�u�W�F�N�g
	m_pModel	= nullptr;	// ���f���I�u�W�F�N�g
	m_pFade		= nullptr;	// �t�F�[�h�I�u�W�F�N�g
	m_pScene	= nullptr;	// �V�[���I�u�W�F�N�g
	m_pRetentionManager	= nullptr;	// �f�[�^�ۑ��}�l�[�W���[
	m_pDebugProc		= nullptr;	// �f�o�b�O�\��

#ifdef _DEBUG	// �f�o�b�O����

	m_pDebug = nullptr;	// �f�o�b�O

#endif	// _DEBUG

	//--------------------------------------------------------
	//	�V�X�e���̐���
	//--------------------------------------------------------
	// �����_���[�̐���
	m_pRenderer = CRenderer::Create(hWnd, bWindow);
	if (m_pRenderer == nullptr)
	{ // ��g�p���̏ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	// �L�[�{�[�h�̐���
	m_pKeyboard = CInputKeyboard::Create(hInstance, hWnd);
	if (m_pKeyboard == nullptr)
	{ // ��g�p���̏ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	// �}�E�X�̐���
	m_pMouse = CInputMouse::Create(hInstance, hWnd);
	if (m_pMouse == nullptr)
	{ // ��g�p���̏ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	// �p�b�h�̐���
	m_pPad = CInputPad::Create();
	if (m_pPad == nullptr)
	{ // ��g�p���̏ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	// �T�E���h�̐���
	m_pSound = CSound::Create(hWnd);
	if (m_pSound == nullptr)
	{ // ��g�p���̏ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	// �J�����̐���
	m_pCamera = CCamera::Create();
	if (m_pCamera == nullptr)
	{ // ��g�p���̏ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	// ���C�g�̐���
	m_pLight = CLight::Create();
	if (m_pLight == nullptr)
	{ // ��g�p���̏ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	// �f�[�^�ۑ��}�l�[�W���[�̐���
	m_pRetentionManager = CRetentionManager::Create();
	if (m_pRetentionManager == nullptr)
	{ // ��g�p���̏ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	//--------------------------------------------------------
	//	���̓Ǎ��E�ݒ�
	//--------------------------------------------------------
	// �e�N�X�`���̐����E�Ǎ�
	m_pTexture = CTexture::Create();
	if (m_pTexture == nullptr)
	{ // ��g�p���̏ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	// ���f���̐����E�Ǎ�
	m_pModel = CModel::Create();
	if (m_pModel == nullptr)
	{ // ��g�p���̏ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	// �����_�[�e�N�X�`���[�̐���
	if (FAILED(m_pRenderer->CreateRenderTexture()))
	{ // �����Ɏ��s�����ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	// �t�F�[�h�̐����E�V�[���̐ݒ�
	m_pFade = CFade::Create();
	if (m_pFade == nullptr)
	{ // ��g�p���̏ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	//--------------------------------------------------------
	//	�f�o�b�O�p
	//--------------------------------------------------------
	// �f�o�b�O�\���̐���
	m_pDebugProc = CDebugProc::Create();
	if (m_pDebugProc == nullptr)
	{ // ��g�p���̏ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

#ifdef _DEBUG	// �f�o�b�O����

	// �f�o�b�O�̐���
	m_pDebug = CDebug::Create();
	if (m_pDebug == nullptr)
	{ // ��g�p���̏ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

#endif	// _DEBUG

	// ������Ԃ�
	return S_OK;
}

//============================================================
//	�I������
//============================================================
HRESULT CManager::Uninit(void)
{
	//--------------------------------------------------------
	//	�f�o�b�O�p
	//--------------------------------------------------------
	// �f�o�b�O�\���̔j��
	SAFE_REF_RELEASE(m_pDebugProc);

#ifdef _DEBUG	// �f�o�b�O����

	// �f�o�b�O�̔j��
	SAFE_REF_RELEASE(m_pDebug);

#endif	// _DEBUG

	//--------------------------------------------------------
	//	���̔j��
	//--------------------------------------------------------
	// �e�N�X�`���̔j��
	SAFE_REF_RELEASE(m_pTexture);

	// ���f���̔j��
	SAFE_REF_RELEASE(m_pModel);

	//--------------------------------------------------------
	//	�V�X�e���̔j��
	//--------------------------------------------------------
	// �f�[�^�ۑ��}�l�[�W���[�̔j��
	SAFE_REF_RELEASE(m_pRetentionManager);

	// �V�[���̔j��
	SAFE_REF_RELEASE(m_pScene);

	// �t�F�[�h�̔j��
	SAFE_REF_RELEASE(m_pFade);

	// ���C�g�̔j��
	SAFE_REF_RELEASE(m_pLight);

	// �J�����̔j��
	SAFE_REF_RELEASE(m_pCamera);

	// �T�E���h�̔j��
	SAFE_REF_RELEASE(m_pSound);

	// �p�b�h�̔j��
	SAFE_REF_RELEASE(m_pPad);

	// �}�E�X�̔j��
	SAFE_REF_RELEASE(m_pMouse);

	// �L�[�{�[�h�̔j��
	SAFE_REF_RELEASE(m_pKeyboard);

	// �����_���[�̔j��
	SAFE_REF_RELEASE(m_pRenderer);

	// �I�u�W�F�N�g�̑S�j��
	CObject::ReleaseAll();

	// ��O����
	assert(CObject::GetNumAll() == 0);	// �j���̎��s

	// ������Ԃ�
	return S_OK;
}

//============================================================
//	�X�V����
//============================================================
void CManager::Update(void)
{
#ifdef _DEBUG	// �f�o�b�O����

	// �f�o�b�O�\��
	m_pDebugProc->Print(CDebugProc::POINT_CENTER, "[FPS]�F%d\n", m_pDebug->GetFps());

#endif	// _DEBUG

	// �p�b�h�̍X�V
	assert(m_pPad != nullptr);
	m_pPad->Update();

	// �}�E�X�̍X�V
	assert(m_pMouse != nullptr);
	m_pMouse->Update();

	// �L�[�{�[�h�̍X�V
	assert(m_pKeyboard != nullptr);
	m_pKeyboard->Update();

	// �t�F�[�h�̍X�V
	assert(m_pFade != nullptr);
	m_pFade->Update();

	// �V�[���̍X�V
	assert(m_pScene != nullptr);
	m_pScene->Update();

	// �f�o�b�O�\���̍X�V
	assert(m_pDebugProc != nullptr);
	m_pDebugProc->Update();
}

//============================================================
//	�`�揈��
//============================================================
void CManager::Draw(void)
{
	if (m_pRenderer != nullptr)
	{ // �g�p���̏ꍇ

		// �����_���[�̕`��
		m_pRenderer->Draw();
	}
	else { assert(false); }	// ��g�p��
}

//============================================================
//	��������
//============================================================
CManager *CManager::Create(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	if (m_pManager == nullptr)
	{ // �g�p����Ă��Ȃ��ꍇ

		// ���������m��
		m_pManager = new CManager;	// �}�l�[�W���[
	}
	else { assert(false); return nullptr; }	// �g�p��

	if (m_pManager != nullptr)
	{ // �m�ۂɐ������Ă���ꍇ

		// �}�l�[�W���[�̏�����
		if (FAILED(m_pManager->Init(hInstance, hWnd, bWindow)))
		{ // �������Ɏ��s�����ꍇ

			// �}�l�[�W���[�̏I��
			if (FAILED(m_pManager->Uninit()))
			{ // �}�l�[�W���[�̏I���Ɏ��s�����ꍇ

				// �������J��
				delete m_pManager;
				m_pManager = nullptr;

				// ���s��Ԃ�
				assert(false);
				return nullptr;
			}

			// �������J��
			delete m_pManager;
			m_pManager = nullptr;

			// ���s��Ԃ�
			assert(false);
			return nullptr;
		}

		// �m�ۂ����A�h���X��Ԃ�
		return m_pManager;
	}
	else { assert(false); return nullptr; }	// �m�ێ��s
}

//============================================================
//	�擾����
//============================================================
CManager *CManager::GetInstance(void)
{
	// ��O����
	assert(m_pManager != nullptr);	// �C���X�^���X���g�p

	// �}�l�[�W���[�̃|�C���^��Ԃ�
	return m_pManager;
}

//============================================================
//	�j������
//============================================================
HRESULT CManager::Release(CManager *&prManager)
{
	if (prManager != nullptr)
	{ // �g�p���̏ꍇ

		// �}�l�[�W���[�̏I��
		if (FAILED(prManager->Uninit()))
		{ // �}�l�[�W���[�̏I���Ɏ��s�����ꍇ

			// ���s��Ԃ�
			assert(false);
			return E_FAIL;
		}

		// �������J��
		delete prManager;
		prManager = nullptr;

		// ������Ԃ�
		return S_OK;
	}
	else { assert(false); return E_FAIL; }	// ��g�p��
}

//============================================================
//	�V�[���̐ݒ菈��
//============================================================
void CManager::SetScene(const CScene::EMode mode, const int nWait)
{
	// ���̃V�[����ݒ�
	m_pFade->Set(mode, nWait);
}

//============================================================
//	���[�h�̐ݒ菈��
//============================================================
HRESULT CManager::SetMode(const CScene::EMode mode)
{
	// �T�E���h���~
	m_pSound->Stop();

	if (m_pScene != nullptr)
	{ // �V�[�����g�p���̏ꍇ

		// �V�[���̔j��
		if (FAILED(CScene::Release(m_pScene)))
		{ // �j���Ɏ��s�����ꍇ

			// ���s��Ԃ�
			assert(false);
			return E_FAIL;
		}
	}

	// �I�u�W�F�N�g�̑S�j��
	CObject::ReleaseAll();

	if (m_pScene == nullptr)
	{ // �V�[������g�p���̏ꍇ

		// �V�[���̐���
		m_pScene = CScene::Create(mode);
		if (m_pScene == nullptr)
		{ // ��g�p���̏ꍇ

			// ���s��Ԃ�
			assert(false);
			return E_FAIL;
		}
	}
	else { assert(false); return E_FAIL; }	// �g�p��

	// ������Ԃ�
	return S_OK;
}

//============================================================
//	���[�h�̎擾����
//============================================================
CScene::EMode CManager::GetMode(void)
{
	// ���݂̃��[�h��Ԃ�
	return m_pScene->GetMode();
}

//============================================================
//	�����_���[�擾����
//============================================================
CRenderer *CManager::GetRenderer(void)
{
	// �����_���[�̃|�C���^��Ԃ�
	return m_pRenderer;
}

//============================================================
//	�L�[�{�[�h�擾����
//============================================================
CInputKeyboard *CManager::GetKeyboard(void)
{
	// �L�[�{�[�h�̃|�C���^��Ԃ�
	return m_pKeyboard;
}

//============================================================
//	�}�E�X�擾����
//============================================================
CInputMouse *CManager::GetMouse(void)
{
	// �}�E�X�̃|�C���^��Ԃ�
	return m_pMouse;
}

//============================================================
//	�p�b�h�擾����
//============================================================
CInputPad *CManager::GetPad(void)
{
	// �p�b�h�̃|�C���^��Ԃ�
	return m_pPad;
}

//============================================================
//	�T�E���h�擾����
//============================================================
CSound *CManager::GetSound(void)
{
	// �T�E���h�̃|�C���^��Ԃ�
	return m_pSound;
}

//============================================================
//	�J�����擾����
//============================================================
CCamera *CManager::GetCamera(void)
{
	// �J�����̃|�C���^��Ԃ�
	return m_pCamera;
}

//============================================================
//	���C�g�擾����
//============================================================
CLight *CManager::GetLight(void)
{
	// ���C�g�̃|�C���^��Ԃ�
	return m_pLight;
}

//============================================================
//	�e�N�X�`���擾����
//============================================================
CTexture *CManager::GetTexture(void)
{
	// �e�N�X�`���̃|�C���^��Ԃ�
	return m_pTexture;
}

//============================================================
//	���f���擾����
//============================================================
CModel *CManager::GetModel(void)
{
	// ���f���̃|�C���^��Ԃ�
	return m_pModel;
}

//============================================================
//	�t�F�[�h�擾����
//============================================================
CFade *CManager::GetFade(void)
{
	// �t�F�[�h�̃|�C���^��Ԃ�
	return m_pFade;
}

//============================================================
//	�V�[���擾����
//============================================================
CScene *CManager::GetScene(void)
{
	// �V�[���̃|�C���^��Ԃ�
	return m_pScene;
}

//============================================================
//	�f�[�^�ۑ��}�l�[�W���[�擾����
//============================================================
CRetentionManager *CManager::GetRetentionManager(void)
{
	// �f�[�^�ۑ��}�l�[�W���[��Ԃ�
	return m_pRetentionManager;
}

//============================================================
//	�f�o�b�O�\���擾����
//============================================================
CDebugProc *CManager::GetDebugProc(void)
{
	// �f�o�b�O�\���̃|�C���^��Ԃ�
	return m_pDebugProc;
}

//============================================================
//	�f�o�b�O�擾����
//============================================================
#ifdef _DEBUG	// �f�o�b�O����

CDebug *CManager::GetDebug(void)
{
	// �f�o�b�O�̃|�C���^��Ԃ�
	return m_pDebug;
}

#endif	// _DEBUG
