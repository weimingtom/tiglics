#pragma once
#include "Base/Base.h"
#include "Base/Define.h"
namespace TiGLiCS{
	namespace Collision2D{
		class  CCollisionData2D{
		public:
			Object::CSprite2D * pSpr2D;	//����p�X�v���C�g���W
			bool isAbsPos;				//��΍��W���ǂ���(��]�����邩���܂�)
			//�R���X�g���N�^
			CCollisionData2D(Object::CSprite2D * pSpr2D,bool isAbsPos=false){
				this->pSpr2D=pSpr2D;
				this->isAbsPos=isAbsPos;
			}
			//�f�X�g���N�^
			virtual ~CCollisionData2D(){
			}
			virtual void UpdatePos()=0;	///�Փˈʒu�X�V
			virtual eCollisionType GetCollisionType()=0;///�Փ˔���̃^�C�v
		};
		typedef std::list<Collision2D::CCollisionData2D*> CollisionData2DList;

		bool isCollision2D(CCollisionData2D * pCol1,CCollisionData2D* pCol2);

		class  CPoint2DCollisionData:public CCollisionData2D{
			//2D�_�̍��W�f�[�^
			Selene::Math::Vector2D pos;//���W
		public:
			Selene::Math::Vector2D retpos;//���W
			CPoint2DCollisionData(Object::CSprite2D * pSpr2D,Selene::Math::Vector2D &pos,bool isAbsPos)
				:CCollisionData2D(pSpr2D,isAbsPos)
				,pos(pos){
			}
			void UpdatePos();
			eCollisionType GetCollisionType(){return coPoint2D;}
			//Math::Vector2D GetCollisionPos();//�����蔻��p�̈ʒu��Ԃ��B
		};

		class  CLine2DCollisionData:public CCollisionData2D{
			//2D�_�̍��W�f�[�^
			Selene::Collision::CLine2D pos;//���W
		public:
			Selene::Collision::CLine2D retpos;//���W
			CLine2DCollisionData(Object::CSprite2D * pSpr2D,Selene::Collision::CLine2D &pos,bool isAbsPos)
				:CCollisionData2D(pSpr2D,isAbsPos)
				,pos(pos){
			}
			void UpdatePos();
			eCollisionType GetCollisionType(){return coLine2D;}
			//Collision::CLine2D GetCollisionPos();//�����蔻��p�̈ʒu��Ԃ��B
		};
		class  CCircle2DCollisionData:public CCollisionData2D{
			//2D�_�̍��W�f�[�^
			Selene::Collision::CCircle pos;//���W
		public:
			Selene::Collision::CCircle retpos;//���W
			CCircle2DCollisionData(Object::CSprite2D * pSpr2D,Selene::Collision::CCircle &pos,bool isAbsPos)
				:CCollisionData2D(pSpr2D,isAbsPos)
				,pos(pos){
			}
			void UpdatePos();
			eCollisionType GetCollisionType(){return coCircle2D;}
			//Collision::CCircle GetCollisionPos();//�����蔻��p�̈ʒu��Ԃ��B
		};
		class  CPolygon2DCollisionData:public CCollisionData2D{
			//2D�_�̍��W�f�[�^
			Selene::Math::Vector2D * pos;//���W
			Selene::Math::Vector2D * workpos;//���W
		public:
			Selene::Collision::CPolygon2D retpos;//��Ɨp���W
			Sint32 pointNum;//��
			CPolygon2DCollisionData(Object::CSprite2D * pSpr2D,Selene::Math::Vector2D * pos,Sint32 pointNum,bool isAbsPos)
				:CCollisionData2D(pSpr2D,isAbsPos){
					this->pos=pos;
					this->workpos=NULL;
					this->pointNum=pointNum;
			}
			~CPolygon2DCollisionData(){
				delete pos;
				SAFE_DELETE(workpos);
				//DMessageBox("a");
			}
			void UpdatePos();
			eCollisionType GetCollisionType(){return coPolygon2D;}
			//Collision::CPolygon2D GetCollisionPos();//�����蔻��p�̈ʒu��Ԃ��B
		};
		/**
			@brief �Փ˔���߂�l�N���X
			@author my04337

			�Փ˔���ł̖߂�l�N���X�B
		*/
		class  CCollisionResult2D{
		public:
			/**
				@brief �Փ˔���߂�l�\����
				@author my04337

				���̍\���̂ɏՓˏꏊ�Ƒ���̏�񂪊i�[�����B
			*/
			typedef struct tResult{
				///�����̓����蔻��ԍ�
				int srcNum;
				///����̓����蔻��ԍ�
				int dstNum;
				///�Փ˂����I�u�W�F�N�g�ւ̃|�C���^
				Object::CSprite2D * dstObj;
			};
			/**
				@brief �Փ˔���߂�l�^
				@author my04337

				�Փ˔���̖߂�l�^
			*/
			typedef std::list<tResult*> tResultList;
			tResultList ResultList;//�Փ˔���߂�l���X�g
			/**
				@brief �f�X�g���N�^
				@author my04337	
			*/
			~CCollisionResult2D(){
				for(tResultList::iterator it=ResultList.begin();it!=ResultList.end();++it){
					delete *it;
				}
			}
			/**
				@brief �Փˌ��ʂ̒ǉ�[�����p]
				@author my04337

				�Փˌ��ʂ��i�[����
			*/
			void AddResult(int srcNum,int dstNum,Object::CSprite2D * dstObj){
				tResult * ret=new tResult;
				ret->srcNum=srcNum;
				ret->dstNum=dstNum;
				ret->dstObj=dstObj;
				ResultList.push_back(ret);
			}
			/**
				@brief �Փˌ��ʐ��̎擾
				@author my04337
				@return �Փˌ��ʐ�

				�Փˌ��ʂ̐����擾����B
			*/
			int GetResultNum(){return (int)ResultList.size();}
		};
	};

	namespace Manager{
		class  CCollisionManager2D{
			Object::PtrPriorityList CollisionList;//�����蔻��p���X�g
			CPage* pPage;	//�y�[�W�N���X
		public:
			CCollisionManager2D(CPage * pPage);
			void RegisterCollisionObject(Object::CSprite2D* pObj);//�����蔻��̓o�^
			void UnRegisterCollisionObject(Object::CSprite2D* pObj);//�����蔻��̓o�^����
			int CollisionCheck(Object::CSprite2D * srcObj,Collision2D::CCollisionResult2D * &result);//�Փ˃`�F�b�N�B�߂�l��delete������K�v����
		};
	};
};