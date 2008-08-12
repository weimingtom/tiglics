#pragma once

#include "Base/Base.h"
#include <vector>
namespace TiGLiCS{
	namespace Manager{
		/**
			@brief �e�N�X�`��
			@author my04337
			@note
			�e�N�X�`���Ǘ����s���B�e�N�X�`���ƁA�`�掞�Ɏg�p����̈�̃��X�g�����B
		*/
		class  CTexture{
			Selene::Renderer::ITexture *Texture;//�e�N�X�`��
			std::vector<Selene::Math::Rect2DF> TextureArea;//�e�N�X�`���̈�
		public:
			/**
				@brief �R���X�g���N�^
				@author my04337
				@param pEngine [in] �^�X�N�ւ̃|�C���^
				@param FileName [in] �e�N�X�`���t�@�C����
				
				�e�N�X�`���}�l�[�W���̍쐬���s���B
			*/
			CTexture(const char * FileName);
			~CTexture(){SAFE_RELEASE(Texture);}//�f�X�g���N�^
			/**
				@brief �e�N�X�`���擾
				@author my04337
				@return �e�N�X�`���ւ̃|�C���^

				�e�N�X�`���ւ̃|�C���^���擾����
			*/
			inline Selene::Renderer::ITexture *GetITexture(){return Texture;}
			
			/**
				@brief �e�N�X�`���̈�ǉ�
				@author my04337
				@param TexArea �e�N�X�`���̈�
				@return �e�N�X�`���̈�ID

				
				�e�N�X�`���̈�̓o�^���s���B�߂�l�̓e�N�X�`���̈�ID�ŁA�e�N�X�`���̈�̒ǉ�����<br>
				0 , 1 , 2 , ... �Ƃ������l�ƂȂ�B
			*/
			inline Sint32 AddTextureArea(Selene::Math::Rect2DF TexArea){TextureArea.push_back(TexArea);return TextureArea.size();}

			inline Selene::Math::Rect2DF GetTextureArea(Sint32 idx){return (idx >=0 &&idx<(Sint32)TextureArea.size()?TextureArea[idx]:Selene::Math::Rect2DF(0,0,0,0));}
			inline Sint32 GetTextureAreaNum(){return TextureArea.size();}
		};

		//-----------------------------------------------------------------------------------
		/**
			@brief �e�N�X�`���}�l�[�W��
			@author my04337
			@note
			�e�N�X�`���S�̂̊Ǘ��𐿂������B
		*/
		class CTextureManager{
			static CTextureManager * Instance;
			std::vector<CTexture *> TextureList;//�e�N�X�`�����X�g

			CTextureManager(){}
			~CTextureManager(){}
		public:
			static CTextureManager * GetInstance(){return Instance;}
			static void Release(){
				//�e�N�X�`���[�̉��
				for(Sint32 i=0;i<(Sint32)Instance->TextureList.size();++i){
					SAFE_DELETE(Instance->TextureList[i]);
				}	
			}
			/**
				@brief �e�N�X�`���̒ǉ�
				@author my04337
				@param pTex [in] �e�N�X�`���}�l�[�W���ւ̃|�C���^
				@return �e�N�X�`��ID

				�e�N�X�`���̓o�^���s���B�o�^�̍ۂɂ͂��炩���߃e�N�X�`���}�l�[�W����<br>
				�e��ݒ���s���K�v������B�߂�l�̓e�N�X�`��ID�ŁA�e�N�X�`���̒ǉ�����<br>
				0 , 1 , 2 , ... �Ƃ������l�ƂȂ�B
			*/
			Sint32 AddTexture(CTexture * pTex){
				TextureList.push_back(pTex);
				return (Sint32)TextureList.size();
			}
			
			/**
				@brief �e�N�X�`���̎擾
				@author my04337
				@param idx [in] �e�N�X�`��ID
				@retval ������ �e�N�X�`���}�l�[�W���ւ̃|�C���^
				@retval ���s�� NULL
				
				�e�N�X�`���̎擾���s���B���݂��Ȃ��e�N�X�`��ID���w�肷���NULL���Ԃ����B				
			*/
			inline CTexture* GetCTexture(Sint32 idx){
				return (idx>=0 &&idx<(Sint32)TextureList.size()?TextureList[idx]:NULL);
			}
			inline Sint32 GetCTextureNum(void){
				return (Sint32)TextureList.size();
			}
		};
	};
};
