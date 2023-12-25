//============================================================
//
//	���U���g�}�l�[�W���[���� [resultManager.cpp]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "resultManager.h"
#include "manager.h"
#include "sound.h"
#include "camera.h"
#include "fade.h"
#include "texture.h"
#include "model.h"
#include "object2D.h"
#include "retentionManager.h"
#include "multivalue.h"

//************************************************************
//	�}�N����`
//************************************************************
#define RESULT_PRIO	(14)	// ���U���g�̗D�揇��

#define SETCOL_FADE		(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.6f))	// ���l�̒�~�l
#define SIZE_FADE		(SCREEN_SIZE * 0.95f)	// �t�F�[�h�̑傫��
#define INITCOL_FADE	(XCOL_AWHITE)	// ���l�̏����l
#define ADD_ALPHA		(0.008f)		// ���l�̉��Z��

#define POS_RESULT_MISSION	(D3DXVECTOR3(440.0f, 150.0f, 0.0f))	// ���U���g�\���̒x������̈ʒu
#define POS_RESULT_RESULT	(D3DXVECTOR3(840.0f, 150.0f, 0.0f))	// ���U���g�\���̐������s�̈ʒu
#define SIZE_RESULT			(D3DXVECTOR3(1280.0f, 260.0f, 0.0f)*0.5f)	// ���U���g�\���̑傫��
#define SIZE_VALUE			(D3DXVECTOR3(120.0f, 140.0f, 0.0f))
#define SPACE_VALUE			(D3DXVECTOR3(100.0f, 0.0f, 0.0f))
#define SET_RESULT_SCALE	(15.0f)	// ���U���g�\���̏����g�嗦
#define SUB_RESULT_SCALE	(0.65f)	// ���U���g�\���g�嗦�̌��Z��

#define POS_TIME_LOGO	(D3DXVECTOR3(290.0f, 330.0f, 0.0f))	// �^�C�����S�ʒu
#define SIZE_TIME_LOGO	(D3DXVECTOR3(487.5f, 154.7f, 0.0f))	// �^�C�����S�傫��
#define POS_TIME		(D3DXVECTOR3(555.0f, 330.0f, 0.0f))	// �^�C���ʒu
#define SIZE_TIME_VAL	(D3DXVECTOR3(98.0f, 117.0f, 0.0f))	// �^�C�������傫��
#define SIZE_TIME_PART	(D3DXVECTOR3(50.0f, 117.0f, 0.0f))	// �^�C����؂�傫��
#define SPACE_TIME_VAL	(D3DXVECTOR3(SIZE_TIME_VAL.x  * 0.85f, 0.0f, 0.0f))	// �^�C��������
#define SPACE_TIME_PART	(D3DXVECTOR3(SIZE_TIME_PART.x * 0.85f, 0.0f, 0.0f))	// �^�C����؂��
#define SET_TIME_SCALE	(8.0f)	// �^�C���\���̏����g�嗦
#define SUB_TIME_SCALE	(0.3f)	// �^�C���\���g�嗦�̌��Z��
#define TIME_WAIT_CNT	(3)		// �^�C���\����Ԃւ̕ύX�ҋ@�t���[����

#define POS_CONT_LOGO	(D3DXVECTOR3(SCREEN_CENT.x, 490.0f, 0.0f))	// �R���e�j���[���S�ʒu
#define SIZE_CONT_LOGO	(D3DXVECTOR3(576.0f, 172.0f, 0.0f))	// �R���e�j���[���S�傫��
#define POS_CONT_YES	(D3DXVECTOR3(400.0f, 610.0f, 0.0f))	// �R���e�j���[�\����YES�̈ʒu
#define POS_CONT_NO		(D3DXVECTOR3(880.0f, 610.0f, 0.0f))	// �R���e�j���[�\����NO�̈ʒu
#define SIZE_CONT		(D3DXVECTOR3(222.0f, 94.0f, 0.0f))	// �R���e�j���[�\���̑傫��
#define SET_CONT_SCALE	(8.0f)	// �R���e�j���[�\���̏����g�嗦
#define SUB_CONT_SCALE	(0.3f)	// �R���e�j���[�\���g�嗦�̌��Z��
#define CONT_WAIT_CNT	(3)		// �R���e�j���[�\����Ԃւ̕ύX�ҋ@�t���[����

#define CHOICE_COL	(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f))	// �I�𒆃J���[
#define DEFAULT_COL	(D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f))	// ��I�𒆃J���[

//************************************************************
//	�ÓI�����o�ϐ��錾
//************************************************************
const char *CResultManager::mc_apTextureFile[] =	// �e�N�X�`���萔
{
	"data\\TEXTURE\\result000.png",		// �x������e�N�X�`��
	"data\\TEXTURE\\continue000.png",	// �R���e�j���[�\���e�N�X�`��
	"data\\TEXTURE\\continue001.png",	// YES�e�N�X�`��
	"data\\TEXTURE\\continue002.png",	// NO�e�N�X�`��
};

//************************************************************
//	�e�N���X [CResultManager] �̃����o�֐�
//************************************************************
//============================================================
//	�R���X�g���N�^
//============================================================
CResultManager::CResultManager()
{
	// �����o�ϐ����N���A
	memset(&m_apContinue[0], 0, sizeof(m_apContinue));	// �R���e�j���[�\���̏��
	m_pScoreTitle	= nullptr;		// �X�R�A�^�C�g���̏��
	m_pScore		= nullptr;		// �X�R�A�̏��
	m_pContLogo		= nullptr;		// �R���e�j���[���S�̏��
	m_pFade			= nullptr;		// �t�F�[�h�̏��
	m_state			= STATE_NONE;	// ���
	m_nCounterState	= 0;			// ��ԊǗ��J�E���^�[
	m_nSelect		= SELECT_YES;	// ���݂̑I��
	m_nOldSelect	= SELECT_YES;	// �O��̑I��
	m_fScale		= 0.0f;			// �|���S���g�嗦
}

//============================================================
//	�f�X�g���N�^
//============================================================
CResultManager::~CResultManager()
{

}

//============================================================
//	����������
//============================================================
HRESULT CResultManager::Init(void)
{
	// �ϐ��z���錾
	static D3DXVECTOR3 aPosContinue[] =	// �R���e�j���[�̈ʒu
	{
		POS_CONT_YES,	// YES�ʒu
		POS_CONT_NO	,	// NO�ʒu
	};

	// �|�C���^��錾
	CTexture *pTexture = GET_MANAGER->GetTexture();	// �e�N�X�`���ւ̃|�C���^

	// �����o�ϐ���������
	memset(&m_apContinue[0], 0, sizeof(m_apContinue));	// �R���e�j���[�\���̏��
	m_pScoreTitle	= nullptr;		// �X�R�A�^�C�g���̏��
	m_pScore		= nullptr;		// �X�R�A�̏��
	m_pContLogo		= nullptr;		// �R���e�j���[���S�̏��
	m_pFade			= nullptr;		// �t�F�[�h�̏��
	m_state			= STATE_FADEIN;	// ���
	m_nCounterState	= 0;			// ��ԊǗ��J�E���^�[
	m_nSelect		= SELECT_YES;	// ���݂̑I��
	m_nOldSelect	= SELECT_YES;	// �O��̑I��
	m_fScale		= 0.0f;			// �|���S���g�嗦

	//--------------------------------------------------------
	//	�t�F�[�h�̐����E�ݒ�
	//--------------------------------------------------------
	// �t�F�[�h�̐���
	m_pFade = CObject2D::Create
	( // ����
		SCREEN_CENT,	// �ʒu
		SIZE_FADE,		// �傫��
		VEC3_ZERO,		// ����
		INITCOL_FADE	// �F
	);
	if (m_pFade == nullptr)
	{ // �����Ɏ��s�����ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	// �D�揇�ʂ�ݒ�
	m_pFade->SetPriority(RESULT_PRIO);

	//--------------------------------------------------------
	//	���U���g�\���̐����E�ݒ�
	//--------------------------------------------------------
	// ���U���g�\���̐���
	m_pScoreTitle = CObject2D::Create
	( // ����
		POS_RESULT_MISSION,				// �ʒu
		SIZE_RESULT * SET_RESULT_SCALE	// �傫��
	);
	if (m_pScoreTitle == nullptr)
	{ // �����Ɏ��s�����ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	// �e�N�X�`����o�^�E����
	m_pScoreTitle->BindTexture(pTexture->Regist(mc_apTextureFile[TEXTURE_SCORE]));

	// �D�揇�ʂ�ݒ�
	m_pScoreTitle->SetPriority(RESULT_PRIO);

	// �`������Ȃ��ݒ�ɂ���
	m_pScoreTitle->SetEnableDraw(false);

	// ���U���g�\���̐���
	m_pScore = CMultiValue::Create
	( // ����
		CValue::TEXTURE_NORMAL,
		GET_RETENTION->GetScore(),
		3,
		POS_RESULT_RESULT,				// �ʒu
		SIZE_VALUE * SET_RESULT_SCALE,	// �傫��
		SPACE_VALUE
	);
	if (m_pScore == nullptr)
	{ // �����Ɏ��s�����ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	// �D�揇�ʂ�ݒ�
	m_pScore->SetPriority(RESULT_PRIO);

	// �`������Ȃ��ݒ�ɂ���
	m_pScore->SetEnableDraw(false);

	//--------------------------------------------------------
	//	�R���e�j���[���S�\���̐����E�ݒ�
	//--------------------------------------------------------
	// �R���e�j���[���S�\���̐���
	m_pContLogo = CObject2D::Create
	( // ����
		POS_CONT_LOGO,					// �ʒu
		SIZE_CONT_LOGO * SET_CONT_SCALE	// �傫��
	);
	if (m_pContLogo == nullptr)
	{ // �����Ɏ��s�����ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	// �e�N�X�`����o�^�E����
	m_pContLogo->BindTexture(pTexture->Regist(mc_apTextureFile[TEXTURE_CONTINUE]));

	// �D�揇�ʂ�ݒ�
	m_pContLogo->SetPriority(RESULT_PRIO);

	// �`������Ȃ��ݒ�ɂ���
	m_pContLogo->SetEnableDraw(false);

	//--------------------------------------------------------
	//	�R���e�j���[�\���̐����E�ݒ�
	//--------------------------------------------------------
	for (int nCntResult = 0; nCntResult < SELECT_MAX; nCntResult++)
	{ // �I�����̑������J��Ԃ�

		// �R���e�j���[�\���̐���
		m_apContinue[nCntResult] = CObject2D::Create
		( // ����
			aPosContinue[nCntResult],	// �ʒu
			SIZE_CONT * SET_CONT_SCALE	// �傫��
		);
		if (m_apContinue[nCntResult] == nullptr)
		{ // �����Ɏ��s�����ꍇ

			// ���s��Ԃ�
			assert(false);
			return E_FAIL;
		}

		// �D�揇�ʂ�ݒ�
		m_apContinue[nCntResult]->SetPriority(RESULT_PRIO);

		// �`������Ȃ��ݒ�ɂ���
		m_apContinue[nCntResult]->SetEnableDraw(false);

		// �F��ݒ�
		m_apContinue[nCntResult]->SetColor(DEFAULT_COL);
	}

	// �e�N�X�`����o�^�E����
	m_apContinue[SELECT_YES]->BindTexture(pTexture->Regist(mc_apTextureFile[TEXTURE_YES]));
	m_apContinue[SELECT_NO]->BindTexture(pTexture->Regist(mc_apTextureFile[TEXTURE_NO]));

	// ������Ԃ�
	return S_OK;
}

//============================================================
//	�I������
//============================================================
HRESULT CResultManager::Uninit(void)
{
	// �X�R�A�^�C�g���\���̏I��
	m_pScoreTitle->Uninit();

	// �X�R�A�̏I��
	m_pScore->Uninit();

	for (int nCntResult = 0; nCntResult < SELECT_MAX; nCntResult++)
	{ // �I�����̑������J��Ԃ�

		// �R���e�j���[�\���̏I��
		m_apContinue[nCntResult]->Uninit();
	}

	// �R���e�j���[���S�\���̏I��
	m_pContLogo->Uninit();

	// �t�F�[�h�̏I��
	m_pFade->Uninit();

	// ������Ԃ�
	return S_OK;
}

//============================================================
//	�X�V����
//============================================================
void CResultManager::Update(void)
{
	switch (m_state)
	{ // ��Ԃ��Ƃ̏���
	case STATE_NONE:	// �������Ȃ����

		// ����

		break;

	case STATE_FADEIN:	// �t�F�[�h�C�����

		// �t�F�[�h�C���̍X�V
		UpdateFade();

		break;

	case STATE_RESULT:	// ���U���g�\�����

		// ���U���g�\���̍X�V
		UpdateResult();

		break;

	case STATE_CONTINUE_WAIT:	// �R���e�j���[�\���ҋ@���

		// �\���ҋ@�̍X�V
		if (UpdateDrawWait(CONT_WAIT_CNT))
		{ // �ҋ@�����̏ꍇ

			// �R���e�j���[�\���̊g�嗦��ݒ�
			m_fScale = SET_CONT_SCALE;

			// �R���e�j���[���S�\���̕`��J�n
			m_pContLogo->SetEnableDraw(true);
			
			for (int nCntResult = 0; nCntResult < SELECT_MAX; nCntResult++)
			{ // �I�����̑������J��Ԃ�

				// �R���e�j���[�\���̕`��J�n
				m_apContinue[nCntResult]->SetEnableDraw(true);
			}

			// ��Ԃ�ύX
			m_state = STATE_CONTINUE;	// �R���e�j���[�\�����
		}

		break;

	case STATE_CONTINUE:	// �R���e�j���[�\���ҋ@��ԕ\�����

		// �R���e�j���[�\���̍X�V
		UpdateContinue();

		break;

	case STATE_WAIT:	// �J�ڑҋ@���

		// �I���̍X�V
		UpdateSelect();

		break;

	default:	// ��O����
		assert(false);
		break;
	}

	// �J�ڌ���̍X�V
	UpdateTransition();

	// �X�R�A�^�C�g���\���̍X�V
	m_pScoreTitle->Update();

	// �X�R�A�̍X�V
	m_pScore->Update();

	for (int nCntResult = 0; nCntResult < SELECT_MAX; nCntResult++)
	{ // �I�����̑������J��Ԃ�

		// �R���e�j���[�\���̍X�V
		m_apContinue[nCntResult]->Update();
	}

	// �R���e�j���[���S�\���̍X�V
	m_pContLogo->Update();

	// �t�F�[�h�̍X�V
	m_pFade->Update();
}

//============================================================
//	��������
//============================================================
CResultManager *CResultManager::Create(void)
{
	// �|�C���^��錾
	CResultManager *pResultManager = nullptr;	// ���U���g�}�l�[�W���[�����p

	if (pResultManager == nullptr)
	{ // �g�p����Ă��Ȃ��ꍇ

		// �������m��
		pResultManager = new CResultManager;	// ���U���g�}�l�[�W���[
	}
	else { assert(false); return nullptr; }	// �g�p��

	if (pResultManager != nullptr)
	{ // �g�p����Ă���ꍇ
		
		// ���U���g�}�l�[�W���[�̏�����
		if (FAILED(pResultManager->Init()))
		{ // �������Ɏ��s�����ꍇ

			// �������J��
			delete pResultManager;
			pResultManager = nullptr;

			// ���s��Ԃ�
			return nullptr;
		}

		// �m�ۂ����A�h���X��Ԃ�
		return pResultManager;
	}
	else { assert(false); return nullptr; }	// �m�ێ��s
}

//============================================================
//	�j������
//============================================================
HRESULT CResultManager::Release(CResultManager *&prResultManager)
{
	if (prResultManager != nullptr)
	{ // �g�p���̏ꍇ

		// ���U���g�}�l�[�W���[�̏I��
		if (FAILED(prResultManager->Uninit()))
		{ // �j���Ɏ��s�����ꍇ

			// �������J��
			delete prResultManager;
			prResultManager = nullptr;

			// ���s��Ԃ�
			assert(false);
			return E_FAIL;
		}

		// �������J��
		delete prResultManager;
		prResultManager = nullptr;

		// ������Ԃ�
		return S_OK;
	}
	else { assert(false); return E_FAIL; }	// ��g�p��
}

//============================================================
//	�t�F�[�h�C���̍X�V����
//============================================================
void CResultManager::UpdateFade(void)
{
	// �ϐ���錾
	D3DXCOLOR colFade = m_pFade->GetColor();	// �t�F�[�h�̐F

	if (colFade.a < SETCOL_FADE.a)
	{ // �����ʂ��ݒ�l�����̏ꍇ

		// �����x�����Z
		colFade.a += ADD_ALPHA;
	}
	else
	{ // �����ʂ��ݒ�l�ȏ�̏ꍇ

		// �����x��␳
		colFade.a = SETCOL_FADE.a;

		// �X�R�A�^�C�g���\���̕`��J�n
		m_pScoreTitle->SetEnableDraw(true);

		// �X�R�A�̕`��J�n
		m_pScore->SetEnableDraw(true);

		// ���U���g�\���̊g�嗦��ݒ�
		m_fScale = SET_RESULT_SCALE;

		// ��Ԃ�ύX
		m_state = STATE_RESULT;	// ���U���g�\�����
	}

	// �����x�𔽉f
	m_pFade->SetColor(colFade);
}

//============================================================
//	���U���g�\���̍X�V����
//============================================================
void CResultManager::UpdateResult(void)
{
	if (m_fScale > 1.0f)
	{ // �g�嗦���ŏ��l���傫���ꍇ

		// �g�嗦�����Z
		m_fScale -= SUB_RESULT_SCALE;

		// �X�R�A�^�C�g���\���̑傫����ݒ�
		m_pScoreTitle->SetVec3Sizing(SIZE_RESULT * m_fScale);

		// �X�R�A�̑傫����ݒ�
		m_pScore->SetVec3Sizing(SIZE_VALUE * m_fScale);
	}
	else
	{ // �g�嗦���ŏ��l�ȉ��̏ꍇ

		// �X�R�A�^�C�g���\���̑傫����ݒ�
		m_pScoreTitle->SetVec3Sizing(SIZE_RESULT);

		// �X�R�A�̑傫����ݒ�
		m_pScore->SetVec3Sizing(SIZE_VALUE);

		// ��Ԃ�ύX
		m_state = STATE_CONTINUE_WAIT;	// �R���e�j���[�\���ҋ@���

		// �T�E���h�̍Đ�
		GET_MANAGER->GetSound()->Play(CSound::LABEL_SE_DECISION_001);	// ���艹01
	}
}

//============================================================
//	�R���e�j���[�\������
//============================================================
void CResultManager::UpdateContinue(void)
{
	if (m_fScale > 1.0f)
	{ // �g�嗦���ŏ��l���傫���ꍇ

		// �g�嗦�����Z
		m_fScale -= SUB_CONT_SCALE;

		// �R���e�j���[���S�\���̑傫����ݒ�
		m_pContLogo->SetVec3Sizing(SIZE_CONT_LOGO * m_fScale);

		for (int nCntResult = 0; nCntResult < SELECT_MAX; nCntResult++)
		{ // �I�����̑������J��Ԃ�

			// �R���e�j���[�\���̑傫����ݒ�
			m_apContinue[nCntResult]->SetVec3Sizing(SIZE_CONT * m_fScale);
		}
	}
	else
	{ // �g�嗦���ŏ��l�ȉ��̏ꍇ

		// �g�嗦��␳
		m_fScale = 1.0f;

		// �R���e�j���[���S�\���̑傫����ݒ�
		m_pContLogo->SetVec3Sizing(SIZE_CONT_LOGO);

		for (int nCntResult = 0; nCntResult < SELECT_MAX; nCntResult++)
		{ // �I�����̑������J��Ԃ�

			// �R���e�j���[�\���̑傫����ݒ�
			m_apContinue[nCntResult]->SetVec3Sizing(SIZE_CONT);
		}

		// ��Ԃ�ύX
		m_state = STATE_WAIT;	// �J�ڑҋ@���

		// �T�E���h�̍Đ�
		GET_MANAGER->GetSound()->Play(CSound::LABEL_SE_DECISION_001);	// ���艹01
	}
}

//============================================================
//	�I���̍X�V����
//============================================================
void CResultManager::UpdateSelect(void)
{
	// �|�C���^��錾
	CInputKeyboard	*pKeyboard	= GET_INPUTKEY;	// �L�[�{�[�h
	CInputPad		*pPad		= GET_INPUTPAD;		// �p�b�h

	if (pKeyboard->IsTrigger(DIK_A)
	||  pKeyboard->IsTrigger(DIK_LEFT)
	||  pPad->IsTrigger(CInputPad::KEY_LEFT))
	{ // ���ړ��̑��삪�s��ꂽ�ꍇ

		// ���ɑI�������炷
		m_nSelect = (m_nSelect + (SELECT_MAX - 1)) % SELECT_MAX;

		// �T�E���h�̍Đ�
		GET_MANAGER->GetSound()->Play(CSound::LABEL_SE_SELECT_000);	// �I�𑀍쉹00
	}
	if (pKeyboard->IsTrigger(DIK_D)
	||  pKeyboard->IsTrigger(DIK_RIGHT)
	||  pPad->IsTrigger(CInputPad::KEY_RIGHT))
	{ // �E�ړ��̑��삪�s��ꂽ�ꍇ

		// �E�ɑI�������炷
		m_nSelect = (m_nSelect + 1) % SELECT_MAX;

		// �T�E���h�̍Đ�
		GET_MANAGER->GetSound()->Play(CSound::LABEL_SE_SELECT_000);	// �I�𑀍쉹00
	}

	// �O��̑I��v�f�̐F�����ɐݒ�
	m_apContinue[m_nOldSelect]->SetColor(DEFAULT_COL);

	// ���݂̑I��v�f�̐F�𔒂ɐݒ�
	m_apContinue[m_nSelect]->SetColor(CHOICE_COL);

	// ���݂̑I��v�f����
	m_nOldSelect = m_nSelect;
}

//============================================================
//	�J�ڌ���̍X�V����
//============================================================
void CResultManager::UpdateTransition(void)
{
	// �|�C���^��錾
	CInputKeyboard	*pKeyboard	= GET_INPUTKEY;	// �L�[�{�[�h
	CInputPad		*pPad		= GET_INPUTPAD;		// �p�b�h

	if (pKeyboard->IsTrigger(DIK_RETURN)
	||  pKeyboard->IsTrigger(DIK_SPACE)
	||  pPad->IsTrigger(CInputPad::KEY_A)
	||  pPad->IsTrigger(CInputPad::KEY_B)
	||  pPad->IsTrigger(CInputPad::KEY_X)
	||  pPad->IsTrigger(CInputPad::KEY_Y)
	||  pPad->IsTrigger(CInputPad::KEY_START))
	{
		if (m_state != STATE_WAIT)
		{ // �J�ڑҋ@��Ԃł͂Ȃ��ꍇ

			// ���o�X�L�b�v
			SkipStaging();

			// �T�E���h�̍Đ�
			GET_MANAGER->GetSound()->Play(CSound::LABEL_SE_DECISION_001);	// ���艹01
		}
		else
		{ // �J�ڑҋ@��Ԃ̏ꍇ

			if (GET_MANAGER->GetFade()->GetState() == CFade::FADE_NONE)
			{ // �t�F�[�h���ł͂Ȃ��ꍇ

				switch (m_nSelect)
				{ // �I�����Ƃ̏���
				case SELECT_YES:

					// �V�[���̐ݒ�
					GET_MANAGER->SetScene(CScene::MODE_GAME);	// �Q�[�����

					break;

				case SELECT_NO:

					// �V�[���̐ݒ�
					GET_MANAGER->SetScene(CScene::MODE_RANKING);	// �����L���O���

					break;
				}

				// �T�E���h�̍Đ�
				GET_MANAGER->GetSound()->Play(CSound::LABEL_SE_DECISION_000);	// ���艹00
			}
		}
	}
}

//============================================================
//	���o�X�L�b�v����
//============================================================
void CResultManager::SkipStaging(void)
{
	// ���U���g�\���̕`���ON�ɂ��A�傫����ݒ�
	// �X�R�A�^�C�g���\���̕`��J�n
	m_pScoreTitle->SetEnableDraw(true);

	// �X�R�A�̕`��J�n
	m_pScore->SetEnableDraw(true);

	// �X�R�A�^�C�g���\���̑傫����ݒ�
	m_pScoreTitle->SetVec3Sizing(SIZE_RESULT);

	// �X�R�A�̑傫����ݒ�
	m_pScore->SetVec3Sizing(SIZE_VALUE);

	// �R���e�j���[���S�\���̕`��J�n
	m_pContLogo->SetEnableDraw(true);

	// �R���e�j���[���S�\���̑傫����ݒ�
	m_pContLogo->SetVec3Sizing(SIZE_CONT_LOGO);

	for (int nCntResult = 0; nCntResult < SELECT_MAX; nCntResult++)
	{ // �I�����̑������J��Ԃ�

		// �R���e�j���[�\���̕`��J�n
		m_apContinue[nCntResult]->SetEnableDraw(true);

		// �R���e�j���[�\���̑傫����ݒ�
		m_apContinue[nCntResult]->SetVec3Sizing(SIZE_CONT);
	}

	// �t�F�[�h�̓����x��ݒ�
	m_pFade->SetColor(SETCOL_FADE);

	// ��Ԃ�ύX
	m_state = STATE_WAIT;	// �J�ڑҋ@���
}

//============================================================
//	�\���ҋ@����
//============================================================
bool CResultManager::UpdateDrawWait(const int nWait)
{
	if (m_nCounterState < nWait)
	{ // �J�E���^�[���ҋ@�J�E���g�܂ŒB���Ă��Ȃ��ꍇ

		// �J�E���^�[�����Z
		m_nCounterState++;

		// �ҋ@��������Ԃ�
		return false;
	}
	else
	{ // �J�E���^�[���ҋ@���������ꍇ

		// �J�E���^�[��������
		m_nCounterState = 0;

		// �ҋ@������Ԃ�
		return true;
	}
}
