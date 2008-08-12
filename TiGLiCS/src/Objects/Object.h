#pragma once

#include "Objects/Fiber.h"
#include <typeinfo>
//class CEngine;//循環参照回避
//基本オブジェクト
//受け取ったテクスチャ、レンダラは解放しない
namespace TiGLiCS{
	namespace Object{
		/**
			@brief オブジェクトクラス
			@author my04337

			タスクに組み込むためのクラス。ユーザはこのクラスを継承して使用する。
		*/
		class  CObject:public IObject,private CFiber{
			Sint32 ProcessPriority;
			CObjectContainer *pObjectContainer;
			Sint32 WaitNum;//待機フレーム数
			bool bDead;//死亡したかどうか
		public:
			///自分の所属するページへのポインタ
			CPage *pPage;
			/**
				@brief コンストラクタ
				@author my04337
				@param pPage [in] 所属させるページへのポインタ
				@param ProcessPriority [in] 処理優先度
			*/
			CObject(CPage *pPage,Sint32 ProcessPriority);

			/**
				@brief デストラクタ
				@author my04337
				
				デストラクタ。基本的に使用すべきではない。
			*/
			virtual ~CObject(){}//デストラクタ

			/**
				@brief 処理優先度取得
				@author my04337
				@return 処理優先度

				処理優先度を取得する。
			*/
			inline Sint32 GetProcessPriority(void){return ProcessPriority;}
			
			//必須関数
			/**
				@brief 初期化関数
				@author my04337

				オブジェクトがタスクに組み込まれた直後に実行される。<br>
				タスクやページが関係する初期化文はここに書くとよい。
			*/
			virtual void Init(void)=0;
			/**
				@brief 処理関数
				@author my04337

				オブジェクトの移動などの処理を記述する。<br>
				この館数が終了すると自動的にオブジェクトは削除キューに入る。<br>
				この関数内でのみ、Update(),Wait()関数を呼び出すことができる。<br>
				また、この関数内でも描画を行うことはできる。<br>
				記述の際には、無限ループなどを作っておき、それをUpdateにて中断する<br>
				なお、この関数のみスタックは独自に確保した領域を使うため、<br>
				スタックオーバーフローに注意する必要がある。<br>
				<br>
				以下のコードではProcessが10回呼ばれるとオブジェクトが削除される。
				@code
				class CTestObject:public IObject{
					...
					Process(){
						for(int i=0;i<10;++i){
							...//いろいろな処理（移動処理、キー入力判定など)
							Update();
						}
					}
					...
				}
				@endcode				
			*/
			virtual void Process(void)=0;//処理
			/**
				@brief　描画関数
				@author my04337

				ここには主に描画処理など毎フレーム確実に実行したい処理を記述する。<br>
				なお、毎フレーム必ず呼ばれることを利用して移動処理も書くこともできるが、<br>
				それよりははOnUpdate関数に記述する方式を推奨する。
			*/
			virtual void Draw(void)=0;//描画
			/**
				@brief 解放関数
				@author my04337

				この関数は、オブジェクトがタスクから外される直前に呼ばれる。<br>
				解放処理などはここに書くことを推奨する。<br>
				※デストラクタにて解放処理を行うことは推奨しません。
			*/
			virtual void Release(void)=0;//オブジェクトがタスクから外される直前に呼ばれる
			//任意関数
			/**
				@brief レンダラ描画前
				@author my04337

				この関数はレンダラが描画を始める前に呼ばれる。<br>
				3Dで描画などを行うとき、シーンマネージャの設定などを行いたいときは<br>
				ここを利用するとよい。なお、この中では描画は不可能である。
			*/
			virtual void BeforeRenderBegin(void){};//Beginする前
			/**
				@brief オブジェクト死亡時
				@author my04337

				この関数はオブジェクトが死亡し、削除キューに入った直後に呼ばれる。<br>
				オブジェクトに対しDie()関数を呼び出すと、削除対象のオブジェクトでこの関数が呼ばれる。<br>
				死亡直後に処理を行いたいときにここに書けばよい。
			*/
			virtual void OnDie(void){}//オブジェクト死亡時
			/**
				@brief オブジェクトアップデート時
				@author my04337

				この関数はオブジェクトがUpdate関数を呼び出したときに呼び出される。<br>
				移動処理など、毎フレーム実行したい処理などはここに書くとよい。
			*/
			virtual void OnUpdate(void){}//Updateが呼ばれたとき


			//その他関数
			/**
				@brief アップデート
				@author my04337

				Process内にて、実行を中断し1フレーム待機する関数である。<br>
				この関数を呼び出した後、Draw関数が実行され、次のオブジェクトの実行が行われる。<br>
				絶対にこの関数をProess関数外で使用してはいけない。<br>
				なお、再開時はこの関数の直後から再開される。

			*/
			virtual void Update();//アップデート処理
			///オブジェクトの死亡判定
			bool isDead(){return bDead;}
			/**
				@brief オブジェクトを死亡させる
				@author my04337

				この関数を呼び出すことで、オブジェクトは削除キューに入れられる。<br>
				その後、OnDie関数が呼ばれる。<br>
				ただし、この関数が呼ばれた時点ではオブジェクトの削除は行われず、<br>
				自分自身のDie関数を呼び出した場合でも処理が続行される。
			*/
			void Die();//死亡させる
			bool _RunProcess();//プロセス実行。
			void _SuspendProcess(){Suspend();}
			int GetRestProcessStack(){return GetStackRest();}
			/**
				@brief 指定回数アップデート
				@author my04337
				@param FrameNum [in] 待機フレーム
				この関数では、FrameNumで指定したフレーム数Update()を呼び出す。<br>
				Update関数はUpdate(1)とほぼ等価である。<br>
				なお、この関数はオーバーライトを推奨しない(する場合はUpdate()をオーバーライトすればよい)。
			*/
			void Update(Sint32 FrameNum);//指定フレーム数待機
			inline CObjectContainer *GetCObjectContainer(){return pObjectContainer;}
			inline void SetCObjectContainer(CObjectContainer *pObjectContainer){this->pObjectContainer=pObjectContainer;}

			//あると便利な関数
			/**
				@brief 画面内外判定
				@author my04337
				@param pos [in] オブジェクト座標
				@retval true 画面外
				@retval false 画面内

				指定された座標が画面外にいるかを判定する。
			*/
			Bool isScreenOut(Selene::Math::Point2DF &pos);
			/**
				@brief キー状態取得
				@author my04337
				@param KeyCode [in] キーコード
				@retval おされていない場合 0
				@retval おされている場合 おされたフレーム数

				キーがおされたかどうかを判定する。CEngine::GetKey()と等価
			*/
			Sint32 GetKey(Selene::eVirtualKeyCode KeyCode);
			/*
				@brief オブジェクト追加
				@author my04337
				@param pObject [in] 追加するオブジェクトのポインタ
				
				現在のページにオブジェクトを追加する。<br>
				追加したオブジェクトは次のフレームから実行される。
			*/
			void AddObject(IObject *pOboect);

			/**
				@brief スクリーンサイズ取得
				@author my04337
				@return スクリーンサイズ

				スクリーンのサイズを取得。CEngine::GetScreenSize()と等価
			*/
			Selene::Math::Point2DI GetScreenSize(); 

			/**
				@brief フレームレート取得
				@author my04337
				@return フレームレート

				設定されたフレームレートを取得。CEngine::GetFrameRate()と等価
			*/
			Sint32 GetFrameRate(); 

			/**
				@brief タスクの終了
				@author my04337
				
				タスクの実行を終了する。CEngine::End()と等価である
			*/
			void End();
		};

		//-----------------------------------------------------------------------------------------------------
		class  CObjectContainer {//削除高速化対策
			void Process();
		public:
			bool isDead;//削除済みかどうか
			IObject * pObj;//IObjectへのポインタ
			CObjectContainer(IObject *pObj){
				//コンストラクタ
				isDead=false;
				this->pObj= pObj;//IObjectへのポインタ
			}
			~CObjectContainer(){}
		};
	};
};