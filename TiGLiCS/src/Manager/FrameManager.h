#pragma once
#include "Base/Base.h"
using namespace Selene;
namespace TiGLiCS{
	namespace Manager{
		/**
			@brief �t���[���}�l�[�W��
			@author my04337

			�t���[���}�l�[�W���B�e�y�[�W�Ɉ���z�u�\<br>
			�^�X�N�̐擪�A�����ōs�����������Ȃǂ��L�q����<br>
			���[�U�[�͂�����p�����Ďg�p����B
		*/
		class  CFrameManager:public IFrameManager{
		public:
			
			///�����y�[�W�N���X
			CPage * pPage;

			/**
				@brief �R���X�g���N�^
				@author my04337
				@param pPage [in] ��������y�[�W�N���X
			*/
			CFrameManager(CPage * pPage){this->pPage=pPage;}

			///�f�X�g���N�^
			virtual ~CFrameManager(){};

			/**
				@brief �^�X�N�擪�ōs������
				@author my04337

				���ׂẴI�u�W�F�N�g�̏����O�Ɏ��s����֐�
			*/
			virtual void BeforeProcess(void)=0;

			/**
				@brief �V�[���}�l�[�W�����Z�b�g���ɌĂяo�����֐�
				@author my04337

				�V�[���}�l�[�W�����֘A�Â����Ă���ꍇ�AReset()���Ă΂ꂽ��<br>
				���ِ̊����Ăяo�����B
			*/
			virtual void OnSceneManagerReset(void)=0;

			/**
				@brief �^�X�N�����ōs������
				@author my04337

				���ׂẴI�u�W�F�N�g�̏�����Ɏ��s����֐�
			*/
			virtual void AfterProcess(void)=0;
		};
	};
};