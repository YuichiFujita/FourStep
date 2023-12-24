//============================================================
//
//	���f��UI���� [modelUI.cpp]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "modelUI.h"
#include "manager.h"
#include "renderer.h"
#include "camera.h"
#include "model.h"

//************************************************************
//	�}�N����`
//************************************************************
#define MODEL_UI_PRIO	(14)	// ���f��UI�\���̗D�揇��

//************************************************************
//	�q�N���X [CModelUI] �̃����o�֐�
//************************************************************
//============================================================
//	�R���X�g���N�^
//============================================================
CModelUI::CModelUI() : CObjectModel(CObject::LABEL_NONE, MODEL_UI_PRIO)
{

}

//============================================================
//	�f�X�g���N�^
//============================================================
CModelUI::~CModelUI()
{

}

//============================================================
//	����������
//============================================================
HRESULT CModelUI::Init(void)
{
	// �I�u�W�F�N�g���f���̏�����
	if (FAILED(CObjectModel::Init()))
	{ // �������Ɏ��s�����ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	// ������Ԃ�
	return S_OK;
}

//============================================================
//	�I������
//============================================================
void CModelUI::Uninit(void)
{
	// �I�u�W�F�N�g���f���̏I��
	CObjectModel::Uninit();
}

//============================================================
//	�X�V����
//============================================================
void CModelUI::Update(void)
{
	// �I�u�W�F�N�g���f���̍X�V
	CObjectModel::Update();
}

//============================================================
//	�`�揈��
//============================================================
void CModelUI::Draw(void)
{
	// �ϐ���錾
	D3DVIEWPORT9 viewportDef;	// �J�����̃r���[�|�[�g�ۑ��p

	// �|�C���^��錾
	LPDIRECT3DDEVICE9 pDevice = GET_DEVICE;	// �f�o�C�X�̃|�C���^

	// ���݂̃r���[�|�[�g���擾
	pDevice->GetViewport(&viewportDef);

	// �J�����̐ݒ�
	GET_MANAGER->GetCamera()->SetCamera(CCamera::TYPE_MODELUI);

	// �I�u�W�F�N�g���f���̕`��
	CObjectModel::Draw();

	// �J�����̐ݒ�����ɖ߂�
	GET_MANAGER->GetCamera()->SetCamera(CCamera::TYPE_MAIN);

	// �r���[�|�[�g�����ɖ߂�
	pDevice->SetViewport(&viewportDef);
}

//============================================================
//	��������
//============================================================
CModelUI *CModelUI::Create
( // ����
	const D3DXVECTOR3& rPos,	// �ʒu
	const D3DXVECTOR3& rRot,	// ����
	const D3DXVECTOR3& rScale	// �傫��
)
{
	// �|�C���^��錾
	CModelUI *pModelUI = nullptr;	// ���f��UI�����p

	if (pModelUI == nullptr)
	{ // �g�p����Ă��Ȃ��ꍇ

		// �������m��
		pModelUI = new CModelUI;	// ���f��UI
	}
	else { assert(false); return nullptr; }	// �g�p��

	if (pModelUI != nullptr)
	{ // �g�p����Ă���ꍇ
		
		// ���f��UI�̏�����
		if (FAILED(pModelUI->Init()))
		{ // �������Ɏ��s�����ꍇ

			// �������J��
			delete pModelUI;
			pModelUI = nullptr;

			// ���s��Ԃ�
			return nullptr;
		}

		// �ʒu��ݒ�
		pModelUI->SetVec3Position(rPos);

		// ������ݒ�
		pModelUI->SetVec3Rotation(rRot);

		// �g�嗦��ݒ�
		pModelUI->SetVec3Scaling(rScale);

		// �m�ۂ����A�h���X��Ԃ�
		return pModelUI;
	}
	else { assert(false); return nullptr; }	// �m�ێ��s
}
