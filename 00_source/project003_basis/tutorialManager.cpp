//============================================================
//
//	�`���[�g���A���}�l�[�W���[���� [tutorialManager.cpp]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "tutorialManager.h"
#include "manager.h"
#include "sound.h"
#include "camera.h"
#include "texture.h"
#include "object2D.h"

//************************************************************
//	�萔�錾
//************************************************************
namespace
{
	const int PRIORITY = 14;	// �`���[�g���A���̗D�揇��

	namespace lesson
	{
		const D3DXVECTOR3 POS	= D3DXVECTOR3(640.0f, 580.0f, 0.0f);	// ���b�X���\���̈ʒu
		const D3DXVECTOR3 SIZE	= D3DXVECTOR3(1000.0f, 270.0f, 0.0f);	// ���b�X���\���̈ʒu
	}

	namespace control
	{
		const D3DXVECTOR3 POS	= D3DXVECTOR3(1140.0f, 85.0f, 0.0f);	// ������@�̈ʒu
		const D3DXVECTOR3 SIZE	= D3DXVECTOR3(264.0f, 150.0f, 0.0f);	// ������@�̈ʒu
	}
}

//************************************************************
//	�ÓI�����o�ϐ��錾
//************************************************************
const char *CTutorialManager::mc_apTextureFile[] =	// �e�N�X�`���萔
{
	"data\\TEXTURE\\tutorial000.png",	// ��������e�N�X�`��
};
const char *CTutorialManager::mc_apLessonTextureFile[] =	// ���b�X���e�N�X�`���萔
{
	"data\\TEXTURE\\lesson000.png",	// �W�����v�����e�N�X�`��
	"data\\TEXTURE\\lesson001.png",	// �X���C�f�B���O�����e�N�X�`��
	"data\\TEXTURE\\lesson002.png",	// �Ǒ�������e�N�X�`��
	"data\\TEXTURE\\lesson003.png",	// �ǃW�����v�����e�N�X�`��
};

//************************************************************
//	�e�N���X [CTutorialManager] �̃����o�֐�
//************************************************************
//============================================================
//	�R���X�g���N�^
//============================================================
CTutorialManager::CTutorialManager()
{
	// �����o�ϐ����N���A
	m_pExplain = nullptr;	// �����\���̏��
	m_pControl = nullptr;	// ��������̏��
}

//============================================================
//	�f�X�g���N�^
//============================================================
CTutorialManager::~CTutorialManager()
{

}

//============================================================
//	����������
//============================================================
HRESULT CTutorialManager::Init(void)
{
	// �����o�ϐ���������
	m_pExplain = nullptr;	// �����\���̏��
	m_pControl = nullptr;	// ��������̏��

	// �����\���̐���
	m_pExplain = CObject2D::Create
	( // ����
		lesson::POS,	// �ʒu
		lesson::SIZE	// �傫��
	);
	if (m_pExplain == nullptr)
	{ // �����Ɏ��s�����ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	// �D�揇�ʂ�ݒ�
	m_pExplain->SetPriority(PRIORITY);

	// ��������̐���
	m_pControl = CObject2D::Create
	( // ����
		control::POS,	// �ʒu
		control::SIZE	// �傫��
	);
	if (m_pControl == nullptr)
	{ // �����Ɏ��s�����ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	// �e�N�X�`����o�^�E����
	m_pControl->BindTexture(mc_apTextureFile[TEXTURE_CONTROL]);

	// �D�揇�ʂ�ݒ�
	m_pControl->SetPriority(PRIORITY);

	// ������Ԃ�
	return S_OK;
}

//============================================================
//	�I������
//============================================================
HRESULT CTutorialManager::Uninit(void)
{
	// �����\���̏I��
	m_pExplain->Uninit();

	// ��������̏I��
	m_pControl->Uninit();

	// ������Ԃ�
	return S_OK;
}

//============================================================
//	�X�V����
//============================================================
void CTutorialManager::Update(void)
{
	// �|�C���^��錾
	CInputKeyboard	*pKeyboard	= GET_INPUTKEY;	// �L�[�{�[�h
	CInputPad		*pPad		= GET_INPUTPAD;		// �p�b�h

	if (pKeyboard->IsTrigger(DIK_RETURN) || pPad->IsTrigger(CInputPad::KEY_START))
	{
		// �V�[���̐ݒ�
		GET_MANAGER->SetScene(CScene::MODE_TITLE);	// �^�C�g�����
	}

	// �����\���̍X�V
	m_pExplain->Update();

	// ��������̍X�V
	m_pControl->Update();
}

//============================================================
//	��������
//============================================================
CTutorialManager *CTutorialManager::Create(void)
{
	// �|�C���^��錾
	CTutorialManager *pTutorialManager = nullptr;	// �`���[�g���A���}�l�[�W���[�����p

	if (pTutorialManager == nullptr)
	{ // �g�p����Ă��Ȃ��ꍇ

		// �������m��
		pTutorialManager = new CTutorialManager;	// �`���[�g���A���}�l�[�W���[
	}
	else { assert(false); return nullptr; }	// �g�p��

	if (pTutorialManager != nullptr)
	{ // �g�p����Ă���ꍇ
		
		// �`���[�g���A���}�l�[�W���[�̏�����
		if (FAILED(pTutorialManager->Init()))
		{ // �������Ɏ��s�����ꍇ

			// �������J��
			delete pTutorialManager;
			pTutorialManager = nullptr;

			// ���s��Ԃ�
			return nullptr;
		}

		// �m�ۂ����A�h���X��Ԃ�
		return pTutorialManager;
	}
	else { assert(false); return nullptr; }	// �m�ێ��s
}

//============================================================
//	�j������
//============================================================
HRESULT CTutorialManager::Release(CTutorialManager *&prTutorialManager)
{
	if (prTutorialManager != nullptr)
	{ // �g�p���̏ꍇ

		// �`���[�g���A���}�l�[�W���[�̏I��
		if (FAILED(prTutorialManager->Uninit()))
		{ // �j���Ɏ��s�����ꍇ

			// �������J��
			delete prTutorialManager;
			prTutorialManager = nullptr;

			// ���s��Ԃ�
			assert(false);
			return E_FAIL;
		}

		// �������J��
		delete prTutorialManager;
		prTutorialManager = nullptr;

		// ������Ԃ�
		return S_OK;
	}
	else { assert(false); return E_FAIL; }	// ��g�p��
}