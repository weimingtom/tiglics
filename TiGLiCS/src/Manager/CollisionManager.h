#pragma once
#include "Base/Base.h"
#include "Base/Define.h"
namespace TiGLiCS{
	namespace Collision2D{
		class  CCollisionData2D{
		public:
			Object::CSprite2D * pSpr2D;	//判定用スプライト座標
			bool isAbsPos;				//絶対座標かどうか(回転させるかも含む)
			//コンストラクタ
			CCollisionData2D(Object::CSprite2D * pSpr2D,bool isAbsPos=false){
				this->pSpr2D=pSpr2D;
				this->isAbsPos=isAbsPos;
			}
			//デストラクタ
			virtual ~CCollisionData2D(){
			}
			virtual void UpdatePos()=0;	///衝突位置更新
			virtual eCollisionType GetCollisionType()=0;///衝突判定のタイプ
		};
		typedef std::list<Collision2D::CCollisionData2D*> CollisionData2DList;

		bool isCollision2D(CCollisionData2D * pCol1,CCollisionData2D* pCol2);

		class  CPoint2DCollisionData:public CCollisionData2D{
			//2D点の座標データ
			Selene::Math::Vector2D pos;//座標
		public:
			Selene::Math::Vector2D retpos;//座標
			CPoint2DCollisionData(Object::CSprite2D * pSpr2D,Selene::Math::Vector2D &pos,bool isAbsPos)
				:CCollisionData2D(pSpr2D,isAbsPos)
				,pos(pos){
			}
			void UpdatePos();
			eCollisionType GetCollisionType(){return coPoint2D;}
			//Math::Vector2D GetCollisionPos();//あたり判定用の位置を返す。
		};

		class  CLine2DCollisionData:public CCollisionData2D{
			//2D点の座標データ
			Selene::Collision::CLine2D pos;//座標
		public:
			Selene::Collision::CLine2D retpos;//座標
			CLine2DCollisionData(Object::CSprite2D * pSpr2D,Selene::Collision::CLine2D &pos,bool isAbsPos)
				:CCollisionData2D(pSpr2D,isAbsPos)
				,pos(pos){
			}
			void UpdatePos();
			eCollisionType GetCollisionType(){return coLine2D;}
			//Collision::CLine2D GetCollisionPos();//あたり判定用の位置を返す。
		};
		class  CCircle2DCollisionData:public CCollisionData2D{
			//2D点の座標データ
			Selene::Collision::CCircle pos;//座標
		public:
			Selene::Collision::CCircle retpos;//座標
			CCircle2DCollisionData(Object::CSprite2D * pSpr2D,Selene::Collision::CCircle &pos,bool isAbsPos)
				:CCollisionData2D(pSpr2D,isAbsPos)
				,pos(pos){
			}
			void UpdatePos();
			eCollisionType GetCollisionType(){return coCircle2D;}
			//Collision::CCircle GetCollisionPos();//あたり判定用の位置を返す。
		};
		class  CPolygon2DCollisionData:public CCollisionData2D{
			//2D点の座標データ
			Selene::Math::Vector2D * pos;//座標
			Selene::Math::Vector2D * workpos;//座標
		public:
			Selene::Collision::CPolygon2D retpos;//作業用座標
			Sint32 pointNum;//個数
			CPolygon2DCollisionData(Object::CSprite2D * pSpr2D,Selene::Math::Vector2D * pos,Sint32 pointNum,bool isAbsPos)
				:CCollisionData2D(pSpr2D,isAbsPos){
					this->pos=pos;
					this->workpos=NULL;
					this->pointNum=pointNum;
			}
			~CPolygon2DCollisionData(){
				delete pos;
				SAFE_DELETE(workpos);
				//DMessageBox("a");
			}
			void UpdatePos();
			eCollisionType GetCollisionType(){return coPolygon2D;}
			//Collision::CPolygon2D GetCollisionPos();//あたり判定用の位置を返す。
		};
		/**
			@brief 衝突判定戻り値クラス
			@author my04337

			衝突判定での戻り値クラス。
		*/
		class  CCollisionResult2D{
		public:
			/**
				@brief 衝突判定戻り値構造体
				@author my04337

				この構造体に衝突場所と相手の情報が格納される。
			*/
			typedef struct tResult{
				///自分の当たり判定番号
				int srcNum;
				///相手の当たり判定番号
				int dstNum;
				///衝突したオブジェクトへのポインタ
				Object::CSprite2D * dstObj;
			};
			/**
				@brief 衝突判定戻り値型
				@author my04337

				衝突判定の戻り値型
			*/
			typedef std::list<tResult*> tResultList;
			tResultList ResultList;//衝突判定戻り値リスト
			/**
				@brief デストラクタ
				@author my04337	
			*/
			~CCollisionResult2D(){
				for(tResultList::iterator it=ResultList.begin();it!=ResultList.end();++it){
					delete *it;
				}
			}
			/**
				@brief 衝突結果の追加[内部用]
				@author my04337

				衝突結果を格納する
			*/
			void AddResult(int srcNum,int dstNum,Object::CSprite2D * dstObj){
				tResult * ret=new tResult;
				ret->srcNum=srcNum;
				ret->dstNum=dstNum;
				ret->dstObj=dstObj;
				ResultList.push_back(ret);
			}
			/**
				@brief 衝突結果数の取得
				@author my04337
				@return 衝突結果数

				衝突結果の数を取得する。
			*/
			int GetResultNum(){return (int)ResultList.size();}
		};
	};

	namespace Manager{
		class  CCollisionManager2D{
			Object::PtrPriorityList CollisionList;//当たり判定用リスト
			CPage* pPage;	//ページクラス
		public:
			CCollisionManager2D(CPage * pPage);
			void RegisterCollisionObject(Object::CSprite2D* pObj);//当たり判定の登録
			void UnRegisterCollisionObject(Object::CSprite2D* pObj);//当たり判定の登録解除
			int CollisionCheck(Object::CSprite2D * srcObj,Collision2D::CCollisionResult2D * &result);//衝突チェック。戻り値はdeleteをする必要あり
		};
	};
};