#include "Manager/Collision.h"
#include "Objects/Sprite2D.h"
#include "Engine/Engine.h"
using namespace TiGLiCS;
using namespace Manager;
using namespace TiGLiCS::Collision2D;
using namespace TiGLiCS::Object;
using namespace std;
void CPoint2DCollisionData::UpdatePos(){
	//あたり判定用の位置を返す。
	if(isAbsPos){//絶対座標なら
		retpos=pos;
	}else{
		float px=-Math::Sin(pSpr2D->Angle)*pos.x+Math::Cos(pSpr2D->Angle)*pos.y;
		float py= Math::Cos(pSpr2D->Angle)*pos.x+Math::Sin(pSpr2D->Angle)*pos.y;
		retpos= Math::Vector2D(px+pSpr2D->pos.x,py+pSpr2D->pos.y);
	}
}

void CLine2DCollisionData::UpdatePos(){
	//あたり判定用の位置を返す。
	if(isAbsPos){//絶対座標なら
		retpos= pos;
	}else{
		float px1=-Math::Sin(pSpr2D->Angle)*pos.vStart.x+Math::Cos(pSpr2D->Angle)*pos.vStart.y;
		float py1= Math::Cos(pSpr2D->Angle)*pos.vStart.x+Math::Sin(pSpr2D->Angle)*pos.vStart.y;
		float px2=-Math::Sin(pSpr2D->Angle)*pos.vEnd.x+Math::Cos(pSpr2D->Angle)*pos.vEnd.y;
		float py2= Math::Cos(pSpr2D->Angle)*pos.vEnd.x+Math::Sin(pSpr2D->Angle)*pos.vEnd.y;
		retpos= Collision::CLine2D(px1+pSpr2D->pos.x,py1+pSpr2D->pos.y,
			px2+pSpr2D->pos.x,py2+pSpr2D->pos.y);
	}
}

void CPolygon2DCollisionData::UpdatePos(){
	//あたり判定用の位置を返す。
	if(isAbsPos){//絶対座標なら
		retpos=Collision::CPolygon2D(this->pointNum,pos);
	}else{
		
		SAFE_DELETE(workpos);
		workpos=new Math::Vector2D[pointNum];
		for(int i=0;i<pointNum;++i){
			float px=-Math::Sin(pSpr2D->Angle)*pos[i].x+Math::Cos(pSpr2D->Angle)*pos[i].y;
			float py= Math::Cos(pSpr2D->Angle)*pos[i].x+Math::Sin(pSpr2D->Angle)*pos[i].y;
			workpos[i]=Math::Vector2D(px+pSpr2D->pos.x,py+pSpr2D->pos.y);
		}
		retpos= Collision::CPolygon2D(pointNum,workpos);
		
	}
}

void CCircle2DCollisionData::UpdatePos(){
	//あたり判定用の位置を返す。
	if(isAbsPos){//絶対座標なら
		retpos= pos;
	}else{
		float px=-Math::Sin(pSpr2D->Angle)*pos.vCenter.x+Math::Cos(pSpr2D->Angle)*pos.vCenter.y;
		float py= Math::Cos(pSpr2D->Angle)*pos.vCenter.x+Math::Sin(pSpr2D->Angle)*pos.vCenter.y;
		retpos= Collision::CCircle(px+pSpr2D->pos.x,py+pSpr2D->pos.y,pos.fRadius );
	}
}


//-------------------------------------------------------------------------

//--------------------------------------------------------------------------

CCollisionManager2D::CCollisionManager2D(CPage *pPage){
	this->pPage=pPage;
}
void CCollisionManager2D::RegisterCollisionObject(CSprite2D * pObj){//登録
	CollisionList.insert(pObj->GetCObjectContainer()); 
}
void CCollisionManager2D::UnRegisterCollisionObject(CSprite2D * pObj){//解除
	PtrPriorityList::iterator it=CollisionList.find(pObj->GetCObjectContainer());
	if(it!=CollisionList.end()){
		CollisionList.erase(it);
	}
}
int CCollisionManager2D::CollisionCheck(CSprite2D *srcObj,CCollisionResult2D* &result){
	//当たり判定チェック。
	int idst=0,isrc=0;
	result=new CCollisionResult2D();
	CollisionData2DList* srccl=srcObj->GetCollisionList2D();
	for(PtrPriorityList::iterator it=CollisionList.begin();it!=CollisionList.end();++it){
		CSprite2D* dstObj=(CSprite2D*)(*it)->pObj;
		if(!(*it)->isDead && dstObj!=srcObj){//死亡しておらず、自分自身ではないとき
			CollisionData2DList* cl=dstObj->GetCollisionList2D();
			idst=0;
			for(CollisionData2DList::iterator itc=cl->begin();itc!=cl->end();++itc,++idst){
				isrc=0;
				for(CollisionData2DList::iterator itcsrc=srccl->begin();itcsrc!=srccl->end();++itcsrc,++isrc){
					if(isCollision2D(*itc,*itcsrc)){
						result->AddResult(isrc,idst,dstObj);
					}
				}
				
			}
		}
	}
	return result->GetResultNum();
}

//--------------------------------------------------------------------------

bool TiGLiCS::Collision2D::isCollision2D(CCollisionData2D * pCol1,CCollisionData2D* pCol2){
	
	//ぶつかったかどうか
	Bool bRet=false;
	eCollisionType eCol1,eCol2;
	eCol1=pCol1->GetCollisionType();
	eCol2=pCol2->GetCollisionType();
	
	//if(!(eCol1> CCollisionData2D::coStart && eCol1< CCollisionData2D::coDummy
	//	&& eCol2> CCollisionData2D::coStart && eCol2< CCollisionData2D::coDummy)) return false;

	if(eCol1>eCol2){//条件を減らすため
		swap<CCollisionData2D*>(pCol1,pCol2);
		swap<eCollisionType>(eCol1,eCol2);
		//pTmp=pCol1;pCol1=pCol2;pCol2=pTmp;
		//eTmp=eCol1;eCol1=eCol2;eCol2=eTmp;
	}
	
	switch(eCol1){
	case coPoint2D:
		switch(eCol2){
		case coPoint2D:
			bRet=Collision::Point_Point(((CPoint2DCollisionData*)pCol1)->retpos,
				((CPoint2DCollisionData*)pCol2)->retpos);break;
		case coLine2D:
			bRet=Collision::Point_Line(((CPoint2DCollisionData*)pCol1)->retpos,
				((CLine2DCollisionData*)pCol2)->retpos);break;
		case coCircle2D:
			bRet=Collision::Point_Circle(((CPoint2DCollisionData*)pCol1)->retpos,
				((CCircle2DCollisionData*)pCol2)->retpos);break;
		case coPolygon2D:
			bRet=Collision::Point_Polygon(((CPoint2DCollisionData*)pCol1)->retpos,
				((CPolygon2DCollisionData*)pCol2)->retpos);break;
		default:bRet=false;
		}break;
	case coCircle2D:
		switch(eCol2){
		case coCircle2D:
			bRet=Collision::Circle_Circle(((CCircle2DCollisionData*)pCol1)->retpos,
				((CCircle2DCollisionData*)pCol2)->retpos);break;
		case coLine2D:
			bRet=Collision::Circle_Line(((CCircle2DCollisionData*)pCol1)->retpos,
				((CLine2DCollisionData*)pCol2)->retpos);break;
		case coPolygon2D:
			bRet=Collision::Circle_Polygon(((CCircle2DCollisionData*)pCol1)->retpos,
				((CPolygon2DCollisionData*)pCol2)->retpos);break;
		default:bRet=false;
		}break;
	case coLine2D:
		switch(eCol2){
		case coLine2D:
			bRet=Collision::Line_Line(((CLine2DCollisionData*)pCol1)->retpos,
				((CLine2DCollisionData*)pCol2)->retpos);break;
		case coPolygon2D:
			bRet=Collision::Line_Polygon(((CLine2DCollisionData*)pCol1)->retpos,
				((CPolygon2DCollisionData*)pCol2)->retpos);break;
		default:bRet=false;
		}break;
	case coPolygon2D:
		switch(eCol2){
		case coPolygon2D:
			bRet=Collision::Polygon_Polygon(((CPolygon2DCollisionData*)pCol1)->retpos,
				((CPolygon2DCollisionData*)pCol2)->retpos);break;
		default:bRet=false;
		}break;
	default:bRet=false;
	}
	
	return bRet;
}