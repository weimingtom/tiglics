#pragma once
#include "Base/Base.h"
#include "Manager/CollisionManager.h"
#include "Objects/Object.h"
//2Dスプライトオブジェクト
namespace TiGLiCS{
	namespace Object{
		/**
			@brief 2Dスプライトクラス
			@author my04337

			このクラスは、2Dでのオブジェクトの描画,衝突判定の簡単化<br>
			を行うために作成された。通常の2Dシューティングやアクション系ゲームでは<br>
			このクラスを使用することで手間の軽減がはかれると考える。
		*/
		class  CSprite2D:public ISprite2D,public CObject{
			bool bCollisionDetect2D;//あたり判定処理を行うか
			Collision2D::CollisionData2DList CollisionList2D;//あたり判定のリスト
			void UpdateCollisionData();//当たり判定更新
		public:	
			///描画マネージャへのポインタ
			Manager::CRenderManager	*pRenderManager;
			///スプライト座標
			Selene::Math::Point2DF pos;
			///スプライトの角度
			Sint32 Angle;
			/**
				@brief コンストラクタ
				@author my04337
				@param pPage [in] ページへのポインタ
				@param pos [in] 座標
				@param Angle [in] 角度
				@param ProcessPriority [in] 処理優先度
				
				コンストラクタ。角度はSelene式
			*/
			CSprite2D(CPage *pPage,
					  Selene::Math::Point2DF &pos,//スプライト座標
					  Sint32 Angle,
					  Sint32 ProcessPriority//処理優先度
					  );
			virtual ~CSprite2D();//デストラクタ

			//当たり判定系
			Collision2D::CollisionData2DList * GetCollisionList2D(){return &CollisionList2D;}//当たり判定リストの

			int AddCollisionData(Collision2D::CCollisionData2D * pCollisionData2D);//当たり判定追加
			/**
				@brief 衝突判定追加(四角形)
				@author my04337
				@param cpos [in] 衝突判定枠
				@param isAbsPath [in] 絶対座標かどうか
				@return 衝突判定ID

				四角形の衝突判定を追加する。相対座標とするとオブジェクトの座標、回転が反映される。<br>
				戻り値は衝突判定IDで、衝突判定の追加順に<br>
				0 , 1 , 2 , ... といった値となる。<br>
				また、衝突判定が有効な時には追加できないため、一時的に無効化する必要がある。
			*/
			int AddCollisionData(Selene::Math::Rect2DF &cpos,bool isAbsPath);//当たり判定(四角形)

			/**
				@brief 衝突判定追加(円)
				@author my04337
				@param cpos [in] 衝突判定枠
				@param isAbsPath [in] 絶対座標かどうか
				@return 衝突判定ID

				円の衝突判定を追加する。相対座標とするとオブジェクトの座標、回転が反映される。<br>
				戻り値は衝突判定IDで、衝突判定の追加順に<br>
				0 , 1 , 2 , ... といった値となる。<br>
				また、衝突判定が有効な時には追加できないため、一時的に無効化する必要がある。
			*/
			int AddCollisionData(Selene::Collision::CCircle &cpos,bool isAbsPath);//当たり判定(円)

			/**
				@brief 衝突判定追加(線)
				@author my04337
				@param cpos [in] 衝突判定枠
				@param isAbsPath [in] 絶対座標かどうか
				@return 衝突判定ID

				線の衝突判定を追加する。相対座標とするとオブジェクトの座標、回転が反映される。<br>
				戻り値は衝突判定IDで、衝突判定の追加順に<br>
				0 , 1 , 2 , ... といった値となる。<br>
				また、衝突判定が有効な時には追加できないため、一時的に無効化する必要がある。
			*/
			int AddCollisionData(Selene::Collision::CLine2D &cpos,bool isAbsPath);//当たり判定(線)
			
			/**
				@brief 衝突判定追加(点)
				@author my04337
				@param cpos [in] 衝突判定枠
				@param isAbsPath [in] 絶対座標かどうか
				@return 衝突判定ID

				点の衝突判定を追加する。相対座標とするとオブジェクトの座標、回転が反映される。<br>
				戻り値は衝突判定IDで、衝突判定の追加順に<br>
				0 , 1 , 2 , ... といった値となる。<br>
				また、衝突判定が有効な時には追加できないため、一時的に無効化する必要がある。
			*/
			int AddCollisionData(Selene::Math::Vector2D &cpos,bool isAbsPath);//当たり判定(点)

			/**
				@brief 衝突判定追加(ポリゴン)
				@author my04337
				@param vecArray [in] 衝突判定枠
				@param vecNum [in] 衝突判定点数
				@param isAbsPath [in] 絶対座標かどうか
				@return 衝突判定ID

				点の衝突判定を追加する。相対座標とするとオブジェクトの座標、回転が反映される。<br>
				戻り値は衝突判定IDで、衝突判定の追加順に<br>
				0 , 1 , 2 , ... といった値となる。<br>
				また、衝突判定が有効な時には追加できないため、一時的に無効化する必要がある。
			*/
			int AddCollisionData(Selene::Math::Vector2D *vecArray,Sint32 vecSize,bool isAbsPath);//当たり判定(点)

			/**
				@brief 衝突判定枠描画
				@author my04337
				@param Priority [in] 描画優先度

				衝突判定枠の描画を行う。描画色は黒である。
			*/
			void DrawCollisionData(Sint32 Priority);

			/**
				@brief アップデート
				@author my04337				

				衝突判定の更新と待機を行う。
			*/
			virtual void Update();//更新処理上書き
			/**
				@brief アップデート
				@author my04337				

				衝突判定の更新と待機を行う。指定フレーム待機
			*/
			virtual void Update(Sint32 FrameCount);//更新処理上書き
			
			/**
				@brief 衝突判定有効化
				@author my04337

				衝突判定を有効にする。
			*/
			void EnableCollisionDetect();//当たり判定を有効へ
			/**
				@brief 衝突判定無効化
				@author my04337

				衝突判定を無効にする。
			*/
			void DisableCollisionDetect();//当たり判定を無効へ

			/*
				@brief　衝突判定
				@author my04337
				@param result [out] 衝突判定結果
				@return 衝突個数

				他の2Dスプライトとの衝突判定を行う。<br>
				戻り値が0ではないときは、必ずresultに対しdeleteを使うこと<br>
				(使わない場合、メモリリークとなる)
			*/
			int CollisionCheck2D(Collision2D::CCollisionResult2D * &result);//衝突チェック
		};
	};
};