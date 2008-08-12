#pragma once
#include "Base/Base.h"
#include "Manager/CollisionManager.h"
#include "Objects/Object.h"
//2D�X�v���C�g�I�u�W�F�N�g
namespace TiGLiCS{
	namespace Object{
		/**
			@brief 2D�X�v���C�g�N���X
			@author my04337

			���̃N���X�́A2D�ł̃I�u�W�F�N�g�̕`��,�Փ˔���̊ȒP��<br>
			���s�����߂ɍ쐬���ꂽ�B�ʏ��2D�V���[�e�B���O��A�N�V�����n�Q�[���ł�<br>
			���̃N���X���g�p���邱�ƂŎ�Ԃ̌y�����͂����ƍl����B
		*/
		class  CSprite2D:public ISprite2D,public CObject{
			bool bCollisionDetect2D;//�����蔻�菈�����s����
			Collision2D::CollisionData2DList CollisionList2D;//�����蔻��̃��X�g
			void UpdateCollisionData();//�����蔻��X�V
		public:	
			///�`��}�l�[�W���ւ̃|�C���^
			Manager::CRenderManager	*pRenderManager;
			///�X�v���C�g���W
			Selene::Math::Point2DF pos;
			///�X�v���C�g�̊p�x
			Sint32 Angle;
			/**
				@brief �R���X�g���N�^
				@author my04337
				@param pPage [in] �y�[�W�ւ̃|�C���^
				@param pos [in] ���W
				@param Angle [in] �p�x
				@param ProcessPriority [in] �����D��x
				
				�R���X�g���N�^�B�p�x��Selene��
			*/
			CSprite2D(CPage *pPage,
					  Selene::Math::Point2DF &pos,//�X�v���C�g���W
					  Sint32 Angle,
					  Sint32 ProcessPriority//�����D��x
					  );
			virtual ~CSprite2D();//�f�X�g���N�^

			//�����蔻��n
			Collision2D::CollisionData2DList * GetCollisionList2D(){return &CollisionList2D;}//�����蔻�胊�X�g��

			int AddCollisionData(Collision2D::CCollisionData2D * pCollisionData2D);//�����蔻��ǉ�
			/**
				@brief �Փ˔���ǉ�(�l�p�`)
				@author my04337
				@param cpos [in] �Փ˔���g
				@param isAbsPath [in] ��΍��W���ǂ���
				@return �Փ˔���ID

				�l�p�`�̏Փ˔����ǉ�����B���΍��W�Ƃ���ƃI�u�W�F�N�g�̍��W�A��]�����f�����B<br>
				�߂�l�͏Փ˔���ID�ŁA�Փ˔���̒ǉ�����<br>
				0 , 1 , 2 , ... �Ƃ������l�ƂȂ�B<br>
				�܂��A�Փ˔��肪�L���Ȏ��ɂ͒ǉ��ł��Ȃ����߁A�ꎞ�I�ɖ���������K�v������B
			*/
			int AddCollisionData(Selene::Math::Rect2DF &cpos,bool isAbsPath);//�����蔻��(�l�p�`)

			/**
				@brief �Փ˔���ǉ�(�~)
				@author my04337
				@param cpos [in] �Փ˔���g
				@param isAbsPath [in] ��΍��W���ǂ���
				@return �Փ˔���ID

				�~�̏Փ˔����ǉ�����B���΍��W�Ƃ���ƃI�u�W�F�N�g�̍��W�A��]�����f�����B<br>
				�߂�l�͏Փ˔���ID�ŁA�Փ˔���̒ǉ�����<br>
				0 , 1 , 2 , ... �Ƃ������l�ƂȂ�B<br>
				�܂��A�Փ˔��肪�L���Ȏ��ɂ͒ǉ��ł��Ȃ����߁A�ꎞ�I�ɖ���������K�v������B
			*/
			int AddCollisionData(Selene::Collision::CCircle &cpos,bool isAbsPath);//�����蔻��(�~)

			/**
				@brief �Փ˔���ǉ�(��)
				@author my04337
				@param cpos [in] �Փ˔���g
				@param isAbsPath [in] ��΍��W���ǂ���
				@return �Փ˔���ID

				���̏Փ˔����ǉ�����B���΍��W�Ƃ���ƃI�u�W�F�N�g�̍��W�A��]�����f�����B<br>
				�߂�l�͏Փ˔���ID�ŁA�Փ˔���̒ǉ�����<br>
				0 , 1 , 2 , ... �Ƃ������l�ƂȂ�B<br>
				�܂��A�Փ˔��肪�L���Ȏ��ɂ͒ǉ��ł��Ȃ����߁A�ꎞ�I�ɖ���������K�v������B
			*/
			int AddCollisionData(Selene::Collision::CLine2D &cpos,bool isAbsPath);//�����蔻��(��)
			
			/**
				@brief �Փ˔���ǉ�(�_)
				@author my04337
				@param cpos [in] �Փ˔���g
				@param isAbsPath [in] ��΍��W���ǂ���
				@return �Փ˔���ID

				�_�̏Փ˔����ǉ�����B���΍��W�Ƃ���ƃI�u�W�F�N�g�̍��W�A��]�����f�����B<br>
				�߂�l�͏Փ˔���ID�ŁA�Փ˔���̒ǉ�����<br>
				0 , 1 , 2 , ... �Ƃ������l�ƂȂ�B<br>
				�܂��A�Փ˔��肪�L���Ȏ��ɂ͒ǉ��ł��Ȃ����߁A�ꎞ�I�ɖ���������K�v������B
			*/
			int AddCollisionData(Selene::Math::Vector2D &cpos,bool isAbsPath);//�����蔻��(�_)

			/**
				@brief �Փ˔���ǉ�(�|���S��)
				@author my04337
				@param vecArray [in] �Փ˔���g
				@param vecNum [in] �Փ˔���_��
				@param isAbsPath [in] ��΍��W���ǂ���
				@return �Փ˔���ID

				�_�̏Փ˔����ǉ�����B���΍��W�Ƃ���ƃI�u�W�F�N�g�̍��W�A��]�����f�����B<br>
				�߂�l�͏Փ˔���ID�ŁA�Փ˔���̒ǉ�����<br>
				0 , 1 , 2 , ... �Ƃ������l�ƂȂ�B<br>
				�܂��A�Փ˔��肪�L���Ȏ��ɂ͒ǉ��ł��Ȃ����߁A�ꎞ�I�ɖ���������K�v������B
			*/
			int AddCollisionData(Selene::Math::Vector2D *vecArray,Sint32 vecSize,bool isAbsPath);//�����蔻��(�_)

			/**
				@brief �Փ˔���g�`��
				@author my04337
				@param Priority [in] �`��D��x

				�Փ˔���g�̕`����s���B�`��F�͍��ł���B
			*/
			void DrawCollisionData(Sint32 Priority);

			/**
				@brief �A�b�v�f�[�g
				@author my04337				

				�Փ˔���̍X�V�Ƒҋ@���s���B
			*/
			virtual void Update();//�X�V�����㏑��
			/**
				@brief �A�b�v�f�[�g
				@author my04337				

				�Փ˔���̍X�V�Ƒҋ@���s���B�w��t���[���ҋ@
			*/
			virtual void Update(Sint32 FrameCount);//�X�V�����㏑��
			
			/**
				@brief �Փ˔���L����
				@author my04337

				�Փ˔����L���ɂ���B
			*/
			void EnableCollisionDetect();//�����蔻���L����
			/**
				@brief �Փ˔��薳����
				@author my04337

				�Փ˔���𖳌��ɂ���B
			*/
			void DisableCollisionDetect();//�����蔻��𖳌���

			/*
				@brief�@�Փ˔���
				@author my04337
				@param result [out] �Փ˔��茋��
				@return �Փˌ�

				����2D�X�v���C�g�Ƃ̏Փ˔�����s���B<br>
				�߂�l��0�ł͂Ȃ��Ƃ��́A�K��result�ɑ΂�delete���g������<br>
				(�g��Ȃ��ꍇ�A���������[�N�ƂȂ�)
			*/
			int CollisionCheck2D(Collision2D::CCollisionResult2D * &result);//�Փ˃`�F�b�N
		};
	};
};