#pragma once
#include "Base/Base.h"
#include "Base/Configure.h"
#include "Manager/SoundManager.h"
#include "Manager/RenderManager.h"
#include "Manager/PageManager.h"
#include <ctime>
#include <vector>
#include <mmsystem.h> // winmm.lib をリンクするのを忘れずに

namespace TiGLiCS{
	/**
		@brief タスクシステム
		@author my04337

		すべての中心となるクラス。各マネージャ類へのアクセスは<br>
		ほぼここから可能である。
	*/
	class  CEngine{	//シングルトンクラス
		Selene::ICore						*pCore;			//コア
		Selene::IGraphicCard				*pGraphicCard;	//グラフィックカード情報
		Selene::Renderer::IRender			*pRender;		//レンダー
		Selene::File::IFileManager			*pFileMgr;		//ファイルマネージャ
		Selene::Peripheral::IMouse			*pMouse;		//マウスデバイス
		Selene::Peripheral::IKeyboard		*pKeyboard;		//キーボードデバイス
		Selene::Renderer::CTextureConfig	Conf;			//テクスチャコンフィグ
		


		Selene::Math::Point2DI ScreenSize;//スクリーンサイズ
		Sint32 FrameRate;

		//デバッグ用変数

		void Exec(void);//処理実行
		void _Release(void);//解放処理
		///コンストラクタ。シングルトン用にプライベート
		CEngine(){	
			//まずはNULLで初期化
			pCore=NULL;
			pGraphicCard=NULL;
			pRender=NULL;
			pMouse=NULL;
			pKeyboard=NULL;
		}
		//デストラクタ
		~CEngine(){
		}

		static CEngine * Instance;//自分自身のインスタンス(シングルトン用)
	public:
		static CEngine * GetInstance(){
			return Instance;
		}
		static void Release(){
			Instance->_Release();
			delete Instance;
		}
		/*
			@brief 初期化関数
			@author my04337
			@param Title [in] タイトル
			@param FrameRate [in] フレームレート指定
			@param isDrawDebugTitle [in] デバッグ用タイトルを表示するか
			@param ScreenWidth [in] スクリーン幅
			@param ScreenHeight [in] スクリーン高さ
			@param isFullScreen [in] フルスクリーンにするか
			@param RootPath [in] ルートディレクトリのアドレス
			@param CurrentPath [in] カレントディレクトリのアドレス
			@param isBenchMode [in] ベンチマークモードにするか
			@return 初期化に成功したか


		*/
		bool Init(const char * Title,Selene::eFrameRate FrameRate,bool isDrawDebugTitle,
					 Sint32 ScreenWidth,Sint32 ScreenHeight,bool isFullScreen,const char * RootPath,
					 const char * CurrentPath,bool isBenchMode=false);
		/**
			@brief 実行関数
			@author my04337
			@retval true タスクが終了していない
			@retval false タスクが終了した

			この関数をループさせることで、毎フレーム各処理を行わせる。<br>
			実行の際には、以下のように記述する<br>
			@code
			...
			WinMain(){
				...//初期化等
				while(pEngine->Run()){}
				...//終了処理

				return ...;
			}
			@endcode
		*/
		inline Bool Run(){
			Exec();
			return pCore->Run();
		}

		
		//スクリーンサイズとフレームレート
		Selene::Math::Point2DI GetScreenSize(){return ScreenSize;}
		Sint32 GetFrameRate(){return FrameRate;}

		inline void End(){pCore->Exit();}//終了させる。
		
		///TiGLICSのバージョン取得
		inline const char* GetVerStr(){return TIGLICS_VERSION;}

		//各種オブジェクトへのポインタの取得
		///Selene::ICoreを取得
		inline Selene::ICore* GetICore(){return pCore;}
		///Selene::IGraphicを取得
		inline Selene::IGraphicCard* GetIGraphicCard(){return pGraphicCard;}
		///Selene::IRenderを取得
		inline Selene::Renderer::IRender* GetIRender(){return pRender;}
		///テクスチャ設定を取得
		inline Selene::Renderer::CTextureConfig *GetCTextureConfig(){return &Conf;}
		///Selene::File::IFileManagerを取得
		inline Selene::File::IFileManager* GetIFileManager(){return pFileMgr;}
		///Selene::Peripheral::IMouseを取得
		inline Selene::Peripheral::IMouse* GetIMouse(){return pMouse;}
		///Selene::Peripheral::IKeyboardを取得
		inline Selene::Peripheral::IKeyboard* GetIKeyboard(){return pKeyboard;}
		
	};

};