//�t�H���g�Ǘ��\���́B�����ɕK�v�ȏ��̊Ǘ�
#pragma once
#include "Base/Base.h"
#include <vector>
namespace TiGLiCS{
	namespace Manager{
		/**
			@brief �t�H���g�P�̃}�l�[�W��
			@author my04337
			@note
			�t�H���g�t�@�C���Ǘ��N���X�B�t�H���g�X�v���C�g�̐����𐿂�����
		*/
		class  CFont{
			const char * FileName;//�t�@�C����
			const char * FileType;//�t�@�C���t�H�[�}�b�g
		public:
			/**
				@brief �R���X�g���N�^
				@author my04337
				@param FileName [in] �t�H���g�t�@�C����
				@param FileType [in] �t�@�C���t�H�[�}�b�g
			*/
			CFont(const char * FileName,const char * FileType){
				this->FileName=FileName;
				this->FileType=FileType;
			}
			~CFont(){}//�f�X�g���N�^
			Selene::Renderer::Object::IFontSprite2D *MakeFontSprite2D(Selene::Renderer::IRender *pRender,Sint32 MaxDrawNum){
				return pRender->CreateFontSprite2DFromFile(FileName,FileType,MaxDrawNum);
			}
			Selene::Renderer::Object::IFontSprite3D *MakeFontSprite3D(Selene::Renderer::IRender *pRender,Sint32 MaxDrawNum){
				return pRender->CreateFontSprite3DFromFile(FileName,FileType,MaxDrawNum);
			}
			inline const char * GetFileName(){return FileName;}
			inline const char * GetFileType(){return FileType;}
		};
		//-------------------------------------------------------------------------------------
		
		/**
			@brief �t�H���g�}�l�[�W��
			@author my04337
			@note
			�t�H���g�S�̂̊Ǘ��𐿂������B
		*/
		class CFontManager{//�V���O���g��
			static CFontManager * Instance;
			std::vector<CFont *> FontList;//�t�H���g���X�g
			CFontManager(){}
			~CFontManager(){}
		public:
			static CFontManager * GetInstance(){return Instance;}
			static void Release(){
				//�t�H���g�̉��
				for(Sint32 i=0;i<(Sint32)Instance->FontList.size();++i){
					SAFE_DELETE(Instance->FontList[i]);
				}	
			}
			/**
				@brief �t�H���g�̒ǉ�
				@author my04337
				@param pFont [in] �t�H���g�}�l�[�W���ւ̃|�C���^
				@return �t�H���gID

				�t�H���g�̓o�^���s���B�߂�l�̓t�H���gID�ŁA�t�H���g�̒ǉ�����<br>
				0 , 1 , 2 , ... �Ƃ������l�ƂȂ�B
			*/
			Sint32 AddFont(CFont * pFont){FontList.push_back(pFont);return (Sint32)FontList.size();}
			
			inline Sint32 GetCFontNum(void){
				return (Sint32)FontList.size();
			}
			inline CFont* GetCFont(Sint32 idx){
				return (idx>=0 && idx<(Sint32)FontList.size()?FontList[idx]:NULL);
			}
		};
	};
};
