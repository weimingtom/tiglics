//自作ファイバクラス 
//作成者:tomoteru
//作成日:20080325
//用途：ゲーム等で処理を一時中断したいときなど。
#pragma once
#include "Base/Base.h"
#include "Base/Configure.h"
#include <cstdio>
#include <list>
#include <cstdlib>
#include <setjmp.h>

namespace TiGLiCS{
	namespace Object{
		class  CFiberMemoryManager{//スタック用メモリ管理
			static std::list<int*> Stack_List;//確保したスタック用メモリリスト
		public:
			static int* GetStackMem();//スタック用メモリ確保
			static void RetStackMem(int* ptr);//スタック用メモリ返却
			static void ClearStackMem();//スタック用メモリ全返却
			static void GCStackMem(int max,int rest=1000);//メモリ
			static int GetStackMemNum();//確保メモリの数
		};

		/**
			@brief ファイバークラス
			@author my04337

			ファイバーを実装するためのクラス。IObjectが継承している。<br>
			このクラスを継承することで、自作のファイバクラスが作成可能である。<br>
			なお、CFiber::Processは独自のスタック領域(ヒープ)で動作する。<br>
			なお、継承の際にはprivateにて継承することで外部から不用意にProcessやSuspendが<br>
			呼ばれることを防ぐことができる。
		*/
		class  CFiber:IFiber{//ファイバクラス。基底クラスとする
			CFiberBase * cfbase;//実際にスイッチングなどを行うクラス
		public:
			CFiber();
			virtual ~CFiber();
			/**
				@brief 中断可能関数
				@author my04337
				
				中断可能な関数である。この関数内でSuspend()を呼び出すと、<br>
				自動変数などを保存した状態で中断することができる。<br>
				再開時Suspend()が呼び出された直後から実行される。<br>
				ユーザーはこの関数をオーバーライトして使用する。<br>
				また、関数が終了後に呼び出すと呼び出しが失敗する。				
			*/
			virtual void Process()=0;//実際の処理。
			/**
				@brief Processの中断
				@author my04337

				Process内で呼び出すことでProcessの実行を中断することができる。<br>
				ただし、Process外で呼び出すとメモリが破壊されるために、呼び出し元は<br>
				Processのみにする必要がある。
			*/
			void Suspend();//中断。Process内で呼び出す
			/**
				@実行関数
				@author my04337
				@retval true 関数が中断されている場合
				@retval false 関数が終了したか、すでに終了している場合

				外部からProcess関数を呼び出す場合、この関数を呼び出すようにする。<br>
				実行が終了したかどうかは戻り値から確認することができる。
			*/
			bool Run();//使用者が呼び出す
			/**
				@brief 残りスタックサイズ確認
				@author my04337
				@return 残りスタックサイズ

				Process関数の残りスタックサイズを取得する。ただし、この値は<br>
				Suspend()が呼ばれた際に更新されるため、目安として考えるべきである。
			*/
			int GetStackRest();//スタックの残りを返す	
			/**
				@brief ファイバ終了確認
				@author my04337
				@retval true Process()の実行が終わっている場合
				@retval false Process()が中断されている場合

				ファイバの実行が終了したかを取得する。
			*/
			bool isFiberEnd();//ファイバが終了したかどうか
		};

		class  CFiberBase{//スタック管理、切り替え
			int func_sp;//呼び出し側のSp [this+4]
			int * stack_mem;//仮想スタック[this+8]
			jmp_buf ret_jb;//戻り側
			jmp_buf func_jb;//関数側
			bool isEnd;//終了したかどうか
			bool isStart;//開始されたかどうか
			int	StackMemRest;//残りスタックサイズ(中断時更新)
			CFiber* cfiber;//ファイバへのアドレス
			void SwitchStack();//スタック切り替え
			void SwitchStack(int return_pc);//スタック切り替え
			static void start_() {//呼び出し用ジャンプ台
				int fib;
				__asm{//ebp+4には、呼び出し側のthisが入っているので
					mov eax,[ebp+4];
					mov fib,eax;
				}
				((CFiberBase*)fib)->cfiber->Process();//処理実行
				((CFiberBase*)fib)->isEnd = true; // ファイバの実行が終了した
				((CFiberBase*)fib)->SwitchStack(0);//もう戻ることはないので
				//	もう↓が実行されることは無い
			}
			static void end_(){//終了用のジャンプ台
				int fib;
				__asm{
					mov eax,[ebp+4];
					mov fib,eax;
				}
				longjmp(((CFiberBase*)fib)->ret_jb,1);//メインへ戻る
				
			}
			static void resume_(){
				int fib;//復帰用のジャンプ台
				__asm{
					mov eax,[ebp+4];
					mov fib,eax;
				}
				longjmp(((CFiberBase*)fib)->func_jb,1);//呼び出し先関数へ戻る
				
			}

		public:
			CFiberBase(CFiber* cf);//コンストラクタ
			~CFiberBase();//デストラクタ
			void _Suspend();//中断。Process内で呼び出す
			bool _Run();//使用者が呼び出す
			int _GetStackRest(){//内部用。残りスタックサイズを調べる
				int now_sp;
				__asm mov now_sp,esp;
				return now_sp-(int)stack_mem;
			}
			int _GetStackRest_Out(){//外部用。残りスタックサイズを返す	
				return StackMemRest-(int)stack_mem;
			}
			inline bool _isFiberEnd(){return isEnd;}//ファイバが終了したかどうか

		};
	};
};