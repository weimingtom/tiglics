#pragma once


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include <windows.h>


//-----------------------------------------------------------------------------------
// WARNING
//-----------------------------------------------------------------------------------
#pragma inline_depth ( 255 )
#pragma inline_recursion ( on )

#pragma warning ( disable: 4100 )
#pragma warning ( disable: 4819 )
#pragma warning ( disable: 4201 )
#pragma warning ( disable: 4239 )
#pragma warning ( disable: 4995 )
#pragma warning ( disable: 4996 )
#pragma warning ( disable: 4324 )


//-----------------------------------------------------------------------------------
// LIBRARY
//-----------------------------------------------------------------------------------
#pragma comment( lib, "ole32.lib" )
#pragma comment( lib, "gdi32.lib" )
#pragma comment( lib, "user32.lib" )
#pragma comment( lib, "comdlg32.lib" )
#pragma comment( lib, "advapi32.lib" )


//-----------------------------------------------------------------------------------
// TYPEDEF
//-----------------------------------------------------------------------------------
typedef char					Sint8;					///< signed char �^�̕ʒ�`
typedef short					Sint16;					///< signed short �^�̕ʒ�`
typedef long					Sint32;					///< signed long �^�̕ʒ�`
typedef long long				Sint64;					///< signed long �^�̕ʒ�`
typedef unsigned char			Uint8;					///< unsigned char �^�̕ʒ�`
typedef unsigned short			Uint16;					///< unsigned short �^�̕ʒ�`
typedef unsigned long			Uint32;					///< unsigned long �^�̕ʒ�`
typedef unsigned long long		Uint64;					///< unsigned long long �^�̕ʒ�`
typedef float					Float;					///< float �^�̕ʒ�`
typedef double					Double;					///< double �^�̕ʒ�`
typedef long					Bool;					///< bool �^�̕ʒ�`


//-----------------------------------------------------------------------------------
// DEFINE
//-----------------------------------------------------------------------------------
#define ef									else if															///< else if �ȗ��p�}�N��

#define PI									(3.141592653589793238462643383279f)								///< ��
#define PI2									(6.283185307179586476925286766559f)								///< 2��
#define REV(val)							(1.0f/toF(val))													///< �t���Z�o�}�N��

#define AXIS_RANGE_MAX						(4096)															///< �W���C�X�e�B�b�N�̎��̍ő�l

#define toF(val)							((Float)(val))													///< float�ւ̃L���X�g
#define toI(val)							((Sint32)(val))													///< int�ւ̃L���X�g

#define MIN(N1,N2)							((N1 < N2) ? (N1) : (N2))										///< �ŏ��l�擾�}�N��
#define MAX(N1,N2)							((N1 > N2) ? (N1) : (N2))										///< �ő�l�擾�}�N��
#define SWAP(N1,N2)							{ N1 = N2 - N1; N2 -= N1; N1 += N2; }							///< �l�����}�N��

#define SAFE_ADDREF(val)					if ( (val) != NULL ) { (val)->AddRef(); }						///< COM���SAddRef�}�N��
#define SAFE_RELEASE(val)					if ( (val) != NULL ) { (val)->Release(); (val) = NULL; }		///< COM���SRelease�}�N��
#define SAFE_DELETE(val)					if ( (val) != NULL ) { delete (val); (val) = NULL; }			///< new���������S���
#define SAFE_DELETE_ARRAY(val)				if ( (val) != NULL ) { delete [] (val); (val) = NULL; }			///< new[]���������S���

#define ANGLE_TABLE_BIT						(16)															///< �T�C���e�[�u���̃r�b�g��
#define ANGLE_MAX							(1 << ANGLE_TABLE_BIT)											///< �T�C���e�[�u���̃T�C�Y
#define ANGLE_TABLE_MASK					(ANGLE_MAX - 1)													///< �T�C���e�[�u���̃A�N�Z�X�p�}�X�N
#define NORMALIZE_ANGLE(val)				((val) & ANGLE_TABLE_MASK)										///< �p�x�̐��K��
#define DEG_TO_ANGLE(val)					toI(toF(val) * toF(ANGLE_MAX) / 360.0f)							///< �x���@�����p�p�x
#define ANGLE_TO_DEG(val)					((val) * 360 / ANGLE_MAX)										///< �x���@�����p�p�x
#define PI_TO_ANGLE(val)					toI(toF(val) * toF(ANGLE_MAX) / PI2)							///< �ʓx�@�����p�p�x
#define ANGLE_TO_PI(val)					(toF(val) * PI2 / toF(ANGLE_MAX))								///< ��p�p�x����ʓx�@

#define MemoryClear(PD,S)					::FillMemory((PD),(S),0x00)										///< �������N���A
#define MemoryFill(PD,PS,S)					::FillMemory((PD),(S),(PS))										///< �������h��Ԃ�
#define MemoryMove(PD,PS,S)					::MoveMemory((PD),(PS),(S))										///< �������ړ�
#define MemoryCopy(PD,PS,S)					::CopyMemory((PD),(PS),(S))										///< �������R�s�[


//-----------------------------------------------------------------------------------
// DEFINE
//-----------------------------------------------------------------------------------
#ifdef LIB_SELENE
#	define SELENE_DLL_API
#else // LIB_SELENE
#	ifdef DLL_SELENE
#		define SELENE_DLL_API	__declspec(dllexport)
#	else // DLL_SELENE
#		define SELENE_DLL_API	__declspec(dllimport)
#	endif // DLL_SELENE
#endif // LIB_SELENE


//-----------------------------------------------------------------------------------
// ENUM
//-----------------------------------------------------------------------------------
/**
	@brief ���C�u�������O���
*/
namespace Selene
{
	/**
		@brief ���_��`
		@author �t���`

		���_��`�N���X�̍쐬���Ɏw�肷��t���O�ł��B<BR>
		�Ȃ� VERTEX_ELEMENT_PRIMITIVE�AVERTEX_ELEMENT_SPRITE�AVERTEX_ELEMENT_3DBASE ��<BR>
		�Ɨ����Ă���r���ł��B
	*/
	enum eVertexElement
	{
		VERTEX_ELEMENT_PRIMITIVE	= 1 << 0,			///< �ʒu�ƐF�������܂ލł��P����2D�p���_
		VERTEX_ELEMENT_SPRITE		= 1 << 1,			///< �ʒu�ƐF�ƃe�N�X�`��UV���܂�2D�p���_
		VERTEX_ELEMENT_3DBASE		= 1 << 2,			///< �ʒu�ƐF���܂ނ����Ƃ��P����3D���_
		VERTEX_ELEMENT_3DTEXTURE	= 1 << 3,			///< �e�N�X�`��UV���܂ފ�{�I��3D�p���_
		VERTEX_ELEMENT_3DLIGHT		= 1 << 4,			///< ���C�e�B���O�Ɋւ���@�����܂�3D���_
		VERTEX_ELEMENT_3DBUMP		= 1 << 5,			///< �o���v�}�b�v�Ɋւ���ڐ����܂�3D���_
		VERTEX_ELEMENT_3DANIMATION	= 1 << 6,			///< �X�L�j���O�Ɋւ���{�[���̃C���f�b�N�X���E�F�C�g���܂�3D���_
	};

	/**
		@brief IParticle�p�^�C�v
		@author �t���`
	*/
	enum eParticleType
	{
		PARTICLE_TYPE_NORMAL,				///< �ʏ�p�[�e�B�N��
		PARTICLE_TYPE_VOLUME,				///< �^���{�����[���p�[�e�B�N��
	};

	/**
		@brief �t���[�����[�g��`
		@author �t���`
	*/
	enum eFrameRate
	{
		FRAME_RATE_60,					///< 1�t���[��1/60�b
		FRAME_RATE_30,					///< 1�t���[��1/30�b
		FRAME_RATE_20,					///< 1�t���[��1/20�b
		FRAME_RATE_15,					///< 1�t���[��1/15�b
	};

	/**
		@brief �A�_�v�^�[�^�C�v
		@author �t���`
	*/
	enum eGraphicCardNo
	{
		GRAPHIC_CARD_NO1,									///< �P�Ԗڂɐڑ����ꂽ�r�f�I�J�[�h
		GRAPHIC_CARD_NO2,									///< �Q�Ԗڂɐڑ����ꂽ�r�f�I�J�[�h

		GRAPHIC_CARD_DEFAULT_NO		= GRAPHIC_CARD_NO1,		///< �f�t�H���g�̃r�f�I�J�[�h
		GRAPHIC_CARD_NV_PERF_HUD	= 0xFFFFFFFF,			///< NVPerfHUD��p�̃r�f�I�J�[�h
	};

	/**
		@brief �T�[�t�F�C�X�t�H�[�}�b�g��`
		@author �t���`
	*/
	enum eSurfaceFormat
	{
		FORMAT_INVALID,						///< ����

		FORMAT_TEXTURE_32BIT,				///< 32Bit�e�N�X�`���t�H�[�}�b�g�ɏ���
		FORMAT_TEXTURE_16BIT,				///< 16Bit�e�N�X�`���t�H�[�}�b�g�ɏ���
		FORMAT_TEXTURE_DXT,					///< DXT���k�t�H�[�}�b�g�e�N�X�`��

		FORMAT_TARGET_UCHAR4,				///< unsnged char x4 �����_�����O�^�[�Q�b�g
		FORMAT_TARGET_FLOAT1,				///< float x1 �����_�����O�^�[�Q�b�g
		FORMAT_TARGET_FLOAT2,				///< float x2 �����_�����O�^�[�Q�b�g
		FORMAT_TARGET_FLOAT4,				///< float x4 �����_�����O�^�[�Q�b�g
		FORMAT_TARGET_FLOAT4_ALPHA,			///< float x4 �A���t�@�\�����_�����O�^�[�Q�b�g

		FORMAT_DEPTHBUFFER_SURFACE,			///< �[�x�o�b�t�@
		FORMAT_DEPTHBUFFER_TEXTURE,			///< �[�x�o�b�t�@

		FORMAT_MAX,

		FORMAT_TARGET_32BIT		= FORMAT_TARGET_UCHAR4,
		FORMAT_TARGET_HDR		= FORMAT_TARGET_FLOAT4_ALPHA,
	};

	/**
		@brief �e�N�X�`���X�e�[�W��`
		@author �t���`

		�e�N�X�`���X�e�[�W�Ɋւ��Ă̒�`�ł��B<BR>
		3D�I�u�W�F�N�g�Ɋւ��Ă͊�{�I�ɃV�F�[�_�[����<BR>
		UV���v�Z����悤�ɂȂ��Ă���̂ŁA<BR>
		���_�f�[�^�Ƃ��ĕێ�����UV�̓J���[�}�b�v�ƃ��C�g�}�b�v�����ł��B
	*/
	enum eTextureStage
	{
		TEXTURE_STAGE_COLOR			= 0,	///< �J���[�}�b�v
		TEXTURE_STAGE_LIGHT,				///< ���C�g�}�b�v
		TEXTURE_STAGE_ENVIRONMENT,			///< �L���[�u��
		TEXTURE_STAGE_SPECULAR,				///< �X�y�L�����}�b�v
		TEXTURE_STAGE_NORMAL,				///< �o���vor�����}�b�v�p�@���}�b�v

		TEXTURE_STAGE_SHADOW,				///< �V���h�E�}�b�v
		TEXTURE_STAGE_DEPTH,				///< �[�x�}�b�v

		TEXTURE_STAGE_TOON,					///< �g�D�[���p����}�b�v

		TEXTURE_STAGE_MAX,					///< �e�N�X�`���X�e�[�W��

		MATERIAL_TEXTURE_MAX = TEXTURE_STAGE_NORMAL + 1,
	};

	/**
		@brief �`��^�C�v��`
		@author �t���`

		�e��`��^�C�v�Ɋւ��Ă̒�`�ł��B
	*/
	enum eDrawType
	{
		DRAW_TYPE_NORMAL,					///< �ʏ�`��
		DRAW_TYPE_BLEND,					///< �������`��
		DRAW_TYPE_ADD,						///< ���Z�`��
		DRAW_TYPE_ADD_NOALPHA,				///< ���Z�`��i�A���t�@�l�����j
		DRAW_TYPE_SUB,						///< ���Z�`��
		DRAW_TYPE_SUB_NOALPHA,				///< ���Z�`��i�A���t�@�l�����j
		DRAW_TYPE_MULTIPLE,					///< ��Z�`��
	};

	/**
		@brief �J�����O�^�C�v��`
		@author �t���`

		�|���S���̕\���ɕ`��Ɋւ��Ă̒�`�ł��B
	*/
	enum eCullType
	{
		CULL_FRONT,							///< �\�̏ꍇ�̂ݕ`��
		CULL_BACK,							///< ���̏ꍇ�̂ݕ`��
		CULL_NONE,							///< ���\���ʕ`��
	};

	/**
		@brief �e�N�X�`���t�B���^�^�C�v��`
		@author �t���`

		�|���S���̕\���ɕ`��Ɋւ��Ă̒�`�ł��B
	*/
	enum eTextureFilterType
	{
		TEXTURE_FILTER_DISABLE,		///< �t�B���^�����O����
		TEXTURE_FILTER_2D,			///< �o�C���j�A�t�B���^�����O
		TEXTURE_FILTER_3D_LOW,		///< �o�C���j�A�t�B���^�����O
		TEXTURE_FILTER_3D_MIDDLE,	///< �ٕ����t�B���^�����O/��掿
		TEXTURE_FILTER_3D_HIGH,		///< �ٕ����t�B���^�����O/���掿
	};

	/**
		@brief �t�@�C���V�[�N��`
		@author �t���`
	*/
	enum eSeekFlag
	{
		SEEK_FILE_CURRENT,					///< �J�����g�ʒu
		SEEK_FILE_START,					///< �擪�ʒu
		SEEK_FILE_END,						///< �I�[�ʒu
	};

	/**
		@brief ���_�ϊ��^�C�v
		@author �t���`
	*/
	enum eTransformType
	{
		TRANSFORM_TYPE_MODEL,				///< ���f���p���_�ϊ�
		TRANSFORM_TYPE_BILLBOARD,			///< �r���{�[�h�p���_�ϊ�
	};

	/**
		@brief �o���v�^�C�v
		@author �t���`
	*/
	enum eBumpType
	{
		BUMP_TYPE_NONE,						///< �o���v�����Ȃ�
		BUMP_TYPE_ENABLE,					///< �o���v��������
	};

	/**
		@brief �X�y�L�����^�C�v
		@author �t���`
	*/
	enum eSpecularType
	{
		SPECULAR_TYPE_NONE,					///< �X�y�L���������Ȃ�
		SPECULAR_TYPE_ENABLE,				///< �X�y�L������������
	};

	/**
		@brief ���[�V�����u���[���x��
		@author �t���`
	*/
	enum eSceneMotionBlurQuarity
	{
		MOTION_BLUR_LIGHT,						///< ���f���������΂����s��Ȃ��y�ʂȃu���[
		MOTION_BLUR_FULL,						///< ���f���������΂����s���u���[

		MOTION_BLUR_MAX
	};

	/**
		@brief ��ʊE�[�x�^�C�v
		@author �t���`
	*/
	enum eSceneDepthOfFieldType
	{
		DOF_TYPE_DISABLE,						///< ��ʊE�[�x�Ȃ�
		DOF_TYPE_ENABLE,						///< ��ʊE�[�x����
	};

	/**
		@brief �t�H�O�^�C�v
		@author �t���`
	*/
	enum eSceneFogType
	{
		FOG_TYPE_DISABLE,						///< �t�H�O�Ȃ�
		FOG_TYPE_ENABLE,						///< �t�H�O����
	};

	/**
		@brief �A���`�G�C���A�X�^�C�v
		@author �t���`
	*/
	enum eSceneAntiAliasType
	{
		AA_TYPE_DISABLE,						///< �A���`�G�C���A�X�Ȃ�
		AA_TYPE_ENABLE,							///< �A���`�G�C���A�X����
	};

	/**
		@brief �t�H�O�G�t�F�N�g
		@author �t���`
	*/
	enum eSceneFogEffect
	{
		FOG_EFFECT_LINEAR,						///< ���`�t�H�O
//		FOG_EFFECT_SCATTERING,					///< �X�L���b�^�����O
	};

	/**
		@brief �V�F�[�f�B���O�^�C�v
		@author �t���`
	*/
	enum eSceneShadingType
	{
		SHADING_TYPE_NORMAL,					///< �ʏ�̃V�F�[�f�B���O
		SHADING_TYPE_TOON,						///< �g�D�[�����V�F�[�f�B���O
		SHADING_TYPE_HATCHING,					///< �n�b�`���O���V�F�[�f�B���O
	};

	/**
		@brief �V�[���p���[�V�����u���[�^�C�v
		@author �t���`
	*/
	enum eSceneMotionBlurType
	{
		MOTION_BLUR_TYPE_DISABLE,				///< �Ȃ�
		MOTION_BLUR_TYPE_LOW,					///< �N�I���e�B��F�S�T���v�����O
		MOTION_BLUR_TYPE_HIGH,					///< �N�I���e�B���F�W�T���v�����O
	};

	/**
		@brief �V�[���p�V���h�E�}�b�v�^�C�v
		@author �t���`
	*/
	enum eSceneShadowType
	{
		SHADOW_TYPE_DISABLE,				///< �e�Ȃ�
		SHADOW_TYPE_PROJECTION,				///< �v���W�F�N�V�����V���h�E
		SHADOW_TYPE_SHADOWMAP,				///< �V���h�E�}�b�s���O
	};

	/**
		@brief �V�[���p�V���h�E�N�I���e�B�^�C�v
		@author �t���`
	*/
	enum eSceneShadowQuarity
	{
		SHADOW_QUARITY_LOW,					///< ��𑜓x(512x512)
		SHADOW_QUARITY_MIDDLE,				///< ��𑜓x(1024x1024)
		SHADOW_QUARITY_HIGH,				///< ��𑜓x(2048x2048)
		SHADOW_QUARITY_BEST,				///< ��𑜓x(4096x4096)
	};

	/**
		@brief HDR����
		@author �t���`
	*/
	enum eSceneHighDynamicRangeType
	{
		HDR_TYPE_DISABLE,						///< HDR�����Ȃ�
		HDR_TYPE_ENABLE,						///< HDR��������
	};

	/**
		@brief HDR�G�t�F�N�g
		@author �t���`
	*/
	enum eSceneHighDynamicRangeEffect
	{
		HDR_EFFECT_BLOOM,						///< �u���[������
		HDR_EFFECT_CROSS,						///< �N���X�t�B���^
	};

	/**
		@brief ���e�V���h�E�p���
		@author �t���`
	*/
	enum eProjectionShadowType
	{
		PROJECTION_SHADOW_DISABLE,				///< �e�𗎂Ƃ����A�e�̉e�����Ȃ�
		PROJECTION_SHADOW_DROP_SIMPLE,			///< �ۉe�𗎂Ƃ��A�e�̉e���͎󂯂Ȃ�
		PROJECTION_SHADOW_DROP_SHAPE,			///< ���f���̌`��̉e�𗎂Ƃ��A�e�̉e���͎󂯂Ȃ�
	};

	/**
		@brief ���e�V���h�E�p�v���C�I���e�B
		@author �t���`
	*/
	enum eProjectionShadowPriority
	{
		PROJECTION_SHADOW_PRIORITY_0,			///< �e�𗎂Ƃ��Ȃ�
		PROJECTION_SHADOW_PRIORITY_1,			///< PROJECTION_SHADOW_PRIORITY_0�ȉ��ɉe�𗎂Ƃ�
		PROJECTION_SHADOW_PRIORITY_2,			///< PROJECTION_SHADOW_PRIORITY_1�ȉ��ɉe�𗎂Ƃ�
		PROJECTION_SHADOW_PRIORITY_3,			///< PROJECTION_SHADOW_PRIORITY_2�ȉ��ɉe�𗎂Ƃ�
		PROJECTION_SHADOW_PRIORITY_4,			///< PROJECTION_SHADOW_PRIORITY_3�ȉ��ɉe�𗎂Ƃ�

		PROJECTION_SHADOW_PRIORITY_MAX,
	};

	/**
		@brief �{�^�����
		@author �t���`
	*/
	enum eInputButtonState
	{
		BUTTON_STATE_FREE,					///< �����Ă��Ȃ���Ԏ擾�p
		BUTTON_STATE_HOLD,					///< ���������Ă����Ԏ擾�p
		BUTTON_STATE_PUSH,					///< �������u�Ԏ擾�p
		BUTTON_STATE_PULL,					///< �������u�Ԏ擾�p

		BUTTON_STATE_MAX,
	};

	/**
		@brief ����`
		@author �t���`
	*/
	enum eInputAxisType
	{
		AXIS_TYPE_01,						///< 1�Ԗڂ̎�
		AXIS_TYPE_02,						///< 2�Ԗڂ̎�
		AXIS_TYPE_03,						///< 3�Ԗڂ̎�
		AXIS_TYPE_04,						///< 4�Ԗڂ̎�

		AXIS_TYPE_MAX,
	};

	/**
		@brief �{�^�����
		@author �t���`
	*/
	enum eInputButtonType
	{
		BUTTON_AXIS1_UP,					///< ������w��
		BUTTON_AXIS1_DOWN,					///< �������w��
		BUTTON_AXIS1_LEFT,					///< �������w��
		BUTTON_AXIS1_RIGHT,					///< �E�����w��

		BUTTON_AXIS2_UP,					///< ������w��
		BUTTON_AXIS2_DOWN,					///< �������w��
		BUTTON_AXIS2_LEFT,					///< �������w��
		BUTTON_AXIS2_RIGHT,					///< �E�����w��

		BUTTON_AXIS3_UP,					///< ������w��
		BUTTON_AXIS3_DOWN,					///< �������w��
		BUTTON_AXIS3_LEFT,					///< �������w��
		BUTTON_AXIS3_RIGHT,					///< �E�����w��

		BUTTON_AXIS4_UP,					///< ������w��
		BUTTON_AXIS4_DOWN,					///< �������w��
		BUTTON_AXIS4_LEFT,					///< �������w��
		BUTTON_AXIS4_RIGHT,					///< �E�����w��

		BUTTON_01,							///< �{�^��1�w��
		BUTTON_02,							///< �{�^��2�w��
		BUTTON_03,							///< �{�^��3�w��
		BUTTON_04,							///< �{�^��4�w��
		BUTTON_05,							///< �{�^��5�w��
		BUTTON_06,							///< �{�^��6�w��
		BUTTON_07,							///< �{�^��7�w��
		BUTTON_08,							///< �{�^��8�w��
		BUTTON_09,							///< �{�^��9�w��
		BUTTON_10,							///< �{�^��10�w��
		BUTTON_11,							///< �{�^��11�w��
		BUTTON_12,							///< �{�^��12�w��
		BUTTON_13,							///< �{�^��13�w��
		BUTTON_14,							///< �{�^��14�w��
		BUTTON_15,							///< �{�^��15�w��
		BUTTON_16,							///< �{�^��16�w��

		BUTTON_AXIS_MAX,
		BUTTON_MAX		= BUTTON_16 - BUTTON_01,
		AXIS_MAX		= BUTTON_AXIS4_RIGHT - BUTTON_AXIS1_UP,

		BUTTON_DISABLE,						///< ����
	};

	/**
		@brief �W���C�X�e�B�b�N��������`
		@author �t���`
	*/
	enum ePadAxisDirection
	{
		PAD_AXIS_X,							///< X��
		PAD_AXIS_Y,							///< Y��
		PAD_AXIS_Z,							///< Z��

		PAD_AXIS_DIRECTION_MAX,
	};

	/**
		@brief �W���C�X�e�B�b�N����ޒ�`
		@author �t���`
	*/
	enum ePadAxisType
	{
		PAD_AXIS_POSITION,
		PAD_AXIS_POSITION_ROTATE,
		PAD_AXIS_VELOCITY,
		PAD_AXIS_VELOCITY_ROTATE,
		PAD_AXIS_ACCEL,
		PAD_AXIS_ACCEL_ROTATE,
		PAD_AXIS_FORCE,
		PAD_AXIS_FORCE_ROTATE,
		PAD_AXIS_POV,

		PAD_AXIS_MAX,
	};

	/**
		@brief �W���C�X�e�B�b�N�X���C�_�[��`
		@author �t���`
	*/
	enum ePadSliderType
	{
		PAD_SLIDER_0,							///< 1�Ԗڂ̃X���C�_�[
		PAD_SLIDER_1,							///< 2�Ԗڂ̃X���C�_�[
		PAD_SLIDER_2,							///< 3�Ԗڂ̃X���C�_�[
		PAD_SLIDER_3,							///< 4�Ԗڂ̃X���C�_�[

		PAD_SLIDER_MAX,
	};

	/**
		@brief �W���C�X�e�B�b�N�{�^����`
		@author �t���`
	*/
	enum ePadButtonType
	{
		PAD_BUTTON_01,
		PAD_BUTTON_02,
		PAD_BUTTON_03,
		PAD_BUTTON_04,
		PAD_BUTTON_05,
		PAD_BUTTON_06,
		PAD_BUTTON_07,
		PAD_BUTTON_08,
		PAD_BUTTON_09,
		PAD_BUTTON_10,
		PAD_BUTTON_11,
		PAD_BUTTON_12,
		PAD_BUTTON_13,
		PAD_BUTTON_14,
		PAD_BUTTON_15,
		PAD_BUTTON_16,

		PAD_BUTTON_MAX,
	};

	/**
		@brief ���z�L�[�R�[�h
		@author �t���`
	*/
	enum eVirtualKeyCode
	{
		SELENE_VK_ESCAPE          = 0x01,
		SELENE_VK_1               = 0x02,
		SELENE_VK_2               = 0x03,
		SELENE_VK_3               = 0x04,
		SELENE_VK_4               = 0x05,
		SELENE_VK_5               = 0x06,
		SELENE_VK_6               = 0x07,
		SELENE_VK_7               = 0x08,
		SELENE_VK_8               = 0x09,
		SELENE_VK_9               = 0x0A,
		SELENE_VK_0               = 0x0B,
		SELENE_VK_MINUS           = 0x0C,
		SELENE_VK_EQUALS          = 0x0D,
		SELENE_VK_BACK            = 0x0E,
		SELENE_VK_TAB             = 0x0F,
		SELENE_VK_Q               = 0x10,
		SELENE_VK_W               = 0x11,
		SELENE_VK_E               = 0x12,
		SELENE_VK_R               = 0x13,
		SELENE_VK_T               = 0x14,
		SELENE_VK_Y               = 0x15,
		SELENE_VK_U               = 0x16,
		SELENE_VK_I               = 0x17,
		SELENE_VK_O               = 0x18,
		SELENE_VK_P               = 0x19,
		SELENE_VK_LBRACKET        = 0x1A,
		SELENE_VK_RBRACKET        = 0x1B,
		SELENE_VK_RETURN          = 0x1C,
		SELENE_VK_LCONTROL        = 0x1D,
		SELENE_VK_A               = 0x1E,
		SELENE_VK_S               = 0x1F,
		SELENE_VK_D               = 0x20,
		SELENE_VK_F               = 0x21,
		SELENE_VK_G               = 0x22,
		SELENE_VK_H               = 0x23,
		SELENE_VK_J               = 0x24,
		SELENE_VK_K               = 0x25,
		SELENE_VK_L               = 0x26,
		SELENE_VK_SEMICOLON       = 0x27,
		SELENE_VK_APOSTROPHE      = 0x28,
		SELENE_VK_GRAVE           = 0x29,
		SELENE_VK_LSHIFT          = 0x2A,
		SELENE_VK_BACKSLASH       = 0x2B,
		SELENE_VK_Z               = 0x2C,
		SELENE_VK_X               = 0x2D,
		SELENE_VK_C               = 0x2E,
		SELENE_VK_V               = 0x2F,
		SELENE_VK_B               = 0x30,
		SELENE_VK_N               = 0x31,
		SELENE_VK_M               = 0x32,
		SELENE_VK_COMMA           = 0x33,
		SELENE_VK_PERIOD          = 0x34,
		SELENE_VK_SLASH           = 0x35,
		SELENE_VK_RSHIFT          = 0x36,
		SELENE_VK_MULTIPLY        = 0x37,
		SELENE_VK_LMENU           = 0x38,
		SELENE_VK_SPACE           = 0x39,
		SELENE_VK_CAPITAL         = 0x3A,
		SELENE_VK_F1              = 0x3B,
		SELENE_VK_F2              = 0x3C,
		SELENE_VK_F3              = 0x3D,
		SELENE_VK_F4              = 0x3E,
		SELENE_VK_F5              = 0x3F,
		SELENE_VK_F6              = 0x40,
		SELENE_VK_F7              = 0x41,
		SELENE_VK_F8              = 0x42,
		SELENE_VK_F9              = 0x43,
		SELENE_VK_F10             = 0x44,
		SELENE_VK_NUMLOCK         = 0x45,
		SELENE_VK_SCROLL          = 0x46,
		SELENE_VK_NUMPAD7         = 0x47,
		SELENE_VK_NUMPAD8         = 0x48,
		SELENE_VK_NUMPAD9         = 0x49,
		SELENE_VK_SUBTRACT        = 0x4A,
		SELENE_VK_NUMPAD4         = 0x4B,
		SELENE_VK_NUMPAD5         = 0x4C,
		SELENE_VK_NUMPAD6         = 0x4D,
		SELENE_VK_ADD             = 0x4E,
		SELENE_VK_NUMPAD1         = 0x4F,
		SELENE_VK_NUMPAD2         = 0x50,
		SELENE_VK_NUMPAD3         = 0x51,
		SELENE_VK_NUMPAD0         = 0x52,
		SELENE_VK_DECIMAL         = 0x53,
		SELENE_VK_OEM_102         = 0x56,
		SELENE_VK_F11             = 0x57,
		SELENE_VK_F12             = 0x58,
		SELENE_VK_KANA            = 0x70,
		SELENE_VK_ABNT_C1         = 0x73,
		SELENE_VK_CONVERT         = 0x79,
		SELENE_VK_NOCONVERT       = 0x7B,
		SELENE_VK_YEN             = 0x7D,
		SELENE_VK_ABNT_C2         = 0x7E,
		SELENE_VK_NUMPADEQUALS    = 0x8D,
		SELENE_VK_PREVTRACK       = 0x90,
		SELENE_VK_NUMPADENTER     = 0x9C,
		SELENE_VK_RCONTROL        = 0x9D,
		SELENE_VK_NUMPADCOMMA     = 0xB3,
		SELENE_VK_DIVIDE          = 0xB5,
		SELENE_VK_SYSRQ           = 0xB7,
		SELENE_VK_RMENU           = 0xB8,
		SELENE_VK_PAUSE           = 0xC5,
		SELENE_VK_HOME            = 0xC7,
		SELENE_VK_UP              = 0xC8,
		SELENE_VK_PRIOR           = 0xC9,
		SELENE_VK_LEFT            = 0xCB,
		SELENE_VK_RIGHT           = 0xCD,
		SELENE_VK_END             = 0xCF,
		SELENE_VK_DOWN            = 0xD0,
		SELENE_VK_NEXT            = 0xD1,
		SELENE_VK_INSERT          = 0xD2,
		SELENE_VK_DELETE          = 0xD3,
		SELENE_VK_LWIN            = 0xDB,
		SELENE_VK_RWIN            = 0xDC,

		SELENE_VK_DISABLE         = 0x00
	};

	/**
		@brief �}�E�X�{�^����Ԓ�`
		@author �t���`
	*/
	enum eMouseState
	{
		MOUSE_FREE,							///< �}�E�X�{�^���͉�����Ă��Ȃ�
		MOUSE_PULL,							///< �}�E�X�{�^���͗����ꂽ
		MOUSE_PUSH,							///< �}�E�X�{�^���͉����ꂽ
		MOUSE_HOLD,							///< �}�E�X�{�^���͉�����Â��Ă���
	};

	/**
		@brief �����V�~�����[�V�����p�ڐG�_��`
		@author �t���`
	*/
	enum eContactMode
	{
		ContactMu2			= 0x001,
		ContactFDir1		= 0x002,
		ContactBounce		= 0x004,
		ContactSoftERP		= 0x008,
		ContactSoftCFM		= 0x010,
		ContactMotion1		= 0x020,
		ContactMotion2		= 0x040,
		ContactSlip1		= 0x080,
		ContactSlip2		= 0x100,

		ContactApprox0		= 0x0000,
		ContactApprox1_1	= 0x1000,
		ContactApprox1_2	= 0x2000,
		ContactApprox1		= 0x3000,
	};

	/**
		@brief �`��n
	*/
	namespace Renderer
	{
		/**
			@brief �V�F�[�_�[�n
		*/
		namespace Shader
		{
		}

		/**
			@brief �`��I�u�W�F�N�g�n
		*/
		namespace Object
		{
		}
	}

	/**
		@brief �t�@�C���n
	*/
	namespace File
	{
	}

	namespace Scene
	{
	}

	/**
		@brief ���̓f�o�C�X�n
	*/
	namespace Peripheral
	{
	}

	/**
		@brief �T�E���h�n
	*/
	namespace Sound
	{
	}

	/**
		@brief �V�X�e���n
	*/
	namespace System
	{
	}

	/**
		@brief �Z�p���Z�n
	*/
	namespace Math
	{
	}

	/**
		@brief ���l��Ԍn
	*/
	namespace Interpolation
	{
	}

	/**
		@brief �R���W�����n
	*/
	namespace Collision
	{
	}

	/**
		@brief �����V�~�����[�V�����n
	*/
	namespace Dynamics
	{
		class IRigidModel;
		class IRigidBody;
		class IContactPoint;
		class ISimulationWorld;
	}

	/**
		@brief �X���b�h�n
	*/
	namespace Thread
	{
	}

	/**
		@brief �V�[���n
	*/
	namespace Scene
	{
	}

	/**
		@brief �t�@�C���n
	*/
	namespace File
	{
	}

	/**
		@brief �t�@�C�o�[�n
	*/
	namespace Fiber
	{
	}

	/**
		@brief �l�b�g���[�N�n
	*/
	namespace Network
	{
		class INetworkManager;
		class ISocketTCP;
		class IServerTCP;
		class IServerClientTCP;
	}
}


//-----------------------------------------------------------------------------------
// INTERFACE
//-----------------------------------------------------------------------------------
namespace Selene
{
	class ICore;
	class IGraphicCard;

	namespace Renderer
	{
		class IRender;
		class ITexture;
		class ITexture;

		namespace Shader
		{
			class IShader;
		}

		namespace Object
		{
			class IPoint2D;
			class ILine2D;
			class IPrimitive2D;
			class ISprite2D;
			class IFontSprite2D;
			class IPoint3D;
			class ILine3D;
			class IPrimitive3D;
			class ISprite3D;
			class IFontSprite3D;
			class IParticle;
			class IModel;
			class IMapModel;
		}
	}

	namespace Fiber
	{
		class IFiber;
		class IFiberController;
	};

	namespace Peripheral
	{
		class IMouse;
		class IKeyboard;
		class IJoystick;
		class IInputController;
	}

	namespace File
	{
		class IFileManager;
		class IResourceFile;
	}

	namespace Sound
	{
		class ISound;
		class IStreamSound;
	}

	namespace Scene
	{
		class IPrimitiveActor;
		class ISpriteActor;
		class IParticleActor;
		class IModelActor;
		class IMapActor;
		class IInstanceModelActor;
		class IInstanceModelController;
		class ICamera;
		class ISceneManager;
		class ICustomizedSceneManager;
		class ICustomizedSceneRenderMaterial;
		class ICustomizedSceneRenderObject;
	}

	namespace Dynamics
	{
		class ISimulationWorld;
		class IRigidBody;
		class IRigidModel;
		class IContactPoint;
	}

	namespace Math
	{
		class Vector2D;
		class Vector3D;
		class Vector4D;
		class Quaternion;
		class Matrix;
		class Style;
	}
}


//-----------------------------------------------------------------------------------
// INLINE
//-----------------------------------------------------------------------------------
namespace Selene
{
	inline void Float2Int( Sint32 &iVal, Float fVal )
	{
		*((Uint32*)&iVal) = *((Uint32*)&fVal);
	}

	inline void Int2Float( Float &fVal, Sint32 iVal )
	{
		*((Uint32*)&fVal) = *((Uint32*)&iVal);
	}

	inline Float FastSqrt( Float fVal )
	{
		Float fRetVal;
		Sint32 iVal;

		Float2Int( iVal, fVal );

		iVal &= 0x7FFFFFFF;
		iVal -= 0x3F800000;
		iVal >>= 1;
		iVal += 0x3F800000;

		Int2Float( fRetVal, iVal );

		return fRetVal;
	}

	inline float InvSqrt( float fVal )
	{
		Sint32 iVal;
		Float fValHalf = fVal * 0.5f;

		Float2Int( iVal, fVal );

		iVal = 0x5F375A86 - (iVal >> 1);

		Int2Float( fVal, iVal );

		return fVal * (1.5f - fValHalf * fVal * fVal);
	}

	inline Float Abs( Float fVal )
	{
		Sint32 iVal;

		Float2Int( iVal, fVal );

		iVal &= 0x7FFFFFFF;

		Int2Float( fVal, iVal );

		return fVal;
	}

	inline Sint32 Abs( Sint32 iVal )
	{
		return iVal & 0x7FFFFFFF;
	}

	inline Bool Is2ByteChara( char Src )
	{
		unsigned char Code = *((unsigned char*)&Src);

		if ( Code <= 0x80 ) return false;	// ����R�[�h������
		if ( Code <= 0x9F ) return true;
		if ( Code <= 0xDF ) return false;	// ���p�J�i
		if ( Code <= 0xFE ) return true;

		return false;
	}

}

#pragma once


/**
	@file
	@brief �F�\���p�N���X
	@author �t���`
*/

//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
	/**
		@brief �F���Ǘ��N���X
		@author �t���`

		@note
			�e��f�[�^�̐F���`���邽�߂̃N���X�ł��B<BR>
			���C�u�������ŐF���w�肷��ꍇ�͂��ׂĂ��̃N���X���g���܂��B
	*/
	class CColor
	{
	public:
		union {
			struct {
				Uint8 b;		///< �F�̐���
				Uint8 g;		///< �F�̗ΐ���
				Uint8 r;		///< �F�̐Ԑ���
				Uint8 a;		///< �F�̓����x����
			};
			Sint32 Color;		///< �F��32Bit�����\�L
		};

	public:
/**
@brief �R���X�g���N�^
@author �t���`
*/
		CColor()
		{
		}

/**
@brief �R���X�g���N�^
@author �t���`
@param r		[in] �Ԑ����i�O�`�Q�T�T�j
@param g		[in] �ΐ����i�O�`�Q�T�T�j
@param b		[in] �����i�O�`�Q�T�T�j
@param a		[in] �A���t�@�����i�O�`�Q�T�T�j
*/
		CColor( Sint32 r, Sint32 g, Sint32 b, Sint32 a = 255 )
		{
			this->a = (Uint8)a;
			this->r = (Uint8)r;
			this->g = (Uint8)g;
			this->b = (Uint8)b;
		}

/**
@brief �R���X�g���N�^
@author �t���`
@param Color	[in] �F����
*/
		CColor( Sint32 Color )
		{
			this->Color = Color;
		}

/**
@brief �F�u�����h
@author �t���`
@param SrcA		[in] �F����
@param SrcB		[in] �F����
@param fRate	[in] �u�����h��

@note
2�̐F���u�����h���܂��B

@code

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  Selene::CColor ColorA( 255, 255, 255, 255 );
  Selene::CColor ColorB( 128, 128, 128, 128 );

  // ColorA��ColorB��50%�Ńu�����h
  Selene::CColor Ret;
  Ret.Blend( ColorA, ColorB, 0.5f );

  return 0;
}
@endcode
*/
		CColor &Blend( const CColor &SrcA, const CColor &SrcB, Float fRate )
		{
			if ( fRate < 0.0f ) fRate = 0.0f;
			if ( fRate > 1.0f ) fRate = 1.0f;
			r = (Uint8)(toF(SrcA.r) + (toF(SrcB.r - SrcA.r) * fRate));
			g = (Uint8)(toF(SrcA.g) + (toF(SrcB.g - SrcA.g) * fRate));
			b = (Uint8)(toF(SrcA.b) + (toF(SrcB.b - SrcA.b) * fRate));
			a = (Uint8)(toF(SrcA.a) + (toF(SrcB.a - SrcA.a) * fRate));

			return *this;
		}

/**
@brief �I�y���[�^�[=���Z�q
@author �t���`
*/
		CColor operator = ( const CColor &Color )
		{
			this->a = Color.a;
			this->r = Color.r;
			this->g = Color.g;
			this->b = Color.b;

			return *this;
		}

/**
@brief �I�y���[�^�[=���Z�q
@author �t���`
*/
		CColor operator = ( Sint32 Color )
		{
			this->Color = Color;

			return *this;
		}

/**
@brief �^�ϊ�
@author �t���`
*/
		operator Sint32 () const
		{
			return Color;
		}

	public:
/**
@brief �F�擾
@author �t���`

@note
RGBA�J���[�擾

@code

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  Selene::CColor Color = Selene::CColor::RGBA( 255, 255, 255, 255 );

  return 0;
}
@endcode
*/
		static CColor RGBA( Sint32 r, Sint32 g, Sint32 b, Sint32 a )
		{
			return CColor( r, g, b, a );
		}

/**
@brief �F�擾
@author �t���`

@note
BGRA�J���[�擾

@code

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  Selene::CColor Color = Selene::CColor::BGRA( 255, 255, 255, 255 );

  return 0;
}
@endcode
*/
		static CColor BGRA( Sint32 b, Sint32 g, Sint32 r, Sint32 a )
		{
			return CColor( r, g, b, a );
		}

/**
@brief �F�擾
@author �t���`

@note
ARGB�J���[�擾

@code

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  Selene::CColor Color = Selene::CColor::ARGB( 255, 255, 255, 255 );

  return 0;
}
@endcode
*/
		static CColor ARGB( Sint32 a, Sint32 r, Sint32 g, Sint32 b )
		{
			return CColor( r, g, b, a );
		}

/**
@brief �F�擾
@author �t���`

@note
XRGB�J���[�擾

@code

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  Selene::CColor Color = Selene::CColor::XRGB( 255, 255, 255 );

  return 0;
}
@endcode
*/
		static CColor XRGB( Sint32 r, Sint32 g, Sint32 b )
		{
			return CColor( r, g, b, 255 );
		}
	};
}
#pragma once


/**
	@file
	@brief �V�X�e���n�֐��Q
	@author �t���`
*/


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace System
{
/**
@brief �V�X�e��������
@author �t���`
@param IsSetExePath		[in] �J�����g�f�B���N�g�������s�t�@�C���̏ꏊ�ɋ����I�ɕύX���邩�̗L��
@param IsCreateLogFile	[in] ���O�t�@�C���𐶐����邩�ǂ���
@param IsSSE			[in] SSE�̎g�p�L��
@retval true	����
@retval false	���s

@note
Selene�V�X�e���̏��������s���܂��B

@code

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  // �V�X�e���̋N��
  if ( System::Initialize() )
  {  
  }

  System::Finalize();            // �V�X�e���̏I���������s��

  return 0;
}
@endcode
*/
SELENE_DLL_API Bool Initialize( Bool IsSetExePath = true, Bool IsCreateLogFile = true, Bool IsSSE = true );

/**
@brief �V�X�e���I��
@author �t���`

@note
Selene�V�X�e���̏I�������܂��B

@code

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  // �V�X�e���̋N��
  if ( System::Initialize() )
  {  
  }

  System::Finalize();            // �V�X�e���̏I���������s��

  return 0;
}
@endcode
*/
SELENE_DLL_API void Finalize( void );

/**
@brief ���d�N���u���b�N
@author �t���`
@param pApplicationName	[in] �A�v���P�[�V������
@retval false	���ɓ����̃A�v���P�[�V�������N�����Ă���
@retval true	�����̃A�v���P�[�V�����͑��݂��Ȃ�

@note
�Ԃ�lfalse���ɃA�v���P�[�V�������I�������邱�Ƃ�<BR>
���d�N����h�~���邱�Ƃ��ł��܂��B

@code

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  // �V�X�e���̋N��
  if ( System::Initialize() )
  {  
    // ���d�N���`�F�b�N
    if ( System::BlockDualBoot( "Application Name" ) )
    {
    }
  }

  System::Finalize();            // �V�X�e���̏I���������s��

  return 0;
}
@endcode
*/
SELENE_DLL_API Bool BlockDualBoot( const char *pApplicationName );

/**
@brief �J�����g�f�B���N�g�����Z�b�g
@author �t���`

@note
�J�����g�f�B���N�g�����A�v���P�[�V�����̎��s�t�H���_�ɐݒ肵�܂��B

@code

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  // �V�X�e���̋N��
  if ( System::Initialize() )
  {  
    // �J�����g�f�B���N�g�������s�t�@�C���̃t�H���_�ɂ���
    System::ResetCurrentDirectory();
  }

  System::Finalize();            // �V�X�e���̏I���������s��

  return 0;
}
@endcode
*/
SELENE_DLL_API void ResetCurrentDirectory( void );

/**
@brief �f�B���N�g������
@author �t���`
@param pPath	[in] �t�H���_�p�X

@note
�w��p�X�փf�B���N�g���𐶐����܂��B<BR>
�r���̃t�H���_�����݂��Ȃ��ꍇ�A�S�Ă̊K�w�ɑ΂��ăt�H���_���쐬���Ă����܂��B

@code

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  // �V�X�e���̋N��
  if ( System::Initialize() )
  {  
    // �J�����g�f�B���N�g�������s�t�@�C���̃t�H���_�ɂ���
    System::ResetCurrentDirectory();

    // �J�����g�f�B���N�g���̏ꏊ�ȉ��Ƀt�H���_����
    // �����s�t�@�C���̏ꏊ�Ƀt�H���_���@��
    System::DirectoryCreate( "Save\\Config" );
  }

  System::Finalize();            // �V�X�e���̏I���������s��

  return 0;
}
@endcode
*/
SELENE_DLL_API void DirectoryCreate( const char *pPath );

/**
@brief Core�̎擾
@author �t���`
@return ICore�C���^�[�t�F�C�X

@note
�E�B���h�E���Ǘ�����ICore�N���X�𐶐�/�擾���܂��B<BR>
���݁A�P��ICore���������ł��܂���B

@code

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  ICore      *pCore      = NULL;

  // �V�X�e���̋N��
  if ( System::Initialize() )
  {
    // ICore�̐���
    ICore *pCore = System::CreateCore();
    if ( pCore == NULL ) goto EXIT;      // ICore�ɂ�NullDevice���Ȃ��̂Ŏ��s�����NULL���Ԃ�  
  }

EXIT:
  SAFE_RELEASE( pCore );            // �R�A�̉��

  System::Finalize();              // �V�X�e���̏I���������s��

  return 0;
}
@endcode
*/
SELENE_DLL_API ICore *CreateCore( void );

/**
@brief SSE�̃T�|�[�g�̗L��
@author �t���`
@return	SSE�̃T�|�[�g�̗L��

@note
�g�p���Ă���CPU��SSE���T�|�[�g���Ă��邩�𒲂ׂ܂��B<BR>
���̊֐���Initialize()��IsSSE��false���w�肷��Ƃ��Ȃ炸false��Ԃ��܂��B

@code

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  // �V�X�e���̋N��
  if ( System::Initialize() )
  {  
    // SSE�T�|�[�g���Ă�H
    if ( System::IsSupportSSE() )
    {
      // SSE��SIMD���Z
    }
    else
    {
      // FPU�ŕ��ʂɉ��Z
    }
  }

  System::Finalize();        // �V�X�e���̏I���������s��

  return 0;
}
@endcode
*/
SELENE_DLL_API Bool IsSupportSSE( void );

/**
@brief �g�p����CPU�ԍ���ݒ�
@author �t���`
@param No	[in] CPU�ԍ�

@note
���݂̃X���b�h�Ŏg�p����CPU�̔ԍ���ݒ肵�܂��B

@code

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  // �V�X�e���̋N��
  if ( System::Initialize() )
  {  
    // ���݂̃X���b�h��CPU1�œ�����
    System::SetThreadCPUNo( 1 );
  }

  System::Finalize();        // �V�X�e���̏I���������s��

  return 0;
}
@endcode
*/
SELENE_DLL_API void SetThreadCPUNo( Sint32 No );
}
}
#pragma once


/**
	@file
	@brief �V�X�e���n�֐��Q
	@author �t���`
*/

//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Dynamics
{
/**
@brief �_�C�i�~�N�X�p���[���h����
@author �t���`
@return ���[���h�̃C���^�[�t�F�C�X

@note
Dynamics(ODE)�̃��[���h�̐������s���܂��B

@code
int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
	// ���[���h�̐���
	ISimulationWorld *pWorld = CreateWorld();

	// ��
	�c

	// ���[���h�̉��
	SAFE_RELEASE( pWorld );

	return 0;
}
@endcode
*/
SELENE_DLL_API ISimulationWorld *CreateWorld( Scene::ISceneManager *pScene = NULL );
}
}

#pragma once


/**
	@file
	@brief �V�X�e���n�֐��Q
	@author �t���`
*/

//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Network
{
/**
@brief �l�b�g���[�N�}�l�[�W���[�C���^�[�t�F�C�X����
@author �t���`
@return �l�b�g���[�N�}�l�[�W���[�C���^�[�t�F�C�X

@note
�V�K�̃l�b�g���[�N�}�l�[�W���[�C���^�[�t�F�C�X�𐶐����܂��B<BR>
�l�b�g���[�N�̃p�X�Ȃǂ̐ݒ�͑S��INetworkManager���o�R���čs���܂��B
�擾�����l�b�g���[�N�}�l�[�W���[�C���^�[�t�F�C�X�͎g�p�I����ɂ͕K��Release()���ĉ������B�B

@code
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
  ICore *pCore = NULL;
  Network::INetworkManager *pNetworkMgr = NULL;

  // �V�X�e���̏�����
  System::Initialize();

  // �l�b�g���[�N�}�l�[�W���[�̐���
  pNetworkMgr = Network::CreateManager();

  // �l�b�g���[�N�}�l�[�W���[�̉��
  SAFE_RELEASE( pNetworkMgr );

  // �R�A�̉��
  SAFE_RELEASE( pCore );

  // �V�X�e���̉��
  System::Finalize();

  return 0;
}
@endcode
*/
SELENE_DLL_API INetworkManager *CreateManager( void );
}
}

#pragma once


/**
	@file
	@brief �N���e�B�J���Z�N�V��������
	@author �t���`
*/


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Thread
{
	/**
		@brief �N���e�B�J���Z�N�V�����Ǘ��N���X
		@author �t���`
	*/
	class SELENE_DLL_API CCriticalSection
	{
	private:
		CRITICAL_SECTION m_CriticalSection;		///< �N���e�B�J���Z�N�V����

	public:
/**
@brief �R���X�g���N�^
@author �t���`
*/
		CCriticalSection();

/**
@brief �f�X�g���N�^
@author �t���`
*/
		virtual ~CCriticalSection();

/**
@brief �N���e�B�J���Z�N�V�����ɓ���
@author �t���`

@note
�N���e�B�J���Z�N�V�����ɓ���܂��B

@code

using namespace Selene;

CriticalSection cs;
Sint32 g_Result = 0;

void CThreadProc( void *pData )
{
  // �ϐ��ɃA�N�Z�X�O�Ƀ��b�N
  cs.Enter();

  // �K��
  for ( Sint32 i = 0; i < 100000; )
  {
    g_Result += i * i;
  }

  // �ϐ��g���I������̂ŃA�N�Z�X���b�N����
  cs.Leave();
}

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  CThread CThread;

  // �X���b�h����
  CThread.Create( CThreadProc, NULL );

  // �K���ɑ҂��Ă�
  Sleep( 1000 );

  // �ϐ��ɃA�N�Z�X�O�Ƀ��b�N
  cs.Enter();

  // ���ʂ��Q�b�g
  Sint32 ret = g_Result;

  // �ϐ��g���I������̂ŃA�N�Z�X���b�N����
  cs.Leave();

  // �X���b�h�I����Ă�H
  while ( !CThread.WaitForExit() )
  {
    Sleep( 1000 );
  }
  return 0;
}
@endcode
*/
		void Enter( void ) const;

/**
@brief �N���e�B�J���Z�N�V�������甲����
@author �t���`

@note
�N���e�B�J���Z�N�V�������甲���܂��B

@code

using namespace Selene;

CriticalSection cs;
Sint32 g_Result = 0;

void CThreadProc( void *pData )
{
  // �ϐ��ɃA�N�Z�X�O�Ƀ��b�N
  cs.Enter();

  // �K��
  for ( Sint32 i = 0; i < 100000; )
  {
    g_Result += i * i;
  }

  // �ϐ��g���I������̂ŃA�N�Z�X���b�N����
  cs.Leave();
}

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  CThread CThread;

  // �X���b�h����
  CThread.Create( CThreadProc, NULL );

  // �K���ɑ҂��Ă�
  Sleep( 1000 );

  // �ϐ��ɃA�N�Z�X�O�Ƀ��b�N
  cs.Enter();

  // ���ʂ��Q�b�g
  Sint32 ret = g_Result;

  // �ϐ��g���I������̂ŃA�N�Z�X���b�N����
  cs.Leave();

  // �X���b�h�I����Ă�H
  while ( !CThread.WaitForExit() )
  {
    Sleep( 1000 );
  }
  return 0;
}
@endcode
*/
		void Leave( void ) const;
	};

	/**
		@brief �����N���e�B�J���Z�N�V�����Ǘ��N���X
		@author �t���`
	*/
	class CAutoLock
	{
	private:
		const CCriticalSection	&m_cs;			///< �g�p����N���e�B�J���Z�N�V����

	private:
/**
@brief = �I�y���[�^�[
@author �t���`
@param	Lock [in] ����
@return	���͂Ɠ�������

�R���p�C����ʂ����߂̃_�~�[�p�B
*/
		CAutoLock & operator = ( CAutoLock &Lock ) {
			return Lock;
		}

	public:
/**
@brief �R���X�g���N�^
@author �t���`
@param cs	[in] �N���e�B�J���Z�N�V����

@note
�R���X�g���N�^���Ŏ����I�ɃN���e�B�J���Z�N�V�����ɓ���܂��B

@code

using namespace Selene;

CriticalSection cs;
Sint32 g_Result = 0;

void CThreadProc( void *pData )
{
  // Lock�̃R���X�g���N�^����
  // cs���N���e�B�J���Z�N�V�����ɓ���
  CAutoLock Lock( cs );

  // �K��
  for ( Sint32 i = 0; i < 100000; )
  {
    g_Result += i * i;
  }

  // �X�R�[�v���甲����Ƃ���Lock�̃f�X�g���N�^���R�[������
  // cs���N���e�B�J���Z�N�V�������甲����
}

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  CThread CThread;

  // �X���b�h����
  CThread.Create( CThreadProc, NULL );

  // �K���ɑ҂��Ă�
  Sleep( 1000 );

  // �ϐ��ɃA�N�Z�X�O�Ƀ��b�N
  cs.Enter();

  // ���ʂ��Q�b�g
  Sint32 ret = g_Result;

  // �ϐ��g���I������̂ŃA�N�Z�X���b�N����
  cs.Leave();

  // �X���b�h�I����Ă�H
  while ( !CThread.WaitForExit() )
  {
    Sleep( 1000 );
  }
  return 0;
}
@endcode
*/
		CAutoLock( const CCriticalSection &cs )
			: m_cs	( cs )
		{
			m_cs.Enter();
		}

/**
@brief �R���X�g���N�^
@author �t���`
@param cs	[in] �N���e�B�J���Z�N�V����

@note
�R���X�g���N�^���Ŏ����I�ɃN���e�B�J���Z�N�V�����ɓ���܂��B

@code

using namespace Selene;

CriticalSection cs;
Sint32 g_Result = 0;

void CThreadProc( void *pData )
{
  // Lock�̃R���X�g���N�^����
  // cs���N���e�B�J���Z�N�V�����ɓ���
  CAutoLock Lock( &cs );

  // �K��
  for ( Sint32 i = 0; i < 100000; )
  {
    g_Result += i * i;
  }

  // �X�R�[�v���甲����Ƃ���Lock�̃f�X�g���N�^���R�[������
  // cs���N���e�B�J���Z�N�V�������甲����
}

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  CThread CThread;

  // �X���b�h����
  CThread.Create( CThreadProc, NULL );

  // �K���ɑ҂��Ă�
  Sleep( 1000 );

  // �ϐ��ɃA�N�Z�X�O�Ƀ��b�N
  cs.Enter();

  // ���ʂ��Q�b�g
  Sint32 ret = g_Result;

  // �ϐ��g���I������̂ŃA�N�Z�X���b�N����
  cs.Leave();

  // �X���b�h�I����Ă�H
  while ( !CThread.WaitForExit() )
  {
    Sleep( 1000 );
  }
  return 0;
}
@endcode
*/
		CAutoLock( const CCriticalSection *cs )
			: m_cs	( *cs )
		{
			m_cs.Enter();
		}

/**
@brief �f�X�g���N�^
@author �t���`

@note
�f�X�g���N�^���Ă΂�鎞�Ɏ����I�ɃN���e�B�J���Z�N�V��������o�܂��B

@code

using namespace Selene;

CriticalSection cs;
Sint32 g_Result = 0;

void CThreadProc( void *pData )
{
  // Lock�̃R���X�g���N�^����
  // cs���N���e�B�J���Z�N�V�����ɓ���
  CAutoLock Lock( &cs );

  // �K��
  for ( Sint32 i = 0; i < 100000; )
  {
    g_Result += i * i;
  }

  // �X�R�[�v���甲����Ƃ���Lock�̃f�X�g���N�^���R�[������
  // cs���N���e�B�J���Z�N�V�������甲����
}

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  CThread CThread;

  // �X���b�h����
  CThread.Create( CThreadProc, NULL );

  // �K���ɑ҂��Ă�
  Sleep( 1000 );

  // �ϐ��ɃA�N�Z�X�O�Ƀ��b�N
  cs.Enter();

  // ���ʂ��Q�b�g
  Sint32 ret = g_Result;

  // �ϐ��g���I������̂ŃA�N�Z�X���b�N����
  cs.Leave();

  // �X���b�h�I����Ă�H
  while ( !CThread.WaitForExit() )
  {
    Sleep( 1000 );
  }
  return 0;
}
@endcode
*/
		~CAutoLock()
		{
			m_cs.Leave();
		}
	};
}
}

#pragma once


/**
	@file
	@brief �C�x���g����
	@author �t���`
*/


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Thread
{
	/**
		@brief �X���b�h�p�C�x���g�I�u�W�F�N�g
		@author �t���`
	*/
	class SELENE_DLL_API CEvent
	{
	private:
		HANDLE m_EventHandle[MAXIMUM_WAIT_OBJECTS];		///< �C�x���g�n���h��
		Sint32 m_HandleCount;							///< �C�x���g��

	public:
/**
@brief �R���X�g���N�^
@author �t���`
@param IsSignal		[in] �V�O�i����Ԃŏ���������ꍇ��true
@param Count		[in] �C�x���g�̃J�E���g�iMAXIMUM_WAIT_OBJECTS�ȉ��j
*/
		CEvent( Bool IsSignal = false, Sint32 Count = 1 );

/**
@brief �f�X�g���N�^
@author �t���`
*/
		virtual ~CEvent();

/**
@brief �w�肳�ꂽ�C�x���g���V�O�i����Ԃɐݒ�
@author �t���`
@param No	[in] �V�O�i����Ԃ���C�x���g�̔ԍ�

@note
�w�肵���ԍ��̃C�x���g���V�O�i����Ԃɐݒ肵�܂��B

@code

using namespace Selene;

// 5�̃C�x���g����
Event Event( false, 5 );

void ThreadProc( void *pData )
{
  // No=3�̃C�x���g���V�O�i���H
  while ( !Event.IsSignal( 3 ) )
  {
    // ���΂��҂�
    Sleep( 1000 );
  }

  // No=3�̃C�x���g���V�O�i���ɂ���
  Event.Reset( 3 );
}

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  Thread Thread;

  // �X���b�h����
  Thread.Create( ThreadProc, NULL );

  // �K���ɑ҂��Ă�ӂ�
  Sleep( 1000 );

  // No=3�̃C�x���g���V�O�i���ɂ���
  Event.Set( 3 );

  // �X���b�h�I����Ă�H
  while ( !Thread.WaitForExit() )
  {
    Sleep( 1000 );
  }
  return 0;
}
@endcode
*/
		virtual void Set( Sint32 No = 0 );

/**
@brief �w�肳�ꂽ�C�x���g���V�O�i����Ԃɐݒ�
@author �t���`
@param No	[in] ��V�O�i����Ԃ���C�x���g�̔ԍ�

@note
�w�肵���ԍ��̃C�x���Ƃ���V�O�i����Ԃɐݒ肵�܂��B

@code

using namespace Selene;

// 5�̃C�x���g����
Event Event( false, 5 );

void ThreadProc( void *pData )
{
  // No=3�̃C�x���g���V�O�i���H
  while ( !Event.IsSignal( 3 ) )
  {
    // ���΂��҂�
    Sleep( 1000 );
  }

  // No=3�̃C�x���g���V�O�i���ɂ���
  Event.Reset( 3 );
}

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  Thread Thread;

  // �X���b�h����
  Thread.Create( ThreadProc, NULL );

  // �K���ɑ҂��Ă�ӂ�
  Sleep( 1000 );

  // No=3�̃C�x���g���V�O�i���ɂ���
  Event.Set( 3 );

  // �X���b�h�I����Ă�H
  while ( !Thread.WaitForExit() )
  {
    Sleep( 1000 );
  }
  return 0;
}
@endcode
*/
		virtual void Reset( Sint32 No = 0 );

/**
@brief �w�肵���C�x���g���V�O�i����Ԃ��`�F�b�N
@author �t���`
@param No	[in] �`�F�b�N����C�x���g�̔ԍ�
@retval false	��V�O�i�����
@retval true	�V�O�i�����

@note
�w�肵���C�x���g���V�O�i����ԂɂȂ��Ă��邩���`�F�b�N���܂��B

@code

using namespace Selene;

// 5�̃C�x���g����
Event Event( false, 5 );

void ThreadProc( void *pData )
{
  // No=3�̃C�x���g���V�O�i���H
  while ( !Event.IsSignal( 3 ) )
  {
    // ���΂��҂�
    Sleep( 1000 );
  }

  // No=3�̃C�x���g���V�O�i���ɂ���
  Event.Reset( 3 );
}

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  Thread Thread;

  // �X���b�h����
  Thread.Create( ThreadProc, NULL );

  // �K���ɑ҂��Ă�ӂ�
  Sleep( 1000 );

  // No=3�̃C�x���g���V�O�i���ɂ���
  Event.Set( 3 );

  // �X���b�h�I����Ă�H
  while ( !Thread.WaitForExit() )
  {
    Sleep( 1000 );
  }
  return 0;
}
@endcode
*/
		virtual Bool IsSignal( Sint32 No = 0 );

/**
@brief �S�ẴC�x���g���V�O�i����Ԃ��`�F�b�N
@author �t���`
@retval false	��V�O�i�����
@retval true	�V�O�i�����

@note
�S�ẴC�x���g���V�O�i����ԂɂȂ��Ă��邩���`�F�b�N���܂��B

@code

using namespace Selene;

// 3�̃C�x���g����
Event Event( false, 3 );

void ThreadProc( void *pData )
{
  // �S���V�O�i���ɂȂ�܂ő҂�
  while ( !Event.IsSignalAll() )
  {
    // �܂��Ȃ̂ł��΂��҂�
    Sleep( 1000 );
  }
}

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  Thread Thread;

  // �X���b�h����
  Thread.Create( ThreadProc, NULL );

  // �K���ɑ҂��Ă�ӂ�
  Sleep( 1000 );

  // �C�x���g���V�O�i���ɂ���
  Event.Set( 0 );
  Event.Set( 1 );
  Event.Set( 2 );

  // �X���b�h�I����Ă�H
  while ( !Thread.WaitForExit() )
  {
    Sleep( 1000 );
  }
  return 0;
}
@endcode
*/
		virtual Bool IsSignalAll( void );

/**
@brief �V�O�i����ԂɂȂ����C�x���g���擾
@author �t���`
@param TimeOut		[in] �^�C���A�E�gms���ԁi-1�Ŗ����j
@retval -1		�^�C���A�E�g
@retval 0�ȏ�	�V�O�i����ԂɂȂ����C�x���g�ԍ�

@note
�w�莞�ԑҋ@���P�ł��V�O�i����ԂɂȂ����炻�̏u�Ԃɂ��̃C�x���g�̔ԍ���Ԃ��܂��B<BR>
�w�莞�Ԍo�߂��Ă��V�O�i����ԂɂȂ����C�x���g���Ȃ����-1��Ԃ��܂��B

@code

using namespace Selene;

// 3�̃C�x���g����
Event Event( false, 3 );

void ThreadProc( void *pData )
{
  // �������V�O�i���ɂȂ�܂�1�b�قǑ҂�
  Sint32 No = Event.Wait( 1000 );
  switch ( No )
  {
  case 0:
  case 1:
  case 2:
    break;
  default:
    break;
  }
}

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  Thread Thread;

  // �X���b�h����
  Thread.Create( ThreadProc, NULL );

  // �K���ɑ҂��Ă�ӂ�
  Sleep( 1000 );

  // �C�x���g���V�O�i���ɂ���
  Event.Set( 1 );

  // �X���b�h�I����Ă�H
  while ( !Thread.WaitForExit() )
  {
    Sleep( 1000 );
  }
  return 0;
}
@endcode
*/
		virtual Sint32 Wait( Sint32 TimeOut = -1 );

/**
@brief �V�O�i����ԂɂȂ����C�x���g���擾
@author �t���`
@param No		[in] �n���h���ԍ�
@return		�n���h��

@note
�w��ԍ��̃n���h�����擾���܂��B
*/
		virtual HANDLE GetHandle( Sint32 No );
	};
}
}

#pragma once


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Thread
{
	/**
		@brief �X���b�h���s�D��x
		@author �t���`
	*/
	enum eCThreadPriority
	{
		THREAD_PRIORITY_LOW		= -2,		/// �Ⴂ
		THREAD_PRIORITY_MIDDLE	= -1,		/// ���Ⴂ
		THREAD_PRIORITY_DEFAULT	=  0,		/// �ʏ�
		THREAD_PRIORITY_HIGH	= +1,		/// ����
	};

	/**
		@brief �X���b�h�Ǘ�����N���X
		@author �t���`
	*/
	class SELENE_DLL_API CThread
	{
	private:
/**
@brief �X���b�h�p�֐�
@author �t���`
@param pArguments	[in] CThread�̃|�C���^

@note
�N���X�̊֐��𒼐ڂ͎w��ł��Ȃ��̂�<BR>
static�Ȋ֐����o�R���ČĂяo���B
*/
		static Uint32 __stdcall CThreadFunc( void* pArguments );

	private:
		HANDLE m_hThread;					///< �X���b�h�n���h��
		Uint32 m_ThreadId;					///< �X���b�hID
		void *m_pData;						///< �X���b�h�f�[�^�`�B�p�|�C���^
		void (*m_pMainProc)( void* );		///< �X���b�h�֐�
		CCriticalSection m_cs;				///< �N���e�B�J���Z�N�V����

	public:
/**
@brief �R���X�g���N�^
@author �t���`
*/
		CThread();

/**
@brief �f�X�g���N�^
@author �t���`
*/
		virtual ~CThread();

	public:
/**
@brief �X���b�h����
@author �t���`
@param pCThreadFunc	[in] �X���b�h�֐�
@param pData		[in] �X���b�h�Ɉ����n���f�[�^�|�C���^
@retval false	�������sor���ɃX���b�h����������Ă���
@retval true	��������

@note
�X���b�h�̐������s���܂��B

@code

using namespace Selene;

void CThreadProc( void *pData )
{
  // 10�b�ҋ@
  Sleep( 10 * 1000 );
}

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  CThread CThread;

  // �X���b�h����
  CThread.Create( CThreadProc, NULL );

  // �X���b�h�I���܂ő҂�
  while ( !CThread.WaitForExit() )
  {
    // �K��
    Sleep( 100 );
  }
  return 0;
}
@endcode
*/
		virtual Bool Create( void (*pCThreadFunc)( void* ), void *pData );

/**
@brief �X���b�h�I���҂�
@author �t���`
@retval false	�X���b�h�͏I�����Ă��Ȃ�
@retval true	�X���b�h�͏I������

@note
�X���b�h���I������̂�҂��܂�

@code
void CThreadProc( void *pData )
{
  // 10�b�ҋ@
  Sleep( 10 * 1000 );
}

void hogehoge( void )
{
	CThread CThread;

	// �X���b�h����
	CThread.Create( CThreadProc, NULL );

	// �X���b�h�I���܂ő҂�
	while ( !CThread.WaitForExit() )
	{
		// �K��
		Sleep( 100 );
	}
}
@endcode
*/
		virtual Bool WaitForExit( void );

/**
@brief �X���b�h�̗D��x�ύX
@author �t���`
@param Priority		[in] �X���b�h�����̗D��x

@note
�X���b�h�̗D��x��ύX���܂��B<BR>
�f�t�H���g�̗D��x��THREAD_PRIORITY_DEFAULT�ł��B

@code

using namespace Selene;

void CThreadProc( void *pData )
{
  // 10�b�ҋ@
  Sleep( 10 * 1000 );
}

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  CThread CThread;

  // �X���b�h����
  CThread.Create( CThreadProc, NULL );

  // �X���b�h�̗D��x��1�����N������
  CThread.SetPriority( THREAD_PRIORITY_MIDDLE );

  // �X���b�h�I���܂ő҂�
  while ( !CThread.WaitForExit() )
  {
    // �K��
    Sleep( 100 );
  }
  return 0;
}
@endcode
*/
		virtual Bool SetPriority( Sint32 Priority );

/**
@brief �X���b�h�̒��f������
@author �t���`

@note
�X���b�h�̃T�X�y���h�J�E���g�� 1 ����܂��B<BR>
�J�E���g�� 0 �ɂȂ������_�ŃX���b�h�̒��f����������܂��B

@code

using namespace Selene;

void CThreadProc( void *pData )
{
  // 10�b�ҋ@
  Sleep( 10 * 1000 );
}

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  CThread CThread;

  // �X���b�h����
  CThread.Create( CThreadProc, NULL );

  // �X���b�h�ꎞ��~
  CThread.Suspend();

  // �K���ɑ҂��Ă�ӂ�
  Sleep( 1000 );

  // �X���b�h�ĊJ
  CThread.Resume();

  // �X���b�h�I���܂ő҂�
  while ( !CThread.WaitForExit() )
  {
    // �K��
    Sleep( 100 );
  }
  return 0;
}
@endcode
*/
		virtual void Resume( void );

/**
@brief �X���b�h�̎��s�𒆒f
@author �t���`

@note
�w�肳�ꂽ�X���b�h�̎��s�����f����A<BR>
���̃X���b�h�̃T�X�y���h�J�E���g�� 1 �����܂��B

@code
void CThreadProc( void *pData  )
{
}

void hogehoge( void )
{
	Selene::CThread CThread;

	// �X���b�h����
	CThread.Create( CThreadProc );

	// �X���b�h�ꎞ��~
	CThread.Suspend();

	// ��
	�c

	// �X���b�h�ĊJ
	CThread.Resume();

	// ��
	�c
}
@endcode
*/
		virtual void Suspend( void );

/**
@brief �X���b�h�̎��s���I��
@author �t���`

@note
�w�肳�ꂽ�X���b�h�̎��s�������I�����܂��B<BR>
���̊֐��ŏI��������ꍇ�̓X�^�b�N�̉���Ȃǂ��s���Ȃ��̂�<BR>
�ʏ�͎g�p���Ȃ��ł��������B<BR>
�����I�����s�킴��𓾂Ȃ��󋵂ł̂ݎg�p���ĉ������B

@code

using namespace Selene;

void CThreadProc( void *pData )
{
  // 10�b�ҋ@
  Sleep( 10 * 1000 );
}

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  CThread CThread;

  // �X���b�h����
  CThread.Create( CThreadProc, NULL );

  // �K���ɑ҂��Ă�ӂ�
  Sleep( 1000 );

  // �X���b�h�I����Ă�H
  if ( !CThread.WaitForExit() )
  {
    // �����I��
    CThread.Terminate();
  }
  return 0;
}
@endcode
*/
		virtual void Terminate( void );
	};
}
}

#pragma once


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
	/**
		@brief �t�@�C���I�[�v�����[�h
		@author �t���`
	*/
	enum eFileOpenType
	{
		FILE_OPEN_TYPE_WRITE,			///< �������ݐ�p
		FILE_OPEN_TYPE_READ,			///< �ǂݍ��ݐ�p
		FILE_OPEN_TYPE_READ_WRITE,		///< �ǂݏ����p

		FILE_OPEN_TYPE_INVALID,			///< ����
	};

namespace File
{
	/**
		@brief �t�@�C������
		@author �t���`
	*/
	class SELENE_DLL_API CFile
	{
	private:
		HANDLE m_hFile;				///< �t�@�C���n���h��
		eFileOpenType m_Type;		///< �t�@�C���I�[�v�����[�h
		FILETIME m_TimeCreate;		///< �t�@�C���쐬����
		FILETIME m_TimeAccess;		///< �t�@�C���A�N�Z�X����
		FILETIME m_TimeLastWrite;	///< �t�@�C���������ݎ���

	public:
		/**
			@brief �R���X�g���N�^
			@author �t���`
		*/
		CFile( const char *pFileName, eFileOpenType Type );

		/**
			@brief �f�X�g���N�^
			@author �t���`
		*/
		virtual ~CFile();

		/**
			@brief �t�@�C���I�[�v���`�F�b�N
			@author �t���`
			@retval false	�t�@�C���͊J����Ă��Ȃ�
			@retval true	�t�@�C���͊J����Ă���
		*/
		virtual Bool IsOpened( void );

		/**
			@brief �t�@�C����������
			@author �t���`
			@param pData	[in] �������݃f�[�^
			@param Size		[in] �f�[�^�T�C�Y
			@return ���ۂ̏������݃T�C�Y
		*/
		virtual Sint32 Write( const void *pData, Sint32 Size );

		/**
			@brief �t�@�C���ǂݍ���
			@author �t���`
			@param pData	[in] �ǂݍ��݃f�[�^
			@param Size		[in] �f�[�^�T�C�Y
			@return ���ۂ̓ǂݍ��݃T�C�Y
		*/
		virtual Sint32 Read( void *pData, Sint32 Size );

		/**
			@brief �t�@�C���T�C�Y�擾
			@author �t���`
		*/
		virtual Sint32 GetFileSize( void );

		/**
			@brief �t�@�C���ʒu�擾
			@author �t���`
			preturn �t�@�C���ʒu
		*/
		virtual Sint32 GetFilePosition( void );

		/**
			@brief �擪����V�[�N
			@author �t���`
			@param Offset	[in] �擪����̃I�t�Z�b�g
			@param �t�@�C���ʒu
		*/
		virtual Sint32 SeekStart( Sint32 Offset );

		/**
			@brief �I�[����V�[�N
			@author �t���`
			@param Offset	[in] �I�[����̃I�t�Z�b�g
			@param �t�@�C���ʒu
		*/
		virtual Sint32 SeekEnd( Sint32 Offset );

		/**
			@brief �V�[�N
			@author �t���`
			@param Offset	[in] ���݈ʒu����̃I�t�Z�b�g
			@param �t�@�C���ʒu
		*/
		virtual Sint32 Seek( Sint32 Offset );
	};
}
}

#pragma once


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace File
{
	/**
		@brief HTML���O�p�t�@�C������
		@author �t���`
	*/
	class SELENE_DLL_API CFileHtmlLog : public CFile
	{
	private:
		Thread::CCriticalSection m_CS;

	public:
		CFileHtmlLog( const char *pFileName, const char *pTitle );
		virtual ~CFileHtmlLog();

		virtual Sint32 Print( Sint32 Color, const char *pStr,... );
		virtual Sint32 PrintStrong( Sint32 Color, const char *pStr,... );
		virtual Sint32 PrintLine( Sint32 Color, const char *pStr,... );
		virtual Sint32 PrintStrongLine( Sint32 Color, const char *pStr,... );

		virtual Sint32 TableBegin( void );
		virtual Sint32 TableEnd( void );
		virtual Sint32 TableLine( Sint32 Bold );

		virtual Sint32 CellBegin( Sint32 Width );
		virtual Sint32 CellEnd( void );
	};
}
}


#pragma once


/**
	@file
	@brief 2�����x�N�g��
	@author �t���`
*/


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Math
{
	/**
		@brief 2�����x�N�g�����Z�N���X
	*/
	class SELENE_DLL_API Vector2D
	{
	public:
		Float x;
		Float y;

	public:
		/**
			@brief �R���X�g���N�^
			@author �t���`
		*/
		Vector2D();
		/**
			@brief �R���X�g���N�^
			@author �t���`
			@param v	[in] ����
		*/
		Vector2D( const Vector2D &v );
		/**
			@brief �R���X�g���N�^
			@author �t���`
			@param fPx	[in] x�����l
			@param fPy	[in] y�����l
		*/
		Vector2D( Float fPx, Float fPy );
		/**
			@brief ���Z
			@author �t���`
			@param In1	[in] ���Z�p���̓x�N�g��
			@param In2	[in] ���Z�p���̓x�N�g��
			@return �v�Z���ʌ��*this

			@note
			this = In + In2
		*/
		Vector2D& Add( const Vector2D &In1, const Vector2D &In2 );
		/**
			@brief ���Z
			@author �t���`
			@param In1	[in] ���Z�p���̓x�N�g��
			@param In2	[in] ���Z�p���̓x�N�g��
			@return �v�Z���ʌ��*this

			@note
			this = In - In2
		*/
		Vector2D& Sub( const Vector2D &In1, const Vector2D &In2 );
		/**
			@brief �l�ݒ�
			@author �t���`
			@param fPx	[in] x�ݒ�l
			@param fPy	[in] y�ݒ�l
			@return �v�Z���ʌ��*this
		*/
		Vector2D& Set( Float fPx, Float fPy );
		/**
			@brief �����̓��擾
			@author �t���`
			@return �����̓��
		*/
		Float LengthSq( void ) const;
		/**
			@brief �����擾
			@author �t���`
			@return ����
		*/
		Float Length( void ) const;
		/**
			@brief �����擾
			@author �t���`
			@return ����
		*/
		Float LengthFast( void ) const;
		/**
			@brief ����
			@author �t���`
			@param In	[in] ���ώZ�o�p���̓x�N�g��
			@return ����
		*/
		Float Dot( const Vector2D &In ) const;
		/**
			@brief ���K��
			@author �t���`
			@return �v�Z���ʌ��*this

			@note
			������1.0�ɐ��K�����܂��B
		*/
		Vector2D& Normalize( void );
		/**
			@brief ���K��
			@author �t���`
			@return �v�Z���ʌ��*this

			@note
			������1.0�ɐ��K�����܂��B
		*/
		Vector2D& NormalizeFast( void );
		/**
			@brief ���˃x�N�g���̎擾
			@author �t���`
			@param In1	[in] ���ˑΏۂ̖@��
			@param In2	[in] ���˃x�N�g��
			@return �v�Z���ʌ��*this
		*/
		Vector2D& Reflect( const Vector2D &In1, const Vector2D &In2 );
		/**
			@brief ���K��
			@author �t���`
			@param In	[in] ���K�����̃x�N�g��
			@return �v�Z���ʌ��*this
		*/
		Vector2D& Normalize( const Vector2D &In );
		/**
			@brief ���K��
			@author �t���`
			@param In	[in] ���K�����̃x�N�g��
			@return �v�Z���ʌ��*this
		*/
		Vector2D& NormalizeFast( const Vector2D &In );
		/**
			@brief �O��
			@author �t���`
			@param In	[in] �O�ϗp�̃x�N�g��
			@return z=0.0�Ƃ��Čv�Z�����x�N�g���̊O��
		*/
		Float Cross( const Vector2D &In ) const;
		/**
			@brief ����
			@author �t���`
			@param In	[in] ���˗p�@��
			@return �v�Z���ʌ��*this
		*/
		Vector2D& Reflect( const Vector2D &In );
		/**
			@brief Z����]
			@author �t���`
			@param Angle	[in] ��]�p�x
			@return �v�Z���ʌ��*this
		*/
		Vector2D& RotationZ( Sint32 Angle );
		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		Vector2D operator + () const
		{
			return *this;
		}
		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		Vector2D operator - () const
		{
			return Vector2D(-x, -y);
		}
		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		Bool operator == ( const Vector2D &v )
		{
			return (x == v.x) && (y == v.y);
		}
		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		Bool operator != ( const Vector2D &v )
		{
			return (x != v.x) || (y != v.y);
		}
		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		Vector2D& operator += ( Float f )
		{
			x += f;
			y += f;
			return *this;
		}
		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		Vector2D& operator -= ( Float f )
		{
			x -= f;
			y -= f;
			return *this;
		}
		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		Vector2D& operator *= ( Float f )
		{
			x *= f;
			y *= f;
			return *this;
		}
		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		Vector2D& operator /= ( Float f )
		{
			x /= f;
			y /= f;
			return *this;
		}
		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		Vector2D& operator += ( const Vector2D &v )
		{
			x += v.x;
			y += v.y;
			return *this;
		}
		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		Vector2D& operator -= ( const Vector2D &v )
		{
			x -= v.x;
			y -= v.y;
			return *this;
		}
		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		Vector2D& operator *= ( const Vector2D &v )
		{
			x *= v.x;
			y *= v.y;
			return *this;
		}
		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		Vector2D& operator /= ( const Vector2D &v )
		{
			x /= v.x;
			y /= v.y;
			return *this;
		}
		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		Vector2D operator + ( Float f ) const
		{
		    return Vector2D(x + f, y + f);
		}
		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		Vector2D operator - ( Float f ) const
		{
			f = 1.0f / f;
			return Vector2D(x - f, y - f);
		}
		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		Vector2D operator * ( Float f ) const
		{
		    return Vector2D(x * f, y * f);
		}
		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		Vector2D operator / ( Float f ) const
		{
			return Vector2D(x / f, y / f);
		}
		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		Vector2D operator + ( const Vector2D &v ) const
		{
			return Vector2D(x + v.x, y + v.y);
		}
		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		Vector2D operator - ( const Vector2D &v ) const
		{
			return Vector2D(x - v.x, y - v.y);
		}
		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		Vector2D operator * ( const Vector2D &v ) const
		{
			return Vector2D(x * v.x, y * v.y);
		}
		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		Vector2D operator / ( const Vector2D &v ) const
		{
			return Vector2D(x / v.x, y / v.y);
		}
	};
}
}

#pragma once


/**
	@file
	@brief 3�����x�N�g��
	@author �t���`
*/


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Math
{
	/**
		@brief 3�����x�N�g�����Z�N���X
	*/
	class SELENE_DLL_API Vector3D
	{
	public:
		Float x;
		Float y;
		Float z;

	public:
		/**
			@brief �R���X�g���N�^
			@author �t���`
		*/
		Vector3D();
		/**
			@brief �R���X�g���N�^
			@author �t���`
			@param v	[in] ����
		*/
		Vector3D( const Vector3D &v );
		/**
			@brief �R���X�g���N�^
			@author �t���`
			@param fPx	[in] x�����l
			@param fPy	[in] y�����l
			@param fPz	[in] z�����l
		*/
		Vector3D( Float fPx, Float fPy, Float fPz );
		/**
			@brief ���Z
			@author �t���`
			@param In1	[in] ���Z�p���̓x�N�g��
			@param In2	[in] ���Z�p���̓x�N�g��
			@return �v�Z���ʌ��*this

			@note
			this = In + In2
		*/
		Vector3D& Add( const Vector3D &In1, const Vector3D &In2 );
		/**
			@brief ���Z
			@author �t���`
			@param In1	[in] ���Z�p���̓x�N�g��
			@param In2	[in] ���Z�p���̓x�N�g��
			@return �v�Z���ʌ��*this

			@note
			this = In - In2
		*/
		Vector3D& Sub( const Vector3D &In1, const Vector3D &In2 );
		/**
			@brief �l�ݒ�
			@author �t���`
			@param fPx	[in] x�ݒ�l
			@param fPy	[in] y�ݒ�l
			@param fPz	[in] z�ݒ�l
			@return �v�Z���ʌ��*this
		*/
		Vector3D& Set( Float fPx, Float fPy, Float fPz );
		/**
			@brief �����̓��擾
			@author �t���`
			@return �����̓��
		*/
		Float LengthSq( void ) const;
		/**
			@brief �����擾
			@author �t���`
			@return ����
		*/
		Float Length( void ) const;
		/**
			@brief �����擾
			@author �t���`
			@return ����
		*/
		Float LengthFast( void ) const;
		/**
			@brief ����
			@author �t���`
			@param In	[in] ���ώZ�o�p���̓x�N�g��
			@return ����
		*/
		Float Dot( const Vector3D &In ) const;
		/**
			@brief ���K��
			@author �t���`
			@return �v�Z���ʌ��*this

			@note
			������1.0�ɐ��K�����܂��B
		*/
		Vector3D &Normalize( void );
		/**
			@brief ���K��
			@author �t���`
			@return �v�Z���ʌ��*this

			@note
			������1.0�ɐ��K�����܂��B
		*/
		Vector3D &NormalizeFast( void );
		/**
			@brief �O��
			@author �t���`
			@param In1	[in] �O�ώZ�o�p���̓x�N�g��
			@param In2	[in] �O�ώZ�o�p���̓x�N�g��
			@return �v�Z���ʌ��*this
		*/
		Vector3D& Cross( const Vector3D &In1, const Vector3D &In2 );
		/**
			@brief ���˃x�N�g���̎擾
			@author �t���`
			@param In1	[in] ���ˑΏۂ̖@��
			@param In2	[in] ���˃x�N�g��
			@return �v�Z���ʌ��*this
		*/
		Vector3D& Reflect( const Vector3D &In1, const Vector3D &In2 );
		/**
			@brief �g��k���{��]�ϊ�
			@author �t���`
			@param In1	[in] �ϊ����x�N�g��
			@param In2	[in] �ϊ��p�}�g���b�N�X
			@return �v�Z���ʌ��*this
		*/
		Vector3D& TransformNormal( const Vector3D &In1, const Matrix &In2 );
		/**
			@brief �g��k���{��]�{�ړ��ϊ�
			@author �t���`
			@param In1	[in] �ϊ����x�N�g��
			@param In2	[in] �ϊ��p�}�g���b�N�X
			@return �v�Z���ʌ��*this
		*/
		Vector3D& TransformCoord( const Vector3D &In1, const Matrix &In2 );
		/**
			@brief �����ϊ�
			@author �t���`
			@param In1	[in] �ϊ����x�N�g��
			@param In2	[in] �ϊ��p�}�g���b�N�X
			@return �v�Z���ʌ��*this
		*/
		Vector3D& TransformProjection( const Vector3D &In1, const Matrix &In2 );
		/**
			@brief ���K��
			@author �t���`
			@param In	[in] ���K�����̃x�N�g��
			@return �v�Z���ʌ��*this
		*/
		Vector3D &Normalize( const Vector3D &In );
		/**
			@brief ���K��
			@author �t���`
			@param In	[in] ���K�����̃x�N�g��
			@return �v�Z���ʌ��*this
		*/
		Vector3D &NormalizeFast( const Vector3D &In );
		/**
			@brief �O��
			@author �t���`
			@param In	[in] �O�ϗp�̃x�N�g��
			@return �v�Z���ʌ��*this
		*/
		Vector3D& Cross( const Vector3D &In );
		/**
			@brief ����
			@author �t���`
			@param In	[in] ���˗p�@��
			@return �v�Z���ʌ��*this
		*/
		Vector3D& Reflect( const Vector3D &In );
		/**
			@brief �g��k���{��]�ϊ�
			@author �t���`
			@param In	[in] �ϊ��p�}�g���b�N�X
			@return �v�Z���ʌ��*this
		*/
		Vector3D& TransformNormal( const Matrix &In );
		/**
			@brief �g��k���{��]�{�ړ��ϊ�
			@author �t���`
			@param In	[in] �ϊ��p�}�g���b�N�X
			@return �v�Z���ʌ��*this
		*/
		Vector3D& TransformCoord( const Matrix &In );
		/**
			@brief �����ϊ�
			@author �t���`
			@param In	[in] �ϊ��p�}�g���b�N�X
			@return �v�Z���ʌ��*this
		*/
		Vector3D& TransformProjection( const Matrix &In );
		/**
			@brief X����]
			@author �t���`
			@param Angle	[in] ��]�p�x
			@return �v�Z���ʌ��*this
		*/
		Vector3D& RotationX( Sint32 Angle );
		/**
			@brief Y����]
			@author �t���`
			@param Angle	[in] ��]�p�x
			@return �v�Z���ʌ��*this
		*/
		Vector3D& RotationY( Sint32 Angle );
		/**
			@brief Z����]
			@author �t���`
			@param Angle	[in] ��]�p�x
			@return �v�Z���ʌ��*this
		*/
		Vector3D& RotationZ( Sint32 Angle );
		/**
			@brief �x�N�g�������ɉ�]
			@author �t���`
			@param Angle	[in] ��]�p�x
			@param Axis		[in] ��]��
			@return �v�Z���ʌ��*this
		*/
		Vector3D& RotationAxis( Sint32 Angle, const Vector3D &Axis );
		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		Vector3D operator + () const
		{
			return *this;
		}
		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		Vector3D operator - () const
		{
			return Vector3D(-x, -y, -z);
		}
		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		Bool operator == ( const Vector3D &v )
		{
			return (x == v.x) && (y == v.y) && (z == v.z);
		}
		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		Bool operator != ( const Vector3D &v )
		{
			return (x != v.x) || (y != v.y) || (z != v.z);
		}
		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		Vector3D& operator += ( Float f )
		{
			x += f;
			y += f;
			z += f;
			return *this;
		}
		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		Vector3D& operator -= ( Float f )
		{
			x -= f;
			y -= f;
			z -= f;
			return *this;
		}
		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		Vector3D& operator *= ( Float f )
		{
			x *= f;
			y *= f;
			z *= f;
			return *this;
		}
		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		Vector3D& operator /= ( Float f )
		{
			x /= f;
			y /= f;
			z /= f;
			return *this;
		}
		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		Vector3D& operator += ( const Vector3D &v )
		{
			x += v.x;
			y += v.y;
			z += v.z;
			return *this;
		}
		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		Vector3D& operator -= ( const Vector3D &v )
		{
			x -= v.x;
			y -= v.y;
			z -= v.z;
			return *this;
		}
		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		Vector3D& operator *= ( const Vector3D &v )
		{
			x *= v.x;
			y *= v.y;
			z *= v.z;
			return *this;
		}
		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		Vector3D& operator /= ( const Vector3D &v )
		{
			x /= v.x;
			y /= v.y;
			z /= v.z;
			return *this;
		}
		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		Vector3D operator + ( Float f ) const
		{
			return Vector3D(x + f, y + f, z + f);
		}
		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		Vector3D operator - ( Float f ) const
		{
			return Vector3D(x - f, y - f, z - f);
		}
		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		Vector3D operator * ( Float f ) const
		{
			return Vector3D(x * f, y * f, z * f);
		}
		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		Vector3D operator / ( Float f ) const
		{
			return Vector3D(x / f, y / f, z / f);
		}
		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		Vector3D operator + ( const Vector3D &v ) const
		{
			return Vector3D(x + v.x, y + v.y, z + v.z);
		}
		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		Vector3D operator - ( const Vector3D &v ) const
		{
			return Vector3D(x - v.x, y - v.y, z - v.z);
		}
		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		Vector3D operator * ( const Vector3D &v ) const
		{
			return Vector3D(x * v.x, y * v.y, z * v.z);
		}
		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		Vector3D operator / ( const Vector3D &v ) const
		{
			return Vector3D(x - v.x, y - v.y, z - v.z);
		}
	};
}
}

#pragma once


/**
	@file
	@brief 4�����x�N�g��
	@author �t���`
*/

//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Math
{
	/**
		@brief 4�����x�N�g�����Z�N���X
	*/
	class SELENE_DLL_API Vector4D
	{
	public:
		Float x;
		Float y;
		Float z;
		Float w;

	public:
		/**
			@brief �R���X�g���N�^
			@author �t���`
		*/
		Vector4D();
		/**
			@brief �R���X�g���N�^
			@author �t���`
			@param v	[in] ���́ix, y, 0, 1)�ɓW�J
		*/
		Vector4D( const Vector2D &v );
		/**
			@brief �R���X�g���N�^
			@author �t���`
			@param v	[in] ���́ix, y, z, 1)�ɓW�J
		*/
		Vector4D( const Vector3D &v );
		/**
			@brief �R���X�g���N�^
			@author �t���`
			@param v	[in] ����
		*/
		Vector4D( const Vector4D &v );
		/**
			@brief �R���X�g���N�^
			@author �t���`
			@param fPx	[in] x�����l
			@param fPy	[in] y�����l
			@param fPz	[in] z�����l
			@param fPw	[in] w�����l
		*/
		Vector4D( Float fPx, Float fPy = 0.0f, Float fPz = 0.0f, Float fPw = 1.0f );
		/**
			@brief ���Z
			@author �t���`
			@param In1	[in] ���Z�p���̓x�N�g��
			@param In2	[in] ���Z�p���̓x�N�g��
			@return �v�Z���ʌ��*this

			@note
			this = In + In2
		*/
		Vector4D& Add( const Vector4D &In1, const Vector4D &In2 );
		/**
			@brief ���Z
			@author �t���`
			@param In1	[in] ���Z�p���̓x�N�g��
			@param In2	[in] ���Z�p���̓x�N�g��
			@return �v�Z���ʌ��*this

			@note
			this = In - In2
		*/
		Vector4D& Sub( const Vector4D &In1, const Vector4D &In2 );
		/**
			@brief �l�ݒ�
			@author �t���`
			@param fPx	[in] x�ݒ�l
			@param fPy	[in] y�ݒ�l
			@param fPz	[in] z�ݒ�l
			@param fPw	[in] w�ݒ�l
			@return �v�Z���ʌ��*this
		*/
		Vector4D& Set( Float fPx, Float fPy, Float fPz, Float fPw = 1.0f );
		/**
			@brief �����̓��擾
			@author �t���`
			@return �����̓��
		*/
		Float LengthSq( void ) const;
		/**
			@brief �����擾
			@author �t���`
			@return ����
		*/
		Float Length( void ) const;
		/**
			@brief �����擾
			@author �t���`
			@return ����
		*/
		Float LengthFast( void ) const;
		/**
			@brief ����
			@author �t���`
			@param In	[in] ���ώZ�o�p���̓x�N�g��
			@return ����
		*/
		Float Dot( const Vector4D &In ) const;
		/**
			@brief ���K��
			@author �t���`
			@return �v�Z���ʌ��*this

			@note
			������1.0�ɐ��K�����܂��B
		*/
		Vector4D& Normalize( void );
		/**
			@brief ���K��
			@author �t���`
			@return �v�Z���ʌ��*this

			@note
			������1.0�ɐ��K�����܂��B
		*/
		Vector4D& NormalizeFast( void );
		/**
			@brief �O��
			@author �t���`
			@param In1	[in] �O�ώZ�o�p���̓x�N�g��
			@param In2	[in] �O�ώZ�o�p���̓x�N�g��
			@return �v�Z���ʌ��*this
		*/
		Vector4D& Cross( const Vector4D &In1, const Vector4D &In2 );
		/**
			@brief ���˃x�N�g���̎擾
			@author �t���`
			@param In1	[in] ���ˑΏۂ̖@��
			@param In2	[in] ���˃x�N�g��
			@return �v�Z���ʌ��*this
		*/
		Vector4D& Reflect( const Vector4D &In1, const Vector4D &In2 );
		/**
			@brief �g��k���{��]�ϊ�
			@author �t���`
			@param In1	[in] �ϊ����x�N�g��
			@param In2	[in] �ϊ��p�}�g���b�N�X
			@return �v�Z���ʌ��*this
		*/
		Vector4D& TransformNormal( const Vector4D &In1, const Matrix &In2 );
		/**
			@brief �g��k���{��]�{�ړ��ϊ�
			@author �t���`
			@param In1	[in] �ϊ����x�N�g��
			@param In2	[in] �ϊ��p�}�g���b�N�X
			@return �v�Z���ʌ��*this
		*/
		Vector4D& TransformCoord( const Vector4D &In1, const Matrix &In2 );
		/**
			@brief �����ϊ�
			@author �t���`
			@param In1	[in] �ϊ����x�N�g��
			@param In2	[in] �ϊ��p�}�g���b�N�X
			@return �v�Z���ʌ��*this
		*/
		Vector4D& TransformProjection( const Vector4D &In1, const Matrix &In2 );
		/**
			@brief ���K��
			@author �t���`
			@param In	[in] ���K�����̃x�N�g��
			@return �v�Z���ʌ��*this
		*/
		Vector4D& Normalize( const Vector4D &In );
		/**
			@brief ���K��
			@author �t���`
			@param In	[in] ���K�����̃x�N�g��
			@return �v�Z���ʌ��*this
		*/
		Vector4D& NormalizeFast( const Vector4D &In );
		/**
			@brief �O��
			@author �t���`
			@param In	[in] �O�ϗp�̃x�N�g��
			@return �v�Z���ʌ��*this
		*/
		Vector4D& Cross( const Vector4D &In );
		/**
			@brief ����
			@author �t���`
			@param In	[in] ���˗p�@��
			@return �v�Z���ʌ��*this
		*/
		Vector4D& Reflect( const Vector4D &In );
		/**
			@brief �g��k���{��]�ϊ�
			@author �t���`
			@param In	[in] �ϊ��p�}�g���b�N�X
			@return �v�Z���ʌ��*this
		*/
		Vector4D& TransformNormal( const Matrix &In );
		/**
			@brief �g��k���{��]�{�ړ��ϊ�
			@author �t���`
			@param In	[in] �ϊ��p�}�g���b�N�X
			@return �v�Z���ʌ��*this
		*/
		Vector4D& TransformCoord( const Matrix &In );
		/**
			@brief �����ϊ�
			@author �t���`
			@param In	[in] �ϊ��p�}�g���b�N�X
			@return �v�Z���ʌ��*this
		*/
		Vector4D& TransformProjection( const Matrix &In );
		/**
			@brief X����]
			@author �t���`
			@param Angle	[in] ��]�p�x
			@return �v�Z���ʌ��*this
		*/
		Vector4D& RotationX( Sint32 Angle );
		/**
			@brief Y����]
			@author �t���`
			@param Angle	[in] ��]�p�x
			@return �v�Z���ʌ��*this
		*/
		Vector4D& RotationY( Sint32 Angle );
		/**
			@brief Z����]
			@author �t���`
			@param Angle	[in] ��]�p�x
			@return �v�Z���ʌ��*this
		*/
		Vector4D& RotationZ( Sint32 Angle );
		/**
			@brief �x�N�g�������ɉ�]
			@author �t���`
			@param Angle	[in] ��]�p�x
			@param Axis		[in] ��]��
			@return �v�Z���ʌ��*this
		*/
		Vector4D& RotationAxis( Sint32 Angle, const Vector3D &Axis );
		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		Bool operator == ( const Vector4D &v )
		{
			return (x == v.x) && (y == v.y) && (z == v.z) && (w == v.w);
		}
		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		Bool operator != ( const Vector4D &v )
		{
			return (x != v.x) || (y != v.y) || (z != v.z) || (w != v.w);
		}
		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		Vector4D operator + () const
		{
			return *this;
		}
		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		Vector4D operator - () const
		{
			return Vector4D(-x, -y, -z, 1.0);
		}
		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		Vector4D& operator += ( const Vector2D &v )
		{
			x += v.x;
			y += v.y;
			return *this;
		}
		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		Vector4D& operator -= ( const Vector2D &v )
		{
			x -= v.x;
			y -= v.y;
			return *this;
		}
		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		Vector4D& operator *= ( const Vector2D &v )
		{
			x *= v.x;
			y *= v.y;
			return *this;
		}
		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		Vector4D& operator /= ( const Vector2D &v )
		{
			x /= v.x;
			y /= v.y;
			return *this;
		}
		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		Vector4D& operator += ( const Vector3D &v )
		{
			x += v.x;
			y += v.y;
			z += v.z;
			return *this;
		}
		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		Vector4D& operator -= ( const Vector3D &v )
		{
			x -= v.x;
			y -= v.y;
			z -= v.z;
			return *this;
		}
		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		Vector4D& operator *= ( const Vector3D &v )
		{
			x *= v.x;
			y *= v.y;
			z *= v.z;
			return *this;
		}
		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		Vector4D& operator /= ( const Vector3D &v )
		{
			x /= v.x;
			y /= v.y;
			z /= v.z;
			return *this;
		}
		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		Vector4D& operator += ( Float f )
		{
			x += f;
			y += f;
			z += f;
			w += f;
			return *this;
		}
		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		Vector4D& operator -= ( Float f )
		{
			x -= f;
			y -= f;
			z -= f;
			w -= f;
			return *this;
		}
		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		Vector4D& operator *= ( Float f )
		{
			x *= f;
			y *= f;
			z *= f;
			w *= f;
			return *this;
		}
		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		Vector4D& operator /= ( Float f )
		{
			x /= f;
			y /= f;
			z /= f;
			w /= f;
			return *this;
		}
		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		Vector4D& operator += ( const Vector4D &v )
		{
			x += v.x;
			y += v.y;
			z += v.z;
			w += v.w;
			return *this;
		}
		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		Vector4D& operator -= ( const Vector4D &v )
		{
			x -= v.x;
			y -= v.y;
			z -= v.z;
			w -= v.w;
			return *this;
		}
		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		Vector4D& operator *= ( const Vector4D &v )
		{
			x *= v.x;
			y *= v.y;
			z *= v.z;
			w *= v.w;
			return *this;
		}
		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		Vector4D& operator /= ( const Vector4D &v )
		{
			x /= v.x;
			y /= v.y;
			z /= v.z;
			w /= v.w;
			return *this;
		}
		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		Vector4D& operator *= ( Matrix &m )
		{
			return TransformCoord( m );
		}
		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		Vector4D operator + ( Float f ) const
		{
			return Vector4D(x + f, y + f, z + f, w + f );
		}
		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		Vector4D operator - ( Float f ) const
		{
			return Vector4D(x - f, y - f, z - f, w - f );
		}
		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		Vector4D operator * ( Float f ) const
		{
			return Vector4D(x * f, y * f, z * f, w * f );
		}
		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		Vector4D operator / ( Float f ) const
		{
			return Vector4D(x / f, y / f, z / f, w / f );
		}
		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		Vector4D operator + ( const Vector2D &v ) const
		{
			return Vector4D(x + v.x, y + v.y, z, w );
		}
		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		Vector4D operator - ( const Vector2D &v ) const
		{
			return Vector4D(x - v.x, y - v.y, z, w );
		}
		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		Vector4D operator * ( const Vector2D &v ) const
		{
			return Vector4D(x * v.x, y * v.y, z, w );
		}
		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		Vector4D operator / ( const Vector2D &v ) const
		{
			return Vector4D(x / v.x, y / v.y, z, w );
		}
		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		Vector4D operator + ( const Vector3D &v ) const
		{
			return Vector4D(x + v.x, y + v.y, z + v.z, w );
		}
		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		Vector4D operator - ( const Vector3D &v ) const
		{
			return Vector4D(x - v.x, y - v.y, z - v.z, w );
		}
		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		Vector4D operator * ( const Vector3D &v ) const
		{
			return Vector4D(x * v.x, y * v.y, z * v.z, w );
		}
		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		Vector4D operator / ( const Vector3D &v ) const
		{
			return Vector4D(x / v.x, y / v.y, z / v.z, w );
		}
		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		Vector4D operator + ( const Vector4D &v ) const
		{
			return Vector4D(x + v.x, y + v.y, z + v.z, w + v.w );
		}
		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		Vector4D operator - ( const Vector4D &v ) const
		{
			return Vector4D(x - v.x, y - v.y, z - v.z, w - v.w );
		}
		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		Vector4D operator * ( const Vector4D &v ) const
		{
			return Vector4D(x * v.x, y * v.y, z * v.z, w * v.w );
		}
		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		Vector4D operator / ( const Vector4D &v ) const
		{
			return Vector4D(x / v.x, y / v.y, z / v.z, w / v.w );
		}
		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		Vector4D operator * ( Matrix &m ) const
		{
			Vector4D vTemp;
			return vTemp.TransformCoord( *this, m );
		}
	};
}
}

#pragma once


/**
	@file
	@brief �l�����Ǘ�
	@author �t���`
*/


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Math
{
	/**
		@brief �l�����N���X
	*/
	class SELENE_DLL_API Quaternion
	{
	public:
		Float x;
		Float y;
		Float z;
		Float w;

	public:
		/**
			@brief �R���X�g���N�^
			@author �t���`
		*/
		Quaternion();
		/**
			@brief �R���X�g���N�^
			@author �t���`
			@param x	[in] X�v�f
			@param y	[in] Y�v�f
			@param z	[in] Z�v�f
			@param w	[in] W�v�f
		*/
		Quaternion( Float x, Float y, Float z, Float w );
		/**
			@brief �R���X�g���N�^
			@author �t���`
			@param In	[in] �N�H�[�^�j�I��
		*/
		Quaternion( const Quaternion &In );
		/**
			@brief �R���X�g���N�^
			@author �t���`
			@param mIn	[in] �}�g���b�N�X
		*/
		Quaternion( const Matrix &mIn );
		/**
			@brief ���Z
			@author �t���`
			@param In1	[in] ���̓N�H�[�^�j�I���P
			@param In2	[in] ���̓N�H�[�^�j�I���Q
			@return �v�Z���ʌ��*this
			@note
			��̃N�H�[�^�j�I�������Z���܂��B
		*/
		Quaternion& Add( const Quaternion &In1, const Quaternion &In2 );
		/**
			@brief ���Z
			@author �t���`
			@param In1	[in] ���̓N�H�[�^�j�I���P
			@param In2	[in] ���̓N�H�[�^�j�I���Q
			@return �v�Z���ʌ��*this
			@note
			��̃N�H�[�^�j�I�������Z���܂��B
		*/
		Quaternion& Sub( const Quaternion &In1, const Quaternion &In2 );
		/**
			@brief ��Z
			@author �t���`
			@param In1	[in] ���̓N�H�[�^�j�I���P
			@param In2	[in] ���̓N�H�[�^�j�I���Q
			@return �v�Z���ʌ��*this
			@note
			��̃N�H�[�^�j�I������Z���܂��B
		*/
		Quaternion& Mul( const Quaternion &In1, const Quaternion &In2 );
		/**
			@brief ���`���
			@author �t���`
			@param In0		[in] ���̓N�H�[�^�j�I���P
			@param In1		[in] ���̓N�H�[�^�j�I���Q
			@param fRate	[in] �u�����h��(0.0�`1.0f)
			@return �v�Z���ʌ��*this
			@note
			��̃N�H�[�^�j�I������`��Ԃ��܂�
		*/
		Quaternion& Lerp( const Quaternion &In0, const Quaternion &In1, Float fRate );
		/**
			@brief ���ʐ��`���
			@author �t���`
			@param In0		[in] ���̓N�H�[�^�j�I���P
			@param In1		[in] ���̓N�H�[�^�j�I���Q
			@param fRate	[in] �u�����h��(0.0�`1.0f)
			@return �v�Z���ʌ��*this
			@note
			��̃N�H�[�^�j�I�������ʐ��`��Ԃ��܂�
		*/
		Quaternion& Slerp( const Quaternion &In0, const Quaternion &In1, Float fRate );
		/**
			@brief ���Z
			@author �t���`
			@param In	[in] ���̓N�H�[�^�j�I��
			@note
			��̃N�H�[�^�j�I�������Z���܂��B
		*/
		Quaternion& Add( const Quaternion &In );
		/**
			@brief ���Z
			@author �t���`
			@param In	[in] ���̓N�H�[�^�j�I��
			@return �v�Z���ʌ��*this
			@note
			��̃N�H�[�^�j�I�������Z���܂��B
		*/
		Quaternion& Sub( const Quaternion &In );
		/**
			@brief ��Z
			@author �t���`
			@param In	[in] ���̓N�H�[�^�j�I��
			@return �v�Z���ʌ��*this
			@note
			��̃N�H�[�^�j�I������Z���܂��B
		*/
		Quaternion& Mul( const Quaternion &In );
		/**
			@brief ���`���
			@author �t���`
			@param In		[in] ���̓N�H�[�^�j�I��
			@param fRate	[in] �u�����h��(0.0�`1.0f)
			@return �v�Z���ʌ��*this
			@note
			��̃N�H�[�^�j�I������`��Ԃ��܂�
		*/
		Quaternion& Lerp( const Quaternion &In, Float fRate );
		/**
			@brief ���ʐ��`���
			@author �t���`
			@param In		[in] ���̓N�H�[�^�j�I��
			@param fRate	[in] �u�����h��(0.0�`1.0f)
			@return �v�Z���ʌ��*this
			@note
			��̃N�H�[�^�j�I�������ʐ��`��Ԃ��܂�
		*/
		Quaternion& Slerp( const Quaternion &In, Float fRate );
		/**
			@brief ������
			@author �t���`
			@return �v�Z���ʌ��*this
			@note
			xyz=0.0�Aw=1.0�ɏ��������܂��B
		*/
		Quaternion& Identity( void );
		/**
			@brief �����̓����擾
			@author �t���`
			@return �����̓��
			@note
			�����̓����擾���܂��B
		*/
		Float LengthSq( void ) const;
		/**
			@brief �������擾
			@author �t���`
			@return ����
			@note
			�������擾���܂��B
		*/
		Float Length( void ) const;
		/**
			@brief ���ς��擾
			@author �t���`
			@return ����
			@note
			���ς��擾���܂�
		*/
		Float Dot( const Quaternion &In ) const;
		/**
			@brief ����
			@author �t���`
			@return �v�Z���ʌ��*this
			@note
			�N�H�[�^�j�I�����������܂��B
		*/
		Quaternion& Conjugate( void );
		/**
			@brief ����
			@author �t���`
			@return �v�Z���ʌ��*this
			@note
			�N�H�[�^�j�I�����������Ċi�[���܂��B
		*/
		Quaternion& Conjugate( const Quaternion &In );
	};
}
}

#pragma once


/**
	@file
	@brief �s�񉉎Z
	@author �t���`
*/


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Math
{
	/**
		@brief �s��\����
	*/
	struct SELENE_DLL_API SMatrix4x4
	{
		union {
			struct {
				Vector4D x;
				Vector4D y;
				Vector4D z;
				Vector4D w;
			};
			Float m[4][4];
		};
	};

	/**
		@brief �s��N���X
	*/
	class SELENE_DLL_API Matrix : public SMatrix4x4
	{
	public:
		/**
			@brief �R���X�g���N�^
			@author �t���`
		*/
		Matrix();

		/**
			@brief �R���X�g���N�^
			@author �t���`
		*/
		Matrix( const Matrix &Mat );

		/**
			@brief �R���X�g���N�^
			@author �t���`
		*/
		Matrix( const SMatrix4x4 &Mat );

		/**
			@brief �R���X�g���N�^
			@author �t���`
		*/
		Matrix( const Quaternion &In );

		/**
			@brief �R���X�g���N�^
			@author �t���`
		*/
		Matrix(
			Float _11, Float _12, Float _13, Float _14,
			Float _21, Float _22, Float _23, Float _24,
			Float _31, Float _32, Float _33, Float _34,
			Float _41, Float _42, Float _43, Float _44 );

		/**
			@brief �s��̒P�ʉ�
			@author �t���`
		*/
		void Identity( void );

		/**
			@brief �s��̓]�u��
			@author �t���`
			@param In	[in] �������s��
		*/
		Matrix &Transpose( const Matrix &In );

		/**
			@brief �s��̋t�s��
			@author �t���`
			@param In	[in] �������s��
		*/
		Matrix &Inverse( const Matrix &In );

		/**
			@brief �s��̍���
			@author �t���`
			@param In1		[in] �������s��P
			@param In2		[in] �������s��Q
		*/
		Matrix &Multiply( const Matrix &In1, const Matrix &In2 );

		/**
			@brief �s��̓]�u�s��
			@author �t���`
		*/
		Matrix &Transpose( void );

		/**
			@brief �s��̋t�s��
			@author �t���`
		*/
		Matrix &Inverse( void );

		/**
			@brief �s��̍���
			@author �t���`
			@param In	[in] �������s��
		*/
		Matrix &Multiply( const Matrix &In );

		/**
			@brief �w����]
			@author �t���`
			@param Angle	[in] ��]�p�x
		*/
		Matrix &RotationX( Sint32 Angle );

		/**
			@brief �x����]
			@author �t���`
			@param Angle	[in] ��]�p�x
		*/
		Matrix &RotationY( Sint32 Angle );

		/**
			@brief �y����]
			@author �t���`
			@param Angle	[in] ��]�p�x
		*/
		Matrix &RotationZ( Sint32 Angle );

		/**
			@brief �y�w�x��]�s��𐶐�
			@author �t���`
			@param AngleX	[in] �w����]�p�x
			@param AngleY	[in] �x����]�p�x
			@param AngleZ	[in] �y����]�p�x
		*/
		Matrix &RotationZXY( Sint32 AngleX, Sint32 AngleY, Sint32 AngleZ );

		/**
			@brief �C�ӎ���]
			@author �t���`
			@param Angle	[in] �p�x
			@param Axis		[in] ��]��
		*/
		Matrix &RotationAxis( Sint32 Angle, const Vector3D &Axis );

		/**
			@brief �g��k���s�񐶐�
			@author �t���`
			@param sx	[in] �w�����g�嗦
			@param sy	[in] �x�����g�嗦
			@param sz	[in] �y�����g�嗦
		*/
		Matrix &Scaling( Float sx, Float sy, Float sz );

		/**
			@brief �ړ��s�񐶐�
			@author �t���`
			@param px	[in] �w�ʒu
			@param py	[in] �x�ʒu
			@param pz	[in] �y�ʒu
		*/
		Matrix &Translation( Float px, Float py, Float pz );

		/**
			@brief �����ϊ��p�s�񐶐�
			@author �t���`
			@param Fov		[in] ��p
			@param NearZ	[in] �ߐڃN���b�v��
			@param FarZ		[in] �����N���b�v��
			@param Aspect	[in] �A�X�y�N�g��i���`��G���A�������`��G���A�c���j
		*/
		Matrix &Perspective( Sint32 Fov, Float NearZ, Float FarZ, Float Aspect );

		/**
			@brief ���s���e�p�s�񐶐�
			@author �t���`
			@param Width	[in] ����
			@param Height	[in] �c��
			@param NearZ	[in] �ߐڃN���b�v��
			@param FarZ		[in] �����N���b�v��
		*/
		Matrix &Ortho( Float Width, Float Height, Float NearZ, Float FarZ );

		/**
			@brief �C�ӓ_�����s��쐬
			@author �t���`
			@param Eye	[in] ���_
			@param At	[in] �����_
			@param Up	[in] �����
		*/
		Matrix &LookAt( const Vector3D &Eye, const Vector3D &At, const Vector3D &Up );

		/**
			@brief �s��̕���
			@author �t���`
			@param vTranslate	[in] �ړ�
			@param vScale		[in] �g��k��
			@param qRotate		[in] ��]
		*/
		void Resolution( Vector3D &vTranslate, Vector3D &vScale, Quaternion &qRotate );

		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		Matrix &operator = ( const Quaternion &q )
		{
			Float xx = q.x * q.x;
			Float yy = q.y * q.y;
			Float zz = q.z * q.z;
			Float xy = q.x * q.y;
			Float xz = q.x * q.z;
			Float yz = q.y * q.z;
			Float wx = q.w * q.x;
			Float wy = q.w * q.y;
			Float wz = q.w * q.z;

			x.x = 1.0f - 2.0f * (yy + zz);
			x.y =        2.0f * (xy - wz);
			x.z =        2.0f * (xz + wy);
			x.w = 0.0f;

			y.x =        2.0f * (xy + wz);
			y.y = 1.0f - 2.0f * (xx + zz);
			y.z =        2.0f * (yz - wx);
			y.w = 0.0f;

			z.x =        2.0f * (xz - wy);
			z.y =        2.0f * (yz + wx);
			z.z = 1.0f - 2.0f * (xx + yy);
			z.w = 0.0f;

			w.x = 0.0f;
			w.y = 0.0f;
			w.z = 0.0f;
			w.w = 1.0f;

			return *this;
		}

		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		Matrix &operator = ( const Matrix &m )
		{
			MemoryCopy( this->m, m.m, sizeof(Float[4][4]) );
			return *this;
		}

		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		Matrix &operator = ( const SMatrix4x4 &m )
		{
			MemoryCopy( this->m, m.m, sizeof(Float[4][4]) );
			return *this;
		}

		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		Matrix operator * ( const Matrix &m )
		{
			Matrix mTemp;
			return mTemp.Multiply( *this, m );
		}

		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		Matrix &operator *= ( const Matrix &m )
		{
			return Multiply( m );
		}

		/**
			@brief �P�ʍs��
			@author �t���`
			@return �P�ʍs��
		*/
		static Matrix GetIdentity( void )
		{
			Matrix mTemp;
			mTemp.Identity();
			return mTemp;
		}

		/**
			@brief �ړ��s�񐶐�
			@author �t���`
			@param px	[in] �w�ʒu
			@param py	[in] �x�ʒu
			@param pz	[in] �y�ʒu
			@return �ړ��s��
		*/
		static Matrix GetTranslation( Float px, Float py, Float pz )
		{
			Matrix mTemp;
			mTemp.Translation( px, py, pz );
			return mTemp;
		}

		/**
			@brief �w����]
			@author �t���`
			@param Angle	[in] ��]�p�x
			@return ��]�s��
		*/
		static Matrix GetRotationX( Sint32 Angle )
		{
			Matrix mTemp;
			mTemp.RotationX( Angle );
			return mTemp;
		}

		/**
			@brief �x����]
			@author �t���`
			@param Angle	[in] ��]�p�x
			@return ��]�s��
		*/
		static Matrix GetRotationY( Sint32 Angle )
		{
			Matrix mTemp;
			mTemp.RotationY( Angle );
			return mTemp;
		}

		/**
			@brief �y����]
			@author �t���`
			@param Angle	[in] ��]�p�x
			@return ��]�s��
		*/
		static Matrix GetRotationZ( Sint32 Angle )
		{
			Matrix mTemp;
			mTemp.RotationZ( Angle );
			return mTemp;
		}
		
		/**
			@brief �g��k���s��
			@author �t���`
			@param sx	[in] �w�����g�嗦
			@param sy	[in] �x�����g�嗦
			@param sz	[in] �y�����g�嗦
			@return �g��k���s��
		*/
		static Matrix GetScaling( Float sx, Float sy, Float sz )
		{
			Matrix mTemp;
			mTemp.Scaling( sx, sy, sz );
			return mTemp;
		}
	};
}
}

#pragma once


/**
	@file
	@brief �p���Ǘ�
	@author �t���`
*/


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Math
{
	/**
		@brief �p������N���X
	*/
	class SELENE_DLL_API Style
	{
	private:
		Vector3D m_vUp;					///< ������x�N�g��
		Vector3D m_vRight;				///< �E�����x�N�g��
		Vector3D m_vFront;				///< �O�����x�N�g��
		Vector3D m_vPosition;			///< �ʒu�x�N�g��
		Vector3D m_vLocalPosition;		///< �ʒu�x�N�g��
		Vector3D m_vScale;				///< �g��k���x�N�g��

		Bool m_IsScale;					///< �g��k��
		Bool m_IsLocal;					///< ���[�J���ړ�

	public:
		/**
			@brief �R���X�g���N�^
			@author �t���`
		*/
		Style();
		/**
			@brief �R���X�g���N�^
			@author �t���`
			@param Style	[in] �R�s�[��
		*/
		Style( const Style &Style );
		/**
			@brief �ϊ�������
			@author �t���`

			@note
			�ϊ������������ď����l�ɖ߂��܂��B
		*/
		virtual void TransformReset( void );
		/**
			@brief X����]
			@author �t���`
			@param Rot		[in] �p�x

			@note
			���[���h���W�����X������ɉ�]�����܂��B
		*/
		virtual void RotationX( Sint32 Rot );
		/**
			@brief Y����]
			@author �t���`
			@param Rot		[in] �p�x

			@note
			���[���h���W�����Y������ɉ�]�����܂��B
		*/
		virtual void RotationY( Sint32 Rot );
		/**
			@brief Z����]
			@author �t���`
			@param Rot		[in] �p�x

			@note
			���[���h���W�����Z������ɉ�]�����܂��B
		*/
		virtual void RotationZ( Sint32 Rot );
		/**
			@brief �s�b�`���O
			@author �t���`
			@param Rot		[in] �p�x

			@note
			���[�J�����W�����X������ɉ�]�����܂��B
		*/
		virtual void LocalRotationX( Sint32 Rot );
		/**
			@brief �w�b�f�B���O
			@author �t���`
			@param Rot		[in] �p�x

			@note
			���[�J�����W�����Y������ɉ�]�����܂��B
		*/
		virtual void LocalRotationY( Sint32 Rot );
		/**
			@brief ���[�����O
			@author �t���`
			@param Rot		[in] �p�x

			@note
			���[�J�����W�����Z������ɉ�]�����܂��B
		*/
		virtual void LocalRotationZ( Sint32 Rot );
		/**
			@brief �N�H�[�^�j�I���ŉ�]
			@author �t���`
			@param Quat		[in] �N�H�[�^�j�I��

			@note
			�N�H�[�^�j�I�����g���ĉ�]�����܂��B
		*/
		virtual void RotationQuaternion( const Quaternion &Quat );
		/**
			@brief �ړ�
			@author �t���`
			@param fPx		[in] X���W
			@param fPy		[in] Y���W
			@param fPz		[in] Z���W

			@note
			�w����W�ֈړ������܂��B
		*/
		virtual void Translation( Float fPx, Float fPy, Float fPz );
		/**
			@brief �ړ�
			@author �t���`
			@param vPos		[in] ���W

			@note
			�w����W�ֈړ������܂��B
		*/
		virtual void Translation( const Vector3D &vPos );
		/**
			@brief �ړ�
			@author �t���`
			@param fPx		[in] X���W
			@param fPy		[in] Y���W
			@param fPz		[in] Z���W

			@note
			�w����W�ֈړ������܂��B
		*/
		virtual void LocalTranslation( Float fPx, Float fPy, Float fPz );
		/**
			@brief �ړ�
			@author �t���`
			@param vPos		[in] ���W

			@note
			�w����W�ֈړ������܂��B
		*/
		virtual void LocalTranslation( const Vector3D &vPos );
		/**
			@brief �g��k��
			@author �t���`
			@param fSx		[in] X���g��k����
			@param fSy		[in] Y���g��k����
			@param fSz		[in] Z���g��k����

			@note
			�w��{���Ŋg��k���������܂��B
		*/
		virtual void Scaling( Float fSx, Float fSy, Float fSz );
		/**
			@brief �C�ӕ����֎p��
			@author �t���`
			@param vEye		[in] ���_�ʒu
			@param vAt		[in] �ڕW�ʒu
			@param vUp		[in] �����

			@note
			�C�ӂ̏ꏊ����w��̏ꏊ�������ꍇ�̎p�����쐬���܂��B
		*/
		virtual void LookAt( const Vector3D &vEye, const Vector3D &vAt, const Vector3D &vUp );
		/**
			@brief �s�񂩂�ϊ�
			@author �t���`
			@param Mat		[in] �ϊ��}�g���b�N�X

			@note
			�w��̃}�g���b�N�X�ɂȂ�悤�Ȏp���f�[�^�𐶐����܂��B
		*/
		virtual void FromMatrix( const Matrix &Mat );
		/**
			@brief X����]�p�x�擾
			@author �t���`
			@return X���ɂ������]�p�x

			@note
			X���ɂ������]�p�x���擾���܂��B
		*/
		virtual Sint32 GetAngleX( void ) const;
		/**
			@brief Y����]�p�x�擾
			@author �t���`
			@return Y���ɂ������]�p�x

			@note
			Y���ɂ������]�p�x���擾���܂��B
		*/
		virtual Sint32 GetAngleY( void ) const;
		/**
			@brief Z����]�p�x�擾
			@author �t���`
			@return Z���ɂ������]�p�x

			@note
			Z���ɂ������]�p�x���擾���܂��B
		*/
		virtual Sint32 GetAngleZ( void ) const;
		/**
			@brief �ʒu�ݒ�
			@author �t���`
			@param Pos	[in] �ʒu

			@note
			�w��ʒu�Ɉړ����܂��B
		*/
		virtual void SetPosition( const Vector3D &Pos );
		/**
			@brief �O���ݒ�
			@author �t���`
			@param Vec	[in] �O���x�N�g��

			@note
			�p���̐��ʕ�����ݒ肵�܂��B
		*/
		virtual void SetFront( const Vector3D &Vec );
		/**
			@brief �E���ݒ�
			@author �t���`
			@param Vec	[in] �E���x�N�g��

			@note
			�p���̉E�������ݒ肵�܂��B
		*/
		virtual void SetRight( const Vector3D &Vec );
		/**
			@brief ����ݒ�
			@author �t���`
			@param Vec	[in] ����x�N�g��

			@note
			�p���̏�������ݒ肵�܂��B
		*/
		virtual void SetUp( const Vector3D &Vec );
		/**
			@brief �ʒu�擾
			@author �t���`
			@param Pos	[out] �i�[��

			@note
			�w��ʒu�Ɉړ����܂��B
		*/
		virtual void GetPosition( Vector3D &Pos ) const;
		/**
			@brief �O���擾
			@author �t���`
			@param Vec	[out] �i�[��

			@note
			�p���̐��ʕ������擾���܂��B
		*/
		virtual void GetFront( Vector3D &Vec ) const;
		/**
			@brief �E���擾
			@author �t���`
			@param Vec	[out] �i�[��

			@note
			�p���̉E��������擾���܂��B
		*/
		virtual void GetRight( Vector3D &Vec ) const;
		/**
			@brief ����擾
			@author �t���`
			@param Vec	[out] �i�[��

			@note
			�p���̏��������擾���܂��B
		*/
		virtual void GetUp( Vector3D &Vec ) const;
		/**
			@brief �p���s����擾
			@author �t���`
			@param Mat	[out] �i�[��

			@note
			�p���s����擾���܂��B<BR>
			���̍s��ɂ͉�]�v�f�����܂݂܂���B
		*/
		virtual void GetStyle( Matrix &Mat ) const;
		/**
			@brief �t�p���s����擾
			@author �t���`
			@param Mat	[out] �i�[��

			@note
			�t�p���s����擾���܂��B<BR>
			���̍s��ɂ͉�]�v�f�����܂݂܂���B
		*/
		virtual void GetStyleInverse( Matrix &Mat ) const;
		/**
			@brief �ϊ��s����擾
			@author �t���`
			@param Mat	[out] �i�[��

			@note
			�ϊ��s����擾���܂��B<BR>
			���̍s��ɂ͉�]�ƈʒu�v�f�����܂݂܂���B
		*/
		virtual void GetTransform( Matrix &Mat ) const;
		/**
			@brief �t�ϊ��s����擾
			@author �t���`
			@param Mat	[out] �i�[��

			@note
			�t�ϊ��s����擾���܂��B<BR>
			���̍s��ɂ͉�]�ƈʒu�v�f�����܂݂܂���B
		*/
		virtual void GetTransformInverse( Matrix &Mat ) const;
		/**
			@brief �ϊ��s����擾
			@author �t���`
			@param Mat	[out] �i�[��

			@note
			�ϊ��s����擾���܂��B<BR>
			���̍s��ɂ͉�]�ƈʒu�Ɗg��k���̑S�v�f���܂݂܂��B
		*/
		virtual void GetTransformWithScale( Matrix &Mat ) const;
		/**
			@brief �t�ϊ��s����擾
			@author �t���`
			@param Mat	[out] �i�[��

			@note
			�t�ϊ��s����擾���܂��B<BR>
			���̍s��ɂ͉�]�ƈʒu�Ɗg��k���̑S�v�f���܂݂܂��B
		*/
		virtual void GetTransformInverseWithScale( Matrix &Mat ) const;
	};
}
}

#pragma once


/**
	@file
	@brief �Z�p���Z
	@author �t���`
*/


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Math
{
/**
@brief sin�擾
@author �t���`
@param Angle	[in] 1��65536�Ƃ����p�x
@return sin�l

@note
sin�l���擾���܂��B

@code

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  // 90�x�̎���sin�l���擾
  Float fRet = Math::Sin( DEG_TO_ANGLE(90) );

  return 0;
}
@endcode
*/
SELENE_DLL_API Float Sin( Sint32 Angle );

/**
@brief cos�擾
@author �t���`
@param Angle	[in] 1��65536�Ƃ����p�x
@return cos�l

@note
cos�l���擾���܂��B

@code

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  // 90�x�̎���cos�l���擾
  Float fRet = Math::Cos( DEG_TO_ANGLE(90) );

  return 0;
}
@endcode
*/
SELENE_DLL_API Float Cos( Sint32 Angle );

/**
@brief �x�N�g���擾
@author �t���`
@param Angle	[in] 1��65536�Ƃ����p�x
@return 2D�x�N�g��

@note
���K�����ꂽ2D�x�N�g�����擾���܂��B

@code

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  // 90�x�̕����������P�ʃx�N�g�����擾
  Vector2D vDir = Math::GetVector( DEG_TO_ANGLE(90) );

  return 0;
}
@endcode
*/
SELENE_DLL_API Vector2D GetVector( Sint32 Angle );

/**
@brief atan2�擾
@author �t���`
@param Dx	[in] �w����
@param Dy	[in] �x����
@return X-Y�̐����p�x

@note
X,Y���狁�߂���atan2�̒l��Selene�̊p�x�P�ʂ�<BR>
���킹���l�Ŏ擾���܂��B

@code

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  // (x,y)=(100.0f,50.0f)�ɂ����錴�_��̊p�x�����߂�
  Sint32 Angle = Math::ATan2( 100.0f, 50.0f );

  return 0;
}
@endcode
*/
SELENE_DLL_API Sint32 ATan2( Float Dx, Float Dy );

	/**
		@brief ��`�f�[�^
		@author �t���`
	*/
	template <typename Type>
	class Rect2D
	{
	public:
		Type x;					///< �w�n�_���W
		Type y;					///< �x�n�_���W
		Type w;					///< �w�T�C�Y
		Type h;					///< �x�T�C�Y

		/**
			@brief �R���X�g���N�^
			@author �t���`
		*/
		Rect2D()
		{
		}

		/**
			@brief �R���X�g���N�^
			@author �t���`
		*/
		template <typename TypeT>
		Rect2D( const Rect2D<TypeT> &Src )
		{
			this->x = (Type)Src.x;
			this->y = (Type)Src.y;
			this->w = (Type)Src.w;
			this->h = (Type)Src.h;
		}

		/**
			@brief �R���X�g���N�^
			@author �t���`

			@param x		[in] �w�n�_���W
			@param y		[in] �x�n�_���W
			@param w		[in] �w�T�C�Y
			@param h		[in] �x�T�C�Y
		*/
		Rect2D( Type x, Type y, Type w, Type h )
		{
			this->x = x;
			this->y = y;
			this->w = w;
			this->h = h;
		}

		/**
			@brief �l�ݒ�
			@author �t���`

			@param x		[in] �w���S���W
			@param y		[in] �x���S���W
			@param w		[in] �w�T�C�Y
			@param h		[in] �x�T�C�Y
		*/
		void Set( Type x, Type y, Type w, Type h )
		{
			this->x = x;
			this->y = y;
			this->w = w;
			this->h = h;
		}

		/**
			@brief �l�ݒ�
			@author �t���`

			@param x		[in] �w���S���W
			@param y		[in] �x���S���W
			@param w		[in] �w�T�C�Y
			@param h		[in] �x�T�C�Y
			@param Scale	[in] �g��k����
		*/
		void SetCenter( Type x, Type y, Type w, Type h, Float Scale = 1.0f )
		{
			this->w = (Type)(w * Scale);
			this->h = (Type)(h * Scale);
			this->x = x - (Type)(toF(this->w) * 0.5f);
			this->y = y - (Type)(toF(this->h) * 0.5f);
		}

		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		template <typename TypeT>
		Rect2D<Type> & operator = ( const Rect2D<TypeT> &Src )
		{
			this->x = (Type)Src.x;
			this->y = (Type)Src.y;
			this->w = (Type)Src.w;
			this->h = (Type)Src.h;
			return *this;
		}
	};

	/**
		@brief �Q�����̓_
		@author �t���`
	*/
	template <typename Type>
	class Point2D
	{
	public:
		Type x;					///< �w���W
		Type y;					///< �x���W

		/**
			@brief �R���X�g���N�^
			@author �t���`
		*/
		Point2D()
		{
		}

		/**
			@brief �R���X�g���N�^
			@author �t���`
		*/
		template <typename TypeT>
		Point2D( const Point2D<TypeT> &Src )
		{
			this->x = (Type)Src.x;
			this->y = (Type)Src.y;
		}

		/**
			@brief �R���X�g���N�^
			@author �t���`

			@param x		[in] �w���W
			@param y		[in] �x���W
		*/
		Point2D( Type x, Type y )
		{
			this->x = x;
			this->y = y;
		}

		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		Point2D<Type> operator + ( Point2D<Type> &Pt )
		{
			return Point2D<Type>( this->x + Pt.x, this->y + Pt.y );
		}

		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		Point2D<Type> operator - ( Point2D<Type> &Pt )
		{
			return Point2D<Type>( this->x - Pt.x, this->y - Pt.y );
		}

		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		Point2D<Type> operator * ( Type Mul )
		{
			return Point2D<Type>( this->x * Mul, this->y * Mul );
		}

		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		Point2D<Type> operator / ( Type Div )
		{
			return Point2D<Type>( this->x / Div, this->y / Div );
		}

		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		Point2D<Type> &operator += ( Point2D<Type> &Pt )
		{
			this->x += Pt.x;
			this->y += Pt.y;
			return *this;
		}

		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		Point2D<Type> &operator -= ( Point2D<Type> &Pt )
		{
			this->x -= Pt.x;
			this->y -= Pt.y;
			return *this;
		}

		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		Point2D<Type> &operator *= ( Type Mul )
		{
			this->x *= Mul;
			this->y *= Mul;
			return *this;
		}

		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		Point2D<Type> &operator /= ( Type Div )
		{
			this->x /= Div;
			this->y /= Div;
			return *this;
		}

		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		template <typename TypeT>
		Point2D<Type> & operator = ( const Point2D<TypeT> &Src )
		{
			this->x = (Type)Src.x;
			this->y = (Type)Src.y;
			return *this;
		}
	};

	/**
		@brief �R�����̓_
	*/
	template <typename Type>
	struct Point3D
	{
		Type x;							///< �w�ʒu
		Type y;							///< �x�ʒu
		Type z;							///< �y�ʒu

		/**
			@brief �R���X�g���N�^
			@author �t���`
		*/
		Point3D()
		{
		}

		/**
			@brief �R���X�g���N�^
			@author �t���`
		*/
		template <typename TypeT>
		Point3D( const Point3D<TypeT> &Src )
		{
			this->x = (Type)Src.x;
			this->y = (Type)Src.y;
			this->z = (Type)Src.z;
		}

		/**
			@brief �R���X�g���N�^
			@author �t���`

			@param x		[in] �w���W
			@param y		[in] �x���W
			@param z		[in] �y���W
		*/
		Point3D( Type x, Type y, Type z )
		{
			this->x = x;
			this->y = y;
			this->z = z;
		}

		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		Point3D<Type> operator + ( Point3D<Type> &Pt )
		{
			return Point3D<Type>( this->x + Pt.x, this->y + Pt.y, this->z + Pt.z );
		}

		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		Point3D<Type> operator - ( Point3D<Type> &Pt )
		{
			return Point3D<Type>( this->x - Pt.x, this->y - Pt.y, this->z - Pt.z );
		}

		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		Point3D<Type> operator * ( Type Mul )
		{
			return Point3D<Type>( this->x * Mul, this->y * Mul, this->z * Mul );
		}

		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		Point3D<Type> operator / ( Type Div )
		{
			return Point3D<Type>( this->x / Div, this->y / Div, this->z / Div );
		}

		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		Point3D<Type> &operator += ( Point3D<Type> &Pt )
		{
			this->x += Pt.x;
			this->y += Pt.y;
			this->z += Pt.z;
			return *this;
		}

		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		Point3D<Type> &operator -= ( Point3D<Type> &Pt )
		{
			this->x -= Pt.x;
			this->y -= Pt.y;
			this->z -= Pt.z;
			return *this;
		}

		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		Point3D<Type> &operator *= ( Type Mul )
		{
			this->x *= Mul;
			this->y *= Mul;
			this->z *= Mul;
			return *this;
		}

		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		Point3D<Type> &operator /= ( Type Div )
		{
			this->x /= Div;
			this->y /= Div;
			this->z /= Div;
			return *this;
		}

		/**
			@brief �I�y���[�^�[
			@author �t���`
		*/
		template <typename TypeT>
		Point3D<Type> & operator = ( const Point3D<TypeT> &Src )
		{
			this->x = (Type)Src.x;
			this->y = (Type)Src.y;
			this->z = (Type)Src.z;
			return *this;
		}
	};

	typedef Point3D<Float>		Point3DF;	///< Point3D<Float>�̗���
	typedef Point3D<Sint32>		Point3DI;	///< Point3D<Sint32>�̗���
	typedef Point2D<Float>		Point2DF;	///< Point2D<Float>�̗���
	typedef Point2D<Sint32>		Point2DI;	///< Point2D<Sint32>�̗���
	typedef Rect2D<Float>		Rect2DF;	///< Rect2D<Float>�̗���
	typedef Rect2D<Sint32>		Rect2DI;	///< Rect2D<Sint32>�̗���
}
}

#pragma once


/**
	@file
	@brief �^������
	@author �t���`
*/


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Math
{
	/**
		@brief ���������N���X
		@author �t���`
	*/
	class SELENE_DLL_API CRandom
	{
		enum { N = 624UL };

	private:
		Sint32 m_MersenneTwister[N];		///< ���������p���[�N
		Sint32 m_MersenneTwisterCount;		///< ���������p���[�N

	private:
		/**
			@brief �[����������
			@author �t���`
			@return �����l

			@note
			32Bit�����̋[�������𐶐����܂��B
		*/
		virtual Sint32 GenerateInt32( void );

	public:
		/**
			@brief �R���X�g���N�^
			@author �t���`
		*/
		CRandom();

		/**
			@brief �R���X�g���N�^
			@author �t���`
		*/
		CRandom( Sint32 Param );

		/**
			@brief �����p��ݒ�
			@author �t���`
			@param Param	[in] �V�[�h�l

			@note
			���������̎��ݒ肵�܂��B
		*/
		virtual void Seed( Sint32 Param );

		/**
			@brief 32Bit���������擾
			@author �t���`
			@return �����l

			@note
			32Bit�����̗����l���擾���܂��B
		*/
		virtual Sint32 GetInt32( void );

		/**
			@brief 64Bit���������擾
			@author �t���`
			@return �����l

			@note
			64Bit�����̗����l���擾���܂��B
		*/
		virtual Uint64 GetInt64( void );

		/**
			@brief 32Bit�������������擾
			@author �t���`
			@return �����l

			@note
			32Bit���������̗����l���擾���܂��B
		*/
		virtual Float GetFloat32( void );

		/**
			@brief �w��͈͗����擾
			@author �t���`
			@param Min [in] �ŏ��l
			@param Max [in] �ő�l
			@return �����l

			@note
			�w��͈͓��̐����������擾���܂��B
		*/
		virtual Sint32 GetInt( Sint32 Min, Sint32 Max );

		/**
			@brief �w��͈͗����擾
			@author �t���`
			@param Min [in] �ŏ��l
			@param Max [in] �ő�l
			@return �����l

			@note
			�w��͈͓��̕��������������擾���܂��B
		*/
		virtual Float GetFloat( Float Min, Float Max );
	};
}
}

#pragma once


/**
	@file
	@brief ���l���
	@author �t���`
*/


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Interpolation
{
/**
@brief �����^��
@author �t���`
@param Start	[in] �J�n�l
@param End		[in] �I���l
@param TimeAll	[in] End���B����
@param Time		[in] ���ݎ���
@return Time�ɂ�����l

@note
�����^�����s���Ƃ��̕�Ԓl���擾���܂��B

@code

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  ICore *pCore = NULL;
  Sint32 Time = 0;

  // �V�X�e���̋N��
  if ( !System::Initialize() )
  {
    return 0;
  }

  // ICore�̐���
  pCore = System::CreateCore();
  if ( pCore == NULL ) goto EXIT;               // ICore�ɂ�NullDevice���Ȃ��̂Ŏ��s�����NULL���Ԃ�

  // �R�A�̏�����
  if ( pCore->Initialize( "Sample Program", FRAME_RATE_60 ) )
  {
    // �A�v���P�[�V�����̊J�n
    pCore->Start( 640, 480, true );

    // ���C�����[�v
    while ( pCore->Run() )
    {
      Time++;

      // 60�J�E���g��0����100�܂ňړ�����
      Sint32 Pos = Interpolation::Flat( 0L, 100L, 60L, Time );
      if ( Time > 60L )
      {
      }
    }
  }

EXIT:
  SAFE_RELEASE( pCore );               // �R�A�̉��

  System::Finalize();                  // �V�X�e���̏I���������s��

  return 0;
}
@endcode
*/
	template <typename TypeA, typename TypeB>
	inline TypeA Flat( TypeA Start, TypeA End, TypeB TimeAll, TypeB Time )
	{
		Float fRate = toF(Time) / toF(TimeAll);
		return (TypeA)(toF(Start) + toF(End - Start) * fRate);
	}

/**
@brief �����^��
@author �t���`
@param Start	[in] �J�n�l
@param End		[in] �I���l
@param TimeAll	[in] End���B����
@param Time		[in] ���ݎ���
@return Time�ɂ�����l

@note
�����^�����s���Ƃ��̕�Ԓl���擾���܂��B

@code

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  ICore *pCore = NULL;
  Sint32 Time = 0;

  // �V�X�e���̋N��
  if ( !System::Initialize() )
  {
    return 0;
  }

  // ICore�̐���
  pCore = System::CreateCore();
  if ( pCore == NULL ) goto EXIT;               // ICore�ɂ�NullDevice���Ȃ��̂Ŏ��s�����NULL���Ԃ�

  // �R�A�̏�����
  if ( pCore->Initialize( "Sample Program", FRAME_RATE_60 ) )
  {
    // �A�v���P�[�V�����̊J�n
    pCore->Start( 640, 480, true );

    // ���C�����[�v
    while ( pCore->Run() )
    {
      Time++;

      // 60�J�E���g��0����100�܂ňړ�����
      Sint32 Pos = Interpolation::Add( 0L, 100L, 60L, Time );
      if ( Time > 60L )
      {
      }
    }
  }

EXIT:
  SAFE_RELEASE( pCore );               // �R�A�̉��

  System::Finalize();                  // �V�X�e���̏I���������s��

  return 0;
}
@endcode
*/
	template <typename TypeA, typename TypeB>
	inline TypeA Add( TypeA Start, TypeA End, TypeB TimeAll, TypeB Time )
	{
		Float fRate = toF(Time) / toF(TimeAll);
		fRate *= fRate;
		return (TypeA)(toF(Start) + toF(End - Start) * fRate);
	}

/**
@brief �����^��
@author �t���`
@param Start	[in] �J�n�l
@param End		[in] �I���l
@param TimeAll	[in] End���B����
@param Time		[in] ���ݎ���
@return Time�ɂ�����l

@note
�����^�����s���Ƃ��̕�Ԓl���擾���܂��B

@code

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  ICore *pCore = NULL;
  Sint32 Time = 0;

  // �V�X�e���̋N��
  if ( !System::Initialize() )
  {
    return 0;
  }

  // ICore�̐���
  pCore = System::CreateCore();
  if ( pCore == NULL ) goto EXIT;               // ICore�ɂ�NullDevice���Ȃ��̂Ŏ��s�����NULL���Ԃ�

  // �R�A�̏�����
  if ( pCore->Initialize( "Sample Program", FRAME_RATE_60 ) )
  {
    // �A�v���P�[�V�����̊J�n
    pCore->Start( 640, 480, true );

    // ���C�����[�v
    while ( pCore->Run() )
    {
      Time++;

      // 60�J�E���g��0����100�܂ňړ�����
      Sint32 Pos = Interpolation::Sub( 0L, 100L, 60L, Time );
      if ( Time > 60L )
      {
      }
    }
  }

EXIT:
  SAFE_RELEASE( pCore );               // �R�A�̉��

  System::Finalize();                  // �V�X�e���̏I���������s��

  return 0;
}
@endcode
*/
	template <typename TypeA, typename TypeB>
	inline TypeA Sub( TypeA Start, TypeA End, TypeB TimeAll, TypeB Time )
	{
		Float fRate = toF(TimeAll-Time) / toF(TimeAll);
		fRate *= fRate;
		return (TypeA)(toF(End) + toF(Start - End) * fRate);
	}

/**
@brief �����^��
@author �t���`
@param Start	[in] �J�n�l
@param End		[in] �I���l
@param TimeAll	[in] End���B����
@param Time		[in] ���ݎ���
@return Time�ɂ�����l

@note
�����^�����s���Ƃ��̕�Ԓl���擾���܂��B

@code

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  ICore *pCore = NULL;
  Sint32 Time = 0;

  // �V�X�e���̋N��
  if ( !System::Initialize() )
  {
    return 0;
  }

  // ICore�̐���
  pCore = System::CreateCore();
  if ( pCore == NULL ) goto EXIT;               // ICore�ɂ�NullDevice���Ȃ��̂Ŏ��s�����NULL���Ԃ�

  // �R�A�̏�����
  if ( pCore->Initialize( "Sample Program", FRAME_RATE_60 ) )
  {
    // �A�v���P�[�V�����̊J�n
    pCore->Start( 640, 480, true );

    // ���C�����[�v
    while ( pCore->Run() )
    {
      Time++;

      // 60�J�E���g��0����100�܂ňړ�����
      Sint32 Pos = Interpolation::Add2( 0L, 100L, 60L, Time );
      if ( Time > 60L )
      {
      }
    }
  }

EXIT:
  SAFE_RELEASE( pCore );               // �R�A�̉��

  System::Finalize();                  // �V�X�e���̏I���������s��

  return 0;
}
@endcode
*/
	template <typename TypeA, typename TypeB>
	inline TypeA Add2( TypeA Start, TypeA End, TypeB TimeAll, TypeB Time )
	{
		Float fRate = toF(Time) / toF(TimeAll);
		fRate *= fRate;
		fRate *= fRate;
		return (TypeA)(toF(Start) + toF(End - Start) * fRate);
	}

/**
@brief �����^��
@author �t���`
@param Start	[in] �J�n�l
@param End		[in] �I���l
@param TimeAll	[in] End���B����
@param Time		[in] ���ݎ���
@return Time�ɂ�����l

@note
�����^�����s���Ƃ��̕�Ԓl���擾���܂��B

@code

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  ICore *pCore = NULL;
  Sint32 Time = 0;

  // �V�X�e���̋N��
  if ( !System::Initialize() )
  {
    return 0;
  }

  // ICore�̐���
  pCore = System::CreateCore();
  if ( pCore == NULL ) goto EXIT;               // ICore�ɂ�NullDevice���Ȃ��̂Ŏ��s�����NULL���Ԃ�

  // �R�A�̏�����
  if ( pCore->Initialize( "Sample Program", FRAME_RATE_60 ) )
  {
    // �A�v���P�[�V�����̊J�n
    pCore->Start( 640, 480, true );

    // ���C�����[�v
    while ( pCore->Run() )
    {
      Time++;

      // 60�J�E���g��0����100�܂ňړ�����
      Sint32 Pos = Interpolation::Sub2( 0L, 100L, 60L, Time );
      if ( Time > 60L )
      {
      }
    }
  }

EXIT:
  SAFE_RELEASE( pCore );               // �R�A�̉��

  System::Finalize();                  // �V�X�e���̏I���������s��

  return 0;
}
@endcode
*/
	template <typename TypeA, typename TypeB>
	inline TypeA Sub2( TypeA Start, TypeA End, TypeB TimeAll, TypeB Time )
	{
		Float fRate = toF(TimeAll-Time) / toF(TimeAll);
		fRate *= fRate;
		fRate *= fRate;
		return (TypeA)(toF(End) + toF(Start - End) * fRate);
	}

/**
@brief �����^��
@author �t���`
@param Start	[in] �J�n�l
@param End		[in] �I���l
@param TimeAll	[in] End���B����
@param Time		[in] ���ݎ���
@return Time�ɂ�����l

@note
�����^�����s���Ƃ��̕�Ԓl���擾���܂��B

@code

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  ICore *pCore = NULL;
  Sint32 Time = 0;

  // �V�X�e���̋N��
  if ( !System::Initialize() )
  {
    return 0;
  }

  // ICore�̐���
  pCore = System::CreateCore();
  if ( pCore == NULL ) goto EXIT;               // ICore�ɂ�NullDevice���Ȃ��̂Ŏ��s�����NULL���Ԃ�

  // �R�A�̏�����
  if ( pCore->Initialize( "Sample Program", FRAME_RATE_60 ) )
  {
    // �A�v���P�[�V�����̊J�n
    pCore->Start( 640, 480, true );

    // ���C�����[�v
    while ( pCore->Run() )
    {
      Time++;

      // 60�J�E���g��0����100�܂ňړ�����
      Sint32 Pos = Interpolation::Add4( 0L, 100L, 60L, Time );
      if ( Time > 60L )
      {
      }
    }
  }

EXIT:
  SAFE_RELEASE( pCore );               // �R�A�̉��

  System::Finalize();                  // �V�X�e���̏I���������s��

  return 0;
}
@endcode
*/
	template <typename TypeA, typename TypeB>
	inline TypeA Add4( TypeA Start, TypeA End, TypeB TimeAll, TypeB Time )
	{
		Float fRate = toF(Time) / toF(TimeAll);
		fRate *= fRate;
		fRate *= fRate;
		fRate *= fRate;
		return (TypeA)(toF(Start) + toF(End - Start) * fRate);
	}

/**
@brief �����^��
@author �t���`
@param Start	[in] �J�n�l
@param End		[in] �I���l
@param TimeAll	[in] End���B����
@param Time		[in] ���ݎ���
@return Time�ɂ�����l

@note
�����^�����s���Ƃ��̕�Ԓl���擾���܂��B

@code

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  ICore *pCore = NULL;
  Sint32 Time = 0;

  // �V�X�e���̋N��
  if ( !System::Initialize() )
  {
    return 0;
  }

  // ICore�̐���
  pCore = System::CreateCore();
  if ( pCore == NULL ) goto EXIT;               // ICore�ɂ�NullDevice���Ȃ��̂Ŏ��s�����NULL���Ԃ�

  // �R�A�̏�����
  if ( pCore->Initialize( "Sample Program", FRAME_RATE_60 ) )
  {
    // �A�v���P�[�V�����̊J�n
    pCore->Start( 640, 480, true );

    // ���C�����[�v
    while ( pCore->Run() )
    {
      Time++;

      // 60�J�E���g��0����100�܂ňړ�����
      Sint32 Pos = Interpolation::Sub4( 0L, 100L, 60L, Time );
      if ( Time > 60L )
      {
      }
    }
  }

EXIT:
  SAFE_RELEASE( pCore );               // �R�A�̉��

  System::Finalize();                  // �V�X�e���̏I���������s��

  return 0;
}
@endcode
*/
	template <typename TypeA, typename TypeB>
	inline TypeA Sub4( TypeA Start, TypeA End, TypeB TimeAll, TypeB Time )
	{
		Float fRate = toF(TimeAll-Time) / toF(TimeAll);
		fRate *= fRate;
		fRate *= fRate;
		fRate *= fRate;
		return (TypeA)(toF(End) + toF(Start - End) * fRate);
	}

/**
@brief �����������^��
@author �t���`
@param Start	[in] �J�n�l
@param End		[in] �I���l
@param TimeAll	[in] End���B����
@param Time		[in] ���ݎ���
@return Time�ɂ�����l

@note
�����������^�����s���Ƃ��̕�Ԓl���擾���܂��B

@code

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  ICore *pCore = NULL;
  Sint32 Time = 0;

  // �V�X�e���̋N��
  if ( !System::Initialize() )
  {
    return 0;
  }

  // ICore�̐���
  pCore = System::CreateCore();
  if ( pCore == NULL ) goto EXIT;               // ICore�ɂ�NullDevice���Ȃ��̂Ŏ��s�����NULL���Ԃ�

  // �R�A�̏�����
  if ( pCore->Initialize( "Sample Program", FRAME_RATE_60 ) )
  {
    // �A�v���P�[�V�����̊J�n
    pCore->Start( 640, 480, true );

    // ���C�����[�v
    while ( pCore->Run() )
    {
      Time++;

      // 60�J�E���g��0����100�܂ňړ�����
      Sint32 Pos = Interpolation::AddSub( 0L, 100L, 60L, Time );
      if ( Time > 60L )
      {
      }
    }
  }

EXIT:
  SAFE_RELEASE( pCore );               // �R�A�̉��

  System::Finalize();                  // �V�X�e���̏I���������s��

  return 0;
}
@endcode
*/
	template <typename TypeA, typename TypeB>
	inline TypeA AddSub( TypeA Start, TypeA End, TypeB TimeAll, TypeB Time )
	{
		TypeA Middle = (End + Start) / (TypeA)2;
		TypeB MiddleTime = TimeAll / (TypeB)2;

		if ( Time < MiddleTime )
		{
			return Add( Start, Middle, MiddleTime, Time );
		}
		else
		{
			return Sub( Middle, End, TimeAll-MiddleTime, Time-MiddleTime );
		}
	}

/**
@brief �����������^��
@author �t���`
@param Start	[in] �J�n�l
@param End		[in] �I���l
@param TimeAll	[in] End���B����
@param Time		[in] ���ݎ���
@return Time�ɂ�����l

@note
�����������^�����s���Ƃ��̕�Ԓl���擾���܂��B

@code

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  ICore *pCore = NULL;
  Sint32 Time = 0;

  // �V�X�e���̋N��
  if ( !System::Initialize() )
  {
    return 0;
  }

  // ICore�̐���
  pCore = System::CreateCore();
  if ( pCore == NULL ) goto EXIT;               // ICore�ɂ�NullDevice���Ȃ��̂Ŏ��s�����NULL���Ԃ�

  // �R�A�̏�����
  if ( pCore->Initialize( "Sample Program", FRAME_RATE_60 ) )
  {
    // �A�v���P�[�V�����̊J�n
    pCore->Start( 640, 480, true );

    // ���C�����[�v
    while ( pCore->Run() )
    {
      Time++;

      // 60�J�E���g��0����100�܂ňړ�����
      Sint32 Pos = Interpolation::SubAdd( 0L, 100L, 60L, Time );
      if ( Time > 60L )
      {
      }
    }
  }

EXIT:
  SAFE_RELEASE( pCore );               // �R�A�̉��

  System::Finalize();                  // �V�X�e���̏I���������s��

  return 0;
}
@endcode
*/
	template <typename TypeA, typename TypeB>
	inline TypeA SubAdd( TypeA Start, TypeA End, TypeB TimeAll, TypeB Time )
	{
		TypeA Middle = (End + Start) / (TypeA)2;
		TypeB MiddleTime = TimeAll / (TypeB)2;

		if ( Time < MiddleTime )
		{
			return Sub( Start, Middle, MiddleTime, Time );
		}
		else
		{
			return Add( Middle, End, TimeAll-MiddleTime, Time-MiddleTime );
		}
	}

/**
@brief �����������^��
@author �t���`
@param Start	[in] �J�n�l
@param End		[in] �I���l
@param TimeAll	[in] End���B����
@param Time		[in] ���ݎ���
@return Time�ɂ�����l

@note
�����������^�����s���Ƃ��̕�Ԓl���擾���܂��B

@code

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  ICore *pCore = NULL;
  Sint32 Time = 0;

  // �V�X�e���̋N��
  if ( !System::Initialize() )
  {
    return 0;
  }

  // ICore�̐���
  pCore = System::CreateCore();
  if ( pCore == NULL ) goto EXIT;               // ICore�ɂ�NullDevice���Ȃ��̂Ŏ��s�����NULL���Ԃ�

  // �R�A�̏�����
  if ( pCore->Initialize( "Sample Program", FRAME_RATE_60 ) )
  {
    // �A�v���P�[�V�����̊J�n
    pCore->Start( 640, 480, true );

    // ���C�����[�v
    while ( pCore->Run() )
    {
      Time++;

      // 60�J�E���g��0����100�܂ňړ�����
      Sint32 Pos = Interpolation::AddSub2( 0L, 100L, 60L, Time );
      if ( Time > 60L )
      {
      }
    }
  }

EXIT:
  SAFE_RELEASE( pCore );               // �R�A�̉��

  System::Finalize();                  // �V�X�e���̏I���������s��

  return 0;
}
@endcode
*/
	template <typename TypeA, typename TypeB>
	inline TypeA AddSub2( TypeA Start, TypeA End, TypeB TimeAll, TypeB Time )
	{
		TypeA Middle = (End + Start) / (TypeA)2;
		TypeB MiddleTime = TimeAll / (TypeB)2;

		if ( Time < MiddleTime )
		{
			return Add2( Start, Middle, MiddleTime, Time );
		}
		else
		{
			return Sub2( Middle, End, TimeAll-MiddleTime, Time-MiddleTime );
		}
	}

/**
@brief �����������^��
@author �t���`
@param Start	[in] �J�n�l
@param End		[in] �I���l
@param TimeAll	[in] End���B����
@param Time		[in] ���ݎ���
@return Time�ɂ�����l

@note
�����������^�����s���Ƃ��̕�Ԓl���擾���܂��B

@code

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  ICore *pCore = NULL;
  Sint32 Time = 0;

  // �V�X�e���̋N��
  if ( !System::Initialize() )
  {
    return 0;
  }

  // ICore�̐���
  pCore = System::CreateCore();
  if ( pCore == NULL ) goto EXIT;               // ICore�ɂ�NullDevice���Ȃ��̂Ŏ��s�����NULL���Ԃ�

  // �R�A�̏�����
  if ( pCore->Initialize( "Sample Program", FRAME_RATE_60 ) )
  {
    // �A�v���P�[�V�����̊J�n
    pCore->Start( 640, 480, true );

    // ���C�����[�v
    while ( pCore->Run() )
    {
      Time++;

      // 60�J�E���g��0����100�܂ňړ�����
      Sint32 Pos = Interpolation::SubAdd2( 0L, 100L, 60L, Time );
      if ( Time > 60L )
      {
      }
    }
  }

EXIT:
  SAFE_RELEASE( pCore );               // �R�A�̉��

  System::Finalize();                  // �V�X�e���̏I���������s��

  return 0;
}
@endcode
*/
	template <typename TypeA, typename TypeB>
	inline TypeA SubAdd2( TypeA Start, TypeA End, TypeB TimeAll, TypeB Time )
	{
		TypeA Middle = (End + Start) / (TypeA)2;
		TypeB MiddleTime = TimeAll / (TypeB)2;

		if ( Time < MiddleTime )
		{
			return Sub2( Start, Middle, MiddleTime, Time );
		}
		else
		{
			return Add2( Middle, End, TimeAll-MiddleTime, Time-MiddleTime );
		}
	}

/**
@brief �����������^��
@author �t���`
@param Start	[in] �J�n�l
@param End		[in] �I���l
@param TimeAll	[in] End���B����
@param Time		[in] ���ݎ���
@return Time�ɂ�����l

@note
�����������^�����s���Ƃ��̕�Ԓl���擾���܂��B

@code

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  ICore *pCore = NULL;
  Sint32 Time = 0;

  // �V�X�e���̋N��
  if ( !System::Initialize() )
  {
    return 0;
  }

  // ICore�̐���
  pCore = System::CreateCore();
  if ( pCore == NULL ) goto EXIT;               // ICore�ɂ�NullDevice���Ȃ��̂Ŏ��s�����NULL���Ԃ�

  // �R�A�̏�����
  if ( pCore->Initialize( "Sample Program", FRAME_RATE_60 ) )
  {
    // �A�v���P�[�V�����̊J�n
    pCore->Start( 640, 480, true );

    // ���C�����[�v
    while ( pCore->Run() )
    {
      Time++;

      // 60�J�E���g��0����100�܂ňړ�����
      Sint32 Pos = Interpolation::AddSub4( 0L, 100L, 60L, Time );
      if ( Time > 60L )
      {
      }
    }
  }

EXIT:
  SAFE_RELEASE( pCore );               // �R�A�̉��

  System::Finalize();                  // �V�X�e���̏I���������s��

  return 0;
}
@endcode
*/
	template <typename TypeA, typename TypeB>
	inline TypeA AddSub4( TypeA Start, TypeA End, TypeB TimeAll, TypeB Time )
	{
		TypeA Middle = (End + Start) / (TypeA)2;
		TypeB MiddleTime = TimeAll / (TypeB)2;

		if ( Time < MiddleTime )
		{
			return Add4( Start, Middle, MiddleTime, Time );
		}
		else
		{
			return Sub4( Middle, End, TimeAll-MiddleTime, Time-MiddleTime );
		}
	}

/**
@brief �����������^��
@author �t���`
@param Start	[in] �J�n�l
@param End		[in] �I���l
@param TimeAll	[in] End���B����
@param Time		[in] ���ݎ���
@return Time�ɂ�����l

@note
�����������^�����s���Ƃ��̕�Ԓl���擾���܂��B

@code

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  ICore *pCore = NULL;
  Sint32 Time = 0;

  // �V�X�e���̋N��
  if ( !System::Initialize() )
  {
    return 0;
  }

  // ICore�̐���
  pCore = System::CreateCore();
  if ( pCore == NULL ) goto EXIT;               // ICore�ɂ�NullDevice���Ȃ��̂Ŏ��s�����NULL���Ԃ�

  // �R�A�̏�����
  if ( pCore->Initialize( "Sample Program", FRAME_RATE_60 ) )
  {
    // �A�v���P�[�V�����̊J�n
    pCore->Start( 640, 480, true );

    // ���C�����[�v
    while ( pCore->Run() )
    {
      Time++;

      // 60�J�E���g��0����100�܂ňړ�����
      Sint32 Pos = Interpolation::SubAdd4( 0L, 100L, 60L, Time );
      if ( Time > 60L )
      {
      }
    }
  }

EXIT:
  SAFE_RELEASE( pCore );               // �R�A�̉��

  System::Finalize();                  // �V�X�e���̏I���������s��

  return 0;
}
@endcode
*/
	template <typename TypeA, typename TypeB>
	inline TypeA SubAdd4( TypeA Start, TypeA End, TypeB TimeAll, TypeB Time )
	{
		TypeA Middle = (End + Start) / (TypeA)2;
		TypeB MiddleTime = TimeAll / (TypeB)2;

		if ( Time < MiddleTime )
		{
			return Sub4( Start, Middle, MiddleTime, Time );
		}
		else
		{
			return Add4( Middle, End, TimeAll-MiddleTime, Time-MiddleTime );
		}
	}

/**
@brief sin�^��
@author �t���`
@param Start	[in] �J�n�l
@param End		[in] �I���l
@param TimeAll	[in] End���B����
@param Time		[in] ���ݎ���
@return Time�ɂ�����l

@note
sin�g�ŉ^�����s���Ƃ��̕�Ԓl���擾���܂��B

@code

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  ICore *pCore = NULL;
  Sint32 Time = 0;

  // �V�X�e���̋N��
  if ( !System::Initialize() )
  {
    return 0;
  }

  // ICore�̐���
  pCore = System::CreateCore();
  if ( pCore == NULL ) goto EXIT;               // ICore�ɂ�NullDevice���Ȃ��̂Ŏ��s�����NULL���Ԃ�

  // �R�A�̏�����
  if ( pCore->Initialize( "Sample Program", FRAME_RATE_60 ) )
  {
    // �A�v���P�[�V�����̊J�n
    pCore->Start( 640, 480, true );

    // ���C�����[�v
    while ( pCore->Run() )
    {
      Time++;

      // 60�J�E���g��0����100�܂ňړ�����
      Sint32 Pos = Interpolation::Sin( 0L, 100L, 60L, Time );
      if ( Time > 60L )
      {
      }
    }
  }

EXIT:
  SAFE_RELEASE( pCore );               // �R�A�̉��

  System::Finalize();                  // �V�X�e���̏I���������s��

  return 0;
}
@endcode
*/
	template <typename TypeA, typename TypeB>
	inline TypeA Sin( TypeA Start, TypeA End, TypeB TimeAll, TypeB Time )
	{
		Sint32 Angle = (Sint32)(DEG_TO_ANGLE(180) * Time / TimeAll);
		Float fRate = Math::Sin( Angle );
		return (TypeA)(toF(Start) + toF(End - Start) * fRate);
	}

/**
@brief �l���B�����
@author �t���`
@param Start	[in] �J�n�l
@param Center	[in] ���Ԓl
@param End		[in] �I���l
@param fTime	[in] ���ݎ��ԁi0.0�`1.0�j
@return Time�ɂ�����l

@note
�l���B����Ԃ��s���Ƃ��̕�Ԓl���擾���܂��B

@code

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  ICore *pCore = NULL;
  Sint32 Time = 0;

  // �V�X�e���̋N��
  if ( !System::Initialize() )
  {
    return 0;
  }

  // ICore�̐���
  pCore = System::CreateCore();
  if ( pCore == NULL ) goto EXIT;               // ICore�ɂ�NullDevice���Ȃ��̂Ŏ��s�����NULL���Ԃ�

  // �R�A�̏�����
  if ( pCore->Initialize( "Sample Program", FRAME_RATE_60 ) )
  {
    // �A�v���P�[�V�����̊J�n
    pCore->Start( 640, 480, true );

    // ���C�����[�v
    while ( pCore->Run() )
    {
      Time++;

      // 60�J�E���g��0����100�܂Œ��Ԃ�30���o�R���Ĉړ�����
      Sint32 Pos = Interpolation::Neville( 0.0f, 30.0f, 100.0f, toF(Time) / 60.0f );
      if ( Time > 60L )
      {
      }
    }
  }

EXIT:
  SAFE_RELEASE( pCore );               // �R�A�̉��

  System::Finalize();                  // �V�X�e���̏I���������s��

  return 0;
}
@endcode
*/
	inline Float Neville( Float Start, Float Center, Float End, Float fTime )
	{
		fTime *= 2.0f;
		Start = Center + (Center - Start) * (fTime - 1.0f);
		Center = End + (End - Center) * (fTime - 2.0f);
		return Center + (Center - Start) * (fTime - 2.0f) * 0.5f;
	}
}
}

#pragma once


/**
	@file
	@brief �A�j���[�V��������
	@author �t���`
*/


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
	/**
		@brief �A�j���[�V�����^�C�v��`
		@author �t���`
	*/
	enum eAnimationType
	{
		ANIMATION_TYPE_STEP,					///< �X�e�b�v���
		ANIMATION_TYPE_LINEAR,					///< ���`���
		ANIMATION_TYPE_TCB,						///< �s�b�a�X�v���C�����
	};

	/**
		@brief �L�[�t���[���f�[�^
		@author �t���`
	*/
	struct SKeyFrame
	{
		Bool IsIn;								///< �X�v���C������IN�W����萔�ɂ��邩�ǂ���
		Bool IsOut;								///< �X�v���C������OUT�W����萔�ɂ��邩�ǂ���
		Float fTime;							///< �L�[����
		Float fParam;							///< �L�[�l
		Float fIn;								///< IN�W���̒萔
		Float fOut;								///< OUT�W���̒萔

		SKeyFrame *pPrev;						///< �O���L�[�t���[���f�[�^�|�C���^
		SKeyFrame *pNext;						///< ����L�[�t���[���f�[�^�|�C���^
	};

namespace Math
{
	/**
		@brief �A�j���[�V�����N���X
		@author �t���`
	*/
	class SELENE_DLL_API Animation
	{
	private:
		Float m_fTimeFirst;						///< �J�n����
		Float m_fTimeLast;						///< �I������
		SKeyFrame *m_pKeys;						///< �L�[�t���[���f�[�^�|�C���^
		Sint32 m_KeyMax;						///< �L�[�t���[����

	private:
/**
@brief �w�莞�Ԃ���ł��߂��L�[�f�[�^���擾���܂�
@author �t���`
@param pKeys		[in] �L�[�t���[���f�[�^
@param fTime		[in] ��������
@param KeyMax		[in] �L�[�ő吔
@return �L�[�t���[���f�[�^�|�C���^

@note
�w�莞�Ԃ�������Ƃ��߂��L�[�����A<BR>
�o�C�i���T�[�`�Ō������܂��B
*/
		SKeyFrame *GetKeyData( SKeyFrame *pKeys, Float fTime, Sint32 KeyMax );

/**
@brief �G���~�[�g��Ԋ֐����������܂�
@author �t���`
@param fTime	[in] ����
@param pH1		[out] �p�����[�^�[�i�[��P
@param pH2		[out] �p�����[�^�[�i�[��Q
@param pH3		[out] �p�����[�^�[�i�[��R
@param pH4		[out] �p�����[�^�[�i�[��S

@note
�G���~�[�g��Ԋ֐����g���ė^����ꂽ�p�����[�^�[���猋�ʂ��Z�o���܂��B
*/
		void Hermite( Float fTime, Float *pH1, Float *pH2, Float *pH3, Float *pH4 );

/**
@brief �O���̃L�[�̏o�͐�̃p�����[�^�����߂܂�
@author �t���`
@param pKey0	[in] �O���L�[�f�[�^
@param pKey1	[in] ����L�[�f�[�^
@return �Z�o���ꂽ�p�����[�^�[

@note
�w�莞�Ԃɑ΂��Ă̒��O�̃L�[�̋������v�Z���܂��B
*/
		Float InComing( SKeyFrame *pKey0, SKeyFrame *pKey1 );

/**
@brief ����̃L�[�̏o�͐�̃p�����[�^�����߂܂�
@author �t���`
@param pKey0	[in] �O���L�[�f�[�^
@param pKey1	[in] ����L�[�f�[�^
@return �Z�o���ꂽ�p�����[�^�[

@note
�w�莞�Ԃɑ΂��Ă̒���̃L�[�̋������v�Z���܂��B
*/
		Float OutGoing( SKeyFrame *pKey0, SKeyFrame *pKey1 );

	public:
/**
@brief �R���X�g���N�^
@author �t���`
@param KeyMax		[in] �L�[�ő吔
*/
		Animation( Sint32 KeyMax );

/**
@brief �f�X�g���N�^
@author �t���`
*/
		virtual ~Animation();

/**
@brief �L�[�t���[���f�[�^�ɃL�[��ݒ肵�܂�
@author �t���`
@param KeyNo		[in] �ݒ��L�[�ԍ�
@param fTime		[in] �ݒ莞��
@param fParam		[in] �ݒ�p�����[�^
@param IsIn			[in] ���̓p�����[�^�[�w��L��
@param IsOut		[in] �o�̓p�����[�^�[�w��L��
@param fIn			[in] ���̓p�����[�^�[
@param fOut			[in] �o�̓p�����[�^�[
@return ��������true

@note
�w��̃L�[�ɑ΂��āA��ԗp�̃p�����[�^�[��ݒ肵�܂��B

@code

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  ICore        *pCore        = NULL;

  Math::Animation Anim( 3 );	// �L�[�R�ō쐬
  Anim.SetKey( 0,  0.0f,   0.0f );	// �L�[�P
  Anim.SetKey( 1,  5.0f,  40.0f );	// �L�[�Q
  Anim.SetKey( 2, 10.0f, 100.0f );	// �L�[�R

  Float fTime = 0.0f;

  // �V�X�e���̋N��
  if ( !System::Initialize() )
  {
    return 0;
  }

  // ICore�̐���
  pCore = System::CreateCore();
  if ( pCore == NULL ) goto EXIT;               // ICore�ɂ�NullDevice���Ȃ��̂Ŏ��s�����NULL���Ԃ�

  // �R�A�̏�����
  if ( pCore->Initialize( "Sample Program", FRAME_RATE_60 ) )
  {
    // �A�v���P�[�V�����̊J�n
    pCore->Start( 640, 480, true );

    // ���C�����[�v
    while ( pCore->Run() )
    {
      fTime += 0.1f;

      // ����fTime�ɂ�����l���擾
      // ��ԕ��@��TCB�X�v���C��
      Float fNow = Anim.GetParameter( fTime, ANIMATION_TYPE_TCB, 0.0f );
    }
  }

EXIT:
  SAFE_RELEASE( pCore );               // �R�A�̉��

  System::Finalize();                  // �V�X�e���̏I���������s��

  return 0;
}
@endcode
*/
		virtual Bool SetKey( Sint32 KeyNo, Float fTime, Float fParam, Bool IsIn = false, Bool IsOut = false, Float fIn = 0.0f, Float fOut = 0.0f );

/**
@brief �w��^�C�v�̃A�j���[�V�����Ŏw�莞�Ԃɂ�����l���擾���܂�
@author �t���`
@param fTime		[in] ����
@param Type			[in] ��ԃ^�C�v
@param fDefault		[in] �f�t�H���g�l
@return		��Ԍ��ʒl

@note
�w��̎��Ԃɑ΂��āA��Ԃ��ꂽ�p�����[�^�[���擾���܂��B

@code

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  ICore        *pCore        = NULL;

  Math::Animation Anim( 3 );	// �L�[�R�ō쐬
  Anim.SetKey( 0,  0.0f,   0.0f );	// �L�[�P
  Anim.SetKey( 1,  5.0f,  40.0f );	// �L�[�Q
  Anim.SetKey( 2, 10.0f, 100.0f );	// �L�[�R

  Float fTime = 0.0f;

  // �V�X�e���̋N��
  if ( !System::Initialize() )
  {
    return 0;
  }

  // ICore�̐���
  pCore = System::CreateCore();
  if ( pCore == NULL ) goto EXIT;               // ICore�ɂ�NullDevice���Ȃ��̂Ŏ��s�����NULL���Ԃ�

  // �R�A�̏�����
  if ( pCore->Initialize( "Sample Program", FRAME_RATE_60 ) )
  {
    // �A�v���P�[�V�����̊J�n
    pCore->Start( 640, 480, true );

    // ���C�����[�v
    while ( pCore->Run() )
    {
      fTime += 0.1f;

      // ����fTime�ɂ�����l���擾
      // ��ԕ��@��TCB�X�v���C��
      Float fNow = Anim.GetParameter( fTime, ANIMATION_TYPE_TCB, 0.0f );
    }
  }

EXIT:
  SAFE_RELEASE( pCore );               // �R�A�̉��

  System::Finalize();                  // �V�X�e���̏I���������s��

  return 0;
}
@endcode
*/
		virtual Float GetParameter( Float fTime, eAnimationType Type, Float fDefault );
	};
}
}

#pragma once


/**
	@file
	@brief �R��������
	@author �t���`
*/


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Collision
{
	/**
		@brief �R�����̕���
		@author �t���`
	*/
	class SELENE_DLL_API CPlane
	{
	public:
		Math::Vector3D n;		///< ��ʕ��ʕ������ɂ�����N���b�v�ʂ� a b c �W��
		Float d;				///< ��ʕ��ʕ������ɂ�����N���b�v�ʂ� d �W��

	public:
		/**
			@brief �R���X�g���N�^
			@author �t���`
		*/
		CPlane( void );

		/**
			@brief �R���X�g���N�^
			@author �t���`

			@param a	[in] ��ʕ��ʕ������ɂ�����N���b�v�ʂ� a �W��
			@param b	[in] ��ʕ��ʕ������ɂ�����N���b�v�ʂ� b �W��
			@param c	[in] ��ʕ��ʕ������ɂ�����N���b�v�ʂ� c �W��
			@param d	[in] ��ʕ��ʕ������ɂ�����N���b�v�ʂ� d �W��
		*/
		CPlane( Float a, Float b, Float c, Float d );

		/**
			@brief �@���f�[�^���琶��
			@author �t���`

			@param Pt		[in] ���ʏ��1�_
			@param vNormal	[in] ���ʂ̖@��
		*/
		void FromNormal( const Math::Vector3D &Pt, const Math::Vector3D &vNormal );

		/**
			@brief ���ʏ�̂R�_���琶��
			@author �t���`

			@param vPt0		[in] ���ʏ��1�_
			@param vPt1		[in] ���ʏ��1�_
			@param vPt2		[in] ���ʏ��1�_
		*/
		void FromPoint( const Math::Vector3D &vPt0, const Math::Vector3D &vPt1, const Math::Vector3D &vPt2 );

		/**
			@brief ����
			@author �t���`

			@param Pt	[in] �C�ӂ̓_

			@note
			���ʂƔC�ӂ̓_�̓��ς��Ƃ�܂��B
		*/
		Float Dot( const Math::Vector3D &Pt ) const;
	};
}
}

#pragma once


/**
	@file
	@brief �R���W�����p��
	@author �t���`
*/


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Collision
{
	/**
		@brief �R������̋�
		@author �t���`
	*/
	class SELENE_DLL_API CSphere
	{
	public:
		Math::Vector3D vCenter;				///< ���̒��S
		Float fRadius;						///< ���̔��a

	public:
		/**
			@brief �R���X�g���N�^
			@author �t���`
		*/
		CSphere( void );

		/**
			@brief �R���X�g���N�^
			@author �t���`

			@param x		[in] �w���W
			@param y		[in] �x���W
			@param z		[in] �y���W
			@param r		[in] ���a
		*/
		CSphere( Float x, Float y, Float z, Float r );

		/**
			@brief �R���X�g���N�^
			@author �t���`

			@param c		[in] ���S���W
			@param r		[in] ���a
		*/
		CSphere( const Math::Vector3D &c, Float r );
	};
}
}

#pragma once


/**
	@file
	@brief �R�����{�b�N�X
	@author �t���`
*/


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Collision
{
	/**
		@brief �R������̔�
		@author �t���`
	*/
	class SELENE_DLL_API CBox
	{
	public:
		Math::Vector3D Points[8];		///< �����\������8���_
		CPlane Planes[6];				///< �����\������6����
		Math::Vector3D vMin;			///< AABB�̍ŏ��_
		Math::Vector3D vMax;			///< AABB�̍ő�_

	private:
		/**
			@brief �|�C���g�f�[�^�����Ƀ{�b�N�X�̊e�ʁA���E���̍Čv�Z
			@author �t���`
		*/
		void UpdateBox( void );

	public:
		/**
			@brief �R���X�g���N�^
			@author �t���`
		*/
		CBox( void );

		/**
			@brief �o�E���f�B���O�{�b�N�X���\������W���_���w��
			@author �t���`
			@param vPoints	[in] �|�C���g

			@note
			�ȉ��̏��Ԃɕ���ł���K�v������܂��B<BR>
			(min.x,min.y,min.z)-(min.x,max.y,min.z)-(min.x,max.y,max.z)-(min.x,min.y,max.z)-<BR>
			(max.x,min.y,min.z)-(max.x,max.y,min.z)-(max.x,max.y,max.z)-(max.x,min.y,max.z)
		*/
		void SetPoints( const Math::Vector3D vPoints[] );

		/**
			@brief �R���w��Ńo�E���f�B���O�{�b�N�X���\������W���_���X�V
			@author �t���`
			@param vCenter	[in] ���S
			@param vAxis	[in] ��(X,Y,Z)
			@param fLength	[in] ���̒���(X,Y,Z)
		*/
		void UpdatePoints( const Math::Vector3D &vCenter, const Math::Vector3D vAxis[], const Float fLength[] );

		/**
			@brief �o�E���f�B���O�{�b�N�X���w�肵���s��ŕϊ����܂��B
			@author �t���`
			@param Matrix	[in] �|�C���g��ϊ����邽�߂̍s��
		*/
		void Transform( const Math::Matrix &Matrix );

		/**
			@brief �o�E���f�B���O�{�b�N�X���w�肵���s��ŕϊ����܂��B
			@author �t���`
			@param vPoints	[in] �|�C���g�̔z��
			@param Matrix	[in] �|�C���g��ϊ����邽�߂̍s��
		*/
		void Transform( const Math::Vector3D vPoints[], const Math::Matrix &Matrix );

		/**
			@brief �o�E���f�B���O�{�b�N�X���w�肵���s��œ����ϊ����܂��B
			@author �t���`
			@param Matrix	[in] �|�C���g�𓧎��ϊ����邽�߂̍s��
		*/
		void TransformProjection( const Math::Matrix &Matrix );

		/**
			@brief �o�E���f�B���O�{�b�N�X���w�肵���s��œ����ϊ����܂��B
			@author �t���`
			@param vPoints	[in] �|�C���g�̔z��
			@param Matrix	[in] �|�C���g�𓧎��ϊ����邽�߂̍s��
		*/
		void TransformProjection( const Math::Vector3D vPoints[], const Math::Matrix &Matrix );

		/**
			@brief �o�E���f�B���O�{�b�N�X�𐶐�
			@author �t���`
			@param MinPt	[in] AABB�̍ŏ��l
			@param MaxPt	[in] AABB�̍ő�l
			@param Matrix	[in] �|�C���g��ϊ����邽�߂̍s��
		*/
		void CreateBox( const Math::Vector3D &MinPt, const Math::Vector3D &MaxPt, const Math::Matrix &Matrix );

		/**
			@brief �o�E���f�B���O�{�b�N�X�𐶐�
			@author �t���`
			@param MinPt	[in] AABB�̍ŏ��l
			@param MaxPt	[in] AABB�̍ő�l
			@param Matrix	[in] �|�C���g�𓧎��ϊ����邽�߂̍s��
		*/
		void CreateBoxProjection( const Math::Vector3D &MinPt, const Math::Vector3D &MaxPt, const Math::Matrix &Matrix );
	};
}
}

#pragma once


/**
	@file
	@brief �Q��������
	@author �t���`
*/


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Collision
{
	/**
		@brief �Q�����̐���
		@author �t���`
	*/
	class SELENE_DLL_API CLine2D
	{
	public:
		Math::Vector2D vStart;				///< �����n�_�ʒu
		Math::Vector2D vEnd;				///< �����I�_�ʒu

	public:
		/**
			@brief �R���X�g���N�^
			@author �t���`
		*/
		CLine2D( void );

		/**
			@brief �R���X�g���N�^
			@author �t���`

			@param x0		[in] �w���W
			@param y0		[in] �x���W
			@param x1		[in] �w���W
			@param y1		[in] �x���W
		*/
		CLine2D( Float x0, Float y0, Float x1, Float y1 );

		/**
			@brief �R���X�g���N�^
			@author �t���`

			@param pt0		[in] �����̒��_�P
			@param pt1		[in] �����̒��_�Q
		*/
		CLine2D( Math::Vector2D &pt0, Math::Vector2D &pt1 );
	};
}
}


#pragma once


/**
	@file
	@brief �R��������
	@author �t���`
*/


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Collision
{
	/**
		@brief �R�����̐���
		@author �t���`
	*/
	class SELENE_DLL_API CLine3D
	{
	public:
		Math::Vector3D vStart;				///< �����n�_�ʒu
		Math::Vector3D vEnd;				///< �����I�_�ʒu

	public:
		/**
			@brief �R���X�g���N�^
			@author �t���`
		*/
		CLine3D( void );

		/**
			@brief �R���X�g���N�^
			@author �t���`

			@param x0		[in] �w���W
			@param y0		[in] �x���W
			@param z0		[in] �y���W
			@param x1		[in] �w���W
			@param y1		[in] �x���W
			@param z1		[in] �y���W
		*/
		CLine3D( Float x0, Float y0, Float z0, Float x1, Float y1, Float z1 );

		/**
			@brief �R���X�g���N�^
			@author �t���`

			@param pt0	[in] �����̒��_�P
			@param pt1	[in] �����̒��_�Q
		*/
		CLine3D( const Math::Vector3D &pt0, const Math::Vector3D &pt1 );
	};
}
}

#pragma once


/**
	@file
	@brief �Q�������p�`
	@author �t���`
*/


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Collision
{
	/**
		@brief �Q�����̑��p�`
		@author �t���`
	*/
	class SELENE_DLL_API CPolygon2D
	{
	public:
		Sint32 Count;					///< �|�C���g�z��̃|�C���g��
		Math::Vector2D *pPts;			///< �|���S����\�����߂̃|�C���g�z��̃|�C���^

	public:
		/**
			@brief �R���X�g���N�^
			@author �t���`
		*/
		CPolygon2D( void );

		/**
			@brief �R���X�g���N�^
			@author �t���`

			@param Cnt		[in] ���_��
			@param pPt		[in] ���_�̔z��̃A�h���X(���ŃR�s�[�͂���܂���̂ŁA�Q�ƌ��̃������͕ێ����Ă����K�v������܂�)

			@note
			Collision�N���X�Ŕ�����s���ꍇ�ACnt�̒l��4�ȏ��pPt[0]==pPt[Cnt-1]�ɂȂ��Ă���A<BR>
			pPt�̓��e�͎��v���A���邢�͔����v���̓ʌ`������Ă���K�v������܂��B
		*/
		CPolygon2D( Sint32 Cnt, Math::Vector2D *pPt );
	};
}
}

#pragma once


/**
	@file
	@brief �Q�����~
	@author �t���`
*/


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Collision
{
	/**
		@brief �Q������̉~
		@author �t���`
	*/
	class SELENE_DLL_API CCircle
	{
	public:
		Math::Vector2D vCenter;			///< �~�̒��S
		Float fRadius;					///< �~�̔��a

	public:
		/**
			@brief �R���X�g���N�^
			@author �t���`
		*/
		CCircle( void );

		/**
			@brief �R���X�g���N�^
			@author �t���`

			@param x		[in] �w���W
			@param y		[in] �x���W
			@param r		[in] ���a
		*/
		CCircle( Float x, Float y, Float r );

		/**
			@brief �R���X�g���N�^
			@author �t���`

			@param c		[in] ���S���W
			@param r		[in] ���a
		*/
		CCircle( Math::Vector2D &c, Float r );
	};
}
}

#pragma once


/**
	@file
	@brief �Փ˔���
	@author �t���`
*/


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Collision
{
/**
@brief 2D�_��2D�_�̏Փ˔���
@author �t���`
@param Pt1		[in] 2D���ʏ�̓_
@param Pt2		[in] 2D���ʏ�̓_
@retval false	�Փ˂��Ă��Ȃ�
@retval true	�Փ˂��Ă���

@note
2D���ʏ��2�̓_�̏Փ˔�����s���܂��B

@code

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  Math::Vector2D Pt1, Pt2;
  // �Փ˔���
  if ( Collision::Point_Point( Pt1, Pt2 ) )
  {
  }

  return 0;
}
@endcode
*/
	SELENE_DLL_API Bool Point_Point( const Math::Vector2D &Pt1, const Math::Vector2D &Pt2 );
/**
@brief 2D�_��2D�����̏Փ˔���
@author �t���`
@param Pt		[in] 2D���ʏ�̓_
@param Line		[in] 2D���ʏ�̐���
@retval false	�Փ˂��Ă��Ȃ�
@retval true	�Փ˂��Ă���

@note
2D���ʏ�̓_�Ɛ����̏Փ˔�����s���܂��B

@code

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  Math::Vector2D Pt;
  Collision::CLine2D Line;
  // �Փ˔���
  if ( Collision::Point_Line( Pt, Line ) )
  {
  }

  return 0;
}
@endcode
*/
	SELENE_DLL_API Bool Point_Line( const Math::Vector2D &Pt, const CLine2D &Line );
/**
@brief 2D�_��2D��`�̏Փ˔���
@author �t���`
@param Pt		[in] 2D���ʏ�̓_
@param Rect		[in] 2D���ʏ�̋�`
@retval false	�Փ˂��Ă��Ȃ�
@retval true	�Փ˂��Ă���

@note
2D���ʏ�̓_�Ƌ�`�̏Փ˔�����s���܂��B

@code

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  Math::Vector2D Pt;
  Math::Rect2D<Float> Rect;
  // �Փ˔���
  if ( Collision::Point_Rect( Pt, Rect ) )
  {
  }

  return 0;
}
@endcode
*/
	SELENE_DLL_API Bool Point_Rect( const Math::Vector2D &Pt, const Math::Rect2D<Float> &Rect );
/**
@brief 2D�_��2D��`�̏Փ˔���
@author �t���`
@param Pt		[in] 2D���ʏ�̓_
@param Cir		[in] 2D���ʏ�̉~
@retval false	�Փ˂��Ă��Ȃ�
@retval true	�Փ˂��Ă���

@note
2D���ʏ�̓_�Ɖ~�̏Փ˔�����s���܂��B

@code

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  Math::Vector2D Pt;
  Collision::CCircle Cir;
  // �Փ˔���
  if ( Collision::Point_Circle( Pt, Cir ) )
  {
  }

  return 0;
}
@endcode
*/
	SELENE_DLL_API Bool Point_Circle( const Math::Vector2D &Pt, const CCircle &Cir );
/**
@brief 2D�_��2D���p�`�̏Փ˔���
@author �t���`
@param Pt		[in] 2D���ʏ�̓_
@param Poly		[in] 2D���ʏ�̑��p�`
@retval false	�Փ˂��Ă��Ȃ�
@retval true	�Փ˂��Ă���

@note
2D���ʏ�̓_�Ƒ��p�`�̏Փ˔�����s���܂��B<BR>
CPolygon2D�Ɋւ��ẮA���v���A���邢�͔����v����<BR>
�ʌ`������Ă���K�v������܂��B

@code

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  Math::Vector2D Pt;
  Collision::CPolygon2D Poly;
  // �Փ˔���
  if ( Collision::Point_Polygon( Pt, Poly ) )
  {
  }

  return 0;
}
@endcode
*/
	SELENE_DLL_API Bool Point_Polygon( const Math::Vector2D &Pt, const CPolygon2D &Poly );
/**
@brief 2D��`��2D��`�̏Փ˔���
@author �t���`
@param Rect1		[in] 2D���ʏ�̋�`
@param Rect2		[in] 2D���ʏ�̋�`
@retval false	�Փ˂��Ă��Ȃ�
@retval true	�Փ˂��Ă���

@note
2D���ʏ�̋�`���m�̏Փ˔�����s���܂��B

@code

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  Math::Rect2D<Float> Rect1, Rect2;
  // �Փ˔���
  if ( Collision::Rect_Rect( Rect1, Rect2 ) )
  {
  }

  return 0;
}
@endcode
*/
	SELENE_DLL_API Bool Rect_Rect( const Math::Rect2D<Float> &Rect1, const Math::Rect2D<Float> &Rect2 );
/**
@brief 2D��`��2D�~�̏Փ˔���
@author �t���`
@param Rect		[in] 2D���ʏ�̋�`
@param Cir		[in] 2D���ʏ�̉~
@retval false	�Փ˂��Ă��Ȃ�
@retval true	�Փ˂��Ă���

@note
2D���ʏ�̋�`�Ɖ~�̏Փ˔�����s���܂��B

@code

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  Math::Rect2D<Float> Rect;
  Collision::CCircle Cir;
  // �Փ˔���
  if ( Collision::Rect_Circle( Rect, Cir ) )
  {
  }

  return 0;
}
@endcode
*/
	SELENE_DLL_API Bool Rect_Circle( const Math::Rect2D<Float> &Rect, const CCircle &Cir );
/**
@brief 2D��`��2D�����̏Փ˔���
@author �t���`
@param Rect		[in] 2D���ʏ�̋�`
@param Line		[in] 2D���ʏ�̐���
@retval false	�Փ˂��Ă��Ȃ�
@retval true	�Փ˂��Ă���

@note
2D���ʏ�̋�`�Ɛ����̏Փ˔�����s���܂��B

@code

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  Math::Rect2D<Float> Rect;
  Collision::CLine2D Line;
  // �Փ˔���
  if ( Collision::Rect_Line( Rect, Line ) )
  {
  }

  return 0;
}
@endcode
*/
	SELENE_DLL_API Bool Rect_Line( const Math::Rect2D<Float> &Rect, const CLine2D &Line );
/**
@brief 2D��`��2D���p�`�̏Փ˔���
@author �t���`
@param Rect		[in] 2D���ʏ�̋�`
@param Poly		[in] 2D���ʏ�̑��p�`
@retval false	�Փ˂��Ă��Ȃ�
@retval true	�Փ˂��Ă���

@note
2D���ʏ�̋�`�Ƒ��p�`�̏Փ˔�����s���܂��B<BR>
CPolygon2D�Ɋւ��ẮA���v���A���邢�͔����v����<BR>
�ʌ`������Ă���K�v������܂��B

@code

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  Math::Rect2D<Float> Rect;
  Collision::CPolygon2D Poly;
  // �Փ˔���
  if ( Collision::Rect_Polygon( Rect, Poly ) )
  {
  }

  return 0;
}
@endcode
*/
	SELENE_DLL_API Bool Rect_Polygon( const Math::Rect2D<Float> &Rect, const CPolygon2D &Poly );
/**
@brief 2D�~��2D�~�̏Փ˔���
@author �t���`
@param Cir1		[in] 2D���ʏ�̉~
@param Cir2		[in] 2D���ʏ�̉~
@retval false	�Փ˂��Ă��Ȃ�
@retval true	�Փ˂��Ă���

@note
2D���ʏ�̉~���m�̏Փ˔�����s���܂��B

@code

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  Collision::CCircle Cir1, Cir2;
  // �Փ˔���
  if ( Collision::Circle_Circle( Cir1, Cir2 ) )
  {
  }

  return 0;
}
@endcode
*/
	SELENE_DLL_API Bool Circle_Circle( const CCircle &Cir1, const CCircle &Cir2 );
/**
@brief 2D�~��2D�����̏Փ˔���
@author �t���`
@param Cir		[in] 2D���ʏ�̉~
@param Line		[in] 2D���ʏ�̐���
@retval false	�Փ˂��Ă��Ȃ�
@retval true	�Փ˂��Ă���

@note
2D���ʏ�̉~���m�̏Փ˔�����s���܂��B

@code

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  Collision::CCircle Cir;
  Collision::CLine2D Line;
  // �Փ˔���
  if ( Collision::Circle_Line( Cir, Line ) )
  {
  }

  return 0;
}
@endcode
*/
	SELENE_DLL_API Bool Circle_Line( const CCircle &Cir, const CLine2D &Line );
/**
@brief 2D�~��2D���p�`�̏Փ˔���
@author �t���`
@param Cir		[in] 2D���ʏ�̉~
@param Poly		[in] 2D���ʏ�̑��p�`
@retval false	�Փ˂��Ă��Ȃ�
@retval true	�Փ˂��Ă���

@note
2D���ʏ�̉~�Ƒ��p�`�̏Փ˔�����s���܂��B<BR>
CPolygon2D�Ɋւ��ẮA���v���A���邢�͔����v����<BR>
�ʌ`������Ă���K�v������܂��B

@code

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  Collision::CCircle Cir;
  Collision::CPolygon2D Poly;
  // �Փ˔���
  if ( Collision::Circle_Polygon( Cir, Poly ) )
  {
  }

  return 0;
}
@endcode
*/
	SELENE_DLL_API Bool Circle_Polygon( const CCircle &Cir, const CPolygon2D &Poly );
/**
@brief 2D������2D�����̏Փ˔���
@author �t���`
@param Line1	[in] 2D���ʏ�̐���
@param Line2	[in] 2D���ʏ�̐���
@retval false	�Փ˂��Ă��Ȃ�
@retval true	�Փ˂��Ă���

@note
2D���ʏ�̐������m�̏Փ˔�����s���܂��B

@code

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  Collision::CLine2D Line1, Line2;
  // �Փ˔���
  if ( Collision::Line_Line( Line1, Line2 ) )
  {
  }

  return 0;
}
@endcode
*/
	SELENE_DLL_API Bool Line_Line( const CLine2D &Line1, const CLine2D &Line2 );
/**
@brief 2D������2D���p�`�̏Փ˔���
@author �t���`
@param Line		[in] 2D���ʏ�̐���
@param Poly		[in] 2D���ʏ�̑��p�`
@retval false	�Փ˂��Ă��Ȃ�
@retval true	�Փ˂��Ă���

@note
2D���ʏ�̐����Ƒ��p�`�̏Փ˔�����s���܂��B<BR>
CPolygon2D�Ɋւ��ẮA���v���A���邢�͔����v����<BR>
�ʌ`������Ă���K�v������܂��B

@code

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  Collision::CLine2D Line1;
  Collision::CPolygon2D Poly;
  // �Փ˔���
  if ( Collision::Line_Polygon( Line, Poly ) )
  {
  }

  return 0;
}
@endcode
*/
	SELENE_DLL_API Bool Line_Polygon( const CLine2D &Line, const CPolygon2D &Poly );
/**
@brief 2D���p�`��2D���p�`�̏Փ˔���
@author �t���`
@param Poly1	[in] 2D���ʏ�̑��p�`
@param Poly2	[in] 2D���ʏ�̑��p�`
@retval false	�Փ˂��Ă��Ȃ�
@retval true	�Փ˂��Ă���

@note
2D���ʏ�̑��p�`���m�̂̏Փ˔�����s���܂��B<BR>
CPolygon2D�Ɋւ��ẮA���v���A���邢�͔����v����<BR>
�ʌ`������Ă���K�v������܂��B

@code

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  Collision::CPolygon2D Poly1, Poly2;
  // �Փ˔���
  if ( Collision::Polygon_Polygon( Poly1, Poly2 ) )
  {
  }

  return 0;
}
@endcode
*/
	SELENE_DLL_API Bool Polygon_Polygon( const CPolygon2D &Poly1, const CPolygon2D &Poly2 );
/**
@brief 3D�_��3D�_�̏Փ˔���
@author �t���`
@param Pt1		[in] 3D��Ԃ̓_
@param Pt2		[in] 3D��Ԃ̓_
@retval false	�Փ˂��Ă��Ȃ�
@retval true	�Փ˂��Ă���

@note
3D��ԓ��̓_���m�̏Փ˔�����s���܂��B

@code

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  Math::Vector3D Pt1, Pt2;
  // �Փ˔���
  if ( Collision::Point_Point_3D( Pt1, Pt2 ) )
  {
  }

  return 0;
}
@endcode
*/
	SELENE_DLL_API Bool Point_Point_3D( const Math::Vector3D &Pt1, const Math::Vector3D &Pt2 );
/**
@brief 3D�_��3D���̏Փ˔���
@author �t���`
@param Pt		[in] 3D��Ԃ̓_
@param Sph		[in] 3D��Ԃ̋�
@retval false	�Փ˂��Ă��Ȃ�
@retval true	�Փ˂��Ă���

@note
3D��ԓ��̓_�Ƌ��̏Փ˔�����s���܂��B

@code

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  Math::Vector3D Pt;
  Collision::CSphere Sph;
  // �Փ˔���
  if ( Collision::Point_Sphere_3D( Pt, Sph ) )
  {
  }

  return 0;
}
@endcode
*/
	SELENE_DLL_API Bool Point_Sphere_3D( const Math::Vector3D &Pt, const CSphere &Sph );
/**
@brief 3D�_��3D�����̏Փ˔���
@author �t���`
@param Pt		[in] 3D��Ԃ̓_
@param Line		[in] 3D��Ԃ̐���
@retval false	�Փ˂��Ă��Ȃ�
@retval true	�Փ˂��Ă���

@note
3D��ԓ��̓_�Ɛ����̏Փ˔�����s���܂��B

@code

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  Math::Vector3D Pt;
  Collision::CLine3D Line;
  // �Փ˔���
  if ( Collision::Point_Line_3D( Pt, Line ) )
  {
  }

  return 0;
}
@endcode
*/
	SELENE_DLL_API Bool Point_Line_3D( const Math::Vector3D &Pt, const CLine3D &Line );
/**
@brief 3D�_��3D���ʂ̏Փ˔���
@author �t���`
@param Pt		[in] 3D��Ԃ̓_
@param Plane	[in] 3D��Ԃ̕���
@retval false	�Փ˂��Ă��Ȃ�
@retval true	�Փ˂��Ă���

@note
3D��ԓ��̓_�ƕ��ʂ̏Փ˔�����s���܂��B

@code

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  Math::Vector3D Pt;
  Collision::CPlane Plane;
  // �Փ˔���
  if ( Collision::Point_Plane_3D( Pt, Plane ) )
  {
  }

  return 0;
}
@endcode
*/
	SELENE_DLL_API Bool Point_Plane_3D( const Math::Vector3D &Pt, const CPlane &Plane );
/**
@brief 3D�_��3D���̏Փ˔���
@author �t���`
@param Pt		[in] 3D��Ԃ̓_
@param Box		[in] 3D��Ԃ̔�
@retval false	�Փ˂��Ă��Ȃ�
@retval true	�Փ˂��Ă���

@note
3D��ԓ��̓_�ƕ��ʂ̏Փ˔�����s���܂��B

@code

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  Math::Vector3D Pt;
  Collision::CBox Box;
  // �Փ˔���
  if ( Collision::Point_Box_3D( Pt, Box ) )
  {
  }

  return 0;
}
@endcode
*/
	SELENE_DLL_API Bool Point_Box_3D( const Math::Vector3D &Pt, const CBox &Box );
/**
@brief 3D����3D���̏Փ˔���
@author �t���`
@param Sph1		[in] 3D��Ԃ̋�
@param Sph2		[in] 3D��Ԃ̋�
@retval false	�Փ˂��Ă��Ȃ�
@retval true	�Փ˂��Ă���

@note
3D��ԓ��̋����m�̏Փ˔�����s���܂��B

@code

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  Collision::CSphere Sph1, Sph2;
  // �Փ˔���
  if ( Collision::Sphere_Sphere_3D( Sph1, Sph2 ) )
  {
  }

  return 0;
}
@endcode
*/
	SELENE_DLL_API Bool Sphere_Sphere_3D( const CSphere &Sph1, const CSphere &Sph2 );
/**
@brief 3D����3D�����̏Փ˔���
@author �t���`
@param Sph		[in] 3D��Ԃ̋�
@param Line		[in] 3D��Ԃ̐���
@retval false	�Փ˂��Ă��Ȃ�
@retval true	�Փ˂��Ă���

@note
3D��ԓ��̋��Ɛ����̏Փ˔�����s���܂��B

@code

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  Collision::CSphere Sph;
  Collision::CLine3D Line;
  // �Փ˔���
  if ( Collision::Sphere_Line_3D( Sph, Line ) )
  {
  }

  return 0;
}
@endcode
*/
	SELENE_DLL_API Bool Sphere_Line_3D( const CSphere &Sph, const CLine3D &Line );
/**
@brief 3D����3D���ʂ̏Փ˔���
@author �t���`
@param Sph		[in] 3D��Ԃ̋�
@param Plane	[in] 3D��Ԃ̕���
@retval false	�Փ˂��Ă��Ȃ�
@retval true	�Փ˂��Ă���

@note
3D��ԓ��̋��ƕ��ʂ̏Փ˔�����s���܂��B

@code

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  Collision::CSphere Sph;
  Collision::CPlane Plane;
  // �Փ˔���
  if ( Collision::Sphere_Plane( Sph, Plane ) )
  {
  }

  return 0;
}
@endcode
*/
	SELENE_DLL_API Bool Sphere_Plane( const CSphere &Sph, const CPlane &Plane );
/**
@brief 3D������3D���ʂ̏Փ˔���
@author �t���`
@param Line			[in] 3D��Ԃ̐���
@param Plane		[in] 3D��Ԃ̕���
@param vIntersect	[out] �Փˈʒu
@retval false	�Փ˂��Ă��Ȃ�
@retval true	�Փ˂��Ă���

@note
3D��ԓ��̐����ƕ��ʂ̏Փ˔�����s���܂��B

@code

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  Collision::CLine3D Line;
  Collision::CPlane Plane;
  Math::Vector3D vIntersect;
  // �Փ˔���
  if ( Collision::Line_Plane_3D( Line, Plane, vIntersect ) )
  {
  }

  return 0;
}
@endcode
*/
	SELENE_DLL_API Bool Line_Plane_3D( const CLine3D &Line, const CPlane &Plane, Math::Vector3D &vIntersect );
/**
@brief 3D������3D���̏Փ˔���
@author �t���`
@param Line			[in] 3D��Ԃ̐���
@param Box			[in] 3D��Ԃ̔�
@retval false	�Փ˂��Ă��Ȃ�
@retval true	�Փ˂��Ă���

@note
3D��ԓ��̐����Ɣ��̏Փ˔�����s���܂��B

@code

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  Collision::CLine3D Line;
  Collision::CBox Box;
  // �Փ˔���
  if ( Collision::Line_Box_3D( Line, Box ) )
  {
  }

  return 0;
}
@endcode
*/
	SELENE_DLL_API Bool Line_Box_3D( const CLine3D &Line, const CBox &Box );
/**
@brief 3D����3D���̏Փ˔���
@author �t���`
@param Box1		[in] 3D��Ԃ̔�
@param Box2		[in] 3D��Ԃ̔�
@retval false	�Փ˂��Ă��Ȃ�
@retval true	�Փ˂��Ă���

@note
3D��ԓ��̔����m�̏Փ˔�����s���܂��B

@code

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  Collision::CBox Box1, Box2;
  // �Փ˔���
  if ( Collision::Box_Box_3D( Box1, Box2 ) )
  {
  }

  return 0;
}
@endcode
*/
	SELENE_DLL_API Bool Box_Box_3D( const CBox &Box1, const CBox &Box2 );
}
}

#pragma once


/**
	@file
	@brief �C���^�[�t�F�C�X���N���X
	@author �t���`
*/


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
	/**
		@brief �C���^�[�t�F�[�X���N���X
		@author �t���`
	*/
	class IInterface
	{
	public:
		virtual ~IInterface() {}

/**
@brief �L�����`�F�b�N
@author �t���`
@retval true ����
@retval false �L��

@note
�C���^�[�t�F�C�X���L�����������𒲂ׂ܂��B

@code
// �L�����`�F�b�N
if ( this->IsInvalid() )
{
	// �����ȃC���^�[�t�F�C�X
	reutrn false;
}
*/
		virtual Bool IsInvalid( void ) = 0;

/**
@brief �Q�ƃJ�E���^�f�N�������g
@author �t���`
@return �f�N�������g��̎Q�ƃJ�E���g

@note
�Q�ƃJ�E���^���f�N�������g���A<BR>
�Q�ƃJ�E���g��0�ɂȂ������_�Ń��������������܂��B

@code
// ����i�Q�ƃJ�E���^��-1���邾���B���ۂɂ͎Q�ƃJ�E���g��0�ɂȂ�ƃ���������������j
this->Release();
@endcode
*/
		virtual Sint32 Release( void ) = 0;

/**
@brief �Q�ƃJ�E���^�C���N�������g
@author �t���`
@return �C���N�������g��̎Q�ƃJ�E���g

@note
�Q�ƃJ�E���^���C���N�������g���܂��B<BR>
�C���N�������g�����Q�ƃJ�E���g��Release()���ĂԂ��Ƃɂ��f�N�������g����܂��B<BR>
AddRef()�������C���^�[�t�F�C�X�͕K��Release()�ŉ�����Ă��������B

@code
IInterface *pCopy = this;
// ���ł��Q�Ƃ���̂ŎQ�Ɛ�+1
this->AddRef();
@endcode
*/
		virtual Sint32 AddRef( void ) = 0;
	};
}

#pragma once


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Fiber
{
	/**
		@brief �t�@�C�o�[�R���g���[���[�C���^�[�t�F�C�X
		@author �t���`

		@note
		�t�@�C�o�[�̐�����s�����߂̃C���^�[�t�F�C�X�ł��B
	*/
	class IFiberController : public IInterface
	{
	public:
		virtual ~IFiberController() {}

/**
@brief �t�@�C�o�[�V�X�e���J�n
@author �t���`
@note
�t�@�C�o�[�̏������J�n���܂��B
*/
		virtual void Start( void ) = 0;

/**
@brief �t�@�C�o�[�V�X�e���I��
@author �t���`
@note
�t�@�C�o�[�̏������I�����܂��B
*/
		virtual void Exit( void ) = 0;

/**
@brief �t�@�C�o�[�؂�ւ�
@author �t���`
@retval false	�A�v���P�[�V�����͏I�����Ă���
@retval true	�A�v���P�[�V�����͌p�����ł���
@note
�t�@�C�o�[�̐؂�ւ����s���܂��B
*/
		virtual Bool Switch( void ) = 0;

/**
@brief �t�@�C�o�[����
@author �t���`
@param FiberId	[in] �t�@�C�o�[ID
@param pFiber	[in] �t�@�C�o�[�C���^�[�t�F�C�X
@retval false	�w���FiberId�ɂ��łɃt�@�C�o�[������
@retval true	����
@note
�t�@�C�o�[�̐������s���܂��B
*/
		virtual Bool Create( Sint32 FiberId, IFiber *pFiber ) = 0;
	};
}
}


#pragma once


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Fiber
{
	/**
		@brief �t�@�C�o�[�C���^�[�t�F�C�X
		@author �t���`

		@note
		�t�@�C�o�[���������邽�߂̊��N���X�ł��B
	*/
	class IFiber
	{
	private:
		Sint32 m_RefCount;
		IFiberController *m_pFiberCtrl;

	protected:
/**
@brief �t�@�C�o�[�؂�ւ�
@author �t���`
@retval true	�A�v���P�[�V�����͌p����
@retval false	�A�v���P�[�V�������I�����Ă���

@note
�o�^����Ă��鎟��ID�̃t�@�C�o�[�ɏ�����؂�ւ��܂��B<BR>
�Ԃ�l��false�̏ꍇ�A�v���P�[�V�������I���������s���Ă���̂�<BR>
Controller()���\�b�h���璼���ɔ�����悤�ɑg��ŉ������B
*/
		Bool Switch( void )
		{
			return m_pFiberCtrl->Switch();
		}

	public:
/**
@brief �R���X�g���N�^
@author �t���`
*/
		IFiber( void )
			: m_pFiberCtrl	( NULL )
			, m_RefCount	( 1 )
		{
		}

/**
@brief �f�X�g���N�^
@author �t���`
*/
		virtual ~IFiber()
		{
			if ( m_pFiberCtrl != NULL )
			{
				m_pFiberCtrl->Release();
			}
		}

/**
@brief �Q�ƃJ�E���^�f�N�������g
@author �t���`
@return �f�N�������g��̎Q�ƃJ�E���g

@note
�Q�ƃJ�E���^���f�N�������g���A<BR>
�Q�ƃJ�E���g��0�ɂȂ������_�Ń��������������܂��B
*/
		Sint32 Release( void )
		{
			Sint32 Cnt = --m_RefCount;
			if ( Cnt == 0 )
			{
				delete this;
			}
			return Cnt;
		}

/**
@brief �Q�ƃJ�E���^�C���N�������g
@author �t���`
@return �C���N�������g��̎Q�ƃJ�E���g

@note
�Q�ƃJ�E���^���C���N�������g���܂��B<BR>
�C���N�������g�����Q�ƃJ�E���g��Release()���ĂԂ��Ƃɂ��f�N�������g����܂��B<BR>
AddRef()�������C���^�[�t�F�C�X�͕K��Release()�ŉ�����Ă��������B
*/
		Sint32 AddRef( void )
		{
			return ++m_RefCount;
		}

/**
@brief �R���g���[���[�ݒ�
@author �t���`
@param pCtrl	[in] �R���g���[���[
*/
		void SetController( IFiberController *pCtrl )
		{
			m_pFiberCtrl = pCtrl;
			m_pFiberCtrl->AddRef();
		}

	public:
/**
@brief �t�@�C�o�[�p����֐�
@author �t���`

@note
�t�@�C�o�[�����ۂɑ��삷�邽�߂̏������z�֐��ł��B<BR>
���̊֐����甲���邱�Ƃł��̃t�@�C�o�[�̏�������~���܂��B<BR>
Switch()���\�b�h�ł̐؂�ւ�����false���A���Ă����炽������<BR>
�֐����甲����悤�ɂ��ĉ������B
*/
		virtual void Control( void ) = 0;
	};
}
}

#pragma once


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
	/**
		@brief �r�f�I�J�[�h�Ǘ��C���^�[�t�F�C�X
		@author �t���`
	*/
	class IGraphicCard
	{
	public:
		/**
			@brief �L�����`�F�b�N
			@author �t���`
			@retval true ����
			@retval false �L��

			�C���^�[�t�F�C�X���L�����������𒲂ׂ܂��B
		*/
		virtual Bool IsInvalid( void ) = 0;

		/**
			@brief �Q�ƃJ�E���^�f�N�������g
			@author �t���`
			@return �f�N�������g��̎Q�ƃJ�E���g

			�Q�ƃJ�E���^���f�N�������g���A<BR>
			�Q�ƃJ�E���g��0�ɂȂ������_�Ń��������������܂��B
		*/
		virtual Sint32 Release( void ) = 0;

		/**
			@brief �Q�ƃJ�E���^�C���N�������g
			@author �t���`
			@return �C���N�������g��̎Q�ƃJ�E���g

			�Q�ƃJ�E���^���C���N�������g���܂��B<BR>
			�C���N�������g�����Q�ƃJ�E���g��Release()���ĂԂ��Ƃɂ��f�N�������g����܂��B<BR>
			AddRef()�������C���^�[�t�F�C�X�͕K��Release()�ŉ�����Ă��������B
		*/
		virtual Sint32 AddRef( void	) = 0;

		/**
			@brief 16Bit�J���[���[�h���g�p
			@author �t���`

			�t���X�N���[�����̉�ʃJ���[��32Bit�ł͂Ȃ�16Bit�ɂ��܂��B<BR>
			�t�B�����[�g�̌��������ő��x�̌��オ�]�߂܂����A<BR>
			�}�b�n�o���h�Ȃǂ̉掿�I�Ȗ����o�܂��B
		*/
		virtual void EnableHighlColorScreen( void ) = 0;

		/**
			@brief �s�N�Z���V�F�[�_�[���T�|�[�g����Ă��邩�擾
			@author �t���`
			@param Major	[in] ���W���[�o�[�W����
			@param Minor	[in] �}�C�i�[�o�[�W����

			���݂̃f�o�C�X�Ŏw�肵���s�N�Z���V�F�[�_�[���T�|�[�g<BR>
			���Ă��邩�ǂ������擾���܂��B
		*/
		virtual Bool GetPixelShaderSupport( Uint16 Major, Uint16 Minor ) = 0;

		/**
			@brief ��ʉ𑜓x���擾
			@author �t���`
			@param IsFullColor	[in] �t���J���[(32Bit)�̉�ʉ𑜓x���ۂ�
			@return ��ʉ𑜓x��

			�g�p�\�ȉ�ʉ𑜓x�̐����擾�ł��܂��B<BR>
			IsFullColor�t���O�ɉ����āA16Bit/32Bit�J���[�̉�ʉ𑜓x�����擾�o���܂��B
		*/
		virtual Sint32 GetScreenModeCount( Bool IsFullColor ) = 0;

		/**
			@brief ��ʉ𑜓x
			@author �t���`
			@param IsFullColor	[in] �t���J���[(32Bit)�̉�ʉ𑜓x���ۂ�
			@param No			[in] ��ʉ𑜓x�̃C���f�b�N�X�i�ő吔��GetScreenModeCount()�Ŏ擾�j
			@param Width		[out] ��ʉ����i�[��
			@param Height		[out] ��ʏc���i�[��

			�g�p�\�ȉ�ʉ𑜓x���擾���܂��B
		*/
		virtual void GetScreenMode( Bool IsFullColor, Sint32 No, Sint32 &Width, Sint32 &Height ) = 0;

		/**
			@brief �����_�����O�^�[�Q�b�g�e�N�X�`���T�C�Y���擾
			@author �t���`
			@return �����_�����O�^�[�Q�b�g�e�N�X�`���T�C�Y��

			�g�p�\�ȃ����_�����O�^�[�Q�b�g�e�N�X�`���T�C�Y�̐����擾�ł��܂��B
		*/
		virtual Sint32 CreateRenderTargetTextureSizeCount( void ) = 0;

		/**
			@brief �����_�����O�^�[�Q�b�g�e�N�X�`���T�C�Y
			@author �t���`
			@param No			[in] �����_�����O�^�[�Q�b�g�e�N�X�`���T�C�Y�̃C���f�b�N�X�i�ő吔��CreateRenderTargetTextureSizeCount()�Ŏ擾�j
			@param pWidth		[out] ��ʉ����i�[��
			@param pHeight		[out] ��ʏc���i�[��

			�g�p�\�ȃ����_�����O�^�[�Q�b�g�e�N�X�`���T�C�Y���擾���܂��B
		*/
		virtual void CreateRenderTargetTextureSize( Sint32 No, Sint32 *pWidth, Sint32 *pHeight ) = 0;

		/**
			@brief �O���t�B�b�N�J�[�h���̎擾
			@author �t���`
			@param pName		[out] ���̊i�[��
			@param NameSize		[in] pName�̃o�b�t�@�T�C�Y

			�ڑ�����Ă���O���t�B�b�N�J�[�h�̖��̂��擾���܂��B
		*/
		virtual void GetGraphicCardName( char *pName, Sint32 NameSize ) = 0;

		/**
			@brief ���_�V�F�[�_�[�̃o�[�W�������擾
			@author �t���`
			@param pName		[out] �o�[�W�����i�[��
			@param NameSize		[in] pName�̃o�b�t�@�T�C�Y

			�ڑ�����Ă���O���t�B�b�N�J�[�h�̒��_�V�F�[�_�[�̃o�[�W�������擾���܂��B
		*/
		virtual void GetVertexShaderVersion( char *pName, Sint32 NameSize ) = 0;

		/**
			@brief �s�N�Z���V�F�[�_�[�̃o�[�W�������擾
			@author �t���`
			@param pName		[out] �o�[�W�����i�[��
			@param NameSize		[in] pName�̃o�b�t�@�T�C�Y

			�ڑ�����Ă���O���t�B�b�N�J�[�h�̃s�N�Z���V�F�[�_�[�̃o�[�W�������擾���܂��B
		*/
		virtual void GetPixelShaderVersion( char *pName, Sint32 NameSize ) = 0;

		/**
			@brief IRender�C���^�[�t�F�C�X����
			@author �t���`
			@param IsLockEnableBackBuffer	[in] �o�b�N�o�b�t�@�̃��b�N�L��
			@param IsWaitVSync				[in] ��ʍX�V����VSYNC��҂�
			@return IRender�C���^�[�t�F�C�X

			�O���t�B�b�N�J�[�h��̃����_���[����p��IRender�C���^�[�t�F�C�X���擾���܂��B<BR>
			IRender�C���^�[�t�F�C�X�͂P��IGraphicCard�ɑ΂��ĂP�������݂��܂���B
		*/
		virtual Renderer::IRender *CreateRender( Bool IsLockEnableBackBuffer = false, Bool IsWaitVSync = true ) = 0;
	};
}

#pragma once


/**
	@file
	@brief �A�v���P�[�V�����Ǘ��C���^�[�t�F�C�X
	@author �t���`
*/


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
	/**
		@brief �A�v���P�[�V�����Ǘ��C���^�[�t�F�C�X
		@author �t���`

		@note
		�E�B���h�E���Ǘ�����A�v���P�[�V�����̃R�A�̃C���^�[�t�F�C�X�ł��B
	*/
	class ICore : public IInterface
	{
	public:
		virtual ~ICore() {}

/**
@brief �R�A�̏�����
@author �t���`
@param pAppName		[in] �A�v���P�[�V������
@param FrameRate	[in] �t���[�����[�g
@retval false	���s
@retval true	����

@note
�A�v���P�[�V�����Ɋւ��鏉�������s���܂��B

@code
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
  ICore *pCore = NULL;

  // �V�X�e���̏�����
  System::Initialize();

  // �R�A�̐���
  pCore = System::CreateCore();

  // ������
  if ( pCore->Initialize( "Sample Program", FRAME_RATE_60 ) )
  {
  }

  // �R�A�̉��
  SAFE_RELEASE( pCore );

  // �V�X�e���̉��
  System::Finalize();

  return 0;
}
@endcode
*/
		virtual Bool Initialize( const char *pAppName, eFrameRate FrameRate ) = 0;

/**
@brief �E�B���h�E����
@author �t���`
@param ScreenWidth	[in] ��ʉ���
@param ScreenHeight	[in] ��ʏc��
@param IsWindow		[in] �E�B���h�E���[�h�ŋN������ꍇtrue

@note
�E�B���h�E���쐬���A�A�v���P�[�V�������N�����܂��B<BR>
�����ł̐ݒ�ŋN����ύX�\�Ȃ��͉̂�ʃ��[�h�����ł��B

@code
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
  ICore *pCore = NULL;

  // �V�X�e���̏�����
  System::Initialize();

  // �R�A�̐���
  pCore = System::CreateCore();

  // ������
  if ( pCore->Initialize( "Sample Program", FRAME_RATE_60 ) )
  {
    // �A�v���P�[�V�����J�n
    pCore->Start( 640, 480, true );
  }

  // �R�A�̉��
  SAFE_RELEASE( pCore );

  // �V�X�e���̉��
  System::Finalize();

  return 0;
}
@endcode
*/
		virtual void Start( Sint32 ScreenWidth, Sint32 ScreenHeight, Bool IsWindow ) = 0;

/**
@brief �E�B���h�E�̏I��
@author �t���`

@note
�E�B���h�E����̂��A�A�v���P�[�V�������I�����܂��B<BR>
���̊֐��͏I����ʒm���邾���ŁA���ۂɂ̓��C�����[�v���<BR>
�I���������s���܂��B

@code
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
  ICore *pCore = NULL;

  // �V�X�e���̏�����
  System::Initialize();

  // �R�A�̐���
  pCore = System::CreateCore();

  // ������
  if ( pCore->Initialize( "Sample Program", FRAME_RATE_60 ) )
  {
    // �A�v���P�[�V�����J�n
    pCore->Start( 640, 480, true );

    // ���C�����[�v
    while ( pCore->Run() )
    {
      // �I��
      pCore->Exit();
    }
  }

  // �R�A�̉��
  SAFE_RELEASE( pCore );

  // �V�X�e���̉��
  System::Finalize();

  return 0;
}
@endcode
*/
		virtual void Exit( void ) = 0;

/**
@brief �A�v���P�[�V�������C������
@author �t���`
@param IsFullActive	[in] �펞����t���O
@retval false	�A�v���P�[�V�����͏I������
@retval true	�A�v���P�[�V�����͉ғ���

@note
IsFullActive��true���w�肷��ƁA<BR>
�E�B���h�E���t�H�[�J�X�������Ă����Ԃł����삵�����܂��B

@code
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
  ICore *pCore = NULL;

  // �V�X�e���̏�����
  System::Initialize();

  // �R�A�̐���
  pCore = System::CreateCore();

  // ������
  if ( pCore->Initialize( "Sample Program", FRAME_RATE_60 ) )
  {
    // �A�v���P�[�V�����J�n
    pCore->Start( 640, 480, true );

    // ���C�����[�v
    while ( pCore->Run() )
    {
    }
  }

  // �R�A�̉��
  SAFE_RELEASE( pCore );

  // �V�X�e���̉��
  System::Finalize();

  return 0;
}
@endcode
*/
		virtual Bool Run( Bool IsFullActive = false ) = 0;

/**
@brief �E�B���h�E�n���h���擾
@author �t���`
@return �E�B���h�E�̃E�B���h�E�n���h��

@note
ICore�̏��L����E�B���h�E�̃E�B���h�E�n���h�����擾���܂��B


@code
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
  ICore *pCore = NULL;

  // �V�X�e���̏�����
  System::Initialize();

  // �R�A�̐���
  pCore = System::CreateCore();

  // ������
  if ( pCore->Initialize( "Sample Program", FRAME_RATE_60 ) )
  {
    // �A�v���P�[�V�����J�n
    pCore->Start( 640, 480, true );

    // �E�B���h�E�n���h�����擾
    HWND hWnd = pCore->GetWindowHandle();

    // ���C�����[�v
    while ( pCore->Run() )
    {
    }
  }

  // �R�A�̉��
  SAFE_RELEASE( pCore );

  // �V�X�e���̉��
  System::Finalize();

  return 0;
}
@endcode
*/
		virtual HWND GetWindowHandle( void ) = 0;

/**
@brief �x���`�}�[�N�p���[�h�ݒ�
@author �t���`
@param IsEnable	[in] true�ɂ���Ƃ��ׂẴE�F�C�g�������Ȃ��܂�

@note
�x���`�}�[�N�̂悤�ȑ��x�`�F�b�N������ꍇ�Ɏg���܂��B<BR>
���̃t���O��true�ɂ����VSYNC��^�C�}�[�Ȃǂ̏��������ׂďȂ���A<BR>
�o����ō��̑��x�ŏ��������܂��B<BR>
<BR>
�f�t�H���g��false�ł��B

@code
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
  ICore *pCore = NULL;

  // �V�X�e���̏�����
  System::Initialize();

  // �R�A�̐���
  pCore = System::CreateCore();

  // ������
  if ( pCore->Initialize( "Sample Program", FRAME_RATE_60 ) )
  {
    // �x���`�}�[�N�p�Ɋe��E�F�C�g��OFF
    pCore->SetBenchMode( true );

    // �A�v���P�[�V�����J�n
    pCore->Start( 640, 480, true );

    // ���C�����[�v
    while ( pCore->Run() )
    {
    }
  }

  // �R�A�̉��
  SAFE_RELEASE( pCore );

  // �V�X�e���̉��
  System::Finalize();

  return 0;
}
@endcode
*/
		virtual void SetBenchMode( Bool IsEnable ) = 0;

/**
@brief Sleep�g�p�L���ݒ�
@author �t���`
@param IsEnable	[in] true�ɂ����Sleep���g�p���܂�

@note
�t���[�����[�g�̒�����Sleep���g�����ǂ�����ݒ肵�܂��B<BR>
���ɂ���Ă͌덷���傫���t���[�����[�g�����ɂȂ�Ȃ����Ƃ�����̂ŁA<BR>
���̂悤�ȏ����ł�false��ݒ肵�ĉ������B<BR>
Sleep���g��Ȃ��ꍇ�͓��RCPU����ɐ�L����悤�ɂȂ�܂��B<BR>
<BR>
�f�t�H���g��true�ł��B

@code
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
  ICore *pCore = NULL;

  // �V�X�e���̏�����
  System::Initialize();

  // �R�A�̐���
  pCore = System::CreateCore();

  // ������
  if ( pCore->Initialize( "Sample Program", FRAME_RATE_60 ) )
  {
    // ��茵���Ɏ��Ԍv��������iCPU�g�p�������ˏオ��̂Œ��Ӂj
    pCore->SetSleepUse( false );

    // �A�v���P�[�V�����J�n
    pCore->Start( 640, 480, true );

    // ���C�����[�v
    while ( pCore->Run() )
    {
    }
  }

  // �R�A�̉��
  SAFE_RELEASE( pCore );

  // �V�X�e���̉��
  System::Finalize();

  return 0;
}
@endcode
*/
		virtual void SetSleepUse( Bool IsEnable ) = 0;

/**
@brief ���z��ʏ�����ON/OFF
@author �t���`
@param IsEnable		[in] true �L�� / false ����

@note
2D�`�掞�̉��z��ʏ����̗L����ON/OFF��ݒ肵�܂��B<BR>
true�ɂ��鎖��2D�̕`�悪���z��ʂɍs����悤�ɂȂ�A<BR>
��ʉ𑜓x�Ɋ֌W�Ȃ���ʂɑ΂��铯�������ŕ`�悳���悤�ɂȂ�܂��B<BR>
<BR>
�f�t�H���g��false�ł��B

@code
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
  ICore *pCore = NULL;

  // �V�X�e���̏�����
  System::Initialize();

  // �R�A�̐���
  pCore = System::CreateCore();

  // ������
  if ( pCore->Initialize( "Sample Program", FRAME_RATE_60 ) )
  {
    // ��ʃT�C�Y���Ԃ��Ă������悤��2D�������z��ʂɕ`��
    pCore->SetVirtualScreenEnable( true );

    // �A�v���P�[�V�����J�n
    pCore->Start( 640, 480, true );

    // ���C�����[�v
    while ( pCore->Run() )
    {
    }
  }

  // �R�A�̉��
  SAFE_RELEASE( pCore );

  // �V�X�e���̉��
  System::Finalize();

  return 0;
}
@endcode
*/
		virtual void SetVirtualScreenEnable( Bool IsEnable ) = 0;

/**
@brief ���z��ʐݒ�
@author �t���`
@param RealWidth		[in] ����ʂ̉���
@param RealHeight		[in] ����ʂ̏c��
@param VirtualWidth		[in] ���z��ʂ̉���
@param VirtualHeight	[in] ���z��ʂ̏c��

@note
�ω�ʃT�C�Y�p�̐ݒ���s���܂��B<BR>
3D�p�ɉ�ʂ̃T�C�Y�����R�ɕς�����悤�ɍ���Ă���ꍇ�ł�<BR>
2D�̕`��͉��z��ʂɐݒ肳�ꂽ��ʃT�C�Y�ƌ����Ăĕ`����s���܂��B<BR>
�܂艼�z��ʂ�(640x480)�̎���(0,0)-(640,480)�ւ̑S��ʂ�2D�`����s�����ꍇ�A<BR>
���ۂ̉�ʂ̃T�C�Y��(320x240)��(1280x960)���̃T�C�Y�ł����Ă�<BR>
�S��ʂɎ����I�Ɋg��k�����ĕ`�悳���Ƃ������Ƃł��B

@code
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
  ICore *pCore = NULL;

  // �V�X�e���̏�����
  System::Initialize();

  // �R�A�̐���
  pCore = System::CreateCore();

  // ������
  if ( pCore->Initialize( "Sample Program", FRAME_RATE_60 ) )
  {
    // ��ʃT�C�Y���Ԃ��Ă������悤��2D�������z��ʂɕ`��
    pCore->SetVirtualScreenEnable( true );

    // ���z��ʃT�C�Y
    pCore->SetVirtualScreenSize( 640, 480, 800, 600 );

    // �A�v���P�[�V�����J�n
    pCore->Start( 640, 480, true );

    // ���C�����[�v
    while ( pCore->Run() )
    {
    }
  }

  // �R�A�̉��
  SAFE_RELEASE( pCore );

  // �V�X�e���̉��
  System::Finalize();

  return 0;
}
@endcode
*/
		virtual void SetVirtualScreenSize( Sint32 RealWidth, Sint32 RealHeight, Sint32 VirtualWidth, Sint32 VirtualHeight ) = 0;

/**
@brief GPU���ׂ��擾���܂��B
@author �t���`
@return GPU���ׁi���j

@note
�����܂���GPU�̕��ׂ��擾���܂��B

@code
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
  ICore *pCore = NULL;

  // �V�X�e���̏�����
  System::Initialize();

  // �R�A�̐���
  pCore = System::CreateCore();

  // ������
  if ( pCore->Initialize( "Sample Program", FRAME_RATE_60 ) )
  {
    // �A�v���P�[�V�����J�n
    pCore->Start( 640, 480, true );

    // ���C�����[�v
    while ( pCore->Run() )
    {
      // CPU�g�p��
      Float fCPU = pCore->GetCPU();
    }
  }

  // �R�A�̉��
  SAFE_RELEASE( pCore );

  // �V�X�e���̉��
  System::Finalize();

  return 0;
}
@endcode
*/
		virtual Float GetCPU( void ) = 0;

/**
@brief FPS���擾���܂��B
@author �t���`
@return FPS

@note
�b�Ԃ̃t���[�������擾���܂��B

@code
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
  ICore *pCore = NULL;

  // �V�X�e���̏�����
  System::Initialize();

  // �R�A�̐���
  pCore = System::CreateCore();

  // ������
  if ( pCore->Initialize( "Sample Program", FRAME_RATE_60 ) )
  {
    // �A�v���P�[�V�����J�n
    pCore->Start( 640, 480, true );

    // ���C�����[�v
    while ( pCore->Run() )
    {
      // FPS
      Float fFPS = pCore->GetFPS();
    }
  }

  // �R�A�̉��
  SAFE_RELEASE( pCore );

  // �V�X�e���̉��
  System::Finalize();

  return 0;
}
@endcode
*/
		virtual Float GetFPS( void ) = 0;

/**
@brief 1�t���[���̃|���S�������擾���܂��B
@author �t���`
@return PPS

@note
�b�Ԃ̃|���S�������擾���܂��B

@code
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
  ICore *pCore = NULL;

  // �V�X�e���̏�����
  System::Initialize();

  // �R�A�̐���
  pCore = System::CreateCore();

  // ������
  if ( pCore->Initialize( "Sample Program", FRAME_RATE_60 ) )
  {
    // �A�v���P�[�V�����J�n
    pCore->Start( 640, 480, true );

    // ���C�����[�v
    while ( pCore->Run() )
    {
      // �|���S�����擾
	  Float fPPF = pCore->GetPPF();
    }
  }

  // �R�A�̉��
  SAFE_RELEASE( pCore );

  // �V�X�e���̉��
  System::Finalize();

  return 0;
}
@endcode
*/
		virtual Float GetPPF( void ) = 0;

/**
@brief OS�N������̎��Ԏ擾
@author �t���`
@return 1/1000�b�P�ʂ̎���

@note
OS���N�����Ă���̎��Ԃ��擾���܂��B<BR>
32Bit�ϐ��Ȃ̂Ŗ�48����1������0�ɖ߂�܂��B

@code
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
  ICore *pCore = NULL;

  // �V�X�e���̏�����
  System::Initialize();

  // �R�A�̐���
  pCore = System::CreateCore();

  // ������
  if ( pCore->Initialize( "Sample Program", FRAME_RATE_60 ) )
  {
    // �A�v���P�[�V�����J�n
    pCore->Start( 640, 480, true );

    // ���C�����[�v
    while ( pCore->Run() )
    {
      // ���Ԏ擾
      Uint32 Time = pCore->GetMultiMediaTime();
    }
  }

  // �R�A�̉��
  SAFE_RELEASE( pCore );

  // �V�X�e���̉��
  System::Finalize();

  return 0;
}
@endcode
*/
		virtual Uint32 GetMultiMediaTime( void ) = 0;

/**
@brief CPU�^�C�}�[�̃J�E���g�l�擾
@author �t���`
@return 1/GetSystemTimerBySec�b�P�ʂ̎���

@note
CPU�^�C�}�[�̌��݂̎��Ԃ��擾���܂��B

@code
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
  ICore *pCore = NULL;

  // �V�X�e���̏�����
  System::Initialize();

  // �R�A�̐���
  pCore = System::CreateCore();

  // ������
  if ( pCore->Initialize( "Sample Program", FRAME_RATE_60 ) )
  {
    // �A�v���P�[�V�����J�n
    pCore->Start( 640, 480, true );

    // ���C�����[�v
    while ( pCore->Run() )
    {
      // ���Ԏ擾
      Uint64 Time = pCore->GetSystemTimer();

      // �Ȃ񂩏�������
 
      // �o�ߎ��Ԏ擾
      Time = pCore->GetSystemTimer() - Time;

      // �o�ߎ��Ԃ�1�b������́���
      Float fTime = 100.0 * (double)Time / (double)pCore->GetSystemTimerBySec();
    }
  }

  // �R�A�̉��
  SAFE_RELEASE( pCore );

  // �V�X�e���̉��
  System::Finalize();

  return 0;
}
@endcode
*/
		virtual Uint64 GetSystemTimer( void ) = 0;

/**
@brief CPU�^�C�}�[��1�b�̃J�E���g�l�擾
@author �t���`
@return GetSystemTimer��1�b�̃J�E���g�l

@note
CPU�^�C�}�[��1�b�̎��Ԃ��擾���܂��B

@code
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
  ICore *pCore = NULL;

  // �V�X�e���̏�����
  System::Initialize();

  // �R�A�̐���
  pCore = System::CreateCore();

  // ������
  if ( pCore->Initialize( "Sample Program", FRAME_RATE_60 ) )
  {
    // �A�v���P�[�V�����J�n
    pCore->Start( 640, 480, true );

    // ���C�����[�v
    while ( pCore->Run() )
    {
      // ���Ԏ擾
      Uint64 Time = pCore->GetSystemTimer();

      // �Ȃ񂩏�������
 
      // �o�ߎ��Ԏ擾
      Time = pCore->GetSystemTimer() - Time;

      // �o�ߎ��Ԃ�1�b������́���
      Float fTime = 100.0 * (double)Time / (double)pCore->GetSystemTimerBySec();
    }
  }

  // �R�A�̉��
  SAFE_RELEASE( pCore );

  // �V�X�e���̉��
  System::Finalize();

  return 0;
}
@endcode
*/
		virtual Uint64 GetSystemTimerBySec( void ) = 0;

/**
@brief ��ʃT�C�Y�ύX
@author �t���`
@param Size		[in] ��ʃT�C�Y

@note
��ʃT�C�Y��ύX���܂��B

@code
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
  ICore *pCore = NULL;

  // �V�X�e���̏�����
  System::Initialize();

  // �R�A�̐���
  pCore = System::CreateCore();

  // ������
  if ( pCore->Initialize( "Sample Program", FRAME_RATE_60 ) )
  {
    // �A�v���P�[�V�����J�n
    pCore->Start( 640, 480, true );

    // ��ʃT�C�Y�ύX
    pCore->ResizeWindowSize( Math::Point2DI(320,240) );

    // ���C�����[�v
    while ( pCore->Run() )
    {
    }
  }

  // �R�A�̉��
  SAFE_RELEASE( pCore );

  // �V�X�e���̉��
  System::Finalize();

  return 0;
}
@endcode
*/
		virtual void ResizeWindowSize( Math::Point2DI Size ) = 0;

/**
@brief ��ʃ��[�h��ύX���܂�
@author �t���`

@note
��ʃ��[�h��ύX���܂��B

@code
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
  ICore *pCore = NULL;

  // �V�X�e���̏�����
  System::Initialize();

  // �R�A�̐���
  pCore = System::CreateCore();

  // ������
  if ( pCore->Initialize( "Sample Program", FRAME_RATE_60 ) )
  {
    // �A�v���P�[�V�����J�n
    pCore->Start( 640, 480, true );

    // ��ʃ��[�h�ύX
    pCore->ChangeScreenMode();

    // ���C�����[�v
    while ( pCore->Run() )
    {
    }
  }

  // �R�A�̉��
  SAFE_RELEASE( pCore );

  // �V�X�e���̉��
  System::Finalize();

  return 0;
}
@endcode
*/
		virtual void ChangeScreenMode( void ) = 0;

/**
@brief �E�B���h�E���[�h�`�F�b�N
@author �t���`

@note
���݂̉�ʃ��[�h���E�B���h�E���[�h���ǂ����𒲂ׂ܂�

@code
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
  ICore *pCore = NULL;

  // �V�X�e���̏�����
  System::Initialize();

  // �R�A�̐���
  pCore = System::CreateCore();

  // ������
  if ( pCore->Initialize( "Sample Program", FRAME_RATE_60 ) )
  {
    // �A�v���P�[�V�����J�n
    pCore->Start( 640, 480, true );

    // ��ʃ��[�h�擾
    if ( pCore->IsWindowMode() )
    {
    }

    // ���C�����[�v
    while ( pCore->Run() )
    {
    }
  }

  // �R�A�̉��
  SAFE_RELEASE( pCore );

  // �V�X�e���̉��
  System::Finalize();

  return 0;
}
@endcode
*/
		virtual Bool IsWindowMode( void ) = 0;

/**
@brief ���[�r�[�Đ�
@author �t���`
@param pFileName	[in] �t�@�C����
@param IsLoop		[in] ���[�vON/OFF
@param pCallback	[in] �����I���p�R�[���o�b�N�֐�

@note
�t����ʂŃ��[�r�[�̍Đ����s���܂��B<BR>
���[�r�[���I�����邩�ApCallback�֐�����false��Ԃ��܂ŏ����͖߂��Ă��܂���B

@code
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
  ICore *pCore = NULL;

  // �V�X�e���̏�����
  System::Initialize();

  // �R�A�̐���
  pCore = System::CreateCore();

  // ������
  if ( pCore->Initialize( "Sample Program", FRAME_RATE_60 ) )
  {
    // �A�v���P�[�V�����J�n
    pCore->Start( 640, 480, true );

    // ���[�r�[�Đ�
    if ( pCore->PlayMovie( "Sample.mpg", false, NULL ) )
    {
    }
  }

  // �R�A�̉��
  SAFE_RELEASE( pCore );

  // �V�X�e���̉��
  System::Finalize();

  return 0;
}
@endcode
*/
		virtual Bool PlayMovie( const char *pFileName, Bool IsLoop, Bool (__stdcall *pCallback)( void ) ) = 0;

/**
@brief �t���[���J�E���g���擾���܂��B
@author �t���`
@return �t���[����

@note
�N��������̑��t���[�������擾���܂��B

@code
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
  ICore *pCore = NULL;

  // �V�X�e���̏�����
  System::Initialize();

  // �R�A�̐���
  pCore = System::CreateCore();

  // ������
  if ( pCore->Initialize( "Sample Program", FRAME_RATE_60 ) )
  {
    // �A�v���P�[�V�����J�n
    pCore->Start( 640, 480, true );

    // ���C�����[�v
    while ( pCore->Run() )
    {
      // �N������̃t���[����
      Sint32 Cnt = pCore->GetSyncCount();
    }
  }

  // �R�A�̉��
  SAFE_RELEASE( pCore );

  // �V�X�e���̉��
  System::Finalize();

  return 0;
}
@endcode
*/
		virtual Sint32 GetSyncCount( void ) = 0;

/**
@brief �^�C�g���o�[�̏��\��ON/OFF
@author �t���`
@param IsEnable		[in] �\����ON/OFF

@note
�^�C�g���o�[�Ɍ��݂̏��̕\�����s�����ݒ肵�܂��B<BR>
<BR>
�f�t�H���g��false�ł��B

@code
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
  ICore *pCore = NULL;

  // �V�X�e���̏�����
  System::Initialize();

  // �R�A�̐���
  pCore = System::CreateCore();

  // ������
  if ( pCore->Initialize( "Sample Program", FRAME_RATE_60 ) )
  {
    // �^�C�g���o�[�ɏ��\��
    pCore->EnableDrawTitleInformation( true );

    // �A�v���P�[�V�����J�n
    pCore->Start( 640, 480, true );

    // ���C�����[�v
    while ( pCore->Run() )
    {
    }
  }

  // �R�A�̉��
  SAFE_RELEASE( pCore );

  // �V�X�e���̉��
  System::Finalize();

  return 0;
}
@endcode
*/
		virtual void EnableDrawTitleInformation( Bool IsEnable ) = 0;

/**
@brief �}�E�X�J�[�\���̕\��ON/OFF
@author �t���`
@param IsEnable		[in] �\����ON/OFF

@note
�}�E�X�J�[�\���̕\�����s�����ݒ肵�܂��B<BR>
<BR>
�f�t�H���g��false�ł��B

@code
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
  ICore *pCore = NULL;

  // �V�X�e���̏�����
  System::Initialize();

  // �R�A�̐���
  pCore = System::CreateCore();

  // ������
  if ( pCore->Initialize( "Sample Program", FRAME_RATE_60 ) )
  {
    // �}�E�X�J�[�\������
    pCore->EnableDrawMouseCursor( false );

    // �A�v���P�[�V�����J�n
    pCore->Start( 640, 480, true );

    // ���C�����[�v
    while ( pCore->Run() )
    {
    }
  }

  // �R�A�̉��
  SAFE_RELEASE( pCore );

  // �V�X�e���̉��
  System::Finalize();

  return 0;
}
@endcode
*/
		virtual void EnableDrawMouseCursor( Bool IsEnable ) = 0;

/**
@brief �O���t�B�b�N�J�[�h�C���^�[�t�F�C�X���擾
@author �t���`
@param GraphicCardNo	[in] �O���t�B�b�N�J�[�h�ԍ�
@return �O���t�B�b�N�J�[�h�C���^�[�t�F�C�X

@note
�O���t�B�b�N�J�[�h�Ɋւ��Ă̏��������s���A<BR>
���̃C���^�[�t�F�C�X���擾���܂��B<BR>
�ʏ�GraphicCardNo�ɂ�GRAPHIC_CARD_DEFAULT_NO���w�肵�܂��B<BR>
�uNV PerfHUD�v�̃C���X�g�[�����ꂽ���ł́A<BR>
GRAPHIC_CARD_NV_PERF_HUD���w�肷�邱�Ƃł����L���ɏo���܂��B

@code
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
  ICore *pCore = NULL;
  IGraphicCard *pGraphicCard = NULL;

  // �V�X�e���̏�����
  System::Initialize();

  // �R�A�̐���
  pCore = System::CreateCore();

  // ������
  if ( pCore->Initialize( "Sample Program", FRAME_RATE_60 ) )
  {
    // �A�v���P�[�V�����J�n
    pCore->Start( 640, 480, true );

    // �O���t�B�b�N�J�[�h�C���^�[�t�F�C�X�𐶐�
    pGraphicCard = pCore->CreateGraphicCard( GRAPHIC_CARD_DEFAULT_NO );

    // ���C�����[�v
    while ( pCore->Run() )
    {
    }
  }

  // �O���t�B�b�N�J�[�h�̉��
  SAFE_RELEASE( pGraphicCard );

  // �R�A�̉��
  SAFE_RELEASE( pCore );

  // �V�X�e���̉��
  System::Finalize();

  return 0;
}
@endcode
*/
		virtual IGraphicCard *CreateGraphicCard( eGraphicCardNo GraphicCardNo ) = 0;

/**
@brief �W���C�X�e�B�b�N�̐����擾
@author �t���`
@return �L���ȃW���C�X�e�B�b�N�̐�

@note
�������ɐ��������L���ȃW���C�X�e�B�b�N�Ȃ̐����擾���܂��B

@code
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
  ICore *pCore = NULL;

  // �V�X�e���̏�����
  System::Initialize();

  // �R�A�̐���
  pCore = System::CreateCore();

  // ������
  if ( pCore->Initialize( "Sample Program", FRAME_RATE_60 ) )
  {
    // �A�v���P�[�V�����J�n
    pCore->Start( 640, 480, true );

    // �W���C�X�e�B�b�N�����擾
    Sint32 Count = pCore->GetJoystickCount();

    // ���C�����[�v
    while ( pCore->Run() )
    {
    }
  }

  // �R�A�̉��
  SAFE_RELEASE( pCore );

  // �V�X�e���̉��
  System::Finalize();

  return 0;
}
@endcode
*/
		virtual Sint32 GetJoystickCount( void ) = 0;

/**
@brief �}�E�X�C���^�[�t�F�C�X���擾
@author �t���`
@return �}�E�X�C���^�[�t�F�C�X

@note
ICore�̏��L����E�B���h�E�Ɋ֘A�t����ꂽ�}�E�X�̏��������s���A<BR>
���̃C���^�[�t�F�C�X���擾���܂��B<BR>
�}�E�X�Ɋւ��Ă̏��͂��̃C���^�[�t�F�C�X�o�R�Ŏ擾���ĉ������B

@code
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
  ICore *pCore = NULL;
  Peripheral::IMouse *pMouse = NULL;

  // �V�X�e���̏�����
  System::Initialize();

  // �R�A�̐���
  pCore = System::CreateCore();

  // ������
  if ( pCore->Initialize( "Sample Program", FRAME_RATE_60 ) )
  {
    // �A�v���P�[�V�����J�n
    pCore->Start( 640, 480, true );

    // �}�E�X�̎擾
    pMouse = pCore->GetMouse();

    // ���C�����[�v
    while ( pCore->Run() )
    {
    }
  }

  // �}�E�X�̉��
  SAFE_RELEASE( pMouse );

  // �R�A�̉��
  SAFE_RELEASE( pCore );

  // �V�X�e���̉��
  System::Finalize();

  return 0;
}
@endcode
*/
		virtual Peripheral::IMouse *GetMouse( void ) = 0;

/**
@brief �L�[�{�[�h�C���^�[�t�F�C�X���擾
@author �t���`
@return �L�[�{�[�h�C���^�[�t�F�C�X

@note
ICore�̏��L����E�B���h�E�Ɋ֘A�t����ꂽ�L�[�{�[�h�̏��������s���A<BR>
���̃C���^�[�t�F�C�X���擾���܂��B<BR>
�L�[�{�[�h�Ɋւ��Ă̏��͂��̃C���^�[�t�F�C�X�o�R�Ŏ擾���ĉ������B

@code
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
  ICore *pCore = NULL;
  Peripheral::IKeyboard *pKeyboard = NULL;

  // �V�X�e���̏�����
  System::Initialize();

  // �R�A�̐���
  pCore = System::CreateCore();

  // ������
  if ( pCore->Initialize( "Sample Program", FRAME_RATE_60 ) )
  {
    // �A�v���P�[�V�����J�n
    pCore->Start( 640, 480, true );

    // �L�[�{�[�h�̎擾
    pKeyboard = pCore->GetKeyboard();

    // ���C�����[�v
    while ( pCore->Run() )
    {
    }
  }

  // �L�[�{�[�h�̉��
  SAFE_RELEASE( pKeyboard );

  // �R�A�̉��
  SAFE_RELEASE( pCore );

  // �V�X�e���̉��
  System::Finalize();

  return 0;
}
@endcode
*/
		virtual Peripheral::IKeyboard *GetKeyboard( void ) = 0;

/**
@brief �W���C�X�e�B�b�N�C���^�[�t�F�C�X���擾
@author �t���`
@param No	[in] �W���C�X�e�B�b�N�ԍ�(0�`15)
@return �W���C�X�e�B�b�N�C���^�[�t�F�C�X

@note
ICore�̏��L����E�B���h�E�Ɋ֘A�t����ꂽ�W���C�X�e�B�b�N�̏��������s���A<BR>
���̃C���^�[�t�F�C�X���擾���܂��B<BR>
�W���C�X�e�B�b�N�Ɋւ��Ă̏��͂��̃C���^�[�t�F�C�X�o�R�Ŏ擾���ĉ������B

@code
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
  ICore *pCore = NULL;
  Peripheral::IJoystick *pJoystick = NULL;

  // �V�X�e���̏�����
  System::Initialize();

  // �R�A�̐���
  pCore = System::CreateCore();

  // ������
  if ( pCore->Initialize( "Sample Program", FRAME_RATE_60 ) )
  {
    // �A�v���P�[�V�����J�n
    pCore->Start( 640, 480, true );

    // �W���C�X�e�B�b�N�̎擾
    pJoystick = pCore->GetJoystick( 0 );

    // ���C�����[�v
    while ( pCore->Run() )
    {
    }
  }

  // �W���C�X�e�B�b�N�̉��
  SAFE_RELEASE( pJoystick );

  // �R�A�̉��
  SAFE_RELEASE( pCore );

  // �V�X�e���̉��
  System::Finalize();

  return 0;
}
@endcode
*/
		virtual Peripheral::IJoystick *GetJoystick( Sint32 No ) = 0;

/**
@brief ���͓����C���^�[�t�F�C�X���擾
@author �t���`
@param No					[in] �K�p����W���C�X�e�B�b�N�ԍ�
@param KeyRepeatStartTime	[in] �L�[���s�[�g�J�n�t���[��
@param KeyRepeatInterval	[in] �L�[���s�[�g�Ԋu�t���[��
@return ���͓����C���^�[�t�F�C�X

@note
ICore�̏��L����E�B���h�E�Ɋ֘A�t����ꂽ�W���C�X�e�B�b�N���L�[�{�[�h�̏��������s���A<BR>
���̃C���^�[�t�F�C�X���擾���܂��B<BR>
�W���C�X�e�B�b�N�ƃL�[�{�[�h�𓝍����Ĉ������Ƃ̂ł���C���^�[�t�F�C�X�ł��B

@code
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
  ICore *pCore = NULL;
  Peripheral::IInputController *pInputController = NULL;

  // �V�X�e���̏�����
  System::Initialize();

  // �R�A�̐���
  pCore = System::CreateCore();

  // ������
  if ( pCore->Initialize( "Sample Program", FRAME_RATE_60 ) )
  {
    // �A�v���P�[�V�����J�n
    pCore->Start( 640, 480, true );

    // ���̓R���g���[���[�̎擾
    pInputController = pCore->GetInputController( 0, 30, 5 );

    // ���C�����[�v
    while ( pCore->Run() )
    {
    }
  }

  // ���̓R���g���[���[�̉��
  SAFE_RELEASE( pInputController );

  // �R�A�̉��
  SAFE_RELEASE( pCore );

  // �V�X�e���̉��
  System::Finalize();

  return 0;
}
@endcode
*/
		virtual Peripheral::IInputController *GetInputController( Sint32 No, Sint32 KeyRepeatStartTime, Sint32 KeyRepeatInterval ) = 0;

/**
@brief �t�@�C���}�l�[�W���[�C���^�[�t�F�C�X����
@author �t���`
@return �t�@�C���}�l�[�W���[�C���^�[�t�F�C�X

@note
�V�K�̃t�@�C���}�l�[�W���[�C���^�[�t�F�C�X�𐶐����܂��B<BR>
�t�@�C���̃p�X�Ȃǂ̐ݒ�͑S��IFileManager���o�R���čs���܂��B
�擾�����t�@�C���}�l�[�W���[�C���^�[�t�F�C�X�͎g�p�I����ɂ͕K��Release()���ĉ������B�B

@code
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
  ICore *pCore = NULL;
  File::IFileManager *pFileMgr = NULL;

  // �V�X�e���̏�����
  System::Initialize();

  // �R�A�̐���
  pCore = System::CreateCore();

  // ������
  if ( pCore->Initialize( "Sample Program", FRAME_RATE_60 ) )
  {
    // �A�v���P�[�V�����J�n
    pCore->Start( 640, 480, true );

    // �t�@�C���}�l�[�W���[�̐���
    pFileMgr = pCore->CreateFileManager();

    // �t�@�C���}�l�[�W���[��ݒ�
    pCore->SetFileManager( pFileMgr );

    // ���C�����[�v
    while ( pCore->Run() )
    {
    }
  }

  // �t�@�C���}�l�[�W���[�̉��
  SAFE_RELEASE( pFileMgr );

  // �R�A�̉��
  SAFE_RELEASE( pCore );

  // �V�X�e���̉��
  System::Finalize();

  return 0;
}
@endcode
*/
		virtual File::IFileManager *CreateFileManager( void ) = 0;

/**
@brief �t�@�C���}�l�[�W���[�C���^�[�t�F�C�X�擾
@author �t���`
@return �t�@�C���}�l�[�W���[�C���^�[�t�F�C�X

@note
���ݐݒ肳��Ă���t�@�C���}�l�[�W���[�C���^�[�t�F�C�X���擾���܂��B<BR>
�ݒ�ς݂̃t�@�C���}�l�[�W���[�C���^�[�t�F�C�X�ւ̃A�N�Z�X���s���ꍇ�Ɏg�p���Ă��������B

@code
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
  ICore *pCore = NULL;
  File::IFileManager *pFileMgr = NULL;

  // �V�X�e���̏�����
  System::Initialize();

  // �R�A�̐���
  pCore = System::CreateCore();

  // ������
  if ( pCore->Initialize( "Sample Program", FRAME_RATE_60 ) )
  {
    // �A�v���P�[�V�����J�n
    pCore->Start( 640, 480, true );

    // �t�@�C���}�l�[�W���[�̐���
    pFileMgr = pCore->CreateFileManager();

    // �t�@�C���}�l�[�W���[��ݒ�
    pCore->SetFileManager( pFileMgr );

    // �t�@�C���p�X�ݒ�
    pCore->GetFileMgrPointer()->SetCurrentPath( "Data\\Texture" );

    // ���C�����[�v
    while ( pCore->Run() )
    {
    }
  }

  // �t�@�C���}�l�[�W���[�̉��
  SAFE_RELEASE( pFileMgr );

  // �R�A�̉��
  SAFE_RELEASE( pCore );

  // �V�X�e���̉��
  System::Finalize();

  return 0;
}
@endcode
*/
		virtual File::IFileManager *GetFileMgrPointer( void ) = 0;

/**
@brief �t�@�C���}�l�[�W���[�C���^�[�t�F�C�X�ݒ�
@author �t���`
@param pMgr	[in] �t�@�C���}�l�[�W���[�C���^�[�t�F�C�X

@note
�t�@�C���̓ǂݍ��݂Ɏg����t�@�C���}�l�[�W���[�C���^�[�t�F�C�X��ݒ肵�܂��B<BR>
�t�@�C���̓ǂݍ��݂͂��̃}�l�[�W���[���o�R���čs���̂ŁA<BR>
�t�@�C���̓ǂݍ��݂��s���ꍇ�͕K���ݒ肵�Ă��������B<BR>
���ɐݒ肳��Ă���}�l�[�W���[�͓����ŉ������܂��B

@code
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
  ICore *pCore = NULL;
  File::IFileManager *pFileMgr = NULL;

  // �V�X�e���̏�����
  System::Initialize();

  // �R�A�̐���
  pCore = System::CreateCore();

  // ������
  if ( pCore->Initialize( "Sample Program", FRAME_RATE_60 ) )
  {
    // �A�v���P�[�V�����J�n
    pCore->Start( 640, 480, true );

    // �t�@�C���}�l�[�W���[�̐���
    pFileMgr = pCore->CreateFileManager();

    // �t�@�C���}�l�[�W���[��ݒ�
    pCore->SetFileManager( pFileMgr );

    // ���C�����[�v
    while ( pCore->Run() )
    {
    }
  }

  // �t�@�C���}�l�[�W���[�̉��
  SAFE_RELEASE( pFileMgr );

  // �R�A�̉��
  SAFE_RELEASE( pCore );

  // �V�X�e���̉��
  System::Finalize();

  return 0;
}
@endcode
*/
		virtual void SetFileManager( File::IFileManager *pMgr ) = 0;

/**
@brief �T�E���h�t�@�C���ǂݍ���
@author �t���`
@param pFileName		[in] �T�E���h�t�@�C����(wav)
@param LayerCount		[in] ���C���[���i���������\���j
@param IsGlobalScope	[in] �T�E���h�̃X�R�[�v
@retval	�T�E���h�C���^�[�t�F�C�X

@note
ICore�̏��L����E�B���h�E�Ɋ֘A�t����ꂽ�T�E���h���擾���܂��B<BR>
IsGlobalScope��true��n���ƁA�E�B���h�E�̃t�H�[�J�X�Ɋ֌W�Ȃ��Đ�����܂��B<BR>
LayerCount�Ŏw�肵�������̃��C���[������Ŏ����܂��B<BR>
����͓���̃o�b�t�@��ʁX�̃^�C�~���O�ōĐ��E��~����<BR>
������s�����߂̋@�\�ł����A�P�̃o�b�t�@���g���܂킷�̂�<BR>
�������g�p�ʂ͂P�̏ꍇ�Ɠ����ł��B<BR>
�g�p�̏I�������T�E���h�͕K��Release()���ĉ������B

@code
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
  ICore *pCore = NULL;
  Sound::ISound *pSound = NULL;

  // �V�X�e���̏�����
  System::Initialize();

  // �R�A�̐���
  pCore = System::CreateCore();

  // ������
  if ( pCore->Initialize( "Sample Program", FRAME_RATE_60 ) )
  {
    // �A�v���P�[�V�����J�n
    pCore->Start( 640, 480, true );

    // �T�E���h�̐���
    pSound = CreateSoundFromFile( "Sample.wav", 4, false );

    // ���C�����[�v
    while ( pCore->Run() )
    {
    }
  }

  // �T�E���h�̉��
  SAFE_RELEASE( pSound );

  // �R�A�̉��
  SAFE_RELEASE( pCore );

  // �V�X�e���̉��
  System::Finalize();

  return 0;
}
@endcode
*/
		virtual Sound::ISound *CreateSoundFromFile( const char *pFileName, Sint32 LayerCount, Bool IsGlobalScope ) = 0;

/**
@brief �T�E���h�t�@�C���ǂݍ���
@author �t���`
@param pFileName		[in] �T�E���h�t�@�C����
@param IsGlobalScope	[in] �T�E���h�̃X�R�[�v
@param pPluginName		[in] �v���O�C����
@retval		�T�E���h�C���^�[�t�F�C�X

@note
ICore�̏��L����E�B���h�E�Ɋ֘A�t����ꂽ�T�E���h���擾���܂��B<BR>
IsGlobalScope��true��n���ƁA�E�B���h�E�̃t�H�[�J�X�Ɋ֌W�Ȃ��Đ�����܂��B<BR>
�g�p�̏I�������T�E���h�͕K��Release()���ĉ������B

@code
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
  ICore *pCore = NULL;
  Sound::IStreamSound *pSound = NULL;

  // �V�X�e���̏�����
  System::Initialize();

  // �R�A�̐���
  pCore = System::CreateCore();

  // ������
  if ( pCore->Initialize( "Sample Program", FRAME_RATE_60 ) )
  {
    // �A�v���P�[�V�����J�n
    pCore->Start( 640, 480, true );

    // �T�E���h�̐���
    pSound = CreateStreamSoundFromFile( "Sample.ogg", false, "OggVorbis" );

    // ���C�����[�v
    while ( pCore->Run() )
    {
    }
  }

  // �T�E���h�̉��
  SAFE_RELEASE( pSound );

  // �R�A�̉��
  SAFE_RELEASE( pCore );

  // �V�X�e���̉��
  System::Finalize();

  return 0;
}
@endcode
*/
		virtual Sound::IStreamSound *CreateStreamSoundFromFile( const char *pFileName, Bool IsGlobalScope, const char *pPluginName ) = 0;

/**
@brief �t�@�C�o�[�R���g���[���[����
@author �t���`
@param Max	[in] �t�@�C�o�[�ő吔
@return �t�@�C�o�[�R���g���[���[�C���^�[�t�F�C�X

@note
�t�@�C�o�[�R���g���[���[���擾���܂��B<BR>
ICore�ɂP�������݂���2��ڈȍ~�͊����̃C���^�[�t�F�C�X��Ԃ��܂��B

@code
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
  ICore *pCore = NULL;
  Fiber::IFiberController *pFiber = NULL;

  // �V�X�e���̏�����
  System::Initialize();

  // �R�A�̐���
  pCore = System::CreateCore();

  // ������
  if ( pCore->Initialize( "Sample Program", FRAME_RATE_60 ) )
  {
    // �A�v���P�[�V�����J�n
    pCore->Start( 640, 480, true );

    // �t�@�C�o�[�R���g���[���[�̐���
    pFiber = pCore->CreateFiberController( 8 );

    // ���C�����[�v
    while ( pCore->Run() )
    {
    }
  }

  // �t�@�C�o�[�̉��
  SAFE_RELEASE( pFiber );

  // �R�A�̉��
  SAFE_RELEASE( pCore );

  // �V�X�e���̉��
  System::Finalize();

  return 0;
}
@endcode
*/
		virtual Fiber::IFiberController *CreateFiberController( Sint32 Max ) = 0;
	};
}

#pragma once


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Renderer
{
	/**
		@brief �R���W�������ʕێ��p
		@author �t���`

		�R���W�����̌��ʂ�ێ����邽�߂̍\���̂ł��B
	*/
	struct SCollisionResult
	{
		Uint32 Attribute;				///< ����
		Math::Vector3D vHitPosition;	///< �Փ˓_
		Math::Vector3D vNormal;			///< �Փ˖ʂ̖@��
		Math::Vector3D vTriangle[3];	///< �ՓˎO�p�`���Ȃ����_
		CColor Color[3];				///< �ՓˎO�p�`���Ȃ����_�̐F
	};

	/**
		@brief �R���W�������ʕێ��p
		@author �t���`

		�R���W�����̌��ʂ�ێ����邽�߂̍\���̂ł��B
	*/
	struct SCollisionResultExtend
	{
		Uint32 Attribute;					///< �����iAlmeria��ł̃}�e���A���̔ԍ��j
		Math::Vector3D vHitPosition;		///< �Փ˓_
		Math::Vector3D vNormal;				///< �Փ˖ʂ̖@��
		Math::Vector3D vTriangle[3];		///< �ՓˎO�p�`���Ȃ����_
		Math::Vector3D vRefrectDirection;	///< ���ˌ�̕���
		Math::Vector3D vRefrectPosition;	///< ���ˌ�̈ʒu
		Math::Vector3D vSlidePosition;		///< �ʏ���X���C�h�����ꍇ�̈ʒu
		CColor Color[3];					///< �ՓˎO�p�`���Ȃ����_�̐F
	};

	/**
		@brief �R���W�������ʕێ��p
		@author �t���`

		�R���W�����̌��ʂ�ێ����邽�߂̍\���̂ł��B
	*/
	struct SCollisionResultSphere
	{
		Math::Vector3D vHitPosition;	///< �Փ˓_
		Math::Vector3D vNormal;			///< �Փ˖ʂ̖@��
	};

	/**
		@brief �R���W�������ʕێ��p
		@author �t���`

		�R���W�����̌��ʂ�ێ����邽�߂̍\���̂ł��B
	*/
	struct SCollisionResultSphereExtend
	{
		Math::Vector3D vHitPosition;		///< �Փ˓_
		Math::Vector3D vNormal;				///< �Փ˖ʂ̖@��
		Math::Vector3D vRefrectDirection;	///< ���ˌ�̕���
		Math::Vector3D vRefrectPosition;	///< ���ˌ�̈ʒu
		Math::Vector3D vSlidePosition;		///< �ʏ���X���C�h�����ꍇ�̈ʒu
	};

	/**
		@brief 2D�`��p���_
		@author �t���`

		2D�`��p�̊�{���_�f�[�^�ł��B<BR>
		���IPoint2D/ILine2D�N���X�Ŏg�p���܂��B<BR>
		VERTEX_ELEMENT_PRIMITIVE�t���O���w�肵�č쐬����<BR>
		���_��`�ł͂��̍\���̂��g���܂��B
	*/
	struct SVertex2D
	{
		Math::Vector4D Pos;		///< �ʒu
		CColor Col;				///< ���_�F
	};

	/**
		@brief 2D�`��p���_
		@author �t���`

		2D�`��p�̃e�N�X�`��UV�t�����_�f�[�^�ł��B<BR>
		���IPrimitive2D/ISprite2D/IFontSprite2D�N���X�Ŏg�p���܂��B<BR>
		VERTEX_ELEMENT_SPRITE�t���O���w�肵�č쐬����<BR>
		���_��`�ł͂��̍\���̂��g���܂��B
	*/
	struct SVertex2DTex
	{
		Math::Vector4D Pos;		///< �ʒu
		CColor Col;				///< ���_�F
		Math::Vector2D Tex[2];	///< �e�N�X�`��UV
	};

	/**
		@brief 3D�`��p���_
		@author �t���`

		3D�`��p�̊�{���_�f�[�^�ł��B<BR>
		VERTEX_ELEMENT_BASE�t���O���w�肵�č쐬����<BR>
		���_��`�ɑ΂��Ē�`����܂��B
	*/
	struct SVertex3DBase
	{
		Math::Vector3D Pos;		///< �ʒu
		CColor Col;				///< ���_�F
	};

	/**
		@brief 3D�`��p���_
		@author �t���`

		3D�`��p�̃e�N�X�`��UV�p���_�f�[�^�ł��B<BR>
		VERTEX_ELEMENT_3DTEXTURE�t���O���w�肵�č쐬����<BR>
		���_��`�ɑ΂��Ē�`����܂��B
	*/
	struct SVertex3DTexture
	{
		Math::Vector2D TexColor;		///< �e�N�X�`��UV
		Math::Vector2D TexLight;		///< �e�N�X�`��UV
	};

	/**
		@brief 3D�`��p���_
		@author �t���`

		3D�`��p�̃��C�e�B���O�p���_�f�[�^�ł��B<BR>
		VERTEX_ELEMENT_3DLIGHT�t���O���w�肵�č쐬����<BR>
		���_��`�ɑ΂��Ē�`����܂��B
	*/
	struct SVertex3DLight
	{
		Math::Vector3D Norm;		///< �@��
	};

	/**
		@brief 3D�`��p���_
		@author �t���`

		3D�`��p�̃o���v�}�b�s���O�p���_�f�[�^�ł��B<BR>
		VERTEX_ELEMENT_3DBUMP�t���O���w�肵�č쐬����<BR>
		���_��`�ɑ΂��Ē�`����܂��B
	*/
	struct SVertex3DBump
	{
		Math::Vector3D Tangent;	///< �ڐ�
	};

	/**
		@brief 3D�`��p���_
		@author �t���`

		3D�`��p�̃X�L�j���O�p���_�f�[�^�ł��B<BR>
		VERTEX_ELEMENT_3DANIMATION�t���O���w�肵�č쐬����<BR>
		���_��`�ɑ΂��Ē�`����܂��B
		�P�̒��_�ɂ��Q�̃{�[���̌v�Z���s���܂��B
	*/
	struct SVertex3DAnimation
	{
		Float Weight;		///< �E�F�C�g�i�P�Ԗڂ̃E�F�C�g�������w��A�Q�Ԗڂ̓V�F�[�_�[����1.0-Weight�ŎZ�o�j
		Uint8 Index[4];		///< �{�[���C���f�b�N�X
	};

	/**
		@brief ���C���v���~�e�B�u�p���_�f�[�^
		@author �t���`
	*/
	struct SLineVertex2D
	{
		SVertex2D v1;
		SVertex2D v2;
	};

	/**
		@brief �v���~�e�B�u�p���_�f�[�^
		@author �t���`
	*/
	struct SPrimitiveVertex2D
	{
		SVertex2DTex v1;
		SVertex2DTex v2;
		SVertex2DTex v3;
	};

	/**
		@brief 3D�v���~�e�B�u��{�f�[�^
		@author �t���`

		ILine3D�ŕ`����s���ۂɎg�p���钸�_�f�[�^�B
	*/
	struct SLineVertex3D
	{
		SVertex3DBase v1;			///< �ʒu�E���_�F
		SVertex3DBase v2;			///< �ʒu�E���_�F
	};

	/**
		@brief �e�N�X�`�������p�R���t�B�O
		@author �t���`

		�e�N�X�`���������ɎQ�Ƃ����<BR>
		�쐬�p�p�����[�^�[����`�����N���X�ł��B
	*/
	class CTextureConfig
	{
	private:
		eSurfaceFormat m_Format;	///< �T�[�t�F�C�X�t�H�[�}�b�g
		CColor m_KeyColor;			///< �J���[�L�[�̐F
		Bool m_IsMipmap;			///< �~�b�v�}�b�v
		Bool m_IsHalfSize;			///< �����T�C�Y

	public:
		/**
			@brief �R���X�g���N�^
		*/
		CTextureConfig()
			: m_Format		( FORMAT_TEXTURE_32BIT )
			, m_KeyColor	( 0x00000000 )
			, m_IsMipmap	( false )
			, m_IsHalfSize	( false )
		{
		}

		/**
			@brief �f�X�g���N�^
		*/
		~CTextureConfig()
		{
		}

		/**
			@brief �J���[�L�[�i�����F�j�ݒ�
			@author �t���`
			@param Col	[in] �J���[�L�[�i�����F�j�Ɏg���F<BR>0x00000000�̎��J���[�L�[�i�����F�jOFF

			�e�N�X�`����ǂݍ��񂾍ۂɎw�肵���F�̃A���t�@��0�ɂ��A<BR>
			�J���[�L�[�������s�����悤�ɂ��̃s�N�Z����`��<BR>
			����Ȃ��悤�ɂ��܂��B
		*/
		void SetColorKey( CColor Col )
		{
			m_KeyColor = Col;
		}

		/**
			@brief �T�[�t�F�C�X�t�H�[�}�b�g�ݒ�
			@author �t���`
			@param Fmt	[in] �T�[�t�F�C�X�t�H�[�}�b�g

			�e�N�X�`���ǂݍ��ݎ��̃T�[�t�F�C�X�t�H�[�}�b�g��ݒ肵�܂��B<BR>
			�����ȃt�H�[�}�b�g���w�肵���ꍇ�A�쐬�͎��s���܂��B
		*/
		void SetFormat( eSurfaceFormat Fmt )
		{
			m_Format = Fmt;
		}

		/**
			@brief �~�b�v�}�b�v�L���ݒ�
			@author �t���`
			@param IsEnable	[in] �~�b�v�}�b�v�L��

			�e�N�X�`���ǂݍ��ݎ��̃~�b�v�}�b�v�̗L����ݒ肵�܂��B
		*/
		void SetMipmapEnable( Bool IsEnable ) 
		{
			m_IsMipmap = IsEnable;
		}

		/**
			@brief 1/2�T�C�Y�e�N�X�`���L���ݒ�
			@author �t���`
			@param IsEnable	[in] 1/2�T�C�Y�e�N�X�`���L��

			�e�N�X�`���ǂݍ��ݎ���1/2�T�C�Y�e�N�X�`���̗L����ݒ肵�܂��B<BR>
			���̃t���O�͏����Ƀe�N�X�`���̎g�p�ʂ�}���鎞�Ɏg���܂��B
		*/
		void SetHalfSizeEnable( Bool IsEnable ) 
		{
			m_IsHalfSize = IsEnable;
		}

		/**
			@brief �J���[�L�[���擾
			@author �t���`
			@retval	0		�J���[�L�[�������s��Ȃ�
			@retval	0�ȊO	���̐F���J���[�L�[�Ƃ���
		*/
		CColor GetColorKey( void )
		{
			return m_KeyColor;
		}

		/**
			@brief �T�[�t�F�C�X�t�H�[�}�b�g���擾���܂�
			@author �t���`
			@return �T�[�t�F�C�X�t�H�[�}�b�g
		*/
		eSurfaceFormat GetFormat( void )
		{
			return m_Format;
		}

		/**
			@brief �~�b�v�}�b�v�̗L�����擾���܂�
			@author �t���`
			@return �~�b�v�}�b�v�̗L��
		*/
		Bool IsMipmap( void )
		{
			return m_IsMipmap;
		}

		/**
			@brief 1/2�T�C�Y�e�N�X�`���̗L�����擾���܂�
			@author �t���`
			@return 1/2�T�C�Y�e�N�X�`���̗L��
		*/
		Bool IsHalfSize( void )
		{
			return m_IsHalfSize;
		}
	};

	/**
		@brief �����_���[�C���^�[�t�F�C�X
		@author �t���`

		��ʂɑ΂���S�Ă̕`�揈�����Ǘ����܂��B<BR>
		�`��p�̊e��N���X���S�Ă��̃N���X����擾���܂�<BR>
		�܂����̃C���^�[�t�F�C�X�͂P��IDevice�C���^�[�t�F�C�X�ɑ΂��ĂP�����쐬����܂���B
	*/
	class IRender
	{
	public:
		virtual ~IRender() {}

		/**
			@brief �L�����`�F�b�N
			@author �t���`
			@retval true ����
			@retval false �L��

			�C���^�[�t�F�C�X���L�����������𒲂ׂ܂��B
		*/
		virtual Bool IsInvalid( void ) = 0;

		/**
			@brief �Q�ƃJ�E���^�f�N�������g
			@author �t���`
			@return �f�N�������g��̎Q�ƃJ�E���g

			�Q�ƃJ�E���^���f�N�������g���A<BR>
			�Q�ƃJ�E���g��0�ɂȂ������_�Ń��������������܂��B
		*/
		virtual Sint32 Release( void ) = 0;

		/**
			@brief �Q�ƃJ�E���^�C���N�������g
			@author �t���`
			@return �C���N�������g��̎Q�ƃJ�E���g

			�Q�ƃJ�E���^���C���N�������g���܂��B<BR>
			�C���N�������g�����Q�ƃJ�E���g��Release()���ĂԂ��Ƃɂ��f�N�������g����܂��B<BR>
			AddRef()�������C���^�[�t�F�C�X�͕K��Release()�ŉ�����Ă��������B
		*/
		virtual Sint32 AddRef( void	) = 0;

		/**
			@brief �V�F�[�_�[�o�[�W�����`�F�b�N
			@author �t���`
			@retval false	���Ή�
			@retval true	�Ή�

			�V�F�[�_�[���f��2.0�ɑΉ����Ă��邩�ǂ����𒲂ׂ܂��B
		*/
		virtual Bool IsSupportedPS20( void ) = 0;

		/**
			@brief �V�F�[�_�[�o�[�W�����`�F�b�N
			@author �t���`
			@retval false	���Ή�
			@retval true	�Ή�

			�V�F�[�_�[���f��3.0�ɑΉ����Ă��邩�ǂ����𒲂ׂ܂��B
		*/
		virtual Bool IsSupportedPS30( void ) = 0;

		/**
			@brief �s�N�Z���V�F�[�_�[�̖��ߐ��`�F�b�N
			@author �t���`
			@parma Count	[in] ���ߐ�
			@retval false	���Ή�
			@retval true	�Ή�

			�w�肵�����ߐ��ɑΉ����Ă���ғ��𒲂ׂ܂��B
		*/
		virtual Bool IsPixelShaderInstructionSupport( Sint32 Count ) = 0;

		/**
			@brief �s�N�Z���V�F�[�_�[�̖��ߐ��`�F�b�N
			@author �t���`
			@retval �}���`�����_�����O�^�[�Q�b�g��

			�}���`�����_�����O�^�[�Q�b�g�̑Ή������擾���܂��B
		*/
		virtual Sint32 GetMRTs( void ) = 0;

		/**
			@brief �����_�����O�^�[�Q�b�g�N���A
			@author �t���`
			@param Color	[in] �N���A�Ɏg���F
			@retval false	���s
			@retval true	����

			�ݒ肳�ꂽ�����_�����O�^�[�Q�b�g���w�肳�ꂽ�F�ŃN���A�[���܂��B
		*/
		virtual Bool Clear( CColor Color = 0x00000000 ) = 0;

		/**
			@brief �[�x�X�e���V���o�b�t�@�N���A
			@author �t���`
			@retval false	���s
			@retval true	����

			�ݒ肳�ꂽ�[�x�X�e���V���o�b�t�@���N���A���܂��B<BR>
			�[�x�X�e���V���o�b�t�@�����݂��Ȃ��ꍇ���s���܂��B
		*/
		virtual Bool ClearDepthStencil( void ) = 0;

		/**
			@brief �`��̈�V�U�����O
			@author �t���`
			@param pRect		[in] �`��̈�(NULL�ŉ���)

			�w�肵���`��̈���ɂ��������_�����O����Ȃ��悤�ɂȂ�܂��B<BR>
			�r���[�|�[�g�ɂ͉e����^���܂���B
		*/
		virtual void SetScissorRect( const Math::Rect2DI *pRect ) = 0;

		/**
			@brief �f�o�C�X���Z�b�g���R�[���o�b�N�֐��o�^
			@author �t���`
			@param pCallback	[in] �R�[���o�b�N�֐�

			�f�o�C�X���X�g���ɃR�[���o�b�N�����֐���ݒ肵�܂��B<BR>
			�ʏ�̗p�r�ł͎g�p����K�v�͂���܂���B<BR>
			�Ȃ�炩�̗��R�Œ��ڃf�o�C�X�𑀍삷�鎞�ɂ̂ݎg�p���Ă��������B
		*/
		virtual void SetCallbackDeviceReset( void (*pCallback)( void ) ) = 0;

		/**
			@brief ���p�\��VRAM�c�ʂ��擾
			@author �t���`
			@return VRAM�c��

			�g�p�\��VRAM�c�ʂ��擾���܂��B<BR>
			���̒l�̓r�f�I�J�[�h�ɓ��ڂ���Ă���VRAM�ʂƂ͈Ⴂ�A<BR>
			�h���C�o���g�p�\�ȗe�ʂ�Ԃ��܂��B
		*/
		virtual Float GetRestVRAM( void ) = 0;

		/**
			@brief �f�o�C�X���X�g���R�[���o�b�N�֐��o�^
			@author �t���`
			@param pCallback	[in] �R�[���o�b�N�֐�

			�f�o�C�X���X�g�A���ɃR�[���o�b�N�����֐���ݒ肵�܂��B<BR>
			�ʏ�̗p�r�ł͎g�p����K�v�͂���܂���B<BR>
			�Ȃ�炩�̗��R�Œ��ڃf�o�C�X�𑀍삷�鎞�ɂ̂ݎg�p���Ă��������B
		*/
		virtual void SetCallbackDeviceRestore( void (*pCallback)( void ) ) = 0;

		/**
			@brief �J���[�������݃}�X�N��ݒ�
			@author �t���`
			@param IsAlpha		[in] �A���t�@�������݃}�X�NON/OFF
			@param IsRed		[in] �Ԑ����������݃}�X�NON/OFF
			@param IsGreen		[in] �ΐ����������݃}�X�NON/OFF
			@param IsBlue		[in] �����������݃}�X�NON/OFF

			�t���O��true�ɂ����F�ւ̏������݂��s���܂��B<BR>
			false�ɂ���Ƃ��̐F�ւ̏������݂��s���܂���B
		*/
		virtual void SetColorWriteEnable( Bool IsAlpha, Bool IsRed, Bool IsGreen, Bool IsBlue ) = 0;

		/**
			@brief �����f�o�C�X���擾
			@author �t���`
			@return		�f�o�C�X�̃|�C���^�[

			�����Ŏg�p���Ă���f�o�C�X�����I�Ɏ擾���܂��B<BR>
			�ʏ�̗p�r�ł͎g�p����K�v�͂���܂���B<BR>
			�Ȃ�炩�̗��R�Œ��ڃf�o�C�X�𑀍삷�鎞�ɂ̂ݎg�p���Ă��������B<BR>
			�����Ŏ擾�����f�o�C�X���o�R���ăX�e�[�g�Ȃǂ̕ύX���s�����ꍇ�A<BR>
			���̌��Selene�ł̃X�e�[�g�Ǘ��̓T�|�[�g�O�ɂȂ�܂��B<BR>
		*/
		virtual void *GetDriverDevicePointer( void ) = 0;

		/**
			@brief �����_�����O�^�[�Q�b�g�̓��e��PNG�t�@�C���ɕۑ�
			@author �t���`
			@param pFileName	[in] �t�@�C����(*.png)

			�����_�����O�^�[�Q�b�g�̓��e��PNG�t�@�C���Ƃ��ĕۑ����܂��B<BR>
			���̋@�\���g���ɂ̓����_�����O�^�[�Q�b�g�����b�N�\�ȃT�[�t�F�C�X�łȂ���΂����܂���B
		*/
		virtual void SaveToFilePNG( const char *pFileName ) = 0;

		/**
			@brief �����_�����O�^�[�Q�b�g�̓��e��JPG�t�@�C���ɕۑ�
			@author �t���`
			@param pFileName	[in] �t�@�C����(*.jpg)

			�����_�����O�^�[�Q�b�g�̓��e��JPG�t�@�C���Ƃ��ĕۑ����܂��B<BR>
			���̋@�\���g���ɂ̓����_�����O�^�[�Q�b�g�����b�N�\�ȃT�[�t�F�C�X�łȂ���΂����܂���B
		*/
		virtual void SaveToFileJPG( const char *pFileName ) = 0;

		/**
			@brief �W���̃R���g���[����\�����邽�߂̃N���b�s���O��ON/OFF
			@author �t���`
			@param IsEnable	[in] �N���b�v������ON/OFF

			true���w�肷�邱�ƂŃN���b�s���O���L���ɂȂ�f�o�C�X��ł��������\�������悤�ɂȂ�܂��B<BR>
		*/
		virtual void SetGUIEnable( Bool IsEnable ) = 0;

		/**
			@brief �e�N�X�`���ݒ�
			@author �t���`
			@param Stage	[in] �ݒ肷��X�e�[�W�i�O�`�V�j
			@param pTex		[in] �ݒ肷��e�N�X�`���iNULL�Ŗ������j
			@retval false	���s
			@retval true	����

			�e�N�X�`���������_���[�ɐݒ肵�܂��B<BR>
			��x�ݒ肳�ꂽ�e�N�X�`����NULL��ݒ肷��܂�<BR>
			�L���ɂȂ��Ă��܂��B
		*/
		virtual Bool SetTexture( eTextureStage Stage, ITexture *pTex ) = 0;

		/**
			@brief �[�x�o�b�t�@�ݒ�
			@author �t���`
			@param pSurface	[in] �ݒ肷��T�[�t�F�C�X
			@retval false	���s
			@retval true	����

			�[�x�o�b�t�@��ݒ肵�܂��B
		*/
		virtual Bool SetDepthBuffer( ITexture *pTexture ) = 0;

		/**
			@brief �����_�����O�^�[�Q�b�g�ݒ�
			@author �t���`
			@retval false	���s
			@retval true	����

			�����_�����O�^�[�Q�b�g���o�b�N�o�b�t�@�ɖ߂��܂��B
		*/
		virtual Bool ResetRenderTarget( void ) = 0;

		/**
			@brief �����_�����O�^�[�Q�b�g�ݒ�
			@author �t���`
			@retval false	���s
			@retval true	����

			�����_�����O�^�[�Q�b�g�Ƃ��Đݒ肵�܂��B<BR>
			CreateRenderTarget()�Ő������ꂽ�e�N�X�`���ȊO�͎��s���܂��B
		*/
		virtual Bool SetRenderTarget( ITexture *pTexture ) = 0;

		/**
			@brief �����_�����O�����J�n�ʒm
			@author �t���`

			�����_���[�ɑ΂��Ă��ꂩ�烌���_�����O������<BR>
			�J�n����Ƃ�������ʒm���܂��B
		*/
		virtual void Begin( void ) = 0;

		/**
			@brief �����_�����O�����I���ʒm
			@author �t���`

			�����_���[�ɑ΂��Ă���Ń����_�����O������<BR>
			�I������Ƃ������Ƃ�ʒm���܂��B
		*/
		virtual void End( void ) = 0;

		/**
			@brief 2D�`��V�U�����O�ݒ�
			@author �t���`
			@param pRect	[in] �V�U�����O�̈�(NULL�ŉ���)

			�����_���[�Ɋ֘A����Q�c�`��̃V�U�����O���s���܂��B
		*/
		virtual void SetScissorPrimitive2D( const Math::Rect2DF *pRect ) = 0;

		/**
			@brief �J�X�^���V�[���Ǘ��C���^�[�t�F�C�X����
			@author �t���`
			@param QueMax			[in] �V�[���̕`��L���[�̍ő吔
			@return �J�X�^���V�[���Ǘ��C���^�[�t�F�C�X

			�S�Ă��v���W�F�N�g���ŊǗ�����J�X�^���V�[���}�l�[�W���[�𐶐����܂��B<BR>
			�����_�����O�V�X�e�������O�ŊǗ��������ꍇ�ɗ��p���ĉ������B
		*/
		virtual Scene::ICustomizedSceneManager *CreateCustomizedSceneManager( Sint32 QueMax ) = 0;

		/**
			@brief �V�[���Ǘ��C���^�[�t�F�C�X����
			@author �t���`
			@param QueMax				[in] �V�[���̕`��L���[�̍ő吔
			@param IsPixelShaderEnable	[in] �s�N�Z���V�F�[�_�[�̗L��
			@return �V�[���Ǘ��C���^�[�t�F�C�X

			�V�F�[�_�[���f��2.0�x�[�X�̃V�[���Ǘ��p�̃C���^�[�t�F�C�X�𐶐����܂��B<BR>
			3D�Ɋւ��郌���_�����O�����͑S�Ă��̃C���^�[�t�F�C�X����܂��B
		*/
		virtual Scene::ISceneManager *CreateSceneManager( Sint32 QueMax, Bool IsPixelShaderEnable ) = 0;

		/**
			@brief 2D�|�C���g�v���~�e�B�u�C���^�[�t�F�C�X����
			@author �t���`
			@param PointMax		[in] �����o�b�t�@�i�[�\�|�C���g��
			@param IsAutoResize	[in] �������T�C�Y
			@param ResizeStep	[in] ���T�C�Y���g���T�C�Y
			@return 2D�|�C���g�v���~�e�B�u�C���^�[�t�F�C�X

			2D�̓_�`��p�̃C���^�[�t�F�C�X�𐶐����܂��B<BR>
			��ʂɓ_��łꍇ�͂��̃C���^�[�t�F�C�X���g���܂��B
		*/
		virtual Object::IPoint2D *CreatePoint2D( Sint32 PointMax, Bool IsAutoResize = false, Sint32 ResizeStep = 0 ) = 0;

		/**
			@brief 2D���C���v���~�e�B�u�C���^�[�t�F�C�X����
			@author �t���`
			@param LineMax	[in] �����o�b�t�@�i�[�\���C����
			@param IsAutoResize	[in] �������T�C�Y
			@param ResizeStep	[in] ���T�C�Y���g���T�C�Y
			@return 2D���C���v���~�e�B�u�C���^�[�t�F�C�X

			2D�̓_�`��p�̃C���^�[�t�F�C�X�𐶐����܂��B<BR>
			��ʂɐ��������ꍇ�͂��̃C���^�[�t�F�C�X���g���܂��B
		*/
		virtual Object::ILine2D *CreateLine2D( Sint32 LineMax, Bool IsAutoResize = false, Sint32 ResizeStep = 0 ) = 0;

		/**
			@brief 2D�|���S���v���~�e�B�u�C���^�[�t�F�C�X����
			@author �t���`
			@param PrimitiveMax	[in] �����o�b�t�@�i�[�\���_���i�ʏ�P�̎O�p�`�ɎO���_�����j
			@param IsAutoResize	[in] �������T�C�Y
			@param ResizeStep	[in] ���T�C�Y���g���T�C�Y
			@return 2D�|���S���v���~�e�B�u�C���^�[�t�F�C�X

			2D�̃|���S���i�O�p�`�j��`�悷�邽�߂̃C���^�[�t�F�C�X�𐶐����܂��B<BR>
			�ŏ��P�ʂł���O�p�`���Ƃ̕`����s���ꍇ�͂��̃C���^�[�t�F�C�X���g���܂��B
		*/
		virtual Object::IPrimitive2D *CreatePrimitive2D( Sint32 PrimitiveMax, Bool IsAutoResize = false, Sint32 ResizeStep = 0 ) = 0;

		/**
			@brief 2D�X�v���C�g�C���^�[�t�F�C�X����
			@author �t���`
			@param PrimitiveMax	[in] �����o�b�t�@�i�[�\���_���i�ʏ�P�̎O�p�`�ɎO���_�����j
			@param pTexture		[in] �X�v���C�g�Ɋ֘A�t����e�N�X�`���C���^�[�t�F�C�X
			@param IsFiltering	[in] �e�N�X�`���t�B���^���g�����ۂ�
			@param IsOffset		[in] �t�B���^�g�p���̃e�N�X�`��UV�␳�l���s�����ۂ�
			@param IsAutoResize	[in] �������T�C�Y
			@param ResizeStep	[in] ���T�C�Y���g���T�C�Y
			@return 2D�X�v���C�g�C���^�[�t�F�C�X

			2D�̃X�v���C�g��`�悷�邽�߂̃C���^�[�t�F�C�X�𐶐����܂��B<BR>
			IPrimitive2D���p�����Ă���A�����I�ɂ�IPrimitive2D�ł̕`����s���Ă��܂��B<BR>
			�e�N�X�`�����g�����ł��ȒP�ȃX�v���C�g�`�悪�\�ȃC���^�[�t�F�C�X�ł��B<BR>
			<BR>
			IsFiltering��true�̎��A�`��Ƀo�C���j�A�t�B���^�����O���K�p����A�g��k���A��]�Ȃǂ̎���<BR>
			��Ԃ����Y��ȕ`��s���܂����A�t�ɒʏ�̓��{�\���̎��ɂڂ₯�Ă��܂��Ƃ������_������܂��B<BR>
			���̌��_����������ɂ�IsFitler��true�ɂ��AIsOffset��false�ɂ��鎖�ŉ\�ł����A<BR>
			�o�C���j�A�t�B���^�̗אڃs�N�Z�����Q�Ƃ��Ă��܂��Ƃ������͉摜�f�[�^�̕��ŉ�������K�v������܂��B<BR>
			��̓I�ɂ͎��͂ɂP�h�b�g�ɗ]���Ƃ��ĉ����`�悳��Ȃ��s�N�Z����u�����Ƃł��B
		*/
		virtual Object::ISprite2D *CreateSprite2D( Sint32 PrimitiveMax, ITexture *pTexture, Bool IsFiltering = false, Bool IsOffset = false, Bool IsAutoResize = false, Sint32 ResizeStep = 0 ) = 0;

		/**
			@brief 2D�p�t�H���g�X�v���C�g�C���^�[�t�F�C�X����
			@author �t���`
			@param pFileName	[in] �t�H���g�X�v���C�g�p��`�t�@�C��
			@param pExt			[in] �t�H���g�X�v���C�g�p�摜�t�@�C���g���q
			@param FontMax		[in] �ő�t�H���g���i�����̒��_�o�b�t�@���j
			@param IsAutoResize	[in] �������T�C�Y
			@param ResizeStep	[in] ���T�C�Y���g���T�C�Y
			@return 2D�t�H���g�X�v���C�g�C���^�[�t�F�C�X

			2D�̃t�H���g�X�v���C�g��`�悷�邽�߂̃C���^�[�t�F�C�X�𐶐����܂��B<BR>
			ISprite2D�𗘗p���Ă���A�����I�ɂ�ISprite2D�ł̕`����s���Ă��܂��B<BR>
			FontUtility�Ő���������`�t�@�C���ƃe�N�X�`�����g���āA�����ɕ������<BR>
			�`����s�����Ƃ��\�ł��B
		*/
		virtual Object::IFontSprite2D *CreateFontSprite2DFromFile( const char *pFileName, const char *pExt, Sint32 FontMax, Bool IsAutoResize = false, Sint32 ResizeStep = 0 ) = 0;

		/**
			@brief 3D�|�C���g�v���~�e�B�u�C���^�[�t�F�C�X����
			@author �t���`
			@param VertexMax	[in] �|�C���g�̍ő吔
			@param IsDynamic	[in] �_�C�i�~�b�N�o�b�t�@�̎g�pON/OFF�i�p�ɂɏ���������ꍇ��true�ɂ��ĉ������j
			@return 3D�|�C���g�v���~�e�B�u�C���^�[�t�F�C�X

			3D�̃|�C���g�`��p�̃C���^�[�t�F�C�X�𐶐����܂��B<BR>
			�ʒu�y�ѐF�f�[�^�݂̂ŁA�e�N�X�`���⃉�C�g�Ȃǂ̕s���ʂ����邱�Ƃ͏o���܂���B
		*/
		virtual Object::IPoint3D *CreatePoint3D( Sint32 VertexMax, Bool IsDynamic ) = 0;

		/**
			@brief 3D���C���v���~�e�B�u�C���^�[�t�F�C�X����
			@author �t���`
			@param VertexMax	[in] ���C���̍ő吔
			@param IsDynamic	[in] �_�C�i�~�b�N�o�b�t�@�̎g�pON/OFF�i�p�ɂɏ���������ꍇ��true�ɂ��ĉ������j
			@return 3D���C���v���~�e�B�u�C���^�[�t�F�C�X

			3D�̃��C���`��p�̃C���^�[�t�F�C�X�𐶐����܂��B<BR>
			�ʒu�y�ѐF�f�[�^�݂̂ŁA�e�N�X�`���⃉�C�g�Ȃǂ̕s���ʂ����邱�Ƃ͏o���܂���B
		*/
		virtual Object::ILine3D *CreateLine3D( Sint32 VertexMax, Bool IsDynamic ) = 0;

		/**
			@brief 3D�|���S���v���~�e�B�u�C���^�[�t�F�C�X����
			@author �t���`
			@param VertexMax		[in] �������_�o�b�t�@�̍ő吔
			@param IndexMax			[in] �����C���f�b�N�X�o�b�t�@�̍ő吔
			@param VertexFlag		[in] ���_�f�[�^�t���O�ieVertexElement�̑g�ݍ��킹�j
			@param IsDynamicVertex	[in] �_�C�i�~�b�N���_�o�b�t�@�̎g�pON/OFF�i�p�ɂɏ���������ꍇ��true�ɂ��ĉ������j
			@param IsDynamicIndex	[in] �_�C�i�~�b�N�C���f�b�N�X�o�b�t�@�̎g�pON/OFF�i�p�ɂɏ���������ꍇ��true�ɂ��ĉ������j
			@return 3D�|���S���v���~�e�B�u�C���^�[�t�F�C�X

			3D�̃|���S���i�O�p�`�j��`�悷�邽�߂̃C���^�[�t�F�C�X�𐶐����܂��B<BR>
			�ŏ��P�ʂł���O�p�`���Ƃ̕`����s���ꍇ�͂��̃C���^�[�t�F�C�X���g���܂��B<BR>
			�܂��C���f�b�N�X���g�p���������I�ȕ`����T�|�[�g���܂��B<BR>
			VertexFlag�͒��_�̃t�H�[�}�b�g���w�肷����̂� eVertexElement �񋓌^�̒�����<BR>
			VERTEX_ELEMENT_PRIMITIVE �� VERTEX_ELEMENT_SPRITE �����������̂��w�肵�܂��B<BR>
			�����g�ݍ��킹��ꍇ�� | ���Z�q�Ŏw�肵�Ă��������B<BR>
			���p�����V�F�[�_�[�͓����ō쐬���ꂽ�Œ�V�F�[�_�[�����p����܂��B<BR>
			���݂̃o�[�W�����ł̓o���v�}�b�v�Ɋւ��鏈���͍s���܂���B<BR>
			<BR>
			�i��j�@�����������C�e�B���O�\�Ȓ��_ -> VERTEX_ELEMENT_3DTEXTURE | VERTEX_ELEMENT_3DLIGHT
		*/
		virtual Object::IPrimitive3D *CreatePrimitive3D( Sint32 VertexMax, Sint32 IndexMax, Sint32 VertexFlag, Bool IsDynamicVertex, Bool IsDynamicIndex ) = 0;

		/**
			@brief 3D�X�v���C�g�C���^�[�t�F�C�X����
			@author �t���`
			@param SpriteMax		[in] �����o�b�t�@�i�[�\�X�v���C�g��
			@param pTexture			[in] �X�v���C�g�Ɋ֘A�t����e�N�X�`���C���^�[�t�F�C�X
			@return 3D�X�v���C�g�C���^�[�t�F�C�X

			3D�̃X�v���C�g��`�悷�邽�߂̃C���^�[�t�F�C�X�𐶐����܂��B<BR>
			IPrimitive3D���p�����Ă���A�����I�ɂ�IPrimitive3D�ł̕`����s���Ă��܂��B<BR>
			�e�N�X�`�����g�����ł��ȒP�ȃX�v���C�g�`�悪�\�ȃC���^�[�t�F�C�X�ł��B
		*/
		virtual Object::ISprite3D *CreateSprite3D( Sint32 SpriteMax, ITexture *pTexture ) = 0;

		/**
			@brief �p�[�e�B�N���C���^�[�t�F�C�X����
			@author �t���`
			@param ParticleMax		[in] �����o�b�t�@�i�[�\�p�[�e�B�N����
			@param pTexture			[in] �p�[�e�B�N���Ɋ֘A�t����e�N�X�`���C���^�[�t�F�C�X
			@param Type				[in] �p�[�e�B�N���Ɋւ��钸�_�t�H�[�}�b�g�^�C�v
			@param IsSoftBillboard	[in] �\�t�g�p�[�e�B�N�������邩�ǂ���
			@return �p�[�e�B�N���C���^�[�t�F�C�X

			�p�[�e�B�N����`�悷�邽�߂̃C���^�[�t�F�C�X�𐶐����܂��B<BR>
			IPrimitive3D���p�����Ă���A�����I�ɂ�IPrimitive3D�ł̕`����s���Ă��܂��B
		*/
		virtual Object::IParticle *CreateParticle( Sint32 ParticleMax, ITexture *pTexture, eParticleType Type, Bool IsSoftBillboard = false ) = 0;

		/**
			@brief 3D�p�t�H���g�X�v���C�g�C���^�[�t�F�C�X����
			@author �t���`
			@param pFileName	[in] �t�H���g�X�v���C�g�p��`�t�@�C��
			@param pExt			[in] �t�H���g�X�v���C�g�p�摜�t�@�C���g���q
			@param FontMax		[in] �ő�t�H���g���i�����̒��_�o�b�t�@���j
			@return 3D�t�H���g�X�v���C�g�C���^�[�t�F�C�X

			3D�̃t�H���g�X�v���C�g��`�悷�邽�߂̃C���^�[�t�F�C�X�𐶐����܂��B<BR>
			IParticle�𗘗p���Ă���A�����I�ɂ�IParticle�ł̕`����s���Ă��܂��B<BR>
			FontUtility�Ő���������`�t�@�C���ƃe�N�X�`�����g���āA�����ɕ������<BR>
			�`����s�����Ƃ��\�ł��B
		*/
		virtual Object::IFontSprite3D *CreateFontSprite3DFromFile( const char *pFileName, const char *pExt, Sint32 FontMax ) = 0;

		/**
			@brief �c���[���f�����t�@�C�����琶��
			@author �t���`
			@param pFileName	[in] ���f����

			SMF�`���̃��f���t�@�C����ǂݍ��݂܂��B<BR>
			SMF�t�@�C����Amaryllis���g�����Ƃ�X�t�@�C�����琶���ł��܂��B
		*/
		virtual Object::IMapModel *CreateMapModelFromFile( const char *pFileName ) = 0;

		/**
			@brief �c���[���f�������������琶��
			@author �t���`
			@param pData	[in] ���f���f�[�^
			@param Size		[in] �f�[�^�T�C�Y

			SMF�`���̃��f���f�[�^��ǂݍ��݂܂��B<BR>
			SMF�t�@�C����Amaryllis���g�����Ƃ�X�t�@�C�����琶���ł��܂��B
		*/
		virtual Object::IMapModel *CreateMapModelFromMemory( const Uint8 *pData, Sint32 Size ) = 0;

		/**
			@brief ���f�����t�@�C�����琶��
			@author �t���`
			@param pFileName	[in] ���f����

			SMF�`���̃��f���t�@�C����ǂݍ��݂܂��B<BR>
			SMF�t�@�C����Amaryllis���g�����Ƃ�X�t�@�C�����琶���ł��܂��B
		*/
		virtual Object::IModel *CreateModelFromFile( const char *pFileName ) = 0;

		/**
			@brief ���f�������������琶��
			@author �t���`
			@param pData	[in] ���f���f�[�^
			@param Size		[in] �f�[�^�T�C�Y

			SMF�`���̃��f���f�[�^��ǂݍ��݂܂��B<BR>
			SMF�t�@�C����Amaryllis���g�����Ƃ�X�t�@�C�����琶���ł��܂��B
		*/
		virtual Object::IModel *CreateModelFromMemory( const Uint8 *pData, Sint32 Size ) = 0;

		/**
			@brief �e�N�X�`���ǂݍ��ݗp�R���t�B�O�f�[�^���擾
			@author �t���`
			@return �e�N�X�`���R���t�B�O�f�[�^
		*/
		virtual CTextureConfig &GetTextureConfig( void ) = 0;

		/**
			@brief �e�N�X�`���ǂݍ��ݗp�R���t�B�O�f�[�^�ݒ�
			@author �t���`
			@param Conf		[in] �e�N�X�`���R���t�B�O�f�[�^
		*/
		virtual void SetTextureConfig( CTextureConfig &Conf ) = 0;

		/**
			@brief �f�o�C�X����T�[�t�F�C�X�𐶐�
			@author �t���`
			@param Width	[in] ����
			@param Height	[in] �c��
			@return �T�[�t�F�C�X�C���^�[�t�F�C�X
		*/
		virtual ITexture *CreateTextureDepthBuffer( Sint32 Width, Sint32 Height ) = 0;

		/**
			@brief �f�o�C�X����e�N�X�`���𐶐�
			@author �t���`
			@param Width	[in] �e�N�X�`���̉���
			@param Height	[in] �e�N�X�`���̏c��
			@param Format	[in] �e�N�X�`���t�H�[�}�b�g
			@return �e�N�X�`���C���^�[�t�F�C�X
		*/
		virtual ITexture *CreateTextureRenderTarget( Sint32 Width, Sint32 Height, eSurfaceFormat Format ) = 0;

		/**
			@brief �f�o�C�X����e�N�X�`���𐶐�
			@author �t���`
			@param pFileName	[in] �e�N�X�`���t�@�C����
			@return �e�N�X�`���C���^�[�t�F�C�X
		*/
		virtual ITexture *CreateTextureFromFile( const char *pFileName ) = 0;

		/**
			@brief �f�o�C�X����e�N�X�`���𐶐�
			@author �t���`
			@param pData	[in] �f�[�^�̃|�C���^
			@param Size		[in] �f�[�^�T�C�Y
			@return �e�N�X�`���C���^�[�t�F�C�X
		*/
		virtual ITexture *CreateTextureFromMemory( const void *pData, Sint32 Size ) = 0;

		/**
			@brief �f�o�C�X����L���[�u�e�N�X�`���𐶐�
			@author �t���`
			@param pFileName	[in] �e�N�X�`���t�@�C����
			@return �e�N�X�`���C���^�[�t�F�C�X
		*/
		virtual ITexture *CreateCubeTextureFromFile( const char *pFileName ) = 0;

		/**
			@brief �f�o�C�X����L���[�u�e�N�X�`���𐶐�
			@author �t���`
			@param pData	[in] �f�[�^�̃|�C���^
			@param Size		[in] �f�[�^�T�C�Y
			@return �e�N�X�`���C���^�[�t�F�C�X
		*/
		virtual ITexture *CreateCubeTextureFromMemory( const void *pData, Sint32 Size ) = 0;

		/**
			@brief �V�F�[�_�[�̐���
			@author �t���`
			@param pShader		[in] �V�F�[�_�[�f�[�^�̃|�C���^
			@param Size			[in] �V�F�[�_�[�f�[�^�̃T�C�Y
			@param IsCompiled	[in] �R���p�C���ς݂��ۂ�
			@return �V�F�[�_�[�C���^�[�t�F�C�X

			�V�F�[�_�[�t�@�C������V�F�[�_�[�C���^�[�t�F�C�X�𐶐����܂��B
		*/
		virtual Shader::IShader *CreateShaderFromMemory( const void *pShader, Sint32 Size, Bool IsCompiled = false ) = 0;

		/**
			@brief �V�F�[�_�[�̐���
			@author �t���`
			@param pShader		[in] �V�F�[�_�[�t�@�C��
			@param IsCompiled	[in] �R���p�C���ς݂��ۂ�
			@return �V�F�[�_�[�C���^�[�t�F�C�X

			�V�F�[�_�[�t�@�C������V�F�[�_�[�C���^�[�t�F�C�X�𐶐����܂��B
		*/
		virtual Shader::IShader *CreateShaderFromFile( const char *pFile, Bool IsCompiled = false ) = 0;

		/**
			@brief �`��^�C�v�ݒ�
			@author �t���`
			@param Type		[in] �`��^�C�v

			�|���S���̕`��^�C�v��ݒ肵�܂��B
		*/
		virtual void SetDrawType( eDrawType Type ) = 0;

		/**
			@brief �\������^�C�v�ݒ�
			@author �t���`
			@param Type		[in] �\������^�C�v

			�|���S���̕\������^�C�v��ݒ肵�܂��B
		*/
		virtual void SetCullType( eCullType Type ) = 0;

		/**
			@brief �t�B���^�����O�^�C�v�ݒ�
			@author �t���`
			@param Stage	[in] �ݒ�X�e�[�W
			@param Type		[in] �t�B���^�����O�^�C�v

			�e�N�X�`���X�e�[�W���̃t�B���^�����O�^�C�v��ݒ肵�܂��B<BR>
			TEXTURE_FILTER_ANISOTROPY�n �̃t�B���^���T�|�[�g����Ȃ��n�[�h�E�F�A�ł�<BR>
			TEXTURE_FILTER_2D ���g���܂��B
		*/
		virtual void SetTextureFilterType( eTextureStage Stage, eTextureFilterType Type ) = 0;

		/**
			@brief �[�x�e�X�gON/OFF�ݒ�
			@author �t���`
			@param Flag		[in] �[�x�e�X�gON/OFF

			�[�x�e�X�g��ON/OFF��ݒ肵�܂��B
		*/
		virtual void SetDepthTestEnable( Bool Flag ) = 0;

		/**
			@brief �[�x�o�b�t�@��������ON/OFF�ݒ�
			@author �t���`
			@param Flag		[in] �[�x�o�b�t�@��������ON/OFF

			�[�x�o�b�t�@�������݂�ON/OFF��ݒ肵�܂��B
		*/
		virtual void SetDepthWriteEnable( Bool Flag ) = 0;

		/**
			@brief �A���t�@�e�X�gON/OFF�ݒ�
			@author �t���`
			@param Flag		[in] �A���t�@�e�X�gON/OFF

			�A���t�@�e�X�g��ON/OFF��ݒ肵�܂��B
		*/
		virtual void SetAlphaTestEnable( Bool Flag ) = 0;

		/**
			@brief �A���t�@�e�X�g臒l�ݒ�
			@author �t���`
			@param Bound	[in] �A���t�@�e�X�g臒l

			�A���t�@�e�X�g��臒l��ݒ肵�܂��B
		*/
		virtual void SetAlphaBoundary( Sint32 Bound ) = 0;

		/**
			@brief �X�e�[�g�̐ݒ���X�^�b�N�ɑޔ����܂�
			@author �t���`
			@retval false	�X�^�b�N�I�[�o�[�t���[
			@retval true	�G���[����

			���݂̃X�e�[�g���X�^�b�N�ɑޔ������܂��B<BR>
			���̊֐��ɂ���đޔ������X�e�[�g�͈ȉ��̊֐��Őݒ肵�����̂ł��B<BR>
			�Evoid SetDrawType( eDrawType Type )<BR>
			�Evoid SetCullType( eCullType Type )<BR>
			�Evoid SetTextureFilterType( Sint32 Stage, eTextureFilterType Type )<BR>
			�Evoid SetTextureAddressType( Sint32 Stage, eTextureAddressType Type )<BR>
			�Evoid SetDepthTestEnable( Bool Flag )<BR>
			�Evoid SetDepthWriteEnable( Bool Flag )<BR>
			�Evoid SetAlphaTestEnable( Bool Flag )<BR>
			�Evoid SetAlphaBoundary( Sint32 Bound )<BR>
			�EBool SetTexture( Sint32 Stage, ITexture *pTex )
		*/
		virtual Bool StatePush( void ) = 0;

		/**
			@brief �X�e�[�g�̐ݒ���X�^�b�N���畜�A���܂�
			@author �t���`
			@retval false	�X�^�b�N�I�[�o�[�t���[
			@retval true	�G���[����

			���݂̃X�e�[�g���X�^�b�N�ɑޔ�����Ă���X�e�[�g�ɖ߂��܂��B
		*/
		virtual Bool StatePop( void ) = 0;

		/**
			@brief �X�e�[�g�̐ݒ��������ԂɃ��Z�b�g���܂�
			@author �t���`

			���݂̃X�e�[�g���X�^�b�N�ɑޔ�����Ă���X�e�[�g�ɖ߂��܂��B<BR>
			�ESetDrawType( DRAW_TYPE_NORMAL )<BR>
			�ESetCullType( CULL_FRONT )<BR>
			�ESetDepthTestEnable( false )<BR>
			�ESetDepthWriteEnable( false )<BR>
			�Evoid SetAlphaTestEnable( true )<BR>
			�Evoid SetAlphaBoundary( Sint32 Bound )<BR>
			�ESetTextureFilterType( \\<Stage\\>, TEXTURE_FILTER_DISABLE )<BR>
			�ESetTextureAddressType( \\<Stage\\>, TEXTURE_ADDRESS_REPEAT )<BR>
			�ESetTexture( \\<Stage\\>, NULL )
		*/
		virtual void StateInit( void ) = 0;

		/**
			@brief �f�o�b�O�p�����ݒ�ύX
			@author �t���`
			@param pFontFace	[in] �t�H���g���
			@param Size			[in] �t�H���g�T�C�Y

			�f�o�b�O�p�̕����̐ݒ��ύX���܂��B
		*/
		virtual void ChangeDebugPrintFont( const char *pFontFace, Sint32 Size ) = 0;

		/**
			@brief �f�o�b�O�p�����`�揈��
			@author �t���`
			@param Pos		[in] �`��ʒu
			@param Color	[in] �`��F
			@param pStr		[in] �`�敶����

			�f�o�b�O�p�̕����`����s���܂��B
		*/
		virtual void DebugPrint( Math::Point2DI &Pos, CColor Color, const char *pStr, ... ) = 0;

		/**
			@brief �ȈՕ����`��p�t�H���g�ݒ�
			@author �t���`
			@param pFontFace	[in] �t�H���g���
			@param Size			[in] �t�H���g�T�C�Y

			�ȈՕ����`��̃t�H���g�̐ݒ�����܂�
		*/
		virtual void SetDrawTextFont( const char *pFontFace, Sint32 Size ) = 0;

		/**
			@brief �ȈՕ����`�揈��
			@author �t���`
			@param Pos		[in] �`��ʒu
			@param Color	[in] �`��F
			@param pStr		[in] �`�敶����

			�ȈՕ����`����s���܂��B
		*/
		virtual void DrawText( Math::Point2DI &Pos, CColor Color, const char *pStr, ... ) = 0;

		/**
			@brief ��`�����_�����O
			@author �t���`
			@param Dst			[in] �`����`
			@param Color		[in] �`��F

			�P���ȋ�`��h��Ԃ��܂��B
		*/
		virtual void FillRect( const Math::Rect2DF &Dst, CColor Color ) = 0;

		/**
			@brief �V�F�[�_�[�𗘗p����ꍇ�̃e�N�X�`�����g������`��]�t���̃����_�����O
			@author �t���`
			@param Dst		[in] �`����`
			@param Color	[in] �`��F
			@param Src		[in] �e�N�X�`��UV��`
			@param pTex		[in] �e�N�X�`��
			@param Angle	[in] ��]�p�x
			@param Offset	[in] ��]�̒��S�̉摜�̒��S����̃I�t�Z�b�g

			�O���̃V�F�[�_�[�𗘗p����ꍇ�̉�]�t���̒P���ȋ�`���e�N�X�`���Ή��Ń����_�����O���܂��B
		*/
		virtual void DrawTextureByShader( const Math::Rect2DF &Dst, CColor Color, const Math::Rect2DF &Src, ITexture *pTex, Sint32 Angle = 0, const Math::Point2DF &Offset = Math::Point2DF(0.0f,0.0f) ) = 0;

		/**
			@brief �e�N�X�`�����g������`��]�t���̃����_�����O
			@author �t���`
			@param Dst		[in] �`����`
			@param Color	[in] �`��F
			@param Src		[in] �e�N�X�`��UV��`
			@param pTex		[in] �e�N�X�`��
			@param Angle	[in] ��]�p�x
			@param Offset	[in] ��]�̒��S�̉摜�̒��S����̃I�t�Z�b�g

			��]�t���̒P���ȋ�`���e�N�X�`���Ή��Ń����_�����O���܂��B
		*/
		virtual void DrawTexture( const Math::Rect2DF &Dst, CColor Color, const Math::Rect2DF &Src, ITexture *pTex, Sint32 Angle = 0, const Math::Point2DF &Offset = Math::Point2DF(0.0f,0.0f) ) = 0;

		/**
			@brief �e�N�X�`�����g������`��]�t���̃����_�����O
			@author �t���`
			@param Dst		[in] �`����`
			@param Color	[in] �`��F
			@param Src		[in] �e�N�X�`��UV��`
			@param pTex		[in] �e�N�X�`��
			@param Angle	[in] ��]�p�x
			@param Offset	[in] ��]�̒��S�̉摜�̒��S����̃I�t�Z�b�g

			��]�t���̒P���ȋ�`���e�N�X�`���Ή��Ń����_�����O���܂��B
		*/
		virtual void DrawTextureTile( const Math::Rect2DF &Dst, CColor Color, const Math::Rect2DF &Src, ITexture *pTex, Sint32 Angle = 0, const Math::Point2DF &Offset = Math::Point2DF(0.0f,0.0f) ) = 0;

		/**
			@brief ���j�o�[�T���g�����W�V�����`��
			@author �t���`
			@param Dst			[in] �`����`
			@param fRate		[in] �����x�i0.0�`1.0�j
			@param SrcBase		[in] �x�[�X�摜�e�N�X�`��UV��`
			@param pTexBase		[in] �x�[�X�摜�e�N�X�`��
			@param SrcRule		[in] �A���t�@�p���[���e�N�X�`��UV��`
			@param pTexRule		[in] �A���t�@�p���[���e�N�X�`��
			@param Angle		[in] ��]�p�x
			@param Offset		[in] ��]�̒��S�̉摜�̒��S����̃I�t�Z�b�g

			���[���摜��p�������j�o�[�T���g�����W�V�������s���܂��B<BR>
			PixelShader2.0���Ȃ����ł�DrawTexture�ɒu���������܂��B
		*/
		virtual void DrawUniversal( const Math::Rect2DF &Dst, Float fRate, const Math::Rect2DF &SrcBase, ITexture *pTexBase, const Math::Rect2DF &SrcRule, ITexture *pTexRule, Sint32 Angle = 0, const Math::Point2DF &Offset = Math::Point2DF(0.0f,0.0f) ) = 0;

		/**
			@brief 4x4�R�[���ڂ����t�B���^�`��
			@author �t���`
			@param Dst		[in] �`����`
			@param Color	[in] �`��F
			@param Src		[in] �e�N�X�`��UV��`
			@param pTex		[in] �e�N�X�`��
			@param Angle	[in] ��]�p�x
			@param Offset	[in] ��]�̒��S�̉摜�̒��S����̃I�t�Z�b�g

			4x4�̃{�b�N�X�ڂ����̃t�B���^�������ĕ`�悵�܂��B<BR>
			PixelShader2.0���Ȃ����ł�DrawTexture�ɒu���������܂��B
		*/
		virtual void DrawBlur( const Math::Rect2DF &Dst, CColor Color, const Math::Rect2DF &Src, ITexture *pTex, Sint32 Angle = 0, const Math::Point2DF &Offset = Math::Point2DF(0.0f,0.0f) ) = 0;

		/**
			@brief �O���[�X�P�[���t�B���^�`��
			@author �t���`
			@param Dst		[in] �`����`
			@param Color	[in] �`��F
			@param Src		[in] �e�N�X�`��UV��`
			@param pTex		[in] �e�N�X�`��
			@param Angle	[in] ��]�p�x
			@param Offset	[in] ��]�̒��S�̉摜�̒��S����̃I�t�Z�b�g

			�O���[�X�P�[���̃t�B���^�������ĕ`�悵�܂��B<BR>
			PixelShader2.0���Ȃ����ł�DrawTexture�ɒu���������܂��B
		*/
		virtual void DrawGrayscale( const Math::Rect2DF &Dst, CColor Color, const Math::Rect2DF &Src, ITexture *pTex, Sint32 Angle = 0, const Math::Point2DF &Offset = Math::Point2DF(0.0f,0.0f) ) = 0;

		/**
			@brief ���჌���Y�`��
			@author �t���`
			@param Dst		[in] �`����`
			@param Color	[in] �`��F
			@param Src		[in] �e�N�X�`��UV��`
			@param pTex		[in] �e�N�X�`��
			@param fRate	[in] ���჌���Y�c�ݓx�i�O�Řc�݂Ȃ��j

			���჌���Y�̃t�B���^�������ĕ`�悵�܂��B<BR>
			PixelShader2.0���Ȃ����ł�DrawTexture�ɒu���������܂��B
		*/
		virtual void DrawFishEye( const Math::Rect2DF &Dst, CColor Color, const Math::Rect2DF &Src, ITexture *pTex, Float fRate ) = 0;
	};
}
}

#pragma once


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
	typedef void *FX_HANDLE;

namespace Renderer
{
namespace Shader
{
	class IShader : public IInterface
	{
	protected:
		virtual ~IShader() {}

	public:
		virtual Bool Begin( Sint32 *pPassMax, Bool IsSave = false ) = 0;
		virtual void End( void ) = 0;
		virtual void BeginPass( Sint32 Pass ) = 0;
		virtual void EndPass( void ) = 0;
		virtual void UpdateParameter( void ) = 0;

		virtual FX_HANDLE GetParameterByName( const char *pName ) = 0;
		virtual FX_HANDLE GetParameterBySemantic( const char *pSemantic ) = 0;

		virtual FX_HANDLE GetTechnique( const char *pName ) = 0;
		virtual void SetTechnique( FX_HANDLE Handle ) = 0;

		virtual void SetFloat( FX_HANDLE Handle, Float Param ) = 0;
		virtual void SetFloatArray( FX_HANDLE Handle, const Float *pParam, Sint32 Num ) = 0;
		virtual void SetInt( FX_HANDLE Handle, Sint32 Param ) = 0;
		virtual void SetIntArray( FX_HANDLE Handle, const Sint32 *pParam, Sint32 Num ) = 0;
		virtual void SetMatrix( FX_HANDLE Handle, const Math::SMatrix4x4 *pMatrix ) = 0;
		virtual void SetMatrixArray( FX_HANDLE Handle, const Math::SMatrix4x4 *pMatrix, Sint32 Num ) = 0;
		virtual void SetMatrixPointerArray( FX_HANDLE Handle, const Math::SMatrix4x4 **ppMatrix, Sint32 Num ) = 0;
		virtual void SetMatrixTranspose( FX_HANDLE Handle, const Math::SMatrix4x4 *pMatrix ) = 0;
		virtual void SetMatrixTransposeArray( FX_HANDLE Handle, const Math::SMatrix4x4 *pMatrix, Sint32 Num ) = 0;
		virtual void SetTexture( FX_HANDLE Handle, Renderer::ITexture *pTex ) = 0;
		virtual void SetVector( FX_HANDLE Handle, const Math::Vector4D *pVec ) = 0;
		virtual void SetVectorArray( FX_HANDLE Handle, const Math::Vector4D *pVec, Sint32 Num ) = 0;
	};
}
}
}
#pragma once


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Renderer
{
namespace Object
{
	/**
		@brief 2D�|�C���g�v���~�e�B�u�Ǘ��C���^�[�t�F�C�X
		@author �t���`

		2D�|�C���g�`��p�̃C���^�[�t�F�C�X�ł��B
	*/
	class IPoint2D
	{
	public:
		virtual ~IPoint2D() {}
		/**
			@brief �L�����`�F�b�N
			@author �t���`
			@retval true ����
			@retval false �L��

			�C���^�[�t�F�C�X���L�����������𒲂ׂ܂��B
		*/
		virtual Bool IsInvalid( void ) = 0;

		/**
			@brief �Q�ƃJ�E���^�f�N�������g
			@author �t���`
			@return �f�N�������g��̎Q�ƃJ�E���g

			�Q�ƃJ�E���^���f�N�������g���A<BR>
			�Q�ƃJ�E���g��0�ɂȂ������_�Ń��������������܂��B
		*/
		virtual Sint32 Release( void ) = 0;

		/**
			@brief �Q�ƃJ�E���^�C���N�������g
			@author �t���`
			@return �C���N�������g��̎Q�ƃJ�E���g

			�Q�ƃJ�E���^���C���N�������g���܂��B<BR>
			�C���N�������g�����Q�ƃJ�E���g��Release()���ĂԂ��Ƃɂ��f�N�������g����܂��B<BR>
			AddRef()�������C���^�[�t�F�C�X�͕K��Release()�ŉ�����Ă��������B
		*/
		virtual Sint32 AddRef( void ) = 0;

		/**
			@brief �f�[�^�ǉ��J�n�錾
			@author �t���`

			�����o�b�t�@�ւ̃f�[�^�̒ǉ����s�����Ƃ�ʒm���܂��B<BR>
			���̊֐����Ă΂���Push*�n�̊֐����Ă΂Ȃ��悤�ɂ��Ă��������B
		*/
		virtual void Begin( void ) = 0;

		/**
			@brief �f�[�^�ǉ��I���錾
			@author �t���`

			�����o�b�t�@�ւ̃f�[�^�̒ǉ��������������Ƃ�ʒm���܂��B<BR>
			���̊֐����ĂԑO�ɕK��Begin�֐����ĂԂ悤�ɂ��Ă��������B
		*/
		virtual void End( void ) = 0;

		/**
			@brief �����o�b�t�@�փf�[�^�ǉ�
			@author �t���`
			@param pPoint	[in] ���_�f�[�^
			@param Count	[in] �ǉ���

			�����o�b�t�@�̃f�[�^�̒ǉ����s���܂��B<BR>
			���̊֐����Ăяo���O�ɕK��Being�֐��Ńf�[�^�ǉ��̊J�n��錾���ĉ������B
		*/
		virtual Bool Push( SVertex2D *pPoint, Sint32 Count ) = 0;

		/**
			@brief �����_�����O
			@author �t���`

			�����o�b�t�@�̓��e�̃����_�����O���s���܂��B
		*/
		virtual void Rendering( void ) = 0;
	};
}
}
}
#pragma once


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Renderer
{
namespace Object
{
	/**
		@brief 2D���C���v���~�e�B�u�Ǘ��C���^�[�t�F�C�X
		@author �t���`

		2D���C���`��p�̃C���^�[�t�F�C�X�ł��B
	*/
	class ILine2D
	{
	public:
		virtual ~ILine2D() {}
		/**
			@brief �L�����`�F�b�N
			@author �t���`
			@retval true ����
			@retval false �L��

			�C���^�[�t�F�C�X���L�����������𒲂ׂ܂��B
		*/
		virtual Bool IsInvalid( void ) = 0;

		/**
			@brief �Q�ƃJ�E���^�f�N�������g
			@author �t���`
			@return �f�N�������g��̎Q�ƃJ�E���g

			�Q�ƃJ�E���^���f�N�������g���A<BR>
			�Q�ƃJ�E���g��0�ɂȂ������_�Ń��������������܂��B
		*/
		virtual Sint32 Release( void ) = 0;

		/**
			@brief �Q�ƃJ�E���^�C���N�������g
			@author �t���`
			@return �C���N�������g��̎Q�ƃJ�E���g

			�Q�ƃJ�E���^���C���N�������g���܂��B<BR>
			�C���N�������g�����Q�ƃJ�E���g��Release()���ĂԂ��Ƃɂ��f�N�������g����܂��B<BR>
			AddRef()�������C���^�[�t�F�C�X�͕K��Release()�ŉ�����Ă��������B
		*/
		virtual Sint32 AddRef( void ) = 0;

		/**
			@brief �f�[�^�ǉ��J�n�錾
			@author �t���`

			�����o�b�t�@�ւ̃f�[�^�̒ǉ����s�����Ƃ�ʒm���܂��B<BR>
			���̊֐����Ă΂���Push*�n�̊֐����Ă΂Ȃ��悤�ɂ��Ă��������B
		*/
		virtual void Begin( void ) = 0;

		/**
			@brief �f�[�^�ǉ��I���錾
			@author �t���`

			�����o�b�t�@�ւ̃f�[�^�̒ǉ��������������Ƃ�ʒm���܂��B<BR>
			���̊֐����ĂԑO�ɕK��Begin�֐����ĂԂ悤�ɂ��Ă��������B
		*/
		virtual void End( void ) = 0;

		/**
			@brief �����o�b�t�@�փf�[�^�ǉ�
			@author �t���`
			@param pLine	[in] ���C���f�[�^
			@param Count	[in] �ǉ���

			�����o�b�t�@�̃f�[�^�̒ǉ����s���܂��B<BR>
			���̊֐����Ăяo���O�ɕK��Being�֐��Ńf�[�^�ǉ��̊J�n��錾���ĉ������B
		*/
		virtual Bool Push( SLineVertex2D *pLine, Sint32 Count ) = 0;

		/**
			@brief �����_�����O
			@author �t���`

			�����o�b�t�@�̓��e�̃����_�����O���s���܂��B
		*/
		virtual void Rendering( void ) = 0;
	};
}
}
}
#pragma once


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Renderer
{
namespace Object
{
	/**
		@brief 2D�v���~�e�B�u�Ǘ��C���^�[�t�F�C�X
		@author �t���`

		2D�v���~�e�B�u�`��p�̃C���^�[�t�F�C�X�ł��B
	*/
	class IPrimitive2D
	{
	public:
		virtual ~IPrimitive2D() {}

		/**
			@brief �L�����`�F�b�N
			@author �t���`
			@retval true ����
			@retval false �L��

			�C���^�[�t�F�C�X���L�����������𒲂ׂ܂��B
		*/
		virtual Bool IsInvalid( void )																													= 0;

		/**
			@brief �Q�ƃJ�E���^�f�N�������g
			@author �t���`
			@return �f�N�������g��̎Q�ƃJ�E���g

			�Q�ƃJ�E���^���f�N�������g���A<BR>
			�Q�ƃJ�E���g��0�ɂȂ������_�Ń��������������܂��B
		*/
		virtual Sint32 Release( void )																													= 0;

		/**
			@brief �Q�ƃJ�E���^�C���N�������g
			@author �t���`
			@return �C���N�������g��̎Q�ƃJ�E���g

			�Q�ƃJ�E���^���C���N�������g���܂��B<BR>
			�C���N�������g�����Q�ƃJ�E���g��Release()���ĂԂ��Ƃɂ��f�N�������g����܂��B<BR>
			AddRef()�������C���^�[�t�F�C�X�͕K��Release()�ŉ�����Ă��������B
		*/
		virtual Sint32 AddRef( void )																													= 0;

		/**
			@brief �f�[�^�ǉ��J�n�錾
			@author �t���`

			�����o�b�t�@�ւ̃f�[�^�̒ǉ����s�����Ƃ�ʒm���܂��B<BR>
			���̊֐����Ă΂���Push*�n�̊֐����Ă΂Ȃ��悤�ɂ��Ă��������B
		*/
		virtual void Begin( void )																														= 0;

		/**
			@brief �f�[�^�ǉ��I���錾
			@author �t���`

			�����o�b�t�@�ւ̃f�[�^�̒ǉ��������������Ƃ�ʒm���܂��B<BR>
			���̊֐����ĂԑO�ɕK��Begin�֐����ĂԂ悤�ɂ��Ă��������B
		*/
		virtual void End( void )																														= 0;

		/**
			@brief ���_���N�G�X�g���擾
			@author �t���`
			@return ���N�G�X�g�������_��

			Push�����ő咸�_�����擾���܂��B
		*/
		virtual Sint32 GetRequestedVertexCount( void )																									= 0;

		/**
			@brief ���_���N�G�X�g���擾
			@author �t���`
			@return ���N�G�X�g�������_��

			Push�����ő咸�_�����擾���܂��B
		*/
		virtual Sint32 GetRequestedVertexCountMax( void )																								= 0;

		/**
			@brief �����o�b�t�@�փf�[�^�ǉ�
			@author �t���`
			@param pPrimitive	[in] �v���~�e�B�u�f�[�^
			@param Count		[in] �ǉ���

			�����o�b�t�@�̃f�[�^�̒ǉ����s���܂��B<BR>
			���̊֐����Ăяo���O�ɕK��Being�֐��Ńf�[�^�ǉ��̊J�n��錾���ĉ������B
		*/
		virtual Bool Push( SPrimitiveVertex2D *pPrimitive, Sint32 Count )																				= 0;

		/**
			@brief �����_�����O
			@author �t���`

			�����o�b�t�@�̓��e�̃����_�����O���s���܂��B
		*/
		virtual void Rendering( void )																													= 0;

		/**
			@brief �l�p�`�`��
			@author �t���`
			@param DstRect	[in] �`���`�f�[�^
			@param Color	[in] �`��F

			�P���Ȏl�p�`��`�悵�܂��B
		*/
		virtual void Square( Math::Rect2DI &DstRect, CColor Color )																					= 0;

		/**
			@brief ��]�t���l�p�`�`��
			@author �t���`
			@param DstRect	[in] �`���`�f�[�^
			@param Color	[in] �`��F
			@param Angle	[in] 1����65536�Ƃ�����]�p�x

			��]�t���̎l�p�`��`�悵�܂��B
		*/
		virtual void SquareRotate( Math::Rect2DI &DstRect, CColor Color, Sint32 Angle )																= 0;

		/**
			@brief ���p�`�`��
			@author �t���`
			@param Pos		[in] ���S�ʒu
			@param fRadius	[in] �`�攼�a
			@param Color	[in] �`��F
			@param Num		[in] �p��

			�P���ȑ��p�`��`�悵�܂��B
		*/
		virtual void Polygon( Math::Point2DI Pos, Float fRadius, CColor Color, Sint32 Num )															= 0;

		/**
			@brief ��]�t�����p�`�`��
			@author �t���`
			@param Pos		[in] ���S�ʒu
			@param fRadius	[in] �`�攼�a
			@param Color	[in] �`��F
			@param Num		[in] �p��
			@param Angle	[in] 1����65536�Ƃ�����]�p�x

			��]�t�����p�`��`�悵�܂��B
		*/
		virtual void PolygonRotate( Math::Point2DI Pos, Float fRadius, CColor Color, Sint32 Num, Sint32 Angle )										= 0;

		/**
			@brief �����O��`��
			@author �t���`
			@param Pos			[in] ���S�ʒu
			@param fInRadius	[in] �������a
			@param fOutRadius	[in] �O�����a
			@param InColor		[in] �����`��F
			@param OutColor		[in] �O���`��F
			@param Num			[in] �p��

			�����O��|���S����`�悵�܂��B
		*/
		virtual void Ring( Math::Point2DI Pos, Float fInRadius, Float fOutRadius, CColor InColor, CColor OutColor, Sint32 Num )						= 0;

		/**
			@brief ��]�t�������O��`��
			@author �t���`
			@param Pos			[in] ���S�ʒu
			@param fInRadius	[in] �������a
			@param fOutRadius	[in] �O�����a
			@param InColor		[in] �����`��F
			@param OutColor		[in] �O���`��F
			@param Num			[in] �p��
			@param Angle	[in] 1����65536�Ƃ�����]�p�x

			��]�t�������O��|���S����`�悵�܂��B
		*/
		virtual void RingRotate( Math::Point2DI Pos, Float fInRadius, Float fOutRadius, CColor InColor, CColor OutColor, Sint32 Num, Sint32 Angle )	= 0;
	};
}
}
}
#pragma once


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Renderer
{
namespace Object
{
	/**
		@brief DrawList�p�\����
		@author �t���`

		@note
		DrawList�ŗ��p����\���̂ł��B
	*/
	struct SSpriteListData2D
	{
		Math::Vector2D Pos;
		Float Width;
		Sint32 Angle;
		CColor Color;
	};

	/**
		@brief 2D�X�v���C�g�Ǘ��C���^�[�t�F�C�X
		@author �t���`

		2D�X�v���C�g�`��p�̃C���^�[�t�F�C�X�ł��B
	*/
	class ISprite2D
	{
	public:
		virtual ~ISprite2D() {}

		/**
			@brief �L�����`�F�b�N
			@author �t���`
			@retval true ����
			@retval false �L��

			�C���^�[�t�F�C�X���L�����������𒲂ׂ܂��B
		*/
		virtual Bool IsInvalid( void ) = 0;

		/**
			@brief �Q�ƃJ�E���^�f�N�������g
			@author �t���`
			@return �f�N�������g��̎Q�ƃJ�E���g

			�Q�ƃJ�E���^���f�N�������g���A<BR>
			�Q�ƃJ�E���g��0�ɂȂ������_�Ń��������������܂��B
		*/
		virtual Sint32 Release( void ) = 0;

		/**
			@brief �Q�ƃJ�E���^�C���N�������g
			@author �t���`
			@return �C���N�������g��̎Q�ƃJ�E���g

			�Q�ƃJ�E���^���C���N�������g���܂��B<BR>
			�C���N�������g�����Q�ƃJ�E���g��Release()���ĂԂ��Ƃɂ��f�N�������g����܂��B<BR>
			AddRef()�������C���^�[�t�F�C�X�͕K��Release()�ŉ�����Ă��������B
		*/
		virtual Sint32 AddRef( void ) = 0;

		/**
			@brief �f�[�^�ǉ��J�n�錾
			@author �t���`

			�����o�b�t�@�ւ̃f�[�^�̒ǉ����s�����Ƃ�ʒm���܂��B<BR>
			���̊֐����Ă΂���Push*�n�̊֐����Ă΂Ȃ��悤�ɂ��Ă��������B
		*/
		virtual void Begin( void ) = 0;

		/**
			@brief �f�[�^�ǉ��I���錾
			@author �t���`

			�����o�b�t�@�ւ̃f�[�^�̒ǉ��������������Ƃ�ʒm���܂��B<BR>
			���̊֐����ĂԑO�ɕK��Begin�֐����ĂԂ悤�ɂ��Ă��������B
		*/
		virtual void End( void ) = 0;

		/**
			@brief �����_�����O
			@author �t���`

			�����o�b�t�@�̓��e�̃����_�����O���s���܂��B
		*/
		virtual void Rendering( void ) = 0;

		/**
			@brief ���_���N�G�X�g���擾
			@author �t���`
			@return ���N�G�X�g�������_��

			Push�����ő咸�_�����擾���܂��B
		*/
		virtual Sint32 GetRequestedVertexCount( void ) = 0;

		/**
			@brief ���_���N�G�X�g���擾
			@author �t���`
			@return ���N�G�X�g�������_��

			Push�����ő咸�_�����擾���܂��B
		*/
		virtual Sint32 GetRequestedVertexCountMax( void ) = 0;

		/**
			@brief �����o�b�t�@�փf�[�^�ǉ�
			@author �t���`
			@param pPrimitive	[in] �v���~�e�B�u�f�[�^
			@param Count		[in] �ǉ���

			�����o�b�t�@�̃f�[�^�̒ǉ����s���܂��B<BR>
			���̊֐����Ăяo���O�ɕK��Being�֐��Ńf�[�^�ǉ��̊J�n��錾���ĉ������B
		*/
		virtual Bool Push( SPrimitiveVertex2D *pPrimitive, Sint32 Count ) = 0;

		/**
			@brief �����p�e�N�X�`���̐ݒ�
			@author �t���`

			@param pTex		[in] �e�N�X�`���C���^�[�t�F�C�X

			�����p�̃e�N�X�`����ݒ肵�܂��B
		*/
		virtual void SetDecoration( ITexture *pTex ) = 0;

		/**
			@brief �l�p�`�`��
			@author �t���`

			@param DstRect		[in] �]����X�N���[���̋�`
			@param SrcRect		[in] �]�����e�N�X�`���̋�`
			@param Color		[in] ���_�F

			�ł��P���ȃX�v���C�g��`�悷�邱�Ƃ��o���܂��B<BR>
			���̊֐��̓f�[�^��`��o�b�t�@�ɒǉ����邾����<BR>
			���ۂ̃����_�����O������Rendering�֐��Ăяo�����ɊJ�n����܂��B
		*/
		virtual void DrawSquare( Math::Rect2DF &DstRect, Math::Rect2DF &SrcRect, CColor Color ) = 0;

		/**
			@brief ��]�t���l�p�`�`��
			@author �t���`

			@param DstRect		[in] �]����X�N���[���̋�`
			@param SrcRect		[in] �]�����e�N�X�`���̋�`
			@param Color		[in] ���_�F
			@param Angle		[in] 1��65536�Ƃ�����]�p�x

			��]�t���X�v���C�g��`�悷�邱�Ƃ��o���܂��B<BR>
			���̊֐��̓f�[�^��`��o�b�t�@�ɒǉ����邾����<BR>
			���ۂ̃����_�����O������Rendering�֐��Ăяo�����ɊJ�n����܂��B
		*/
		virtual void DrawSquareRotate( Math::Rect2DF &DstRect, Math::Rect2DF &SrcRect, CColor Color, Sint32 Angle ) = 0;

		/**
			@brief ��]�t���l�p�`�`��
			@author �t���`

			@param DstRect		[in] �]����X�N���[���̋�`
			@param SrcRect		[in] �]�����e�N�X�`���̋�`
			@param Color		[in] ���_�F
			@param AngleX		[in] 1��65536�Ƃ�����]�p�x
			@param AngleY		[in] 1��65536�Ƃ�����]�p�x
			@param AngleZ		[in] 1��65536�Ƃ�����]�p�x

			��]�t���X�v���C�g��`�悷�邱�Ƃ��o���܂��B<BR>
			���̊֐��̓f�[�^��`��o�b�t�@�ɒǉ����邾����<BR>
			���ۂ̃����_�����O������Rendering�֐��Ăяo�����ɊJ�n����܂��B
		*/
		virtual void DrawSquareRotateXYZ( Math::Rect2DF &DstRect, Math::Rect2DF &SrcRect, CColor Color, Sint32 AngleX, Sint32 AngleY, Sint32 AngleZ ) = 0;

		/**
			@brief �s��ϊ��l�p�`�`��
			@author �t���`

			@param mWorld		[in] �ϊ��s��
			@param SrcRect		[in] �]�����e�N�X�`���̋�`
			@param Color		[in] ���_�F

			�s��ϊ��t���X�v���C�g��`�悷�邱�Ƃ��o���܂��B<BR>
			���̊֐��̓f�[�^��`��o�b�t�@�ɒǉ����邾����<BR>
			���ۂ̃����_�����O������Rendering�֐��Ăяo�����ɊJ�n����܂��B
		*/
		virtual void DrawSquareMatrix( Math::Matrix &mWorld, Math::Rect2DF &SrcRect, CColor Color ) = 0;

		/**
			@brief �я�l�p�`�`��
			@author �t���`

			@param Pos		[in] �`��ʒu�̔z��
			@param Angle	[in] 1��65536�Ƃ�����]�p�x�̔z��
			@param Color	[in] �`��F�̔z��
			@param Count	[in] �e�v�f�̔z��
			@param Width	[in] ���_���Ƃ̕�
			@param Src		[in] �]�����e�N�X�`���̋�`

			�я�ɘA�������X�v���C�g��`�悷�邱�Ƃ��o���܂��B<BR>
			���̊֐��̓f�[�^��`��o�b�t�@�ɒǉ����邾����<BR>
			���ۂ̃����_�����O������Rendering�֐��Ăяo�����ɊJ�n����܂��B
		*/
		virtual void DrawList( Math::Point2DF Pos[], Sint32 Angle[], CColor Color[], Sint32 Count, Float Width, Math::Rect2DF &Src ) = 0;

		/**
			@brief �я�l�p�`�`��
			@author �t���`

			@param Pos		[in] �`��ʒu�̔z��
			@param Width	[in] ���_���Ƃ̕��̔z��
			@param Angle	[in] 1��65536�Ƃ�����]�p�x�̔z��
			@param Color	[in] �`��F�̔z��
			@param Count	[in] �e�v�f�̔z��
			@param Src		[in] �]�����e�N�X�`���̋�`

			�я�ɘA�������X�v���C�g��`�悷�邱�Ƃ��o���܂��B<BR>
			���̊֐��̓f�[�^��`��o�b�t�@�ɒǉ����邾����<BR>
			���ۂ̃����_�����O������Rendering�֐��Ăяo�����ɊJ�n����܂��B
		*/
		virtual void DrawList( Math::Point2DF Pos[], Float Width[], Sint32 Angle[], CColor Color[], Sint32 Count, Math::Rect2DF &Src ) = 0;

		/**
			@brief �я�l�p�`�`��
			@author �t���`

			@param Pos		[in] �`��ʒu�̔z��
			@param List		[in] ���X�g���̔z��
			@param Count	[in] �e�v�f�̔z��
			@param Src		[in] �]�����e�N�X�`���̋�`

			�я�ɘA�������X�v���C�g��`�悷�邱�Ƃ��o���܂��B<BR>
			���̊֐��̓f�[�^��`��o�b�t�@�ɒǉ����邾����<BR>
			���ۂ̃����_�����O������Rendering�֐��Ăяo�����ɊJ�n����܂��B
		*/
		virtual void DrawList( SSpriteListData2D List[], Sint32 Count, Math::Rect2DF &Src ) = 0;

		/**
			@brief ���ˏ�t�F�[�h
			@author �t���`

			@param SrcRect		[in] �]�����e�N�X�`���̋�`
			@param Divide		[in] �~���̃|���S���̕�����
			@param Side			[in] �P�ӂ�����̃|���S���̕�����
			@param Alpha		[in] �����x

			���S�Ɍ������ăt�F�[�h����G�t�F�N�g�ł��B<BR>
			��ʂ̐؂�ւ����Ȃǂɗ��p�ł���Ǝv���܂��B
		*/
		virtual void CircleFade( Math::Rect2DF &SrcRect, Sint32 Divide, Sint32 Side, Sint32 Alpha ) = 0;

		/**
			@brief �~���]�t�F�[�h
			@author �t���`

			@param SrcRect		[in] �]�����e�N�X�`���̋�`
			@param Divide		[in] �~���̃|���S���̕�����
			@param Side			[in] �P�ӂ�����̃|���S���̕�����
			@param Alpha		[in] �����x

			���v���Ƀt�F�[�h����G�t�F�N�g�ł��B<BR>
			��ʂ̐؂�ւ����Ȃǂɗ��p�ł���Ǝv���܂��B
		*/
		virtual void CircleRoundFade( Math::Rect2DF &SrcRect, Sint32 Divide, Sint32 Side, Sint32 Alpha ) = 0;
	};
}
}
}
#pragma once


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Renderer
{
namespace Object
{
	/**
		@brief �t�H���g�X�v���C�g�Ǘ��C���^�[�t�F�C�X
		@author �t���`

		2D�t�H���g�`��p�̃C���^�[�t�F�C�X�ł��B
	*/
	class IFontSprite2D
	{
	public:
		virtual ~IFontSprite2D() {}

		/**
			@brief �L�����`�F�b�N
			@author �t���`
			@retval true ����
			@retval false �L��

			�C���^�[�t�F�C�X���L�����������𒲂ׂ܂��B
		*/
		virtual Bool IsInvalid( void ) = 0;

		/**
			@brief �Q�ƃJ�E���^�f�N�������g
			@author �t���`
			@return �f�N�������g��̎Q�ƃJ�E���g

			�Q�ƃJ�E���^���f�N�������g���A<BR>
			�Q�ƃJ�E���g��0�ɂȂ������_�Ń��������������܂��B
		*/
		virtual Sint32 Release( void ) = 0;

		/**
			@brief �Q�ƃJ�E���^�C���N�������g
			@author �t���`
			@return �C���N�������g��̎Q�ƃJ�E���g

			�Q�ƃJ�E���^���C���N�������g���܂��B<BR>
			�C���N�������g�����Q�ƃJ�E���g��Release()���ĂԂ��Ƃɂ��f�N�������g����܂��B<BR>
			AddRef()�������C���^�[�t�F�C�X�͕K��Release()�ŉ�����Ă��������B
		*/
		virtual Sint32 AddRef( void ) = 0;

		/**
			@brief �f�[�^�ǉ��J�n�錾
			@author �t���`
			@param Space	[in] �s�ԕ␳�l

			�����o�b�t�@�ւ̃f�[�^�̒ǉ����s�����Ƃ�ʒm���܂��B<BR>
			���̊֐����Ă΂���Push*�n�̊֐����Ă΂Ȃ��悤�ɂ��Ă��������B
		*/
		virtual void Begin( Sint32 Space = 0 ) = 0;

		/**
			@brief �f�[�^�ǉ��I���錾
			@author �t���`

			�����o�b�t�@�ւ̃f�[�^�̒ǉ��������������Ƃ�ʒm���܂��B<BR>
			���̊֐����ĂԑO�ɕK��Begin�֐����ĂԂ悤�ɂ��Ă��������B
		*/
		virtual void End( void ) = 0;

		/**
			@brief �����_�����O
			@author �t���`

			�����o�b�t�@�̓��e�̃����_�����O���s���܂��B
		*/
		virtual void Rendering( void ) = 0;

		/**
			@brief �����p�e�N�X�`���̐ݒ�
			@author �t���`

			@param pTex		[in] �e�N�X�`���C���^�[�t�F�C�X

			�����p�̃e�N�X�`����ݒ肵�܂��B
		*/
		virtual void SetDecoration( ITexture *pTex ) = 0;

		/**
			@brief �T�C�Y�擾
			@author �t���`

			�����T�C�Y���擾
		*/
		virtual Sint32 GetSize( void ) = 0;

		/**
			@brief ������`��
			@author �t���`
			@param pStr		[in] �`�敶����
			@param Pos		[in] �`����W
			@param Color	[in] �`��F
			@param Length	[in] �`�敶����(-1�őS��)

			�����t�H���g�ŕ�����̕`����s���܂��B<BR>
			�������̏��̂������t�H���g�łȂ��ꍇ�͐������`�悳��Ȃ���������܂��B
		*/
		virtual void DrawString( const char *pStr, Math::Point2DF Pos, CColor Color, Sint32 Length = -1 ) = 0;

		/**
			@brief ������`��
			@author �t���`
			@param pStr		[in] �`�敶����
			@param Pos		[in] �`����W
			@param Color	[in] �`��F
			@param Length	[in] �`�敶����(-1�őS��)

			�v���|�[�V���i���t�H���g�ŕ�����̕`����s���܂��B<BR>
			�������̏��̂��v���|�[�V���i���t�H���g�łȂ��Ă��������`�悳��܂��B
		*/
		virtual void DrawStringP( const char *pStr, Math::Point2DF Pos, CColor Color, Sint32 Length = -1 ) = 0;

		/**
			@brief �����`��
			@author �t���`
			@param pChara	[in] �`�敶��
			@param Dst		[in] �`���`
			@param Color	[in] �`��F

			�w��ʒu�ɕ�����`�悵�܂��B<BR>
			���̊֐��ł͕����̊g��k�����T�|�[�g���܂��B
		*/
		virtual Sint32 DrawChara( const char *pChara, Math::Rect2DF &Dst, CColor Color ) = 0;

		/**
			@brief ��]�t�������`��
			@author �t���`
			@param pChara	[in] �`�敶��
			@param Dst		[in] �`���`
			@param Color	[in] �`��F
			@param Angle	[in] 1����65536�Ƃ�����]�p�x

			�w��ʒu�ɕ�������]�t���ŕ`�悵�܂��B<BR>
			���̊֐��ł͕����̊g��k�����T�|�[�g���܂��B
		*/
		virtual Sint32 DrawCharaRotate( const char *pChara, Math::Rect2DF &Dst, CColor Color, Sint32 Angle ) = 0;

		/**
			@brief ������`�抮���ʒu�擾
			@author �t���`
			@param pStr		[in] �`�敶����
			@param Pos		[in] �`����W
			@param Length	[in] �`�敶����(-1�őS��)
			@return		�`�抮�����̍��W

			�����t�H���g�ŕ�����̕`����s�����ꍇ�̍ŏI�I�ȕ`��I���ʒu���擾���܂��B<BR>
			���s���܂܂��ꍇ�͉��s���l�������ŏI�ʒu��Ԃ��̂ŁA<BR>
			������̍ő啝���擾�������ꍇ�͒��ӂ��Ă��������B
		*/
		virtual Math::Point2DF GetStringLastPos( const char *pStr, Math::Point2DF Pos, Sint32 Length = -1 ) = 0;

		/**
			@brief ������`�抮���ʒu�擾
			@author �t���`
			@param pStr		[in] �`�敶����
			@param Pos		[in] �`����W
			@param Length	[in] �`�敶����(-1�őS��)
			@return		�`�抮�����̍��W

			�v���|�[�V���i���t�H���g�ŕ�����̕`����s�����ꍇ�̍ŏI�I�ȕ`��I���ʒu���擾���܂��B<BR>
			���s���܂܂��ꍇ�͉��s���l�������ŏI�ʒu��Ԃ��̂ŁA<BR>
			������̍ő啝���擾�������ꍇ�͒��ӂ��Ă��������B
		*/
		virtual Math::Point2DF GetStringLastPosP( const char *pStr, Math::Point2DF Pos, Sint32 Length = -1 ) = 0;

		/**
			@brief ������`��T�C�Y�擾
			@author �t���`
			@param pStr		[in] �`�敶����
			@return		�`��T�C�Y

			�����t�H���g�ŕ�����̕`����s�����ꍇ�̏c���̃T�C�Y���擾���܂��B<BR>
			���s���܂܂��ꍇ�ł��ő�̉������擾�ł��܂��B
		*/
		virtual Math::Point2DF GetStringSize( const char *pStr ) = 0;

		/**
			@brief ������`��T�C�Y�擾
			@author �t���`
			@param pStr		[in] �`�敶����
			@return		�`��T�C�Y

			�v���|�[�V���i���t�H���g�ŕ�����̕`����s�����ꍇ�̏c���̃T�C�Y���擾���܂��B<BR>
			���s���܂܂��ꍇ�ł��ő�̉������擾�ł��܂��B
		*/
		virtual Math::Point2DF GetStringSizeP( const char *pStr ) = 0;

		/**
			@brief ������`��
			@author �t���`
			@param pStr		[in] �`�敶����
			@param Pos		[in] �`����W
			@param Color	[in] �`��F
			@param Length	[in] �`�敶����(-1�őS��)

			�����t�H���g�ŕ�����̕`����s���܂��B<BR>
			�������̏��̂������t�H���g�łȂ��ꍇ�͐������`�悳��Ȃ���������܂��B
		*/
		virtual void DrawString( const wchar_t *pStr, Math::Point2DF Pos, CColor Color, Sint32 Length = -1 ) = 0;

		/**
			@brief ������`��
			@author �t���`
			@param pStr		[in] �`�敶����
			@param Pos		[in] �`����W
			@param Color	[in] �`��F
			@param Length	[in] �`�敶����(-1�őS��)

			�v���|�[�V���i���t�H���g�ŕ�����̕`����s���܂��B<BR>
			�������̏��̂��v���|�[�V���i���t�H���g�łȂ��Ă��������`�悳��܂��B
		*/
		virtual void DrawStringP( const wchar_t *pStr, Math::Point2DF Pos, CColor Color, Sint32 Length = -1 ) = 0;

		/**
			@brief �����`��
			@author �t���`
			@param pChara	[in] �`�敶��
			@param Dst		[in] �`���`
			@param Color	[in] �`��F

			�w��ʒu�ɕ�����`�悵�܂��B<BR>
			���̊֐��ł͕����̊g��k�����T�|�[�g���܂��B
		*/
		virtual Sint32 DrawChara( const wchar_t *pChara, Math::Rect2DF &Dst, CColor Color ) = 0;

		/**
			@brief ��]�t�������`��
			@author �t���`
			@param pChara	[in] �`�敶��
			@param Dst		[in] �`���`
			@param Color	[in] �`��F
			@param Angle	[in] 1����65536�Ƃ�����]�p�x

			�w��ʒu�ɕ�������]�t���ŕ`�悵�܂��B<BR>
			���̊֐��ł͕����̊g��k�����T�|�[�g���܂��B
		*/
		virtual Sint32 DrawCharaRotate( const wchar_t *pChara, Math::Rect2DF &Dst, CColor Color, Sint32 Angle ) = 0;

		/**
			@brief ������`�抮���ʒu�擾
			@author �t���`
			@param pStr		[in] �`�敶����
			@param Pos		[in] �`����W
			@param Length	[in] �`�敶����(-1�őS��)
			@return		�`�抮�����̍��W

			�����t�H���g�ŕ�����̕`����s�����ꍇ�̍ŏI�I�ȕ`��I���ʒu���擾���܂��B<BR>
			���s���܂܂��ꍇ�͉��s���l�������ŏI�ʒu��Ԃ��̂ŁA<BR>
			������̍ő啝���擾�������ꍇ�͒��ӂ��Ă��������B
		*/
		virtual Math::Point2DF GetStringLastPos( const wchar_t *pStr, Math::Point2DF Pos, Sint32 Length = -1 ) = 0;

		/**
			@brief ������`�抮���ʒu�擾
			@author �t���`
			@param pStr		[in] �`�敶����
			@param Pos		[in] �`����W
			@param Length	[in] �`�敶����(-1�őS��)
			@return		�`�抮�����̍��W

			�v���|�[�V���i���t�H���g�ŕ�����̕`����s�����ꍇ�̍ŏI�I�ȕ`��I���ʒu���擾���܂��B<BR>
			���s���܂܂��ꍇ�͉��s���l�������ŏI�ʒu��Ԃ��̂ŁA<BR>
			������̍ő啝���擾�������ꍇ�͒��ӂ��Ă��������B
		*/
		virtual Math::Point2DF GetStringLastPosP( const wchar_t *pStr, Math::Point2DF Pos, Sint32 Length = -1 ) = 0;

		/**
			@brief ������`��T�C�Y�擾
			@author �t���`
			@param pStr		[in] �`�敶����
			@return		�`��T�C�Y

			�����t�H���g�ŕ�����̕`����s�����ꍇ�̏c���̃T�C�Y���擾���܂��B<BR>
			���s���܂܂��ꍇ�ł��ő�̉������擾�ł��܂��B
		*/
		virtual Math::Point2DF GetStringSize( const wchar_t *pStr ) = 0;

		/**
			@brief ������`��T�C�Y�擾
			@author �t���`
			@param pStr		[in] �`�敶����
			@return		�`��T�C�Y

			�v���|�[�V���i���t�H���g�ŕ�����̕`����s�����ꍇ�̏c���̃T�C�Y���擾���܂��B<BR>
			���s���܂܂��ꍇ�ł��ő�̉������擾�ł��܂��B
		*/
		virtual Math::Point2DF GetStringSizeP( const wchar_t *pStr ) = 0;
	};
}
}
}
#pragma once


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Renderer
{
namespace Object
{
	/**
		@brief 3D�|�C���g�`��p�C���^�[�t�F�C�X
		@author �t���`

		3D�|�C���g�`���ێ����邽�߂̃C���^�[�t�F�C�X�ł��B
	*/
	class IPoint3D
	{
	public:
		virtual ~IPoint3D() {}

		/**
			@brief �L�����`�F�b�N
			@author �t���`
			@retval true ����
			@retval false �L��

			�C���^�[�t�F�C�X���L�����������𒲂ׂ܂��B
		*/
		virtual Bool IsInvalid( void ) = 0;

		/**
			@brief �Q�ƃJ�E���^�f�N�������g
			@author �t���`
			@return �f�N�������g��̎Q�ƃJ�E���g

			�Q�ƃJ�E���^���f�N�������g���A<BR>
			�Q�ƃJ�E���g��0�ɂȂ������_�Ń��������������܂��B
		*/
		virtual Sint32 Release( void ) = 0;

		/**
			@brief �Q�ƃJ�E���^�C���N�������g
			@author �t���`
			@return �C���N�������g��̎Q�ƃJ�E���g

			�Q�ƃJ�E���^���C���N�������g���܂��B<BR>
			�C���N�������g�����Q�ƃJ�E���g��Release()���ĂԂ��Ƃɂ��f�N�������g����܂��B<BR>
			AddRef()�������C���^�[�t�F�C�X�͕K��Release()�ŉ�����Ă��������B
		*/
		virtual Sint32 AddRef( void	) = 0;

		/**
			@brief ���_�f�[�^��ǉ�
			@author �t���`
			@param pPoint		[in] �|�C���g�f�[�^
			@param PointCount	[in] �|�C���g��
			@retval false	�ǉ��ł��Ȃ������i�o�b�t�@�[�I�[�o�[�t���[�j
			@retval true	�ǉ��ł���

			�����o�b�t�@�֒��_�f�[�^��ǉ����܂��B<BR>
			�������Ɏw�肵�����_�t�H�[�}�b�g�ɓK���������_�f�[�^��ݒ肵�Ă��������B
		*/
		virtual Bool Push( const SVertex3DBase *pPoint, Sint32 PointCount ) = 0;

		/**
			@brief �f�[�^�ǉ��J�n�錾
			@author �t���`

			�����o�b�t�@�ւ̃f�[�^�̒ǉ����s�����Ƃ�ʒm���܂��B<BR>
			���̊֐����Ă΂���Push*�n�̊֐����Ă΂Ȃ��悤�ɂ��Ă��������B
		*/
		virtual void Begin( void ) = 0;

		/**
			@brief �f�[�^�ǉ��I���錾
			@author �t���`

			�����o�b�t�@�ւ̃f�[�^�̒ǉ��������������Ƃ�ʒm���܂��B<BR>
			���̊֐����ĂԑO�ɕK��Begin�֐����ĂԂ悤�ɂ��Ă��������B
		*/
		virtual void End( void ) = 0;
	};
}
}
}
#pragma once


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Renderer
{
namespace Object
{
	/**
		@brief 3D���C���`��p�C���^�[�t�F�C�X
		@author �t���`

		3D���C���`���ێ����邽�߂̃C���^�[�t�F�C�X�ł��B
	*/
	class ILine3D
	{
	public:
		virtual ~ILine3D() {}

		/**
			@brief �L�����`�F�b�N
			@author �t���`
			@retval true ����
			@retval false �L��

			�C���^�[�t�F�C�X���L�����������𒲂ׂ܂��B
		*/
		virtual Bool IsInvalid( void ) = 0;

		/**
			@brief �Q�ƃJ�E���^�f�N�������g
			@author �t���`
			@return �f�N�������g��̎Q�ƃJ�E���g

			�Q�ƃJ�E���^���f�N�������g���A<BR>
			�Q�ƃJ�E���g��0�ɂȂ������_�Ń��������������܂��B
		*/
		virtual Sint32 Release( void ) = 0;

		/**
			@brief �Q�ƃJ�E���^�C���N�������g
			@author �t���`
			@return �C���N�������g��̎Q�ƃJ�E���g

			�Q�ƃJ�E���^���C���N�������g���܂��B<BR>
			�C���N�������g�����Q�ƃJ�E���g��Release()���ĂԂ��Ƃɂ��f�N�������g����܂��B<BR>
			AddRef()�������C���^�[�t�F�C�X�͕K��Release()�ŉ�����Ă��������B
		*/
		virtual Sint32 AddRef( void	) = 0;

		/**
			@brief ���_�f�[�^��ǉ�
			@author �t���`
			@param pLine		[in] ���C���f�[�^
			@param LineCount	[in] ���C����
			@retval false	�ǉ��ł��Ȃ������i�o�b�t�@�[�I�[�o�[�t���[�j
			@retval true	�ǉ��ł���

			�����o�b�t�@�֒��_�f�[�^��ǉ����܂��B<BR>
			�������Ɏw�肵�����_�t�H�[�}�b�g�ɓK���������_�f�[�^��ݒ肵�Ă��������B
		*/
		virtual Bool Push( SLineVertex3D *pLine, Sint32 LineCount ) = 0;

		/**
			@brief �o�E���f�B���O�{�b�N�X�`�惊�N�G�X�g
			@author �t���`
			@param Box		[in] �R���W�����p�̃{�b�N�X
			@param Color	[in] �F

			�R���W�����p�̃{�b�N�X�f�[�^�̕`����s���܂��B
		*/
		virtual void PushBox( Collision::CBox &Box, CColor Color ) = 0;

		/**
			@brief �f�[�^�ǉ��J�n�錾
			@author �t���`

			�����o�b�t�@�ւ̃f�[�^�̒ǉ����s�����Ƃ�ʒm���܂��B<BR>
			���̊֐����Ă΂���Push*�n�̊֐����Ă΂Ȃ��悤�ɂ��Ă��������B
		*/
		virtual void Begin( void ) = 0;

		/**
			@brief �f�[�^�ǉ��I���錾
			@author �t���`

			�����o�b�t�@�ւ̃f�[�^�̒ǉ��������������Ƃ�ʒm���܂��B<BR>
			���̊֐����ĂԑO�ɕK��Begin�֐����ĂԂ悤�ɂ��Ă��������B
		*/
		virtual void End( void ) = 0;
	};
}
}
}
#pragma once


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Renderer
{
namespace Object
{
	/**
		@brief 3D�v���~�e�B�u�`��p�C���^�[�t�F�C�X
		@author �t���`

		3D�v���~�e�B�u�`���ێ����邽�߂̃C���^�[�t�F�C�X�ł��B
	*/
	class IPrimitive3D
	{
	public:
		virtual ~IPrimitive3D() {}

		/**
			@brief �L�����`�F�b�N
			@author �t���`
			@retval true ����
			@retval false �L��

			�C���^�[�t�F�C�X���L�����������𒲂ׂ܂��B
		*/
		virtual Bool IsInvalid( void ) = 0;

		/**
			@brief �Q�ƃJ�E���^�f�N�������g
			@author �t���`
			@return �f�N�������g��̎Q�ƃJ�E���g

			�Q�ƃJ�E���^���f�N�������g���A<BR>
			�Q�ƃJ�E���g��0�ɂȂ������_�Ń��������������܂��B
		*/
		virtual Sint32 Release( void ) = 0;

		/**
			@brief �Q�ƃJ�E���^�C���N�������g
			@author �t���`
			@return �C���N�������g��̎Q�ƃJ�E���g

			�Q�ƃJ�E���^���C���N�������g���܂��B<BR>
			�C���N�������g�����Q�ƃJ�E���g��Release()���ĂԂ��Ƃɂ��f�N�������g����܂��B<BR>
			AddRef()�������C���^�[�t�F�C�X�͕K��Release()�ŉ�����Ă��������B
		*/
		virtual Sint32 AddRef( void	) = 0;

		/**
			@brief ���_�f�[�^��ǉ�
			@author �t���`
			@param pVtx		[in] ���_�f�[�^
			@param Count	[in] ���_��
			@retval false	�ǉ��ł��Ȃ������i�o�b�t�@�[�I�[�o�[�t���[�j
			@retval true	�ǉ��ł���

			�����o�b�t�@�֒��_�f�[�^��ǉ����܂��B<BR>
			�K���������_�f�[�^��ݒ肵�Ă��������B
		*/
		virtual Bool Push( const SVertex3DBase *pVtx, Sint32 Count ) = 0;

		/**
			@brief ���_�f�[�^��ǉ�
			@author �t���`
			@param pVtx		[in] ���_�f�[�^
			@param Count	[in] ���_��
			@retval false	�ǉ��ł��Ȃ������i�o�b�t�@�[�I�[�o�[�t���[�j
			@retval true	�ǉ��ł���

			�����o�b�t�@�֒��_�f�[�^��ǉ����܂��B<BR>
			�K���������_�f�[�^��ݒ肵�Ă��������B
		*/
		virtual Bool Push( const SVertex3DTexture *pVtx, Sint32 Count ) = 0;

		/**
			@brief ���_�f�[�^��ǉ�
			@author �t���`
			@param pVtx		[in] ���_�f�[�^
			@param Count	[in] ���_��
			@retval false	�ǉ��ł��Ȃ������i�o�b�t�@�[�I�[�o�[�t���[�j
			@retval true	�ǉ��ł���

			�����o�b�t�@�֒��_�f�[�^��ǉ����܂��B<BR>
			�K���������_�f�[�^��ݒ肵�Ă��������B
		*/
		virtual Bool Push( const SVertex3DLight *pVtx, Sint32 Count ) = 0;

		/**
			@brief ���_�f�[�^��ǉ�
			@author �t���`
			@param pVtx		[in] ���_�f�[�^
			@param Count	[in] ���_��
			@retval false	�ǉ��ł��Ȃ������i�o�b�t�@�[�I�[�o�[�t���[�j
			@retval true	�ǉ��ł���

			�����o�b�t�@�֒��_�f�[�^��ǉ����܂��B<BR>
			�K���������_�f�[�^��ݒ肵�Ă��������B
		*/
		virtual Bool Push( const SVertex3DBump *pVtx, Sint32 Count ) = 0;

		/**
			@brief ���_�f�[�^��ǉ�
			@author �t���`
			@param pVtx		[in] ���_�f�[�^
			@param Count	[in] ���_��
			@retval false	�ǉ��ł��Ȃ������i�o�b�t�@�[�I�[�o�[�t���[�j
			@retval true	�ǉ��ł���

			�����o�b�t�@�֒��_�f�[�^��ǉ����܂��B<BR>
			�K���������_�f�[�^��ݒ肵�Ă��������B
		*/
		virtual Bool Push( const SVertex3DAnimation *pVtx, Sint32 Count ) = 0;

		/**
			@brief �C���f�b�N�X�f�[�^��ǉ�
			@author �t���`
			@param pIndex		[in] �C���f�b�N�X�f�[�^
			@param IndexCount	[in] �C���f�b�N�X��
			@retval false	�ǉ��ł��Ȃ������i�o�b�t�@�[�I�[�o�[�t���[�j
			@retval true	�ǉ��ł���

			�����o�b�t�@�փC���f�b�N�X�f�[�^��ǉ����܂��B<BR>
			�������Ɏw�肵���C���f�b�N�X�t�H�[�}�b�g�ɓK�������C���f�b�N�X�f�[�^��ݒ肵�Ă��������B
		*/
		virtual Bool Push( const void *pIndex, Sint32 IndexCount ) = 0;

		/**
			@brief ���_���擾
			@author �t���`
			@return �ǉ��v�����������_�̐�

			�ǉ��v�����s����SVertex3DBase���_�̐����擾���܂��B<BR>
			���̒l�͎��ۂɒǉ����ꂽ���ł͂Ȃ��APush���s���Ēǉ����ꂽ����<BR>
			�擾����̂ŁA���ۂɎ��Ă�ő吔�ȏ�̐���Ԃ��ꍇ������܂��B
		*/
		virtual Sint32 GetVertexCount( void ) = 0;

		/**
			@brief �C���f�b�N�X���擾
			@author �t���`
			@return �ǉ��v���������C���f�b�N�X�̐�

			�ǉ��v�����s�����C���f�b�N�X�̐����擾���܂��B<BR>
			���̒l�͎��ۂɒǉ����ꂽ���ł͂Ȃ��APush���s���Ēǉ����ꂽ����<BR>
			�擾����̂ŁA���ۂɎ��Ă�ő吔�ȏ�̐���Ԃ��ꍇ������܂��B
		*/
		virtual Sint32 GetIndexCount( void ) = 0;

		/**
			@brief �f�[�^�ǉ��J�n�錾
			@author �t���`
			@param IsVertex		[in] ���_�������ݍs��
			@param IsIndex		[in] �C���f�b�N�X�������ݍs��
			@param IsDirect		[in] �o�b�t�@���ڏ�������

			�����o�b�t�@�ւ̃f�[�^�̒ǉ����s�����Ƃ�ʒm���܂��B<BR>
			���̊֐����Ă΂���Push*�n�̊֐����Ă΂Ȃ��悤�ɂ��Ă��������B
		*/
		virtual void Begin( Bool IsVertex = true, Bool IsIndex = true, Bool IsDirect = true ) = 0;

		/**
			@brief �f�[�^�ǉ��I���錾
			@author �t���`

			�����o�b�t�@�ւ̃f�[�^�̒ǉ��������������Ƃ�ʒm���܂��B<BR>
			���̊֐����ĂԑO�ɕK��Begin�֐����ĂԂ悤�ɂ��Ă��������B
		*/
		virtual void End( void ) = 0;
	};
}
}
}
#pragma once


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Renderer
{
namespace Object
{
	/**
		@brief DrawList�p�\����
		@author �t���`

		@note
		DrawList�ŗ��p����\���̂ł��B
	*/
	struct SSpriteListData3D
	{
		Math::Vector3D Pos;
		Float Width;
		Sint32 Angle;
		CColor Color;
	};

	/**
		@brief 3D�X�v���C�g�`��p�C���^�[�t�F�C�X
		@author �t���`

		3D�X�v���C�g�`���ێ����邽�߂̃C���^�[�t�F�C�X�ł��B
	*/
	class ISprite3D
	{
	public:
		virtual ~ISprite3D() {}

		/**
			@brief �L�����`�F�b�N
			@author �t���`
			@retval true ����
			@retval false �L��

			�C���^�[�t�F�C�X���L�����������𒲂ׂ܂��B
		*/
		virtual Bool IsInvalid( void ) = 0;

		/**
			@brief �Q�ƃJ�E���^�f�N�������g
			@author �t���`
			@return �f�N�������g��̎Q�ƃJ�E���g

			�Q�ƃJ�E���^���f�N�������g���A<BR>
			�Q�ƃJ�E���g��0�ɂȂ������_�Ń��������������܂��B
		*/
		virtual Sint32 Release( void ) = 0;

		/**
			@brief �Q�ƃJ�E���^�C���N�������g
			@author �t���`
			@return �C���N�������g��̎Q�ƃJ�E���g

			�Q�ƃJ�E���^���C���N�������g���܂��B<BR>
			�C���N�������g�����Q�ƃJ�E���g��Release()���ĂԂ��Ƃɂ��f�N�������g����܂��B<BR>
			AddRef()�������C���^�[�t�F�C�X�͕K��Release()�ŉ�����Ă��������B
		*/
		virtual Sint32 AddRef( void	) = 0;

		/**
			@brief �f�[�^�ǉ��J�n�錾
			@author �t���`

			�����o�b�t�@�ւ̃f�[�^�̒ǉ����s�����Ƃ�ʒm���܂��B<BR>
			���̊֐����Ă΂���Push*�n�̊֐����Ă΂Ȃ��悤�ɂ��Ă��������B
		*/
		virtual void Begin( void ) = 0;

		/**
			@brief �f�[�^�ǉ��I���錾
			@author �t���`

			�����o�b�t�@�ւ̃f�[�^�̒ǉ��������������Ƃ�ʒm���܂��B<BR>
			���̊֐����ĂԑO�ɕK��Begin�֐����ĂԂ悤�ɂ��Ă��������B
		*/
		virtual void End( void ) = 0;

		/**
			@brief �`�惊�N�G�X�g
			@author �t���`
			@param mWorld		[in] ���[���h�̕ϊ��s��
			@param Size			[in] �`��T�C�Y
			@param SrcRect		[in] �e�N�X�`����`
			@param Color		[in] �F

			�����o�b�t�@�ւ̃f�[�^�̒ǉ����s���܂��B<BR>
			Size�Ŏw�肵���傫���̎l�p�`�|���S����mWorld�ŕϊ����܂��B
		*/
		virtual void Draw( const Math::Matrix &mWorld, const Math::Point2DF &Size, const Math::Rect2DI &SrcRect, CColor Color ) = 0;

		/**
			@brief �`�惊�N�G�X�g
			@author �t���`
			@param mWorld		[in] ���[���h�̕ϊ��s��
			@param PtTbl		[in] �`��p�S���_�i����|�E��|�����|�E���j
			@param SrcRect		[in] �e�N�X�`����`
			@param Color		[in] �F

			�����o�b�t�@�ւ̃f�[�^�̒ǉ����s���܂��B<BR>
			vPosition����ʒu�Ƃ���PtTbl�Ŏw�肵���傫���̋�`�����mWorld�ŕϊ����܂��B
		*/
		virtual void Draw( const Math::Matrix &mWorld, const Math::Vector2D PtTbl[], const Math::Rect2DI &SrcRect, CColor Color ) = 0;

		/**
			@brief �я�l�p�`�`��
			@author �t���`

			@param vCameraPosition	[in] �J�����̈ʒu
			@param Pos				[in] �`��ʒu�̔z��
			@param Color			[in] �`��F�̔z��
			@param Count			[in] �e�v�f�̔z��
			@param Width			[in] ���_���Ƃ̕�
			@param Src				[in] �]�����e�N�X�`���̋�`

			�J�����̈ʒu�ɉ����Ď�����]�������s��ꂽ<BR>
			�я�ɘA�������X�v���C�g��`�悷�邱�Ƃ��o���܂��B<BR>
			���̊֐��̓f�[�^��`��o�b�t�@�ɒǉ����邾����<BR>
			���ۂ̃����_�����O������Rendering�֐��Ăяo�����ɊJ�n����܂��B
		*/
		virtual void DrawPolyLine( const Math::Vector3D &vCameraPosition, const Math::Vector3D Pos[], const CColor Color[], Sint32 Count, Float Width, const Math::Rect2DF &Src ) = 0;

		/**
			@brief �я�l�p�`�`��
			@author �t���`

			@param vCameraPosition	[in] �J�����̈ʒu
			@param Pos				[in] �`��ʒu�̔z��
			@param Color			[in] �`��F�̔z��
			@param Width			[in] ���_���Ƃ̕�
			@param Count			[in] �e�v�f�̔z��
			@param Src				[in] �]�����e�N�X�`���̋�`

			�J�����̈ʒu�ɉ����Ď�����]�������s��ꂽ<BR>
			�я�ɘA�������X�v���C�g��`�悷�邱�Ƃ��o���܂��B<BR>
			���̊֐��̓f�[�^��`��o�b�t�@�ɒǉ����邾����<BR>
			���ۂ̃����_�����O������Rendering�֐��Ăяo�����ɊJ�n����܂��B
		*/
		virtual void DrawPolyLine( const Math::Vector3D &vCameraPosition, const Math::Vector3D Pos[], const CColor Color[], const Float Width[], Sint32 Count, const Math::Rect2DF &Src ) = 0;

		/**
			@brief �я�l�p�`�`��
			@author �t���`

			@param vCameraPosition	[in] �J�����̈ʒu
			@param List				[in] ���_���Ƃ̔z��
			@param Count			[in] �e�v�f�̔z��
			@param Src				[in] �]�����e�N�X�`���̋�`

			�J�����̈ʒu�ɉ����Ď�����]�������s��ꂽ<BR>
			�я�ɘA�������X�v���C�g��`�悷�邱�Ƃ��o���܂��B<BR>
			���̊֐��̓f�[�^��`��o�b�t�@�ɒǉ����邾����<BR>
			���ۂ̃����_�����O������Rendering�֐��Ăяo�����ɊJ�n����܂��B
		*/
		virtual void DrawPolyLine( const Math::Vector3D &vCameraPosition, const SSpriteListData3D List[], Sint32 Count, const Math::Rect2DF &Src ) = 0;

		/**
			@brief �я�l�p�`�`��
			@author �t���`

			@param Pos		[in] �`��ʒu�̔z��
			@param Angle	[in] 1��65536�Ƃ�����]�p�x�̔z��
			@param Color	[in] �`��F�̔z��
			@param Count	[in] �e�v�f�̔z��
			@param Width	[in] ���_���Ƃ̕�
			@param Src		[in] �]�����e�N�X�`���̋�`

			�я�ɘA�������X�v���C�g��`�悷�邱�Ƃ��o���܂��B<BR>
			���̊֐��̓f�[�^��`��o�b�t�@�ɒǉ����邾����<BR>
			���ۂ̃����_�����O������Rendering�֐��Ăяo�����ɊJ�n����܂��B
		*/
		virtual void DrawListXY( const Math::Vector3D Pos[], const Sint32 Angle[], const CColor Color[], Sint32 Count, Float Width, const Math::Rect2DF &Src ) = 0;

		/**
			@brief �я�l�p�`�`��
			@author �t���`

			@param Pos		[in] �`��ʒu�̔z��
			@param Angle	[in] 1��65536�Ƃ�����]�p�x�̔z��
			@param Color	[in] �`��F�̔z��
			@param Count	[in] �e�v�f�̔z��
			@param Width	[in] ���_���Ƃ̕�
			@param Src		[in] �]�����e�N�X�`���̋�`

			�я�ɘA�������X�v���C�g��`�悷�邱�Ƃ��o���܂��B<BR>
			���̊֐��̓f�[�^��`��o�b�t�@�ɒǉ����邾����<BR>
			���ۂ̃����_�����O������Rendering�֐��Ăяo�����ɊJ�n����܂��B
		*/
		virtual void DrawListYZ( const Math::Vector3D Pos[], const Sint32 Angle[], const CColor Color[], Sint32 Count, Float Width, const Math::Rect2DF &Src ) = 0;

		/**
			@brief �я�l�p�`�`��
			@author �t���`

			@param Pos		[in] �`��ʒu�̔z��
			@param Angle	[in] 1��65536�Ƃ�����]�p�x�̔z��
			@param Color	[in] �`��F�̔z��
			@param Count	[in] �e�v�f�̔z��
			@param Width	[in] ���_���Ƃ̕�
			@param Src		[in] �]�����e�N�X�`���̋�`

			�я�ɘA�������X�v���C�g��`�悷�邱�Ƃ��o���܂��B<BR>
			���̊֐��̓f�[�^��`��o�b�t�@�ɒǉ����邾����<BR>
			���ۂ̃����_�����O������Rendering�֐��Ăяo�����ɊJ�n����܂��B
		*/
		virtual void DrawListZX( const Math::Vector3D Pos[], const Sint32 Angle[], const CColor Color[], Sint32 Count, Float Width, const Math::Rect2DF &Src ) = 0;

		/**
			@brief �я�l�p�`�`��
			@author �t���`

			@param Pos		[in] �`��ʒu�̔z��
			@param Width	[in] ���_���Ƃ̕��̔z��
			@param Angle	[in] 1��65536�Ƃ�����]�p�x�̔z��
			@param Color	[in] �`��F�̔z��
			@param Count	[in] �e�v�f�̔z��
			@param Src		[in] �]�����e�N�X�`���̋�`

			�я�ɘA�������X�v���C�g��`�悷�邱�Ƃ��o���܂��B<BR>
			���̊֐��̓f�[�^��`��o�b�t�@�ɒǉ����邾����<BR>
			���ۂ̃����_�����O������Rendering�֐��Ăяo�����ɊJ�n����܂��B
		*/
		virtual void DrawListXY( const Math::Vector3D Pos[], const Float Width[], const Sint32 Angle[], const CColor Color[], Sint32 Count, const Math::Rect2DF &Src ) = 0;

		/**
			@brief �я�l�p�`�`��
			@author �t���`

			@param Pos		[in] �`��ʒu�̔z��
			@param Width	[in] ���_���Ƃ̕��̔z��
			@param Angle	[in] 1��65536�Ƃ�����]�p�x�̔z��
			@param Color	[in] �`��F�̔z��
			@param Count	[in] �e�v�f�̔z��
			@param Src		[in] �]�����e�N�X�`���̋�`

			�я�ɘA�������X�v���C�g��`�悷�邱�Ƃ��o���܂��B<BR>
			���̊֐��̓f�[�^��`��o�b�t�@�ɒǉ����邾����<BR>
			���ۂ̃����_�����O������Rendering�֐��Ăяo�����ɊJ�n����܂��B
		*/
		virtual void DrawListYZ( const Math::Vector3D Pos[], const Float Width[], const Sint32 Angle[], const CColor Color[], Sint32 Count, const Math::Rect2DF &Src ) = 0;

		/**
			@brief �я�l�p�`�`��
			@author �t���`

			@param Pos		[in] �`��ʒu�̔z��
			@param Width	[in] ���_���Ƃ̕��̔z��
			@param Angle	[in] 1��65536�Ƃ�����]�p�x�̔z��
			@param Color	[in] �`��F�̔z��
			@param Count	[in] �e�v�f�̔z��
			@param Src		[in] �]�����e�N�X�`���̋�`

			�я�ɘA�������X�v���C�g��`�悷�邱�Ƃ��o���܂��B<BR>
			���̊֐��̓f�[�^��`��o�b�t�@�ɒǉ����邾����<BR>
			���ۂ̃����_�����O������Rendering�֐��Ăяo�����ɊJ�n����܂��B
		*/
		virtual void DrawListZX( const Math::Vector3D Pos[], const Float Width[], const Sint32 Angle[], const CColor Color[], Sint32 Count, const Math::Rect2DF &Src ) = 0;

		/**
			@brief �я�l�p�`�`��
			@author �t���`

			@param List		[in] ���_���Ƃ̔z��
			@param Count	[in] �e�v�f�̔z��
			@param Src		[in] �]�����e�N�X�`���̋�`

			�я�ɘA�������X�v���C�g��`�悷�邱�Ƃ��o���܂��B<BR>
			���̊֐��̓f�[�^��`��o�b�t�@�ɒǉ����邾����<BR>
			���ۂ̃����_�����O������Rendering�֐��Ăяo�����ɊJ�n����܂��B
		*/
		virtual void DrawListXY( const SSpriteListData3D List[], Sint32 Count, const Math::Rect2DF &Src ) = 0;

		/**
			@brief �я�l�p�`�`��
			@author �t���`

			@param List		[in] ���_���Ƃ̔z��
			@param Count	[in] �e�v�f�̔z��
			@param Src		[in] �]�����e�N�X�`���̋�`

			�я�ɘA�������X�v���C�g��`�悷�邱�Ƃ��o���܂��B<BR>
			���̊֐��̓f�[�^��`��o�b�t�@�ɒǉ����邾����<BR>
			���ۂ̃����_�����O������Rendering�֐��Ăяo�����ɊJ�n����܂��B
		*/
		virtual void DrawListYZ( const SSpriteListData3D List[], Sint32 Count, const Math::Rect2DF &Src ) = 0;

		/**
			@brief �я�l�p�`�`��
			@author �t���`

			@param List		[in] ���_���Ƃ̔z��
			@param Count	[in] �e�v�f�̔z��
			@param Src		[in] �]�����e�N�X�`���̋�`

			�я�ɘA�������X�v���C�g��`�悷�邱�Ƃ��o���܂��B<BR>
			���̊֐��̓f�[�^��`��o�b�t�@�ɒǉ����邾����<BR>
			���ۂ̃����_�����O������Rendering�֐��Ăяo�����ɊJ�n����܂��B
		*/
		virtual void DrawListZX( const SSpriteListData3D List[], Sint32 Count, const Math::Rect2DF &Src ) = 0;
	};
}
}
}
#pragma once


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Renderer
{
namespace Object
{
	/**
		@brief 3D�����`��p�C���^�[�t�F�C�X
		@author �t���`

		3D�����`���ێ����邽�߂̃C���^�[�t�F�C�X�ł��B
	*/
	class IFontSprite3D
	{
	public:
		virtual ~IFontSprite3D() {}

		/**
			@brief �L�����`�F�b�N
			@author �t���`
			@retval true ����
			@retval false �L��

			�C���^�[�t�F�C�X���L�����������𒲂ׂ܂��B
		*/
		virtual Bool IsInvalid( void ) = 0;

		/**
			@brief �Q�ƃJ�E���^�f�N�������g
			@author �t���`
			@return �f�N�������g��̎Q�ƃJ�E���g

			�Q�ƃJ�E���^���f�N�������g���A<BR>
			�Q�ƃJ�E���g��0�ɂȂ������_�Ń��������������܂��B
		*/
		virtual Sint32 Release( void ) = 0;

		/**
			@brief �Q�ƃJ�E���^�C���N�������g
			@author �t���`
			@return �C���N�������g��̎Q�ƃJ�E���g

			�Q�ƃJ�E���^���C���N�������g���܂��B<BR>
			�C���N�������g�����Q�ƃJ�E���g��Release()���ĂԂ��Ƃɂ��f�N�������g����܂��B<BR>
			AddRef()�������C���^�[�t�F�C�X�͕K��Release()�ŉ�����Ă��������B
		*/
		virtual Sint32 AddRef( void ) = 0;

		/**
			@brief �f�[�^�ǉ��J�n�錾
			@author �t���`

			�����o�b�t�@�ւ̃f�[�^�̒ǉ����s�����Ƃ�ʒm���܂��B<BR>
			���̊֐����Ă΂���Push*�n�̊֐����Ă΂Ȃ��悤�ɂ��Ă��������B
		*/
		virtual void Begin( void ) = 0;

		/**
			@brief �f�[�^�ǉ��I���錾
			@author �t���`

			�����o�b�t�@�ւ̃f�[�^�̒ǉ��������������Ƃ�ʒm���܂��B<BR>
			���̊֐����ĂԑO�ɕK��Begin�֐����ĂԂ悤�ɂ��Ă��������B
		*/
		virtual void End( void ) = 0;

		/**
			@brief ������`��
			@author �t���`
			@param pStr		[in] �`�敶����
			@param vPos		[in] �`����W
			@param fSize	[in] �`��T�C�Y
			@param Color	[in] �`��F

			�����t�H���g�ŕ�����̕`����s���܂��B<BR>
			�������̏��̂������t�H���g�łȂ��ꍇ�͐������`�悳��Ȃ���������܂��B
		*/
		virtual void DrawString( const char *pStr, const Math::Vector3D &vPos, const Math::Point2DF &fSize, CColor Color ) = 0;

		/**
			@brief ������`��
			@author �t���`
			@param pStr		[in] �`�敶����
			@param vPos		[in] �`����W
			@param fSize	[in] �`��T�C�Y
			@param Color	[in] �`��F

			�v���|�[�V���i���t�H���g�ŕ�����̕`����s���܂��B<BR>
			�������̏��̂��v���|�[�V���i���t�H���g�łȂ��Ă��������`�悳��܂��B
		*/
		virtual void DrawStringP( const char *pStr, const Math::Vector3D &vPos, const Math::Point2DF &fSize, CColor Color ) = 0;

		/**
			@brief ������`��
			@author �t���`
			@param pStr		[in] �`�敶����
			@param vPos		[in] �`����W
			@param fSize	[in] �`��T�C�Y
			@param Color	[in] �`��F

			�����t�H���g�ŕ�����̕`����s���܂��B<BR>
			�������̏��̂������t�H���g�łȂ��ꍇ�͐������`�悳��Ȃ���������܂��B
		*/
		virtual void DrawString( const wchar_t *pStr, const Math::Vector3D &vPos, const Math::Point2DF &fSize, CColor Color ) = 0;

		/**
			@brief ������`��
			@author �t���`
			@param pStr		[in] �`�敶����
			@param vPos		[in] �`����W
			@param fSize	[in] �`��T�C�Y
			@param Color	[in] �`��F

			�v���|�[�V���i���t�H���g�ŕ�����̕`����s���܂��B<BR>
			�������̏��̂��v���|�[�V���i���t�H���g�łȂ��Ă��������`�悳��܂��B
		*/
		virtual void DrawStringP( const wchar_t *pStr, const Math::Vector3D &vPos, const Math::Point2DF &fSize, CColor Color ) = 0;
	};
}
}
}
#pragma once


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Renderer
{
namespace Object
{
	/**
		@brief 3D�X�v���C�g�`��p�C���^�[�t�F�C�X
		@author �t���`

		3D�X�v���C�g�`���ێ����邽�߂̃C���^�[�t�F�C�X�ł��B
	*/
	class IParticle
	{
	public:
		virtual ~IParticle() {}

		/**
			@brief �L�����`�F�b�N
			@author �t���`
			@retval true ����
			@retval false �L��

			�C���^�[�t�F�C�X���L�����������𒲂ׂ܂��B
		*/
		virtual Bool IsInvalid( void ) = 0;

		/**
			@brief �Q�ƃJ�E���^�f�N�������g
			@author �t���`
			@return �f�N�������g��̎Q�ƃJ�E���g

			�Q�ƃJ�E���^���f�N�������g���A<BR>
			�Q�ƃJ�E���g��0�ɂȂ������_�Ń��������������܂��B
		*/
		virtual Sint32 Release( void ) = 0;

		/**
			@brief �Q�ƃJ�E���^�C���N�������g
			@author �t���`
			@return �C���N�������g��̎Q�ƃJ�E���g

			�Q�ƃJ�E���^���C���N�������g���܂��B<BR>
			�C���N�������g�����Q�ƃJ�E���g��Release()���ĂԂ��Ƃɂ��f�N�������g����܂��B<BR>
			AddRef()�������C���^�[�t�F�C�X�͕K��Release()�ŉ�����Ă��������B
		*/
		virtual Sint32 AddRef( void	) = 0;

		/**
			@brief ��ʒu�ݒ�
			@author �t���`
			@param vPos		[in] ��ʒu

			�����o�b�t�@�ɑ΂���S�Ă̊�ƂȂ�ʒu��ݒ肵�܂��B<BR>
			�����Ŏw�肳�ꂽ�ʒu�̓\�[�g�ɂ����p����܂��B
		*/
		virtual void SetBasePosition( const Math::Vector3D &vPos ) = 0;

		/**
			@brief �f�[�^�ǉ��J�n�錾
			@author �t���`

			�����o�b�t�@�ւ̃f�[�^�̒ǉ����s�����Ƃ�ʒm���܂��B<BR>
			���̊֐����Ă΂���Push*�n�̊֐����Ă΂Ȃ��悤�ɂ��Ă��������B
		*/
		virtual void Begin( void ) = 0;

		/**
			@brief �f�[�^�ǉ��I���錾
			@author �t���`

			�����o�b�t�@�ւ̃f�[�^�̒ǉ��������������Ƃ�ʒm���܂��B<BR>
			���̊֐����ĂԑO�ɕK��Begin�֐����ĂԂ悤�ɂ��Ă��������B
		*/
		virtual void End( void ) = 0;

		/**
			@brief �`�惊�N�G�X�g
			@author �t���`
			@param vPosition	[in] �X�v���C�g�̈ʒu
			@param Size			[in] �`��T�C�Y
			@param SrcRect		[in] �e�N�X�`����`
			@param Color		[in] �F

			�����o�b�t�@�ւ̃f�[�^�̒ǉ����s���܂��B<BR>
			vPosition����ʒu�Ƃ���Size�Ŏw�肵���傫���̋�`�����A
			�J�����̕��֌����悤�ɒ��_�V�F�[�_�[�Ōv�Z����܂��B
		*/
		virtual void Draw( const Math::Vector3D &vPosition, const Math::Point2DF &Size, const Math::Rect2DI &SrcRect, CColor Color ) = 0;

		/**
			@brief �`�惊�N�G�X�g
			@author �t���`
			@param vPosition	[in] �X�v���C�g�̈ʒu
			@param PtTbl		[in] �`��p�S���_�i����|�E��|�����|�E���j
			@param SrcRect		[in] �e�N�X�`����`
			@param Color		[in] �F

			�����o�b�t�@�ւ̃f�[�^�̒ǉ����s���܂��B<BR>
			vPosition����ʒu�Ƃ���PtTbl�Ŏw�肵���傫���̋�`�����A
			�J�����̕��֌����悤�ɒ��_�V�F�[�_�[�Ōv�Z����܂��B
		*/
		virtual void Draw( const Math::Vector3D &vPosition, const Math::Vector2D PtTbl[], const Math::Rect2DI &SrcRect, CColor Color ) = 0;

		/**
			@brief �`�惊�N�G�X�g
			@author �t���`
			@param vPosition	[in] �X�v���C�g�̈ʒu
			@param Size			[in] �`��T�C�Y
			@param SrcRect		[in] �e�N�X�`����`
			@param Color		[in] �F
			@param Angle		[in] ��]�p�x

			�����o�b�t�@�ւ̃f�[�^�̒ǉ����s���܂��B<BR>
			vPosition����ʒu�Ƃ���Size�Ŏw�肵���傫���̋�`�����A
			�J�����̕��֌����悤�ɒ��_�V�F�[�_�[�Ōv�Z����܂��B
		*/
		virtual void DrawRotate( const Math::Vector3D &vPosition, const Math::Point2DF &Size, const Math::Rect2DI &SrcRect, CColor Color, Sint32 Angle ) = 0;

		/**
			@brief �`�惊�N�G�X�g
			@author �t���`
			@param vPosition	[in] �X�v���C�g�̈ʒu
			@param PtTbl		[in] �`��p�S���_�i����|�E��|�����|�E���j
			@param SrcRect		[in] �e�N�X�`����`
			@param Color		[in] �F
			@param Angle		[in] ��]�p�x

			�����o�b�t�@�ւ̃f�[�^�̒ǉ����s���܂��B<BR>
			vPosition����ʒu�Ƃ���PtTbl�Ŏw�肵���傫���̋�`�����A
			�J�����̕��֌����悤�ɒ��_�V�F�[�_�[�Ōv�Z����܂��B
		*/
		virtual void DrawRotate( const Math::Vector3D &vPosition, const Math::Vector2D PtTbl[], const Math::Rect2DI &SrcRect, CColor Color, Sint32 Angle ) = 0;
	};
}
}
}
#pragma once


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Renderer
{
namespace Object
{
	/**
		@brief ���f���f�[�^�p�C���^�[�t�F�C�X
		@author �t���`

		@note
		���f���f�[�^��ێ����邽�߂̃C���^�[�t�F�C�X�ł��B
	*/
	class IModel : public IInterface
	{
	public:
		virtual ~IModel() {}
	};
}
}
}

#pragma once


/**
	@file
	@brief �}�b�v���f���C���^�[�t�F�C�X
	@author �t���`
*/


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Renderer
{
namespace Object
{
	/**
		@brief �}�b�v���f���f�[�^�p�C���^�[�t�F�C�X
		@author �t���`

		@note
		�}�b�v���f���f�[�^��ێ����邽�߂̃C���^�[�t�F�C�X�ł��B
	*/
	class IMapModel : public IInterface
	{
	public:
		virtual ~IMapModel() {}
	};
}
}
}

#pragma once


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Scene
{
	/**
		@brief �V�[���v���~�e�B�u�A�N�^�[�p�C���^�[�t�F�C�X
		@author �t���`

		�V�[���Ǘ����ꂽ�v���~�e�B�u�A�N�^�[�������ׂ̃C���^�[�t�F�C�X�ł��B
	*/
	class IPrimitiveActor : public Math::Style
	{
	public:
		virtual ~IPrimitiveActor() {}

		/**
			@brief �L�����`�F�b�N
			@author �t���`
			@retval true ����
			@retval false �L��

			�C���^�[�t�F�C�X���L�����������𒲂ׂ܂��B
		*/
		virtual Bool IsInvalid( void ) = 0;

		/**
			@brief �Q�ƃJ�E���^�f�N�������g
			@author �t���`
			@return �f�N�������g��̎Q�ƃJ�E���g

			�Q�ƃJ�E���^���f�N�������g���A<BR>
			�Q�ƃJ�E���g��0�ɂȂ������_�Ń��������������܂��B
		*/
		virtual Sint32 Release( void ) = 0;

		/**
			@brief �Q�ƃJ�E���^�C���N�������g
			@author �t���`
			@return �C���N�������g��̎Q�ƃJ�E���g

			�Q�ƃJ�E���^���C���N�������g���܂��B<BR>
			�C���N�������g�����Q�ƃJ�E���g��Release()���ĂԂ��Ƃɂ��f�N�������g����܂��B<BR>
			AddRef()�������C���^�[�t�F�C�X�͕K��Release()�ŉ�����Ă��������B
		*/
		virtual Sint32 AddRef( void	) = 0;

		/**
			@brief �`�惊�N�G�X�g
			@author �t���`

			ISceneManager�ɑ΂��ă����_�����O���N�G�X�g�𔭍s���܂��B<BR>
			�擾����ISceneManager��Begin()/End()���łȂ��ꍇ���̊֐��͎��s���܂��B
		*/
		virtual void RenderingRequest( void ) = 0;

		/**
			@brief ���W�ϊ�������
			@author �t���`

			�A�N�^�[�̍��W�ϊ������������܂��B<BR>
			�A�j���[�V�����̏��Ȃǂ����̊֐����ł��ׂď���������܂��B
		*/
		virtual void TransformReset( void )	 = 0;

		/**
			@brief ���W�ϊ��X�V
			@author �t���`

			�A�N�^�[�̍��W�ϊ����X�V���܂��B<BR>
			�A�j���[�V�����̏��Ȃǂ����̊֐����ł��ׂčX�V����܂��B
		*/
		virtual void TransformUpdate( void ) = 0;

		/**
			@brief �{�[���ϊ��s���ݒ�
			@author �t���`
			@param pMatrix	[in] �{�[���s��̔z��
			@param Count	[in] �{�[���s��̐�

			�A�N�^�[�ɑ΂��ă{�[���̕ϊ��s���ݒ肵�܂��B<BR>
			�{�[���f�[�^������IPrimitive3D�ɑ΂��Ă̂ݗL���ł��B
		*/
		virtual void SetBoneMatrixArray( Math::Matrix *pMatrix, Sint32 Count ) = 0;

		/**
			@brief �V�F�[�_�[��ݒ�
			@author �t���`
			@param pShader	[in] �V�F�[�_�[�C���^�[�t�F�C�X

			�A�N�^�[�ɑ΂��ĔC�ӂ̃V�F�[�_�[��ݒ肵�܂��B
		*/
		virtual void SetShader( Renderer::Shader::IShader *pShader ) = 0;

		/**
			@brief �}�e���A���̊g�U���ːF�ݒ�
			@author �t���`
			@param vColor			[in] �F

			���b�V�����̃}�e���A���̊g�U���ːF��ݒ肵�܂��B
		*/
		virtual void SetMaterialColor( Math::Vector4D &vColor ) = 0;

		/**
			@brief �}�e���A���̎��Ȕ����F�ݒ�
			@author �t���`
			@param vColor			[in] �F

			���b�V�����̃}�e���A���̎��Ȕ����F��ݒ肵�܂��B
		*/
		virtual void SetEmissiveColor( Math::Vector4D &vColor )										= 0;

		/**
			@brief �}�e���A���̋��ʔ��ːF�ݒ�
			@author �t���`
			@param vColor			[in] �F

			���b�V�����̃}�e���A���̋��ʔ��ːF��ݒ肵�܂��B
		*/
		virtual void SetSpecularColor( Math::Vector4D &vColor )										= 0;

		/**
			@brief �}�e���A���̋��ʔ��˂̋����ݒ�
			@author �t���`
			@param fParam			[in] ����

			���b�V�����̃}�e���A���̋��ʔ��˂̋�����ݒ肵�܂��B
		*/
		virtual void SetSpecularRefractive( Float fParam )									= 0;

		/**
			@brief �}�e���A���̋��ʔ��˂̍r���ݒ�
			@author �t���`
			@param fParam			[in] �r��

			���b�V�����̃}�e���A���̋��ʔ��˂̍r����ݒ肵�܂��B
		*/
		virtual void SetSpecularRoughly( Float fParam )									= 0;
	};
}
}

#pragma once


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Scene
{
	/**
		@brief �V�[���v���~�e�B�u�A�N�^�[�p�C���^�[�t�F�C�X
		@author �t���`

		�V�[���Ǘ����ꂽ�v���~�e�B�u�A�N�^�[�������ׂ̃C���^�[�t�F�C�X�ł��B
	*/
	class ISpriteActor : public Math::Style
	{
	public:
		virtual ~ISpriteActor() {}

		/**
			@brief �L�����`�F�b�N
			@author �t���`
			@retval true ����
			@retval false �L��

			�C���^�[�t�F�C�X���L�����������𒲂ׂ܂��B
		*/
		virtual Bool IsInvalid( void ) = 0;

		/**
			@brief �Q�ƃJ�E���^�f�N�������g
			@author �t���`
			@return �f�N�������g��̎Q�ƃJ�E���g

			�Q�ƃJ�E���^���f�N�������g���A<BR>
			�Q�ƃJ�E���g��0�ɂȂ������_�Ń��������������܂��B
		*/
		virtual Sint32 Release( void ) = 0;

		/**
			@brief �Q�ƃJ�E���^�C���N�������g
			@author �t���`
			@return �C���N�������g��̎Q�ƃJ�E���g

			�Q�ƃJ�E���^���C���N�������g���܂��B<BR>
			�C���N�������g�����Q�ƃJ�E���g��Release()���ĂԂ��Ƃɂ��f�N�������g����܂��B<BR>
			AddRef()�������C���^�[�t�F�C�X�͕K��Release()�ŉ�����Ă��������B
		*/
		virtual Sint32 AddRef( void	) = 0;

		/**
			@brief �`�惊�N�G�X�g
			@author �t���`

			ISceneManager�ɑ΂��ă����_�����O���N�G�X�g�𔭍s���܂��B<BR>
			�擾����ISceneManager��Begin()/End()���łȂ��ꍇ���̊֐��͎��s���܂��B
		*/
		virtual void RenderingRequest( void ) = 0;

		/**
			@brief ���W�ϊ�������
			@author �t���`

			�A�N�^�[�̍��W�ϊ������������܂��B<BR>
			�A�j���[�V�����̏��Ȃǂ����̊֐����ł��ׂď���������܂��B
		*/
		virtual void TransformReset( void )	 = 0;

		/**
			@brief ���W�ϊ��X�V
			@author �t���`

			�A�N�^�[�̍��W�ϊ����X�V���܂��B<BR>
			�A�j���[�V�����̏��Ȃǂ����̊֐����ł��ׂčX�V����܂��B
		*/
		virtual void TransformUpdate( void ) = 0;
	};
}
}

#pragma once


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Scene
{
	/**
		@brief �V�[���X�v���C�g�A�N�^�[�p�C���^�[�t�F�C�X
		@author �t���`

		�V�[���Ǘ����ꂽ�X�v���C�g�A�N�^�[�������ׂ̃C���^�[�t�F�C�X�ł��B
	*/
	class IParticleActor
	{
	public:
		virtual ~IParticleActor() {}

		/**
			@brief �L�����`�F�b�N
			@author �t���`
			@retval true ����
			@retval false �L��

			�C���^�[�t�F�C�X���L�����������𒲂ׂ܂��B
		*/
		virtual Bool IsInvalid( void ) = 0;

		/**
			@brief �Q�ƃJ�E���^�f�N�������g
			@author �t���`
			@return �f�N�������g��̎Q�ƃJ�E���g

			�Q�ƃJ�E���^���f�N�������g���A<BR>
			�Q�ƃJ�E���g��0�ɂȂ������_�Ń��������������܂��B
		*/
		virtual Sint32 Release( void ) = 0;

		/**
			@brief �Q�ƃJ�E���^�C���N�������g
			@author �t���`
			@return �C���N�������g��̎Q�ƃJ�E���g

			�Q�ƃJ�E���^���C���N�������g���܂��B<BR>
			�C���N�������g�����Q�ƃJ�E���g��Release()���ĂԂ��Ƃɂ��f�N�������g����܂��B<BR>
			AddRef()�������C���^�[�t�F�C�X�͕K��Release()�ŉ�����Ă��������B
		*/
		virtual Sint32 AddRef( void	) = 0;

		/**
			@brief �`�惊�N�G�X�g
			@author �t���`

			ISceneManager�ɑ΂��ă����_�����O���N�G�X�g�𔭍s���܂��B<BR>
			�擾����ISceneManager��Begin()/End()���łȂ��ꍇ���̊֐��͎��s���܂��B
		*/
		virtual void RenderingRequest( void ) = 0;
	};
}
}

#pragma once


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Scene
{
	/**
		@brief �V�[�����f���A�N�^�[�p�C���^�[�t�F�C�X
		@author �t���`

		�V�[���Ǘ����ꂽ���f���A�N�^�[�������ׂ̃C���^�[�t�F�C�X�ł��B
	*/
	class IInstanceModelActor : public IInterface
	{
	public:
		virtual ~IInstanceModelActor() {}

		/**
			@brief �C���X�^���X���f������p�C���^�[�t�F�C�X�擾
			@author �t���`

			�C���X�^���X�o�^���ꂽ�X�̃��f���𐧌䂷�邽�߂̃C���^�[�t�F�C�X���擾���܂��B<BR>
			�{�[���⃏�[���h�ϊ��̏����͂��̃C���^�[�t�F�C�X���o�R���čs���܂��B
		*/
		virtual IInstanceModelController *GetController( Sint32 Index ) = 0;

		/**
			@brief �`�惊�N�G�X�g�J�n
			@author �t���`

			IInstanceModelController�̃����_�����O�����̊J�n��錾���܂��B
			IInstanceModelController��RenderingRequest()��Begin-End�ԂŌĂ�ŉ������B
		*/
		virtual void Begin( void ) = 0;

		/**
			@brief �`�惊�N�G�X�g�I��
			@author �t���`

			IInstanceModelController�̃����_�����O�����̏I����錾���܂��B
			IInstanceModelController��RenderingRequest()��Begin-End�ԂŌĂ�ŉ������B
		*/
		virtual void End( void ) = 0;
	};
}
}

#pragma once


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Scene
{
	/**
		@brief �V�[�����f���A�N�^�[�p�C���^�[�t�F�C�X
		@author �t���`

		�V�[���Ǘ����ꂽ���f���A�N�^�[�������ׂ̃C���^�[�t�F�C�X�ł��B
	*/
	class IInstanceModelController : public Math::Style
	{
	public:
		virtual ~IInstanceModelController() {}

		/**
			@brief �L�����`�F�b�N
			@author �t���`
			@retval true ����
			@retval false �L��

			�C���^�[�t�F�C�X���L�����������𒲂ׂ܂��B
		*/
		virtual Bool IsInvalid( void ) = 0;

		/**
			@brief �Q�ƃJ�E���^�f�N�������g
			@author �t���`
			@return �f�N�������g��̎Q�ƃJ�E���g

			�Q�ƃJ�E���^���f�N�������g���A<BR>
			�Q�ƃJ�E���g��0�ɂȂ������_�Ń��������������܂��B
		*/
		virtual Sint32 Release( void ) = 0;

		/**
			@brief �Q�ƃJ�E���^�C���N�������g
			@author �t���`
			@return �C���N�������g��̎Q�ƃJ�E���g

			�Q�ƃJ�E���^���C���N�������g���܂��B<BR>
			�C���N�������g�����Q�ƃJ�E���g��Release()���ĂԂ��Ƃɂ��f�N�������g����܂��B<BR>
			AddRef()�������C���^�[�t�F�C�X�͕K��Release()�ŉ�����Ă��������B
		*/
		virtual Sint32 AddRef( void	) = 0;

		/**
			@brief �`�惊�N�G�X�g
			@author �t���`

			ISceneManager�ɑ΂��ă����_�����O���N�G�X�g�𔭍s���܂��B<BR>
			�擾����ISceneManager��Begin()/End()���łȂ��ꍇ���̊֐��͎��s���܂��B
		*/
		virtual void RenderingRequest( void ) = 0;

		/**
			@brief �J�����O�p�o�E���f�B���O�����_�����O
			@author �t���`
			@param pLine	[in] ���C���v���~�e�B�u�C���^�[�t�F�C�X

			�o�E���f�B���O�{�b�N�X���w�肵�����C���f�[�^�ɑ΂��Ēǉ����܂��B
		*/
		virtual void RenderingBounding( Renderer::Object::ILine3D *pLine ) = 0;

		/**
			@brief ���W�ϊ�������
			@author �t���`

			�A�N�^�[�̍��W�ϊ������������܂��B<BR>
			�A�j���[�V�����̏��Ȃǂ����̊֐����ł��ׂď���������܂��B
		*/
		virtual void TransformReset( void ) = 0;

		/**
			@brief ���W�ϊ��X�V
			@author �t���`

			�A�N�^�[�̍��W�ϊ����X�V���܂��B<BR>
			�A�j���[�V�����̏��Ȃǂ����̊֐����ł��ׂčX�V����܂��B<BR>
			�����I�ɂ́@TransformUpdateCollisionOnly() �� TransformUpdateActorOnly() ���Ăяo���Ă��܂��B
		*/
		virtual void TransformUpdate( void ) = 0;

		/**
			@brief ���W�ϊ��X�V
			@author �t���`

			�A�N�^�[�̃R���W�����̍��W�ϊ����X�V���܂��B<BR>
			�R���W�����Ɋ֌W����f�[�^�������ōX�V����܂��B
		*/
		virtual void TransformUpdateCollisionOnly( void ) = 0;

		/**
			@brief ���W�ϊ��X�V
			@author �t���`

			�A�N�^�[�̍��W�ϊ����X�V���܂��B<BR>
			�`��p�̃A�N�^�[�������X�V����܂��B
		*/
		virtual void TransformUpdateActorOnly( void ) = 0;

		/**
			@brief ���f���ɑ΂��ăA�j���[�V�����f�[�^�����擾
			@author �t���`
			@return	�A�j���[�V������

			�A�N�^�[�̏�������A�j���[�V�����̐����擾���܂��B
		*/
		virtual Sint32 GetAnimationCount( void ) = 0;

		/**
			@brief �A�j���[�V�����f�[�^�̍ŏI���Ԃ��擾
			@author �t���`
			@param AnimationNo		[in] �K�p����A�j���[�V�����ԍ�
			@return	�A�j���[�V�����̍ŏI����

			�A�j���[�V�����̍ŏI�t���[�����擾���܂��B
		*/
		virtual Float GetAnimationLastTime( Sint32 AnimationNo ) = 0;

		/**
			@brief ���f���ɑ΂��ăA�j���[�V�����f�[�^���X�V
			@author �t���`
			@param AnimationNo		[in] �K�p����A�j���[�V�����ԍ�
			@param fAnimationTime	[in] �A�j���[�V�����̎��ԁi�P�ʂ͍쐬�����c�[���ɂ��j

			�P��̃A�j���[�V�����f�[�^�̍X�V�����܂��B
		*/
		virtual void UpdateAnimation( Sint32 AnimationNo, Float fAnimationTime ) = 0;

		/**
			@brief ���f���ɑ΂��ăA�j���[�V�����f�[�^���X�V
			@author �t���`
			@param AnimationNo1		[in] �K�p����A�j���[�V�����ԍ�
			@param fAnimationTime1	[in] �A�j���[�V�����̎��ԁi�P�ʂ͍쐬�����c�[���ɂ��j
			@param AnimationNo2		[in] �K�p����A�j���[�V�����ԍ�
			@param fAnimationTime2	[in] �A�j���[�V�����̎��ԁi�P�ʂ͍쐬�����c�[���ɂ��j
			@param fWeight			[in] �u�����h�����i0.0f�̎�AnimationNo0�A1.0�̎�AnimationNo1)

			�Q�̃A�j���[�V�������u�����h���ăA�j���[�V�����f�[�^���X�V���܂��B
		*/
		virtual void UpdateAnimation( Sint32 AnimationNo1, Float fAnimationTime1, Sint32 AnimationNo2, Float fAnimationTime2, Float fWeight ) = 0;

		/**
			@brief �J�����O�����ɗL���ݒ�
			@author �t���`
			@param IsEnable	[in] �J�����O�̗L��

			���f�����̊e�A�N�^�[�ɑ΂��ăr���[�t���X�^���J�����O���s������ݒ肵�܂��B<BR>
			�r���[�t���X�^���J�����O�Ƃ̓J�����̕`��̈���ɂȂ��A�N�^�[��`��Ɋւ����A�̏�������<BR>
			�Ȃ����߂̏����ŁA�s������CPU���ׂ͑����܂�����ʊO�ɏo��A�N�^�[�ɑ΂��Ă̕`�敉�ׂ��y���ł��܂��B
		*/
		virtual void SetCullTestEnable( Bool IsEnable ) = 0;

		/**
			@brief ���f�����̃t���[�����擾
			@author �t���`
			@return	���f�����̃t���[���̐�

			���f�����̃t���[���̐����擾���܂��B<BR>
			�X�L�����b�V���Ɋ֘A�t�����Ă���t���[����<BR>
			�����I�ɂ̓{�[���ɂȂ�܂��B
		*/
		virtual Sint32 GetFrameCount( void ) = 0;

		/**
			@brief ���f�����̃t���[�����擾
			@author �t���`
			@return	���f�����̃t���[���̐�

			���f�����̃t���[���̐����擾���܂��B
		*/
		virtual Sint32 Frame_GetIndex( const char *pName ) = 0;

		/**
			@brief �t���[���̕ϊ��s����擾
			@author �t���`
			@param Index	[in] �t���[���̔ԍ�
			@return	�t���[���̕ϊ��s��

			�t���[���̕ϊ��s����擾���܂��B
		*/
		virtual Math::Matrix &Frame_GetTransformLocal( Sint32 Index ) = 0;

		/**
			@brief �t���[���̕ϊ��s����擾
			@author �t���`
			@param Index	[in] �t���[���̔ԍ�
			@return	�t���[���̕ϊ��s��

			�t���[���̕ϊ��s����擾���܂��B
		*/
		virtual Math::Matrix &Frame_GetTransformWorld( Sint32 Index ) = 0;

		/**
			@brief �R���W��������
			@author �t���`

			�A�N�^�[�ɑ΂��ẴR���W��������p�̃C���^�[�t�F�C�X�𐶐����܂��B<BR>
			������s����Collision_***()�n�̊֐����L���ɂȂ�܂��B
		*/
		virtual void Collision_Create( void ) = 0;

		/**
			@brief �R���W�����L���ݒ�
			@author �t���`
			@param Index	[in] �t���[���ԍ�
			@param IsEnable	[in] true�̎��R���W����ON�i�f�t�H���g��ON�j

			�w��ԍ��̃t���[���̃R���W������ON/OFF���܂��B
		*/
		virtual void Collision_SetEnable( Sint32 Index, Bool IsEnable ) = 0;

		/**
			@brief �R���W�����L���ݒ�
			@author �t���`
			@param pName	[in] ����
			@param IsEnable	[in] true�̎��R���W����ON�i�f�t�H���g��ON�j

			�w�薼�̃t���[���̃R���W������ON/OFF���܂��B
		*/
		virtual void Collision_SetEnable( const char *pName, Bool IsEnable ) = 0;

		/**
			@brief �R���W�����f�[�^�`��
			@author �t���`
			@param pLine	[in] �`��p���C���v���~�e�B�u�C���^�[�t�F�C�X

			�����蔻��f�[�^�������_�����O���邽�߂̊֐��ł��B
		*/
		virtual void Collision_Rendering( Renderer::Object::ILine3D *pLine ) = 0;

		/**
			@brief �R���W�����̌��ʎ擾
			@author �t���`
			@param FrameNo	[in,out] �Փ˂����t���[���ԍ��i�[��
			@param vPos		[in,out] �Փ˂����ʒu�i�[��

			�����蔻��f�[�^���擾���܂��B<BR>
			�����_�ł͏Փ˂�����܂��Ȉʒu�ƏՓ˂���<BR>
			�t���[���ԍ������擾���邱�Ƃ͂ł��܂���B
		*/
		virtual void Collision_GetResult( Sint32 &FrameNo, Math::Vector3D &vPos ) = 0;

		/**
			@brief �R���W�����`�F�b�N
			@author �t���`
			@param pSrc	[in] �`�F�b�N����IModelActor

			�w�肳�ꂽ�f�[�^�Ƃ̏Փˌ��o���s���܂��B<BR>
			�Փ˂̌��ʂ�Collision_GetResult()�Ŏ擾�ł��܂��B
		*/
		virtual Bool Collision_Check( IModelActor *pSrc ) = 0;

		/**
			@brief �R���W�����`�F�b�N
			@author �t���`
			@param Src	[in] �`�F�b�N����{�b�N�X�f�[�^

			�w�肳�ꂽ�f�[�^�Ƃ̏Փˌ��o���s���܂��B<BR>
			�Փ˂̌��ʂ�Collision_GetResult()�Ŏ擾�ł��܂��B
		*/
		virtual Bool Collision_Check( Collision::CBox &Src ) = 0;

		/**
			@brief �R���W�����`�F�b�N
			@author �t���`
			@param Src	[in] �`�F�b�N���郉�C���f�[�^

			�w�肳�ꂽ�f�[�^�Ƃ̏Փˌ��o���s���܂��B<BR>
			�Փ˂̌��ʂ�Collision_GetResult()�Ŏ擾�ł��܂��B
		*/
		virtual Bool Collision_Check( Collision::CLine3D &Src ) = 0;

		/**
			@brief �R���W�����`�F�b�N
			@author �t���`
			@param Src	[in] �`�F�b�N����_�f�[�^

			�w�肳�ꂽ�f�[�^�Ƃ̏Փˌ��o���s���܂��B<BR>
			�Փ˂̌��ʂ�Collision_GetResult()�Ŏ擾�ł��܂��B
		*/
		virtual Bool Collision_Check( Math::Vector3D &Src ) = 0;

		/**
			@brief �R���W�����`�F�b�N
			@author �t���`
			@param Src			[in] �`�F�b�N����_�f�[�^
			@param pSceneMgr	[in] �����_�����O���s�����V�[���̃C���^�[�t�F�C�X

			�X�N���[�����W�Ƃ̏Փˌ��o���s���܂��B<BR>
			�Փ˂̌��ʂ�Collision_GetResult()�Ŏ擾�ł��܂��B
		*/
		virtual Bool Collision_CheckOnScreen( Math::Vector2D &Src, ISceneManager *pSceneMgr ) = 0;

		/**
			@brief �Փ˔���
			@author �t���`
			@param Ray			[in] �n�_����I�_�����Ԑ���
			@retval false	�Փ˂��Ȃ�
			@retval true	�Փ˂���

			�}�b�v���f�������R���W�����f�[�^�ɑ΂��āA
			�_��Ray�Ŏ����ړ��������ꍇ�̃R���W�������������܂��B
		*/
		virtual Bool HitCheckByRay( const Collision::CLine3D &Ray ) = 0;

		/**
			@brief �Փ˔���
			@author �t���`
			@param Ray			[in] �n�_����I�_�����Ԑ���
			@param Box			[out] �Փ˂������b�V����OBB
			@retval false	�Փ˂��Ȃ�
			@retval true	�Փ˂���

			�}�b�v���f�������R���W�����f�[�^�ɑ΂��āA
			�_��Ray�Ŏ����ړ��������ꍇ�̃R���W�������������܂��B
		*/
		virtual Bool HitCheckByRay( const Collision::CLine3D &Ray, Collision::CBox &Box ) = 0;

		/**
			@brief �Փ˔���
			@author �t���`
			@param Ray			[in] �n�_����I�_�����Ԑ���
			@param Out			[out] �Փˌ���
			@retval false	�Փ˂��Ȃ�
			@retval true	�Փ˂���

			�}�b�v���f�������R���W�����f�[�^�ɑ΂��āA
			�_��Ray�Ŏ����ړ��������ꍇ�̃R���W�������������܂��B
		*/
		virtual Bool HitCheckByRay( const Collision::CLine3D &Ray, Renderer::SCollisionResult &Out ) = 0;

		/**
			@brief �Փ˔���
			@author �t���`
			@param Ray			[in] �n�_����I�_�����Ԑ���
			@param Out			[out] �Փˌ���
			@param Box			[out] �Փ˂������b�V����OBB
			@retval false	�Փ˂��Ȃ�
			@retval true	�Փ˂���

			�}�b�v���f�������R���W�����f�[�^�ɑ΂��āA
			�_��Ray�Ŏ����ړ��������ꍇ�̃R���W�������������܂��B
		*/
		virtual Bool HitCheckByRay( const Collision::CLine3D &Ray, Renderer::SCollisionResult &Out, Collision::CBox &Box ) = 0;

		/**
			@brief �Փ˔���
			@author �t���`
			@param Ray			[in] �n�_����I�_�����Ԑ���
			@param Out			[out] �Փˌ���
			@retval false	�Փ˂��Ȃ�
			@retval true	�Փ˂���

			�}�b�v���f�������R���W�����f�[�^�ɑ΂��āA
			�_��Ray�Ŏ����ړ��������ꍇ�̃R���W�������������܂��B
		*/
		virtual Bool HitCheckByRay( const Collision::CLine3D &Ray, Renderer::SCollisionResultExtend &Out ) = 0;

		/**
			@brief �Փ˔���
			@author �t���`
			@param Ray			[in] �n�_����I�_�����Ԑ���
			@param Out			[out] �Փˌ���
			@param Box			[out] �Փ˂������b�V����OBB
			@retval false	�Փ˂��Ȃ�
			@retval true	�Փ˂���

			�}�b�v���f�������R���W�����f�[�^�ɑ΂��āA
			�_��Ray�Ŏ����ړ��������ꍇ�̃R���W�������������܂��B
		*/
		virtual Bool HitCheckByRay( const Collision::CLine3D &Ray, Renderer::SCollisionResultExtend &Out, Collision::CBox &Box ) = 0;

		/**
			@brief �R���W�������f���\��
			@author �t���`
			@param pLine		[in] ���C���v���~�e�B�u�C���^�[�t�F�C�X

			�}�b�v���f�������R���W�����f�[�^��Renderer::Object::ILine3D���g����<BR>
			���o����悤�ɕ`�悵�܂��B
		*/
		virtual void CreateCollisionDrawPrimitive( Renderer::Object::ILine3D *pLine ) = 0;
	};
}
}

#pragma once


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Scene
{
	/**
		@brief �V�[�����f���A�N�^�[�p�C���^�[�t�F�C�X
		@author �t���`

		�V�[���Ǘ����ꂽ���f���A�N�^�[�������ׂ̃C���^�[�t�F�C�X�ł��B
	*/
	class IModelActor : public Math::Style
	{
	public:
		virtual ~IModelActor() {}

		/**
			@brief �L�����`�F�b�N
			@author �t���`
			@retval true ����
			@retval false �L��

			�C���^�[�t�F�C�X���L�����������𒲂ׂ܂��B
		*/
		virtual Bool IsInvalid( void ) = 0;

		/**
			@brief �Q�ƃJ�E���^�f�N�������g
			@author �t���`
			@return �f�N�������g��̎Q�ƃJ�E���g

			�Q�ƃJ�E���^���f�N�������g���A<BR>
			�Q�ƃJ�E���g��0�ɂȂ������_�Ń��������������܂��B
		*/
		virtual Sint32 Release( void ) = 0;

		/**
			@brief �Q�ƃJ�E���^�C���N�������g
			@author �t���`
			@return �C���N�������g��̎Q�ƃJ�E���g

			�Q�ƃJ�E���^���C���N�������g���܂��B<BR>
			�C���N�������g�����Q�ƃJ�E���g��Release()���ĂԂ��Ƃɂ��f�N�������g����܂��B<BR>
			AddRef()�������C���^�[�t�F�C�X�͕K��Release()�ŉ�����Ă��������B
		*/
		virtual Sint32 AddRef( void	) = 0;

		/**
			@brief �`�惊�N�G�X�g
			@author �t���`

			ISceneManager�ɑ΂��ă����_�����O���N�G�X�g�𔭍s���܂��B<BR>
			�擾����ISceneManager��Begin()/End()���łȂ��ꍇ���̊֐��͎��s���܂��B
		*/
		virtual void RenderingRequest( void ) = 0;

		/**
			@brief �J�����O�p�o�E���f�B���O�����_�����O
			@author �t���`
			@param pLine	[in] ���C���v���~�e�B�u�C���^�[�t�F�C�X

			�o�E���f�B���O�{�b�N�X���w�肵�����C���f�[�^�ɑ΂��Ēǉ����܂��B
		*/
		virtual void RenderingBounding( Renderer::Object::ILine3D *pLine ) = 0;

		/**
			@brief ���W�ϊ�������
			@author �t���`

			�A�N�^�[�̍��W�ϊ������������܂��B<BR>
			�A�j���[�V�����̏��Ȃǂ����̊֐����ł��ׂď���������܂��B
		*/
		virtual void TransformReset( void ) = 0;

		/**
			@brief ���W�ϊ��X�V
			@author �t���`

			�A�N�^�[�̍��W�ϊ����X�V���܂��B<BR>
			�A�j���[�V�����̏��Ȃǂ����̊֐����ł��ׂčX�V����܂��B<BR>
			�����I�ɂ́@TransformUpdateCollisionOnly() �� TransformUpdateActorOnly() ���Ăяo���Ă��܂��B
		*/
		virtual void TransformUpdate( void ) = 0;

		/**
			@brief ���W�ϊ��X�V
			@author �t���`

			�A�N�^�[�̃R���W�����̍��W�ϊ����X�V���܂��B<BR>
			�R���W�����Ɋ֌W����f�[�^�������ōX�V����܂��B
		*/
		virtual void TransformUpdateCollisionOnly( void ) = 0;

		/**
			@brief ���W�ϊ��X�V
			@author �t���`

			�A�N�^�[�̍��W�ϊ����X�V���܂��B<BR>
			�`��p�̃A�N�^�[�������X�V����܂��B
		*/
		virtual void TransformUpdateActorOnly( void ) = 0;

		/**
			@brief ���f���ɑ΂��ăA�j���[�V�����f�[�^�����擾
			@author �t���`
			@return	�A�j���[�V������

			�A�N�^�[�̏�������A�j���[�V�����̐����擾���܂��B
		*/
		virtual Sint32 GetAnimationCount( void ) = 0;

		/**
			@brief �A�j���[�V�����f�[�^�̍ŏI���Ԃ��擾
			@author �t���`
			@param AnimationNo		[in] �K�p����A�j���[�V�����ԍ�
			@return	�A�j���[�V�����̍ŏI����

			�A�j���[�V�����̍ŏI�t���[�����擾���܂��B
		*/
		virtual Float GetAnimationLastTime( Sint32 AnimationNo ) = 0;

		/**
			@brief ���f���ɑ΂��ăA�j���[�V�����f�[�^���X�V
			@author �t���`
			@param AnimationNo		[in] �K�p����A�j���[�V�����ԍ�
			@param fAnimationTime	[in] �A�j���[�V�����̎��ԁi�P�ʂ͍쐬�����c�[���ɂ��j

			�P��̃A�j���[�V�����f�[�^�̍X�V�����܂��B
		*/
		virtual void UpdateAnimation( Sint32 AnimationNo, Float fAnimationTime ) = 0;

		/**
			@brief ���f���ɑ΂��ăA�j���[�V�����f�[�^���X�V
			@author �t���`
			@param AnimationNo1		[in] �K�p����A�j���[�V�����ԍ�
			@param fAnimationTime1	[in] �A�j���[�V�����̎��ԁi�P�ʂ͍쐬�����c�[���ɂ��j
			@param AnimationNo2		[in] �K�p����A�j���[�V�����ԍ�
			@param fAnimationTime2	[in] �A�j���[�V�����̎��ԁi�P�ʂ͍쐬�����c�[���ɂ��j
			@param fWeight			[in] �u�����h�����i0.0f�̎�AnimationNo0�A1.0�̎�AnimationNo1)

			�Q�̃A�j���[�V�������u�����h���ăA�j���[�V�����f�[�^���X�V���܂��B
		*/
		virtual void UpdateAnimation( Sint32 AnimationNo1, Float fAnimationTime1, Sint32 AnimationNo2, Float fAnimationTime2, Float fWeight ) = 0;

		/**
			@brief �J�����O�����ɗL���ݒ�
			@author �t���`
			@param IsEnable	[in] �J�����O�̗L��

			���f�����̊e�A�N�^�[�ɑ΂��ăr���[�t���X�^���J�����O���s������ݒ肵�܂��B<BR>
			�r���[�t���X�^���J�����O�Ƃ̓J�����̕`��̈���ɂȂ��A�N�^�[��`��Ɋւ����A�̏�������<BR>
			�Ȃ����߂̏����ŁA�s������CPU���ׂ͑����܂�����ʊO�ɏo��A�N�^�[�ɑ΂��Ă̕`�敉�ׂ��y���ł��܂��B
		*/
		virtual void SetCullTestEnable( Bool IsEnable ) = 0;

		/**
			@brief ���f�����̃t���[�����擾
			@author �t���`
			@return	���f�����̃t���[���̐�

			���f�����̃t���[���̐����擾���܂��B<BR>
			�X�L�����b�V���Ɋ֘A�t�����Ă���t���[����<BR>
			�����I�ɂ̓{�[���ɂȂ�܂��B
		*/
		virtual Sint32 GetFrameCount( void ) = 0;

		/**
			@brief ���f�����̃t���[�����擾
			@author �t���`
			@return	���f�����̃t���[���̐�

			���f�����̃t���[���̐����擾���܂��B
		*/
		virtual Sint32 Frame_GetIndex( const char *pName ) = 0;

		/**
			@brief �t���[���̕ϊ��s����擾
			@author �t���`
			@param Index	[in] �t���[���̔ԍ�
			@return	�t���[���̕ϊ��s��

			�t���[���̕ϊ��s����擾���܂��B
		*/
		virtual Math::Matrix &Frame_GetTransformLocal( Sint32 Index ) = 0;

		/**
			@brief �t���[���̕ϊ��s����擾
			@author �t���`
			@param Index	[in] �t���[���̔ԍ�
			@return	�t���[���̕ϊ��s��

			�t���[���̕ϊ��s����擾���܂��B
		*/
		virtual Math::Matrix &Frame_GetTransformWorld( Sint32 Index ) = 0;

		/**
			@brief ���f�����̃��b�V�����擾
			@author �t���`
			@return	���f�����̃��b�V���̐�

			���f�����̃��b�V���̐����擾���܂��B<BR>
			���b�V���̐����`��A�N�^�[�̐��ɂȂ�܂��B
		*/
		virtual Sint32 GetMeshCount( void ) = 0;

		/**
			@brief ���f�����̃��b�V���`��ON/OFF
			@author �t���`
			@param Index		[in] ���b�V���ԍ�
			@param IsDrawEnable	[in] �`�悷�邩�ۂ�

			���f�����̃��b�V����`�悷�邩�ǂ�����ݒ肵�܂��B
		*/
		virtual void GetMesh_DrawEnable( Sint32 Index, Bool IsDrawEnable ) = 0;

		/**
			@brief ���b�V�����̃}�e���A�����擾
			@author �t���`
			@param MeshIndex	[in] ���b�V���ԍ�
			@return	���b�V�����̃}�e���A����

			���b�V�����̃}�e���A�������擾���܂��B
		*/
		virtual Sint32 GetMeshMaterialCount( Sint32 MeshIndex ) = 0;

		/**
			@brief �}�e���A���̃V�F�[�_�[�ݒ�
			@author �t���`
			@param MeshIndex		[in] ���b�V���ԍ�
			@param MaterialIndex	[in] �}�e���A���ԍ�
			@param pShader			[in] �V�F�[�_�[

			���b�V�����̃}�e���A���̃V�F�[�_�[��ݒ肵�܂��B
		*/
		virtual void MeshMaterial_SetShader( Sint32 MeshIndex, Sint32 MaterialIndex, Renderer::Shader::IShader *pShader ) = 0;

		/**
			@brief �}�e���A���̊g�U���ːF�ݒ�
			@author �t���`
			@param MeshIndex		[in] ���b�V���ԍ�
			@param MaterialIndex	[in] �}�e���A���ԍ�
			@param vColor			[in] �F

			���b�V�����̃}�e���A���̊g�U���ːF��ݒ肵�܂��B
		*/
		virtual void MeshMaterial_SetMaterialColor( Sint32 MeshIndex, Sint32 MaterialIndex, Math::Vector4D &vColor ) = 0;

		/**
			@brief �}�e���A���̎��Ȕ����F�ݒ�
			@author �t���`
			@param MeshIndex		[in] ���b�V���ԍ�
			@param MaterialIndex	[in] �}�e���A���ԍ�
			@param vColor			[in] �F

			���b�V�����̃}�e���A���̎��Ȕ����F��ݒ肵�܂��B
		*/
		virtual void MeshMaterial_SetEmissiveColor( Sint32 MeshIndex, Sint32 MaterialIndex, Math::Vector4D &vColor )										= 0;

		/**
			@brief �}�e���A���̋��ʔ��ːF�ݒ�
			@author �t���`
			@param MeshIndex		[in] ���b�V���ԍ�
			@param MaterialIndex	[in] �}�e���A���ԍ�
			@param vColor			[in] �F

			���b�V�����̃}�e���A���̋��ʔ��ːF��ݒ肵�܂��B
		*/
		virtual void MeshMaterial_SetSpecularColor( Sint32 MeshIndex, Sint32 MaterialIndex, Math::Vector4D &vColor )										= 0;

		/**
			@brief �}�e���A���̋��ʔ��˂̋����ݒ�
			@author �t���`
			@param MeshIndex		[in] ���b�V���ԍ�
			@param MaterialIndex	[in] �}�e���A���ԍ�
			@param fParam			[in] ����

			���b�V�����̃}�e���A���̋��ʔ��˂̋�����ݒ肵�܂��B
		*/
		virtual void MeshMaterial_SetSpecularRefractive( Sint32 MeshIndex, Sint32 MaterialIndex, Float fParam )									= 0;

		/**
			@brief �}�e���A���̋��ʔ��˂̍r���ݒ�
			@author �t���`
			@param MeshIndex		[in] ���b�V���ԍ�
			@param MaterialIndex	[in] �}�e���A���ԍ�
			@param fParam			[in] �r��

			���b�V�����̃}�e���A���̋��ʔ��˂̍r����ݒ肵�܂��B
		*/
		virtual void MeshMaterial_SetSpecularRoughly( Sint32 MeshIndex, Sint32 MaterialIndex, Float fParam )									= 0;

		/**
			@brief �}�e���A���̕`��^�C�v�ݒ�
			@author �t���`
			@param MeshIndex		[in] ���b�V���ԍ�
			@param MaterialIndex	[in] �}�e���A���ԍ�
			@param Type				[in] �`��^�C�v

			���b�V�����̃}�e���A���̕`��^�C�v��ݒ肵�܂��B
		*/
		virtual void MeshMaterial_SetDrawType( Sint32 MeshIndex, Sint32 MaterialIndex, eDrawType Type )											= 0;

		/**
			@brief �}�e���A���̃e�N�X�`���ݒ�
			@author �t���`
			@param MeshIndex		[in] ���b�V���ԍ�
			@param MaterialIndex	[in] �}�e���A���ԍ�
			@param pTexture			[in] �e�N�X�`��

			���b�V�����̃}�e���A���̃e�N�X�`����ݒ肵�܂��B
		*/
		virtual void MeshMaterial_SetTexture( Sint32 MeshIndex, Sint32 MaterialIndex, Renderer::ITexture *pTexture )										= 0;

		/**
			@brief �}�e���A���̃e�N�X�`��UV�̃I�t�Z�b�g�ݒ�
			@author �t���`
			@param MeshIndex		[in] ���b�V���ԍ�
			@param MaterialIndex	[in] �}�e���A���ԍ�
			@param vOffset			[in] �I�t�Z�b�g�i0.0->1.0)

			���b�V�����̃}�e���A���̃e�N�X�`��UV�̃I�t�Z�b�g��ݒ肵�܂��B
		*/
		virtual void MeshMaterial_SetTextureOffset( Sint32 MeshIndex, Sint32 MaterialIndex, Math::Vector2D &vOffset )									= 0;

		/**
			@brief �R���W��������
			@author �t���`

			�A�N�^�[�ɑ΂��ẴR���W��������p�̃C���^�[�t�F�C�X�𐶐����܂��B<BR>
			������s����Collision_***()�n�̊֐����L���ɂȂ�܂��B
		*/
		virtual void Collision_Create( void ) = 0;

		/**
			@brief �R���W�����L���ݒ�
			@author �t���`
			@param Index	[in] �t���[���ԍ�
			@param IsEnable	[in] true�̎��R���W����ON�i�f�t�H���g��ON�j

			�w��ԍ��̃t���[���̃R���W������ON/OFF���܂��B
		*/
		virtual void Collision_SetEnable( Sint32 Index, Bool IsEnable ) = 0;

		/**
			@brief �R���W�����L���ݒ�
			@author �t���`
			@param pName	[in] ����
			@param IsEnable	[in] true�̎��R���W����ON�i�f�t�H���g��ON�j

			�w�薼�̃t���[���̃R���W������ON/OFF���܂��B
		*/
		virtual void Collision_SetEnable( const char *pName, Bool IsEnable ) = 0;

		/**
			@brief �R���W�����f�[�^�`��
			@author �t���`
			@param pLine	[in] �`��p���C���v���~�e�B�u�C���^�[�t�F�C�X

			�����蔻��f�[�^�������_�����O���邽�߂̊֐��ł��B
		*/
		virtual void Collision_Rendering( Renderer::Object::ILine3D *pLine ) = 0;

		/**
			@brief �R���W�����̌��ʎ擾
			@author �t���`
			@param FrameNo	[in,out] �Փ˂����t���[���ԍ��i�[��
			@param vPos		[in,out] �Փ˂����ʒu�i�[��

			�����蔻��f�[�^���擾���܂��B<BR>
			�����_�ł͏Փ˂�����܂��Ȉʒu�ƏՓ˂���<BR>
			�t���[���ԍ������擾���邱�Ƃ͂ł��܂���B
		*/
		virtual void Collision_GetResult( Sint32 &FrameNo, Math::Vector3D &vPos ) = 0;

		/**
			@brief �R���W�����`�F�b�N
			@author �t���`
			@param pSrc	[in] �`�F�b�N����IModelActor

			�w�肳�ꂽ�f�[�^�Ƃ̏Փˌ��o���s���܂��B<BR>
			�Փ˂̌��ʂ�Collision_GetResult()�Ŏ擾�ł��܂��B
		*/
		virtual Bool Collision_Check( IModelActor *pSrc ) = 0;

		/**
			@brief �R���W�����`�F�b�N
			@author �t���`
			@param Src	[in] �`�F�b�N����{�b�N�X�f�[�^

			�w�肳�ꂽ�f�[�^�Ƃ̏Փˌ��o���s���܂��B<BR>
			�Փ˂̌��ʂ�Collision_GetResult()�Ŏ擾�ł��܂��B
		*/
		virtual Bool Collision_Check( Collision::CBox &Src ) = 0;

		/**
			@brief �R���W�����`�F�b�N
			@author �t���`
			@param Src	[in] �`�F�b�N���郉�C���f�[�^

			�w�肳�ꂽ�f�[�^�Ƃ̏Փˌ��o���s���܂��B<BR>
			�Փ˂̌��ʂ�Collision_GetResult()�Ŏ擾�ł��܂��B
		*/
		virtual Bool Collision_Check( Collision::CLine3D &Src ) = 0;

		/**
			@brief �R���W�����`�F�b�N
			@author �t���`
			@param Src	[in] �`�F�b�N����_�f�[�^

			�w�肳�ꂽ�f�[�^�Ƃ̏Փˌ��o���s���܂��B<BR>
			�Փ˂̌��ʂ�Collision_GetResult()�Ŏ擾�ł��܂��B
		*/
		virtual Bool Collision_Check( Math::Vector3D &Src ) = 0;

		/**
			@brief �R���W�����`�F�b�N
			@author �t���`
			@param Src			[in] �`�F�b�N����_�f�[�^
			@param pSceneMgr	[in] �����_�����O���s�����V�[���̃C���^�[�t�F�C�X

			�X�N���[�����W�Ƃ̏Փˌ��o���s���܂��B<BR>
			�Փ˂̌��ʂ�Collision_GetResult()�Ŏ擾�ł��܂��B
		*/
		virtual Bool Collision_CheckOnScreen( Math::Vector2D &Src, ISceneManager *pSceneMgr ) = 0;

		/**
			@brief �Փ˔���
			@author �t���`
			@param Ray			[in] �n�_����I�_�����Ԑ���
			@retval false	�Փ˂��Ȃ�
			@retval true	�Փ˂���

			�}�b�v���f�������R���W�����f�[�^�ɑ΂��āA
			�_��Ray�Ŏ����ړ��������ꍇ�̃R���W�������������܂��B
		*/
		virtual Bool HitCheckByRay( const Collision::CLine3D &Ray ) = 0;

		/**
			@brief �Փ˔���
			@author �t���`
			@param Ray			[in] �n�_����I�_�����Ԑ���
			@param Box			[out] �Փ˂������b�V����OBB
			@retval false	�Փ˂��Ȃ�
			@retval true	�Փ˂���

			�}�b�v���f�������R���W�����f�[�^�ɑ΂��āA
			�_��Ray�Ŏ����ړ��������ꍇ�̃R���W�������������܂��B
		*/
		virtual Bool HitCheckByRay( const Collision::CLine3D &Ray, Collision::CBox &Box ) = 0;

		/**
			@brief �Փ˔���
			@author �t���`
			@param Ray			[in] �n�_����I�_�����Ԑ���
			@param Out			[out] �Փˌ���
			@retval false	�Փ˂��Ȃ�
			@retval true	�Փ˂���

			�}�b�v���f�������R���W�����f�[�^�ɑ΂��āA
			�_��Ray�Ŏ����ړ��������ꍇ�̃R���W�������������܂��B
		*/
		virtual Bool HitCheckByRay( const Collision::CLine3D &Ray, Renderer::SCollisionResult &Out ) = 0;

		/**
			@brief �Փ˔���
			@author �t���`
			@param Ray			[in] �n�_����I�_�����Ԑ���
			@param Out			[out] �Փˌ���
			@param Box			[out] �Փ˂������b�V����OBB
			@retval false	�Փ˂��Ȃ�
			@retval true	�Փ˂���

			�}�b�v���f�������R���W�����f�[�^�ɑ΂��āA
			�_��Ray�Ŏ����ړ��������ꍇ�̃R���W�������������܂��B
		*/
		virtual Bool HitCheckByRay( const Collision::CLine3D &Ray, Renderer::SCollisionResult &Out, Collision::CBox &Box ) = 0;

		/**
			@brief �Փ˔���
			@author �t���`
			@param Ray			[in] �n�_����I�_�����Ԑ���
			@param Out			[out] �Փˌ���
			@retval false	�Փ˂��Ȃ�
			@retval true	�Փ˂���

			�}�b�v���f�������R���W�����f�[�^�ɑ΂��āA
			�_��Ray�Ŏ����ړ��������ꍇ�̃R���W�������������܂��B
		*/
		virtual Bool HitCheckByRay( const Collision::CLine3D &Ray, Renderer::SCollisionResultExtend &Out ) = 0;

		/**
			@brief �Փ˔���
			@author �t���`
			@param Ray			[in] �n�_����I�_�����Ԑ���
			@param Out			[out] �Փˌ���
			@param Box			[out] �Փ˂������b�V����OBB
			@retval false	�Փ˂��Ȃ�
			@retval true	�Փ˂���

			�}�b�v���f�������R���W�����f�[�^�ɑ΂��āA
			�_��Ray�Ŏ����ړ��������ꍇ�̃R���W�������������܂��B
		*/
		virtual Bool HitCheckByRay( const Collision::CLine3D &Ray, Renderer::SCollisionResultExtend &Out, Collision::CBox &Box ) = 0;

		/**
			@brief �R���W�������f���\��
			@author �t���`
			@param pLine		[in] ���C���v���~�e�B�u�C���^�[�t�F�C�X

			�}�b�v���f�������R���W�����f�[�^��Renderer::Object::ILine3D���g����<BR>
			���o����悤�ɕ`�悵�܂��B
		*/
		virtual void CreateCollisionDrawPrimitive( Renderer::Object::ILine3D *pLine ) = 0;
	};
}
}

#pragma once


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Scene
{
	/**
		@brief �V�[���A�N�^�[�p�C���^�[�t�F�C�X
		@author �t���`

		�V�[���Ǘ����ꂽ�I�u�W�F�N�g�������ׂ̃C���^�[�t�F�C�X�ł��B
	*/
	class IMapActor
	{
	public:
		virtual ~IMapActor() {}

		/**
			@brief �L�����`�F�b�N
			@author �t���`
			@retval true ����
			@retval false �L��

			�C���^�[�t�F�C�X���L�����������𒲂ׂ܂��B
		*/
		virtual Bool IsInvalid( void ) = 0;

		/**
			@brief �Q�ƃJ�E���^�f�N�������g
			@author �t���`
			@return �f�N�������g��̎Q�ƃJ�E���g

			�Q�ƃJ�E���^���f�N�������g���A<BR>
			�Q�ƃJ�E���g��0�ɂȂ������_�Ń��������������܂��B
		*/
		virtual Sint32 Release( void ) = 0;

		/**
			@brief �Q�ƃJ�E���^�C���N�������g
			@author �t���`
			@return �C���N�������g��̎Q�ƃJ�E���g

			�Q�ƃJ�E���^���C���N�������g���܂��B<BR>
			�C���N�������g�����Q�ƃJ�E���g��Release()���ĂԂ��Ƃɂ��f�N�������g����܂��B<BR>
			AddRef()�������C���^�[�t�F�C�X�͕K��Release()�ŉ�����Ă��������B
		*/
		virtual Sint32 AddRef( void	) = 0;

		/**
			@brief �`�惊�N�G�X�g
			@author �t���`

			ISceneManager�ɑ΂��ă����_�����O���N�G�X�g�𔭍s���܂��B<BR>
			�擾����ISceneManager��Begin()/End()���łȂ��ꍇ���̊֐��͎��s���܂��B
		*/
		virtual void RenderingRequest( void ) = 0;

		/**
			@brief �J�����O�p�o�E���f�B���O�����_�����O
			@author �t���`
			@param pLine	[in] ���C���v���~�e�B�u�C���^�[�t�F�C�X

			�o�E���f�B���O�{�b�N�X���w�肵�����C���f�[�^�ɑ΂��Ēǉ����܂��B
		*/
		virtual void RenderingBounding( Renderer::Object::ILine3D *pLine ) = 0;

		/**
			@brief �Z���̑S�̐��擾
			@author �t���`
			@return �Z���̑S�̐�

			�}�b�v���̃Z���̐����擾���܂��B
		*/
		virtual Sint32 GetCellCount( void ) = 0;

		/**
			@brief �Z���̕`�搔�擾
			@author �t���`
			@return �Z���̕`�搔

			�}�b�v���̕`�悳�ꂽ�Z���̐����擾���܂��B
		*/
		virtual Sint32 GetRenderingCellCount( void ) = 0;

		/**
			@brief �Փ˔���
			@author �t���`
			@param Ray			[in] �n�_����I�_�����Ԑ���
			@retval false	�Փ˂��Ȃ�
			@retval true	�Փ˂���

			�}�b�v���f�������R���W�����f�[�^�ɑ΂��āA<BR>
			�_��Ray�Ŏ����ړ��������ꍇ�̃R���W�������������܂��B
		*/
		virtual Bool HitCheckByRay( const Collision::CLine3D &Ray ) = 0;

		/**
			@brief �Փ˔���
			@author �t���`
			@param Ray			[in] �n�_����I�_�����Ԑ���
			@param Box			[out] �Փ˂������b�V����OBB
			@retval false	�Փ˂��Ȃ�
			@retval true	�Փ˂���

			�}�b�v���f�������R���W�����f�[�^�ɑ΂��āA<BR>
			�_��Ray�Ŏ����ړ��������ꍇ�̃R���W�������������܂��B
		*/
		virtual Bool HitCheckByRay( const Collision::CLine3D &Ray, Collision::CBox &Box ) = 0;

		/**
			@brief �Փ˔���
			@author �t���`
			@param Ray			[in] �n�_����I�_�����Ԑ���
			@param Out			[out] �Փˌ���
			@retval false	�Փ˂��Ȃ�
			@retval true	�Փ˂���

			�}�b�v���f�������R���W�����f�[�^�ɑ΂��āA<BR>
			�_��Ray�Ŏ����ړ��������ꍇ�̃R���W�������������܂��B
		*/
		virtual Bool HitCheckByRay( const Collision::CLine3D &Ray, Renderer::SCollisionResult &Out ) = 0;

		/**
			@brief �Փ˔���
			@author �t���`
			@param Ray			[in] �n�_����I�_�����Ԑ���
			@param Out			[out] �Փˌ���
			@param Box			[out] �Փ˂������b�V����OBB
			@retval false	�Փ˂��Ȃ�
			@retval true	�Փ˂���

			�}�b�v���f�������R���W�����f�[�^�ɑ΂��āA<BR>
			�_��Ray�Ŏ����ړ��������ꍇ�̃R���W�������������܂��B
		*/
		virtual Bool HitCheckByRay( const Collision::CLine3D &Ray, Renderer::SCollisionResult &Out, Collision::CBox &Box ) = 0;

		/**
			@brief �Փ˔���
			@author �t���`
			@param Ray			[in] �n�_����I�_�����Ԑ���
			@param Out			[out] �Փˌ���
			@retval false	�Փ˂��Ȃ�
			@retval true	�Փ˂���

			�}�b�v���f�������R���W�����f�[�^�ɑ΂��āA<BR>
			�_��Ray�Ŏ����ړ��������ꍇ�̃R���W�������������܂��B
		*/
		virtual Bool HitCheckByRay( const Collision::CLine3D &Ray, Renderer::SCollisionResultExtend &Out ) = 0;

		/**
			@brief �Փ˔���
			@author �t���`
			@param Ray			[in] �n�_����I�_�����Ԑ���
			@param Out			[out] �Փˌ���
			@param Box			[out] �Փ˂������b�V����OBB
			@retval false	�Փ˂��Ȃ�
			@retval true	�Փ˂���

			�}�b�v���f�������R���W�����f�[�^�ɑ΂��āA<BR>
			�_��Ray�Ŏ����ړ��������ꍇ�̃R���W�������������܂��B
		*/
		virtual Bool HitCheckByRay( const Collision::CLine3D &Ray, Renderer::SCollisionResultExtend &Out, Collision::CBox &Box ) = 0;

		/**
			@brief �Փ˔���
			@author �t���`
			@param Ray			[in] �n�_����I�_�����Ԑ���
			@param fRadius		[in] �Փ˔��a
			@retval false	�Փ˂��Ȃ�
			@retval true	�Փ˂���

			�}�b�v���f�������R���W�����f�[�^�ɑ΂��āA<BR>
			�_��Ray�Ŏ����ړ��������ꍇ�̃R���W�������������܂��B
		*/
//		virtual Bool HitCheckBySphere( const Collision::CLine3D &Ray, Float fRadius ) = 0;

		/**
			@brief �Փ˔���
			@author �t���`
			@param Ray			[in] �n�_����I�_�����Ԑ���
			@param fRadius		[in] �Փ˔��a
			@param Box			[out] �Փ˂������b�V����OBB
			@retval false	�Փ˂��Ȃ�
			@retval true	�Փ˂���

			�}�b�v���f�������R���W�����f�[�^�ɑ΂��āA<BR>
			�_��Ray�Ŏ����ړ��������ꍇ�̃R���W�������������܂��B
		*/
//		virtual Bool HitCheckBySphere( const Collision::CLine3D &Ray, Float fRadius, Collision::CBox &Box ) = 0;

		/**
			@brief �Փ˔���
			@author �t���`
			@param Ray			[in] �n�_����I�_�����Ԑ���
			@param fRadius		[in] �Փ˔��a
			@param Out			[out] �Փˌ���
			@retval false	�Փ˂��Ȃ�
			@retval true	�Փ˂���

			�}�b�v���f�������R���W�����f�[�^�ɑ΂��āA<BR>
			�_��Ray�Ŏ����ړ��������ꍇ�̃R���W�������������܂��B
		*/
//		virtual Bool HitCheckBySphere( const Collision::CLine3D &Ray, Float fRadius, Renderer::SCollisionResultSphere &Out ) = 0;

		/**
			@brief �Փ˔���
			@author �t���`
			@param Ray			[in] �n�_����I�_�����Ԑ���
			@param fRadius		[in] �Փ˔��a
			@param Out			[out] �Փˌ���
			@param Box			[out] �Փ˂������b�V����OBB
			@retval false	�Փ˂��Ȃ�
			@retval true	�Փ˂���

			�}�b�v���f�������R���W�����f�[�^�ɑ΂��āA<BR>
			�_��Ray�Ŏ����ړ��������ꍇ�̃R���W�������������܂��B
		*/
//		virtual Bool HitCheckBySphere( const Collision::CLine3D &Ray, Float fRadius, Renderer::SCollisionResultSphere &Out, Collision::CBox &Box ) = 0;

		/**
			@brief �Փ˔���
			@author �t���`
			@param Ray			[in] �n�_����I�_�����Ԑ���
			@param fRadius		[in] �Փ˔��a
			@param Out			[out] �Փˌ���
			@retval false	�Փ˂��Ȃ�
			@retval true	�Փ˂���

			�}�b�v���f�������R���W�����f�[�^�ɑ΂��āA<BR>
			�_��Ray�Ŏ����ړ��������ꍇ�̃R���W�������������܂��B
		*/
//		virtual Bool HitCheckBySphere( const Collision::CLine3D &Ray, Float fRadius, Renderer::SCollisionResultSphereExtend &Out ) = 0;

		/**
			@brief �Փ˔���
			@author �t���`
			@param Ray			[in] �n�_����I�_�����Ԑ���
			@param fRadius		[in] �Փ˔��a
			@param Out			[out] �Փˌ���
			@param Box			[out] �Փ˂������b�V����OBB
			@retval false	�Փ˂��Ȃ�
			@retval true	�Փ˂���

			�}�b�v���f�������R���W�����f�[�^�ɑ΂��āA<BR>
			�_��Ray�Ŏ����ړ��������ꍇ�̃R���W�������������܂��B
		*/
//		virtual Bool HitCheckBySphere( const Collision::CLine3D &Ray, Float fRadius, Renderer::SCollisionResultSphereExtend &Out, Collision::CBox &Box ) = 0;

		/**
			@brief �R���W�������f���\��
			@author �t���`
			@param pLine		[in] ���C���v���~�e�B�u�C���^�[�t�F�C�X

			�}�b�v���f�������R���W�����f�[�^��Renderer::Object::ILine3D���g����<BR>
			���o����悤�ɕ`�悵�܂��B
		*/
		virtual void CreateCollisionDrawPrimitive( Renderer::Object::ILine3D *pLine ) = 0;
	};
}
}

#pragma once


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Scene
{
	/**
		@brief �V�[���J��������p�C���^�[�t�F�C�X
		@author �t���`

		�V�[���̃J�����𑀍삷�邽�߂̃C���^�[�t�F�C�X�ł��B
	*/
	class ICamera
	{
	public:
		virtual ~ICamera() {}

		/**
			@brief �L�����`�F�b�N
			@author �t���`
			@retval true ����
			@retval false �L��

			�C���^�[�t�F�C�X���L�����������𒲂ׂ܂��B
		*/
		virtual Bool IsInvalid( void ) = 0;

		/**
			@brief �Q�ƃJ�E���^�f�N�������g
			@author �t���`
			@return �f�N�������g��̎Q�ƃJ�E���g

			�Q�ƃJ�E���^���f�N�������g���A<BR>
			�Q�ƃJ�E���g��0�ɂȂ������_�Ń��������������܂��B
		*/
		virtual Sint32 Release( void ) = 0;

		/**
			@brief �Q�ƃJ�E���^�C���N�������g
			@author �t���`
			@return �C���N�������g��̎Q�ƃJ�E���g

			�Q�ƃJ�E���^���C���N�������g���܂��B<BR>
			�C���N�������g�����Q�ƃJ�E���g��Release()���ĂԂ��Ƃɂ��f�N�������g����܂��B<BR>
			AddRef()�������C���^�[�t�F�C�X�͕K��Release()�ŉ�����Ă��������B
		*/
		virtual Sint32 AddRef( void	) = 0;

		/**
			@brief ���[���h���X�N���[�����W�ϊ��s��擾
			@author �t���`
			@return �ϊ��s��

			���[���h��Ԃ���X�N���[�����W�ւ̋t�ϊ��s����擾���܂��B
		*/
		virtual const Math::Matrix &WorldToScreen( void ) = 0;

		/**
			@brief ���[���h���r���[�ϊ��s��擾
			@author �t���`
			@return �ϊ��s��

			���[���h��Ԃ���J������Ԃւ̋t�ϊ��s����擾���܂��B
		*/
		virtual const Math::Matrix &WorldToView( void ) = 0;

		/**
			@brief �X�N���[�������[���h�ϊ��s��擾
			@author �t���`
			@return �ϊ��s��

			�X�N���[�����W���烏�[���h��Ԃւ̋t�ϊ��s����擾���܂��B
		*/
		virtual const Math::Matrix &ScreenToWorld( void ) = 0;

		/**
			@brief �r���[�����[���h�ϊ��s��擾
			@author �t���`
			@return �ϊ��s��

			�J������Ԃ��烏�[���h��Ԃւ̋t�ϊ��s����擾���܂��B
		*/
		virtual const Math::Matrix &ViewToWorld( void ) = 0;

		/**
			@brief �J�����ʒu�擾
			@author �t���`
			@return �J�����ʒu�x�N�g��

			���[���h��Ԃł̃J�����̈ʒu���擾���܂��B
		*/
		virtual const Math::Vector3D &Position( void ) = 0;

		/**
			@brief �j�A�N���b�v�l�擾
			@author �t���`

			@return �j�A�N���b�v�l

			�j�A�N���b�v�l���擾���܂��B
		*/
		virtual Float GetNearClip( void ) = 0;

		/**
			@brief �t�@�[�N���b�v�l�擾
			@author �t���`

			@return �t�@�[�N���b�v�l

			�t�@�[�N���b�v�l���擾���܂��B
		*/
		virtual Float GetFarClip( void ) = 0;

		/**
			@brief �v���W�F�N�V�����s��X�V
			@author �t���`

			@param fNearClip	[in] �j�A�N���b�v�l
			@param fFarClip		[in] �t�@�[�N���b�v�l
			@param FovAngle		[in] ��p�i1��65536�Ƃ����p�x�j
			@param Width		[in] �\������
			@param Height		[in] �\���c��

			�v���W�F�N�V�����s����X�V���܂��B<BR>
			�J�������g�p����ꍇ�ɂ͕K�����̊֐��Ńv���W�F�N�V�������쐬���ĉ������B<BR>
			�܂�FovAngle��0���w�肷��ƕ��s���e�ɂȂ�܂��B
		*/
		virtual void UpdateProjection( Float fNearClip, Float fFarClip, Sint32 FovAngle, Sint32 Width, Sint32 Height ) = 0;

		/**
			@brief �J�����f�[�^������
			@author �t���`

			�J�����f�[�^�����������܂��B<BR>
			���W(0,0,0)����Z��+��������������ԂɂȂ�܂��B
		*/
		virtual void Reset( void ) = 0;

		/**
			@brief �J�����f�[�^�X�V
			@author �t���`

			�J�����̃f�[�^���X�V���܂��B<BR>
			�e��s���o�E���f�B���O�{�b�N�X�Ȃǂ�<BR>
			���̊֐����Ăяo�����Ƃō쐬����܂��B
		*/
		virtual void Update( void ) = 0;

		/**
			@brief �J������ϊ�
			@author �t���`

			@param vPosition	[in] �J�����̌��݈ʒu
			@param vTarget		[in] �J�����̃^�[�Q�b�g�ʒu
			@param Bank			[in] �o���N(�X��)�p�x

			CStyle���g�킸���ڃJ�����̎p������ݒ肵�܂��B
		*/
		virtual void SetTransformSimple( Math::Vector3D &vPosition, Math::Vector3D &vTarget, Sint32 Bank ) = 0;

		/**
			@brief �J������ϊ�
			@author �t���`

			@param Style	[in] �J�����ϊ��pStyle

			CStyle�f�[�^�Œ�`���ꂽ�ϊ�������<BR>
			�J�����ɓK�p���܂��B<BR>
			�J�����Ŏg�p�����͈̂ړ�/��]�ɂȂ�܂��B
		*/
		virtual void SetTransform( Math::Style &Style ) = 0;

		/**
			@brief �J�����O�p�o�E���f�B���O�����_�����O
			@author �t���`
			@param pLine	[in] ���C���v���~�e�B�u�C���^�[�t�F�C�X

			�o�E���f�B���O�{�b�N�X���w�肵�����C���f�[�^�ɑ΂��Ēǉ����܂��B
		*/
		virtual void RenderingBounding( Renderer::Object::ILine3D *pLine ) = 0;
	};
}
}

#pragma once


/**
	@file
	@brief �V�[���Ǘ��n�N���X
	@author �t���`
*/


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Scene
{
	/**
		@brief �V�[���Ǘ��p�C���^�[�t�F�C�X
		@author �t���`

		�V�[���Ǘ����s�����߂̃C���^�[�t�F�C�X�ł��B
	*/
	class ISceneManager : public IInterface
	{
	protected:
		virtual ~ISceneManager() {}

	public:
		/**
			@brief �V�[���A�N�^�[�擾
			@author �t���`
			@param pObject			[in] �A�N�^�[�Ɋ֘A�t����`��C���^�[�t�F�C�X
			@param InstanceCount	[in] �C���X�^���X��
			@return	IInstanceModelActor�C���^�[�t�F�C�X

			@note
			ISceneManager�Ń����_�����O���s�����߂̃A�N�^�[���擾���܂��B<BR>
			�W�I���g���C���X�^���V���O���s�����߂̓���ȃA�N�^�[�ŁA<BR>
			���̃A�N�^�[���炳��Ɍʂ̃R���g���[���[���擾���A���[���h�ϊ���{�[���̐ݒ���s���܂��B<BR>
			<B>�K��InitParameterUpdate�̌�Ɏ��s���Ă��������B</B>
		*/
		virtual IInstanceModelActor *CreateActor( Renderer::Object::IModel *pObject, Sint32 InstanceCount ) = 0;

		/**
			@brief �V�[���A�N�^�[�擾
			@author �t���`
			@param pObject	[in] �A�N�^�[�Ɋ֘A�t����`��C���^�[�t�F�C�X
			@return	IModelActor�C���^�[�t�F�C�X

			ISceneManager�Ń����_�����O���s�����߂̃A�N�^�[���擾���܂��B<BR>
			���[���h�ϊ��⃌���_�����O�̑����IModelActor���o�R���čs���܂��B<BR>
			<B>�K��InitParameterUpdate�̌�Ɏ��s���Ă��������B</B>
		*/
		virtual IModelActor *CreateActor( Renderer::Object::IModel *pObject ) = 0;

		/**
			@brief �V�[���A�N�^�[�擾
			@author �t���`
			@param pObject	[in] �A�N�^�[�Ɋ֘A�t����`��C���^�[�t�F�C�X
			@return	IMapActor�C���^�[�t�F�C�X

			ISceneManager�Ń����_�����O���s�����߂̃A�N�^�[���擾���܂��B<BR>
			���[���h�ϊ��⃌���_�����O�̑����IMapActor���o�R���čs���܂��B<BR>
			<B>�K��InitParameterUpdate�̌�Ɏ��s���Ă��������B</B>
		*/

		virtual IMapActor *CreateActor( Renderer::Object::IMapModel *pObject ) = 0;

		/**
			@brief �V�[���A�N�^�[�擾
			@author �t���`
			@param pObject	[in] �A�N�^�[�Ɋ֘A�t����`��C���^�[�t�F�C�X
			@return	IPrimitiveActor�C���^�[�t�F�C�X

			ISceneManager�Ń����_�����O���s�����߂̃A�N�^�[���擾���܂��B<BR>
			���[���h�ϊ��⃌���_�����O�̑����IPrimitiveActor���o�R���čs���܂��B<BR>
			<B>�K��InitParameterUpdate�̌�Ɏ��s���Ă��������B</B>
		*/
		virtual IPrimitiveActor *CreateActor( Renderer::Object::IPoint3D *pObject ) = 0;

		/**
			@brief �V�[���A�N�^�[�擾
			@author �t���`
			@param pObject	[in] �A�N�^�[�Ɋ֘A�t����`��C���^�[�t�F�C�X
			@return	IPrimitiveActor�C���^�[�t�F�C�X

			ISceneManager�Ń����_�����O���s�����߂̃A�N�^�[���擾���܂��B<BR>
			���[���h�ϊ��⃌���_�����O�̑����IPrimitiveActor���o�R���čs���܂��B<BR>
			<B>�K��InitParameterUpdate�̌�Ɏ��s���Ă��������B</B>
		*/
		virtual IPrimitiveActor *CreateActor( Renderer::Object::ILine3D *pObject ) = 0;

		/**
			@brief �V�[���A�N�^�[�擾
			@author �t���`
			@param pObject	[in] �A�N�^�[�Ɋ֘A�t����`��C���^�[�t�F�C�X
			@param IsLightmap		[in] 
			@pamra IsNormalmap		[in] 
			@param IsSpecularmap	[in] 
			@param IsEnvironmentmap	[in] 
			@return	IPrimitiveActor�C���^�[�t�F�C�X

			ISceneManager�Ń����_�����O���s�����߂̃A�N�^�[���擾���܂��B<BR>
			���[���h�ϊ��⃌���_�����O�̑����IPrimitiveActor���o�R���čs���܂��B<BR>
			<B>�K��InitParameterUpdate�̌�Ɏ��s���Ă��������B</B>
		*/
		virtual IPrimitiveActor *CreateActor( Renderer::Object::IPrimitive3D *pObject, Bool IsLightmap = false, Bool IsNormalmap = false, Bool IsSpecularmap = false, Bool IsEnvironmentmap = false ) = 0;

		/**
			@brief �V�[���A�N�^�[�擾
			@author �t���`
			@param pObject	[in] �A�N�^�[�Ɋ֘A�t����`��C���^�[�t�F�C�X
			@return	ISpriteActor�C���^�[�t�F�C�X

			ISceneManager�Ń����_�����O���s�����߂̃A�N�^�[���擾���܂��B<BR>
			���[���h�ϊ��⃌���_�����O�̑����ISpriteActor���o�R���čs���܂��B<BR>
			<B>�K��InitParameterUpdate�̌�Ɏ��s���Ă��������B</B>
		*/
		virtual ISpriteActor *CreateActor( Renderer::Object::ISprite3D *pObject ) = 0;

		/**
			@brief �V�[���A�N�^�[�擾
			@author �t���`
			@param pObject	[in] �A�N�^�[�Ɋ֘A�t����`��C���^�[�t�F�C�X
			@return	IParticleActor�C���^�[�t�F�C�X

			ISceneManager�Ń����_�����O���s�����߂̃A�N�^�[���擾���܂��B<BR>
			���[���h�ϊ��⃌���_�����O�̑����IParticleActor���o�R���čs���܂��B<BR>
			<B>�K��InitParameterUpdate�̌�Ɏ��s���Ă��������B</B>
		*/
		virtual IParticleActor *CreateActor( Renderer::Object::IFontSprite3D *pObject ) = 0;

		/**
			@brief �V�[���A�N�^�[�擾
			@author �t���`
			@param pObject	[in] �A�N�^�[�Ɋ֘A�t����`��C���^�[�t�F�C�X
			@return	IParticleActor�C���^�[�t�F�C�X

			ISceneManager�Ń����_�����O���s�����߂̃A�N�^�[���擾���܂��B<BR>
			���[���h�ϊ��⃌���_�����O�̑����IParticleActor���o�R���čs���܂��B<BR>
			<B>�K��InitParameterUpdate�̌�Ɏ��s���Ă��������B</B>
		*/
		virtual IParticleActor *CreateActor( Renderer::Object::IParticle *pObject ) = 0;

		/**
			@brief �V�[���J�����擾
			@author �t���`
			@return �J����

			�V�[���Ɋ֘A�t����ꂽ�J�������擾���܂��B
		*/
		virtual ICamera *GetCamera( void ) = 0;

		/**
			@brief �V�[��������
			@author �t���`

			�V�[���̃��C�g��t�H�O�Ȃǂ̃f�[�^�����Z�b�g���܂��B<BR>
			���̊֐���Begin()-End()���ŌĂяo���Ǝ��s���܂��B
		*/
		virtual void Reset( void ) = 0;

		/**
			@brief �V�[���J�n
			@author �t���`
			@param IsSort	[in] �V�[�����̃I�u�W�F�N�g���\�[�g���邩�ǂ���

			�V�[���Ǘ����J�n���܂��B<BR>
			���̎��_�ŃJ�����̃f�[�^���m�肵�܂��̂�<BR>
			���̊֐����Ăяo�������Ƃ̃J�����̍X�V�͑S�Ė����ł��B
		*/
		virtual void Begin( Bool IsSort ) = 0;

		/**
			@brief �V�[���I��
			@author �t���`

			�V�[���̊Ǘ����������܂��B
		*/
		virtual void End( void ) = 0;

		/**
			@brief �I���ҋ@
			@author �t���`

			ISceneManager�Ń����_�����O�����̊��������S�ɑҋ@���܂��B<BR>
			Begin()-End()�ȍ~����Ńf�[�^�̍\�z�������s���܂��̂ŁA<BR>
			�V�[���A���邢�̓V�[���ŗ��p���Ă��郊�\�[�X���������O��<BR>
			���̊֐��ŃV�[���̍\�z�����̏I����҂��ĉ������B<BR>
			�Ȃ��A�v���P�[�V�����̏I����(ICore::Run()=false)���ɂ͓����őS�ẴV�[����<BR>
			Abort()�������I�ɌĂ΂�܂��B
		*/
		virtual void Abort( void ) = 0;

		/**
			@brief �V�[�������_�����O
			@author �t���`
			@param IsDrawBuffer	[in] �����p�o�b�t�@�̕\��

			�V�[���̊Ǘ��ō\�z���ꂽ�V�[���������_�����O���܂��B<BR>
			���̊֐����R�[�������i�K�œ����ŕ`�揈�����J�n����܂��B<BR>
			�K��IRender::Begin()�`IRender::End()�ԂŌĂяo���Ă��������B
		*/
		virtual void Rendering( Bool IsDrawBuffer = false ) = 0;

		/**
			@brief �A���r�G���g���C�g�ݒ�
			@author �t���`
			@param vColorSky	[in] �V�[�����̓V���̊����̐F
			@param vColorEarth	[in] �V�[�����̒n�\�̊����̐F

			�V�[���̊�����ݒ肵�܂��B<BR>
			�������C�e�B���O���s�����߂ɁA�V���ƒn�\�̐F��ݒ肵�܂��B<BR>
			���̊֐���Begin()-End()���ŌĂяo���Ǝ��s���܂��B
		*/
		virtual void SetLightParameter_Ambient( const Math::Vector3D &vColorSky, const Math::Vector3D &vColorEarth ) = 0;

		/**
			@brief �f�B���N�V�������C�g�ݒ�
			@author �t���`
			@param vDirect	[in] �V�[�����̕��s�����̕���
			@param vColor	[in] �V�[�����̕��s�����̐F

			�V�[���ɑ債�ĂP�������s���������蓖�Ă邱�Ƃ��ł��܂��B<BR>
			���z�̂悤�ɗy�������ɑ��݂��A�I�u�W�F�N�g�̈ʒu�ɂ����<BR>
			���̕������ς��Ȃ��悤�ȃ��C�g�Ɍ����Ă��܂��B<BR>
			���̊֐���Begin()-End()���ŌĂяo���Ǝ��s���܂��B<BR>
			�܂��V�[�����[�h�̉e�������w�肵�Ă��鎞��vDirect�͖����ł��B<BR>
			�����Ɋւ��Ă�SetParameter_Shadow()�Ŏw�肵���l���g�p����܂��B
		*/
		virtual void SetLightParameter_Directional( const Math::Vector3D &vDirect, const Math::Vector3D &vColor ) = 0;

		/**
			@brief �|�C���g���C�g�ǉ�
			@author �t���`
			@param vPosition	[in] �V�[�����̓_�����̈ʒu
			@param vColor		[in] �V�[�����̓_�����̐F
			@param fDistance	[in] �V�[�����̓_�����̉e������

			�V�[���ɑ΂��ē_������ǉ����܂�<BR>
			�ő��32�̃��C�g��ݒ�ł��A���̂����ł��I�u�W�F�N�g�ɋ߂�<BR>
			4�̃��C�g���I�u�W�F�N�g�ɓK�p����܂��B<BR>
			���̊֐���Begin()-End()���ŌĂяo���Ǝ��s���܂��B
		*/
		virtual void SetLightParameter_AddPoint( const Math::Vector3D &vPosition, const Math::Vector3D &vColor, Float fDistance ) = 0;

		/**
			@brief �����_�����O���N�G�X�g���擾
			@author �t���`
			@return �����_�����O���N�G�X�g��

			�V�[���Ƀ��N�G�X�g�����_�����O�����擾���܂��B
		*/
		virtual Sint32 GetResult_RenderingRequestActorCount( void ) = 0;

		/**
			@brief �����_�����O���擾
			@author �t���`
			@return �����_�����O��

			�V�[���Ŏ��s���ꂽ�����_�����O�����擾���܂��B<BR>
			2Pass�n�̏��������J�E���g�����̂ŁA<BR>
			���N�G�X�g���ȏ�̒l�ɂȂ邱�Ƃ�����܂��B
		*/
		virtual Sint32 GetResult_RenderingActorCount( void ) = 0;

		/**
			@brief �V�[���̍\�z�ɂ����������Ԃ��擾
			@author �t���`
			@return �V�[���̍\�z�ɂ����������ԁi�P�t���[���ɑ΂��道�j

			�P�t���[��������̃V�[���\�z�ɂ����������Ԃ����Ŏ擾���܂��B
		*/
		virtual Sint32 GetResult_BackgroundThreadTime( void ) = 0;

		/**
			@brief �V�[���̕`��ɂ����������Ԃ��擾
			@author �t���`
			@return �V�[���̕`��ɂ����������ԁi�P�t���[���ɑ΂��道�j

			�P�t���[��������̃V�[���`��ɂ����������Ԃ����Ŏ擾���܂��B
		*/
		virtual Sint32 GetResult_RenderingTme( void ) = 0;

		/**
			@brief ���[�V�����u���[���x���̐ݒ�
			@author �t���`
			@param Level		[in] �g�p���郌�x��

			���[�V�����u���[�����̃��x����ݒ肵�܂��B<BR>
			MOTION_BLUR_FULL�w��̏ꍇ�̓��f���f�[�^�����Ă��Ė@����ێ����Ă���K�v������܂��B
		*/
		virtual void SetActorParameter_MotionBlur( eSceneMotionBlurQuarity MotionBlurQuarity ) = 0;

		/**
			@brief �e�̐����I�v�V������ON/OFF
			@author �t���`
			@param Type		[in] �e�����̕��@
			@param Priority	[in] �e�̃v���C�I���e�B
			@param fRadius	[in] �ۉe�̏ꍇ�̑傫��

			�V�[���ɓK�p�����e�������uSHADOW_TYPE_PROJECTION_*�v���uSHADOW_TYPE_SOFT_PROJECTION_*�v�̎���<BR>
			�����_�����O���郂�f�����e�𗎂Ƃ����ǂ�����ݒ肵�܂��B<BR>
			�e�𗎂Ƃ����f���ɂ͑��̃��f���̉e���������A�e�𗎂Ƃ��Ȃ����f���ɂ͑��̃��f���̉e�������܂��B
		*/
		virtual void SetActorParameter_ProjectionShadow( eProjectionShadowType Type, eProjectionShadowPriority Priority, Float fRadius = 0.0f ) = 0;

		/**
			@brief �V�[���S�̖̂��邳�̐ݒ�
			@author �t���`
			@param vBrightness	[in] �F

			�V�[���Ƀ��C�g�}�b�v����Ƃ������邳��ݒ肵�܂��B<BR>
			1.0f���w�肷�邱�Ƃ�Amaryllis��Őݒ肵���p�����[�^�[���̂܂܂̖��邳�ɂȂ�A<BR>
			����ȏ�Ŗ��邭�A����ȉ��ňÂ����邱�Ƃ��o���܂��B
		*/
		virtual void SetParameter_SceneBrightness( const Math::Vector3D &vBrightness ) = 0;

		/**
			@brief ���`�t�H�O���ݒ�
			@author �t���`
			@param vColor	[in] �t�H�O�̐F
			@param fNear	[in] �t�H�O�J�n�_
			@param fFar		[in] �t�H�O�I���_

			�V�[���ɓK�p�������`�t�H�O�̃p�����[�^�[��ݒ肵�܂��B<BR>
			���̊֐���Begin()-End()���ŌĂяo���Ǝ��s���܂��B
		*/
		virtual void SetParameter_Fog( Math::Vector3D &vColor, Float fNear, Float fFar ) = 0;

		/**
			@brief ��ʊE�[�x�p�̃t�H�[�J�X�ʒu��ݒ肵�܂��B
			@author �t���`

			@param fForcusZ	[in] �t�H�[�J�X�̂y�i�J������j
			@param fPower	[in] ��ʊE�[�x���x

			��ʊE�[�x�̃t�H�[�J�X�ʒu��ݒ肵�܂��B
		*/
		virtual void SetParameter_DepthOfField( Float fForcusZ, Float fPower ) = 0;

		/**
			@brief �\�t�g�p�[�e�B�N���p�X�P�[���l
			@author �t���`

			@param fSoftParticleScale	[in] �\�t�g�p�[�e�B�N���̃A���t�@�l�p�̃X�P�[��

			�\�t�g�p�[�e�B�N�����̐[�x�l�̍��ق���A���t�@���Z�o����Ƃ��̃X�P�[���l�ł��B<BR>
			���̒l���傫���قǃA���t�@�̋��E���V���[�v�ɂȂ�܂��B
		*/
		virtual void SetParameter_SoftParticleScale( Float fSoftParticleScale ) = 0;

		/**
			@brief HDR�G�t�F�N�g�ݒ�
			@author �t���`
			@param HdrEffect	[in] HDR�G�t�F�N�g�̎��
			@param fHDRPower	[in] HDR�̔{��
			@param fHDRBoundary	[in] HDR�Ƃ��Ĉ���臒l�i1.0�����j

			�V�[���̕`�掞��HDR�G�t�F�N�g�̐ݒ�����܂��B
		*/
		virtual void SetParameter_HighDynamicRange( Float fHDRPower, Float fHDRBoundary ) = 0;

		/**
			@brief �g�D�[���p�p�����[�^�[�ݒ�
			@author �t���`
			@param vHatchingColor	[in] �n�b�`���O�p�̎ΐ��̐F
			@param fToonPower		[in] �g�D�[���}�b�v�p�̉e�����̈Â��i0.0�`1.0)

			�g�D�[�������_�����O�p�̃p�����[�^�[��ݒ肵�܂��B
		*/
		virtual void SetParameter_Toon( Math::Vector3D &vHatchingColor, Float fToonPower ) = 0;

		/**
			@brief �g�D�[���p�G�b�W���o�p�����[�^�[�ݒ�
			@author �t���`
			@param fEdgeNormalPower	[in] �@���G�b�W�̌��o�p�����[�^�[
			@param fEdgeDepthPower	[in] �[�x�G�b�W�̌��o�p�����[�^�[
			@param IsToonBold		[in] �֊s���𑾂����邩�ۂ�

			�g�D�[���p�̃G�b�W���o�p�̃p�����[�^�[��ݒ肵�܂��B<BR>
			������̃p�����[�^�[���傫���قǋ��E�����������͈͂������܂��B
		*/
		virtual void SetParameter_ToonEdge( Float fEdgeNormalPower, Float fEdgeDepthPower, Bool IsToonBold ) = 0;

		/**
			@brief �V���h�E�p�J�����ݒ�
			@author �t���`
			@param vPosition	[in] �J�����ʒu
			@param vTarget		[in] �J���������_
			@param fSize		[in] �����_�����O�T�C�Y
			@param fNear		[in] �߃N���b�v��
			@param fFar			[in] ���N���b�v��
			@param fBias		[in] �V���h�E�}�b�v�p�[�x�o�C�A�X
			@param fPower		[in] �e�̕����̖��邳(0.0����1.0�܂ŁA1.0�̎��e�͊��S�ȃA���r�G���g�ɂȂ�j

			�V���h�E�p�̃J�����f�[�^��ݒ肵�܂��B
		*/
		virtual void SetParameter_Shadow( Math::Vector3D &vPosition, Math::Vector3D &vTarget, Float fSize, Float fNear, Float fFar, Float fBias, Float fPower ) = 0;

		/**
			@brief �����_�����O�^�[�Q�b�g�̋�`��ݒ�
			@author �t���`
			@param Dst		[in] �����_�����O��`

			�V�[���̃����_�����O�^�[�Q�b�g�̋�`���w�肵�܂��B<BR>
			�ŏI�I�ɕ\�������ʒu�Ɋ֌W���܂��B
		*/
		virtual void SetParameter_RenderRect( Math::Rect2DF &Dst ) = 0;

		/**
			@brief �w�i�h��Ԃ��F�ݒ�
			@author �t���`
			@param ClearColor	[in] �o�b�t�@�N���A�F
			@param IsClear		[in] �N���A�L��

			�V�[���̕`�掞�̔w�i�̓h��Ԃ��F��ݒ肵�܂��B
		*/
		virtual void SetParameter_BGColor( Math::Vector4D &ClearColor, Bool IsClear = true ) = 0;

		/**
			@brief �w�i�h��Ԃ��F�ݒ�
			@author �t���`
			@param ClearColor	[in] �o�b�t�@�N���A�F
			@param IsClear		[in] �N���A�L��

			�V�[���̕`�掞�̔w�i�̓h��Ԃ��F��ݒ肵�܂��B
		*/
		virtual void SetParameter_BGColor( CColor ClearColor, Bool IsClear = true ) = 0;

		/**
			@brief �w�i�h��Ԃ��e�N�X�`���ݒ�
			@author �t���`
			@param pTex		[in] �e�N�X�`��

			�V�[���̕`�掞�̔w�i�̃e�N�X�`����ݒ肵�܂��B
		*/
		virtual void SetParameter_BGTexture( Renderer::ITexture *pTex ) = 0;

		/**
			@brief �V�[�������X�V
			@author �t���`

			�V�[��������܂ł̏������ɍX�V���܂��B<BR>
			�K�v�Ȑݒ��ɂ��̊֐����Ăяo���Ȃ�����IActor�𐶐����邱�Ƃ��o���܂���B
		*/
		virtual Bool InitParameter_Update( void ) = 0;

		/**
			@brief �����_�����O�^�[�Q�b�g�̃T�C�Y��ݒ�
			@author �t���`
			@param pTarget				[in] �����_�����O�^�[�Q�b�g�̃e�N�X�`���iNULL�Ńo�b�N�o�b�t�@�֒��ڃ����_�����O�j
			@param Size					[in] �T�C�Y�ipTarget���L���ȏꍇ��pTarget�̃T�C�Y�Ɏ����ݒ肳��܂��j
			@param IsTextureSizePow2	[in] �T�C�Y�������I�ɂQ�̗ݏ�ɂ��邩�ǂ���

			�V�[���̃����_�����O�^�[�Q�b�g�̃T�C�Y���w�肵�܂��B<BR>
			�����_�����O�g����e��o�b�t�@�̃T�C�Y�Ɋ֌W���܂��B<BR>
			<B>�K��InitParameterUpdate�̑O�Ɏ��s���Ă��������B</B>
		*/
		virtual void InitParameter_RenderTargetData( Renderer::ITexture *pTarget, Math::Point2DI Size = Math::Point2DI(0,0), Bool IsTextureSizePow2 = false ) = 0;

		/**
			@brief �V�F�[�f�B���O�p�p�����[�^�[�̏�����
			@author �t���`
			@param ShadingType		[in] �V�F�[�f�B���O�̎��

			�V�[���ōs���V�F�[�f�B���O�̏��������������܂��B<BR>
			<B>�K��InitParameterUpdate�̑O�Ɏ��s���Ă��������B</B>
		*/
		virtual void InitParameter_Shading( eSceneShadingType ShadingType ) = 0;

		/**
			@brief �A���`�G�C���A�X�p�p�����[�^�[�̏�����
			@author �t���`
			@param AntiAliasType	[in] �A���`�G�C���A�X�̎��
			@param fPower			[in] �A���`�G�C���A�X�̂�����(0.0�`1.0)

			�V�[���ōs���A���`�G�C���A�X�̏��������������܂��B<BR>
			<B>�K��InitParameterUpdate�̑O�Ɏ��s���Ă��������B</B>
		*/
		virtual void InitParameter_AntiAliasType( eSceneAntiAliasType AntiAliasType, Float fPower ) = 0;

		/**
			@brief �e�p�p�����[�^�[�̏�����
			@author �t���`
			@param ShadowType			[in] �e�̎��
			@param ShadowQuarity		[in] �e�̕i��
			@param IsSoftShadow			[in] �\�t�g�V���h�E���g�����ǂ���
			@param IsHardwareShadowmap	[in] �n�[�h�E�F�A�V���h�E�}�b�v���g�����ǂ���

			�V�[���ōs���e�̏��������������܂��B<BR>
			<B>�K��InitParameterUpdate�̑O�Ɏ��s���Ă��������B</B>
		*/
		virtual void InitParameter_Shadow( eSceneShadowType ShadowType, eSceneShadowQuarity ShadowQuarity, Bool IsSoftShadow = false, Bool IsHardwareShadowmap = true ) = 0;

		/**
			@brief ���[�V�����u���[�p�p�����[�^�[�̏�����
			@author �t���`
			@param MotionBlurType	[in] ���[�V�����u���[�̎��

			�V�[���ōs�����[�V�����u���[�̏��������������܂��B<BR>
			<B>�K��InitParameterUpdate�̑O�Ɏ��s���Ă��������B</B>
		*/
		virtual void InitParameter_MotionBlur( eSceneMotionBlurType MotionBlurType ) = 0;

		/**
			@brief ��ʊE�[�x�p�p�����[�^�[�̏�����
			@author �t���`
			@param DofType	[in] ��ʊE�[�x�̎��

			�V�[���ōs����ʊE�[�x�̏��������������܂��B<BR>
			<B>�K��InitParameterUpdate�̑O�Ɏ��s���Ă��������B</B>
		*/
		virtual void InitParameter_DepthOfField( eSceneDepthOfFieldType DofType ) = 0;

		/**
			@brief �t�H�O�p�p�����[�^�[�̏�����
			@author �t���`
			@param FogType		[in] �t�H�O�̎��
			@param FogEffect	[in] �t�H�O�̃G�t�F�N�g

			�V�[���ōs���t�H�O�̏��������������܂��B<BR>
			<B>�K��InitParameterUpdate�̑O�Ɏ��s���Ă��������B</B>
		*/
		virtual void InitParameter_Fog( eSceneFogType FogType, eSceneFogEffect FogEffect ) = 0;

		/**
			@brief HDR�����_�����O�p�p�����[�^�[�̏�����
			@author �t���`
			@param HdrType		[in] HDR�����_�����O�̎��
			@param HdrEffect	[in] HDR�����_�����O�̃G�t�F�N�g

			�V�[���ōs��HDR�����_�����O�̏��������������܂��B<BR>
			<B>�K��InitParameterUpdate�̑O�Ɏ��s���Ă��������B</B>
		*/
		virtual void InitParameter_HighDynamicRange( eSceneHighDynamicRangeType HdrType, eSceneHighDynamicRangeEffect HdrEffect ) = 0;

		/**
			@brief �X�J�C�h�[���̐���
			@author �t���`
			@param fRadius		[in] ���a
			@param TopColor		[in] �V���̓������̐F
			@param BottomColor	[in] �V���̒n�ʕ����̐F
			@param pTexCloud	[in] �_�e�N�X�`��

			�V�[���ɓK�p����X�J�C�h�[���𐶐����܂��B<BR>
		*/
		virtual Bool SceneSkydoom_Create( Float fRadius, CColor TopColor, CColor BottomColor, Renderer::ITexture *pTexCloud ) = 0;

		/**
			@brief �X�J�C�h�[���̃����_�����O
			@author �t���`

			�V�[���ɓo�^����Ă���X�J�C�h�[���̃����_�����O�����܂��B
		*/
		virtual void SceneSkydoom_Rendering( void ) = 0;

		/**
			@brief �X�J�C�h�[���̉_�e�N�X�`���̐F��ݒ�
			@author �t���`
			@param Color		[in] �F

			�V�[���ɓK�p����X�J�C�h�[���̉_�̐F��ݒ肵�܂��B
		*/
		virtual void SceneSkydoom_SetCloudColor( const CColor &Color ) = 0;

		/**
			@brief �X�J�C�h�[���̉_�e�N�X�`���̈ړ��ʃI�t�Z�b�g
			@author �t���`
			@param vOffset		[in] �ړ���(1.0�Ńe�N�X�`���T�C�Y)

			�V�[���ɓK�p����X�J�C�h�[���̉_�̗���𐧌䂵�܂��B<BR>
			���̊֐��ŗ^�����I�t�Z�b�g���_���ړ����܂��B
		*/
		virtual void SceneSkydoom_SetCloudOffset( const Math::Vector2D &vOffset ) = 0;

		/**
			@brief �X�N���[�����W�ɕϊ�
			@author �t���`
			@param vPosition	[in] ���[���h���W
			@return �X�N���[�����W

			���[���h��Ԃ̍��W���X�N���[�����W�ɕϊ����܂��B
		*/
		virtual Math::Vector3D TransformToScreen( const Math::Vector3D &vPosition ) = 0;

		/**
			@brief �X�N���[�����W����ϊ�
			@author �t���`
			@param vPosition	[in] �X�N���[�����W
			@return ���[���h���W

			�X�N���[�����W�����[���h��Ԃ̍��W�ɕϊ����܂��B
		*/
		virtual Math::Vector3D TransformFromScreen( const Math::Vector3D &vPosition ) = 0;
	};
}
}

#pragma once


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Scene
{
	/**
		@brief �J�X�^���V�[���Ǘ��p�C���^�[�t�F�C�X
		@author �t���`

		@note
		�J�X�^���V�[���Ǘ����s�����߂̃C���^�[�t�F�C�X�ł��B
	*/
	class ICustomizedSceneManager : public IInterface
	{
	protected:
		virtual ~ICustomizedSceneManager() {}

	public:
		/**
			@brief �I���ҋ@
			@author �t���`

			ISceneManager�Ń����_�����O�����̊��������S�ɑҋ@���܂��B<BR>
			Begin()-End()�ȍ~����Ńf�[�^�̍\�z�������s���܂��̂ŁA<BR>
			�V�[���A���邢�̓V�[���ŗ��p���Ă��郊�\�[�X���������O��<BR>
			���̊֐��ŃV�[���̍\�z�����̏I����҂��ĉ������B<BR>
			�Ȃ��A�v���P�[�V�����̏I����(ICore::Run()=false)���ɂ͓����őS�ẴV�[����<BR>
			Abort()�������I�ɌĂ΂�܂��B
		*/
		virtual void Abort( void ) = 0;

		/**
			@brief �V�[���A�N�^�[�擾
			@author �t���`
			@param pObject			[in] �A�N�^�[�Ɋ֘A�t����`��C���^�[�t�F�C�X
			@param InstanceCount	[in] �C���X�^���X��
			@return	IInstanceModelActor�C���^�[�t�F�C�X

			ISceneManager�Ń����_�����O���s�����߂̃A�N�^�[���擾���܂��B<BR>
			�W�I���g���C���X�^���V���O���s�����߂̓���ȃA�N�^�[�ŁA<BR>
			���̃A�N�^�[���炳��Ɍʂ̃R���g���[���[���擾���A���[���h�ϊ���{�[���̐ݒ���s���܂��B
		*/
		virtual IInstanceModelActor *CreateActor( Renderer::Object::IModel *pObject, Sint32 InstanceCount ) = 0;

		/**
			@brief �V�[���A�N�^�[�擾
			@author �t���`
			@param pObject	[in] �A�N�^�[�Ɋ֘A�t����`��C���^�[�t�F�C�X
			@return	IModelActor�C���^�[�t�F�C�X

			ISceneManager�Ń����_�����O���s�����߂̃A�N�^�[���擾���܂��B<BR>
			���[���h�ϊ��⃌���_�����O�̑����IModelActor���o�R���čs���܂��B
		*/
		virtual IModelActor *CreateActor( Renderer::Object::IModel *pObject ) = 0;

		/**
			@brief �V�[���A�N�^�[�擾
			@author �t���`
			@param pObject	[in] �A�N�^�[�Ɋ֘A�t����`��C���^�[�t�F�C�X
			@return	IMapActor�C���^�[�t�F�C�X

			ISceneManager�Ń����_�����O���s�����߂̃A�N�^�[���擾���܂��B<BR>
			���[���h�ϊ��⃌���_�����O�̑����IMapActor���o�R���čs���܂��B
		*/

		virtual IMapActor *CreateActor( Renderer::Object::IMapModel *pObject ) = 0;

		/**
			@brief �V�[���A�N�^�[�擾
			@author �t���`
			@param pObject	[in] �A�N�^�[�Ɋ֘A�t����`��C���^�[�t�F�C�X
			@return	IPrimitiveActor�C���^�[�t�F�C�X

			ISceneManager�Ń����_�����O���s�����߂̃A�N�^�[���擾���܂��B<BR>
			���[���h�ϊ��⃌���_�����O�̑����IPrimitiveActor���o�R���čs���܂��B
		*/
		virtual IPrimitiveActor *CreateActor( Renderer::Object::IPoint3D *pObject ) = 0;

		/**
			@brief �V�[���A�N�^�[�擾
			@author �t���`
			@param pObject	[in] �A�N�^�[�Ɋ֘A�t����`��C���^�[�t�F�C�X
			@return	IPrimitiveActor�C���^�[�t�F�C�X

			ISceneManager�Ń����_�����O���s�����߂̃A�N�^�[���擾���܂��B<BR>
			���[���h�ϊ��⃌���_�����O�̑����IPrimitiveActor���o�R���čs���܂��B
		*/
		virtual IPrimitiveActor *CreateActor( Renderer::Object::ILine3D *pObject ) = 0;

		/**
			@brief �V�[���A�N�^�[�擾
			@author �t���`
			@param pObject	[in] �A�N�^�[�Ɋ֘A�t����`��C���^�[�t�F�C�X
			@param IsLightmap		[in] 
			@pamra IsNormalmap		[in] 
			@param IsSpecularmap	[in] 
			@param IsEnvironmentmap	[in] 
			@return	IPrimitiveActor�C���^�[�t�F�C�X

			ISceneManager�Ń����_�����O���s�����߂̃A�N�^�[���擾���܂��B<BR>
			���[���h�ϊ��⃌���_�����O�̑����IPrimitiveActor���o�R���čs���܂��B
		*/
		virtual IPrimitiveActor *CreateActor( Renderer::Object::IPrimitive3D *pObject, Bool IsLightmap = false, Bool IsNormalmap = false, Bool IsSpecularmap = false, Bool IsEnvironmentmap = false ) = 0;

		/**
			@brief �V�[���A�N�^�[�擾
			@author �t���`
			@param pObject	[in] �A�N�^�[�Ɋ֘A�t����`��C���^�[�t�F�C�X
			@return	ISpriteActor�C���^�[�t�F�C�X

			ISceneManager�Ń����_�����O���s�����߂̃A�N�^�[���擾���܂��B<BR>
			���[���h�ϊ��⃌���_�����O�̑����ISpriteActor���o�R���čs���܂��B
		*/
		virtual ISpriteActor *CreateActor( Renderer::Object::ISprite3D *pObject ) = 0;

		/**
			@brief �V�[���A�N�^�[�擾
			@author �t���`
			@param pObject	[in] �A�N�^�[�Ɋ֘A�t����`��C���^�[�t�F�C�X
			@return	IParticleActor�C���^�[�t�F�C�X

			ISceneManager�Ń����_�����O���s�����߂̃A�N�^�[���擾���܂��B<BR>
			���[���h�ϊ��⃌���_�����O�̑����IParticleActor���o�R���čs���܂��B
		*/
		virtual IParticleActor *CreateActor( Renderer::Object::IFontSprite3D *pObject ) = 0;

		/**
			@brief �V�[���A�N�^�[�擾
			@author �t���`
			@param pObject	[in] �A�N�^�[�Ɋ֘A�t����`��C���^�[�t�F�C�X
			@return	IParticleActor�C���^�[�t�F�C�X

			ISceneManager�Ń����_�����O���s�����߂̃A�N�^�[���擾���܂��B<BR>
			���[���h�ϊ��⃌���_�����O�̑����IParticleActor���o�R���čs���܂��B
		*/
		virtual IParticleActor *CreateActor( Renderer::Object::IParticle *pObject ) = 0;

		/**
			@brief �V�[���J�����擾
			@author �t���`
			@return �J����

			�V�[���Ɋ֘A�t����ꂽ�J�������擾���܂��B
		*/
		virtual ICamera *GetCamera( void ) = 0;

		/**
			@brief �V�[��������
			@author �t���`

			�V�[���̃��C�g��t�H�O�Ȃǂ̃f�[�^�����Z�b�g���܂��B<BR>
			���̊֐���Begin()-End()���ŌĂяo���Ǝ��s���܂��B
		*/
		virtual void Reset( void ) = 0;

		/**
			@brief �V�[���J�n
			@author �t���`
			@param IsSort	[in] �V�[�����̃I�u�W�F�N�g���\�[�g���邩�ǂ���

			�V�[���Ǘ����J�n���܂��B<BR>
			���̎��_�ŃJ�����̃f�[�^���m�肵�܂��̂�<BR>
			���̊֐����Ăяo�������Ƃ̃J�����̍X�V�͑S�Ė����ł��B
		*/
		virtual void Begin( Bool IsSort ) = 0;

		/**
			@brief �V�[���I��
			@author �t���`

			�V�[���̊Ǘ����������܂��B
		*/
		virtual void End( void ) = 0;

		/**
			@brief �V�[�������_�����O�J�n
			@author �t���`
			@retval false	�V�[���Ƀ����_�����O����I�u�W�F�N�g���Ȃ�
			@retval	true	�V�[���Ƀ����_�����O����I�u�W�F�N�g������

			@note
			�V�[���̃����_�����O���J�n���鎖��錾���܂��B<BR>
			���̊֐���true��Ԃ����ꍇ�͕K��RedneringEnd()���R�[�����ĉ������B
		*/
		virtual Bool RenderingStart( void ) = 0;

		/**
			@brief �V�[�������_�����O�I��
			@author �t���`

			@note
			�V�[���̃����_�����O���I�����鎖��錾���܂��B
		*/
		virtual void RenderingExit( void ) = 0;

		/**
			@brief �X�N���[�����W�ɕϊ�
			@author �t���`
			@param vPosition	[in] ���[���h���W
			@return �X�N���[�����W

			���[���h��Ԃ̍��W���X�N���[�����W�ɕϊ����܂��B
		*/
		virtual Math::Vector3D TransformToScreen( const Math::Vector3D &vPosition ) = 0;

		/**
			@brief �X�N���[�����W����ϊ�
			@author �t���`
			@param vPosition	[in] �X�N���[�����W
			@return ���[���h���W

			�X�N���[�����W�����[���h��Ԃ̍��W�ɕϊ����܂��B
		*/
		virtual Math::Vector3D TransformFromScreen( const Math::Vector3D &vPosition ) = 0;

		/**
			@brief �A�N�^�[�I�u�W�F�N�g�̃��C���[���擾
			@author �t���`
			@return �A�N�^�[�I�u�W�F�N�g�̃��C���[��

			@note
			�����_�����O����A�N�^�[�I�u�W�F�N�g�̃��C���[�����擾���܂��B<BR>
			���C���[�����̂�3�ŌŒ肳��Ă���A�����I�ɉ��̂悤�ɌŒ肳��Ă��܂�<BR>
			0=���g�p<BR>
			1=�s�������f��<BR>
			2=���������f��
		*/
		virtual Sint32 GetRenderObjectLayerCount( void ) = 0;

		/**
			@brief �A�N�^�[�I�u�W�F�N�g�̎擾
			@author �t���`
			@param Layer	[in] �I�u�W�F�N�g���C���[
			@return �A�N�^�[�I�u�W�F�N�g

			@note
			�����_�����O����A�N�^�[�I�u�W�F�N�g���擾���܂��B
		*/
		virtual ICustomizedSceneRenderObject *GetRenderObject( Sint32 Layer ) = 0;
	};
}
}

#pragma once


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Scene
{
	/**
		@brief �J�X�^���V�[���`��I�u�W�F�N�g�C���^�[�t�F�C�X
		@author �t���`

		@note
		�J�X�^���V�[���̕`��I�u�W�F�N�g���������߂̃C���^�[�t�F�C�X�ł��B
	*/
	class ICustomizedSceneRenderObject : public IInterface
	{
	protected:
		virtual ~ICustomizedSceneRenderObject() {}

	public:
		/**
			@brief �{�[���p���_�̗L�����擾
			@author �t���`
			@retval false	����
			@retval true	�L��

			@note
			�`��I�u�W�F�N�g���{�[���p���_�������Ă��邩���擾���܂��B
		*/
		virtual Bool IsSupportVertexBone( void ) = 0;

		/**
			@brief �e�N�X�`���p���_�̗L�����擾
			@author �t���`
			@retval false	����
			@retval true	�L��

			@note
			�`��I�u�W�F�N�g���e�N�X�`���p���_�������Ă��邩���擾���܂��B
		*/
		virtual Bool IsSupportVertexTexture( void ) = 0;

		/**
			@brief �@���p���_�̗L�����擾
			@author �t���`
			@retval false	����
			@retval true	�L��

			@note
			�`��I�u�W�F�N�g���@���p���_�������Ă��邩���擾���܂��B
		*/
		virtual Bool IsSupportVertexNormal( void ) = 0;

		/**
			@brief �o���v�p�ڐ��p���_�̗L�����擾
			@author �t���`
			@retval false	����
			@retval true	�L��

			@note
			�`��I�u�W�F�N�g���o���v�p�ڐ��p���_�������Ă��邩���擾���܂��B
		*/
		virtual Bool IsSupportVertexBump( void ) = 0;

		/**
			@brief �}�e���A�����擾
			@author �t���`
			@return �}�e���A����

			@note
			�`��I�u�W�F�N�g�����L����}�e���A�������擾���܂��B
		*/
		virtual Sint32 GetMaterialCount( void ) = 0;

		/**
			@brief �`��}�e���A���擾
			@author �t���`
			@param Index	[in] �}�e���A���ԍ�

			@note
			�`��I�u�W�F�N�g�����L����}�e���A���f�[�^���擾���܂��B
		*/
		virtual ICustomizedSceneRenderMaterial *GetMaterialPointer( Sint32 Index ) = 0;

		/**
			@brief �{�[�������擾
			@author �t���`
			@return �{�[����

			@note
			�`��I�u�W�F�N�g���������Ă���{�[�������擾���܂��B
		*/
		virtual Sint32 GetBoneCount( void ) = 0;

		/**
			@brief ���[���h�s��擾
			@author �t���`
			@return ���[���h�s��

			@note
			�`��I�u�W�F�N�g�̍s��f�[�^���擾���܂��B
		*/
		virtual const Math::Matrix &GetWorldMatrix( void ) = 0;


		/**
			@brief �O�t���[���̃��[���h�s��擾
			@author �t���`
			@return ���[���h�s��

			@note
			�`��I�u�W�F�N�g�̍s��f�[�^���擾���܂��B
		*/
		virtual const Math::Matrix &GetWorldMatrixPrev( void ) = 0;

		/**
			@brief ���[���h���r���[�s��擾
			@author �t���`
			@return ���[���h���r���[�s��

			@note
			�`��I�u�W�F�N�g�̍s��f�[�^���擾���܂��B
		*/
		virtual const Math::Matrix &GetWorldViewMatrix( void ) = 0;

		/**
			@brief �O�t���[���̃��[���h���r���[�s��擾
			@author �t���`
			@return ���[���h���r���[�s��

			@note
			�`��I�u�W�F�N�g�̍s��f�[�^���擾���܂��B
		*/
		virtual const Math::Matrix &GetWorldViewPrevMatrix( void ) = 0;

		/**
			@brief ���[���h���r���[���v���W�F�N�V�����s��擾
			@author �t���`
			@return ���[���h���r���[���v���W�F�N�V�����s��

			@note
			�`��I�u�W�F�N�g�̍s��f�[�^���擾���܂��B
		*/
		virtual const Math::Matrix &GetWorldViewProjectionMatrix( void ) = 0;

		/**
			@brief �O�t���[���̃��[���h���r���[���v���W�F�N�V�����s��擾
			@author �t���`
			@return ���[���h���r���[���v���W�F�N�V�����s��

			@note
			�`��I�u�W�F�N�g�̍s��f�[�^���擾���܂��B
		*/
		virtual const Math::Matrix &GetWorldViewProjectionPrevMatrix( void ) = 0;

		/**
			@brief ���[���h�t�s��擾
			@author �t���`
			@return ���[���h�t�s��

			@note
			�`��I�u�W�F�N�g�̍s��f�[�^���擾���܂��B
		*/
		virtual const Math::Matrix &GetWorldInverseMatrix( void ) = 0;

		/**
			@brief �O�t���[���̃��[���h�t�s��擾
			@author �t���`
			@return ���[���h�t�s��

			@note
			�`��I�u�W�F�N�g�̍s��f�[�^���擾���܂��B
		*/
		virtual const Math::Matrix &GetWorldInverseMatrixPrev( void ) = 0;

		/**
			@brief �{�[���p�ϊ��s��擾
			@author �t���`
			@return �{�[���ϊ��s��

			@note
			�`��I�u�W�F�N�g�̃{�[���p�̍s��f�[�^���擾���܂��B
		*/
		virtual const Math::SMatrix4x4 *GetBoneMatrixArray( void ) = 0;

		/**
			@brief �O�t���[���̃{�[���p�ϊ��s��擾
			@author �t���`
			@return �{�[���ϊ��s��

			@note
			�`��I�u�W�F�N�g�̃{�[���p�̍s��f�[�^���擾���܂��B
		*/
		virtual const Math::SMatrix4x4 *GetBoneMatrixArrayPrev( void ) = 0;

		/**
			@brief �����_�����O�p���_�f�[�^�ݒ�
			@author �t���`
			@param pRender		[in] �֘A����IRender�C���^�[�t�F�C�X

			@note
			�����_�����O���s�����߂̒��_�X�g���[���̐ݒ���s���܂��B
		*/
		virtual void SetStreamSource( Renderer::IRender *pRender ) = 0;

		/**
			@brief �ʏ탌���_�����O
			@author �t���`
			@param MaterialNo	[in] �`�悷��}�e���A���ԍ�
			@param pRender		[in] �֘A����IRender�C���^�[�t�F�C�X

			@note
			�ʏ�̃����_�����O�������s���܂��B
		*/
		virtual Sint32 Rendering( Sint32 MaterialNo, Renderer::IRender *pRender ) = 0;

		/**
			@brief ���x�}�b�v�p�k�ރ|���S�����背���_�����O
			@author �t���`
			@param pRender	[in] �֘A����IRender�C���^�[�t�F�C�X

			@note
			���x�}�b�v�`��p�̏k�ރ|���S������̃����_�����O���s���܂��B
		*/
		virtual Sint32 Rendering_Velocity( Renderer::IRender *pRender ) = 0;

		/**
			@brief ���_�ϊ��^�C�v���擾
			@author �t���`
			@retval false	����
			@retval true	�L��

			@note
			�`��I�u�W�F�N�g�̒��_�ϊ��^�C�v���擾���܂��B
		*/
		virtual eTransformType GetTransformType( void ) = 0;

		/**
			@brief �\�t�g�p�[�e�B�N���̗L�����擾
			@author �t���`
			@retval false	�\�t�g�p�[�e�B�N���ł͂Ȃ�
			@retval true	�\�t�g�p�[�e�B�N��

			@note
			�`��I�u�W�F�N�g���\�t�g�p�[�e�B�N�����ǂ������擾���܂��B
		*/
		virtual Bool GetSoftBillboardEnable( void ) = 0;

		/**
			@brief �����o���v�}�b�v�̗L�����擾
			@author �t���`
			@retval false	����
			@retval true	�L��

			@note
			�`��I�u�W�F�N�g�������o���v�}�b�v�������Ă��邩���擾���܂��B
		*/
		virtual Bool GetParallaxEnable( void ) = 0;

		/**
			@brief �X�y�L�����[�ݒ�̗̂L�����擾
			@author �t���`
			@retval false	����
			@retval true	�L��

			@note
			�`��I�u�W�F�N�g���X�y�L�����[�ݒ�̂������Ă��邩���擾���܂��B
		*/
		virtual Bool GetSpecularEnable( void ) = 0;

		/**
			@brief ���}�b�v�ݒ�̗̂L�����擾
			@author �t���`
			@retval false	����
			@retval true	�L��

			@note
			�`��I�u�W�F�N�g�����}�b�v�ݒ�̂������Ă��邩���擾���܂��B
		*/
		virtual Bool GetEnvironmentEnable( void ) = 0;

		/**
			@brief ���X�g�ɂȂ���Ă��鎟�̕`��I�u�W�F�N�g���擾
			@author �t���`
			@return �`��I�u�W�F�N�g�C���^�[�t�F�C�X

			@note
			���X�g�ɂȂ���Ă���`��I�u�W�F�N�g�̎����̎��̕`��I�u�W�F�N�g���擾���܂��B
		*/
		virtual ICustomizedSceneRenderObject *GetNextObject( void ) = 0;
	};
}
}

#pragma once


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Scene
{
	/**
		@brief �J�X�^���V�[���}�e���A���C���^�[�t�F�C�X
		@author �t���`

		@note
		�J�X�^���V�[���̃A�N�^�[�̃}�e���A�����������߂̃C���^�[�t�F�C�X�ł��B
	*/
	class ICustomizedSceneRenderMaterial
	{
	protected:
		virtual ~ICustomizedSceneRenderMaterial() {}

	public:
		/**
			@brief �V�F�[�_�[�C���^�[�t�F�C�X�擾
			@author �t���`
			@return �V�F�[�_�[�C���^�[�t�F�C�X

			@note
			�}�e���A���Ɋ֘A�t�����Ă���V�F�[�_�[���擾���܂��B
		*/
		virtual Renderer::Shader::IShader *GetShader( void ) = 0;

		/**
			@brief �e�N�X�`���C���^�[�t�F�C�X�擾
			@author �t���`
			@return �e�N�X�`���C���^�[�t�F�C�X

			@note
			�}�e���A���Ɋ֘A�t�����Ă���e�N�X�`�����擾���܂��B
		*/
		virtual Renderer::ITexture *GetTexture( Sint32 Stage ) = 0;

		/**
			@brief �g�U���ːF�擾
			@author �t���`
			@return �g�U���ːF

			@note
			�}�e���A���Ɋ֘A�t�����Ă���g�U���ːF���擾���܂��B
		*/
		virtual Math::Vector4D &GetDiffuseColor( void ) = 0;

		/**
			@brief ���Ȕ����F�擾
			@author �t���`
			@return ���Ȕ����F

			@note
			�}�e���A���Ɋ֘A�t�����Ă��鎩�Ȕ����F���擾���܂��B
		*/
		virtual Math::Vector4D &GetEmissiveColor( void ) = 0;

		/**
			@brief ���ʔ��ːF�擾
			@author �t���`
			@return ���ʔ��ːF

			@note
			�}�e���A���Ɋ֘A�t�����Ă��鋾�ʔ��ːF���擾���܂��B
		*/
		virtual Math::Vector4D &GetSpecularColor( void ) = 0;

		/**
			@brief �e�N�X�`��UV�I�t�Z�b�g�擾
			@author �t���`
			@return �e�N�X�`��UV�I�t�Z�b�g

			@note
			�}�e���A���Ɋ֘A�t�����Ă���e�N�X�`��UV�I�t�Z�b�g���擾���܂��B
		*/
		virtual Math::Vector2D &GetTextureOffset( void ) = 0;

		/**
			@brief ���ʔ��˔��˗��擾
			@author �t���`
			@return ���ʔ��˔��˗�

			@note
			�}�e���A���Ɋ֘A�t�����Ă��鋾�ʔ��˔��˗����擾���܂��B
		*/
		virtual Float GetSpecularRefractive( void ) = 0;

		/**
			@brief ���ʔ��ˍr���擾
			@author �t���`
			@return ���ʔ��ˍr��

			@note
			�}�e���A���Ɋ֘A�t�����Ă��鋾�ʔ��ˍr�����擾���܂��B
		*/
		virtual Float GetSpecularRoughly( void ) = 0;

		/**
			@brief �����}�b�v�[�x�擾
			@author �t���`
			@return �����}�b�v�[�x

			@note
			�}�e���A���Ɋ֘A�t�����Ă��鎋���}�b�v�[�x���擾���܂��B
		*/
		virtual Float GetParallaxDepth( void ) = 0;

		/**
			@brief ���ʔ��˃^�C�v�擾
			@author �t���`
			@return ���ʔ��˃^�C�v

			@note
			�}�e���A���Ɋ֘A�t�����Ă��鋾�ʔ��˃^�C�v���擾���܂��B
		*/
		virtual eSpecularType GetSpecularType( void ) = 0;

		/**
			@brief ���ʔ��˔��˗��擾
			@author �t���`
			@return ���ʔ��˔��˗�

			@note
			�}�e���A���Ɋ֘A�t�����Ă��鋾�ʔ��˔��˗����擾���܂��B
		*/
		virtual eBumpType GetBumpType( void ) = 0;

		/**
			@brief ���ʔ��˔��˗��擾
			@author �t���`
			@return ���ʔ��˔��˗�

			@note
			�}�e���A���Ɋ֘A�t�����Ă��鋾�ʔ��˔��˗����擾���܂��B
		*/
		virtual eDrawType GetDrawType( void ) = 0;

		/**
			@brief ���ʔ��˔��˗��擾
			@author �t���`
			@return ���ʔ��˔��˗�

			@note
			�}�e���A���Ɋ֘A�t�����Ă��鋾�ʔ��˔��˗����擾���܂��B
		*/
		virtual eCullType GetCullType( void ) = 0;

		/**
			@brief ���ʔ��˔��˗��擾
			@author �t���`
			@return ���ʔ��˔��˗�

			@note
			�}�e���A���Ɋ֘A�t�����Ă��鋾�ʔ��˔��˗����擾���܂��B
		*/
		virtual Sint32 GetAlphaBoundary( void ) = 0;

		/**
			@brief ���ʔ��˔��˗��擾
			@author �t���`
			@return ���ʔ��˔��˗�

			@note
			�}�e���A���Ɋ֘A�t�����Ă��鋾�ʔ��˔��˗����擾���܂��B
		*/
		virtual Bool GetAlphaTestEnable( void ) = 0;

		/**
			@brief ���ʔ��˔��˗��擾
			@author �t���`
			@return ���ʔ��˔��˗�

			@note
			�}�e���A���Ɋ֘A�t�����Ă��鋾�ʔ��˔��˗����擾���܂��B
		*/
		virtual Bool GetZTestEnable( void ) = 0;

		/**
			@brief ���ʔ��˔��˗��擾
			@author �t���`
			@return ���ʔ��˔��˗�

			@note
			�}�e���A���Ɋ֘A�t�����Ă��鋾�ʔ��˔��˗����擾���܂��B
		*/
		virtual Bool GetZWriteEnable( void ) = 0;

		/**
			@brief ���ʔ��˔��˗��擾
			@author �t���`
			@return ���ʔ��˔��˗�

			@note
			�}�e���A���Ɋ֘A�t�����Ă��鋾�ʔ��˔��˗����擾���܂��B
		*/
		virtual Bool GetLightEnable( void ) = 0;
	};
}
}

#pragma once


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Dynamics
{
	struct SSurfaceParameter
	{
		eContactMode	Mode;				///< ���[�h
		Float			Friction;			///< ���C�W��
		Float			FrictionEx;			///< ���C�W��
		Float			Bounce;				///< ���ˌW��
		Float			BounceVelocity;		///< ���ˍŒᑬ�x
		Float			SoftErp;
		Float			SoftCfm;
		Float			Motion;
		Float			MotionEx;
		Float			Slip;
		Float			SlipEx;
	};

	/**
		@brief �ڐG�_�����p�C���^�[�t�F�C�X
		@author �t���`

		�_�C�i�~�N�X�̐ڐG�_���Ǘ����邽�߂̃C���^�[�t�F�C�X�ł��B
	*/
	class IContactPoint : public IInterface
	{
	public:
		virtual ~IContactPoint() {}

		virtual Sint32 GetCount( void ) = 0;
		virtual void SetSurfaceParameter( Sint32 Index, SSurfaceParameter &Param ) = 0;
	};
}
}

#pragma once


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
	enum eBodyType
	{
		BODY_TYPE_GEOMETRY,
		BODY_TYPE_MODEL,
		BODY_TYPE_MAP,
	};

namespace Dynamics
{
	/**
		@brief �_�C�i�~�N�X�p���̃C���^�[�t�F�C�X
		@author �t���`

		�_�C�i�~�N�X���������鍄�̂̃C���^�[�t�F�C�X�ł��B
	*/
	class IRigidBody : public IInterface
	{
	public:
		virtual ~IRigidBody() {}

		virtual void SetUserData( void *pUser ) = 0;
		virtual void *GetUserData( void ) = 0;
		virtual eBodyType GetType( void ) = 0;

		virtual void SetPosition( Math::Vector3D &vPos ) = 0;
		virtual void SetRotation( Math::Matrix &mRot ) = 0;
		virtual void SetLinearSpeed( Math::Vector3D &vDir ) = 0;
		virtual void SetAngularSpeed( Math::Vector3D &vDir ) = 0;

		virtual Math::Matrix &GetMatrix( void ) = 0;
		virtual void GetPosition( Math::Vector3D &vPos ) = 0;

		virtual void SetFixed( void ) = 0;
	};
}
}

#pragma once


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Dynamics
{
	/**
		@brief �_�C�i�~�N�X�p���̃C���^�[�t�F�C�X
		@author �t���`

		�_�C�i�~�N�X���������鍄�̂̃C���^�[�t�F�C�X�ł��B
	*/
	class IRigidModel : public IInterface
	{
	public:
		virtual ~IRigidModel() {}
	};
}
}

#pragma once


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Dynamics
{
	typedef void (*CollisionProc)( ISimulationWorld *pWorld, IRigidBody *pIn1, IRigidBody *pIn2, IContactPoint *pContact );

	/**
		@brief �_�C�i�~�N�X�Ǘ��C���^�[�t�F�C�X
		@author �t���`

		�_�C�i�~�N�X���������郏�[���h���Ǘ�����C���^�[�t�F�C�X�ł��B
	*/
	class ISimulationWorld : public IInterface
	{
	public:
		virtual ~ISimulationWorld() {}

		virtual void SetContactPointCount( Sint32 Count ) = 0;
		virtual void SetStepNumIterations( Sint32 Count ) = 0;

		virtual void CreateEarth( void ) = 0;
		virtual void SetGravity( Math::Vector3D &vDir ) = 0;
		virtual void Update( Float fTime, CollisionProc Proc ) = 0;

		virtual void RenderingRequest( void ) = 0;

		virtual IRigidBody *CreateSphere( Float fRadius, Float fMass, Bool IsBody ) = 0;
		virtual IRigidBody *CreateCapsule( Float fRadius, Float fLength, Float fMass, Bool IsBody ) = 0;
		virtual IRigidBody *CreateBox( Math::Point3DF &Size, Float fMass, Bool IsBody ) = 0;
		virtual IRigidModel *CreateMap( Renderer::Object::IMapModel *pMap ) = 0;
		virtual IRigidModel *CreateModel( Renderer::Object::IModel *pModel, Bool IsBody ) = 0;
	};
}
}

#pragma once


/**
	@file
	@brief �e�N�X�`���C���^�[�t�F�C�X
	@author �t���`
*/


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Renderer
{
	/**
		@brief �[�x�o�b�t�@�^�C�v
		@author �t���`
	*/
	enum eDepthBufferType
	{
		DEPTH_BUFFER_SURFACE,			///< �[�x�o�b�t�@�̓T�[�t�F�C�X
		DEPTH_BUFFER_TEXTURE_NVIDIA,	///< �[�x�o�b�t�@�̓e�N�X�`���iNVIDIA�d�l�j
		DEPTH_BUFFER_TEXTURE_ATI,		///< �[�x�o�b�t�@�̓e�N�X�`���iATI�d�l�j
	};

	/**
		@brief �e�N�X�`���^�C�v
		@author �t���`
	*/
	enum eTextureType
	{
		TEXTURE_TYPE_DEFAULT,		///< �ʏ�̕`��p�e�N�X�`��
		TEXTURE_TYPE_TARGET,		///< �`��^�[�Q�b�g�p�e�N�X�`��
		TEXTURE_TYPE_DEPTH,			///< �[�x�o�b�t�@�p�e�N�X�`��
		TEXTURE_TYPE_NONE,			///< ���ɂȂ�
	};

	/**
		@brief �e�N�X�`���C���^�[�t�F�C�X
		@author �t���`

		@note
		�e�N�X�`���𑀍삷�邽�߂̃C���^�[�t�F�C�X�ł��B<BR>
		IRender�C���^�[�t�F�C�X����擾�ł��܂��B
	*/
	class ITexture : public IInterface
	{
	public:
		virtual ~ITexture() {}

/**
@brief �摜�t�@�C���Ƃ��ĕۑ�
@author �t���`
@param pFileName	[in] �e�N�X�`���t�@�C����
@retval false	���s
@retval true	����

@note
�e�N�X�`���̓��e��TGA�摜�t�@�C���Ƃ��ĕۑ����܂��B

@code

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  ICore        *pCore        = NULL;
  IGraphicCard *pGraphicCard = NULL;
  IRender      *pRender      = NULL;
  ITexture     *pTex         = NULL;

  // �V�X�e���̋N��
  if ( !System::Initialize() )
  {
    return 0;
  }

  // ICore�̐���
  pCore = System::CreateCore();
  if ( pCore == NULL ) goto EXIT;               // ICore�ɂ�NullDevice���Ȃ��̂Ŏ��s�����NULL���Ԃ�

  // �R�A�̏�����
  if ( pCore->Initialize( "Sample Program", FRAME_RATE_60 ) )
  {
    // �A�v���P�[�V�����̊J�n
    pCore->Start( 640, 480, true );

    // �r�f�I�J�[�h������
    IGraphicCard *pGraphicCard = pCore->CreateGraphicCard( GRAPHIC_CARD_DEFAULT_NO );
    if ( pGraphicCard == NULL ) goto EXIT;      // IGraphicCard�ɂ�NullDevice���Ȃ��̂Ŏ��s�����NULL���Ԃ�

    // �����_���[�̐���
    IRender *pRender = pGraphicCard->CreateRender();
    if ( pRender == NULL ) goto EXIT;           // IRender�ɂ�NullDevice���Ȃ��̂Ŏ��s�����NULL���Ԃ�

    // �e�N�X�`���̐���
    pTex = pRender->CreateTextureFromFile( "sample.bmp" );

    // �e�N�X�`�����摜�Ƃ��ĕۑ�
    pTex->SaveToTGA( "hogehoge.tga" );

    // ���C�����[�v
    while ( pCore->Run() )
    {
    }
  }

EXIT:
  SAFE_RELEASE( pTex );                // �e�N�X�`���̉��
  SAFE_RELEASE( pRender );             // �����_���[�̉��
  SAFE_RELEASE( pGraphicCard );        // �r�f�I�J�[�h�̉��
  SAFE_RELEASE( pCore );               // �R�A�̉��

  System::Finalize();                  // �V�X�e���̏I���������s��

  return 0;
}
@endcode
*/
		virtual Bool SaveToTGA( const char *pFileName ) = 0;

/**
@brief �摜�t�@�C���Ƃ��ĕۑ�
@author �t���`
@param pFileName	[in] �e�N�X�`���t�@�C����
@retval false	���s
@retval true	����

@note
�e�N�X�`���̓��e��PNG�摜�t�@�C���Ƃ��ĕۑ����܂��B

@code

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  ICore        *pCore        = NULL;
  IGraphicCard *pGraphicCard = NULL;
  IRender      *pRender      = NULL;
  ITexture     *pTex         = NULL;

  // �V�X�e���̋N��
  if ( !System::Initialize() )
  {
    return 0;
  }

  // ICore�̐���
  pCore = System::CreateCore();
  if ( pCore == NULL ) goto EXIT;               // ICore�ɂ�NullDevice���Ȃ��̂Ŏ��s�����NULL���Ԃ�

  // �R�A�̏�����
  if ( pCore->Initialize( "Sample Program", FRAME_RATE_60 ) )
  {
    // �A�v���P�[�V�����̊J�n
    pCore->Start( 640, 480, true );

    // �r�f�I�J�[�h������
    IGraphicCard *pGraphicCard = pCore->CreateGraphicCard( GRAPHIC_CARD_DEFAULT_NO );
    if ( pGraphicCard == NULL ) goto EXIT;      // IGraphicCard�ɂ�NullDevice���Ȃ��̂Ŏ��s�����NULL���Ԃ�

    // �����_���[�̐���
    IRender *pRender = pGraphicCard->CreateRender();
    if ( pRender == NULL ) goto EXIT;           // IRender�ɂ�NullDevice���Ȃ��̂Ŏ��s�����NULL���Ԃ�

    // �e�N�X�`���̐���
    pTex = pRender->CreateTextureFromFile( "sample.bmp" );

    // �e�N�X�`�����摜�Ƃ��ĕۑ�
    pTex->SaveToPNG( "hogehoge.png" );

    // ���C�����[�v
    while ( pCore->Run() )
    {
    }
  }

EXIT:
  SAFE_RELEASE( pTex );                // �e�N�X�`���̉��
  SAFE_RELEASE( pRender );             // �����_���[�̉��
  SAFE_RELEASE( pGraphicCard );        // �r�f�I�J�[�h�̉��
  SAFE_RELEASE( pCore );               // �R�A�̉��

  System::Finalize();                  // �V�X�e���̏I���������s��

  return 0;
}
@endcode
*/
		virtual Bool SaveToPNG( const char *pFileName ) = 0;

/**
@brief ���e�N�X�`���T�C�Y�擾
@author �t���`
@return �e�N�X�`���̎��T�C�Y

@note
�e�N�X�`���̃T�C�Y���擾���܂��B<BR>
�Q�̗ݏ�łȂ��e�N�X�`�����쐬�����ۂ�<BR>
�f�o�C�X�����̃T�C�Y���T�|�[�g���Ă��Ȃ��Ƃ���<BR>
����ł���傫���̂Q�̗ݏ�̃T�C�Y�ɂȂ��Ă��܂��B

@code

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  ICore        *pCore        = NULL;
  IGraphicCard *pGraphicCard = NULL;
  IRender      *pRender      = NULL;
  ITexture     *pTex         = NULL;

  // �V�X�e���̋N��
  if ( !System::Initialize() )
  {
    return 0;
  }

  // ICore�̐���
  pCore = System::CreateCore();
  if ( pCore == NULL ) goto EXIT;               // ICore�ɂ�NullDevice���Ȃ��̂Ŏ��s�����NULL���Ԃ�

  // �R�A�̏�����
  if ( pCore->Initialize( "Sample Program", FRAME_RATE_60 ) )
  {
    // �A�v���P�[�V�����̊J�n
    pCore->Start( 640, 480, true );

    // �r�f�I�J�[�h������
    IGraphicCard *pGraphicCard = pCore->CreateGraphicCard( GRAPHIC_CARD_DEFAULT_NO );
    if ( pGraphicCard == NULL ) goto EXIT;      // IGraphicCard�ɂ�NullDevice���Ȃ��̂Ŏ��s�����NULL���Ԃ�

    // �����_���[�̐���
    IRender *pRender = pGraphicCard->CreateRender();
    if ( pRender == NULL ) goto EXIT;           // IRender�ɂ�NullDevice���Ȃ��̂Ŏ��s�����NULL���Ԃ�

    // �e�N�X�`���̐���
    pTex = pRender->CreateTextureFromFile( "sample.bmp" );

    // �e�N�X�`���̃T�C�Y���擾
    // �e�N�X�`���̎��T�C�Y
    // �f�o�C�X�ɂ���Ă͐������ɗv���ʂ�ɃT�C�Y�͂Ȃ�Ȃ�
    Math::Point2DI Size = pTex->GetSize();

    // ���C�����[�v
    while ( pCore->Run() )
    {
    }
  }

EXIT:
  SAFE_RELEASE( pTex );                // �e�N�X�`���̉��
  SAFE_RELEASE( pRender );             // �����_���[�̉��
  SAFE_RELEASE( pGraphicCard );        // �r�f�I�J�[�h�̉��
  SAFE_RELEASE( pCore );               // �R�A�̉��

  System::Finalize();                  // �V�X�e���̏I���������s��

  return 0;
}
@endcode
*/
		virtual Math::Point2DI GetSize( void ) = 0;

/**
@brief �v���e�N�X�`���T�C�Y�擾
@author �t���`
@return �e�N�X�`���̃T�C�Y

@note
�e�N�X�`���̌��T�C�Y���擾���܂��B<BR>
�쐬���Ɏw�肵���傫�����擾���܂��B<BR>
���̑傫���͎��ۂ̃e�N�X�`���T�C�Y�Ƃ͈Ⴄ�ꍇ������܂��B

@code

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  ICore        *pCore        = NULL;
  IGraphicCard *pGraphicCard = NULL;
  IRender      *pRender      = NULL;
  ITexture     *pTex         = NULL;

  // �V�X�e���̋N��
  if ( !System::Initialize() )
  {
    return 0;
  }

  // ICore�̐���
  pCore = System::CreateCore();
  if ( pCore == NULL ) goto EXIT;               // ICore�ɂ�NullDevice���Ȃ��̂Ŏ��s�����NULL���Ԃ�

  // �R�A�̏�����
  if ( pCore->Initialize( "Sample Program", FRAME_RATE_60 ) )
  {
    // �A�v���P�[�V�����̊J�n
    pCore->Start( 640, 480, true );

    // �r�f�I�J�[�h������
    IGraphicCard *pGraphicCard = pCore->CreateGraphicCard( GRAPHIC_CARD_DEFAULT_NO );
    if ( pGraphicCard == NULL ) goto EXIT;      // IGraphicCard�ɂ�NullDevice���Ȃ��̂Ŏ��s�����NULL���Ԃ�

    // �����_���[�̐���
    IRender *pRender = pGraphicCard->CreateRender();
    if ( pRender == NULL ) goto EXIT;           // IRender�ɂ�NullDevice���Ȃ��̂Ŏ��s�����NULL���Ԃ�

    // �e�N�X�`���̐���
    pTex = pRender->CreateTextureFromFile( "sample.bmp" );

    // �������Ƀ��N�G�X�g�����e�N�X�`���̃T�C�Y
    // �t�@�C���ǂݍ��݂̏ꍇ�t�@�C����̂ŉ摜�̃T�C�Y
    Math::Point2DI Size = pTex->GetOriginalSize();

    // ���C�����[�v
    while ( pCore->Run() )
    {
    }
  }

EXIT:
  SAFE_RELEASE( pTex );                // �e�N�X�`���̉��
  SAFE_RELEASE( pRender );             // �����_���[�̉��
  SAFE_RELEASE( pGraphicCard );        // �r�f�I�J�[�h�̉��
  SAFE_RELEASE( pCore );               // �R�A�̉��

  System::Finalize();                  // �V�X�e���̏I���������s��

  return 0;
}
@endcode
*/
		virtual Math::Point2DI GetOriginalSize( void ) = 0;

/**
@brief �e�N�X�`���ϊ��p�p�����[�^�[�擾
@author �t���`
@return �ϊ��p�̒l

@note
�e�N�X�`���̌��摜�̍��W����e�N�X�`���̒l���擾���邽�߂̕ϊ��p�̒l���擾���܂��B

@code

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  ICore        *pCore        = NULL;
  IGraphicCard *pGraphicCard = NULL;
  IRender      *pRender      = NULL;
  ITexture     *pTex         = NULL;

  // �V�X�e���̋N��
  if ( !System::Initialize() )
  {
    return 0;
  }

  // ICore�̐���
  pCore = System::CreateCore();
  if ( pCore == NULL ) goto EXIT;               // ICore�ɂ�NullDevice���Ȃ��̂Ŏ��s�����NULL���Ԃ�

  // �R�A�̏�����
  if ( pCore->Initialize( "Sample Program", FRAME_RATE_60 ) )
  {
    // �A�v���P�[�V�����̊J�n
    pCore->Start( 640, 480, true );

    // �r�f�I�J�[�h������
    IGraphicCard *pGraphicCard = pCore->CreateGraphicCard( GRAPHIC_CARD_DEFAULT_NO );
    if ( pGraphicCard == NULL ) goto EXIT;      // IGraphicCard�ɂ�NullDevice���Ȃ��̂Ŏ��s�����NULL���Ԃ�

    // �����_���[�̐���
    IRender *pRender = pGraphicCard->CreateRender();
    if ( pRender == NULL ) goto EXIT;           // IRender�ɂ�NullDevice���Ȃ��̂Ŏ��s�����NULL���Ԃ�

    // �e�N�X�`���̐���
    pTex = pRender->CreateTextureFromFile( "sample.bmp" );

    // ���摜��(100,50)���W��UV�֕ϊ�
    Math::Point2DF Trans = pTex->GetPixelToTexelTransform();
    Float u = 100.0f * Trans.x;
    Float v =  50.0f * Trans.y;

    // ���C�����[�v
    while ( pCore->Run() )
    {
    }
  }

EXIT:
  SAFE_RELEASE( pTex );                // �e�N�X�`���̉��
  SAFE_RELEASE( pRender );             // �����_���[�̉��
  SAFE_RELEASE( pGraphicCard );        // �r�f�I�J�[�h�̉��
  SAFE_RELEASE( pCore );               // �R�A�̉��

  System::Finalize();                  // �V�X�e���̏I���������s��

  return 0;
}
@endcode
*/
		virtual Math::Point2DF GetPixelToTexelTransform( void ) = 0;

/**
@brief �����_�����O�^�[�Q�b�g���e��ۑ�
@author �t���`
@retval true	����
@retval false	���s

@note
�����_�����O�^�[�Q�b�g�̌��݂̓��e���o�b�N�A�b�v���܂��B<BR>
�o�b�N�A�b�v���ꂽ���e�̓f�o�C�X�̃��X�g���Ɏ����I�ɕ�������܂��B

@code

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  ICore        *pCore        = NULL;
  IGraphicCard *pGraphicCard = NULL;
  IRender      *pRender      = NULL;
  ITexture     *pTex         = NULL;

  // �V�X�e���̋N��
  if ( !System::Initialize() )
  {
    return 0;
  }

  // ICore�̐���
  pCore = System::CreateCore();
  if ( pCore == NULL ) goto EXIT;               // ICore�ɂ�NullDevice���Ȃ��̂Ŏ��s�����NULL���Ԃ�

  // �R�A�̏�����
  if ( pCore->Initialize( "Sample Program", FRAME_RATE_60 ) )
  {
    // �A�v���P�[�V�����̊J�n
    pCore->Start( 640, 480, true );

    // �r�f�I�J�[�h������
    IGraphicCard *pGraphicCard = pCore->CreateGraphicCard( GRAPHIC_CARD_DEFAULT_NO );
    if ( pGraphicCard == NULL ) goto EXIT;      // IGraphicCard�ɂ�NullDevice���Ȃ��̂Ŏ��s�����NULL���Ԃ�

    // �����_���[�̐���
    IRender *pRender = pGraphicCard->CreateRender();
    if ( pRender == NULL ) goto EXIT;           // IRender�ɂ�NullDevice���Ȃ��̂Ŏ��s�����NULL���Ԃ�

    // �e�N�X�`���̐���
    pTex = pRender->CreateTextureRenderTarget( 256, 256 );

    // �f�o�C�X���X�g���ɓ��e�������ł���悤��
    // ���݂̏�Ԃ��o�b�N�A�b�v���Ă����B
    //   �ʏ�͉��炩�̃����_�����O���s�������ɁA
    //   ���̓��e��ۑ����Ă��������ꍇ�Ɏg���B
    pTex->BackupTargetBuffer();

    // ���C�����[�v
    while ( pCore->Run() )
    {
    }
  }

EXIT:
  SAFE_RELEASE( pTex );                // �e�N�X�`���̉��
  SAFE_RELEASE( pRender );             // �����_���[�̉��
  SAFE_RELEASE( pGraphicCard );        // �r�f�I�J�[�h�̉��
  SAFE_RELEASE( pCore );               // �R�A�̉��

  System::Finalize();                  // �V�X�e���̏I���������s��

  return 0;
}
@endcode
*/
		virtual Bool BackupTargetBuffer( void ) = 0;

/**
@brief ��ނ��擾
@author �t���`
@return	�e�N�X�`�����ǂ̎�ނɑ����邩���擾���܂��B

@note
�e�N�X�`���̎�ނ��擾���܂��B<BR>
IRender::SetRenderTarget()�Ɏg����̂�TEXTURE_TYPE_TARGET������<BR>
IRender::SetDepthBuffer()�Ɏg����̂�TEXTURE_TYPE_DEPTH�����ł��B
*/
		virtual eTextureType GetType( void ) = 0;

/**
@brief �[�x�o�b�t�@�̎�ނ��擾
@author �t���`
@return	�[�x�o�b�t�@�̎��

@note
�[�x�o�b�t�@�̎�ނ��擾���܂��B<BR>
�Ԃ�l��DEPTH_BUFFER_TEXTURE�̏ꍇ�̓e�N�X�`���Ƃ��Đ[�x�o�b�t�@������Ă��܂��B
*/
		virtual eDepthBufferType GetDepthBufferType( void ) = 0;

/**
@brief �t�B���^�����O�����̐�����擾
@author �t���`
@retval false	�t�B���^�����O���A���t�@�u�����h�o���Ȃ�
@retval true	�t�B���^�����O���A���t�@�u�����h�o����

@note
�t�B���^�����O�\�ȃt�H�[�}�b�g�����擾���܂��B
*/
		virtual Bool IsFilterEnable( void ) = 0;
	};
}
}

#pragma once


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Network
{
	/**
		@brief	�z�X�g���
		@author �t���`
	*/
	struct SHostInfo
	{
		char Name[64];						///< �z�X�g��
		char Alias[16][64];					///< �z�X�g�ʖ��e�[�u��
		char Address[16][64];				///< IP�A�h���X�e�[�u��
		Sint32 Type;						///< �f�[�^�^�C�v
		Sint32 Length;						///< �f�[�^�T�C�Y
		Sint32 AliasCount;					///< �G�C���A�X��
		Sint32 AddressCount;				///< IP�A�h���X��
	};

	/**
		@brief �l�b�g���[�N�Ǘ��N���X
		@author �t���`

		@note
		Selene�Ŏg�p����l�b�g���[�N�̊Ǘ����s���܂��B
	*/
	class INetworkManager : public IInterface
	{
	public:
		virtual ~INetworkManager() {}

/**
@brief �G���[������擾
@author �t���`
@return	������̃|�C���^

@note
��A�̃l�b�g���[�N�������������G���[���b�Z�[�W���擾���܂��B

@code

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  Network::INetworkManager	*pNetworkMgr	= NULL;

  // �V�X�e���̏�����
  System::Initialize();

  // �l�b�g���[�N�}�l�[�W���[�̐���
  pNetworkMgr = Network::CreateManager();

  // �T�[�o�[��TCP���g���Đڑ�����
  pTCP = pNetworkMgr->ConnectByTCP( "127.0.0.1", 80 );
  if ( pTCP == NULL )
  {
    // �G���[���b�Z�[�W
    ::MessageBox( NULL, pNetworkMgr->GetLastErrorString(), "ERROR", MB_ICONERROR );
  }

  // �l�b�g���[�N�}�l�[�W���[�̉��
  SAFE_RELEASE( pNetworkMgr );

  // �V�X�e���̉��
  System::Finalize();

  return 0;
}
@endcode
*/
		virtual const char *GetLastErrorString( void ) = 0;

/**
@brief �N���C�A���g����
@author �t���`
@param pTargetHost	[in] �ڑ���̃z�X�g���iIP�A�h���X�j
@param TargetPort	[in] �ڑ���̃|�[�g
@retval	NULL		���s
@retval	NULL�ȊO	�N���C�A���g�̃C���^�[�t�F�C�X

@note
�w�肵���z�X�g�ւ�TCP�ڑ������݂܂��B<BR>
�ڑ��ł����ꍇ��TCP����p�̃C���^�[�t�F�C�X���Ԃ�܂��B

@code

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  Network::INetworkManager	*pNetworkMgr	= NULL;
  Network::ISocketTCP		*pTCP			= NULL;

  // �V�X�e���̏�����
  System::Initialize();

  // �l�b�g���[�N�}�l�[�W���[�̐���
  pNetworkMgr = Network::CreateManager();

  // �T�[�o�[��TCP���g���Đڑ�����
  pTCP = pNetworkMgr->ConnectByTCP( "127.0.0.1", 80 );
  if ( pTCP == NULL )
  {
    // �G���[���b�Z�[�W
    ::MessageBox( NULL, pNetworkMgr->GetLastErrorString(), "ERROR", MB_ICONERROR );
  }

  // TCP�ڑ������
  SAFE_RELEASE( pTCP );

  // �l�b�g���[�N�}�l�[�W���[�̉��
  SAFE_RELEASE( pNetworkMgr );

  // �V�X�e���̉��
  System::Finalize();

  return 0;
}
@endcode
*/
		virtual ISocketTCP *ConnectByTCP( const char *pTargetHost, Uint16 TargetPort ) = 0;

/**
@brief �T�[�o�[�@�\�𐶐����܂�
@author �t���`
@param Port			[in] �|�[�g�ԍ�
@param ConnectMax	[in] �ڑ��ő吔
@retval	NULL		���s
@retval	NULL�ȊO	�T�[�o�[�̃C���^�[�t�F�C�X

@note
�T�[�o�[�@�\�𐶐����A���̃C���^�[�t�F�C�X���擾���܂��B<BR>
�ڑ��ł����ꍇ��TCP����p�̃C���^�[�t�F�C�X���Ԃ�܂��B

@code

using namespace Selene;

int main()
{
  Network::INetworkManager  *pNetworkMgr  = NULL;
  Network::IServerTCP      *pServer    = NULL;

  // �V�X�e���̏�����
  System::Initialize();

  // �l�b�g���[�N�}�l�[�W���[�̐���
  pNetworkMgr = Network::CreateManager();

  // �T�[�o�[�𐶐�����
  pServer = pNetworkMgr->CreateServer( HOST_PORT, 16 );
  if ( pServer == NULL )
  {
    // ���s
    ::MessageBox( NULL, pNetworkMgr->GetLastErrorString(), "ERROR", MB_ICONERROR );
  }

  // �L�[���͂ŏI��
  getchar();

  // �T�[�o�[�����
  SAFE_RELEASE( pServer );

  // �l�b�g���[�N�}�l�[�W���[�̉��
  SAFE_RELEASE( pNetworkMgr );

  // �V�X�e���̉��
  System::Finalize();

  return 0;
}
@endcode
*/
	virtual IServerTCP *CreateServer( Uint16 Port, Uint32 ConnectMax = 32 ) = 0;

/**
@brief �z�X�g���擾
@author �t���`
@param Info		[out] �z�X�g���

@note
��A�̃l�b�g���[�N�������������G���[���b�Z�[�W���擾���܂��B

@code

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  Network::INetworkManager	*pNetworkMgr	= NULL;

  // �V�X�e���̏�����
  System::Initialize();

  // �l�b�g���[�N�}�l�[�W���[�̐���
  pNetworkMgr = Network::CreateManager();

  // �A�v���P�[�V���������삵�Ă���PC�̃z�X�g�����擾
  SHostInfo Info;
  pNetworkMgr->GetHostInfo( Info );

  // �l�b�g���[�N�}�l�[�W���[�̉��
  SAFE_RELEASE( pNetworkMgr );

  // �V�X�e���̉��
  System::Finalize();

  return 0;
}
@endcode
*/
		virtual void GetHostInfo( SHostInfo &Info ) = 0;
	};
}
}

#pragma once


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Network
{
	/**
		@brief TCP�ڑ��N���C�A���g�N���X
		@author �t���`

		@note
		Selene�Ŏg�p����l�b�g���[�N�������s���܂��B
	*/
	class ISocketTCP : public IInterface
	{
	public:
		virtual ~ISocketTCP() {}

/**
@brief �f�[�^���M
@author �t���`
@param pData	[in] �f�[�^�i�[�o�b�t�@
@param Size		[in] ���M�T�C�Y
@retval false	���s
@retval true	����

@note
�f�[�^�̑��M���s���܂��B<BR>
�w��T�C�Y�̑��M����������܂Ŋ֐����甲���Ă��܂���B

@code

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  Network::INetworkManager	*pNetworkMgr	= NULL;
  Network::ISocketTCP		*pTCP			= NULL;

  // �V�X�e���̏�����
  System::Initialize();

  // �l�b�g���[�N�}�l�[�W���[�̐���
  pNetworkMgr = Network::CreateManager();

  // �T�[�o�[��TCP���g���Đڑ�����
  pTCP = pNetworkMgr->ConnectByTCP( "127.0.0.1", 80 );
  if ( pTCP == NULL )
  {
    // �G���[���b�Z�[�W
    ::MessageBox( NULL, pNetworkMgr->GetLastErrorString(), "ERROR", MB_ICONERROR );
  }

  const Uint32 MAX_PACKET_SIZE = 256;
  Sint8 PacketBuffer[MAX_PACKET_SIZE];

  // �f�[�^���M
  if ( !pTCP->Send( PacketBuffer, sizeof(PacketBuffer) ) )
  {
    // �G���[���b�Z�[�W
    ::MessageBox( NULL, pNetworkMgr->GetLastErrorString(), "ERROR", MB_ICONERROR );
  }

  // TCP�ڑ������
  SAFE_RELEASE( pTCP );

  // �l�b�g���[�N�}�l�[�W���[�̉��
  SAFE_RELEASE( pNetworkMgr );

  // �V�X�e���̉��
  System::Finalize();

  return 0;
}
@endcode
*/
		virtual Bool Send( const void *pData, Sint32 Size ) = 0;

/**
@brief �f�[�^��M
@author �t���`
@param pData	[in] �f�[�^�i�[�o�b�t�@
@param Size		[in] ��M�T�C�Y
@retval false	���s
@retval true	����

@note
�f�[�^�̎�M���s���܂��B<BR>
�w��T�C�Y�̎�M����������܂Ŋ֐����甲���Ă��܂���B

@code

using namespace Selene;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
  Network::INetworkManager	*pNetworkMgr	= NULL;
  Network::ISocketTCP		*pTCP			= NULL;

  // �V�X�e���̏�����
  System::Initialize();

  // �l�b�g���[�N�}�l�[�W���[�̐���
  pNetworkMgr = Network::CreateManager();

  // �T�[�o�[��TCP���g���Đڑ�����
  pTCP = pNetworkMgr->ConnectByTCP( "127.0.0.1", 80 );
  if ( pTCP == NULL )
  {
    // �G���[���b�Z�[�W
    ::MessageBox( NULL, pNetworkMgr->GetLastErrorString(), "ERROR", MB_ICONERROR );
  }

  const Uint32 MAX_PACKET_SIZE = 256;
  Sint8 PacketBuffer[MAX_PACKET_SIZE];

  // �f�[�^��M
  if ( !pTCP->Recv( PacketBuffer, sizeof(PacketBuffer) ) )
  {
    // �G���[���b�Z�[�W
    ::MessageBox( NULL, pNetworkMgr->GetLastErrorString(), "ERROR", MB_ICONERROR );
  }

  // TCP�ڑ������
  SAFE_RELEASE( pTCP );

  // �l�b�g���[�N�}�l�[�W���[�̉��
  SAFE_RELEASE( pNetworkMgr );

  // �V�X�e���̉��
  System::Finalize();

  return 0;
}
@endcode
*/
		virtual Bool Recv( void *pData, Sint32 Size ) = 0;
	};
}
}

#pragma once


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Network
{
	typedef void (*ClientControlCallback)( IServerClientTCP *pClient );		///< �N���C�A���g����p

	/**
		@brief TCP�ڑ��T�[�o�[�N���X
		@author �t���`

		@note
		Selene�Ŏg�p����l�b�g���[�N�������s���܂��B
	*/
	class IServerTCP : public IInterface
	{
	public:
		virtual ~IServerTCP() {}

/**
@brief �T�[�o�[�@�\���J�n
@author �t���`
@param pCallback	[in] �N���C�A���g�����p�R�[���o�b�N�֐�

@note
�T�[�o�[�@�\���J�n���A�N���C�A���g����̐ڑ���҂��܂��B<BR>
�N���C�A���g���ڑ�����邽�тɃX���b�h������A���̒�����pCallback��<BR>
�w�肵���֐��ɏ��������܂��B

@code

using namespace Selene;

static void ClientRecieve( Network::IServerClientTCP *pClient );

int main()
{
  Network::INetworkManager  *pNetworkMgr  = NULL;
  Network::IServerTCP      *pServer    = NULL;

  // �V�X�e���̏�����
  System::Initialize();

  // �l�b�g���[�N�}�l�[�W���[�̐���
  pNetworkMgr = Network::CreateManager();

  // �T�[�o�[�𐶐�����
  pServer = pNetworkMgr->CreateServer( 80, 16 );
  if ( pServer == NULL )
  {
    // ���s
    ::MessageBox( NULL, pNetworkMgr->GetLastErrorString(), "ERROR", MB_ICONERROR );
  }

  // �T�[�o�[�����J�n
  pServer->Start( ClientRecieve );

  // �L�[���͂ŏI��
  getchar();

  // �T�[�o�[�����
  SAFE_RELEASE( pServer );

  // �l�b�g���[�N�}�l�[�W���[�̉��
  SAFE_RELEASE( pNetworkMgr );

  // �V�X�e���̉��
  System::Finalize();

  return 0;
}

void ClientRecieve( Network::IServerClientTCP *pClient )
{
  // �ڑ����N���C�A���g���
  Network::SHostInfo HostInfo;
  pClient->GetHostInfo( HostInfo );

  // �N���C�A���g�p���C���ʐM���[�v
  for ( ; ; )
  {
  }
}
@endcode
*/
		virtual Bool Start( ClientControlCallback pCallback ) = 0;

/**
@brief �f�[�^���M
@author �t���`
@param pData	[in] �f�[�^�i�[�o�b�t�@
@param Size		[in] ���M�T�C�Y
@retval false	���s
@retval true	����

@note
�ڑ�����Ă���S�ẴN���C�A���g�Ƀf�[�^�̑��M���s���܂��B<BR>
�w��T�C�Y�̑��M����������܂Ŋ֐����甲���Ă��܂���B

@code

using namespace Selene;

static void ClientRecieve( Network::IServerClientTCP *pClient );

int main()
{
  Network::INetworkManager  *pNetworkMgr  = NULL;
  Network::IServerTCP      *pServer    = NULL;

  // �V�X�e���̏�����
  System::Initialize();

  // �l�b�g���[�N�}�l�[�W���[�̐���
  pNetworkMgr = Network::CreateManager();

  // �T�[�o�[�𐶐�����
  pServer = pNetworkMgr->CreateServer( 80, 16 );
  if ( pServer == NULL )
  {
    // ���s
    ::MessageBox( NULL, pNetworkMgr->GetLastErrorString(), "ERROR", MB_ICONERROR );
  }

  // �T�[�o�[�����J�n
  pServer->Start( ClientRecieve );

  // �S�ẴN���C�A���g�ɑ��M
  pServer->SendAllClient( "�߂����[��", strlen("�߂����[��") + 1 );

  // �L�[���͂ŏI��
  getchar();

  // �T�[�o�[�����
  SAFE_RELEASE( pServer );

  // �l�b�g���[�N�}�l�[�W���[�̉��
  SAFE_RELEASE( pNetworkMgr );

  // �V�X�e���̉��
  System::Finalize();

  return 0;
}

void ClientRecieve( Network::IServerClientTCP *pClient )
{
  // �ڑ����N���C�A���g���
  Network::SHostInfo HostInfo;
  pClient->GetHostInfo( HostInfo );

  // �N���C�A���g�p���C���ʐM���[�v
  for ( ; ; )
  {
  }
}
@endcode
*/
		virtual Bool SendAllClient( const void *pData, Sint32 Size ) = 0;
	};
}
}

#pragma once


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Network
{
	/**
		@brief TCP�ڑ��T�[�o�[�ɐڑ����ꂽ�N���C�A���g�N���X
		@author �t���`

		@note
		Selene�Ŏg�p����l�b�g���[�N�������s���܂��B
	*/
	class IServerClientTCP : public IInterface
	{
	public:
		virtual ~IServerClientTCP() {}

/**
@brief �f�[�^���M
@author �t���`
@param pData	[in] �f�[�^�i�[�o�b�t�@
@param Size		[in] ���M�T�C�Y
@retval false	���s
@retval true	����

@note
�f�[�^�̑��M���s���܂��B<BR>
�w��T�C�Y�̑��M����������܂Ŋ֐����甲���Ă��܂���B

@code

using namespace Selene;

static void ClientRecieve( Network::IServerClientTCP *pClient );

int main()
{
  Network::INetworkManager  *pNetworkMgr  = NULL;
  Network::IServerTCP      *pServer    = NULL;

  // �V�X�e���̏�����
  System::Initialize();

  // �l�b�g���[�N�}�l�[�W���[�̐���
  pNetworkMgr = Network::CreateManager();

  // �T�[�o�[�𐶐�����
  pServer = pNetworkMgr->CreateServer( 80, 16 );
  if ( pServer == NULL )
  {
    // ���s
    ::MessageBox( NULL, pNetworkMgr->GetLastErrorString(), "ERROR", MB_ICONERROR );
  }

  // �T�[�o�[�����J�n
  pServer->Start( ClientRecieve );

  // �L�[���͂ŏI��
  getchar();

  // �T�[�o�[�����
  SAFE_RELEASE( pServer );

  // �l�b�g���[�N�}�l�[�W���[�̉��
  SAFE_RELEASE( pNetworkMgr );

  // �V�X�e���̉��
  System::Finalize();

  return 0;
}

void ClientRecieve( Network::IServerClientTCP *pClient )
{
  // �ڑ����N���C�A���g���
  Network::SHostInfo HostInfo;
  pClient->GetHostInfo( HostInfo );

  // �N���C�A���g�p���C���ʐM���[�v
  for ( ; ; )
  {
    const Uint32 MAX_PACKET_SIZE = 256;
    Sint8 PacketBuffer[MAX_PACKET_SIZE];

    // �N���C�A���g�փp�P�b�g�𑗂�
    if ( !pClient->Send( PacketBuffer, sizeof(PacketBuffer) ) )
    {
      // �G���[or�ؒf
      return;
    }
  }
}
@endcode
*/
		virtual Bool Send( const void *pData, Sint32 Size ) = 0;

/**
@brief �f�[�^��M
@author �t���`
@param pData	[in] �f�[�^�i�[�o�b�t�@
@param Size		[in] ��M�T�C�Y
@retval false	���s
@retval true	����

@note
�f�[�^�̎�M���s���܂��B<BR>
�w��T�C�Y�̎�M����������܂Ŋ֐����甲���Ă��܂���B

@code

using namespace Selene;

static void ClientRecieve( Network::IServerClientTCP *pClient );

int main()
{
  Network::INetworkManager  *pNetworkMgr  = NULL;
  Network::IServerTCP      *pServer    = NULL;

  // �V�X�e���̏�����
  System::Initialize();

  // �l�b�g���[�N�}�l�[�W���[�̐���
  pNetworkMgr = Network::CreateManager();

  // �T�[�o�[�𐶐�����
  pServer = pNetworkMgr->CreateServer( 80, 16 );
  if ( pServer == NULL )
  {
    // ���s
    ::MessageBox( NULL, pNetworkMgr->GetLastErrorString(), "ERROR", MB_ICONERROR );
  }

  // �T�[�o�[�����J�n
  pServer->Start( ClientRecieve );

  // �L�[���͂ŏI��
  getchar();

  // �T�[�o�[�����
  SAFE_RELEASE( pServer );

  // �l�b�g���[�N�}�l�[�W���[�̉��
  SAFE_RELEASE( pNetworkMgr );

  // �V�X�e���̉��
  System::Finalize();

  return 0;
}

void ClientRecieve( Network::IServerClientTCP *pClient )
{
  // �ڑ����N���C�A���g���
  Network::SHostInfo HostInfo;
  pClient->GetHostInfo( HostInfo );

  // �N���C�A���g�p���C���ʐM���[�v
  for ( ; ; )
  {
    const Uint32 MAX_PACKET_SIZE = 256;
    Sint8 PacketBuffer[MAX_PACKET_SIZE];

    // �N���C�A���g����̃p�P�b�g��҂�
    if ( !pClient->Recv( PacketBuffer, sizeof(PacketBuffer) ) )
    {
      // �G���[or�ؒf
      return;
    }
  }
}
@endcode
*/
		virtual Bool Recv( void *pData, Sint32 Size ) = 0;

/**
@brief �ڑ����ꂽ�N���C�A���g�̏��擾
@author �t���`
@param Info	[in] �N���C�A���g���

@note
�ڑ����ꂽ�N���C�A���g�̏����擾���܂��B

@code

using namespace Selene;

static void ClientRecieve( Network::IServerClientTCP *pClient );

int main()
{
  Network::INetworkManager  *pNetworkMgr  = NULL;
  Network::IServerTCP      *pServer    = NULL;

  // �V�X�e���̏�����
  System::Initialize();

  // �l�b�g���[�N�}�l�[�W���[�̐���
  pNetworkMgr = Network::CreateManager();

  // �T�[�o�[�𐶐�����
  pServer = pNetworkMgr->CreateServer( 80, 16 );
  if ( pServer == NULL )
  {
    // ���s
    ::MessageBox( NULL, pNetworkMgr->GetLastErrorString(), "ERROR", MB_ICONERROR );
  }

  // �T�[�o�[�����J�n
  pServer->Start( ClientRecieve );

  // �L�[���͂ŏI��
  getchar();

  // �T�[�o�[�����
  SAFE_RELEASE( pServer );

  // �l�b�g���[�N�}�l�[�W���[�̉��
  SAFE_RELEASE( pNetworkMgr );

  // �V�X�e���̉��
  System::Finalize();

  return 0;
}

void ClientRecieve( Network::IServerClientTCP *pClient )
{
  // �ڑ����N���C�A���g���
  Network::SHostInfo HostInfo;
  pClient->GetHostInfo( HostInfo );

  // �N���C�A���g�p���C���ʐM���[�v
  for ( ; ; )
  {
    const Uint32 MAX_PACKET_SIZE = 256;
    Sint8 PacketBuffer[MAX_PACKET_SIZE];

    // �N���C�A���g����̃p�P�b�g��҂�
    if ( !pClient->Recv( PacketBuffer, sizeof(PacketBuffer) ) )
    {
      // �G���[or�ؒf
      return;
    }
  }
}
@endcode
*/
		virtual void GetHostInfo( SHostInfo &Info ) = 0;
	};
}
}

#pragma once


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace File
{
	/**
		@brief �t�@�C���Ǘ��N���X
		@author �t���`

		Selene�Ŏg�p����t�@�C���̊Ǘ����s���܂��B
	*/
	class IFileManager
	{
	public:
		virtual ~IFileManager() {}

		/**
			@brief �L�����`�F�b�N
			@author �t���`
			@retval true ����
			@retval false �L��

			�C���^�[�t�F�C�X���L�����������𒲂ׂ܂��B
		*/
		virtual Bool IsInvalid( void ) = 0;

		/**
			@brief �Q�ƃJ�E���^�f�N�������g
			@author �t���`
			@return �f�N�������g��̎Q�ƃJ�E���g

			�Q�ƃJ�E���^���f�N�������g���A<BR>
			�Q�ƃJ�E���g��0�ɂȂ������_�Ń��������������܂��B
		*/
		virtual Sint32 Release( void ) = 0;

		/**
			@brief �Q�ƃJ�E���^�C���N�������g
			@author �t���`
			@return �C���N�������g��̎Q�ƃJ�E���g

			�Q�ƃJ�E���^���C���N�������g���܂��B<BR>
			�C���N�������g�����Q�ƃJ�E���g��Release()���ĂԂ��Ƃɂ��f�N�������g����܂��B<BR>
			AddRef()�������C���^�[�t�F�C�X�͕K��Release()�ŉ�����Ă��������B
		*/
		virtual Sint32 AddRef( void	) = 0;

		/**
			@brief �t�@�C�����[�h�p�X�ݒ�
			@author �t���`
			@param Priority		[in] �����v���C�I���e�B
			@param pRootPath	[in] ���[�g�f�B���N�g��
			@param pPassword	[in] �p�b�N�t�@�C���̏ꍇ�̃p�X���[�h�i�Ȃ��ꍇ��NULL�j

			�t�@�C���̓ǂݍ��݂��s�����[�g�̃f�B���N�g����ݒ肵�܂��B<BR>
			�����Őݒ肳�ꂽ �p�X ����� �p�X.Pack �t�@�C���͓���Ɉ����܂��B<BR>
			�܂�v���O�����̕ύX�Ȃ��o���ɂ܂����������悤�ɃA�N�Z�X�\�ł��B
		*/
		virtual void SetRootPath( Sint32 Priority, const char *pRootPath, const char *pPassword = NULL ) = 0;

		/**
			@brief �J�����g�f�B���N�g���ݒ�
			@author �t���`
			@param pCurrentDir	[in] �f�B���N�g����

			�t�@�C���������s���ۂ̃J�����g�̃f�B���N�g����ݒ肵�܂��B<BR>
			�����Őݒ肳�ꂽ�f�B���N�g�������[�g�Ƃ��ăt�@�C���̌������s���܂��B<BR>
			<BR>
			SetRootPath( 0, "Data", "Data.Pack" ); �Ƃ����ݒ肪�s��ꂢ�āA<BR>
			SetCurrentPath( "texture" ); �ƂȂ��Ă���Ƃ��usample.bmp�v�Ǝw�肵�ēǂݍ��݂����ꍇ<BR>
			<BR>
			�uData\texture\sample.bmp�v��T���ɍs���A������Ȃ��ꍇ��<BR>
			�uData.Pack�v�t�@�C�����́utexture\sample.bmp�v�t�@�C����T���ɍs���܂��B
		*/
		virtual void SetCurrentPath( const char *pCurrentDir ) = 0;

		/**
			@brief �t�@�C�����[�h
			@author �t���`
			@param pFile	[in] �t�@�C����
			@param ppData	[out] �t�@�C���f�[�^�i�[��
			@param pSize	[out] �t�@�C���T�C�Y�i�[��
			@retval true	����
			@retval false	���s

			�t�@�C�������[�h���A�������ɓW�J���܂��B
		*/
		virtual Bool Load( const char *pFile, void **ppData, Sint32 *pSize ) = 0;

		/**
			@brief �f�[�^���
			@author �t���`
			@param pData	[in] �f�[�^

			Load()�֐��Ŏ擾�����f�[�^�����������������܂��B<BR>
			���̊֐����g�������@�ȊO�ł̉���͊��ˑ����邽�߁A<BR>
			�������������Ȃ��\��������܂��B
		*/
		virtual void Free( void *pData ) = 0;

		/**
			@brief �t�@�C���I�[�v��
			@author �t���`
			@param pFile		[in] �t�@�C����
			@retval NULL		���s
			@retval NULL�ȊO	�t�@�C���C���^�[�t�F�C�X

			���\�[�X�t�@�C�����I�[�v�����܂��B<BR>
			�����ł������\�[�X�t�@�C���̓Q�[���Ŏg����f�[�^�S�ʂ̎��ł��B<BR>
			�܂�p�b�N�t�@�C���̓��e�A����у��[�g�f�B���N�g���ȉ��̃f�[�^�ł��B<BR>
			SetRootPath()�Ŏw�肳��Ă���[�t�H���_]��[�p�b�N�t�@�C��]��<BR>
			���Ƀt�@�C�����������܂��B<BR>
			�I�[�v�������t�@�C���̓p�b�N�t�@�C���ł����Ă��A<BR>
			�ʏ�̃t�@�C���Ɠ����悤�ɃA�N�Z�X���邱�Ƃ��o���܂��B<BR>
			�܂����̊֐�����擾����IFIle�C���^�[�t�F�C�X�͓ǂݎ���p�ł��B<BR>
			�g�p���I������IFile�C���^�[�t�F�C�X��Release()�ŉ�����Ă��������B
		*/
		virtual IResourceFile *FileOpen( const char *pFile ) = 0;
	};
}
}

#pragma once


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace File
{
	/**
		@brief ���\�[�X�t�@�C������
		@author �t���`
	*/
	class IResourceFile
	{
	public:
		virtual ~IResourceFile() {};

		/**
			@brief �L�����`�F�b�N
			@author �t���`
			@retval true ����
			@retval false �L��

			�C���^�[�t�F�C�X���L�����������𒲂ׂ܂��B
		*/
		virtual Bool IsInvalid( void ) = 0;

		/**
			@brief �Q�ƃJ�E���^�f�N�������g
			@author �t���`
			@return �f�N�������g��̎Q�ƃJ�E���g

			�Q�ƃJ�E���^���f�N�������g���A<BR>
			�Q�ƃJ�E���g��0�ɂȂ������_�Ń��������������܂��B
		*/
		virtual Sint32 Release( void ) = 0;

		/**
			@brief �Q�ƃJ�E���^�C���N�������g
			@author �t���`
			@return �C���N�������g��̎Q�ƃJ�E���g

			�Q�ƃJ�E���^���C���N�������g���܂��B<BR>
			�C���N�������g�����Q�ƃJ�E���g��Release()���ĂԂ��Ƃɂ��f�N�������g����܂��B<BR>
			AddRef()�������C���^�[�t�F�C�X�͕K��Release()�ŉ�����Ă��������B
		*/
		virtual Sint32 AddRef( void	) = 0;

		/**
			@brief �t�@�C���ւ̓ǂݍ���
			@author �t���`
			@param pData	[in] �ǂݍ��݃f�[�^
			@param Size		[in] �ǂݍ��݃f�[�^�T�C�Y
			@return ���ۂɏ������񂾃o�C�g��

			�t�@�C���ւ̓ǂݍ��݂��s���܂��B<BR>
			�ǂݍ��݉\�ȃt�@�C���̓C���^�[�t�F�C�X��������<BR>
			FILE_OPEN_TYPE_READ��FILE_OPEN_TYPE_READ_WRITE�t���O��<BR>
			�w�肷��K�v������܂��B
		*/
		virtual Sint32 Read( void *pData, Sint32 Size ) = 0;

		/**
			@brief �t�@�C�����擾
			@author �t���`
			@return �t�@�C�����̐擪�A�h���X

			�t�@�C�����̐擪�A�h���X���擾���܂��B
		*/
		virtual const char *GetNamePointer( void ) = 0;

		/**
			@brief �t�@�C���T�C�Y�擾
			@author �t���`
			@return �t�@�C���T�C�Y

			�t�@�C���̃T�C�Y���擾���܂��B
		*/
		virtual Sint32 GetFileSize( void ) = 0;

		/**
			@brief �t�@�C���|�C���^�[�ʒu�擾
			@author �t���`
			@return �t�@�C���|�C���^�[�̈ʒu

			���݂̃t�@�C���|�C���^�̈ʒu���擾���܂��B
		*/
		virtual Sint32 GetFilePosition( void ) = 0;

		/**
			@brief �t�@�C���V�[�N
			@author �t���`
			@param Offset	[in] �ړ���
			@return �t�@�C���|�C���^�[�̈ʒu

			�t�@�C���|�C���^�[�̈ʒu���t�@�C���̐擪����Offset�o�C�g�ړ����܂��B
		*/
		virtual Sint32 SeekStart( Sint32 Offset ) = 0;

		/**
			@brief �t�@�C���V�[�N
			@author �t���`
			@param Offset	[in] �ړ���
			@return �t�@�C���|�C���^�[�̈ʒu

			�t�@�C���|�C���^�[�̈ʒu���t�@�C���̏I�[����Offset�o�C�g�ړ����܂��B
		*/
		virtual Sint32 SeekEnd( Sint32 Offset ) = 0;

		/**
			@brief �t�@�C���V�[�N
			@author �t���`
			@param Offset	[in] �ړ���
			@return �t�@�C���|�C���^�[�̈ʒu

			�t�@�C���|�C���^�[�̈ʒu�����݂̈ʒu����Offset�o�C�g�ړ����܂��B
		*/
		virtual Sint32 Seek( Sint32 Offset ) = 0;
	};
}
}

#pragma once


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Peripheral
{
	/**
		@brief �}�E�X�Ǘ��C���^�[�t�F�C�X
		@author �t���`

		�}�E�X���������߂̃C���^�[�t�F�C�X�ł��B
	*/
	class IMouse
	{
	public:
		virtual ~IMouse() {}

		/**
			@brief �L�����`�F�b�N
			@author �t���`
			@retval true ����
			@retval false �L��

			�C���^�[�t�F�C�X���L�����������𒲂ׂ܂��B
		*/
		virtual Bool IsInvalid( void ) = 0;

		/**
			@brief �Q�ƃJ�E���^�f�N�������g
			@author �t���`
			@return �f�N�������g��̎Q�ƃJ�E���g

			�Q�ƃJ�E���^���f�N�������g���A<BR>
			�Q�ƃJ�E���g��0�ɂȂ������_�Ń��������������܂��B
		*/
		virtual Sint32 Release( void ) = 0;

		/**
			@brief �Q�ƃJ�E���^�C���N�������g
			@author �t���`
			@return �C���N�������g��̎Q�ƃJ�E���g

			�Q�ƃJ�E���^���C���N�������g���܂��B<BR>
			�C���N�������g�����Q�ƃJ�E���g��Release()���ĂԂ��Ƃɂ��f�N�������g����܂��B<BR>
			AddRef()�������C���^�[�t�F�C�X�͕K��Release()�ŉ�����Ă��������B
		*/
		virtual Sint32 AddRef( void ) = 0;

		/**
			@brief �}�E�X��X���W�擾
			@author �t���`
			@return X���W

			�}�E�X�|�C���^�[�̃X�N���[�����W���X���W���擾���܂��B
		*/
		virtual Sint32 GetPosX( void ) = 0;

		/**
			@brief �}�E�X��Y���W�擾
			@author �t���`
			@return Y���W

			�}�E�X�|�C���^�[�̃X�N���[�����W���Y���W���擾���܂��B
		*/
		virtual Sint32 GetPosY( void ) = 0;

		/**
			@brief �}�E�X�̃z�C�[����]�ʎ擾
			@author �t���`
			@return �z�C�[����]��

			�}�E�X�z�C�[���̉�]�ʂ��擾���܂��B
		*/
		virtual Sint32 GetPosW( void ) = 0;

		/**
			@brief �}�E�X��X�ړ��ʎ擾
			@author �t���`
			@return X�ړ���

			�}�E�X�|�C���^�[�̃X�N���[�����X�ړ��ʂ��擾���܂��B
		*/
		virtual Sint32 GetMoveX( void ) = 0;

		/**
			@brief �}�E�X��Y�ړ��ʎ擾
			@author �t���`
			@return Y�ړ���

			�}�E�X�|�C���^�[�̃X�N���[�����Y�ړ��ʂ��擾���܂��B
		*/
		virtual Sint32 GetMoveY( void ) = 0;

		/**
			@brief �}�E�X�̃z�C�[���ړ��ʎ擾
			@author �t���`
			@return �z�C�[���ړ���

			�}�E�X�|�C���^�[�̃z�C�[���ړ��ʂ��擾���܂��B
		*/
		virtual Sint32 GetMoveW( void ) = 0;

		/**
			@brief �}�E�X�̍��N���b�N��Ԏ擾
			@author �t���`
			@retval false	���{�^���͉�����Ă��Ȃ�
			@retval true	���{�^���͉�����Ă���

			�}�E�X�̍��{�^���̏�Ԃ��擾���܂��B<BR>
			���̊֐��ł�ON/OFF�����擾�ł��܂���B
		*/
		virtual Bool GetClickL( void ) = 0;

		/**
			@brief �}�E�X�̉E�N���b�N��Ԏ擾
			@author �t���`
			@retval false	�E�{�^���͉�����Ă��Ȃ�
			@retval true	�E�{�^���͉�����Ă���

			�}�E�X�̉E�{�^���̏�Ԃ��擾���܂��B<BR>
			���̊֐��ł�ON/OFF�����擾�ł��܂���B
		*/
		virtual Bool GetClickR( void ) = 0;

		/**
			@brief �}�E�X�̃z�C�[���N���b�N��Ԏ擾
			@author �t���`
			@retval false	�z�C�[���{�^���͉�����Ă��Ȃ�
			@retval true	�z�C�[���{�^���͉�����Ă���

			�}�E�X�̃z�C�[���{�^���̏�Ԃ��擾���܂��B<BR>
			���̊֐��ł�ON/OFF�����擾�ł��܂���B
		*/
		virtual Bool GetClickW( void ) = 0;

		/**
			@brief �}�E�X�̍��_�u���N���b�N��Ԏ擾
			@author �t���`
			@retval false	���{�^���̓_�u���N���b�N����Ă��Ȃ�
			@retval true	���{�^���̓_�u���N���b�N���ꂽ

			�}�E�X�̍��{�^�����_�u���N���b�N���ꂽ�����擾���܂��B<BR>
			���̊֐��ł�ON/OFF�����擾�ł��܂���B
		*/
		virtual Bool GetDoubleClickL( void ) = 0;

		/**
			@brief �}�E�X�̉E�_�u���N���b�N��Ԏ擾
			@author �t���`
			@retval false	�E�{�^���̓_�u���N���b�N����Ă��Ȃ�
			@retval true	�E�{�^���̓_�u���N���b�N���ꂽ

			�}�E�X�̉E�{�^�����_�u���N���b�N���ꂽ�����擾���܂��B<BR>
			���̊֐��ł�ON/OFF�����擾�ł��܂���B
		*/
		virtual Bool GetDoubleClickR( void ) = 0;

		/**
			@brief �}�E�X�̃z�C�[���_�u���N���b�N��Ԏ擾
			@author �t���`
			@retval false	�z�C�[���{�^���̓_�u���N���b�N����Ă��Ȃ�
			@retval true	�z�C�[���{�^���̓_�u���N���b�N���ꂽ

			�}�E�X�̃z�C�[���{�^�����_�u���N���b�N���ꂽ�����擾���܂��B<BR>
			���̊֐��ł�ON/OFF�����擾�ł��܂���B
		*/
		virtual Bool GetDoubleClickW( void ) = 0;

		/**
			@brief �}�E�X�̍��{�^����Ԏ擾
			@author �t���`
			@return		���{�^���̏��

			�}�E�X�̍��{�^���̏ڍׂȏ����擾���܂��B
		*/
		virtual eMouseState GetStateL( void ) = 0;

		/**
			@brief �}�E�X�̉E�{�^����Ԏ擾
			@author �t���`
			@return		�E�{�^���̏��

			�}�E�X�̉E�{�^���̏ڍׂȏ����擾���܂��B
		*/
		virtual eMouseState	GetStateR( void ) = 0;

		/**
			@brief �}�E�X�̃z�C�[���{�^����Ԏ擾
			@author �t���`
			@return		�z�C�[���{�^���̏��

			�}�E�X�̃z�C�[���{�^���̏ڍׂȏ����擾���܂��B
		*/
		virtual eMouseState	GetStateW( void ) = 0;

		/**
			@brief �}�E�X�̈ʒu��ݒ�
			@author �t���`
			@param Pos	[in] �X�N���[�����W

			�}�E�X�̈ʒu��C�ӂ̏ꏊ�ɐݒ肵�܂��B
		*/
		virtual void SetPosition( Math::Point2DI &Pos ) = 0;
	};
}
}

#pragma once


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Peripheral
{
	/**
		@brief �L�[�{�[�h�Ǘ��C���^�[�t�F�C�X
		@author �t���`

		�L�[�{�[�h���������߂̃C���^�[�t�F�C�X�ł��B
	*/
	class IKeyboard
	{
	public:
		virtual ~IKeyboard() {}

		/**
			@brief �L�����`�F�b�N
			@author �t���`
			@retval true ����
			@retval false �L��

			�C���^�[�t�F�C�X���L�����������𒲂ׂ܂��B
		*/
		virtual Bool IsInvalid( void ) = 0;

		/**
			@brief �Q�ƃJ�E���^�f�N�������g
			@author �t���`
			@return �f�N�������g��̎Q�ƃJ�E���g

			�Q�ƃJ�E���^���f�N�������g���A<BR>
			�Q�ƃJ�E���g��0�ɂȂ������_�Ń��������������܂��B
		*/
		virtual Sint32 Release( void ) = 0;

		/**
			@brief �Q�ƃJ�E���^�C���N�������g
			@author �t���`
			@return �C���N�������g��̎Q�ƃJ�E���g

			�Q�ƃJ�E���^���C���N�������g���܂��B<BR>
			�C���N�������g�����Q�ƃJ�E���g��Release()���ĂԂ��Ƃɂ��f�N�������g����܂��B<BR>
			AddRef()�������C���^�[�t�F�C�X�͕K��Release()�ŉ�����Ă��������B
		*/
		virtual Sint32 AddRef( void ) = 0;

		/**
			@brief �L�[���̓o�b�t�@�t���b�V��
			@author �t���`

			�L�[���̓o�b�t�@�ɒ~�ς������̓o�b�t�@���N���A���܂��B
		*/
		virtual void ClearKeyBuffer( void ) = 0;

		/**
			@brief �L�[���̓o�b�t�@����f�[�^�擾
			@author �t���`
			@return ���͂��ꂽ�L�[�̃L�[�R�[�h

			�L�[���̓o�b�t�@�ɒ~�ς��ꂽ�f�[�^�����o���܂��B<BR>
			�����ꂽ�L�[��S�Ď��o������while()�����ŏ������Ă��������B
		*/
		virtual eVirtualKeyCode GetKeyBuffer( void ) = 0;

		/**
			@brief �L�[��������Ă��邩�`�F�b�N����
			@author �t���`
			@retval false	������Ă��Ȃ�
			@retval true	������Ă���

			�w�肳�ꂽ�L�[�����݉�����Ă��邩�`�F�b�N���܂��B<BR>
			�����ɃL�[��ON/OFF�̂ݎ擾�ł��܂��B
		*/
		virtual Bool GetKeyData( eVirtualKeyCode Key ) = 0;
	};
}
}

#pragma once


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Peripheral
{
	/**
		@brief �W���C�X�e�B�b�N�Ǘ��C���^�[�t�F�C�X
		@author �t���`

		�W���C�X�e�B�b�N���������߂̃C���^�[�t�F�C�X�ł��B
	*/
	class IJoystick
	{
	public:
		virtual ~IJoystick() {}

		/**
			@brief �L�����`�F�b�N
			@author �t���`
			@retval true ����
			@retval false �L��

			�C���^�[�t�F�C�X���L�����������𒲂ׂ܂��B
		*/
		virtual Bool IsInvalid( void ) = 0;

		/**
			@brief �Q�ƃJ�E���^�f�N�������g
			@author �t���`
			@return �f�N�������g��̎Q�ƃJ�E���g

			�Q�ƃJ�E���^���f�N�������g���A<BR>
			�Q�ƃJ�E���g��0�ɂȂ������_�Ń��������������܂��B
		*/
		virtual Sint32 Release( void ) = 0;

		/**
			@brief �Q�ƃJ�E���^�C���N�������g
			@author �t���`
			@return �C���N�������g��̎Q�ƃJ�E���g

			�Q�ƃJ�E���^���C���N�������g���܂��B<BR>
			�C���N�������g�����Q�ƃJ�E���g��Release()���ĂԂ��Ƃɂ��f�N�������g����܂��B<BR>
			AddRef()�������C���^�[�t�F�C�X�͕K��Release()�ŉ�����Ă��������B
		*/
		virtual Sint32 AddRef( void ) = 0;

		/**
			@brief �������擾
			@author �t���`
			@param Type		[in] ���̎��
			@param Dir		[in] ���̕���
			@return ���̌��ݒl

			�w�肳�ꂽ��ށA�����̎��̏�Ԃ��擾���܂��B<BR>
			�A�i���O�X�e�B�b�N�̏ꍇ��-4096�`+4096�̒l���Ԃ�A<BR>
			�f�W�^���X�e�B�b�N�̏ꍇ��-4096��+4096�̒l���Ԃ�܂��B
		*/
		virtual Sint32 GetAxis( ePadAxisType Type, ePadAxisDirection Dir ) = 0;

		/**
			@brief �X���C�_�[�����擾
			@author �t���`
			@param Type		[in] �X���C�_�[�̃^�C�v
			@return �X���C�_�[�̌��ݒl

			�w�肳�ꂽ��ނ̃X���C�_�[�̏�Ԃ��擾���܂��B<BR>
			-4096�`+4096�̒l���Ԃ�܂��B
		*/
		virtual Sint32 GetSlider( ePadSliderType Type ) = 0;

		/**
			@brief �{�^�������擾
			@author �t���`
			@param Type		[in] �{�^���̃^�C�v
			@retval false	������ĂȂ�
			@retval true	������Ă���

			�w�肳�ꂽ��ނ̃{�^���̏�Ԃ��擾���܂��B
		*/
		virtual Bool GetButton( ePadButtonType Type ) = 0;
	};
}
}

#pragma once


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Peripheral
{
	/**
		@brief ���̓f�o�C�X�Ǘ��N���X
		@author �t���`

		�L�[�{�[�h�ƃp�b�h�𓝈ꂵ�Ĉ������߂̃C���^�[�t�F�C�X�ł��B
	*/
	class IInputController
	{
	public:
		virtual ~IInputController() {}

		/**
			@brief �L�����`�F�b�N
			@author �t���`
			@retval true ����
			@retval false �L��

			�C���^�[�t�F�C�X���L�����������𒲂ׂ܂��B
		*/
		virtual Bool IsInvalid( void ) = 0;

		/**
			@brief �Q�ƃJ�E���^�f�N�������g
			@author �t���`
			@return �f�N�������g��̎Q�ƃJ�E���g

			�Q�ƃJ�E���^���f�N�������g���A<BR>
			�Q�ƃJ�E���g��0�ɂȂ������_�Ń��������������܂��B
		*/
		virtual Sint32 Release( void ) = 0;

		/**
			@brief �Q�ƃJ�E���^�C���N�������g
			@author �t���`
			@return �C���N�������g��̎Q�ƃJ�E���g

			�Q�ƃJ�E���^���C���N�������g���܂��B<BR>
			�C���N�������g�����Q�ƃJ�E���g��Release()���ĂԂ��Ƃɂ��f�N�������g����܂��B<BR>
			AddRef()�������C���^�[�t�F�C�X�͕K��Release()�ŉ�����Ă��������B
		*/
		virtual Sint32 AddRef( void ) = 0;

		/**
			@brief ���͏��X�V
			@author �t���`

			���͏�񂩂�ŐV�̏�Ԃ֍X�V���܂��B<BR>
			�K���P�t���[���ɂP��ĂԂ悤�ɂ��ĉ������B
		*/
		virtual void Refresh( void ) = 0;

		/**
			@brief X�����͐ݒ�
			@author �t���`
			@param Type		[in] ���͊Ǘ��p�̎��^�C�v
			@param AxisX	[in] �K�p����W���C�X�e�B�b�N�̎�
			@param AxisDirX	[in] �K�p����W���C�X�e�B�b�N�̎�����

			�W���C�X�e�B�b�N�̎��f�[�^����͊Ǘ��p��X���փ}�b�s���O���܂��B
		*/
		virtual void SetAxisX( eInputAxisType Type, ePadAxisType AxisX, ePadAxisDirection AxisDirX ) = 0;

		/**
			@brief Y�����͐ݒ�
			@author �t���`
			@param Type		[in] ���͊Ǘ��p�̎��^�C�v
			@param AxisY	[in] �K�p����W���C�X�e�B�b�N�̎�
			@param AxisDirY	[in] �K�p����W���C�X�e�B�b�N�̎�����

			�W���C�X�e�B�b�N�̎��f�[�^����͊Ǘ��p��Y���փ}�b�s���O���܂��B
		*/
		virtual void SetAxisY( eInputAxisType Type, ePadAxisType AxisY, ePadAxisDirection AxisDirY ) = 0;

		/**
			@brief �{�^�����͐ݒ�
			@author �t���`
			@param Type		[in] ���͊Ǘ��p�̃{�^���^�C�v
			@param Button	[in] �K�p����W���C�X�e�B�b�N�̃{�^��

			�W���C�X�e�B�b�N�̃{�^���f�[�^����͊Ǘ��p�̃{�^���փ}�b�s���O���܂��B
		*/
		virtual void SetButton( eInputButtonType Type, ePadButtonType Button ) = 0;

		/**
			@brief �L�[�{�[�h�o�R���͐ݒ�
			@author �t���`
			@param Type		[in] ���͊Ǘ��p�̃{�^���^�C�v
			@param Key		[in] �K�p����L�[�{�[�h�̃L�[

			�L�[�{�[�h�̃L�[���W���C�X�e�B�b�N�̕ʖ��Ƃ��ē��͊Ǘ��p�̃{�^���փ}�b�s���O���܂��B
		*/
		virtual void SetAlias( eInputButtonType Type, eVirtualKeyCode Key ) = 0;

		/**
			@brief �ǂꂩ�P�ł��{�^����������Ă��邩�`�F�b�N
			@author �t���`
			@retval false	�{�^���͂P��������Ă��Ȃ�
			@retval true	�{�^���͂P�ȏ㉟����Ă���

			�Ȃ�炩�̃{�^����������Ă��邩�ǂ������`�F�b�N���܂��B
		*/
		virtual Bool IsPushAnyKey( void ) = 0;

		/**
			@brief �{�^���̏�Ԃ�������
			@author �t���`

			���ׂẴX�e�[�g��OFF��Ԃɂ��܂��B
		*/
		virtual void ClearState( void ) = 0;

		/**
			@brief �{�^���̏�Ԃ��擾
			@author �t���`
			@param PadState	[in] �擾������
			@param Type		[in] �擾����{�^��
			@retval false	�{�^���͏����𖞂����Ă��Ȃ�
			@retval true	�{�^���͏����𖞂����Ă���

			�{�^��Type�����PadState�̂Ƃ���true���Ԃ�܂��B<BR>
			�L�[���s�[�g��ݒ肵�Ă���ꍇ�́A�w��Ԋu����BUTTON_STATE_PUSH<BR>
			��ԂɎ����I�ɂȂ�܂��B
		*/
		virtual Bool GetState( eInputButtonState PadState, eInputButtonType Type ) = 0;

		/**
			@brief �{�^���̏�Ԃ�ݒ�
			@author �t���`
			@param PadState	[in] �ݒ肷����
			@param Type		[in] �ݒ肷��{�^��

			�{�^��Type�����PadState�ɐݒ肵�܂��B<BR>
			�O������L�[�𑀍삵�A�����i�s�Ȃǂ��s�킹�邱�Ƃ��\�ł��B
		*/
		virtual void SetState( eInputButtonState PadState, eInputButtonType Type ) = 0;

		/**
			@brief �J�[�\���㉺�ړ�
			@author �t���`
			@param AxisNo		[in] �g�p���鎲�ԍ�
			@param Cursor		[in,out] �J�[�\��
			@param Max			[in] �J�[�\���̂Ƃ肤��ő�l
			@retval BUTTON_DISABLE			�{�^���͉�����Ă��Ȃ�
			@retval BUTTON_DISABLE�ȊO		�{�^���͏�or����������Ă���

			�w�肵�����ɑ΂��ăJ�[�\�����㉺�ɓ������܂��B<BR>
			�܂����̎��ɃJ�[�\���̓��s�[�g����܂��B
		*/
		virtual eInputButtonType CursorRepeatUpDown( Sint32 AxisNo, Sint32 &Cursor, Sint32 Max ) = 0;

		/**
			@brief �J�[�\�����E�ړ�
			@author �t���`
			@param AxisNo		[in] �g�p���鎲�ԍ�
			@param Cursor		[in,out] �J�[�\��
			@param Max			[in] �J�[�\���̂Ƃ肤��ő�l
			@retval BUTTON_DISABLE			�{�^���͉�����Ă��Ȃ�
			@retval BUTTON_DISABLE�ȊO		�{�^���͍�or�E��������Ă���

			�w�肵�����ɑ΂��ăJ�[�\�������E�ɓ������܂��B<BR>
			�܂����̎��ɃJ�[�\���̓��s�[�g����܂��B
		*/
		virtual eInputButtonType CursorRepeatLeftRight( Sint32 AxisNo, Sint32 &Cursor, Sint32 Max ) = 0;

		/**
			@brief �J�[�\���㉺�ړ�
			@author �t���`
			@param AxisNo		[in] �g�p���鎲�ԍ�
			@param Cursor		[in,out] �J�[�\��
			@param Max			[in] �J�[�\���̂Ƃ肤��ő�l
			@retval BUTTON_DISABLE			�{�^���͉�����Ă��Ȃ�
			@retval BUTTON_DISABLE�ȊO		�{�^���͏�or����������Ă���

			�w�肵�����ɑ΂��ăJ�[�\�����㉺�ɓ������܂��B<BR>
			�܂����̎��ɃJ�[�\���̓N�����v����܂��B
		*/
		virtual eInputButtonType CursorClampUpDown( Sint32 AxisNo, Sint32 &Cursor, Sint32 Max ) = 0;

		/**
			@brief �J�[�\�����E�ړ�
			@author �t���`
			@param AxisNo		[in] �g�p���鎲�ԍ�
			@param Cursor		[in,out] �J�[�\��
			@param Max			[in] �J�[�\���̂Ƃ肤��ő�l
			@retval BUTTON_DISABLE			�{�^���͉�����Ă��Ȃ�
			@retval BUTTON_DISABLE�ȊO		�{�^���͍�or�E��������Ă���

			�w�肵�����ɑ΂��ăJ�[�\�������E�ɓ������܂��B<BR>
			�܂����̎��ɃJ�[�\���̓N�����v����܂��B
		*/
		virtual eInputButtonType CursorClampLeftRight( Sint32 AxisNo, Sint32 &Cursor, Sint32 Max ) = 0;
	};
}
}

#pragma once


/**
	@file
	@brief �T�E���h�C���^�[�t�F�C�X
	@author �t���`
*/


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Sound
{
	/**
		@brief �T�E���h�Ǘ��N���X
		@author �t���`

		@note
		�T�E���h�̏������s���N���X�ł��B<BR>
		�����kWave�݂̂̃I�����������d�Đ��ɑΉ����Ă��܂��B<BR>
		SE�̍Đ��p�r��z�肵�Ă��܂��B
	*/
	class ISound : public IInterface
	{
	public:
		virtual ~ISound() {}

/**
@brief �Đ�
@author �t���`
@param Layer	[in] ���C���[�ԍ��i-1�w��őS���C���[�ɑ΂��āj
@param IsLoop	[in] ���[�v�L���t���O

@note
�ǂݍ��񂾃T�E���h�f�[�^�̍Đ����J�n���܂��B<BR>
���[�v�̗L�����w��ł��܂��B

@code
ISound *pSnd;
// ����T�E���h�ł����Ă�Layer���Ⴄ���̂͑��d�Đ����o����B
// ���̂R��10ms���ɑ��d�Đ������B
pSnd->Play( 0, false );
Sleep( 10 );
pSnd->Play( 1, false );
Sleep( 10 );
pSnd->Play( 2, false );
@endcode
*/
		virtual void Play( Sint32 Layer, Bool IsLoop = false ) = 0;

/**
@brief ��~
@author �t���`
@param Layer	[in] ���C���[�ԍ��i-1�w��őS���C���[�ɑ΂��āj

@note
�Đ����̃T�E���h���~���܂��B

@code
ISound *pSnd;
// ����t�@�C��=�T�E���h�ł����Ă�Layer���Ⴆ�Εʂ̂��̂Ƃ��Ĉ�����
pSnd->Play( 0, false );
Sleep( 10 );
pSnd->Play( 1, false );
Sleep( 10 );
// ���̏ꍇLayer=0�̃T�E���h�͒�~���邪�ALayer=1�̃T�E���h�͍Đ����ꂽ�܂܂ɂȂ�
pSnd->Stop( 0, false );
@endcode
*/
		virtual void Stop( Sint32 Layer ) = 0;

/**
@brief �ꎞ��~/����
@author �t���`
@param Layer	[in] ���C���[�ԍ��i-1�w��őS���C���[�ɑ΂��āj

@note
�Đ����̃T�E���h���ꎞ��~�A<BR>
�ꎞ��~���̃T�E���h���Đ����܂��B

@code
ISound *pSnd;
// ����t�@�C��=�T�E���h�ł����Ă�Layer���Ⴆ�Εʂ̂��̂Ƃ��Ĉ�����
pSnd->Play( 0, false );
Sleep( 10 );
pSnd->Play( 1, false );
Sleep( 10 );
// ���̏ꍇLayer=0�̃T�E���h�͈ꎞ��~���邪�ALayer=1�̃T�E���h�͍Đ����ꂽ�܂܂ɂȂ�
pSnd->Pause( 0, false );
@endcode
*/
		virtual void Pause( Sint32 Layer ) = 0;

/**
@brief �{�����[���ύX
@author �t���`
@param Layer	[in] ���C���[�ԍ��i-1�w��őS���C���[�ɑ΂��āj
@param fVolume	[in] �{�����[���i0�`100%�j

@note
�{�����[���̕ύX���s���܂��B

@code
ISound *pSnd;
// ����t�@�C��=�T�E���h�ł����Ă�Layer���Ⴆ�Εʂ̂��̂Ƃ��Ĉ�����
pSnd->Play( 0, false );
Sleep( 10 );
pSnd->Play( 1, false );
Sleep( 10 );
// ���̏ꍇLayer=0�̃T�E���h�͉��ʂ������ɂȂ邪�ALayer=1�̃T�E���h�͂��̂܂܂ɂȂ�
pSnd->SetVolume( 0, 50.0f );
@endcode
*/
		virtual void SetVolume( Sint32 Layer, Float fVolume ) = 0;

/**
@brief �p���ړ�
@author �t���`
@param Layer	[in] ���C���[�ԍ��i-1�w��őS���C���[�ɑ΂��āj
@param fPan	[in] �p���i��:-100�`�E:+100�j

@note
�p���̈ړ����s���܂��B

@code
ISound *pSnd;
// ����t�@�C��=�T�E���h�ł����Ă�Layer���Ⴆ�Εʂ̂��̂Ƃ��Ĉ�����
pSnd->Play( 0, false );
Sleep( 10 );
pSnd->Play( 1, false );
Sleep( 10 );
// ���̏ꍇLayer=0�̃T�E���h�͍�����̂ݖ邪�ALayer=1�̃T�E���h�͂��̂܂܂ɂȂ�
pSnd->SetPan( 0, -100.0f );
@endcode
*/
		virtual void SetPan( Sint32 Layer, Float fPan ) = 0;

/**
@brief �Đ��`�F�b�N
@author �t���`
@param Layer	[in] ���C���[�ԍ�
@retval false	�Đ����Ă��Ȃ�
@retval true	�Đ����Ă���

@note
���ݍĐ����̃T�E���h���ǂ������ׂ܂��B

@code
ISound *pSnd;
// �T�E���h��Layer=1���Đ��������ׂ�
if ( pSnd->IsPlay( 1 ) )
{
	// �Đ���
}
@endcode
*/
		virtual Bool IsPlay( Sint32 Layer ) = 0;
	};
}
}
#pragma once


/**
	@file
	@brief �X�g���[���T�E���h�C���^�[�t�F�C�X
	@author �t���`
*/


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Sound
{
	static const Float PLAY_TIME_AUTO = -1.0f;

	/**
		@brief �X�g���[���T�E���h�Đ��p�����[�^�[
		@author �t���`

		@note
		�X�g���[���T�E���h�̍Đ����s�����߂̃e�[�u���f�[�^�ł��B
	*/
	struct SPlayBlock
	{
		Sint32 LoopCount;		// ���̃e�[�u���̃��[�v���i-1�Ŗ������[�v�j
		Float fStartTime;		// �Đ��J�n�ʒu�i�b�w��j�iPLAY_TIME_AUTO�w��ōŏ�����j
		Float fEndTime;			// �Đ��I���ʒu�i�b�w��j�iPLAY_TIME_AUTO�w��ōŌ�܂Łj
	};

	/**
		@brief �X�g���[���T�E���h�Ǘ��N���X
		@author �t���`

		@note
		�X�g���[���T�E���h�̏������s���N���X�ł��B<BR>
		�����kWave/���kWave/OggVorbis�̍Đ��ɑΉ����Ă��܂��B<BR>
		BGM�≹���̍Đ��p�r��z�肵�Ă��܂��B
	*/
	class IStreamSound : public IInterface
	{
	public:
		virtual ~IStreamSound() {}

/**
@brief �Đ�
@author �t���`
@param pTbl			[in] �Đ��e�[�u��
@param Count		[in] �Đ��e�[�u����
@retval false		�����Ɏ��s
@retval true		�����ɐ���

@note
�ǂݍ��񂾃T�E���h�f�[�^�̍Đ����J�n���܂��B<BR>
�Đ��e�[�u���̒�`�ɂ����čĐ�����Ă����܂��B

@code
IStreamSound *pSnd;
// �Đ��e�[�u��
Sound::SPlayBlock Tbl[] = {
  {
    3,				// 3��
    0.0f,			// 0.0�b����
    5.0f,			// 5.0�b�܂�
  },
};
pSnd->Play( Tbl, sizeof(Tbl) / sizeof(Sound::SPlayBlock) );
@endcode
*/
		virtual Bool Play( SPlayBlock *pTbl, Sint32 Count ) = 0;

/**
@brief �Đ�
@author �t���`
@param LoopCount	[in] ���[�v��(-1�Ŗ���)
@retval false		�����Ɏ��s
@retval true		�����ɐ���

@note
�ǂݍ��񂾃T�E���h�f�[�^�̍Đ����J�n���܂��B

@code
IStreamSound *pSnd;
// ���ʂ�1��Đ�
pSnd->Play();
@endcode
*/
		virtual Bool Play( Sint32 LoopCount = 0 ) = 0;

/**
@brief ��~
@author �t���`

@retval false		�����Ɏ��s
@retval true		�����ɐ���

@note
�Đ����̃T�E���h���~���܂��B

@code
IStreamSound *pSnd;
// �Đ���~
pSnd->Stop();
@endcode
*/
		virtual Bool Stop( void ) = 0;

/**
@brief �ꎞ��~/����
@author �t���`

@retval false		�����Ɏ��s
@retval true		�����ɐ���

@note
�Đ����̃T�E���h���ꎞ��~�A<BR>
�ꎞ��~���̃T�E���h���Đ����܂��B

@code
IStreamSound *pSnd;
// �ꎞ��~
pSnd->Pause();
@endcode
*/
		virtual Bool Pause( void ) = 0;

/**
@brief �{�����[���ύX
@author �t���`
@param fVolume	[in] �{�����[���i0�`100�j
@retval false		�����Ɏ��s
@retval true		�����ɐ���

@note
�{�����[���̕ύX���s���܂��B

@code
IStreamSound *pSnd;
// �{�����[���ő��
pSnd->SetVolume( 100.0f );
@endcode
*/
		virtual Bool SetVolume( Float fVolume ) = 0;

/**
@brief �p���ړ�
@author �t���`
@param fPan	[in] �p���i-100�`+100�j
@retval false		�����Ɏ��s
@retval true		�����ɐ���

@note
�p���̈ړ����s���܂��B

@code
IStreamSound *pSnd;
// �E���炾������炷
pSnd->SetPan( +100.0f );
@endcode
*/
		virtual Bool SetPan( Float fPan ) = 0;

/**
@brief �Đ��`�F�b�N
@author �t���`
@retval false	�Đ����Ă��Ȃ�
@retval true	�Đ����Ă���

@note
���ݍĐ����̃T�E���h���ǂ������ׂ܂��B

@code
IStreamSound *pSnd;
// �Đ��������ׂ�
if ( !pSnd->IsPlay() )
{
	// �Đ��I��
}
@endcode
*/
		virtual Bool IsPlay( void ) = 0;
	};
}
}

