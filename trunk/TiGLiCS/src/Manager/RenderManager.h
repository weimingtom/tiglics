#pragma once
#include "Manager/FontManager.h"
#include "Manager/TextureManager.h"
#include "Base/Base.h"
#include <map>
#include <list>
#include <vector>
using namespace Selene;
namespace TiGLiCS{
	namespace Manager{
		/**
			@brief �`��}�l�[�W��
			@author my04337

			�`�揇���ƃ��\�[�X�̊Ǘ����s���N���X�B<br>
			���2D�̕`����T�|�[�g���邪�A�V�[���}�l�[�W�����擾���邱�Ƃ�<br>
			����3D�̕`����s�����Ƃ��ł���B
		*/
		class  CRenderManager{//�`��}�l�[�W���B�V���O���g��
			//-----�N���X�Q--------------------------------
			class CSprite2DManager{
			public:
				Renderer::Object::ISprite2D * pSpr;//�X�v���C�g
				Sint32 TextureID;//�e�N�X�`��
				Sint32 Priority;//�D��x
				Sint32 DrawNum;//�`�搔
				Sint32 UnUsedFrame;//���g�p�t���[����
				CSprite2DManager(Sint32 TextureID,Sint32 Priority);
				~CSprite2DManager(){SAFE_RELEASE(pSpr);}
			};
			class CFontSprite2DManager{
			public:
				Renderer::Object::IFontSprite2D * pFontSpr;//�X�v���C�g
				Sint32 FontID;//�e�N�X�`��
				Sint32 Priority;//�D��x
				Sint32 DrawNum;//�`�搔
				Sint32 UnUsedFrame;//���g�p�t���[����
				CFontSprite2DManager(Sint32 FontID,Sint32 Priority);
				~CFontSprite2DManager(){SAFE_RELEASE(pFontSpr);}
			};
			class CPrimitive2DManager{
			public:
				Renderer::Object::IPrimitive2D * pPrimitive;//�X�v���C�g
				Sint32 Priority;//�D��x
				Sint32 DrawNum;//�`�搔
				Sint32 UnUsedFrame;//���g�p�t���[����
				CPrimitive2DManager(Sint32 Priority);
				~CPrimitive2DManager(){SAFE_RELEASE(pPrimitive);}
			};
			class CLine2DManager{
			public:
				Renderer::Object::ILine2D * pLine;//�X�v���C�g
				Sint32 Priority;//�D��x
				Sint32 DrawNum;//�`�搔
				Sint32 UnUsedFrame;//���g�p�t���[����
				CLine2DManager(Sint32 Priority);
				~CLine2DManager(){SAFE_RELEASE(pLine);}
			};
			class CPoint2DManager{
			public:
				Renderer::Object::IPoint2D  * pPoint;//�X�v���C�g
				Sint32 Priority;//�D��x
				Sint32 DrawNum;
				Sint32 UnUsedFrame;//���g�p�t���[����
				CPoint2DManager(Sint32 Priority);
				~CPoint2DManager(){SAFE_RELEASE(pPoint);}
			};

			class CSceneManager{
			public:
				Scene::ISceneManager   * pScene;//�V�[��
				Sint32 Priority;//�D��x
				Math::Vector4D ClearColor;//���������̐F
				CSceneManager(Sint32 Priority){
					this->Priority=Priority;
				}
				~CSceneManager(){SAFE_RELEASE(pScene);}
				void SetSceneManager(Scene::ISceneManager   * pScene){
					this->pScene=pScene;
				}
			};

			typedef std::multimap<Sint32,CSprite2DManager*>tSpriteList2D;
			typedef std::multimap<Sint32,CFontSprite2DManager*>tFontSpriteList2D;
			typedef std::multimap<Sint32,CPrimitive2DManager*>tPrimitiveList2D;
			typedef std::multimap<Sint32,CLine2DManager*>tLineList2D;
			typedef std::multimap<Sint32,CPoint2DManager*>tPointList2D;

			//typedef std::list<CLine3DManager*>tLineList3D;

			tSpriteList2D		SpriteList2D;
			tFontSpriteList2D	FontSpriteList2D;
			tPrimitiveList2D	PrimitiveList2D;
			tLineList2D		LineList2D;
			tPointList2D	PointList2D;
			
			//tLineList3D		LineList3D;


			Sint32 UnitPrimitiveSize2D;//���̒P�ʂ�2D�I�u�W�F�N�g�ǉ��폜���s���B
			Sint32 MaxActorNum;//�ő�A�N�^�[�� ���葤�Œ������Ă��炤
			CColor DefaultBackColor;
			static CRenderManager * Instance;
			char str_buf[1024];//�����񐶐��p�o�b�t�@�B�R�X�g�팸�̂���

			CSprite2DManager * GetCSprite2DManager(Sint32 TexutrID,Sint32 Priority);
			CFontSprite2DManager * GetCFontSprite2DManager(Sint32 FontID,Sint32 DrawNum,Sint32 Priority);
			CPrimitive2DManager * GetCPrimitive2DManager(Sint32 DrawNum,Sint32 Priority);
			CLine2DManager * GetCLine2DManager(Sint32 DrawNum,Sint32 Priority);
			CPoint2DManager * GetCPoint2DManager(Sint32 Priority);

			CRenderManager();//�R���X�g���N�^
			~CRenderManager(){}//�f�X�g���N�^
		public:
			static CRenderManager * GetInstance(){return Instance;}
			static void Release();
			///�V�[���}�l�[�W���ւ̃|�C���^
			CSceneManager * pSceneManager;
			
			
			

			/**
				@brief �V�[���}�l�[�W���̍쐬
				@author my04337
				@param isPixelShaderEnable [in] PixelShader��L���ɂ��邩
				@param Priority [in] �`��D��x
				@return �V�[���}�l�[�W���ւ̃|�C���^

				�V�[���}�l�[�W���̍쐬���s���B�߂�l�̓V�[���}�l�[�W���ւ̃|�C���^�ł���B
			*/
			Scene::ISceneManager * CreateSceneManager(bool isPixelShaderEnable,Sint32 Priority);

			inline Scene::ISceneManager * GetSceneManager(){return (pSceneManager->pScene);}

			inline void SetBackgroundColor(CColor &col){DefaultBackColor=col;}
			//2D�n----------------------------------------------------------
			//�X�v���C�g�n
			/**
				@brief 2D�X�v���C�g�`��
				@author my04337
				@param Pos [in] ���W
				@param TextureID [in] �e�N�X�`��ID
				@param TexRectID [in] �e�N�X�`���͈�ID
				@param Priority [in] �`��D��x

				2D�X�v���C�g�̕`����s���B�`�悳�����W�͎����I�Ƀe�N�X�`���̒��S�ƂȂ�B
			*/
			void DrawSprite(Math::Point2DF &Pos,Sint32 TextureID,Sint32 TexRectID,Sint32 Priority);//�X�v���C�g�`��A��]�Ȃ�
			
			/**
				@brief 2D�X�v���C�g�`�� ��]����
				@author my04337
				@param Pos [in] ���W
				@param TextureID [in] �e�N�X�`��ID
				@param TexRectID [in] �e�N�X�`���͈�ID
				@param Priority [in] �`��D��x
				@param Angle [in] �p�x

				��]����2D�X�v���C�g�̕`����s���B�`�悳�����W�͎����I�Ƀe�N�X�`���̒��S�ƂȂ�B
			*/
			void DrawSprite(Math::Point2DF &Pos,Sint32 TextureID,Sint32 TexRectID,Sint32 Priority,Sint32 Angle);//�X�v���C�g�`��

			//�e�L�X�g�n---------------------------------------------------------------------------
			/**
				@brief 2D������`��
				@author my04337
				@param DrawPos [in] �`����W
				@param col [in] �`��F
				@param FontID [in] �t�H���gID
				@param Priority [in] �`��D��x
				@param src [in] ����������
				
				2D�e�L�X�g�̕`����s���BDrawPos��������̉E��[�ƂȂ�B���s�����ꍇ�������ʒu�ɕ`��ł��Ȃ��B<br>
				src , ... ��printf�Ɠ����̏����ł���B
			*/
			void DrawString(Math::Point2DF &DrawPos,CColor &col,Sint32 FontID,Sint32 Priority,const char * src,...);//������`��

			//�v���~�e�B�u�n-------------------------------------------------------------------------
			
			/**
				@brief 2D�h��Ԃ��O�p�`�`��
				@author my04337
				@param Pos1 [in] �`����W1
				@param Pos2 [in] �`����W2
				@param Pos3 [in] �`����W3
				@param col [in] �`��F
				@param Priority [in] �`��D��x
				
				�h��Ԃ���3�p�`��`�悷��B���_�͎��v���Ƀ\�[�g����K�v������B
			*/
			void FillTriangle(Math::Point2DF &Pos1,Math::Point2DF &Pos2,Math::Point2DF &Pos3,CColor &col,Sint32 Priority);//�O�p�`�h��Ԃ�
			
			/**
				@brief 2D�h��Ԃ��l�p�`�`��
				@author my04337
				@param pos [in] �`��͈�
				@param col [in] �`��F
				@param Priority [in] �`��D��x
				
				�h��Ԃ��������`��`�悷��B
			*/
			void FillRect(Math::Rect2DF &pos,CColor &col,Sint32 Priority);//�l�p�`�h��Ԃ�
			
			/**
				@brief 2D�h��Ԃ��l�p�`�`�� ��]����
				@author my04337
				@param pos [in] �`��͈�
				@param col [in] �`��F
				@param Priority [in] �`��D��x
				@param Angle [in] �p�x
				
				��]�����h��Ԃ��������`��`�悷��B
			*/
			void FillRect(Math::Rect2DF &pos,CColor &col,Sint32 Priority,Sint32 Angle);//�l�p�`�p�x�t��

			/**
				@brief 2D�h��Ԃ��~�`�`��
				@author my04337
				@param pos [in] �`��ʒu
				@param Radius [in] ���a
				@param col [in] �`��F
				@param Priority [in] �`��D��x
				
				�h��Ԃ����~��`�悷��B
			*/
			void FillCircle(Math::Point2DF &pos,float Radius,CColor &col,Sint32 Priority);//�~�h��Ԃ�

			/**
				@brief 2D�h��Ԃ����p�`�`��
				@author my04337
				@param posArray [in] ���W�z��̐擪�A�h���X
				@param posNum [in] ���_��
				@param col [in] �`��F
				@param Priority [in] �`��D��x
				
				�����̎O�p�`���A����������`�悷��B���p�`��`�悷��ۂ͎n�_�ƏI�_�����킹��K�v������B<br>
				���_�͎��v���ɕ���ł���K�v������B
			*/
			void FillPolygon(Math::Vector2D *posArray,Sint32 posNum,CColor &col,Sint32 Priority);//�|���S���`��
			
			//���C���n-----------------------------------------------------------------------------------------
			
			/**
				@brief 2D�l�p�`�`��
				@author my04337
				@param pos [in] �`��͈�
				@param col [in] �`��F
				@param Priority [in] �`��D��x
				
				�����`��`�悷��B
			*/
			void DrawRect(Math::Rect2DF &pos,CColor &col,Sint32 Priority);//�l�p�`
			
			/**
				@brief 2D�l�p�`�`�� ��]����
				@author my04337
				@param pos [in] �`��͈�
				@param col [in] �`��F
				@param Priority [in] �`��D��x
				@param Angle [in] �p�x
				
				��]���������`��`�悷��B
			*/
			void DrawRect(Math::Rect2DF &pos,CColor &col,Sint32 Priority,Sint32 Angle);//�l�p�`�p�x�t��
			
			/**
				@brief 2D�O�p�`�`��
				@author my04337
				@param Pos1 [in] �`����W1
				@param Pos2 [in] �`����W2
				@param Pos3 [in] �`����W3
				@param col [in] �`��F
				@param Priority [in] �`��D��x
				
				3�p�`��`�悷��B���_�͎��v���Ƀ\�[�g����K�v������B
			*/
			void DrawTriangle(Math::Point2DF &Pos1,Math::Point2DF &Pos2,Math::Point2DF &Pos3,CColor &col,Sint32 Priority);//�O�p�`�`��

			/**
				@brief 2D���`��
				@author my04337
				@param Pos1 [in] �n�_���W
				@param Pos2 [in] �I�_���W
				@param col [in] �`��F
				@param Priority [in] �`��D��x
				
				������`�悷��B
			*/
			void DrawLine(Math::Point2DF &Pos1,Math::Point2DF &Pos2,CColor &col,Sint32 Priority);//���C���`��

			/**
				@brief 2D���p�`�`��
				@author my04337
				@param posArray [in] ���W�z��̐擪�A�h���X
				@param posNum [in] ���_��
				@param col [in] �`��F
				@param Priority [in] �`��D��x
				
				�����̒������A����������`�悷��B���p�`��`�悷��ۂ͎n�_�ƏI�_�����킹��K�v������B<br>
				���_�͎��v���ɕ���ł���K�v������B
			*/
			void DrawPolygon(Math::Vector2D *posArray,Sint32 posNum,CColor &col,Sint32 Priority);//�|���S���`��
			
			/**
				@brief 2D�~�`�`��
				@author my04337
				@param pos [in] �`��ʒu
				@param Radius [in] ���a
				@param col [in] �`��F
				@param Priority [in] �`��D��x
				
				�~��`�悷��B
			*/
			void DrawCircle(Math::Point2DF &pos,float Radius,CColor &col,Sint32 Priority);//�~�`��

			//�|�C���g�n-----------------------------------------------------------------------------------------

			/**
				@brief 2D�_�`��
				@author my04337
				@param Pos [in] �`��ʒu
				@param col [in] �`��F
				@param Priority [in] �`��D��x
				
				�_��`�悷��B
			*/
			void DrawPoint(Math::Point2DF &Pos,CColor &col,Sint32 Priority);//�|�C���g�`��

			//�_�~�[---------------------------------------------------------------------------------------------

			void DrawDummy(Sint32 Priority);//�x���`�}�[�N�p

			void Begin();//�`��J�n�ʒm
			void End();//�`��I���ʒm
			void Rendering();//�`��I���ʒm
			void GabageCollection(Sint32 MaxCorllectNum=0);//�K�[�x�[�W�R���N�^
		};
	};
};