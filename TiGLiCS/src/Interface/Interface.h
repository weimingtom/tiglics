#pragma once
#include "Base/Base.h"
#include "Base/Configure.h"

namespace TiGLiCS{
	namespace Manager{		
		class  IFrameManager{
		public:
			virtual ~IFrameManager(){};
			virtual void BeforeProcess(void)=0;
			virtual void OnSceneManagerReset(void)=0;
			virtual void AfterProcess(void)=0;
		};
	}
	namespace Object{
		class  IFiber{//ファイバクラス。基底クラスとする
		public:
			virtual void Process()=0;//実際の処理。
			virtual void Suspend()=0;//中断。Process内で呼び出す
			virtual bool Run()=0;//使用者が呼び出す
			virtual int GetStackRest()=0;//スタックの残りを返す
			virtual bool isFiberEnd()=0;//ファイバが終了したかどうか
		};
		class  IObject{
		public:
			virtual ~IObject(){};
			virtual Sint32 GetProcessPriority(void)=0;
			virtual void Init(void)=0;
			virtual void Process(void)=0;//処理
			virtual void Draw(void)=0;//描画
			virtual void Release(void)=0;//オブジェクトがタスクから外される直前に呼ばれる
			virtual void BeforeRenderBegin(void)=0;//Beginする前
			virtual void OnDie(void)=0;//オブジェクト死亡時
			virtual void OnUpdate(void)=0;//Updateが呼ばれたとき
			virtual void Update()=0;//アップデート処理
			virtual bool isDead()=0;
			virtual void Die()=0;//死亡させる
			virtual bool _RunProcess()=0;//プロセス実行。
			virtual void _SuspendProcess()=0;
			virtual int GetRestProcessStack()=0;
			virtual void Update(Sint32 FrameNum)=0;//指定フレーム数待機
			virtual CObjectContainer *GetCObjectContainer()=0;
			virtual void SetCObjectContainer(CObjectContainer *pObjectContainer)=0;
		};
		
		class  ISprite2D{
		public:	
			virtual ~ISprite2D(){};
			virtual int AddCollisionData(Collision2D::CCollisionData2D * pCollisionData2D)=0;//当たり判定追加
			virtual int AddCollisionData(Selene::Math::Rect2DF &cpos,bool isAbsPath)=0;//当たり判定(四角形)
			virtual int AddCollisionData(Selene::Collision::CCircle &cpos,bool isAbsPath)=0;//当たり判定(円)
			virtual int AddCollisionData(Selene::Collision::CLine2D &cpos,bool isAbsPath)=0;//当たり判定(線)
			virtual int AddCollisionData(Selene::Math::Vector2D &cpos,bool isAbsPath)=0;//当たり判定(点)
			virtual void Update()=0;//更新処理上書き
			virtual void Update(Sint32 FrameCount)=0;//更新処理上書き
			virtual void EnableCollisionDetect()=0;//当たり判定を有効へ
			virtual void DisableCollisionDetect()=0;//当たり判定を無効へ
			virtual int CollisionCheck2D(Collision2D::CCollisionResult2D * &result)=0;//衝突チェック
		};
	};
};
