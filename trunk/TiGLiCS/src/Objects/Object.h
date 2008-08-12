#pragma once

#include "Objects/Fiber.h"
#include <typeinfo>
//class CEngine;//�z�Q�Ɖ��
//��{�I�u�W�F�N�g
//�󂯎�����e�N�X�`���A�����_���͉�����Ȃ�
namespace TiGLiCS{
	namespace Object{
		/**
			@brief �I�u�W�F�N�g�N���X
			@author my04337

			�^�X�N�ɑg�ݍ��ނ��߂̃N���X�B���[�U�͂��̃N���X���p�����Ďg�p����B
		*/
		class  CObject:public IObject,private CFiber{
			Sint32 ProcessPriority;
			CObjectContainer *pObjectContainer;
			Sint32 WaitNum;//�ҋ@�t���[����
			bool bDead;//���S�������ǂ���
		public:
			///�����̏�������y�[�W�ւ̃|�C���^
			CPage *pPage;
			/**
				@brief �R���X�g���N�^
				@author my04337
				@param pPage [in] ����������y�[�W�ւ̃|�C���^
				@param ProcessPriority [in] �����D��x
			*/
			CObject(CPage *pPage,Sint32 ProcessPriority);

			/**
				@brief �f�X�g���N�^
				@author my04337
				
				�f�X�g���N�^�B��{�I�Ɏg�p���ׂ��ł͂Ȃ��B
			*/
			virtual ~CObject(){}//�f�X�g���N�^

			/**
				@brief �����D��x�擾
				@author my04337
				@return �����D��x

				�����D��x���擾����B
			*/
			inline Sint32 GetProcessPriority(void){return ProcessPriority;}
			
			//�K�{�֐�
			/**
				@brief �������֐�
				@author my04337

				�I�u�W�F�N�g���^�X�N�ɑg�ݍ��܂ꂽ����Ɏ��s�����B<br>
				�^�X�N��y�[�W���֌W���鏉�������͂����ɏ����Ƃ悢�B
			*/
			virtual void Init(void)=0;
			/**
				@brief �����֐�
				@author my04337

				�I�u�W�F�N�g�̈ړ��Ȃǂ̏������L�q����B<br>
				���ِ̊����I������Ǝ����I�ɃI�u�W�F�N�g�͍폜�L���[�ɓ���B<br>
				���̊֐����ł̂݁AUpdate(),Wait()�֐����Ăяo�����Ƃ��ł���B<br>
				�܂��A���̊֐����ł��`����s�����Ƃ͂ł���B<br>
				�L�q�̍ۂɂ́A�������[�v�Ȃǂ�����Ă����A�����Update�ɂĒ��f����<br>
				�Ȃ��A���̊֐��̂݃X�^�b�N�͓Ǝ��Ɋm�ۂ����̈���g�����߁A<br>
				�X�^�b�N�I�[�o�[�t���[�ɒ��ӂ���K�v������B<br>
				<br>
				�ȉ��̃R�[�h�ł�Process��10��Ă΂��ƃI�u�W�F�N�g���폜�����B
				@code
				class CTestObject:public IObject{
					...
					Process(){
						for(int i=0;i<10;++i){
							...//���낢��ȏ����i�ړ������A�L�[���͔���Ȃ�)
							Update();
						}
					}
					...
				}
				@endcode				
			*/
			virtual void Process(void)=0;//����
			/**
				@brief�@�`��֐�
				@author my04337

				�����ɂ͎�ɕ`�揈���Ȃǖ��t���[���m���Ɏ��s�������������L�q����B<br>
				�Ȃ��A���t���[���K���Ă΂�邱�Ƃ𗘗p���Ĉړ��������������Ƃ��ł��邪�A<br>
				������͂�OnUpdate�֐��ɋL�q��������𐄏�����B
			*/
			virtual void Draw(void)=0;//�`��
			/**
				@brief ����֐�
				@author my04337

				���̊֐��́A�I�u�W�F�N�g���^�X�N����O����钼�O�ɌĂ΂��B<br>
				��������Ȃǂ͂����ɏ������Ƃ𐄏�����B<br>
				���f�X�g���N�^�ɂĉ���������s�����Ƃ͐������܂���B
			*/
			virtual void Release(void)=0;//�I�u�W�F�N�g���^�X�N����O����钼�O�ɌĂ΂��
			//�C�ӊ֐�
			/**
				@brief �����_���`��O
				@author my04337

				���̊֐��̓����_�����`����n�߂�O�ɌĂ΂��B<br>
				3D�ŕ`��Ȃǂ��s���Ƃ��A�V�[���}�l�[�W���̐ݒ�Ȃǂ��s�������Ƃ���<br>
				�����𗘗p����Ƃ悢�B�Ȃ��A���̒��ł͕`��͕s�\�ł���B
			*/
			virtual void BeforeRenderBegin(void){};//Begin����O
			/**
				@brief �I�u�W�F�N�g���S��
				@author my04337

				���̊֐��̓I�u�W�F�N�g�����S���A�폜�L���[�ɓ���������ɌĂ΂��B<br>
				�I�u�W�F�N�g�ɑ΂�Die()�֐����Ăяo���ƁA�폜�Ώۂ̃I�u�W�F�N�g�ł��̊֐����Ă΂��B<br>
				���S����ɏ������s�������Ƃ��ɂ����ɏ����΂悢�B
			*/
			virtual void OnDie(void){}//�I�u�W�F�N�g���S��
			/**
				@brief �I�u�W�F�N�g�A�b�v�f�[�g��
				@author my04337

				���̊֐��̓I�u�W�F�N�g��Update�֐����Ăяo�����Ƃ��ɌĂяo�����B<br>
				�ړ������ȂǁA���t���[�����s�����������Ȃǂ͂����ɏ����Ƃ悢�B
			*/
			virtual void OnUpdate(void){}//Update���Ă΂ꂽ�Ƃ�


			//���̑��֐�
			/**
				@brief �A�b�v�f�[�g
				@author my04337

				Process���ɂāA���s�𒆒f��1�t���[���ҋ@����֐��ł���B<br>
				���̊֐����Ăяo������ADraw�֐������s����A���̃I�u�W�F�N�g�̎��s���s����B<br>
				��΂ɂ��̊֐���Proess�֐��O�Ŏg�p���Ă͂����Ȃ��B<br>
				�Ȃ��A�ĊJ���͂��̊֐��̒��ォ��ĊJ�����B

			*/
			virtual void Update();//�A�b�v�f�[�g����
			///�I�u�W�F�N�g�̎��S����
			bool isDead(){return bDead;}
			/**
				@brief �I�u�W�F�N�g�����S������
				@author my04337

				���̊֐����Ăяo�����ƂŁA�I�u�W�F�N�g�͍폜�L���[�ɓ������B<br>
				���̌�AOnDie�֐����Ă΂��B<br>
				�������A���̊֐����Ă΂ꂽ���_�ł̓I�u�W�F�N�g�̍폜�͍s��ꂸ�A<br>
				�������g��Die�֐����Ăяo�����ꍇ�ł����������s�����B
			*/
			void Die();//���S������
			bool _RunProcess();//�v���Z�X���s�B
			void _SuspendProcess(){Suspend();}
			int GetRestProcessStack(){return GetStackRest();}
			/**
				@brief �w��񐔃A�b�v�f�[�g
				@author my04337
				@param FrameNum [in] �ҋ@�t���[��
				���̊֐��ł́AFrameNum�Ŏw�肵���t���[����Update()���Ăяo���B<br>
				Update�֐���Update(1)�Ƃقړ����ł���B<br>
				�Ȃ��A���̊֐��̓I�[�o�[���C�g�𐄏����Ȃ�(����ꍇ��Update()���I�[�o�[���C�g����΂悢)�B
			*/
			void Update(Sint32 FrameNum);//�w��t���[�����ҋ@
			inline CObjectContainer *GetCObjectContainer(){return pObjectContainer;}
			inline void SetCObjectContainer(CObjectContainer *pObjectContainer){this->pObjectContainer=pObjectContainer;}

			//����ƕ֗��Ȋ֐�
			/**
				@brief ��ʓ��O����
				@author my04337
				@param pos [in] �I�u�W�F�N�g���W
				@retval true ��ʊO
				@retval false ��ʓ�

				�w�肳�ꂽ���W����ʊO�ɂ��邩�𔻒肷��B
			*/
			Bool isScreenOut(Selene::Math::Point2DF &pos);
			/**
				@brief �L�[��Ԏ擾
				@author my04337
				@param KeyCode [in] �L�[�R�[�h
				@retval ������Ă��Ȃ��ꍇ 0
				@retval ������Ă���ꍇ �����ꂽ�t���[����

				�L�[�������ꂽ���ǂ����𔻒肷��BCEngine::GetKey()�Ɠ���
			*/
			Sint32 GetKey(Selene::eVirtualKeyCode KeyCode);
			/*
				@brief �I�u�W�F�N�g�ǉ�
				@author my04337
				@param pObject [in] �ǉ�����I�u�W�F�N�g�̃|�C���^
				
				���݂̃y�[�W�ɃI�u�W�F�N�g��ǉ�����B<br>
				�ǉ������I�u�W�F�N�g�͎��̃t���[��������s�����B
			*/
			void AddObject(IObject *pOboect);

			/**
				@brief �X�N���[���T�C�Y�擾
				@author my04337
				@return �X�N���[���T�C�Y

				�X�N���[���̃T�C�Y���擾�BCEngine::GetScreenSize()�Ɠ���
			*/
			Selene::Math::Point2DI GetScreenSize(); 

			/**
				@brief �t���[�����[�g�擾
				@author my04337
				@return �t���[�����[�g

				�ݒ肳�ꂽ�t���[�����[�g���擾�BCEngine::GetFrameRate()�Ɠ���
			*/
			Sint32 GetFrameRate(); 

			/**
				@brief �^�X�N�̏I��
				@author my04337
				
				�^�X�N�̎��s���I������BCEngine::End()�Ɠ����ł���
			*/
			void End();
		};

		//-----------------------------------------------------------------------------------------------------
		class  CObjectContainer {//�폜�������΍�
			void Process();
		public:
			bool isDead;//�폜�ς݂��ǂ���
			IObject * pObj;//IObject�ւ̃|�C���^
			CObjectContainer(IObject *pObj){
				//�R���X�g���N�^
				isDead=false;
				this->pObj= pObj;//IObject�ւ̃|�C���^
			}
			~CObjectContainer(){}
		};
	};
};