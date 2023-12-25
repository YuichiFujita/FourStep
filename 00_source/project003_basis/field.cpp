//============================================================
//
//	�n�ʏ��� [field.cpp]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "field.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"

//************************************************************
//	�}�N����`
//************************************************************
#define FIELD_SETUP_TXT	"data\\TXT\\field.txt"	// �Z�b�g�A�b�v�e�L�X�g���΃p�X

#define FIELD_PRIO	(0)	// �n�ʂ̗D�揇��

//************************************************************
//	�ÓI�����o�ϐ��錾
//************************************************************
const char *CField::mc_apTextureFile[] =	// �e�N�X�`���萔
{
	"data\\TEXTURE\\field.jpg",	// �����e�N�X�`��
};
CField::STerrainInfo CField::m_aTerrainInfo[TERRAIN_MAX] = {};	// �n�`���

//************************************************************
//	�q�N���X [CField] �̃����o�֐�
//************************************************************
//============================================================
//	�R���X�g���N�^
//============================================================
CField::CField() : CObjectMeshField(CObject::LABEL_FIELD, FIELD_PRIO)
{

}

//============================================================
//	�f�X�g���N�^
//============================================================
CField::~CField()
{

}

//============================================================
//	����������
//============================================================
HRESULT CField::Init(void)
{
	// �I�u�W�F�N�g���b�V���t�B�[���h�̏�����
	if (FAILED(CObjectMeshField::Init()))
	{ // �������Ɏ��s�����ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	// �Z�b�g�A�b�v�̓Ǎ�
	LoadSetup();

	// ������Ԃ�
	return S_OK;
}

//============================================================
//	�I������
//============================================================
void CField::Uninit(void)
{
	// �I�u�W�F�N�g���b�V���t�B�[���h�̏I��
	CObjectMeshField::Uninit();

	// �n�`���̔j��
	for (int nCntField = 0; nCntField < TERRAIN_MAX; nCntField++)
	{ // �n�`���̍ő吔���J��Ԃ�

		if (m_aTerrainInfo[nCntField].pPosGap != nullptr)
		{ // ���_���W�̂���ʏ�񂪎g�p���̏ꍇ

			// �������J��
			delete[] m_aTerrainInfo[nCntField].pPosGap;
			m_aTerrainInfo[nCntField].pPosGap = nullptr;
		}
	}
}

//============================================================
//	�X�V����
//============================================================
void CField::Update(void)
{
	// �I�u�W�F�N�g���b�V���t�B�[���h�̍X�V
	CObjectMeshField::Update();
}

//============================================================
//	�`�揈��
//============================================================
void CField::Draw(void)
{
	// �I�u�W�F�N�g���b�V���t�B�[���h�̕`��
	CObjectMeshField::Draw();
}

//============================================================
//	��������
//============================================================
CField *CField::Create
(
	const ETexture texture,		// ���
	const D3DXVECTOR3& rPos,	// �ʒu
	const D3DXVECTOR3& rRot,	// ����
	const D3DXVECTOR2& rSize,	// �傫��
	const D3DXCOLOR& rCol,		// �F
	const POSGRID2& rPart,		// ������
	const D3DCULL cull,			// �J�����O��
	const bool bLight			// ���C�e�B���O��
)
{
	// �ϐ���錾
	int nTextureID;	// �e�N�X�`���C���f�b�N�X

	// �|�C���^��錾
	CTexture *pTexture = GET_MANAGER->GetTexture();	// �e�N�X�`���ւ̃|�C���^
	CField *pField = nullptr;	// �n�ʐ����p

	if (pField == nullptr)
	{ // �g�p����Ă��Ȃ��ꍇ

		// �������m��
		pField = new CField;	// �n��
	}
	else { assert(false); return nullptr; }	// �g�p��

	if (pField != nullptr)
	{ // �m�ۂɐ������Ă���ꍇ

		// �n�ʂ̏�����
		if (FAILED(pField->Init()))
		{ // �������Ɏ��s�����ꍇ

			// �������J��
			delete pField;
			pField = nullptr;

			// ���s��Ԃ�
			return nullptr;
		}

		// �e�N�X�`����o�^
		nTextureID = pTexture->Regist(mc_apTextureFile[texture]);

		// �e�N�X�`��������
		pField->BindTexture(nTextureID);

		// �ʒu��ݒ�
		pField->SetVec3Position(rPos);

		// ������ݒ�
		pField->SetVec3Rotation(rRot);

		// �傫����ݒ�
		pField->SetVec2Sizing(rSize);

		// �F��ݒ�
		pField->SetColor(rCol);

		// �J�����O��ݒ�
		pField->SetCulling(cull);

		// ���C�e�B���O��ݒ�
		pField->SetLighting(bLight);

		// ��������ݒ�
		if (FAILED(pField->SetPattern(rPart)))
		{ // �������̐ݒ�Ɏ��s�����ꍇ

			// �������J��
			delete pField;
			pField = nullptr;

			// ���s��Ԃ�
			return nullptr;
		}

		// �m�ۂ����A�h���X��Ԃ�
		return pField;
	}
	else { assert(false); return nullptr; }	// �m�ێ��s
}

//============================================================
//	�n�`�̐ݒ菈��
//============================================================
void CField::SetTerrain(const ETerrain terrain)
{
	if (terrain < TERRAIN_MAX)
	{ // �l���͈͓��̏ꍇ

		// �n�`��ݒ�
		CObjectMeshField::SetTerrain(m_aTerrainInfo[terrain].part, m_aTerrainInfo[terrain].pPosGap);
	}
	else { assert(false); }	// �͈͊O
}

//============================================================
//	�Z�b�g�A�b�v����
//============================================================
void CField::LoadSetup(void)
{
	// �ϐ���錾
	int nID = 0;		// �C���f�b�N�X�̑���p
	int nNumVtx = 0;	// ���_���̑���p
	int nEnd = 0;		// �e�L�X�g�ǂݍ��ݏI���̊m�F�p

	// �ϐ��z���錾
	char aString[MAX_STRING];	// �e�L�X�g�̕�����̑���p

	// �|�C���^��錾
	FILE *pFile;	// �t�@�C���|�C���^

	// �n�`���̔j��
	for (int nCntField = 0; nCntField < TERRAIN_MAX; nCntField++)
	{ // �n�`���̍ő吔���J��Ԃ�

		if (m_aTerrainInfo[nCntField].pPosGap != nullptr)
		{ // ���_���W�̂���ʏ�񂪎g�p���̏ꍇ

			// �������J��
			delete[] m_aTerrainInfo[nCntField].pPosGap;
			m_aTerrainInfo[nCntField].pPosGap = nullptr;
		}
	}

	// �ÓI�����o�ϐ��̏����N���A
	memset(&m_aTerrainInfo[0], 0, sizeof(m_aTerrainInfo));	// �n�`���

	// �t�@�C����ǂݍ��݌`���ŊJ��
	pFile = fopen(FIELD_SETUP_TXT, "r");

	if (pFile != nullptr)
	{ // �t�@�C�����J�����ꍇ

		do
		{ // �ǂݍ��񂾕����� EOF �ł͂Ȃ��ꍇ���[�v

			// �t�@�C�����當�����ǂݍ���
			nEnd = fscanf(pFile, "%s", &aString[0]);	// �e�L�X�g��ǂݍ��݂������� EOF ��Ԃ�

			// �n�`�̐ݒ�
			if (strcmp(&aString[0], "TERRAINSET") == 0)
			{ // �ǂݍ��񂾕����� TERRAINSET �̏ꍇ

				do
				{ // �ǂݍ��񂾕����� END_TERRAINSET �ł͂Ȃ��ꍇ���[�v

					// �t�@�C�����當�����ǂݍ���
					fscanf(pFile, "%s", &aString[0]);

					if (strcmp(&aString[0], "FIELDSET") == 0)
					{ // �ǂݍ��񂾕����� FIELDSET �̏ꍇ

						do
						{ // �ǂݍ��񂾕����� END_FIELDSET �ł͂Ȃ��ꍇ���[�v

							// �t�@�C�����當�����ǂݍ���
							fscanf(pFile, "%s", &aString[0]);

							if (strcmp(&aString[0], "PART") == 0)
							{ // �ǂݍ��񂾕����� PART �̏ꍇ

								fscanf(pFile, "%s", &aString[0]);					// = ��ǂݍ��� (�s�v)
								fscanf(pFile, "%d", &m_aTerrainInfo[nID].part.x);	// ������X��ǂݍ���
								fscanf(pFile, "%d", &m_aTerrainInfo[nID].part.y);	// ������Y��ǂݍ���

								// ���_����ݒ�
								nNumVtx = (m_aTerrainInfo[nID].part.x + 1) * (m_aTerrainInfo[nID].part.y + 1);

								if (m_aTerrainInfo[nID].pPosGap == nullptr)
								{ // �|�C���^���g�p����Ă��Ȃ��ꍇ

									// ���_�����������m��
									m_aTerrainInfo[nID].pPosGap = new D3DXVECTOR3[nNumVtx];

									// ��O����
									assert(m_aTerrainInfo[nID].pPosGap != nullptr);	// ��g�p��
								}
								else { assert(false); }	// �g�p��
							}
							else if (strcmp(&aString[0], "GAPSET") == 0)
							{ // �ǂݍ��񂾕����� GAPSET �̏ꍇ

								for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
								{ // ���_�����J��Ԃ�

									fscanf(pFile, "%f", &m_aTerrainInfo[nID].pPosGap[nCntVtx].x);	// ���_���W�̂����X��ǂݍ���
									fscanf(pFile, "%f", &m_aTerrainInfo[nID].pPosGap[nCntVtx].y);	// ���_���W�̂����Y��ǂݍ���
									fscanf(pFile, "%f", &m_aTerrainInfo[nID].pPosGap[nCntVtx].z);	// ���_���W�̂����Z��ǂݍ���
									fscanf(pFile, "%s", &aString[0]);								// , ��ǂݍ��� (�s�v)
								}
							}
						} while (strcmp(&aString[0], "END_FIELDSET") != 0);	// �ǂݍ��񂾕����� END_FIELDSET �ł͂Ȃ��ꍇ���[�v

						// �C���f�b�N�X�����Z
						nID++;
					}
				} while (strcmp(&aString[0], "END_TERRAINSET") != 0);	// �ǂݍ��񂾕����� END_TERRAINSET �ł͂Ȃ��ꍇ���[�v
			}
		} while (nEnd != EOF);	// �ǂݍ��񂾕����� EOF �ł͂Ȃ��ꍇ���[�v
		
		// �t�@�C�������
		fclose(pFile);
	}
	else
	{ // �t�@�C�����J���Ȃ������ꍇ

		// �G���[���b�Z�[�W�{�b�N�X
		MessageBox(nullptr, "�n�ʃZ�b�g�A�b�v�̓ǂݍ��݂Ɏ��s�I", "�x���I", MB_ICONWARNING);
	}
}