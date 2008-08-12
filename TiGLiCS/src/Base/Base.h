/**
	@brief 基本ヘッダファイル

	各種pragmaとネームスペース、列挙体の定義
*/

#pragma once

#pragma warning(disable:4800)///ブール値を 'true' または 'false' に強制的に設定します
#pragma warning(disable:4611)///L4:setjmpと C++ オブジェクト デストラクション間での相互作用には互換性がありません。
#pragma warning(disable:4731)///L4:インライン アセンブラ コードにより変更されたフレーム ポインタ レジスタ 'register' です。
#pragma warning(disable:4733)///L1:インライン asm は 'FS:0' に割り当てています : ハンドラは安全なハンドラとして登録されていません。
#pragma warning(disable:4251)///'identifier' : class 'type' は __export キーワードを使って class 'type2' にエクスポートしてください。(クラス用)
#pragma warning(disable:4505)///参照されていないローカル関数は削除されました。

#define WIN32_LEAN_AND_MEAN             // Windows ヘッダーから使用されていない部分を除外します。
#include "Selene.h"
/**
	@brief ライブラリ名前空間
*/
namespace TiGLiCS{

	 float drand(void);//実数乱数を返す
	 float drand(float min,float max);///実数乱数範囲指定型
	 void DMessageBox(const char *src,...);//デバッグ用メッセージボックス

	class CEngine;
	class CPage;

	/**
		@brief 衝突系
		@author my04337
	*/
	namespace Collision2D{
			
		/**
			@brief 衝突タイプ[内部用]
			@author my04337

			コリジョンマネージャにて使用。内部用
		*/
		enum eCollisionType{
			coPoint2D,			///点
			coCircle2D,			///円
			coLine2D,			///線
			coPolygon2D,		///多角形
			coDummy,			///ダミー
		};
		class CCollisionData2D;			///基底クラス
		class CPoint2DCollisionData;	///点
		class CLine2DCollisionData;		///線
		class CCircle2DCollisionData;	///円
		class CPolygon2DCollisionData;	///多角形
		class CCollisionResult2D;		///戻り値型

	}
	/**
		@brief 管理系
		@author my04337
	*/
	namespace Manager{
		/**
			@brief 描画タイプ[内部用]
			@author my04337
			@note
			描画マネージャにて使用。内部用<br>
			同一優先度の描画オブジェクトがある場合、この順で処理される<br>

		*/
		enum eRequestDrawType{
			drSprite2D,			///スプライト
			drPoint2D,			///点
			drLine2D,			///線
			drPrimitive2D,		///プリミティブ
			drFontSprite2D,		///フォントスプライト
			drScene,			///3Dシーン
			drDummy,			///ダミー　デバッグ用
		};
		class CCollisionManager2D;	///衝突管理
		class CFontManager;		///フォント全体管理
		class CFont;			///フォント単体管理
		class CPageManager;			///ページ管理
		class CFramemanager;		///フレーム管理
		class CRenderManager;		///描画管理
		class CSoundManager;	///SE全体管理
		class CSound;		///SE単体管理
		class CTexture;		///テクスチャ管理
	}
	/**
		@brief オブジェクト系
		@author my04337
	*/
	namespace Object{
		class CObject;			//基本オブジェクト
		class IObject;
		class CFiber;			//ファイバ
		class IFiber;
		class CFiberBase;		//ファイバ管理
		class CObjectContainer;	//オブジェクトコンテナ
		class CSprite2D;		//2Dオブジェクト
	}

}

#include "Interface/Interface.h"