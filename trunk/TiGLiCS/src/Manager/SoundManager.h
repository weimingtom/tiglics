//SE�Ǘ��p�\����
#pragma once

#include "Base/Base.h"
#include <list>
#include <vector>
namespace TiGLiCS{
	namespace Manager{
		/**
			@brief �T�E���h�P�̃}�l�[�W��
			@author my04337
			
			SE�̊Ǘ����s���B�����������\�ł���B
		*/
		class  CSound{
			Selene::Sound::ISound * pSound;
			Sint32 LayerCount;//�ő僌�C����
			Sint32 NowLayer;//���݂̃��C���ԍ�
		public:
			/**
				@brief �R���X�g���N�^
				@author my04337
				@param pEngine [in] �^�X�N�ւ̃|�C���^
				@param FileName [in] �T�E���h�t�@�C����
				@param LayerCount [in] �ő哯���Đ���
				
				�R���X�g���N�^�B LayerCount��1�ɂ���Ɠ����������s��Ȃ��B
			*/
			CSound(const char * FileName,Sint32 LayerCount);//�R���X�g���N�^
			~CSound(){//�f�X�g���N�^
				SAFE_RELEASE(pSound);
			}
			/**
				@brief �Đ�
				@author my04337
				@param isLoop [in] ���[�v���邩�ǂ���
				@return ���C���ԍ�

				SE�̍Đ����s���B�߂�l�̃��C���ԍ��͒�~��ꎞ��~�ȂǂɎg���B
			*/
			Sint32 Play(bool isLoop=false){//�Đ�
				++NowLayer;
				if(NowLayer>=LayerCount)NowLayer=0;
				pSound->Stop(NowLayer);
				pSound->Play(NowLayer,isLoop);
				return NowLayer;
			}

			/**
				@brief �Đ� �ڍ׃p�����[�^�w��
				@author my04337
				@param fVolume [in] �{�����[��(0.0f - 100.0f)
				@param fPan [in] �p��(-100.0f - 100.0f)
				@param isLoop [in] ���[�v���邩�ǂ���
				@return ���C���ԍ�

				SE�̍Đ����s���B�߂�l�̃��C���ԍ��͒�~��ꎞ��~�ȂǂɎg���B
			*/
			Sint32 Play(float fVolume,float fPan,bool isLoop=false){
				++NowLayer;
				if(NowLayer>=LayerCount)NowLayer=0;
				pSound->Stop(NowLayer);
				SetVolume(NowLayer,fVolume);
				SetPan(NowLayer,fPan);
				pSound->Play(NowLayer,isLoop);
				return NowLayer;
			}
			/**
				@brief ��~
				@author my04337
				@param Layer [in] ���C���ԍ�
				
				SE�̒�~���s��.
			*/
			void Stop(Sint32 Layer){
				pSound->Stop(Layer);
			}
			/**
				@brief �ꎞ��~
				@author my04337
				@param Layer [in] ���C���ԍ�
				
				SE�̈ꎞ��~���s��.
			*/
			void Pause(Sint32 Layer){
				pSound->Pause(Layer);
			}
			/**
				@brief ���ʒ���
				@author my04337
				@param Layer [in] ���C���ԍ�
				@param fVolume [in] �{�����[��(0.0f - 100.0f)
				
				�{�����[���̒������s��
			*/
			void SetVolume(Sint32 Layer,float fVolume){
				pSound->SetVolume(Layer,fVolume);
			}
			/**
				@brief �ʑ�����
				@author my04337
				@param Layer [in] ���C���ԍ�
				@param fPan [in] �p��(-100.0f - 100.0f)
				
				�p���̒������s��
			*/
			void SetPan(Sint32 Layer,float fPan){
				pSound->SetPan(Layer,fPan);
			}
			/**
				@brief �Đ���Ԏ擾
				@author my04337
				@param Layer [in] ���C���ԍ�
				@return �Đ�����

				�w�背�C���[���Đ��������擾����
			*/
			Bool isPlay(Sint32 Layer){return pSound->IsPlay(Layer);}
		};
		//-----------------------------------------------------------------------------------
		/**
			@brief �T�E���h�}�l�[�W��
			@author my04337

			SE�S�̃}�l�[�W���B�o�^�폜��S���B
		*/
		class CSoundManager{//�V���O���g��
			std::vector<Manager::CSound *> SoundList;//SE���X�g
			static CSoundManager * Instance;
			CSoundManager(){}
			~CSoundManager(){}
		public:
			static CSoundManager * GetInstance(){return Instance;}
			static void Release(){
				for(Sint32 i=0;i<(Sint32)Instance->SoundList.size();++i){
					SAFE_DELETE(Instance->SoundList[i]);
				}
				delete Instance;
			}
			//�T�E���h�Ǘ�
			inline Sint32 GetCSoundNum(void){
				return (Sint32)SoundList.size();
			}

			/**
				@brief �T�E���h�ǉ�
				@author my04337
				@param pSound [in] �T�E���h�}�l�[�W���̃A�h���X
				@return �T�E���hID

				
				�T�E���h�̓o�^���s���B�߂�l�̓T�E���hID�ŁA�T�E���h�̒ǉ�����<br>
				0 , 1 , 2 , ... �Ƃ������l�ƂȂ�B
			*/
			Sint32 AddSound(const char * FileName,Sint32 LayerCount){
				SoundList.push_back(new CSound(FileName,LayerCount));
				return (Sint32)SoundList.size();
			}

			/**
				@brief �T�E���h�}�l�[�W���擾
				@author my04337
				@param idx [in] �T�E���hID
				@retval ������ �T�E���h�}�l�[�W���̃A�h���X
				@retval ���s�� NULL

				�T�E���h���擾����B�����ȃT�E���hID�̏ꍇ�ANULL���Ԃ����B
			*/
			inline Manager::CSound* GetCSound(Sint32 idx){
				return (idx>=0 && idx<(Sint32)SoundList.size()?SoundList[idx]:NULL);
			}			
		};

	};
};