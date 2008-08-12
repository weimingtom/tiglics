#pragma once
#include "Base/Base.h"
#include "Base/Configure.h"

namespace TiGLiCS{
	namespace Manager{		
		class  IFrameManager{
		public:
			virtual ~IFrameManager(){};
			virtual void BeforeProcess(void)=0;
			virtual void OnSceneManagerReset(void)=0;
			virtual void AfterProcess(void)=0;
		};
	}
	namespace Object{
		class  IFiber{//�t�@�C�o�N���X�B���N���X�Ƃ���
		public:
			virtual void Process()=0;//���ۂ̏����B
			virtual void Suspend()=0;//���f�BProcess���ŌĂяo��
			virtual bool Run()=0;//�g�p�҂��Ăяo��
			virtual int GetStackRest()=0;//�X�^�b�N�̎c���Ԃ�
			virtual bool isFiberEnd()=0;//�t�@�C�o���I���������ǂ���
		};
		class  IObject{
		public:
			virtual ~IObject(){};
			virtual Sint32 GetProcessPriority(void)=0;
			virtual void Init(void)=0;
			virtual void Process(void)=0;//����
			virtual void Draw(void)=0;//�`��
			virtual void Release(void)=0;//�I�u�W�F�N�g���^�X�N����O����钼�O�ɌĂ΂��
			virtual void BeforeRenderBegin(void)=0;//Begin����O
			virtual void OnDie(void)=0;//�I�u�W�F�N�g���S��
			virtual void OnUpdate(void)=0;//Update���Ă΂ꂽ�Ƃ�
			virtual void Update()=0;//�A�b�v�f�[�g����
			virtual bool isDead()=0;
			virtual void Die()=0;//���S������
			virtual bool _RunProcess()=0;//�v���Z�X���s�B
			virtual void _SuspendProcess()=0;
			virtual int GetRestProcessStack()=0;
			virtual void Update(Sint32 FrameNum)=0;//�w��t���[�����ҋ@
			virtual CObjectContainer *GetCObjectContainer()=0;
			virtual void SetCObjectContainer(CObjectContainer *pObjectContainer)=0;
		};
		
		class  ISprite2D{
		public:	
			virtual ~ISprite2D(){};
			virtual int AddCollisionData(Collision2D::CCollisionData2D * pCollisionData2D)=0;//�����蔻��ǉ�
			virtual int AddCollisionData(Selene::Math::Rect2DF &cpos,bool isAbsPath)=0;//�����蔻��(�l�p�`)
			virtual int AddCollisionData(Selene::Collision::CCircle &cpos,bool isAbsPath)=0;//�����蔻��(�~)
			virtual int AddCollisionData(Selene::Collision::CLine2D &cpos,bool isAbsPath)=0;//�����蔻��(��)
			virtual int AddCollisionData(Selene::Math::Vector2D &cpos,bool isAbsPath)=0;//�����蔻��(�_)
			virtual void Update()=0;//�X�V�����㏑��
			virtual void Update(Sint32 FrameCount)=0;//�X�V�����㏑��
			virtual void EnableCollisionDetect()=0;//�����蔻���L����
			virtual void DisableCollisionDetect()=0;//�����蔻��𖳌���
			virtual int CollisionCheck2D(Collision2D::CCollisionResult2D * &result)=0;//�Փ˃`�F�b�N
		};
	};
};
