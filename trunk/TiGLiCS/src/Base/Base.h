/**
	@brief ��{�w�b�_�t�@�C��

	�e��pragma�ƃl�[���X�y�[�X�A�񋓑̂̒�`
*/

#pragma once

#pragma warning(disable:4800)///�u�[���l�� 'true' �܂��� 'false' �ɋ����I�ɐݒ肵�܂�
#pragma warning(disable:4611)///L4:setjmp�� C++ �I�u�W�F�N�g �f�X�g���N�V�����Ԃł̑��ݍ�p�ɂ͌݊���������܂���B
#pragma warning(disable:4731)///L4:�C�����C�� �A�Z���u�� �R�[�h�ɂ��ύX���ꂽ�t���[�� �|�C���^ ���W�X�^ 'register' �ł��B
#pragma warning(disable:4733)///L1:�C�����C�� asm �� 'FS:0' �Ɋ��蓖�ĂĂ��܂� : �n���h���͈��S�ȃn���h���Ƃ��ēo�^����Ă��܂���B
#pragma warning(disable:4251)///'identifier' : class 'type' �� __export �L�[���[�h���g���� class 'type2' �ɃG�N�X�|�[�g���Ă��������B(�N���X�p)
#pragma warning(disable:4505)///�Q�Ƃ���Ă��Ȃ����[�J���֐��͍폜����܂����B

#define WIN32_LEAN_AND_MEAN             // Windows �w�b�_�[����g�p����Ă��Ȃ����������O���܂��B
#include "Selene.h"
/**
	@brief ���C�u�������O���
*/
namespace TiGLiCS{

	 float drand(void);//����������Ԃ�
	 float drand(float min,float max);///���������͈͎w��^
	 void DMessageBox(const char *src,...);//�f�o�b�O�p���b�Z�[�W�{�b�N�X

	class CEngine;
	class CPage;

	/**
		@brief �Փˌn
		@author my04337
	*/
	namespace Collision2D{
			
		/**
			@brief �Փ˃^�C�v[�����p]
			@author my04337

			�R���W�����}�l�[�W���ɂĎg�p�B�����p
		*/
		enum eCollisionType{
			coPoint2D,			///�_
			coCircle2D,			///�~
			coLine2D,			///��
			coPolygon2D,		///���p�`
			coDummy,			///�_�~�[
		};
		class CCollisionData2D;			///���N���X
		class CPoint2DCollisionData;	///�_
		class CLine2DCollisionData;		///��
		class CCircle2DCollisionData;	///�~
		class CPolygon2DCollisionData;	///���p�`
		class CCollisionResult2D;		///�߂�l�^

	}
	/**
		@brief �Ǘ��n
		@author my04337
	*/
	namespace Manager{
		/**
			@brief �`��^�C�v[�����p]
			@author my04337
			@note
			�`��}�l�[�W���ɂĎg�p�B�����p<br>
			����D��x�̕`��I�u�W�F�N�g������ꍇ�A���̏��ŏ��������<br>

		*/
		enum eRequestDrawType{
			drSprite2D,			///�X�v���C�g
			drPoint2D,			///�_
			drLine2D,			///��
			drPrimitive2D,		///�v���~�e�B�u
			drFontSprite2D,		///�t�H���g�X�v���C�g
			drScene,			///3D�V�[��
			drDummy,			///�_�~�[�@�f�o�b�O�p
		};
		class CCollisionManager2D;	///�ՓˊǗ�
		class CFontManager;		///�t�H���g�S�̊Ǘ�
		class CFont;			///�t�H���g�P�̊Ǘ�
		class CPageManager;			///�y�[�W�Ǘ�
		class CFramemanager;		///�t���[���Ǘ�
		class CRenderManager;		///�`��Ǘ�
		class CSoundManager;	///SE�S�̊Ǘ�
		class CSound;		///SE�P�̊Ǘ�
		class CTexture;		///�e�N�X�`���Ǘ�
	}
	/**
		@brief �I�u�W�F�N�g�n
		@author my04337
	*/
	namespace Object{
		class CObject;			//��{�I�u�W�F�N�g
		class IObject;
		class CFiber;			//�t�@�C�o
		class IFiber;
		class CFiberBase;		//�t�@�C�o�Ǘ�
		class CObjectContainer;	//�I�u�W�F�N�g�R���e�i
		class CSprite2D;		//2D�I�u�W�F�N�g
	}

}

#include "Interface/Interface.h"