#pragma once
#include "Base/Define.h"
#include "Objects/Object.h"
#include "Manager/FrameManager.h"
#include "Manager/CollisionManager.h"
#include <map>
#include <vector>

namespace TiGLiCS{
	/**
		@brief ページクラス
		@author my04337
		@note
		ページクラス。各オブジェクトは一つのページクラスに関連づけられる。<br>
		ページ単位でフレームマネージャ、コリジョンマネージャ、ログ出力を持つ。
	*/
	class  CPage{
		Sint32 PageID;//ページID

		Selene::CColor BackColor;//背景色

		Object::ProcessPriorityList ProcessQueue;	//処理順のリスト
		Object::PtrPriorityList PtrQueue;	//ポインタ順のリスト
		std::vector<Object::IObject *> DeleteQueue;//削除のキュー
		std::vector<Object::IObject *> AddQueue;//追加のキュ
		
		Manager::CFrameManager * pFrameManager;//フレームマネージャ
		Manager::CCollisionManager2D * pCollisionManager2D;//2Dコリジョンマネージャ

		void delObject();//実際の削除処理
		void addObject();//実際の追加処理

		//デバッグ用変数
	#ifdef TIGLICS_DEBUG
		LARGE_INTEGER   nFreq,t1,t2,t3,t4,t5,t6,t7;
		Sint32 DataArr[32];//デバッグ用
		
		char log_str[MAX_TASK_LOG_ROW][MAX_TASK_LOG_SIZE];
		char log2_str[MAX_TASK_LOG_ROW][MAX_TASK_LOG_SIZE];
		Sint32 NowLogRow;//どのログがもっとも新しいか

	#endif

	public:
		CPage(Sint32 PageID){
			this->PageID=PageID;
			//当たり判定リストの初期化
			pCollisionManager2D=new Manager::CCollisionManager2D(this);
			pFrameManager=NULL;

	#ifdef TIGLICS_DEBUG
			//ログの初期化
			this->NowLogRow=0;
			for(Sint32 i=0;i<MAX_TASK_LOG_ROW;++i){
				log_str[i][0]='\0';
				log2_str[i][0]='\0';
			}
	#endif
		}
		~CPage(){Release();}
		///ページIDを取得
		Sint32 GetPageID()const{return PageID;}

		void Exec(void);//処理実行

		//オブジェクト関連
		void AddObject(Object::IObject *);//オブジェクト追加
		void DeleteObject(Object::IObject *);//オブジェクトを削除キューに登録
		///オブジェクト数の取得
		inline Sint32 GetObjectNum(void){return (Sint32)PtrQueue.size();}//オブジェクト数を返す
		///削除キュー内のオブジェクト数を返す
		inline Sint32 GetDeleteQueueNum(void){return (Sint32)DeleteQueue.size();}//削除オブジェクト数を返す
		///追加キュー内のオブジェクト数を返す
		inline Sint32 GetAddQueueNum(void){return (Sint32)AddQueue.size();}//追加オブジェクト数を返す	

		/**
			@brief 背景色の設定
			@author my04337
			@param col [in] 背景色

			背景色を設定する。ただし、シーンマネージャが登録されている場合は<br>
			事実上無効となる。
		*/
		void SetBackColor(Selene::CColor &col){BackColor=col;}	
		
		/**
			@brief フレームマネージャの取得
			@author my04337
			@retval 設定時 フレームマネージャへの
			@retval 未設定 NULL

			フレームマネージャへのポインタを取得する。設定されていない場合、NULLが帰る。
		*/
		inline Manager::CFrameManager * GetCFrameManager(){return pFrameManager;}
		
		/**
			@brief フレームマネージャの設定
			@author my04337
			@param pFrameManager [in] フレームマネージャへのポインタ
			
			フレームマネージャを設定する。別なマネージャに差し替えるときは<br>
			一度GetFrameManagerを使い解放を行った後に登録する必要がある。
		*/
		inline void SetFrameManager(Manager::CFrameManager * pFrameManager){this->pFrameManager=pFrameManager;}
		
		//当たり判定マネージャの取得
		inline Manager::CCollisionManager2D* GetCCollisionManager2D(){return pCollisionManager2D;}

		/**
			@brief ログ出力
			@author my04337
			
			画面左下にログを出力する。形式はprintfと同じ。<br>
			複数行に対応している。また、ログは一定数保持され、その後は消去される。<br>
			ただし、ログ無し版のLIBを使用した場合、ログは表示されない。
		*/
		void LogPrint(const char *src,...);//ログ出力

		void Log2Print(Sint32 LineNum,const char *src,...);//ログ出力

		void Release();//解放処理
	};

	typedef std::map<Sint32,CPage *> tPageList;
		
	namespace Manager{
		/**
			@brief ページマネージャ
			@author my04337

			ページ管理を行う。各ページはこれに関連づけられる。<br>
			また、ページの切り替えもここで行われる
		*/
		class  CPageManager{//ページ管理。シングルトン
			tPageList PageList;//ページリスト
			Sint32 NowPageID;//現在のページID
			Sint32 NextPageID;//次回のページID
			bool bNowPageDelete;
			static CPageManager * Instance;
			CPageManager(){}
			~CPageManager(){}
		public:
			static CPageManager* GetInstance(){return Instance;}//インスタンス取得
			static void Release();//終了処理
			/**
				@brief ページ生成
				@author my04337
				@param PageID [in] ページID
				@retval 成功時 ページクラスへのポインタ
				@retval 失敗時 NULL

				ページを生成し、そのポインタを返す<br>
				ページIDは他のページとかぶらない値にする必要がある。<br>
				生成に失敗するとNULLが返される。
			*/
			CPage* CreatePage(Sint32 PageID);

			/**
				@brief ページ削除
				@author my04337
				@param PageID [in] ページID
				@retval 成功時 true
				@retval 失敗時 false

				ページの削除を行う。<br>
				このとき、削除対象が次回実行予定のページの場合、削除が失敗する。
			*/
			bool DeletePage(Sint32 PageID);//ページの削除

			/**
				@brief ページ取得
				@author my04337
				@param PageID [in] ページID
				@retval 成功時 ページクラスへのポインタ
				@retval 失敗時 NULL

				ページIDからページクラスへのポインタを取得する。<br>
				存在しないIDに対して取得しようとした場合、NULLが返される。
			*/
			CPage* GetPage(Sint32 PageID);//ページの取得

			/**
				@brief 現在のページID取得
				@author my04337
				@return 現在のページID

				現在実行中のページIDを取得する。
			*/
			CPage* GetNowPage();//現在のページ取得
			/**
				@brief ページ数取得
				@author my04337
				@return ページ数

				ページマネージャに登録されている総ページ数を返す。
			*/
			Sint32 GetPageNum(){return PageList.size();}//ページ数取得

			/**
				@brief 次回実行のページ設定
				@author my04337
				@param PageID [in] ページID
				@param isNowPageDelete [in] 現在のページを削除するか
				@retval 成功時 true
				@retval 失敗時 false

				次回実行のページ番号を設定する。<br>
				このとき、現在実行中のページを削除するかを設定できる。<br>
				無効なページに切り替えようとした場合、失敗する。

			*/
			bool SetNextPage(Sint32 PageID,bool isNowPageDelete=false);//次に実行するページIDの設定

			void Exec();//ページの実行

		};
	};
};