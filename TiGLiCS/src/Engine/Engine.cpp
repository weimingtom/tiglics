#include "TiGLiCSAll.h"
#include <cstring>
#include <typeinfo>

using namespace TiGLiCS;

float TiGLiCS::drand(void){
	//���܂萸�x�͍����Ȃ����A�Q�[���Ɏg���Ȃ�\��
	return (float)rand()/((float)RAND_MAX+1);
}
float TiGLiCS::drand(float min,float max){
	return (float)(min+(max-min)*rand()/((float)RAND_MAX+1));
}
CEngine * CEngine::Instance=new CEngine();
bool CEngine::Init(const char * Title,Selene::eFrameRate FrameRate,bool DrawDebugTitle,
				 Sint32 ScreenWidth,Sint32 ScreenHeight,bool isFullScreen,
				 const char * RootPath,const char * CurrentPath,bool isDebugMode){
	//----------------------------------------------------------------------------
	// �V�X�e���̏�����
	//----------------------------------------------------------------------------
	// Selene�̃V�X�e�������������Ă��܂��B
	// �N�����ɕK���Ăяo���Ă��������B
	System::Initialize();

	//----------------------------------------------------------------------------
	// �R�A�̐���
	//----------------------------------------------------------------------------
	// �V�X�e������ICore�C���^�[�t�F�C�X���擾���Ă��܂��B
	// �A�v���P�[�V�����E�B���h�E�Ɋւ���C���^�[�t�F�C�X�ł���A
	// �V�X�e�����ɂP�������݂��܂��B
	pCore = System::CreateCore();
	
	//----------------------------------------------------------------------------
	// ������
	//----------------------------------------------------------------------------
	// ICore�C���^�[�t�F�C�X�̏��������s���܂��B
	// �A�v���P�[�V�����E�B���h�E�Ɋւ��Ă̊e�평�������s���܂��B
	if (!pCore->Initialize(Title, FrameRate ) )
		goto EXIT;
	pCore->SetBenchMode(isDebugMode);
	//-----------------------------------------------------------------
	// �^�C�g���o�[�ɏ���\��
	//-----------------------------------------------------------------
	pCore->EnableDrawTitleInformation( DrawDebugTitle );

	//-----------------------------------------------------------------
	// �E�B���h�E�쐬
	//-----------------------------------------------------------------
	// ICore�C���^�[�t�F�C�X���̏��ɏ]���ăA�v���P�[�V����
	// �E�B���h�E�𐶐����܂��B
	// IGraphicCard����̏������ɉ�ʉ𑜓x�Ȃǂ�ύX����ꍇ�́A
	// ICore::Start()���Ăяo���O�ɍs���Ă��������B
	pCore->Start( ScreenWidth, ScreenHeight, true );
	
	//-----------------------------------------------------------------
	// �O���t�B�b�N�J�[�h���擾
	//-----------------------------------------------------------------
	// �O���t�B�b�N�J�[�h�Ɋւ��Ă̏��������s���܂��B
	// IGraphicCard�C���^�[�t�F�C�X����͐ڑ����ꂽ
	// �O���t�B�b�N�J�[�h�̔\�͂��擾���鎖���\�ł��B
	// IGraphicCard�C���^�[�t�F�C�X��1��ICore�C���^�[�t�F�C�X�ɑ΂���1�������݂��܂���B
	pGraphicCard = pCore->CreateGraphicCard( GRAPHIC_CARD_DEFAULT_NO );
	if ( pGraphicCard == NULL ) goto EXIT;

	//-----------------------------------------------------------------
	// �E�B���h�E�쐬
	//-----------------------------------------------------------------
	// ICore�C���^�[�t�F�C�X���̏��ɏ]���ăA�v���P�[�V����
	// �E�B���h�E�𐶐����܂��B
	// IGraphicCard����̏������ɉ�ʉ𑜓x�Ȃǂ�ύX����ꍇ�́A
	// ICore::Start()���Ăяo���O�ɍs���Ă��������B
	pCore->Start( ScreenWidth, ScreenHeight, !isFullScreen );

	//-----------------------------------------------------------------
	// �����_���[���擾
	//-----------------------------------------------------------------
	// �쐬�����O���t�B�b�N�J�[�h�����ʕ`��p�̃����_���[���擾���܂��B
	// Renderer::IRender�C���^�[�t�F�C�X��1��IGraphicCard�C���^�[�t�F�C�X�ɑ΂���1�������݂��܂���B
	pRender = pGraphicCard->CreateRender();
	if ( pRender == NULL ) goto EXIT;
	

	//-----------------------------------------------------------------
	// �}�E�X�擾
	//-----------------------------------------------------------------
	pMouse = pCore->GetMouse();
	if ( pMouse == NULL ) goto EXIT;
	//-----------------------------------------------------------------
	// �L�[�{�[�h�̎擾
	//-----------------------------------------------------------------
	pKeyboard = pCore->GetKeyboard();

	//-----------------------------------------------------------------
	// �e�N�X�`���̓ǂݍ���
	//-----------------------------------------------------------------
	// �e�N�X�`�������p�̃I�v�V�����ݒ�
	//  0,0,0 �̐F���J���[�L�[�ɐݒ�
	Conf.SetColorKey( CColor(0,0,0,255) );
	Conf.SetFormat( FORMAT_TEXTURE_32BIT );
	Conf.SetMipmapEnable( true );	

	//-----------------------------------------------------------------
	// �t�@�C���o�^
	//-----------------------------------------------------------------
	// �t�@�C���}�l�[�W���[�𐶐�
	pFileMgr = pCore->CreateFileManager();
	// �R�A�ɐݒ�
	pCore->SetFileManager( pFileMgr );
	// ���[�g�f�B���N�g����ݒ�
	pFileMgr->SetRootPath( 0, RootPath );
	// ���[�g�f�B���N�g���ɑ΂��ēǂݍ��ރJ�����g�f�B���N�g���ݒ�
	pFileMgr->SetCurrentPath( CurrentPath );
		
	//�t���[�����[�g�Ɖ�ʃT�C�Y�̏�����
	this->ScreenSize.x=ScreenWidth;
	this->ScreenSize.y=ScreenHeight;
	switch(FrameRate){
		case FRAME_RATE_15:this->FrameRate=15;break;
		case FRAME_RATE_20:this->FrameRate=20;break;
		case FRAME_RATE_30:this->FrameRate=30;break;
		case FRAME_RATE_60:this->FrameRate=60;break;
		default:this->FrameRate=60;//�f�t�H���g��60�ɂ��Ă���
	}


	//�`��}�l�[�W���̏������B
	Manager::CRenderManager *pRenderManager=Manager::CRenderManager::GetInstance();
	pRenderManager->SetBackgroundColor(CColor(255,255,255,255));
	//�`��^�C�v�̐ݒ�
	pRender->SetDrawType(DRAW_TYPE_BLEND  );


	return true;
EXIT:
	DMessageBox("TiGLiCS�������G���[");
	return false;
}

void CEngine::Exec(){
	Selene::Peripheral::IKeyboard * pKeyboard=this->GetIKeyboard();
	Sint32 * KeyState=Manager::CInputManager::GetInstance()->_GetKeyStateArr();
	//�L�[�̓��͏󋵎擾
	for(Sint32 i=0;i<=0xFF;++i){
		if(pKeyboard->GetKeyData((eVirtualKeyCode)i)){
			++KeyState[i];
		}else{
			KeyState[i]=0;
		}
	}
	//���̌�Ƀy�[�W�̓���
	Manager::CPageManager::GetInstance()->Exec();
}




void CEngine::_Release(void){//�������
	//�y�[�W�}�l�[�W���̉��
	Manager::CPageManager::Release();
	//�t�@�C�o�̃X�^�b�N���
	Object::CFiberMemoryManager::ClearStackMem();
	//�`��}�l�[�W���̉��
	Manager::CRenderManager::Release();
	//�t�H���g�}�l�[�W���̉��
	Manager::CFontManager::Release();
	//�e�N�X�`���}�l�[�W���̉��
	Manager::CTextureManager::Release();
	//�T�E���h�}�l�[�W���̉��
	Manager::CSoundManager::Release();
	//�C���v�b�g�}�l�[�W���̊C�ۂ�
	Manager::CInputManager::Release();
	// �t�@�C���}�l�[�W���[���
	SAFE_RELEASE( pFileMgr );

	// �����_���[�̉��
	SAFE_RELEASE( pRender );

	// �O���t�B�b�N�J�[�h�̉��
	SAFE_RELEASE( pGraphicCard );
	// �R�A�̉��
	SAFE_RELEASE( pCore );

	//--------------------------------------------------------
	// �V�X�e���̉��
	//--------------------------------------------------------
	// �A�v���P�[�V�����̏I�����ɕK���Ăяo���ĉ������B
	// �܂����̊֐����Ăяo���O�Ɏ擾�����S�Ă�
	// �C���^�[�t�F�C�X��������Ă��������B
	System::Finalize();
}


void TiGLiCS::DMessageBox(const char *src,...){
	char buff[256];
	va_list args;
	va_start(args,src);
	vsnprintf(buff,(size_t)256,src,args);
	MessageBox(NULL,buff,"Debug",MB_OK);
}
