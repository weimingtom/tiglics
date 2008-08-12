#pragma once
#include "Base/Base.h"
#include "Base/Configure.h"
#include "Manager/SoundManager.h"
#include "Manager/RenderManager.h"
#include "Manager/PageManager.h"
#include <ctime>
#include <vector>
#include <mmsystem.h> // winmm.lib �������N����̂�Y�ꂸ��

namespace TiGLiCS{
	/**
		@brief �^�X�N�V�X�e��
		@author my04337

		���ׂĂ̒��S�ƂȂ�N���X�B�e�}�l�[�W���ނւ̃A�N�Z�X��<br>
		�قڂ�������\�ł���B
	*/
	class  CEngine{	//�V���O���g���N���X
		Selene::ICore						*pCore;			//�R�A
		Selene::IGraphicCard				*pGraphicCard;	//�O���t�B�b�N�J�[�h���
		Selene::Renderer::IRender			*pRender;		//�����_�[
		Selene::File::IFileManager			*pFileMgr;		//�t�@�C���}�l�[�W��
		Selene::Peripheral::IMouse			*pMouse;		//�}�E�X�f�o�C�X
		Selene::Peripheral::IKeyboard		*pKeyboard;		//�L�[�{�[�h�f�o�C�X
		Selene::Renderer::CTextureConfig	Conf;			//�e�N�X�`���R���t�B�O
		


		Selene::Math::Point2DI ScreenSize;//�X�N���[���T�C�Y
		Sint32 FrameRate;

		//�f�o�b�O�p�ϐ�

		void Exec(void);//�������s
		void _Release(void);//�������
		///�R���X�g���N�^�B�V���O���g���p�Ƀv���C�x�[�g
		CEngine(){	
			//�܂���NULL�ŏ�����
			pCore=NULL;
			pGraphicCard=NULL;
			pRender=NULL;
			pMouse=NULL;
			pKeyboard=NULL;
		}
		//�f�X�g���N�^
		~CEngine(){
		}

		static CEngine * Instance;//�������g�̃C���X�^���X(�V���O���g���p)
	public:
		static CEngine * GetInstance(){
			return Instance;
		}
		static void Release(){
			Instance->_Release();
			delete Instance;
		}
		/*
			@brief �������֐�
			@author my04337
			@param Title [in] �^�C�g��
			@param FrameRate [in] �t���[�����[�g�w��
			@param isDrawDebugTitle [in] �f�o�b�O�p�^�C�g����\�����邩
			@param ScreenWidth [in] �X�N���[����
			@param ScreenHeight [in] �X�N���[������
			@param isFullScreen [in] �t���X�N���[���ɂ��邩
			@param RootPath [in] ���[�g�f�B���N�g���̃A�h���X
			@param CurrentPath [in] �J�����g�f�B���N�g���̃A�h���X
			@param isBenchMode [in] �x���`�}�[�N���[�h�ɂ��邩
			@return �������ɐ���������


		*/
		bool Init(const char * Title,Selene::eFrameRate FrameRate,bool isDrawDebugTitle,
					 Sint32 ScreenWidth,Sint32 ScreenHeight,bool isFullScreen,const char * RootPath,
					 const char * CurrentPath,bool isBenchMode=false);
		/**
			@brief ���s�֐�
			@author my04337
			@retval true �^�X�N���I�����Ă��Ȃ�
			@retval false �^�X�N���I������

			���̊֐������[�v�����邱�ƂŁA���t���[���e�������s�킹��B<br>
			���s�̍ۂɂ́A�ȉ��̂悤�ɋL�q����<br>
			@code
			...
			WinMain(){
				...//��������
				while(pEngine->Run()){}
				...//�I������

				return ...;
			}
			@endcode
		*/
		inline Bool Run(){
			Exec();
			return pCore->Run();
		}

		
		//�X�N���[���T�C�Y�ƃt���[�����[�g
		Selene::Math::Point2DI GetScreenSize(){return ScreenSize;}
		Sint32 GetFrameRate(){return FrameRate;}

		inline void End(){pCore->Exit();}//�I��������B
		
		///TiGLICS�̃o�[�W�����擾
		inline const char* GetVerStr(){return TIGLICS_VERSION;}

		//�e��I�u�W�F�N�g�ւ̃|�C���^�̎擾
		///Selene::ICore���擾
		inline Selene::ICore* GetICore(){return pCore;}
		///Selene::IGraphic���擾
		inline Selene::IGraphicCard* GetIGraphicCard(){return pGraphicCard;}
		///Selene::IRender���擾
		inline Selene::Renderer::IRender* GetIRender(){return pRender;}
		///�e�N�X�`���ݒ���擾
		inline Selene::Renderer::CTextureConfig *GetCTextureConfig(){return &Conf;}
		///Selene::File::IFileManager���擾
		inline Selene::File::IFileManager* GetIFileManager(){return pFileMgr;}
		///Selene::Peripheral::IMouse���擾
		inline Selene::Peripheral::IMouse* GetIMouse(){return pMouse;}
		///Selene::Peripheral::IKeyboard���擾
		inline Selene::Peripheral::IKeyboard* GetIKeyboard(){return pKeyboard;}
		
	};

};