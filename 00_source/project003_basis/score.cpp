//============================================================
//
//	�X�R�A���� [score.cpp]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "score.h"
#include "manager.h"
#include "renderer.h"
#include "modelUI.h"

//************************************************************
//	�萔�錾
//************************************************************
namespace
{
	const char *MODEL_FILE[] =	// �������f��
	{
		"data\\MODEL\\SCORE\\suuji_0.x",
		"data\\MODEL\\SCORE\\suuji_1.x",
		"data\\MODEL\\SCORE\\suuji_2.x",
		"data\\MODEL\\SCORE\\suuji_3.x",
		"data\\MODEL\\SCORE\\suuji_4.x",
		"data\\MODEL\\SCORE\\suuji_5.x",
		"data\\MODEL\\SCORE\\suuji_6.x",
		"data\\MODEL\\SCORE\\suuji_7.x",
		"data\\MODEL\\SCORE\\suuji_8.x",
		"data\\MODEL\\SCORE\\suuji_9.x",
	};
}

//************************************************************
//	�}�N����`
//************************************************************
#define SCORE_PRIO	(12)	// �X�R�A�̗D�揇��

#define SCO_NUMMIN	(0)		// �ŏ��X�R�A
#define SCO_NUMMAX	(999)	// �ő�X�R�A

//************************************************************
//	�q�N���X [CScore] �̃����o�֐�
//************************************************************
//============================================================
//	�R���X�g���N�^
//============================================================
CScore::CScore() : CObject(CObject::LABEL_UI, SCORE_PRIO)
{
	// �����o�ϐ����N���A
	memset(&m_apValue[0], 0, sizeof(m_apValue));	// ���l�̏��
	m_pos	= VEC3_ZERO;	// �ʒu
	m_scale	= VEC3_ZERO;	// �傫��
	m_space	= VEC3_ZERO;	// ��
	m_nNum	= 0;			// �X�R�A
}

//============================================================
//	�f�X�g���N�^
//============================================================
CScore::~CScore()
{

}

//============================================================
//	����������
//============================================================
HRESULT CScore::Init(void)
{
	// �����o�ϐ���������
	memset(&m_apValue[0], 0, sizeof(m_apValue));	// ���l�̏��
	m_pos	= VEC3_ZERO;	// �ʒu
	m_scale	= VEC3_ZERO;	// �傫��
	m_space	= VEC3_ZERO;	// ��
	m_nNum	= 0;			// �X�R�A

	for (int nCntScore = 0; nCntScore < MAX_SCORE; nCntScore++)
	{ // �X�R�A�̌������J��Ԃ�

		// �����̐���
		m_apValue[nCntScore] = CModelUI::Create(VEC3_ZERO);
		if (m_apValue[nCntScore] == nullptr)
		{ // �����Ɏ��s�����ꍇ

			// ���s��Ԃ�
			assert(false);
			return E_FAIL;
		}

		// �D�揇�ʂ�ݒ�
		m_apValue[nCntScore]->SetPriority(SCORE_PRIO);
	}

	// ������Ԃ�
	return S_OK;
}

//============================================================
//	�I������
//============================================================
void CScore::Uninit(void)
{
	// �����I�u�W�F�N�g��j��
	for (int nCntScore = 0; nCntScore < MAX_SCORE; nCntScore++)
	{ // �X�R�A�̌������J��Ԃ�

		// �����̏I��
		m_apValue[nCntScore]->Uninit();
	}

	// ���g�̃I�u�W�F�N�g��j��
	Release();
}

//============================================================
//	�X�V����
//============================================================
void CScore::Update(void)
{
	for (int nCntScore = 0; nCntScore < MAX_SCORE; nCntScore++)
	{ // �X�R�A�̌������J��Ԃ�

		// �����̍X�V
		m_apValue[nCntScore]->Update();
	}
}

//============================================================
//	�`�揈��
//============================================================
void CScore::Draw(void)
{

}

//============================================================
//	��������
//============================================================
CScore *CScore::Create
(
	const D3DXVECTOR3& rPos,	// �ʒu
	const D3DXVECTOR3& rScale,	// �傫��
	const D3DXVECTOR3& rSpace	// ��
)
{
	// �|�C���^��錾
	CScore *pScore = NULL;		// �X�R�A�����p

	if (pScore == nullptr)
	{ // �g�p����Ă��Ȃ��ꍇ

		// �������m��
		pScore = new CScore;	// �X�R�A
	}
	else { assert(false); return NULL; }	// �g�p��

	if (pScore != nullptr)
	{ // �m�ۂɐ������Ă���ꍇ

		// �X�R�A�̏�����
		if (FAILED(pScore->Init()))
		{ // �������Ɏ��s�����ꍇ

			// �������J��
			delete pScore;
			pScore = NULL;

			// ���s��Ԃ�
			return NULL;
		}

		// �ʒu��ݒ�
		pScore->SetVec3Position(rPos);

		// �傫����ݒ�
		pScore->SetVec3Scaling(rScale);

		// �󔒂�ݒ�
		pScore->SetSpace(rSpace);

		// �m�ۂ����A�h���X��Ԃ�
		return pScore;
	}
	else { assert(false); return NULL; }	// �m�ێ��s
}

//============================================================
//	���Z����
//============================================================
void CScore::Add(const int nNum)
{
	// �X�R�A�����������Z
	m_nNum += nNum;

	// �X�R�A�̕␳
	useful::LimitNum(m_nNum, SCO_NUMMIN, SCO_NUMMAX);

	// �����̃e�N�X�`�����W�̐ݒ�
	SetTexNum();
}

//============================================================
//	�ݒ菈��
//============================================================
void CScore::Set(const int nNum)
{
	// �X�R�A�������̒l�ɐݒ�
	m_nNum = nNum;

	// �X�R�A�̕␳
	useful::LimitNum(m_nNum, SCO_NUMMIN, SCO_NUMMAX);

	// �����̃e�N�X�`�����W�̐ݒ�
	SetTexNum();
}

//============================================================
//	�擾����
//============================================================
int CScore::Get(void)
{
	// �X�R�A�̒l��Ԃ�
	return m_nNum;
}

//============================================================
//	�ʒu�̐ݒ菈��
//============================================================
void CScore::SetVec3Position(const D3DXVECTOR3& rPos)
{
	// �����̈ʒu��ݒ�
	m_pos = rPos;

	// �����̕\���ݒ�
	SetDrawValue();
}

//============================================================
//	�傫���̐ݒ菈��
//============================================================
void CScore::SetVec3Scaling(const D3DXVECTOR3& rScale)
{
	// �����̊g�嗦��ݒ�
	m_scale = rScale;

	// �����̕\���ݒ�
	SetDrawValue();
}

//============================================================
//	�󔒂̐ݒ菈��
//============================================================
void CScore::SetSpace(const D3DXVECTOR3& rSpace)
{
	// �����̋󔒂�ݒ�
	m_space = rSpace;

	// �����̕\���ݒ�
	SetDrawValue();
}

//============================================================
//	�D�揇�ʂ̐ݒ菈��
//============================================================
void CScore::SetPriority(const int nPriority)
{
	// ���g�̗D�揇�ʂ�ݒ�
	CObject::SetPriority(nPriority);

	if (m_apValue[0] != nullptr)
	{ // �X�R�A�̐擪�̐��l���g�p����Ă���ꍇ

		// �����I�u�W�F�N�g�̗D�揇�ʂ�ݒ�
		for (int nCntScore = 0; nCntScore < MAX_SCORE; nCntScore++)
		{ // �X�R�A�̌������J��Ԃ�

			m_apValue[nCntScore]->SetPriority(nPriority);
		}
	}
	else { assert(false); }	// ��g�p��
}

//============================================================
//	�X�V�󋵂̐ݒ菈��
//============================================================
void CScore::SetEnableUpdate(const bool bUpdate)
{
	// ���g�̍X�V�󋵂�ݒ�
	CObject::SetEnableUpdate(bUpdate);

	if (m_apValue[0] != nullptr)
	{ // �X�R�A�̐擪�̐��l���g�p����Ă���ꍇ

		// �����I�u�W�F�N�g�̍X�V�󋵂�ݒ�
		for (int nCntScore = 0; nCntScore < MAX_SCORE; nCntScore++)
		{ // �X�R�A�̌������J��Ԃ�

			m_apValue[nCntScore]->SetEnableUpdate(bUpdate);
		}
	}
	else { assert(false); }	// ��g�p��
}

//============================================================
//	�`��󋵂̐ݒ菈��
//============================================================
void CScore::SetEnableDraw(const bool bDraw)
{
	// ���g�̕`��󋵂�ݒ�
	CObject::SetEnableDraw(bDraw);

	if (m_apValue[0] != nullptr)
	{ // �X�R�A�̐擪�̐��l���g�p����Ă���ꍇ

		// �����I�u�W�F�N�g�̕`��󋵂�ݒ�
		for (int nCntScore = 0; nCntScore < MAX_SCORE; nCntScore++)
		{ // �X�R�A�̌������J��Ԃ�

			m_apValue[nCntScore]->SetEnableDraw(bDraw);
		}
	}
	else { assert(false); }	// ��g�p��
}

//============================================================
//	�ʒu�擾����
//============================================================
D3DXVECTOR3 CScore::GetVec3Position(void) const
{
	// �ʒu��Ԃ�
	return m_pos;
}

//============================================================
//	�傫���擾����
//============================================================
D3DXVECTOR3 CScore::GetVec3Scaling(void) const
{
	// �g�嗦��Ԃ�
	return m_scale;
}

//============================================================
//	�󔒎擾����
//============================================================
D3DXVECTOR3 CScore::GetSpace(void) const
{
	// �󔒂�Ԃ�
	return m_space;
}

//============================================================
//	�j������
//============================================================
void CScore::Release(void)
{
	// �I�u�W�F�N�g�̔j��
	CObject::Release();
}

//============================================================
//	�����̕\���ݒ菈��
//============================================================
void CScore::SetDrawValue(void)
{
	if (m_apValue[0] != nullptr)
	{ // �X�R�A�̐擪�̐��l���g�p����Ă���ꍇ

		for (int nCntScore = 0; nCntScore < MAX_SCORE; nCntScore++)
		{ // �X�R�A�̌������J��Ԃ�

			// �����̈ʒu��ݒ�
			m_apValue[nCntScore]->SetVec3Position(m_pos + (m_space * (float)nCntScore));

			// �����̑傫����ݒ�
			m_apValue[nCntScore]->SetVec3Scaling(m_scale);
		}
	}
	else { assert(false); }	// ��g�p��
}

//============================================================
//	�����̃e�N�X�`�����W�̐ݒ菈��
//============================================================
void CScore::SetTexNum(void)
{
	// �ϐ���錾
	int aNumDivide[MAX_SCORE];	// �������Ƃ̕���p

	// �X�R�A���������Ƃɕ���
	useful::DivideDigitNum
	( // ����
		&aNumDivide[0],	// �������ʂ̊i�[�z��
		m_nNum,			// �������鐔�l
		MAX_SCORE		// �������鐔���̌���
	);

	for (int nCntScore = 0; nCntScore < MAX_SCORE; nCntScore++)
	{ // �X�R�A�̌������J��Ԃ�

		// �����̐ݒ�
		m_apValue[nCntScore]->BindModel(MODEL_FILE[aNumDivide[nCntScore]]);
	}
}
