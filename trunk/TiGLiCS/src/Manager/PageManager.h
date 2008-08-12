#pragma once
#include "Base/Define.h"
#include "Objects/Object.h"
#include "Manager/FrameManager.h"
#include "Manager/CollisionManager.h"
#include <map>
#include <vector>

namespace TiGLiCS{
	/**
		@brief �y�[�W�N���X
		@author my04337
		@note
		�y�[�W�N���X�B�e�I�u�W�F�N�g�͈�̃y�[�W�N���X�Ɋ֘A�Â�����B<br>
		�y�[�W�P�ʂŃt���[���}�l�[�W���A�R���W�����}�l�[�W���A���O�o�͂����B
	*/
	class  CPage{
		Sint32 PageID;//�y�[�WID

		Selene::CColor BackColor;//�w�i�F

		Object::ProcessPriorityList ProcessQueue;	//�������̃��X�g
		Object::PtrPriorityList PtrQueue;	//�|�C���^���̃��X�g
		std::vector<Object::IObject *> DeleteQueue;//�폜�̃L���[
		std::vector<Object::IObject *> AddQueue;//�ǉ��̃L��
		
		Manager::CFrameManager * pFrameManager;//�t���[���}�l�[�W��
		Manager::CCollisionManager2D * pCollisionManager2D;//2D�R���W�����}�l�[�W��

		void delObject();//���ۂ̍폜����
		void addObject();//���ۂ̒ǉ�����

		//�f�o�b�O�p�ϐ�
	#ifdef TIGLICS_DEBUG
		LARGE_INTEGER   nFreq,t1,t2,t3,t4,t5,t6,t7;
		Sint32 DataArr[32];//�f�o�b�O�p
		
		char log_str[MAX_TASK_LOG_ROW][MAX_TASK_LOG_SIZE];
		char log2_str[MAX_TASK_LOG_ROW][MAX_TASK_LOG_SIZE];
		Sint32 NowLogRow;//�ǂ̃��O�������Ƃ��V������

	#endif

	public:
		CPage(Sint32 PageID){
			this->PageID=PageID;
			//�����蔻�胊�X�g�̏�����
			pCollisionManager2D=new Manager::CCollisionManager2D(this);
			pFrameManager=NULL;

	#ifdef TIGLICS_DEBUG
			//���O�̏�����
			this->NowLogRow=0;
			for(Sint32 i=0;i<MAX_TASK_LOG_ROW;++i){
				log_str[i][0]='\0';
				log2_str[i][0]='\0';
			}
	#endif
		}
		~CPage(){Release();}
		///�y�[�WID���擾
		Sint32 GetPageID()const{return PageID;}

		void Exec(void);//�������s

		//�I�u�W�F�N�g�֘A
		void AddObject(Object::IObject *);//�I�u�W�F�N�g�ǉ�
		void DeleteObject(Object::IObject *);//�I�u�W�F�N�g���폜�L���[�ɓo�^
		///�I�u�W�F�N�g���̎擾
		inline Sint32 GetObjectNum(void){return (Sint32)PtrQueue.size();}//�I�u�W�F�N�g����Ԃ�
		///�폜�L���[���̃I�u�W�F�N�g����Ԃ�
		inline Sint32 GetDeleteQueueNum(void){return (Sint32)DeleteQueue.size();}//�폜�I�u�W�F�N�g����Ԃ�
		///�ǉ��L���[���̃I�u�W�F�N�g����Ԃ�
		inline Sint32 GetAddQueueNum(void){return (Sint32)AddQueue.size();}//�ǉ��I�u�W�F�N�g����Ԃ�	

		/**
			@brief �w�i�F�̐ݒ�
			@author my04337
			@param col [in] �w�i�F

			�w�i�F��ݒ肷��B�������A�V�[���}�l�[�W�����o�^����Ă���ꍇ��<br>
			�����㖳���ƂȂ�B
		*/
		void SetBackColor(Selene::CColor &col){BackColor=col;}	
		
		/**
			@brief �t���[���}�l�[�W���̎擾
			@author my04337
			@retval �ݒ莞 �t���[���}�l�[�W���ւ�
			@retval ���ݒ� NULL

			�t���[���}�l�[�W���ւ̃|�C���^���擾����B�ݒ肳��Ă��Ȃ��ꍇ�ANULL���A��B
		*/
		inline Manager::CFrameManager * GetCFrameManager(){return pFrameManager;}
		
		/**
			@brief �t���[���}�l�[�W���̐ݒ�
			@author my04337
			@param pFrameManager [in] �t���[���}�l�[�W���ւ̃|�C���^
			
			�t���[���}�l�[�W����ݒ肷��B�ʂȃ}�l�[�W���ɍ����ւ���Ƃ���<br>
			��xGetFrameManager���g��������s������ɓo�^����K�v������B
		*/
		inline void SetFrameManager(Manager::CFrameManager * pFrameManager){this->pFrameManager=pFrameManager;}
		
		//�����蔻��}�l�[�W���̎擾
		inline Manager::CCollisionManager2D* GetCCollisionManager2D(){return pCollisionManager2D;}

		/**
			@brief ���O�o��
			@author my04337
			
			��ʍ����Ƀ��O���o�͂���B�`����printf�Ɠ����B<br>
			�����s�ɑΉ����Ă���B�܂��A���O�͈�萔�ێ�����A���̌�͏��������B<br>
			�������A���O�����ł�LIB���g�p�����ꍇ�A���O�͕\������Ȃ��B
		*/
		void LogPrint(const char *src,...);//���O�o��

		void Log2Print(Sint32 LineNum,const char *src,...);//���O�o��

		void Release();//�������
	};

	typedef std::map<Sint32,CPage *> tPageList;
		
	namespace Manager{
		/**
			@brief �y�[�W�}�l�[�W��
			@author my04337

			�y�[�W�Ǘ����s���B�e�y�[�W�͂���Ɋ֘A�Â�����B<br>
			�܂��A�y�[�W�̐؂�ւ��������ōs����
		*/
		class  CPageManager{//�y�[�W�Ǘ��B�V���O���g��
			tPageList PageList;//�y�[�W���X�g
			Sint32 NowPageID;//���݂̃y�[�WID
			Sint32 NextPageID;//����̃y�[�WID
			bool bNowPageDelete;
			static CPageManager * Instance;
			CPageManager(){}
			~CPageManager(){}
		public:
			static CPageManager* GetInstance(){return Instance;}//�C���X�^���X�擾
			static void Release();//�I������
			/**
				@brief �y�[�W����
				@author my04337
				@param PageID [in] �y�[�WID
				@retval ������ �y�[�W�N���X�ւ̃|�C���^
				@retval ���s�� NULL

				�y�[�W�𐶐����A���̃|�C���^��Ԃ�<br>
				�y�[�WID�͑��̃y�[�W�Ƃ��Ԃ�Ȃ��l�ɂ���K�v������B<br>
				�����Ɏ��s�����NULL���Ԃ����B
			*/
			CPage* CreatePage(Sint32 PageID);

			/**
				@brief �y�[�W�폜
				@author my04337
				@param PageID [in] �y�[�WID
				@retval ������ true
				@retval ���s�� false

				�y�[�W�̍폜���s���B<br>
				���̂Ƃ��A�폜�Ώۂ�������s�\��̃y�[�W�̏ꍇ�A�폜�����s����B
			*/
			bool DeletePage(Sint32 PageID);//�y�[�W�̍폜

			/**
				@brief �y�[�W�擾
				@author my04337
				@param PageID [in] �y�[�WID
				@retval ������ �y�[�W�N���X�ւ̃|�C���^
				@retval ���s�� NULL

				�y�[�WID����y�[�W�N���X�ւ̃|�C���^���擾����B<br>
				���݂��Ȃ�ID�ɑ΂��Ď擾���悤�Ƃ����ꍇ�ANULL���Ԃ����B
			*/
			CPage* GetPage(Sint32 PageID);//�y�[�W�̎擾

			/**
				@brief ���݂̃y�[�WID�擾
				@author my04337
				@return ���݂̃y�[�WID

				���ݎ��s���̃y�[�WID���擾����B
			*/
			CPage* GetNowPage();//���݂̃y�[�W�擾
			/**
				@brief �y�[�W���擾
				@author my04337
				@return �y�[�W��

				�y�[�W�}�l�[�W���ɓo�^����Ă��鑍�y�[�W����Ԃ��B
			*/
			Sint32 GetPageNum(){return PageList.size();}//�y�[�W���擾

			/**
				@brief ������s�̃y�[�W�ݒ�
				@author my04337
				@param PageID [in] �y�[�WID
				@param isNowPageDelete [in] ���݂̃y�[�W���폜���邩
				@retval ������ true
				@retval ���s�� false

				������s�̃y�[�W�ԍ���ݒ肷��B<br>
				���̂Ƃ��A���ݎ��s���̃y�[�W���폜���邩��ݒ�ł���B<br>
				�����ȃy�[�W�ɐ؂�ւ��悤�Ƃ����ꍇ�A���s����B

			*/
			bool SetNextPage(Sint32 PageID,bool isNowPageDelete=false);//���Ɏ��s����y�[�WID�̐ݒ�

			void Exec();//�y�[�W�̎��s

		};
	};
};