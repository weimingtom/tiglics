#pragma once
#include "Base/Base.h"
using namespace Selene;
namespace TiGLiCS{
	namespace Manager{
		/**
			@brief フレームマネージャ
			@author my04337

			フレームマネージャ。各ページに一つずつ配置可能<br>
			タスクの先頭、末尾で行いたい処理などを記述する<br>
			ユーザーはこれを継承して使用する。
		*/
		class  CFrameManager:public IFrameManager{
		public:
			
			///所属ページクラス
			CPage * pPage;

			/**
				@brief コンストラクタ
				@author my04337
				@param pPage [in] 所属するページクラス
			*/
			CFrameManager(CPage * pPage){this->pPage=pPage;}

			///デストラクタ
			virtual ~CFrameManager(){};

			/**
				@brief タスク先頭で行う処理
				@author my04337

				すべてのオブジェクトの処理前に実行する関数
			*/
			virtual void BeforeProcess(void)=0;

			/**
				@brief シーンマネージャリセット時に呼び出される関数
				@author my04337

				シーンマネージャが関連づけられている場合、Reset()が呼ばれた後<br>
				この館数が呼び出される。
			*/
			virtual void OnSceneManagerReset(void)=0;

			/**
				@brief タスク末尾で行う処理
				@author my04337

				すべてのオブジェクトの処理後に実行する関数
			*/
			virtual void AfterProcess(void)=0;
		};
	};
};